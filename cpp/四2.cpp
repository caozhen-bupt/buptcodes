/*C++������ƣ�    ʵ���� 2����״������(1)�����麯����   format:2015-09-12��  coder�����壻  class��2014211302��   studentID:2014211182*/
#include<iostream>
using namespace std;
const double PI=3.1415926;
																		//��״ 
class Shape
{
	public:
		Shape(){														//���캯�� 
			cout<<"������Shape�޲����Ĺ��캯��"<<endl;
		}
		Shape(const Shape &t){											//�������캯�� 
			*this = t;
		}
		~Shape(){														//��������
			cout<<"������Shape����������"<<endl;
		}
		virtual double compute(){										//�麯�� ������� 
			return 0;
		}
};
																		//���� 
class Rectangle: public Shape											//���м̳� 
{
	public:
		Rectangle(){													//�޲����Ĺ��캯��
			cout<<"������Rectangle�޲����Ĺ��캯��"<<endl;
		}
		Rectangle(double W, double H){									//�в����Ĺ��캯��
			width = W; 
			height = H;
			cout<<"������Rectangle�в����Ĺ��캯��"<<endl;
		}
		Rectangle(const Rectangle &t){									//���캯�� 
			*this = t;
		} 
		~Rectangle(){             										//�������� 
			cout<<"������Rectangle����������"<<endl;
		}
		double compute(){												//������� 
			return (width*height);
		}
	protected:
		double width, height;
};
																		//Բ 
class Circle: public Shape
{
	public:
		Circle(){														//�޲����Ĺ��캯��
			cout<<"������Circle�޲����Ĺ��캯��"<<endl;
		}
		Circle(double r){												//�в����Ĺ��캯��
			radius = r;
			cout<<"������Circle�в����Ĺ��캯��"<<endl;
		}
		Circle(const Circle &t){										//�������캯�� 
			*this = t;
		}
		~Circle(){														//��������
			cout<<"������Circle����������"<<endl;
		} 
		double compute(){												//������� 
			return (PI*radius*radius);
		}
	private:
		double radius;
};
																		//������ 
class Square: public Rectangle
{
	public:
		Square(){														//�޲����Ĺ��캯��
			cout<<"������Square�޲����Ĺ��캯��"<<endl;}
		Square(double l){												//�в����Ĺ��캯��
			length = l;
			cout<<"������Square�в����Ĺ��캯��"<<endl;
		}
		Square(const Square &t){										//�������캯�� 
			*this = t;
		} 
		~Square(){														//��������
			cout<<"������Square����������"<<endl;}
		double compute(){												//������� 
			return length*length;
		}
	private:
		double length;
};
int main()
{
	Shape *pA;															//����ָ�룬����ָ�������࣬�Ӷ����ú��� 
	double m, w, h, l, r;
	
																		//���� 
	cout<<"Please input the width and height of the rectangle: ";
	cin>>w>>h;
	Rectangle R(w, h);													//���岢ͨ�����캯����ʼ�����ζ��� 
	pA = &R;															//����ָ��ָ����ζ��� 
	m=pA->compute();													//ͨ������ָ��ָ����ζ��󣬵��þ��εĳ�Ա����������� 
	cout<<"The area of rectangle is: "<<m<<endl;
	
																		//Բ 
	cout<<"Please input the radius of the circle:";
	cin>>r;
	Circle C(r);														//���岢ͨ�����캯����ʼ��Բ���� 
	pA = &C;															//����ָ��ָ��Բ���� 
	m=pA->compute();													//ͨ������ָ��ָ����ζ��󣬵��þ��εĳ�Ա����������� 
	cout<<"The area of rectangle is: "<<m<<endl;
	
																		//������ 
	cout<<"Please input the width of the square: ";
	cin>>l;
	Square S(l);														//���岢ͨ�����캯����ʼ�������ζ��� 
	pA = &S;															//����ָ��ָ�������ζ��� 
	m=pA->compute();													//ͨ������ָ��ָ����ζ��󣬵��þ��εĳ�Ա����������� 
	cout<<"The square of square is: "<<m<<endl;
	
	return 0;
}
