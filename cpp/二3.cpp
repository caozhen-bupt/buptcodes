/*C++程序设计；      实验二 3、友元；     format:2015-09-08；     coder：曹桢；      class：2014211302；     studentID:2014211182*/ 
#include<iostream>
using namespace std;
																				/*声明类Car*/ 
class Car;
																				/*定义类Boat，具有私有属性——重量*/ 
class Boat{
	public:
		Boat(){
			weight=0;
		}
		~Boat(){}
	private:
		double weight;
	friend double TotalWeight(Boat &b, Car &c);									/*设置友元，使该函数可以访问Boat类的私有属性weight*/ 
}; 
																				/*定义类Car，具有私有属性——重量*/ 
class Car{
	public:
		Car(){
			weight=0;
		}
		~Car(){}
	private:
		double weight;
	friend double TotalWeight(Boat &b, Car &c);									/*设置友元，使该函数可以访问Car类的私有属性weight*/ 
};
																				/*计算Car和Boat的重量和*/ 
double TotalWeight(Boat &b, Car &c)
{
	double total;
	cout<<"Please input the weight of the boat and that of the car."<<endl;
	cin>>b.weight>>c.weight;
	if(b.weight>=0 && c.weight>=0){
		total=b.weight+c.weight;
		return total;
	}
	else{
		return -1;
	}
}
int main()
{
	Boat b;
	Car c;
	double sum;
	sum=TotalWeight(b, c);
	if(sum == -1 || sum == 0){													//若为负数或字符等非法输入 
		cout<<"Please input valid weight."<<endl;
	}
	else{
		cout<<"The total of the weight is: "<<sum<<endl;
	}
	return 0;
}
