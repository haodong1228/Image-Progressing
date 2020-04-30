#if !defined(AFX_RGBTOHSI_H__1B8D8923_E957_45A4_A3EF_B131COA8C971__INCLUDED_)
#define AFX_RGBTOHSI_H__1B8D8923_E957_45A4_A3EF_B131COA8C971__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include "BaseColorInfo.h"
#include "ColorSpaceInfo.h"

#define RINT(x) ((x)-floor(x)>0.5?ceil(x):floor(x))

class CRGBtoHSI
{
public:
	CRGBtoHSI(CBaseColorInfo & colorInfo);
	CRGBtoHSI(CColorSpaceInfo & hsiInfo);
	virtual ~CRGBtoHSI();

public:
	//RGB转HSI
	void RGBToHSI();
	//将HSI的值映射到0~255之间
	void ScaleHSI();
	//从HSI转换到RGB
	void HSIToRGB();
	//将RGB的映射到0~255之间
	void ScaleRGB();

public:
	//读取结果
	CBaseColorInfo GetResult() const;
	//读取RGB
	CColorSpaceInfo GetRGB() const;
	//读取HSI
	CColorSpaceInfo GetHSI() const;
	void SetHSI(CColorSpaceInfo info);

private:
	//RGB归一化
	void RGBPercent();
	//求出最小值
	double MinRGB();
	//求出最大值
	double MaxRGB();
	//求出中间值(求h时)
	double CalcMedium();

private:
	//RGB值(原值，传入)
	CBaseColorInfo _colorInfo;
	//结果
	CBaseColorInfo _result;

	//hsi系数
	CColorSpaceInfo _hsi;
	//rgb系数(0到1范围内)
	CColorSpaceInfo _rgb;

	//归一化后的RGB
	double _r;
	double _g;
	double _b;

	//直接计算出的hsi
	double _h;
	double _s;
	double _i;
};

#endif //!defined(AFX_RGBTOHSI_H__1B8D8923_E957_45A4_A3EF_B131COA8C971__INCLUDED_)