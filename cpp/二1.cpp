/*C++������ƣ�      ʵ��� 1�����Σ�     format:2015-09-08��     coder�����壻      class��2014211302��     studentID:2014211182*/ 
#include<iostream>
#include<math.h>
using namespace std;
																						/*������Point�������԰���������꣬�ṩ��������֮�����ķ��������������ķ�����*/ 
class Point{
	public:
																						/*���캯��*/ 
		Point(){
			x=0;
			y=0;
			cout<<"������Point�Ĺ��캯��"<<endl;
		}
																						/*��������*/
		~Point(){ 
			cout<<"������Point����������"<<endl; 
		}
																						/*���������*/ 
		void getPoint(){
			cin>>x>>y;
		}
																						/*��������֮�����*/ 
		double length(Point a, Point b){
			double len;
			len=(double)sqrt(pow(fabs(b.x-a.x), 2)+pow(fabs(b.y-a.y), 2));
			return len;
		}
	private:
		double x, y;																	/*��������*/ 
	friend class Rectangle;																/*������Ԫ�����ڷ��ʵ������*/ 
};
																						/*������Rectangle�������԰������㣬�ṩ�����������ķ�����*/ 
class Rectangle{
	public:
																						/*���캯��*/ 
		Rectangle(){
			cout<<"������Rectangle�Ĺ��캯��"<<endl;
		}
																						/*�������� */
		~Rectangle(){
			cout<<"������Rectangle����������"<<endl;
		}
																						/*����������*/ 
		double square(Point a, Point b){
			double square;
			square=(double)(fabs(b.x-a.x))*(fabs(b.y-a.y));
			return square;
		}
	private:
		Point a, b;																		/*���ε����㣬���µ�����ϵ� */ 
};
int main()
{
	Point a, b;
	Rectangle c;
	double s, x;
	cout<<"Please input the coordinate left lower point of the rectangle and the upper right one of that in order."<<endl;
	a.getPoint();																		/*����a������*/ 
	b.getPoint();																		/*����b������*/ 
	s=c.square(a,b);																	/*����������*/ 
	x=a.length(a,b);																	/*�����߶γ���*/ 
	cout<<"The square of our rectangle is "<<s<<"."<<endl;								/*����������*/ 
	cout<<"The length between a and b is "<<x<<"."<<endl;								/*����߶γ���*/
	return 0;
}
