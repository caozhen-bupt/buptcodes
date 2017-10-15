/*C++������ƣ�    ʵ���� 2����״������(2)�����麯����     format:2015-09-12��  coder�����壻      class��2014211302��   studentID:2014211182*/
#include<iostream>
using namespace std;
const double PI=3.1415926;
																				//������ ��״ 
class Shape
{
	public:
		Shape(){
			cout<<"������Shape�޲����Ĺ��캯��"<<endl;
		}
		~Shape(){
			cout<<"������Shape����������"<<endl;
		}
		virtual double compute() = 0;											//���麯�� �޶��� �Ӵ����趨�� 
};
																				//���� 
class Rectangle: public Shape
{
	public:
		Rectangle(){
			cout<<"������Rectangle�޲����Ĺ��캯��"<<endl;
		}
		Rectangle(double W, double H){
			width = W;
			height = H;
			cout<<"������Rectangle�в����Ĺ��캯��"<<endl;
		}
		~Rectangle(){
			cout<<"������Rectangle����������"<<endl;
		}
		double compute(){														//�̳��麯�����м����������ľ��巽�� 
			return (width*height);
		}
	protected:
		double width, height;
};
																				// Բ 
class Circle: public Shape
{
	public:
		Circle(){
			cout<<"������Circle�޲����Ĺ��캯��"<<endl;
		}
		Circle(double r){
			radius = r;
			cout<<"������Circle�в����Ĺ��캯��"<<endl;
		}
		~Circle(){
			cout<<"������Circle����������"<<endl;
		} 
		double compute(){														//�̳��麯�����м���Բ����ľ��巽�� 
			return (PI*radius*radius);
		}
	private:
		double radius;
};
																				//������ 
class Square: public Rectangle
{
	public:
		Square(){
			cout<<"������Square�޲����Ĺ��캯��"<<endl;}
		Square(double l){
			length = l;
		}
		~Square(){}
		double compute(){														//�̳��麯�����м�������������ľ��巽�� 
			return (length*length);
		}
	private:
		double length;
};
int main()
{
	Shape *pA;																	//����ָ�룬����ָ�������࣬�Ӷ����ú��� 
	double m, w, h, l, r;
	
																				//���� 
	cout<<"Please input the width and height of the rectangle: ";
	cin>>w>>h;
	Rectangle R(w, h);															//���岢ͨ�����캯����ʼ�����ζ��� 
	pA = &R;																	//����ָ��ָ����ζ��� 
	m=pA->compute();															//ͨ������ָ��ָ����ζ��󣬵��þ��εĳ�Ա����������� 
	cout<<"The area of rectangle is: "<<m<<endl;
	
																				//Բ 
	cout<<"Please input the radius of the circle:";
	cin>>r;
	Circle C(r);																//���岢ͨ�����캯����ʼ��Բ���� 
	pA = &C;																	//����ָ��ָ��Բ���� 
	m=pA->compute();															//ͨ������ָ��ָ����ζ��󣬵��þ��εĳ�Ա����������� 
	cout<<"The area of rectangle is: "<<m<<endl;
	
																				//������ 
	cout<<"Please input the width of the square: ";
	cin>>l;
	Square S(l);																 //���岢ͨ�����캯����ʼ�������ζ��� 
	pA = &S;																	//����ָ��ָ�������ζ��� 
	m=pA->compute();															//ͨ������ָ��ָ����ζ��󣬵��þ��εĳ�Ա����������� 
	cout<<"The square of square is: "<<m<<endl;
	
	return 0;
}
