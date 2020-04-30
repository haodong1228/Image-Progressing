// BaseColorInfo.cpp: implementation of the CBaseColorInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseColorInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseColorInfo::CBaseColorInfo( int red , int green , int blue  )
{
	SetRed( red );
	SetGreen( green );
	SetBlue( blue );
}

CBaseColorInfo::~CBaseColorInfo()
{

}

/************************************************************************/
/*                            变量设置                                  */
/************************************************************************/
// 红
int CBaseColorInfo::GetRed() const{
	return _red;
}
void CBaseColorInfo::SetRed( int red ){

	if( red > 255 ){
		_red = 255;
	}
	else if( red < 0 ){
		_red = 0;
	}
	else{
		_red = red;
	}

}

// 绿
int CBaseColorInfo::GetGreen() const{
	return _green;
}
void CBaseColorInfo::SetGreen( int green ){
	
	if( green > 255 ){
		_green = 255;
	}
	else if( green < 0 ){
		_green = 0;
	}
	else{
		_green = green;
	}

}

// 蓝
int CBaseColorInfo::GetBlue() const{
	return _blue;
}
void CBaseColorInfo::SetBlue( int blue ){
	
	if( blue > 255 ){
		_blue = 255;
	}
	else if( blue < 0 ){
		_blue = 0;
	}
	else{
		_blue = blue;
	}

}

/************************************************************************/
/*                          运算符重载                                  */
/************************************************************************/
// 赋值运算符
CBaseColorInfo & CBaseColorInfo::operator =( CBaseColorInfo & pixel ){

	SetRed( pixel.GetRed() );
	SetGreen( pixel.GetGreen() );
	SetBlue( pixel.GetBlue() );

	return *this;

}

// 判断是否相同运算符
// 红、绿、蓝三个变量均相同则两个像素相同，负责不同
bool CBaseColorInfo::operator == ( CBaseColorInfo & pixel ){

	return ( _red == pixel.GetRed() 
		&& _green == pixel.GetGreen() 
		&& pixel.GetRed() );

}
