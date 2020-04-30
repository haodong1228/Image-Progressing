#if !defined(AFX_DLGTASK_H__AD3176CC_3A0C_48F4_8BCD_81FE33F9DB0C__INCLUDED_)
#define AFX_DLGTASK_H__AD3176CC_3A0C_48F4_8BCD_81FE33F9DB0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
// DlgTask.h : header file
// 实验任务对话框
// 创建人: 邓飞
// 创建日期: 2008-8-31
/////////////////////////////////////////////////////////////////////////////

class CDlgTask : public CDialog
{
// Construction
public:
	CDlgTask(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTask)
	enum { IDD = IDD_DLG_TASK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTask)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// 实验任务
	void SetTask( CString task );

private:
	// 实验任务
	CString _task;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTASK_H__AD3176CC_3A0C_48F4_8BCD_81FE33F9DB0C__INCLUDED_)
