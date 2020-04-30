// CommonCheck.cpp: implementation of the CCommonCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommonCheck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommonCheck::CCommonCheck()
{
   
}

CCommonCheck::~CCommonCheck()
{

}

/////////////////////////////////////////////////////////////////////////////
// 空校验
// 检验字符串是否为空
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
// 返回值：
//  BOOL：空，返回TRUE; 非空，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsEmpty( CString & source ){

	// 去除左右空格
	source.TrimLeft();
	source.TrimRight();

	if( source == "" ){
		return TRUE;
	}
	else{
		return FALSE;
	}

}

/////////////////////////////////////////////////////////////////////////////
// 空校验
// 检验字符串是否为空，如果为空给出错误提示
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，为空时给出的错误提示
// 返回值：
//  BOOL：空，返回TRUE; 非空，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsEmpty( CString & source, CString message ){

	if( IsEmpty( source ) ){
		AfxMessageBox( message );
		return TRUE;
	}
	else{
		return FALSE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// 空校验
// 检验字符串是否为空，如果为空给出错误提示，并将焦点移到相应的控件
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，为空时给出的错误提示
//  ctrl: CWnd，字符串产生的控件，为空时将焦点转移至此
// 返回值：
//  BOOL：空，返回TRUE; 非空，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsEmpty( CString & source, CString message, CWnd & ctrl ){

	if( IsEmpty( source, message ) == TRUE ){
		ctrl.SetFocus();
		return TRUE;
	}
	else{
		return FALSE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// 整数校验
// 检验字符串为整数
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
// 返回值：
//  BOOL：整数，返回TRUE; 不是整数，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsInt( CString & source ){

	BOOL result = TRUE;

	// 去除空格
	IsEmpty( source );

	int length = source.GetLength();
	for( int index = 0; index <= length - 1; index++ ){
		char num = source.GetAt( index );
		if( ( ( num < '0' || num > '9' ) &&  index != 0 )
			|| ( ( num < '0' || num > '9' ) &&  ( index == 0  &&  num != '-' ) ) ){
			result = FALSE;
			break;
		}
	}

	return result;

}

/////////////////////////////////////////////////////////////////////////////
// 整数校验
// 检验字符串是否为整数，如果不是整数给出错误提示
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是整数时给出的错误提示
// 返回值：
//  BOOL：整数，返回TRUE; 不是整数，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsInt( CString & source, CString message ){

	if( IsInt( source ) == FALSE ){
		AfxMessageBox(  message );
		return FALSE;
	}
	else{
		return TRUE;
	}

}

/////////////////////////////////////////////////////////////////////////////
// 整数校验
// 检验字符串是否为整数，如果不是整数给出错误提示，并将焦点移到相应的控件
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是整数时给出的错误提示
//  ctrl: CWnd，字符串产生的控件，为空时将焦点转移至此
// 返回值：
//  BOOL：整数，返回TRUE; 不是整数，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsInt( CString & source, CString message, CWnd & ctrl ){

	if( IsInt( source, message ) == FALSE ){
		ctrl.SetFocus();
		return FALSE;
	}
	else{
		return TRUE;
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// 数字校验
// 检验字符串为数字
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
// 返回值：
//  BOOL：数字，返回TRUE; 不是数字，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsNum( CString & source ){

	BOOL result = TRUE;
    
	// 去除空格
	IsEmpty( source );

	int length = source.GetLength();
	for( int index = 0; index <= length - 1; index++ ){
		
		char num = source.GetAt( index );

		/*******
		CString numStr;
		numStr.Format( "num is %c", num );
		MessageBox( NULL,  numStr, "CComonCheck类", NULL );
		if( num == '.' ){
			MessageBox( NULL, "是小数点", "CComonCheck类", NULL  );
		}
		else{
			MessageBox( NULL, "不是小数点", "CComonCheck类", NULL  );
		}
		*****/

		if( ( num >= '0' && num <= '9' ) || ( num == '.' && index != 0 ) || ( num == '-' && index == 0 ) ){
			result = TRUE;
		}
		else{
			result = FALSE;
			return result;
		}
	}

	return result;

}

/////////////////////////////////////////////////////////////////////////////
// 整数校验
// 检验字符串是否为数字，如果不是数字给出错误提示
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是数字时给出的错误提示
// 返回值：
//  BOOL：数字，返回TRUE; 不是数字，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsNum( CString & source, CString message ){

	if( IsNum( source ) == FALSE ){
		AfxMessageBox(  message );
		return FALSE;
	}
	else{
		return TRUE;
	}

}

/////////////////////////////////////////////////////////////////////////////
// 整数校验
// 检验字符串是否为数字，如果不是整数给出错误提示，并将焦点移到相应的控件
// 校验的过程中同时去除字符串两边的空格
// 参数：
//  source: CString，待校验的字符串;校验完毕后，其两边空格被去除
//  message: CString，不是数字时给出的错误提示
//  ctrl: CWnd，字符串产生的控件，为空时将焦点转移至此
// 返回值：
//  BOOL：数字，返回TRUE; 不是数字，返回FALSE
///////////////////////////////////////////////////////////////////////////////  
BOOL CCommonCheck::IsNum( CString & source, CString message, CWnd & ctrl ){

	if( IsNum( source, message ) == FALSE ){
		ctrl.SetFocus();
		return FALSE;
	}
	else{
		return TRUE;
	}
	
}


