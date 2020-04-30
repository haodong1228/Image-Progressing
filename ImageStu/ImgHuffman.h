#if !defined(__ObjectOrientedModel_1_CImgHuffman_h)
#define __ObjectOrientedModel_1_CImgHuffman_h

#include "HuffmanMergeItem.h"
#include <vector>
#include <bitset>
#include <string>

class CImgHuffman
{
public:
	/*构造函数*/
	CImgHuffman(int * grayData, int pixelCount, int grayLevel);
	/*析构函数*/
	~CImgHuffman();

	/*灰度统计*/
	void CalcGrayStat(void);
	/*初始化待合并的哈夫曼元素*/
	void InitMergeVec(void);
	void MakeCode(std::vector<int> * grayVec, bool flag);
	/*合并两个元素*/
	void MergeItem(CHuffmanMergeItem & first, CHuffmanMergeItem & second,CHuffmanMergeItem & result);
	/*将新元素插入合适的位置*/
	void InsertItem(CHuffmanMergeItem & item);
	/*计算编码位流总位数*/
	int CalcSumBitCount(void);
	/*计算平均码长*/
	float CalcAvgBitLen(void);
	/*计算平均码长*/
	float CalcEntropy(void);
	/*哈夫曼编码*/
	void HuffmanCode(void);
	/*生成编码位流(字符串形式)*/
	void GeneCodeString();
	//初始化灰度字符串(前1000个,以逗号隔开)
	void InitGrayStr();

	//对外接口
	//码表
	std::string * get_codeTable(void);
	//字符串形式的位流
	std::string get_codeString(void);
	//二进制编码位流
	std::vector< std::bitset<8> > * get_codeBitSet(void);
	//平均码长
	float get_avgCodeLen(void);
	//总码长
	int get_sumBitCount(void);
	//灰度统计
	int * get_GrayStat(void);
	//熵
	float get_entropy(void);
	/*分组过程*/
	std::string get_mergeStr();
	//灰度字符串(以逗号隔开)
	std::string GetGrayStr() const{
			return _grayStr;
	}

protected:
private:
	/*初始化码表*/
	void InitCodeTable(void);
	//输出灰度向量
	void PrintGrayVec(CHuffmanMergeItem item);
	//设置合并过程
	void MakeMergeStr(CHuffmanMergeItem iteml, CHuffmanMergeItem item2, CHuffmanMergeItem newItem, int num); 

private:
	/*灰度数据*/
	int * _grayData;
	/*像素数量*/
	int _pixelCount;
	/*图像灰度级数量*/
	int _grayLevel;

	/*待归并的元素(按数量从小到大排序)*/
	std::vector<CHuffmanMergeItem> * _waitMergeVec;

	/*灰度的统计数量*/
	int * _grayStat;
	/*灰度码表,从小到大排序,用字符串表示*/
	std::string * _codeTable;
	/*编码位流,字符串格式*/
	std::string _codeString;	
	/*编码位流(二进制位流)*/
	std::vector< std::bitset<8> > * _codeBitSet;
	/*平均码长(以Bit为单位)*/
	float _avgCodeLen;
	/*编码总位数*/
	int _sumBitCount;
	/*熵*/
	float _entropy;
	/*分组过程*/
	std::string _mergeStr;
	//灰度字符串(以逗号隔开)
	std::string _grayStr;

	//编码表元素大小的比较(用于排序)
	class CElemCompare{
	public:
		bool operator()(CHuffmanMergeItem elem1, CHuffmanMergeItem elem2)
		{
			return elem1.get_num() < elem2.get_num();

		}
	};
};

#endif