/*C++程序设计；      实验四 1、形状（一）；     format:2015-09-12；     coder：曹桢；      class：2014211302；     studentID:2014211182*/
#include<iostream>
using namespace std;
const double PI=3.1415926;
																						//形状 
class Shape
{
	public:
		Shape(){																		//无参数的构造函数 
			cout<<"调用了Shape无参数的构造函数"<<endl;
		}
		Shape(double W, double H){														//有参数的构造函数 
			width = W;
			height = H;
			cout<<"调用了Shape有参数的构造函数"<<endl;
		}
		Shape(const Shape &t){															//拷贝构造函数 
			*this = t;
		}
		~Shape(){																		//析构函数 
			cout<<"调用了Shape的析构函数"<<endl;
		}
		double compute(double w, double h){												//计算面积 
			return (w*h);
		}
	protected:
		double width, height;
};
																						//矩形，公有继承形状 
class Rectangle: public Shape
{
	public:
		Rectangle(){																	//无参数的构造函数 
			cout<<"调用了Rectangle无参数的构造函数"<<endl;
		}
		Rectangle(double W, double H){													//有参数的构造函数 
			width = W;
			height = H;
			cout<<"调用了Rectangle有参数的构造函数"<<endl;
		}
		Rectangle(const Rectangle &t){													//构造函数 
			*this = t;
		} 
		~Rectangle(){																	//析构函数 
			cout<<"调用了Rectangle的析构函数"<<endl;
		}
};
																						//圆 ，公有继承形状 
class Circle: public Shape
{
	public:
		Circle(){																		//无参数的构造函数 
			cout<<"调用了Circle无参数的构造函数"<<endl;
		}
		Circle(double r){																// 有参数的构造函数
			radius = r;
			cout<<"调用了Circle有参数的构造函数"<<endl;
		}
		Circle(const Circle &t){														//拷贝构造函数 
			*this = t;
		}
		~Circle(){																		//析构函数
			cout<<"调用了Circle的析构函数"<<endl;
		} 
		double compute(double radius){													//计算面积 
			return PI*radius*radius;
		}
	private:
		double radius;
};
																						//正方形 ，公有继承矩形，形成多级继承 
class Square: public Rectangle
{
	public:
		Square(){																		// 无参数的构造函数
			cout<<"调用了Square无参数的构造函数"<<endl;}
		Square(double l){																// 有参数的构造函数
			length = l;
			cout<<"调用了Square有参数的构造函数"<<endl;
		}
		Square(const Square &t){														//拷贝构造函数 
			*this = t;
		} 
		~Square(){																		// 析构函数
			cout<<"调用了Square的析构函数"<<endl;}
		double compute(double l){														//计算面积 
			return l*l;
		}
	private:
		double length;
};
int main()
{
	Rectangle R;																		//定义矩形类 
	Circle C;																			//定义圆类 
	Square S;																			//定义正方形类 
	double m, w, h, l, r;
	cout<<"Please input the width and height of the rectangle: ";
	cin>>w>>h;
	m=R.compute(w, h);																	//通过矩形类访问成员函数 
	cout<<"The square of rectangle is: "<<m<<endl;
	cout<<"Please input the radius of the circle:";
	cin>>r;
	m=C.compute(r);
	cout<<"The square of rectangle is: "<<m<<endl;
	cout<<"Please input the width of the square: ";
	cin>>l;
	m=S.compute(l);
	cout<<"The square of square is: "<<m<<endl;
	return 0;
}
