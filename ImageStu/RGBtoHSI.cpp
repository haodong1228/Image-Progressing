#include "StdAfx.h"
#include "CRGBtoHSI.h"
#include "ImagePara.h"
#include <cmath>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


double MIN_NUM=0.0;

CRGBtoHSI::CRGBtoHSI( CBaseColorInfo & colorInfo)
{
		_colorInfo = colorInfo;
}


CRGBtoHSI::CRGBtoHSI( CColorSpaceInfo & hsiInfo)
{
		_hsi = hsiInfo;
		_h = _hsi.GetPara1();
		_s = _hsi.GetPara2();
		_i = _hsi.GetPara2();
}

CRGBtoHSI::~CRGBtoHSI(){

}

void CRGBtoHSI::RGBToHSI(){

	//RGB归一化
	RGBPercent();

	int red = _colorInfo.GetRed();
	int green = _colorInfo.GetGreen();
	int blue = _colorInfo.GetBlue();

	//强度
	_i = (_r + _g + _b) / 3.0;

	//饱和度
	int sum = red + green + blue;
	if(sum != 0 && ! (red == blue && red == green && blue == green ))
	{
		int minV = _colorInfo.GetRed();
		if(minV > _colorInfo.GetGreen())
		{
			minV = _colorInfo.GetGreen();
		}
		if(minV > _colorInfo.GetBlue())
		{
			minV = _colorInfo.GetBlue();
		}
		//饱和度
		_s = 1 - minV * 3.0 / sum;
	}
	else{
		_s = 0;
	}

	//求色度H
	if( (red == blue && red == green && green == blue))
	{
		_h = 0.0;
	}
	else{
		//转换成HSI
		if(blue <= green)
			_h = acos( CalcMedium() );
		else
			_h = 2 * PI - acos( CalcMedium() );
		
	}

	//设置hsi系数
    _hsi.SetPara1(_h);
	_hsi.SetPara2(_s);
	_hsi.SetPara3(_i);

}

//将HSI的值映射到0~255之间
void CRGBtoHSI::ScaleHSI(){
	int red = (int)(_h * 255.0 / (2 * PI));
	int green = (int)_s * 255;
	int blue = (int)_i * 255;

	_result.SetRed(red);
	_result.SetBlue(blue);
	_result.SetGreen(green);

}

//读取结果
CBaseColorInfo CRGBtoHSI::GetResult() const{
	return _result;
}

//读取HSI
CColorSpaceInfo CRGBtoHSI::GetHSI() const{
	return _hsi;
}

void CRGBtoHSI::SetHSI(CColorSpaceInfo info)
{
	_hsi = info;
	_h = info.GetPara1();
	_s = info.GetPara2();
	_i = info.GetPara3();

}

//读取RGB
CColorSpaceInfo CRGBtoHSI::GetRGB() const{

	return _rgb;
}

//从HSI转换到RGB
void CRGBtoHSI::HSIToRGB(){
	double r,g,b;

	//修改H角度
	//_h+=PI/3*3;
	//修改饱和度S
	//_s*=0.5;
	//修改亮度I
	//_i*=0.5;
	CString str;
	if(fabs(_i) < MIN_NUM)
	{
		//黑色图像
		r = 0;
		g = 0;
		b = 0;
	}
	else if(fabs(_s) < MIN_NUM)
	{
		//饱和度为0，灰度图像
		r = g = b = _i; 
	}
	else{
		if( _h - 2 * PI / 3 < MIN_NUM){
			b = _i * (1.0 - _s);
			r = _i * (1 + _s * cos(_h) / cos(PI / 3 - _h));
			g = 3 * _i - (b + r);
			
		}
		else if(_h - 4 * PI / 3 < MIN_NUM) 
		{
			r = _i * (1 - _s);
			g=_i* (1+(_s*cos(_h-2*PI/3)/cos(PI-_h)));
			b = 3 * _i - (r + g);
		}
		else if(_h - 2 * PI < MIN_NUM)
		{
			g = _i * (1 - _s);
			b=_i*(1+_s*cos(_h-4*PI/3)/cos(5*PI/3-_h));
			r = 3 * _i - (g + b);
		}
	
	}
	
	_rgb.SetPara1(r);
	_rgb.SetPara2(g);
	_rgb.SetPara3(b);
}

//将RGB的值映射到0~255之间
void CRGBtoHSI::ScaleRGB(){
	int red = int (_rgb.GetPara1() * 255 + 0.5);
	int green = int (_rgb.GetPara2() * 255 + 0.5);
	int blue = int (_rgb.GetPara3() * 255 + 0.5);

	_result.SetRed(red);
	_result.SetGreen(green);
	_result.SetBlue(blue);

}

//-------------------------私有函数-------------------------------//

//RGB归一化
//将RGB三个分量转换成
void CRGBtoHSI::RGBPercent(){

	//归一化
	_r = _colorInfo.GetRed() * 1.0 / 255;
	_g = _colorInfo.GetGreen() * 1.0 / 255;
	_b = _colorInfo.GetBlue() * 1.0 / 255;

}

//求出最小值
double CRGBtoHSI::MinRGB(){

	int min = _colorInfo.GetRed();
	if(min > _colorInfo.GetGreen() )
	{
		min = _colorInfo.GetGreen();
	}
	if(min > _colorInfo.GetBlue() )
	{
		min = _colorInfo.GetBlue();
	}
	return min * 1.0 / 255.0;
}

//求出最大值
double CRGBtoHSI::MaxRGB(){

	int max = _colorInfo.GetRed();
	if(max < _colorInfo.GetGreen() )
	{
		max = _colorInfo.GetGreen();
	}
	if(max < _colorInfo.GetBlue() )
	{
		max = _colorInfo.GetBlue();
	}
	return max * 1.0 / 255.0;
}


//求出中间值
double CRGBtoHSI::CalcMedium(){
	//分子
	double son = 0.5 * ((_r - _g) + (_r - _b));
	//分母
	double mother = sqrt((_r - _g)*(_r - _g) + (_r - _b) * (_g - _b));

	if(fabs(mother) < MIN_NUM){
		return 0;
	}	
	else{
		return son / mother;
	}
}
