// ColorSpaceInfo.cpp: implementation of the CColorSpaceInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColorSpaceInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorSpaceInfo::CColorSpaceInfo()
{

}

CColorSpaceInfo::CColorSpaceInfo( double para1, double para2, double para3 ){
	_para1 = para1;
	_para2 = para2;
	_para3 = para3;
}

CColorSpaceInfo::~CColorSpaceInfo()
{

}

/************************************************************************/
/*                        操作符重载                                    */
/************************************************************************/
// 重载赋值操作符
CColorSpaceInfo & CColorSpaceInfo::operator =( CColorSpaceInfo info ){

	// 参数一
	SetPara1( info.GetPara1() );
	// 参数二
	SetPara2( info.GetPara2() );
	// 参数三
	SetPara3( info.GetPara3() );

	return *this;

}

/************************************************************************/
/*                          字段读取                                    */
/************************************************************************/

// 三参数
void CColorSpaceInfo::SetPara1(double para1){
	_para1 = para1;
}
double CColorSpaceInfo::GetPara1(){
	return _para1;
}

void CColorSpaceInfo::SetPara2(double para2){
	_para2 = para2;
}
double CColorSpaceInfo::GetPara2(){
	return _para2;
}


void CColorSpaceInfo::SetPara3(double para3){
	_para3 = para3;
}
double CColorSpaceInfo::GetPara3(){
	return _para3;
}
