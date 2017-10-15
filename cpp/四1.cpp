/*C++������ƣ�      ʵ���� 1����״��һ����     format:2015-09-12��     coder�����壻      class��2014211302��     studentID:2014211182*/
#include<iostream>
using namespace std;
const double PI=3.1415926;
																						//��״ 
class Shape
{
	public:
		Shape(){																		//�޲����Ĺ��캯�� 
			cout<<"������Shape�޲����Ĺ��캯��"<<endl;
		}
		Shape(double W, double H){														//�в����Ĺ��캯�� 
			width = W;
			height = H;
			cout<<"������Shape�в����Ĺ��캯��"<<endl;
		}
		Shape(const Shape &t){															//�������캯�� 
			*this = t;
		}
		~Shape(){																		//�������� 
			cout<<"������Shape����������"<<endl;
		}
		double compute(double w, double h){												//������� 
			return (w*h);
		}
	protected:
		double width, height;
};
																						//���Σ����м̳���״ 
class Rectangle: public Shape
{
	public:
		Rectangle(){																	//�޲����Ĺ��캯�� 
			cout<<"������Rectangle�޲����Ĺ��캯��"<<endl;
		}
		Rectangle(double W, double H){													//�в����Ĺ��캯�� 
			width = W;
			height = H;
			cout<<"������Rectangle�в����Ĺ��캯��"<<endl;
		}
		Rectangle(const Rectangle &t){													//���캯�� 
			*this = t;
		} 
		~Rectangle(){																	//�������� 
			cout<<"������Rectangle����������"<<endl;
		}
};
																						//Բ �����м̳���״ 
class Circle: public Shape
{
	public:
		Circle(){																		//�޲����Ĺ��캯�� 
			cout<<"������Circle�޲����Ĺ��캯��"<<endl;
		}
		Circle(double r){																// �в����Ĺ��캯��
			radius = r;
			cout<<"������Circle�в����Ĺ��캯��"<<endl;
		}
		Circle(const Circle &t){														//�������캯�� 
			*this = t;
		}
		~Circle(){																		//��������
			cout<<"������Circle����������"<<endl;
		} 
		double compute(double radius){													//������� 
			return PI*radius*radius;
		}
	private:
		double radius;
};
																						//������ �����м̳о��Σ��γɶ༶�̳� 
class Square: public Rectangle
{
	public:
		Square(){																		// �޲����Ĺ��캯��
			cout<<"������Square�޲����Ĺ��캯��"<<endl;}
		Square(double l){																// �в����Ĺ��캯��
			length = l;
			cout<<"������Square�в����Ĺ��캯��"<<endl;
		}
		Square(const Square &t){														//�������캯�� 
			*this = t;
		} 
		~Square(){																		// ��������
			cout<<"������Square����������"<<endl;}
		double compute(double l){														//������� 
			return l*l;
		}
	private:
		double length;
};
int main()
{
	Rectangle R;																		//��������� 
	Circle C;																			//����Բ�� 
	Square S;																			//������������ 
	double m, w, h, l, r;
	cout<<"Please input the width and height of the rectangle: ";
	cin>>w>>h;
	m=R.compute(w, h);																	//ͨ����������ʳ�Ա���� 
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
