// ImageStuDlg.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include "ImageStu.h"
#include "ImageStuDlg.h"
#include "DlgShowArray.h"
#include "CConnectedComponent.h"
#include "DlgTask.h"
#include "change.h"
#include "CRGBtoHSI.h"
#include "HuffmanMergeItem.h"
#include "ImgHuffman.h"
#include <math.h>
#include <sstream>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg dialog

CImageStuDlg::CImageStuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageStuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 图像已打开标记
	_flag = false;

}

void CImageStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageStuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImageStuDlg, CDialog)
	//{{AFX_MSG_MAP(CImageStuDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_FILE_OPEN, OnFileOpen)
	ON_WM_DESTROY()
	ON_COMMAND(IDC_FILE_SHOW_ARRAY, OnFileShowArray)
	ON_COMMAND(IDC_TEST, OnTest)
	ON_COMMAND(IDC_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDC_FULL_RED, OnFullRed)
	ON_COMMAND(IDC_RED_BLUE, OnRedBlue)
	ON_COMMAND(IDC_COLOR_BLACK, OnColorBlack)
	ON_COMMAND(IDC_GRAY_BLACK, OnGrayBlack)
	ON_COMMAND(IDC_DIRECT_ZOOM, OnDirectZoom)
	ON_COMMAND(IDC_GRAY_ADJUST, OnGrayAdjust)
	ON_COMMAND(IDC_NEAREST_INTERPOLATION, OnNearestInterpolation)
	ON_COMMAND(IDC_BILINEAR_INTERPOLATION, OnBilinearInterpolation)
	ON_COMMAND(IDC_move, Onmove)
	ON_COMMAND(IDC_Horizontal_mirroring, OnHorizontalmirroring)
	ON_COMMAND(IDC_Vertical_Mirroring, OnVerticalMirroring)
	ON_COMMAND(IDC_Transpose, OnTranspose)
	ON_COMMAND(IDC_Rotating, OnRotating)
	ON_COMMAND(IDC_NEGATE, OnNegate)
	ON_COMMAND(IDC_LOGARITHM, OnLogarithm)
	ON_COMMAND(IDC_SHIFTING, OnShifting)
	ON_COMMAND(IDC_FEN_DUAN, OnFenDuan)
	ON_COMMAND(IDC_WEI_PING_MIAN, OnWeiPingMian)
	ON_COMMAND(IDC_ZHI_FANG, OnZhiFang)
	ON_COMMAND(IDC_LIN_YU, OnLinYu)
	ON_COMMAND(IDC_JIA_QUAN, OnJiaQuan)
	ON_COMMAND(IDC_JUN_ZHI_QUICK, OnJunZhiQuick)
	ON_COMMAND(ID_JUN_ZHI_YUZHI, OnJunZhiYuzhi)
	ON_COMMAND(IDC_JIA_QUAN_QUICK, OnJiaQuanQuick)
	ON_COMMAND(IDC_FEI_XIAN_XING, OnFeiXianXing)
	ON_COMMAND(IDC_FEI_XIAN_XING_X, OnFeiXianXingX)
	ON_COMMAND(IDC_lpls, Onlpls)
	ON_COMMAND(IDC_ROBERT, OnRobert)
	ON_COMMAND(IDC_SOBEL, OnSobel)
	ON_COMMAND(IDC_GRAY_COLOR, OnGrayColor)
	ON_COMMAND(IDC_RGB_HSI_RGB, OnRgbHsiRgb)
	ON_COMMAND(IDC_FU_SHI, OnFuShi)
	ON_COMMAND(IDC_PEN_ZHANG, OnPenZhang)
	ON_COMMAND(IDC_OPEN, OnOpen)
	ON_COMMAND(IDC_CLOSE, OnClose)
	ON_COMMAND(IDC_BIAN_JIE, OnBianJie)
	ON_COMMAND(IDC_TIAN_CHONG, OnTianChong)
	ON_COMMAND(IDC_LIAN_TONG, OnLianTong)
	ON_COMMAND(IDC_XI_HUA, OnXiHua)
	ON_COMMAND(IDC_Huffman, OnHuffman)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStuDlg message handlers

BOOL CImageStuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageStuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageStuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	// 绘图
	CDC * pDC = GetDC();
	if( _flag == true ){
		
		// 已经打开文件
		SetDIBitsToDevice(
			  pDC->m_hDC  // 设备描述表
			, 0 // 设备描述表位图输出的起始逻辑x坐标
			, 0 // 设备描述表位图输出的起始逻辑y坐标
			, _infoHeader.biWidth // DIB的宽度
			, _infoHeader.biHeight // DIB的高度
			, 0 // DIB开始读取输出的像素数据的x位置
			, 0 // DIB开始读取输出的像素数据的y位置
			, 0 // DIB中像素的水平行号, 对应lpBits内存缓冲区的第一行数据
			, _infoHeader.biHeight  // DIB的行数
			, _lpBuf  // 像素数据
			, _bitmapInfo //BITMAPINFO数据
			, DIB_RGB_COLORS // 显示的颜色
		);

	}
	ReleaseDC( pDC );

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageStuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// 销毁对话框, 映射WM_DESTORY消息
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	if( _flag == true ){
		FreeData();
	}

	
}

/************************************************************************/
/*                           菜单                                       */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// "文件"-->"打开"(IDC_FILE_OPEN)
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	LPCTSTR lpszFilter = "BMP Files(*.bmp)|*.bmp|任何文件|*.*|";
	CFileDialog dlg( TRUE, lpszFilter, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		lpszFilter, NULL );
	// 文件名
	CString fileName;
	CFile file;
	// 打开文件
	if( dlg.DoModal() == IDOK ){

		// 文件名
		fileName = dlg.GetPathName();
		if( file.Open( fileName, CFile::modeRead | CFile::shareDenyNone, NULL ) == 0 ){
			// 读取文件失败
			AfxMessageBox( "无法打开文件", MB_OK, MB_ICONERROR );
			return;
		}

		// 读取文件头
		if( !ReadFileHeader( file ) ){
			return;
		}

		// 读取信息头 
		if( !ReadInfoHeader( file ) ){
			return;
		}

		// 若前面已有文件打开，则释放相应的数据
		if( _flag == true ){
			FreeData();
			_flag = false;
		}

		// 计算调色板颜色数量
		_numQuad = CalcQuadNum();
		// 读取调色板数据
		ReadQuad( file );

		// 判断图像类型
		_imageType = CalcImageType();

		// 读入图像数据
		ReadImageData( file );
		

		

		// 分配处理后的数据
		_processBuf = ( BYTE * )HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	
		// 宽度不是4的倍数则补齐
		DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
		if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
			dwBytes++;
		}
		dwBytes *= 4;

		
		
		Invalidate( );

		int width = _infoHeader.biWidth;
        int height = _infoHeader.biHeight;

		// 分配空间
		_colorData = new CBaseColorInfo[ width * height ];
		_grayData = new int[ width * height ];

		// 根据图像类型，将其转换成相应的图像数据
		if( _imageType == COLOR_24_BIT ){
			// 24位颜色图像
			BMPConvertColor24();
			
		}
		else if( _imageType == COLOR_8_BIT ){
			// 256彩色图像
			BMPConvertColor8();
		}
		else if( _imageType == GRAY_8_BIT ){
			// 256灰度图像
			BMPConvertGray8();
			// 将8位灰度数据转成用24位颜色
			Gray8ConvertColor24( _grayData, _colorData, width, height );
		}
		else{
			MessageBox( "暂不支持该图像类型" );
			// 关闭图像
			file.Close();
			FreeData();
			return;
		}

		// 图像读取完毕
		file.Close();
		_flag = true;

	}

}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"显示数组图像"
// 将转换后的24位彩色数据在对话框中显示
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileShowArray() 
{
	// TODO: Add your command handler code here

	if(_flag == FALSE){
		MessageBox("没有打开图像");
		return;
	}

	CDlgShowArray dlg;
	dlg.SetColorData( _colorData );
	dlg.SetWidth( _infoHeader.biWidth );
	dlg.SetHeight( _infoHeader.biHeight );
	dlg.DoModal();

}


//////////////////////////////////////////////////////////////////////////
// "文件"-->"保存"菜单
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::OnFileSave() 
{
	// TODO: Add your command handler code here
	if( ! _flag  ){
		MessageBox( "没有图片，无法保存" );
		return;
	}
	
	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
	if (dlg.DoModal()==IDOK)
	{
		SaveAsBmp( (LPTSTR)(LPCTSTR)dlg.GetPathName(), _lpBuf, _infoHeader.biWidth, _infoHeader.biHeight, _infoHeader.biBitCount,
			_quad );
	}
	
}


/************************************************************************/
/*                         私有函数                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// 读取文件头
// 参数:
//   file: CFile &, BMP文件
// 返回值:
//   BOOL, TRUE: 成功; FALSE: 失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadFileHeader( CFile &file ){

	// 读取文件头
	file.Read( &_fileHeader, sizeof( _fileHeader ) );
	// 判断是否为BMP文件
	if( _fileHeader.bfType != 0x4d42 ){
		// "BM"
		AfxMessageBox( "不是BMP文件", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	// 判断文件是否损坏(文件大小是否与文件头的信息一致)
	if( file.GetLength() != _fileHeader.bfSize ){
		AfxMessageBox( "文件已损坏", MB_OK, MB_ICONERROR );
		return FALSE;
	}

	return TRUE;
	
}


//////////////////////////////////////////////////////////////////////////
// 读取文件信息头
// 参数:
//   file: CFile &, 已经打开的BMP文件
// 返回值:
//   BOOL, TRUE成功; 其它失败
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::ReadInfoHeader( CFile &file ){

	// 读取文件信息头
	file.Read( &_infoHeader, sizeof( _infoHeader ) );

	// 将图片格式限定在8位图像
// 	if( _infoHeader.biBitCount != 8 ){
// 		AfxMessageBox( "必须为8位灰度图", MB_OK, MB_ICONERROR );
// 		return FALSE;
// 	}

	return TRUE;

}


//////////////////////////////////////////////////////////////////////////
// 释放数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::FreeData(){

	HeapFree( GetProcessHeap(), 0, _bitmapInfo );
	HeapFree( GetProcessHeap(), 0, _lpBuf );
	// 处理后的数据
	HeapFree( GetProcessHeap(), 0, _processBuf );
	// 灰度颜色数据
	delete [] _grayData;
	// 彩色颜色数据
	delete [] _colorData;



}

//////////////////////////////////////////////////////////////////////////
// 计算调色板颜色数量
// 参数: 无
// 返回值:
//   int, 调色板颜色数量
//////////////////////////////////////////////////////////////////////////
int CImageStuDlg::CalcQuadNum(){

	// 计算调色板数据
	int numQuad = 0;
	if( _infoHeader.biBitCount < 24){
		// 相当于2的biBitCount次方
		numQuad = ( 1 << _infoHeader.biBitCount );
	}

	return numQuad;

}

//////////////////////////////////////////////////////////////////////////
// 读取调色板数据
// 参数:
//   file: CFile &, BMP文件
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadQuad( CFile &file ){

	// 为图像信息pbi申请空间
	_bitmapInfo = ( BITMAPINFO * )HeapAlloc( 
		GetProcessHeap(), 
		0, 
		sizeof( BITMAPINFOHEADER ) + _numQuad * sizeof( RGBQUAD ) 
	);
	memcpy( _bitmapInfo, &_infoHeader, sizeof( _infoHeader ) );
	_quad = ( RGBQUAD * )( ( BYTE *)_bitmapInfo + sizeof( BITMAPINFOHEADER ) );

	// 读取调色板
	if( _numQuad != 0 ){
		file.Read( _quad, sizeof( RGBQUAD ) * _numQuad );
	}

}

//////////////////////////////////////////////////////////////////////////
// 判断是否为256色灰度图
// 判断依据，调色板中所有颜色的的RGB三个分量应该相等
// BOOL: TRUE为256色灰度图
//////////////////////////////////////////////////////////////////////////
BOOL CImageStuDlg::Is256Gray(){

	BOOL result = TRUE;
	for( int i = 0; i <= _numQuad - 1; i++ ){
		RGBQUAD color = *( _quad + i );
		//TRACE( "%d: %d, %d, %d\n", i, color.rgbRed,  color.rgbGreen, color.rgbBlue );
		if( !( color.rgbRed == color.rgbGreen && color.rgbRed == color.rgbBlue ) ){
			result = FALSE;
			break;
		}
	}
	
	return result;

}

//////////////////////////////////////////////////////////////////////////
// 读入图像数据
// 参数:
//   file: CFile &, BMP图像
// 返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ReadImageData( CFile &file ){

	// 为图像数据申请空间
	_infoHeader.biSizeImage = _fileHeader.bfSize - _fileHeader.bfOffBits;
	_lpBuf = ( BYTE *)HeapAlloc( GetProcessHeap(), 0, _infoHeader.biSizeImage );
	// 读取图像数据
	file.Read( _lpBuf, _infoHeader.biSizeImage );

}

//////////////////////////////////////////////////////////////////////////
// 判断图像类型
// 参数: 无
// 返回值: IMAGE_TYPE, 图像类型, 参数枚举IMAGE_TYPE的定义
//////////////////////////////////////////////////////////////////////////
IMAGE_TYPE CImageStuDlg::CalcImageType(){

	IMAGE_TYPE type = COLOR_24_BIT;
	if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_24 ){
		// 24彩色图像
		type = COLOR_24_BIT;
		//MessageBox( "24位图像" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_1 ){
		// 二值图像　
		type = GRAY_1_BIT;
		//MessageBox( "1位图像" );
	}
	else if( _infoHeader.biBitCount == IMAGE_TYPE_BIT_8 ){
		// 8位
		if( Is256Gray() ){
			// 8位灰度图像
			type = GRAY_8_BIT;
			//MessageBox( "8位灰度图像" );
		}
		else{
			// 8位彩色图像
			type = COLOR_8_BIT;
			//MessageBox( "8位彩色图像" );
		}
	}

	return type;

}

//////////////////////////////////////////////////////////////////////////
// 将BMP数据转换成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor24(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据

	int i,j;

	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * 3 * width + 3 * j;
			if( dwBytes % 3 != 0 ){
				index = i * dwBytes + 3 * j ;
			}
			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
			_colorData[ resultIndex ].SetRed( _lpBuf[ index  + 2 ] );
			_colorData[ resultIndex ].SetGreen( _lpBuf[ index  + 1 ] );
			_colorData[ resultIndex ].SetBlue( _lpBuf[ index ] );

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位彩色BMP数据转成24位颜色数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertColor8(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
// 	if( _colorFlag == true ){
// 		delete [] _colorData;
// 	}
// 	_colorData = new CBaseColorInfo[ width * height ];
// 	_colorFlag = true;


	int i,j;
// 	for( i = 0; i <= 100; i++ ){
// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
// 	}
// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j ;

			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
// 					i, j, index, resultIndex, width, height );
// 			}

// 			int red = _lpBuf[ index ] + 2;
// 			int green = _lpBuf[ index ] + 1;
// 			int blue = _lpBuf[ index ] + 0;
// 
// 			if( resultIndex <= width * height - 1 ){
// 			_colorData[ resultIndex ].SetRed( red );
// 			_colorData[ resultIndex ].SetGreen( green );
// 			_colorData[ resultIndex ].SetBlue( blue );
// 			}

			_colorData[ resultIndex ].SetRed( _quad[ _lpBuf[ index ] ].rgbRed );
			_colorData[ resultIndex ].SetGreen( _quad[ _lpBuf[ index ] ].rgbGreen );
			_colorData[ resultIndex ].SetBlue( _quad[ _lpBuf[ index ] ].rgbBlue );

// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );

// 			if( i <= 10 && j <= 10 ){
// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );
/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位灰度BMP数据转成8位灰度数据
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::BMPConvertGray8(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) / 32;
	if(((DWORD) _infoHeader.biWidth * _infoHeader.biBitCount) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	// 分配彩色数据
// 	if( _colorFlag == true ){
// 		delete [] _colorData;
// 	}
// 	_grayData = new BYTE[ width * height ];
// 	_grayFlag = true;


	int i,j;
// 	for( i = 0; i <= 100; i++ ){
// 		TRACE( "%d->%d,", i, _lpBuf[ i ] );
// 	}
// 	TRACE( "\n" );
	for( i = 0; i <= height - 1; i++ ){
		for( j = 0; j <= width - 1; j++ ){
			
			// BMP图片数据中的坐标
			DWORD index = i * dwBytes + j ;

			// 颜色数组中的坐标
			DWORD resultIndex = ( height - 1 - i ) * width + j;
// 			if( index >= _infoHeader.biSizeImage || resultIndex >= _infoHeader.biSizeImage ){
// 				TRACE( "*** i = %d, j = %d, index = %d, resultIndex = %d, widht = %d, height = %d \n", 
// 					i, j, index, resultIndex, width, height );
// 			}

// 			int red = _lpBuf[ index ] + 2;
// 			int green = _lpBuf[ index ] + 1;
// 			int blue = _lpBuf[ index ] + 0;
// 
// 			if( resultIndex <= width * height - 1 ){
// 			_colorData[ resultIndex ].SetRed( red );
// 			_colorData[ resultIndex ].SetGreen( green );
// 			_colorData[ resultIndex ].SetBlue( blue );
// 			}

			_grayData[ resultIndex ] = _lpBuf[ index ];


// 			TRACE( "%d,%d,%d\t", _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );

// 			if( i <= 10 && j <= 10 ){
// 			  TRACE( "(%d,%d,%d)->(%d,%d,%d) ", i,j,index, _colorData[ resultIndex ].GetRed(),
// 				_colorData[ resultIndex ].GetGreen(), 
// 				_colorData[ resultIndex ].GetBlue() );
/*			}*/

		}// for j
	}// for i 

}

//////////////////////////////////////////////////////////////////////////
// 将8位灰度数据转成用24位颜色
// 灰度图的RGB值均相同
// 参数:
//   grayData: BYTE *, 灰度数据
//   colorData: CBaseColorInfo *, 24位颜色数据
//   width: 图片宽度
//   height: 图片高度
//  返回值: 无
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::Gray8ConvertColor24( BYTE * grayData, 
										    CBaseColorInfo * colorData, 
											int width, 
											int height ){


	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

// 将8位灰度数据转成用24位颜色
void CImageStuDlg::Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height ){

	int length = width * height;
	for( int i = 0; i <= length - 1; i++ ){
		colorData[ i ].SetRed( grayData[ i ] );
		colorData[ i ].SetGreen( grayData[ i ] );
		colorData[ i ].SetBlue( grayData[ i ] );
	}

}

//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组,彩色图像)
// 参数:
//   colorData: CBaseColorInfo, 颜色数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( CBaseColorInfo * colorData, 
								   int width, 
								   int height ){

	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData( colorData );
	// 图像宽度
	dlg.SetWidth( width );
	// 图像高度
	dlg.SetHeight( height );
	// 显示对话框
	dlg.DoModal();

}




//////////////////////////////////////////////////////////////////////////
// 显示图像(通过图像数组, 灰度图像)
// 参数:
//   colorData: CBaseColorInfo, 灰度图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//////////////////////////////////////////////////////////////////////////
void CImageStuDlg::ShowPicByArray( int * grayData, 
								   int width, 
								   int height ){

	// 将灰度图像转成彩色图像
	CBaseColorInfo * colorData = new CBaseColorInfo[ width * height ];
	Gray8ConvertColor24( grayData, colorData, width, height );

	CDlgShowArray dlg;
	// 图像数据(24位彩色图像)
	dlg.SetColorData( colorData );
	// 图像宽度
	dlg.SetWidth( width );
	// 图像高度
	dlg.SetHeight( height );
	// 显示对话框
	dlg.DoModal();

	// 释放彩色图像
	delete [] colorData;

}











void CImageStuDlg::OnTest() 
{
	// TODO: Add your command handler code here
	int x, y;
	int width = 800;
	int height = 600;
	CBaseColorInfo * img = new CBaseColorInfo[ width * height ];
	for( x = 0; x < width; ++x ){
		for( y = 0; y < height; ++y ){
			int index = y * width + x;
			if( x % 10 == 0 ){
				img[ index ] = CBaseColorInfo( 255, 0, 0 );
			}
			else{
				img[ index ] = CBaseColorInfo( 0, 255, 0 );
			}
			
		}
	}

	// 显示图像
	ShowPicByArray( img, width, height );

	delete []img;
}


//////////////////////////////////////////////////////////////////////////
// 功能：保存BMP图片
// 参数：
//   bmpName: char *, 文件名(含路径、文件后缀)
//   imgBuf: unsigned char *, 图像数据
//   width: int, 图像宽度
//   height: int, 图像高度
//   biBitCount: int, 像素深度
//   pColorTable: RGBAUAD *, 颜色表
//////////////////////////////////////////////////////////////////////////
bool CImageStuDlg::SaveAsBmp( char * bmpName, 
							  unsigned char * imgBuf, 
							  int width, 
							  int height,
							  int biBitCount, 
							  RGBQUAD * pColorTable 
							 ){
	
	// 如果位图数据为空，则没有数据传入
	if( !imgBuf ){
		return false;
	}
	
	// 颜色表大小，以字节为单位，灰度图像颜色表为1024，彩色图像颜色表大小为0
	int colorTableSize = 0;
	if( biBitCount == 8 ){
		colorTableSize = 1024; // 感觉不一定正确
	} 
	
	// 将带存储图像数据每行字节数转为4的倍数
	int lineByte = ( width * biBitCount / 8 + 3 ) / 4 * 4;
	// 以二进制的写的方式打开文件
	FILE *fp = fopen( bmpName, "wb" );
	if( !fp ){
		return false;
	}
	
	// 申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;// bmp类型
	// bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof( BITMAPFILEHEADER ) 
		+ sizeof( BITMAPINFOHEADER )
		+ colorTableSize 
		+ lineByte * height; // 图像数据字节数
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	
	// bfOffBits是图像文件前三部分所需空间之和
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)  + colorTableSize;
	// 文件头写入文件
	fwrite( &fileHead, sizeof( BITMAPFILEHEADER ) , 1, fp );
	
	// 申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biSize = sizeof(BITMAPINFOHEADER); // 位图信息头结构的大小(40个字节)
	head.biWidth = width;// 图像宽度，以像素为单位
	head.biHeight = height;// 图像高度，以像素为单位
	head.biPlanes = 1;// 必须为1
	head.biBitCount = biBitCount; // 像素深度，每个像素的为数(bit数)
	head.biCompression = BI_RGB; // 图像是否压缩，一般是未压缩的
	head.biSizeImage = lineByte * height; // 实际的位图数据占据的字节数
	head.biXPelsPerMeter = 0; // 目标设备的水平分辨率
	head.biYPelsPerMeter = 0; // 目标设备的垂直分辨率
	head.biClrUsed = 0; // 本图像实际用到的颜色数
	head.biClrImportant = 0; // 本图像重要的颜色，如果为0，则所有的颜色均重要 
	
	// 写位图信息头进内存
	fwrite( &head, sizeof( BITMAPINFOHEADER ), 1, fp );
	
	// 如果图像时灰度图像，有颜色表，写入文件
	if( biBitCount == 8 ){
		fwrite( pColorTable, sizeof( RGBQUAD ), 256, fp );
	}
	
	// 写位图数据进文件
	fwrite( imgBuf, height * lineByte, 1, fp );
	
	// 关闭文件
	fclose( fp );
	
	return true;
	
}



void CImageStuDlg::OnFullRed() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo [size];
	for(int i = 0;i<size;++i){
		img[i]=CBaseColorInfo(255,0,0);
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnRedBlue() 
{
	// TODO: Add your command handler code here
	int width = 800;
	int height = 600;
	CBaseColorInfo * img = new CBaseColorInfo [ width * height ];
	for(int y = 0; y < height; y+=30 ){
		for(int x = 0; x < width; x+=40){	
			for(int h = 0; h < 30; h++){
				for(int w = 0; w < 40; w++){
					int index = (y+h) * width + (x+w);
					if((y%60==0&&x%80==0)||(y%60==30&&x%80==40)){
						img[ index ] = CBaseColorInfo( 255, 0, 0 );
					}
					else{
						img[ index ] = CBaseColorInfo( 0, 0, 255 );
					}
				}
			}
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnColorBlack() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("图片未打开!");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	CBaseColorInfo * newColor = new CBaseColorInfo [ width * height ];
	for(int y = 0; y < height; y++ ){
		for(int x = 0; x < width; x++ ){	
			int index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			int gray = 0.299*info.GetRed()+ 0.587*info.GetGreen()+ 0.114*info.GetBlue();
			newColor[ index ].SetRed( gray );
			newColor[ index ].SetGreen( gray );
			newColor[ index ].SetBlue( gray );
		}
	}
	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

void CImageStuDlg::OnGrayBlack() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	CBaseColorInfo * newColor = new CBaseColorInfo [ width * height ];
	for(int y = 0; y < height; y++ ){
		for(int x = 0; x < width; x++ ){	
			int index = y * width + x;
			CBaseColorInfo info = _colorData[index];
			int gray = info.GetRed();
			if(gray>=120){
				newColor[ index ] = CBaseColorInfo( 255, 255, 255 );
			}
			else{
				newColor[ index ] = CBaseColorInfo( 0, 0, 0 );
			}
		}
	}
	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

void CImageStuDlg::OnGrayAdjust() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	
	int level = 256 / 8;
	for(int i = 0; i < size; ++i){
		int oldGray = _grayData[ i ];
		int gray = oldGray / level * level;
		img[i] = gray;
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnDirectZoom() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;

	double scale = 0.5;
	int width = oldwidth * scale;
	int height = oldheight *scale;
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x / scale;
			int oldY = y / scale;

			int newIndex = y * width + x;
			int oldIndex = oldY * oldwidth + oldX;
			img[ newIndex ] = _colorData[ oldIndex ];
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}


void CImageStuDlg::OnNearestInterpolation() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;

	double scale = 1.5;
	int width = oldwidth * scale;
	int height = oldheight *scale;
	int size = width * height;
	int * img = new int[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x / scale +0.5;
			int oldY = y / scale +0.5;

			int newIndex = y * width + x;
			int oldIndex = oldY * oldwidth + oldX;
			img[ newIndex ] = _grayData[ oldIndex ];
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnBilinearInterpolation() 
{
	// TODO: Add your command handler code here
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int oldwidth = _infoHeader.biWidth;
	int oldheight = _infoHeader.biHeight;

	double scale = 1.5;
	int width = oldwidth * scale;
	int height = oldheight *scale;
	int size = width * height;
	int * img = new int[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x / scale;
			int oldY = y / scale;
			int Cx = oldX,Cy = oldY;
			int Bx = oldX + 1,By = oldY + 1;

			int CIndex = oldY * oldwidth + oldX;
			int DIndex = CIndex + 1;
			int AIndex = CIndex + oldwidth;
			int BIndex = DIndex + oldwidth;
			
			int gA = _grayData[ AIndex ];
			int gB = _grayData[ BIndex ];
			int gC = _grayData[ CIndex ];
			int gD = _grayData[ DIndex ];
			double gE = ( oldX - Cx ) * ( gB - gA ) + gA;
			double gF = ( oldX - Cx ) * ( gD - gC ) + gC;
			double gray = ( oldY - Cy) * ( gF - gE ) + gE;

			int newIndex = y * width + x;
			img[ newIndex ] = gray;

		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::Onmove() 
{
	// 平移
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	int tx = -20, ty = -20;

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = x - tx;
			int oldY = y - ty;
			int newIndex = y * width + x;
			if(oldX<0||oldX>=width||oldY<0||oldY>=height){
				img[ newIndex ] = CBaseColorInfo(255,255,255);
			}else{
				int oldIndex = oldY * width + oldX;
				img[ newIndex ] = _colorData[ oldIndex ];
			}		
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnHorizontalmirroring() 
{
	// 水平镜像
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int newX = - x + width - 1;
			int newIndex = y * width + newX;
			int oldIndex = y * width + x;
			img[ newIndex ] = _colorData[ oldIndex ];
					
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnVerticalMirroring() 
{
	// 垂直镜像
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int newY = - y + height - 1;
			int newIndex = newY * width + x;
			int oldIndex = y * width + x;
			img[ newIndex ] = _colorData[ oldIndex ];
					
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnTranspose() 
{
	// 转置
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int width = _infoHeader.biHeight;
	int height = _infoHeader.biWidth;	
	int size = width * height;
	CBaseColorInfo * img = new CBaseColorInfo[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int newIndex = y * width + x;
			int oldIndex = x * height + y;
			img[ newIndex ] = _colorData[ oldIndex ];
					
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnRotating() 
{
	// 旋转
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}
	int a = 20;
	int change_a = -a;
	double ca = cos( change_a * acos(-1.0) / 180);
	double sa = sin( change_a * acos(-1.0) / 180);

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int x = 0; x < width; x++){
		for(int y = 0; y < height; y++){
			int oldX = ca * x + sa * y + 0.5;
			int oldY = -sa * x + ca * y + 0.5;
			int newIndex = y * width + x;
			if(oldX<0||oldX>=width||oldY<0||oldY>=height){
				img[ newIndex ] = 255;
			}else{
				//int oldIndex = oldY * width + oldX;
				//img[ newIndex ] = _grayData[ oldIndex ];

				int Cx = oldX,Cy = oldY;
				int Bx = oldX + 1,By = oldY + 1;

				if(Bx>=width||By>=height){
					img[ newIndex ] = 255;
				}else{
					int CIndex = oldY * width + oldX;
					int DIndex = CIndex + 1;
					int AIndex = CIndex + width;
					int BIndex = DIndex + width;
					
					int gA = _grayData[ AIndex ];
					int gB = _grayData[ BIndex ];
					int gC = _grayData[ CIndex ];
					int gD = _grayData[ DIndex ];
					
					double gE = ( oldX - Cx ) * ( gB - gA ) + gA;
					double gF = ( oldX - Cx ) * ( gD - gC ) + gC;
					double gray = ( oldY - Cy) * ( gF - gE ) + gE;

					int newIndex = y * width + x;
					img[ newIndex ] = gray;	
				}
			}		
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnNegate() 
{
	// 图像反转
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	const int L = 255;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	for(int i = 0; i < size; i++){
		img[i] = L-1-_grayData[i];
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnLogarithm() 
{
	// 对数变换
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int c = 40;
	double const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	for(int i = 0; i < size; i++){
		img[i] = c*log(_grayData[i]/(LEVEL-1)+1)*(LEVEL-1);
	}


	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnShifting() 
{
	// 冥律变换
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	double c = 1;
	double y = 4.0;
	double const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	for(int i = 0; i < size; i++){
		img[i] = c*pow(_grayData[i]/(LEVEL-1),y)*(LEVEL-1);
	}


	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnFenDuan() 
{
	// 分段线性变换函数
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}
	
	double const LEVEL = 256;
	
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	/*int rmin=256,rmax=0;
	for(int i = 0; i < size; i++){
		if(_grayData[i]>rmax){
			rmax = _grayData[i];
		}
		if(_grayData[i]<rmin){
			rmin =_grayData[i];
		}
	}
	
	int r1=rmin,r2=rmax,s1=0,s2=LEVEL-1;
	*/
	int sum=0,avg=0;
	for(int i = 0; i < size; i++){
		sum+=_grayData[i];
	}
	avg = sum/size;
	int r1=avg,r2=avg,s1=0,s2=LEVEL-1;
	for( i = 0; i < size; i++){
		int gray = _grayData[i];
		if(gray <= r1){
			img[i] = gray * s1 / r1;
		}else if(gray >= r2){
			img[i] = (gray-r2) *(LEVEL-1-s2)/(LEVEL-1-r2)+s2;
		}else{
			img[i] = (gray-r1)*(s2-s1)/(r2-r1)+s1;
		}
	}


	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnWeiPingMian() 
{
	// 位平面
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	double const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	int size = width * height;
	int * img = new int[size];

	//比特平面8
	for(int i = 0; i < size; i++){
		int gray = _grayData[i];
		if(gray <= 127){
			img[i] = 0;
		}else if(gray >= 128){
			img[i] = LEVEL-1;
		}
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnZhiFang() 
{
	// 直方图均衡化
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int const LEVEL = 256;
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;	
	double size = width * height;
	int * img = new int[size];

	int YuanShi[LEVEL]={0};
	double GuiYi[LEVEL]={0};
	double LeiJi[LEVEL]={0};

	for(int i = 0; i < size; i++){
		YuanShi[_grayData[i]]++;
	}

	for(i = 0; i < LEVEL; i++){
		GuiYi[i]=YuanShi[i]/size;
	}

	LeiJi[0]=GuiYi[0];
	for(i = 1; i < LEVEL; i++){
		LeiJi[i]=GuiYi[i]+LeiJi[i-1];
	}
	
	for(i = 0; i < size; i++){
		int gray=_grayData[i];
		img[i]=(LEVEL-1)*LeiJi[gray];
	}

	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnLinYu() 
{
	// 领域均值滤波
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int sum = 0;

	int scale = 15;
	for(int y = scale/2; y < height - scale/2; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			for(int j = y - scale/2; j <= y + scale/2; j++)
			{
				for(int i = x - scale/2; i <= x + scale/2; i++)
				{
					sum += _grayData[j * width + i];
				}
			}
			int index = y * width + x;
			img[index] = sum / ( scale * scale );
			sum = 0;
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnJiaQuan() 
{
	// 领域加权滤波
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int sum = 0;

	int scale = 15;
	int sum_weight=0;
	for(int y = scale/2; y < height - scale/2; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			for(int j = y - scale/2; j <= y + scale/2; j++)
			{
				for(int i = x - scale/2; i <= x + scale/2; i++)
				{
					int power = pow( 2 , scale - 1 - abs( x - i) - abs( y - j));
					sum += _grayData[ j * width + i ] * power;
					sum_weight += power;
				}
			}
			int index = y * width + x;
			img[index] = sum / sum_weight;
			sum = 0;
			sum_weight = 0;
		}
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}



void CImageStuDlg::OnJunZhiQuick() 
{
	// 领域均值滤波 快速计算
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	int sum = 0;

	int scale = 15;

	//水平卷积
	int * temp= new int[size];
	memset(temp,0,sizeof(int)*size);
	for(int y = 0; y < height ; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			if(x==scale/2)
			{
				for(int m = x - scale/2; m <= x + scale/2; m++)
				{
					temp[y*width+x]+=_grayData[y*width+m];
				}
			}
			else
			{
				temp[y*width+x]=temp[y*width+x-1] - _grayData[y*width+x-scale/2-1] + _grayData[y*width+x+scale/2];
			}
		}
	}

	//垂直卷积
	
	for(y = scale/2; y < height - scale/2 ; y++)
	{
		for(int x = scale/2; x < width- scale/2; x++)
		{
			if(y==scale/2)
			{
				for(int n = y - scale/2; n <= y + scale/2; n++)
				{
					img[y*width+x]+=temp[n*width+x];
				}
			}
			else
			{
				img[y*width+x]=img[(y-1)*width+x]-temp[(y-scale/2-1)*width+x]+temp[(y+scale/2)*width+x];
			}
		}
	}

	//除以权和
	for(int i = 0; i < size;i++)
	{
		img[i] /= scale*scale;
	}

	ShowPicByArray(img,width,height);
	delete [] temp;
	delete [] img;
}

void CImageStuDlg::OnJunZhiYuzhi() 
{
	// 领域均值滤波 阈值
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	int sum = 0;

	int scale = 15;

	int max=0;
	for(int i=0; i < size; i++)
	{
		if(_grayData[i]>max)
		{
			max=_grayData[i];
		}
	}
	//水平卷积
	int * temp= new int[size];
	memset(temp,0,sizeof(int)*size);
	for(int y = 0; y < height ; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			if(x==scale/2)
			{
				for(int m = x - scale/2; m <= x + scale/2; m++)
				{
					temp[y*width+x]+=_grayData[y*width+m];
				}
			}
			else
			{
				temp[y*width+x]=temp[y*width+x-1] - _grayData[y*width+x-scale/2-1] + _grayData[y*width+x+scale/2];
			}
		}
	}

	//垂直卷积
	
	for(y = scale/2; y < height - scale/2 ; y++)
	{
		for(int x = scale/2; x < width- scale/2; x++)
		{
			if(y==scale/2)
			{
				for(int n = y - scale/2; n <= y + scale/2; n++)
				{
					img[y*width+x]+=temp[n*width+x];
				}
			}
			else
			{
				img[y*width+x]=img[(y-1)*width+x]-temp[(y-scale/2-1)*width+x]+temp[(y+scale/2)*width+x];
			}
		}
	}

	//除以权和
	for( i = 0; i < size; i++)
	{
		img[i] /= scale*scale;
		if(img[i]>=max*0.4)
		{
			img[i]=_grayData[i];
		}
		else
		{
			img[i]=0;
		}
	}

	ShowPicByArray(img,width,height);
	delete [] temp;
	delete [] img;
	
}

void CImageStuDlg::OnJiaQuanQuick() 
{
	// 领域加权滤波 快速计算
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);

	int scale = 15;

	int pow_sum=0;
	for(int i = 0; i < scale; i++)
	{
		for(int j = 0; j < scale;j++)
		{
			pow_sum+=pow(2,scale-1-abs(scale/2-i)-abs(scale/2-j));
		}
	}
	//水平卷积
	int * temp= new int[size];
	memset(temp,0,sizeof(int)*size);
	for(int y = 0; y < height ; y++)
	{
		for(int x = scale/2; x < width - scale/2; x++)
		{
			for(int m = x - scale/2; m <= x + scale/2; m++)
			{
				temp[y*width+x]+=_grayData[y*width+m]*pow(2,scale/2-abs(x-m));
			}
		}
	}

	//垂直卷积
	
	for(y = scale/2; y < height - scale/2 ; y++)
	{
		for(int x = scale/2; x < width- scale/2; x++)
		{
			for(int n = y - scale/2; n <= y + scale/2; n++)
			{
				img[y*width+x]+=temp[n*width+x]*pow(2,scale/2-abs(y-n));
			}
		}
	}

	//除以权和
	for(i = 0; i < size;i++)
	{
		img[i] /= pow_sum;
	}

	ShowPicByArray(img,width,height);
	delete [] temp;
	delete [] img;
}

void CImageStuDlg::OnFeiXianXing() 
{
	// 非线性滤波 十字叉形
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	int scale = 5;
	
	int number = 1 + scale/2*4;
	int * sor = new int[number];
	
	for(int y=scale/2;y<height-scale/2; y++)
	{
		for(int x = scale/2;x<width-scale/2; x++)
		{	
			int index=y*width+x;
			for(int i=0,row = -scale/2; row <= scale/2; row++)
			{
				if(row!=0)
				{
					sor[i++]=_grayData[index+row*width];
				}
				else
				{
					for(int column = -scale/2; column <=scale/2;column++)
					{
						sor[i++]=_grayData[index+column];
					}
				}
			}
			sort(sor,sor+number);
			img[index]= sor[number/2+1];
			i=0;
		}
	}
	
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnFeiXianXingX() 
{
	// 非线性滤波 X形
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);

	int scale = 5;
	
	int number = 1 + scale/2*4;
	int * sor = new int[number];
	
	for(int y=scale/2;y<height-scale/2; y++)
	{
		for(int x = scale/2;x<width-scale/2; x++)
		{	
			int index=y*width+x;
			for(int j=0,i=-scale/2; i <= scale/2; i++)
			{
				if(i!=0)
				{
					sor[j++]=_grayData[index+i*width+i];
				}
				sor[j++]=_grayData[index-i*width+i];
			}
			sort(sor,sor+number);
			img[index]= sor[number/2+1];
			j=0;
		}
	}
	
	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::Onlpls() 
{
	// 拉普拉斯算法
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	
	for(int y=1; y<height-1;y++)
	{
		for(int x=1; x < width-1 ; x++)
		{
			for(int m=y-1; m <= y+1;m++)
			{
				for(int n=x-1;n <= x+1;n++)
				{
					if(m==y&&n==x)
					{
						img[y*width+x]+=8*_grayData[m*width+n];
					}else{
						img[y*width+x]-=_grayData[m*width+n];
					}
					
				}
			}
		}
	}
	/*
	for(int i = 0; i < size; i++)
	{
		img[i]=abs(img[i]);
	}*/

	//负值标定
	int min=0,max=0;
	for(int i = 0; i < size; i++)
	{
		if(img[i]<min)
		{
			min=img[i];
		}
		if(img[i]>max)
		{
			max=img[i];
		}
	}

	for(i = 0; i < size; i++)
	{
		img[i]+=-1*min;
	}
	for(i = 0; i < size; i++)
	{
		img[i]*=255.0/max;
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnRobert() 
{
	// Robert算法
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	
	for(int y=0; y<height-1;y++)
	{
		for(int x=0; x < width-1 ; x++)
		{
			int index=y*width+x;
			img[index]=abs(-_grayData[index]+_grayData[index+width+1])+abs(-_grayData[index+1]+_grayData[index+width]);
		}
	}

	//负值标定
	int min=0,max=0;
	for(int i = 0; i < size; i++)
	{
		if(img[i]<min)
		{
			min=img[i];
		}
		if(img[i]>max)
		{
			max=img[i];
		}
	}

	for(i = 0; i < size; i++)
	{
		img[i]+=-1*min;
	}
	for(i = 0; i < size; i++)
	{
		img[i]*=255.0/max;
	}
	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnSobel() 
{
	// Sobel算法
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	memset(img,0,sizeof(int)*size);
	
	for(int y=1; y<height-1;y++)
	{
		for(int x=1; x < width-1 ; x++)
		{
			int index=y*width+x;
			int sum_x=0;
			int sum_y=0;
			sum_x+=abs(-_grayData[index-width-1]-2*_grayData[index-width]-_grayData[index-width+1]+_grayData[index+width-1]+2*_grayData[index+width]+_grayData[index+width+1]);
			sum_y+=abs(-_grayData[index-width-1]-2*_grayData[index-1]-_grayData[index+width-1]+_grayData[index-width+1]+2*_grayData[index+1]+_grayData[index+width+1]);
			img[index]=sum_x+sum_y;
		}
	}

	//负值标定
	int min=0,max=0;
	for(int i = 0; i < size; i++)
	{
		if(img[i]<min)
		{
			min=img[i];
		}
		if(img[i]>max)
		{
			max=img[i];
		}
	}

	for(i = 0; i < size; i++)
	{
		img[i]+=-1*min;
	}
	for(i = 0; i < size; i++)
	{
		img[i]*=255.0/max;
	}
	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnGrayColor() 
{
	//  256灰度图像映射成216色彩色图像
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	for(int i = 0; i <size;i++)
	{
		int gray=_grayData[i];
		int red = abs(sin(gray/100.0*3.14)*255);
		int green = abs(sin(gray/100.0*3.14-3.14/4)*255);
		int blue = abs(sin(gray/100.0*3.14-3.14/2)*255);
		newColor[i].SetRed(red);
		newColor[i].SetGreen(green);
		newColor[i].SetBlue(blue);
	}

	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

void CImageStuDlg::OnRgbHsiRgb() 
{
	// RGB->HSI->RGB
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	for(int i = 0; i <size;i++)
	{
		// 调用
		CBaseColorInfo colorInfo = _colorData[i];
			
		CRGBtoHSI bean(colorInfo);
		bean.RGBToHSI();// RGB-->HSI

		bean.HSIToRGB();// HSI-->RGB
		bean.ScaleRGB();// RGB重新映射成【0--255】
		CBaseColorInfo hsiInfo = bean.GetResult();
		newColor[i]=hsiInfo;
	}

	ShowPicByArray(newColor,width,height);
	delete [] newColor;
}

//----------------------------------------------实验七--------------------------------------------//



void CImageStuDlg::OnFuShi() 
{
	// 白色腐蚀
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	fushi_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
}


void CImageStuDlg::OnPenZhang() 
{
	// 白色膨胀
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	penzhang_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnOpen() 
{
	// 开操作
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	fushi_white(img,height,width);

	penzhang_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
	
}

void CImageStuDlg::OnClose() 
{
	// 闭操作
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];

	for(int m=0;m<size;m++)
	{
		img[m]=_grayData[m];
	}

	penzhang_white(img,height,width);

	fushi_white(img,height,width);

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnBianJie() 
{
	// 白色边界
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int * temp = new int[size];

	for(int m=0;m<size;m++)
	{
		temp[m]=img[m]=_grayData[m];	
	}

	fushi_white(temp,height,width);

	for(int i = 0;i < size; i++)
	{
		img[i]-=temp[i];
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnTianChong() 
{
	// 填充
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int * temp = new int[size];
	int * backup = new int[size];
	bool flag = false;
	int number=0;

	for(int m=0;m<size;m++)
	{
		if(_grayData[m]==255)
		{
			temp[m]=0;
		}
		else
		{
			temp[m]=255;
		}
		img[m]=255;
	}	

	img[447*96]=0;
	
	while(!flag)
	{
		fushi_white(img,height,width);

		for(int i = 0; i < size; i++)
		{
			if(img[i]==0&&temp[i]==255)
			{
				img[i]=255;
			}
			if(backup[i]==img[i])
			{
				number++;
			}
			backup[i]=img[i];
		}

		if(number==size)
		{
			flag=true;
		}
		else
		{
			number=0;
		}
	}

	for(int i=0;i<size;i++)
	{
		if(_grayData[i]==0)
		{
			img[i]=_grayData[i];
		}
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnLianTong() 
{
	// 连通
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int size = width * height;
	int * img = new int[size];
	int * result = new int[size];
	CBaseColorInfo * newColor = new CBaseColorInfo[size];

	for(int i=0;i<size;i++)
	{
		if(_grayData[i]>200)
			{
				img[i]=255;
			}
			else
			{
				img[i]=0;
			}
	}

	//腐蚀
	fushi_white(img,height,width);

	//----------------------------------------- 

	CConnectedComponent lian_tong(img,height,width);

	while(!lian_tong.confirm())
	{
		int index=lian_tong.calc_start();

		/*
		CString str;
		str.Format("%d", index);
		MessageBox(str);
		*/

		if(index==-1)
		{
			break;
		}
		lian_tong.set_start(index);	
		lian_tong.calc_area();
	}

	lian_tong.return_L(result);
	
	for(i = 0; i < size; i++)
	{
		int gray=result[i];
		int red,blue,green;
		if(gray==0)
		{
			red=blue=green=0;
		}
		else
		{
			red = abs(sin(gray/100.0*3.14)*255);
			green = abs(sin(gray/100.0*3.14-3.14/4)*255);
			blue = abs(sin(gray/100.0*3.14-3.14/2)*255);
		}
		newColor[i].SetRed(red);
		newColor[i].SetGreen(green);
		newColor[i].SetBlue(blue);
	}

	ShowPicByArray(newColor,width,height);
	delete [] img;
}

void CImageStuDlg::OnXiHua() 
{
	// 细化
	if(_flag == false)
	{
		MessageBox("图片未打开！");
		return;
	}
	int width = _infoHeader.biWidth+2;
	int height = _infoHeader.biHeight+2;
	int size = width * height;
	int * img = new int[size];
	int * backup = new int[size];
	bool equ=false;
	int count = 0;

	//------外围扩充一层白圈---防止算法在边界产生的误差---------
	for(int i =0;i <size;i++)
	{
		img[i]=255;
	}

	for(int m = 0; m < width-2;m++)
	{
		for(int n = 0; n <height-2;n++)
		{
			int index=n*(width-2)+m;
			int img_index=(n+1)*width+m+1;
			img[img_index]=_grayData[index];
		}
	}
	//----------------------------------------- 

	int point1[3][3]={1,1,1,2,0,2,0,0,0};
	int point2[3][3]={2,1,1,0,0,1,0,0,2};
	int point3[3][3]={0,2,1,0,0,1,0,2,1};
	int point4[3][3]={0,0,2,0,0,1,2,1,1};
	int point5[3][3]={0,0,0,2,0,2,1,1,1};
	int point6[3][3]={2,0,0,1,0,0,1,1,2};
	int point7[3][3]={1,2,0,1,0,0,1,2,0};
	int point8[3][3]={1,1,2,1,0,0,2,0,0};

	while(!equ)
	{
		custom_penzhang_white(point1,img,height,width);
		custom_penzhang_white(point2,img,height,width);
		custom_penzhang_white(point3,img,height,width);
		custom_penzhang_white(point4,img,height,width);
		custom_penzhang_white(point5,img,height,width);
		custom_penzhang_white(point6,img,height,width);
		custom_penzhang_white(point7,img,height,width);
		custom_penzhang_white(point8,img,height,width);

		for(int i=0;i<size;i++)
		{
			if(backup[i]==img[i])
			{
				count++;
			}
			backup[i]=img[i];
		}

		if(count==size)
		{
			equ=true;
		}
		else
		{
			count=0;
		}
	}

	ShowPicByArray(img,width,height);
	delete [] img;
}

void CImageStuDlg::OnHuffman() 
{
	//霍夫曼编码
	if(_flag==false){
		MessageBox("图片未打开！");
		return;
	}

	int width = _infoHeader.biWidth;
	int height = _infoHeader.biHeight;
	int pixelCount = width*height;
	int * grayData = new int[pixelCount];
	for(int index=0;index<=pixelCount-1;index++)
	{
		grayData[index]=_grayData[index];
	}

	//灰度等级
	const int GRAY_LEVEL=256;
	//哈夫曼编码
	CImgHuffman huf(grayData,pixelCount,GRAY_LEVEL);
	huf.HuffmanCode();
	//码表
	std::string * codeTable = huf.get_codeTable();
	TRACE("码表：\n");
	for(index = 0;index<=GRAY_LEVEL-1;index++)
	{
		TRACE("%d,%s\n",index,codeTable[index].c_str());
	}
}
