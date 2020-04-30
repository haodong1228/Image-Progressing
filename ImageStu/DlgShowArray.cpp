// DlgShowArray.cpp : implementation file
//

#include "stdafx.h"
#include "ImageStu.h"
#include "DlgShowArray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShowArray dialog


CDlgShowArray::CDlgShowArray(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowArray::IDD, pParent), _biBitCount( 24 )
{
	//{{AFX_DATA_INIT(CDlgShowArray)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgShowArray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowArray)
	DDX_Control(pDX, IDC_STATIC_POS, _staticPos);
	DDX_Control(pDX, IDC_COMBO_TYPE, _comboType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowArray, CDialog)
	//{{AFX_MSG_MAP(CDlgShowArray)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(ID_BUTTON_SAVE, OnButtonSave)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShowArray message handlers


/************************************************************************/
/*                        消息映射                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// 绘制对话框, 映射WM_PAINT消息
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC *pDC = GetDC();


	// 绘制图像
	for( int x = 0; x <= _width - 1; x++ ){
		for( int y = 0; y <= _height - 1; y++ ){

			int index = y * _width + x;

			int curColor = 0;
			switch( _colorType ){
			case ALL:
				break;
			case RED:
				curColor = _colorData[ index ].GetRed();
				break;
			case GREEN:
				curColor = _colorData[ index ].GetGreen();
				break;
			case BLUE:
				curColor = _colorData[ index ].GetBlue();
				break;
			}
			int red = ( _colorType == ALL || _colorType == RED ) ? _colorData[ index ].GetRed() : curColor;
			int green = ( _colorType == ALL || _colorType == GREEN ) ? _colorData[ index ].GetGreen() : curColor;
			int blue = ( _colorType == ALL || _colorType == BLUE ) ? _colorData[ index ].GetBlue() : curColor;
			pDC->SetPixel( x , y + _headPosRect.Height() , RGB( red, green, blue ) );
			
		}
	}

	ReleaseDC( pDC );
	
	// Do not call CDialog::OnPaint() for painting messages
}


//////////////////////////////////////////////////////////////////////////
// 初始化对话框, 映射WM_INITDIALOG消息
//////////////////////////////////////////////////////////////////////////
BOOL CDlgShowArray::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	_staticPos.GetWindowRect( &_headPosRect );
	ScreenToClient( &_headPosRect );
	
	// 设置窗体的大小
	int showWidth = _width + 20;
	if( showWidth < _headPosRect.Width() ){
		showWidth = _headPosRect.Width();
	}

	// 窗体位于屏幕中央 
	CClientDC dc(this);
	int width = dc.GetDeviceCaps(HORZRES);
	int height = dc.GetDeviceCaps(VERTRES);
	CRect rect;
	GetWindowRect( &rect );
	width = ( width - ( rect.right - rect.left ) ) / 2 ;
	height = ( height - (rect.bottom - rect.top ) ) / 2 ;


	this->SetWindowPos( NULL, width, height, showWidth, _height + _headPosRect.Height() + 50, SWP_SHOWWINDOW );
	// 初始化种类下拉框
	InitComboType();
	// 转换成24位彩色位图
	Convert24BMP();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////////////
// 销毁窗体，映射WM_DESTORY消息
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
	// 释放位图数据
	free( _lpBuf );
	
}

//////////////////////////////////////////////////////////////////////////
// 选择种类下拉框(IDC_COMBO_TYPE)
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	int index = _comboType.GetCurSel();
	if( index == 0 ){
		_colorType = ALL;
	}
	else if( index == 1 ){
		_colorType = RED;	
	}
	else if( index == 2 ){
		_colorType = GREEN;	
	}
	else if( index == 3 ){
		_colorType = BLUE;	
	}

	Invalidate();
}


//////////////////////////////////////////////////////////////////////////
// "保存"按钮
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(false,"*.bmp",NULL,NULL,"*.bmp|*.bmp||");
	if (dlg.DoModal()==IDOK)
	{
		// 保存成24位彩色BMP图像
		SaveAsBmp( (LPTSTR)(LPCTSTR)dlg.GetPathName(), _lpBuf, _width, _height, 24,
			NULL );
	}
}


/************************************************************************/
/*                         字段设置                                     */
/************************************************************************/
// 图像数据
void CDlgShowArray::SetColorData( CBaseColorInfo * colorData ){
	_colorData = colorData;
}
// 图像大小
void CDlgShowArray::SetWidth( int width ){
	_width = width;
}
void CDlgShowArray::SetHeight( int height ){
	_height = height;
}

/************************************************************************/
/*                          私有函数                                    */
/************************************************************************/

// 初始化种类下拉框
void CDlgShowArray::InitComboType(){

	_comboType.InsertString( ALL, "全部" );
	_comboType.InsertString( RED, "红色通道" );
	_comboType.InsertString( GREEN, "绿色通道" );
	_comboType.InsertString( BLUE, "蓝色通道" );
	_comboType.SetCurSel( 0 );
	_colorType = ALL;

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
bool CDlgShowArray::SaveAsBmp( char * bmpName, 
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


//////////////////////////////////////////////////////////////////////////
// 图像数据转成24位BMP数据
// 将_colorData表示的图像数据(从上到下、从左到右)转成
//    24BMP图像的图像数据(从下到上，从左到右存储)
//////////////////////////////////////////////////////////////////////////
void CDlgShowArray::Convert24BMP(){

	// 宽度不是4的倍数则补齐
	DWORD dwBytes = ((DWORD) _width * _biBitCount ) / 32;
	if( ( (DWORD) _width * _biBitCount ) % 32) {
		dwBytes++;
	}
	dwBytes *= 4;
	
	int width = _width;
	int height = _height;

	// 分配位图数据空间
	if( dwBytes % 3 == 0 ){
		_lpBuf = new BYTE[ 3 * width * height ] ;
	}
	else{
		_lpBuf = new BYTE[ dwBytes  * height ];
	}

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

			_lpBuf[ index  + 2 ] = _colorData[ resultIndex ].GetRed();
			_lpBuf[ index  + 1 ] = _colorData[ resultIndex ].GetGreen(  );
			_lpBuf[ index ] = _colorData[ resultIndex ].GetBlue();
			
		}// for j
	}// for i 

}






