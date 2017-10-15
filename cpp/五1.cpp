/*C++程序设计；  实验五 1、对Point类重载＋＋和――运算符  format:2015-09-12； coder：曹桢；  class：2014211302；  studentID:2014211182*/
#include<iostream>
#include<math.h>
using namespace std;
class Point{
	public:
																				/*构造函数*/ 
		Point(int X=0, int Y=0){
			x=X;
			y=Y;
			cout<<"调用了Point的构造函数"<<endl;
		}
		Point(const Point &t){													//拷贝构造函数 
			*this = t;
		}
																				/*析构函数*/
		~Point(){ 
			cout<<"调用了Point的析构函数"<<endl; 
		}
																				/*读入点坐标*/ 
		friend istream& operator >>(istream &input, Point &A){
			cin >> A.x >> A.y;
			return input;
		}
		friend ostream& operator <<(ostream &output, Point &A){
			cout<<"("<<A.x<<", "<<A.y<<")"<<endl;
			return output;
		}
		Point & operator ++(){													//实现++a 
			x++;
			y++;
			return *this;														//返回的是引用 
		}
		const Point operator ++(int){											//实现a++ ,后置，int仅作区分，后面有无变量名均可，实现后置的++ 
			Point temp = *this;
			++(*this);
			return temp;
		}
		Point & operator --(){													//实现--a 
			x--;
			y--;
			return *this;
		}
		const Point operator --(int){											//实现a--,后置，int仅作区分，实现后置的-- 
			Point temp = *this;
			--(*this);
			return temp;
		}
	private:
		double x, y;															/*两点坐标*/ 
};
int main()
{
	Point A, B;
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=A++;																		//B=A.operator++(1) 
	cout<<B;
	
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=++A;																		//B=A.operator++()
	cout<<B;
	
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=A--;
	cout<<B;
	
	cout<<"Please input the coordinate of A: ";
	cin>>A;
	B=--A;
	cout<<B;
	
	return 0;
} 
