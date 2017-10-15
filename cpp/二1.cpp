/*C++程序设计；      实验二 1、矩形；     format:2015-09-08；     coder：曹桢；      class：2014211302；     studentID:2014211182*/ 
#include<iostream>
#include<math.h>
using namespace std;
																						/*定义类Point，其属性包括点的坐标，提供计算两点之间距离的方法，读入点坐标的方法；*/ 
class Point{
	public:
																						/*构造函数*/ 
		Point(){
			x=0;
			y=0;
			cout<<"调用了Point的构造函数"<<endl;
		}
																						/*析构函数*/
		~Point(){ 
			cout<<"调用了Point的析构函数"<<endl; 
		}
																						/*读入点坐标*/ 
		void getPoint(){
			cin>>x>>y;
		}
																						/*计算两点之间距离*/ 
		double length(Point a, Point b){
			double len;
			len=(double)sqrt(pow(fabs(b.x-a.x), 2)+pow(fabs(b.y-a.y), 2));
			return len;
		}
	private:
		double x, y;																	/*两点坐标*/ 
	friend class Rectangle;																/*设置友元，用于访问点的坐标*/ 
};
																						/*定义类Rectangle，其属性包括两点，提供计算矩形面积的方法；*/ 
class Rectangle{
	public:
																						/*构造函数*/ 
		Rectangle(){
			cout<<"调用了Rectangle的构造函数"<<endl;
		}
																						/*析构函数 */
		~Rectangle(){
			cout<<"调用了Rectangle的析构函数"<<endl;
		}
																						/*计算矩形面积*/ 
		double square(Point a, Point b){
			double square;
			square=(double)(fabs(b.x-a.x))*(fabs(b.y-a.y));
			return square;
		}
	private:
		Point a, b;																		/*矩形的两点，左下点和右上点 */ 
};
int main()
{
	Point a, b;
	Rectangle c;
	double s, x;
	cout<<"Please input the coordinate left lower point of the rectangle and the upper right one of that in order."<<endl;
	a.getPoint();																		/*读入a点坐标*/ 
	b.getPoint();																		/*读入b点坐标*/ 
	s=c.square(a,b);																	/*计算矩形面积*/ 
	x=a.length(a,b);																	/*计算线段长度*/ 
	cout<<"The square of our rectangle is "<<s<<"."<<endl;								/*输出矩形面积*/ 
	cout<<"The length between a and b is "<<x<<"."<<endl;								/*输出线段长度*/
	return 0;
}
