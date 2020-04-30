// CommonCheck.h: interface for the CCommonCheck class.
// 各种通用校验的实现
// 如数据非空、数字等校验
// 创建人：邓飞
// 创建时间：2007-1-14 8:41
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONCHECK_H__8AD75A18_4E3D_47A0_9ECB_941B660E4099__INCLUDED_)
#define AFX_COMMONCHECK_H__8AD75A18_4E3D_47A0_9ECB_941B660E4099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
class CCommonCheck  
{
public:
	CCommonCheck();
	virtual ~CCommonCheck();

public:
	// 空校验
	static BOOL IsEmpty( CString & source );
	// 空校验，为空给出提示
	static BOOL IsEmpty( CString & source, CString message );
	// 空校验，为空给出提示，并将焦点移到相应的控件
	static BOOL IsEmpty( CString & source, CString message, CWnd & ctrl );

	// 数字检验
	// 整数校验
	static BOOL IsInt( CString & source );
	// 整数校验，不是整数给出提示
	static BOOL IsInt( CString & source, CString message );
	// 整数校验，不是整数给出提示，并将焦点移到相应的控件
	static BOOL IsInt( CString & source, CString message, CWnd & ctrl );

	// 数字校验（可以是整数和小数）
	static BOOL IsNum( CString & source );
	// 数字校验，不是数字给出提示
	static BOOL IsNum( CString & source, CString message );
	// 数字校验，不是数字给出提示，并将焦点移到相应的控件
	static BOOL IsNum( CString & source, CString message, CWnd & ctrl );

};

#endif // !defined(AFX_COMMONCHECK_H__8AD75A18_4E3D_47A0_9ECB_941B660E4099__INCLUDED_)
