// DlgTask.cpp : implementation file
//

#include "stdafx.h"
#include "ImageStu.h"
#include "DlgTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTask dialog


CDlgTask::CDlgTask(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTask::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTask)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTask::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTask)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTask, CDialog)
	//{{AFX_MSG_MAP(CDlgTask)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTask message handlers

/************************************************************************/
/*                          字段处理                                    */
/************************************************************************/

// 实验任务
void CDlgTask::SetTask( CString task ){
	_task = task;
}

/************************************************************************/
/*                          消息映射                                    */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// 初始化对话框, 映射WM_INITDIALOG消息
//////////////////////////////////////////////////////////////////////////
BOOL CDlgTask::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	SetDlgItemText( IDC_EDIT_TASK, _task );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
