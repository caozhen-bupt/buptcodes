/*C++程序设计；    实验四 2、形状（二）(2)——虚函数；     format:2015-09-12；  coder：曹桢；      class：2014211302；   studentID:2014211182*/
#include<iostream>
using namespace std;
const double PI=3.1415926;
																				//抽象类 形状 
class Shape
{
	public:
		Shape(){
			cout<<"调用了Shape无参数的构造函数"<<endl;
		}
		~Shape(){
			cout<<"调用了Shape的析构函数"<<endl;
		}
		virtual double compute() = 0;											//纯虚函数 无定义 子代均需定义 
};
																				//矩形 
class Rectangle: public Shape
{
	public:
		Rectangle(){
			cout<<"调用了Rectangle无参数的构造函数"<<endl;
		}
		Rectangle(double W, double H){
			width = W;
			height = H;
			cout<<"调用了Rectangle有参数的构造函数"<<endl;
		}
		~Rectangle(){
			cout<<"调用了Rectangle的析构函数"<<endl;
		}
		double compute(){														//继承虚函数，有计算矩形面积的具体方法 
			return (width*height);
		}
	protected:
		double width, height;
};
																				// 圆 
class Circle: public Shape
{
	public:
		Circle(){
			cout<<"调用了Circle无参数的构造函数"<<endl;
		}
		Circle(double r){
			radius = r;
			cout<<"调用了Circle有参数的构造函数"<<endl;
		}
		~Circle(){
			cout<<"调用了Circle的析构函数"<<endl;
		} 
		double compute(){														//继承虚函数，有计算圆面积的具体方法 
			return (PI*radius*radius);
		}
	private:
		double radius;
};
																				//正方形 
class Square: public Rectangle
{
	public:
		Square(){
			cout<<"调用了Square无参数的构造函数"<<endl;}
		Square(double l){
			length = l;
		}
		~Square(){}
		double compute(){														//继承虚函数，有计算正方形面积的具体方法 
			return (length*length);
		}
	private:
		double length;
};
int main()
{
	Shape *pA;																	//基类指针，用于指向派生类，从而调用函数 
	double m, w, h, l, r;
	
																				//矩形 
	cout<<"Please input the width and height of the rectangle: ";
	cin>>w>>h;
	Rectangle R(w, h);															//定义并通过构造函数初始化矩形对象 
	pA = &R;																	//基类指针指向矩形对象 
	m=pA->compute();															//通过基类指针指向矩形对象，调用矩形的成员函数计算面积 
	cout<<"The area of rectangle is: "<<m<<endl;
	
																				//圆 
	cout<<"Please input the radius of the circle:";
	cin>>r;
	Circle C(r);																//定义并通过构造函数初始化圆对象 
	pA = &C;																	//基类指针指向圆对象 
	m=pA->compute();															//通过基类指针指向矩形对象，调用矩形的成员函数计算面积 
	cout<<"The area of rectangle is: "<<m<<endl;
	
																				//正方形 
	cout<<"Please input the width of the square: ";
	cin>>l;
	Square S(l);																 //定义并通过构造函数初始化正方形对象 
	pA = &S;																	//基类指针指向正方形对象 
	m=pA->compute();															//通过基类指针指向矩形对象，调用矩形的成员函数计算面积 
	cout<<"The square of square is: "<<m<<endl;
	
	return 0;
}
