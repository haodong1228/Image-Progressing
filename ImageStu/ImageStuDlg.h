//////////////////////////////////////////////////////////////////////////
// ImageStuDlg.h : header file
// 图像处理实验学生平台
// 创建人: 邓飞
// 创建时间: 2008-8-31
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
#define AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "BaseColorInfo.h"

class CImageStuDlg : public CDialog
{
// Construction
public:
	CImageStuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageStuDlg)
	enum { IDD = IDD_IMAGESTU_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageStuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnDestroy();
	afx_msg void OnFileShowArray();
	afx_msg void OnTest();
	afx_msg void OnFileSave();
	afx_msg void OnFullRed();
	afx_msg void OnRedBlue();
	afx_msg void OnColorBlack();
	afx_msg void OnGrayBlack();
	afx_msg void OnDirectZoom();
	afx_msg void OnGrayAdjust();
	afx_msg void OnNearestInterpolation();
	afx_msg void OnBilinearInterpolation();
	afx_msg void Onmove();
	afx_msg void OnHorizontalmirroring();
	afx_msg void OnVerticalMirroring();
	afx_msg void OnTranspose();
	afx_msg void OnRotating();
	afx_msg void OnNegate();
	afx_msg void OnLogarithm();
	afx_msg void OnShifting();
	afx_msg void OnFenDuan();
	afx_msg void OnWeiPingMian();
	afx_msg void OnZhiFang();
	afx_msg void OnLinYu();
	afx_msg void OnJiaQuan();
	afx_msg void OnJunZhiQuick();
	afx_msg void OnJunZhiYuzhi();
	afx_msg void OnJiaQuanQuick();
	afx_msg void OnFeiXianXing();
	afx_msg void OnFeiXianXingX();
	afx_msg void Onlpls();
	afx_msg void OnRobert();
	afx_msg void OnSobel();
	afx_msg void OnGrayColor();
	afx_msg void OnRgbHsiRgb();
	afx_msg void OnFuShi();
	afx_msg void OnPenZhang();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnBianJie();
	afx_msg void OnTianChong();
	afx_msg void OnLianTong();
	afx_msg void OnXiHua();
	afx_msg void OnHuffman();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
		// 读取文件头
	BOOL ReadFileHeader( CFile & file );
	// 读取文件信息头
	BOOL ReadInfoHeader( CFile & file );
	// 释放数据
	void FreeData();
	// 计算调色板颜色数量
	int CalcQuadNum();
	// 读取调色板数据
	void ReadQuad( CFile &file );
	// 判断是否为256色灰度图
	BOOL Is256Gray();
	// 读入图像数据
	void ReadImageData( CFile &file );
	// 判断图像类型
	IMAGE_TYPE CalcImageType();
	// 将24位彩色BMP数据转换成24位颜色数据
	void BMPConvertColor24();
	// 将8位彩色BMP数据转成24位颜色数据
	void BMPConvertColor8();
	// 将8位灰度BMP数据转成8位灰度数据
	void BMPConvertGray8();
	// 将8位灰度数据转成用24位颜色
	void Gray8ConvertColor24( BYTE * grayData, CBaseColorInfo * colorData, int width, int height );
	// 将8位灰度数据转成用24位颜色
	void Gray8ConvertColor24( int * grayData, CBaseColorInfo * colorData, int width, int height );


	// 显示图像(通过图像数组, 彩色图像)
	void ShowPicByArray( CBaseColorInfo * colorData, int width, int height );
	// 显示图像(通过图像数组, 灰度图像)
	void ShowPicByArray( int * grayData, int width, int height );

	// 保存BMP图片
	bool SaveAsBmp( char * bmpName, unsigned char * imgBuf, int width, int height, int biBitCount, RGBQUAD * pColorTable );

//-------------------自定义函数------------------------------------------//
	

//-----------------------------------------------------------------------//
public:
	// 文件头
	BITMAPFILEHEADER _fileHeader;
	
	// 调色板
	RGBQUAD * _quad;
	// 调色板数目
	int _numQuad;
	// 图像数据
	BYTE * _lpBuf;
	BITMAPINFO * _bitmapInfo;
	// 处理后的图像数据
	BYTE * _processBuf;
	// 是否打开了bmp文件
	bool _flag;
	
	// 信息头
	BITMAPINFOHEADER _infoHeader;

	// 图像类型
	IMAGE_TYPE _imageType;
	// 灰度(256灰度数据, 按从上到下, 从左到右的顺序排列,一维矩阵排列)
	int * _grayData;
	// 彩色数据(按从上到下, 从左到右的顺序排列,一维矩阵排列)
	CBaseColorInfo * _colorData;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTUDLG_H__8B975AD1_2A07_4F7F_B0EC_1B03621056BF__INCLUDED_)
