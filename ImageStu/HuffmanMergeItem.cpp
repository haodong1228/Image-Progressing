#include "stdafx.h"
#include "HuffmanMergeItem.h"

std::vector<int> CHuffmanMergeItem::get_grayVec(void)
{
	return _grayVec;
}

void CHuffmanMergeItem::set_grayVec(std::vector<int> new_grayVec)
{
	_grayVec.insert(_grayVec.begin(),new_grayVec.begin(),new_grayVec.end());
}

int CHuffmanMergeItem::get_num(void)
{
	return _num;
}

void CHuffmanMergeItem::set_num(int new_num)
{
	_num = new_num;
}