class CConnectedComponent
{
public:
	CConnectedComponent(int * _origin,int _height,int _width);
	~CConnectedComponent();
	int calc_start();
	void set_start(int index);
	void calc_area();
	bool confirm();
	void return_L(int * result);
private:
	int * tempA;
	int * tempB;
	int * L;
	int * origin;
	int height,width,size;
	int label;
	bool equ;
};