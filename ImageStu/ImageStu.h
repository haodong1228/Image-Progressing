// ImageStu.h : main header file for the IMAGESTU application
//

#if !defined(AFX_IMAGESTU_H__07C828EB_9BAC_456D_91D5_198DBA44563C__INCLUDED_)
#define AFX_IMAGESTU_H__07C828EB_9BAC_456D_91D5_198DBA44563C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageStuApp:
// See ImageStu.cpp for the implementation of this class
//

class CImageStuApp : public CWinApp
{
public:
	CImageStuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImageStuApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTU_H__07C828EB_9BAC_456D_91D5_198DBA44563C__INCLUDED_)
