#if !defined(__ObjectOrientedModel_1_CHuffmanMergeItem_h)
#define __ObjectOrientedModel_1_CHuffmanMergeItem_h

#include <vector>
class CHuffmanMergeItem
{
public:
	//灰度向量
	std::vector<int> get_grayVec(void);
	void set_grayVec(std::vector<int> new_grayVec);
	//灰度总数量
	int get_num(void);
	void set_num(int new_num);

protected:
private:
	//灰度向量
	std::vector<int> _grayVec;
	//灰度总数量
	int _num;
};

#endif