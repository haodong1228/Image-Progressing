//判断是否符合腐蚀条件，满足返回true，不满足false；若满足则把该白色变为黑色
void fushi_white(int * img,int height,int width);
//判断是否符合膨胀条件，满足返回true，不满足false；若满足则把该黑色变为白色
void penzhang_white(int * img,int height,int width);

//自定义数组白色膨胀
void custom_penzhang_white(int point[3][3],int *img,int height,int width);