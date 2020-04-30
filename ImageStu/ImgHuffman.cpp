#include "StdAfx.h"
#include "ImgHuffman.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iostream>

CImgHuffman::CImgHuffman(int * grayData, int pixelCount, int grayLevel)
{
	//灰度数据
	_grayData = grayData;
	//像素数量
	_pixelCount = pixelCount;
	//灰度级
	_grayLevel= grayLevel;
	
	//初始化灰度字符串
	InitGrayStr();
}

CImgHuffman::~CImgHuffman()
{
	/*待归并的元素(按数量从小到大排序)*/
	delete [] _waitMergeVec;

	/*灰度的统计数量*/
	delete [] _grayStat;
	/*灰度码表,从小到大排序,用字符串表示*/
	delete [] _codeTable;
}


//--------------------------初始化码表-----------------------
void CImgHuffman::InitCodeTable(void)
{
	//灰度码表，从小到大排序，用字符串表示
	_codeTable = new std::string[_grayLevel];
	for(int index=0;index<=_grayLevel-1;index++)
	{
		_codeTable[index]="";
	}
	TRACE("初始化码表完成");
}
//------------------------------灰度统计-------------------------
void CImgHuffman::CalcGrayStat(void)
{
	//灰度的统计数量
	_grayStat = new int[_grayLevel];
	int index;
	//初始化为0
	for(index = 0; index<=_grayLevel-1;index++)
	{
		_grayStat[index]=0;
	}

	//统计
	for(index=0;index<=_pixelCount-1;index++)
	{
		int gray=_grayData[index];
		_grayStat[gray]++;
	}
}


//--------------------------------初始化待合并的哈夫曼元素--------------
void CImgHuffman::InitMergeVec(void)
{
	//待归并的元素（按数量从小到大排序）
	_waitMergeVec = new std::vector<CHuffmanMergeItem>[_grayLevel];
	for(int index = 0; index<=_grayLevel-1;index++)
	{
		if(_grayStat[index]!=0)
		{
			CHuffmanMergeItem item;
			//灰度
			std::vector<int> gray;
			gray.push_back(index);
			item.set_grayVec(gray);
			//数量
			item.set_num(_grayStat[index]);
			//添加
			_waitMergeVec->push_back(item);
		}
	}

	//排序
	std::stable_sort(_waitMergeVec->begin(),_waitMergeVec->end(),CElemCompare());
}

void CImgHuffman::MakeCode(std::vector<int> * grayVec,bool flag)
{
	std::vector<int>::iterator begin = grayVec->begin();
	std::vector<int>::iterator end = grayVec->end();
	std::vector<int>::iterator iter;
	for(iter = begin;iter!=end;iter++)
	{
		int gray = (int)(*iter);
		std::string str = (flag==true?"1":"0");
		_codeTable[gray] = str + _codeTable[gray];
	}
}


//合并两个元素

void CImgHuffman::MergeItem(CHuffmanMergeItem &first,CHuffmanMergeItem & second,CHuffmanMergeItem & result)
{
	std::vector<int> newGrayVec(second.get_grayVec());
	std::vector<int> firstGray = first.get_grayVec();
	newGrayVec.insert(newGrayVec.begin(),firstGray.begin(),firstGray.end());

	result.set_grayVec(newGrayVec);
	int num = first.get_num() + second.get_num();
	result.set_num(num);
}

//将新元素插入合适的位置
void CImgHuffman::InsertItem(CHuffmanMergeItem& item)
{
	std::vector<CHuffmanMergeItem>::iterator begin = _waitMergeVec->begin();
	std::vector<CHuffmanMergeItem>::iterator end = _waitMergeVec->end();
	std::vector<CHuffmanMergeItem>::iterator iter;
	for(iter=begin;iter!=end;iter++)
	{
		CHuffmanMergeItem curItem = (CHuffmanMergeItem)(*iter);
		if((iter+1)!= end)
		{
			CHuffmanMergeItem nextItem = (CHuffmanMergeItem)(*(iter+1));
			if(item.get_num()>=curItem.get_num() && item.get_num()<=nextItem.get_num())
			{
				TRACE("前一个：%d,当前：%d,下一个:%d\n",item.get_num(),item.get_num(),nextItem.get_num());
				//找到为止：比前一个大（或相等），比下一个小（或相等）
				_waitMergeVec->insert(iter+1,item);
				return;
			}
		}
	}

	if(iter==end)
	{
		//没有找到合适的位置，新元素是最大的，放在末尾
		_waitMergeVec->push_back(item);
	}
}


//计算编码位流
int CImgHuffman::CalcSumBitCount(void)
{
	int sum=0;
	for(int index=0;index<=_grayLevel-1;index++)
	{
		sum+=_codeTable[index].size() * _grayStat[index];
	}
	return sum;
}


//计算平均码长
float CImgHuffman::CalcAvgBitLen(void)
{
	return (float)_sumBitCount/_pixelCount;
}

//计算平均码长
float CImgHuffman::CalcEntropy(void)
{
	float sum=0.0;
	for(int index=0;index<=_grayLevel-1;index++)
	{
		float p = (float)_grayStat[index]/_pixelCount;
		if(p>0)
		{
			sum-=p*(log10(p)/log10(2));
		}
	}
	return sum;
}


//哈夫曼编码
void CImgHuffman::HuffmanCode(void)
{
	//灰度统计
	CalcGrayStat();
	int index = 0;

	//初始化码表
	InitCodeTable();

	//初始化待组合数组
	InitMergeVec();
	//分组过程字符串
	_mergeStr="";
	//TRANCE("初始化待组合数据\n")；
	//开始编码
	while(_waitMergeVec->size()>=2)
	{
		index++;
		//取出两个最小的
		std::vector<CHuffmanMergeItem>::iterator firstIter=_waitMergeVec->begin();
		std::vector<CHuffmanMergeItem>::iterator secondIter = firstIter+1;
		CHuffmanMergeItem firstItem = (CHuffmanMergeItem)(*firstIter);
		CHuffmanMergeItem secondItem = (CHuffmanMergeItem)(*secondIter);

		//小的编码为0，大的为1
		MakeCode(&firstItem.get_grayVec(),false);
		MakeCode(&secondItem.get_grayVec(),true);
		TRACE("第一个：");
		PrintGrayVec(firstItem);
		TRACE("第二个：");
		PrintGrayVec(secondItem);
		if(_waitMergeVec->size()==2)
		{
			TRACE("剩下最后两个，结束合并");
			return;
		}
		//合并成一个新元素
		CHuffmanMergeItem newItem;
		MergeItem(firstItem,secondItem,newItem);
		MakeMergeStr(firstItem,secondItem,newItem,index);
		TRACE("新元素：");
		PrintGrayVec(newItem);

		//删除两个最小的
		_waitMergeVec->erase(firstIter);
		firstIter = _waitMergeVec->begin();
		firstItem = (CHuffmanMergeItem)(*firstIter);
		_waitMergeVec->erase(firstIter);

		//加入末尾后排序
		_waitMergeVec->push_back(newItem);
		std::stable_sort(_waitMergeVec->begin(),_waitMergeVec->end(),CElemCompare());
	}

	//计算总位数
	_sumBitCount = CalcSumBitCount();
	TRACE("总位数：%d\n",_sumBitCount);
	//计算平均码长
	_avgCodeLen = CalcAvgBitLen();
	TRACE("平均码长:%f\n",_avgCodeLen);
	//计算器
	_entropy = CalcEntropy();
	TRACE("熵:%f\n",_entropy);
	//生成编码位流
	GeneCodeString();
}


//生成编码位流（字符串形式）
void CImgHuffman::GeneCodeString()
{
	char * codeString = new char[_sumBitCount+1];
	TRACE("len=%d\n",_sumBitCount);
	int pos = 0;
	_codeString = "";

	CString str;
	str.Format("编码开始：%d",_sumBitCount);
	std::ostringstream buf;
	for(int index=0;index<=1000-1;index++)
	{
		int gray = _grayData[index];
		_codeString+=_codeTable[gray];
	}
	delete [] codeString;
}


//初始化灰度字符串（前1000个，逗号隔开）
void CImgHuffman::InitGrayStr()
{
	_grayStr="";
	int num = 1000;
	for(int i = 0; i < num; i++)
	{
		int gray = _grayData[i];
		CString curGray;
		curGray.Format("%d,",gray);
		_grayStr+=curGray;
	}
}

std::string * CImgHuffman::get_codeTable(void)
{
	return _codeTable;
}

std::string CImgHuffman::get_codeString(void)
{
	return _codeString;
}

std::vector< std::bitset<8> > * CImgHuffman::get_codeBitSet(void)
{
	return _codeBitSet;
}

float CImgHuffman::get_avgCodeLen(void)
{
	return _avgCodeLen;
}

int CImgHuffman::get_sumBitCount(void)
{
	return _sumBitCount;
}

float CImgHuffman::get_entropy(void)
{
	return _entropy;
}

//灰度统计
int * CImgHuffman::get_GrayStat(void)
{
	return _grayStat;
}

//分组过程
std::string CImgHuffman::get_mergeStr()
{
	return _mergeStr;
}

//输出灰度向量
void CImgHuffman::PrintGrayVec(CHuffmanMergeItem item)
{
	std::vector<int> grayVec = item.get_grayVec();
	std::vector<int>::iterator begin = grayVec.begin();
	std::vector<int>::iterator end = grayVec.end();
	std::vector<int>::iterator iter;
	for(iter = begin;iter!=end;iter++)
	{
		int gray = (int)(*iter);
		TRACE("%d,",gray);
	}
	TRACE("数量：%d\n",item.get_num());
}

//设置合并过程
void CImgHuffman::MakeMergeStr(CHuffmanMergeItem item1,CHuffmanMergeItem item2,CHuffmanMergeItem newItem,int num)
{
	std::vector<int> grayVec = item1.get_grayVec();
	std::vector<int>::iterator begin = grayVec.begin();
	std::vector<int>::iterator end = grayVec.end();
	std::vector<int>::iterator iter;

	char str[1024];
	sprintf(str,"第%d次：\r\n",num);
	_mergeStr+=str;
	for(iter = begin;iter!=end;iter++)
	{
		int gray = (int)(*iter);
		TRACE("%d,",gray);
		sprintf(str,"%d,",gray);
		_mergeStr+=str;
	}
	sprintf(str,"数量:%d;  ", item1.get_num());
	_mergeStr+=str;

	grayVec = item2.get_grayVec();
	begin=grayVec.begin();
	end=grayVec.end();
	//--------------TO DO-------------
	iter;

	sprintf(str,"数量:%d\r\n ",newItem.get_num());
	_mergeStr+=str;
}