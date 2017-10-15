/*coder：曹桢	最后修改时间：2016-12-06 21：09 
  实验：程序设计3    语义分析程序的设计与实现 
*/ 

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

const int columnNum = 12;												//分析表列数 
const int Nsize = 4;													//非终结符个数 
const int Gsize = 10;													//产生式个数 
const int stateNum = 18;												//状态个数 

struct val{
	string value;
	int type;
}; 
typedef struct val VAL;
char N[Nsize]={'S','E','T','F'};										//非终结符
char item[columnNum]={'n', '+','-','*','/','(',')','$', '.', 'E','T','F'};	//分析表的列		
vector<char> First[Nsize];												//First集 
vector<char> Follow[Nsize];												//Follow集 
stack<int> stateStack;													//状态栈 
stack<VAL> valStack;
string AnalyseTable[stateNum][columnNum];								//预测分析表 
string R[Gsize];														//拓广文法后的产生式 
string inputBuffer;														//输入缓冲区 
int ip;																	//输入缓冲区指针 


void Init()
{
	/*First集*/ 
	First[0].push_back('(');
	First[0].push_back('n');
	First[1].push_back('(');
	First[1].push_back('n');
	First[2].push_back('(');
	First[2].push_back('n');
	First[3].push_back('(');
	First[3].push_back('n');
	
	/*Follow集*/ 
	Follow[0].push_back('$');
	Follow[1].push_back('$');
	Follow[1].push_back(')');
	Follow[1].push_back('+');
	Follow[1].push_back('-');
	Follow[2].push_back('$');
	Follow[2].push_back(')');
	Follow[2].push_back('+');
	Follow[2].push_back('-');
	Follow[2].push_back('*');
	Follow[2].push_back('/');
	Follow[3].push_back('$');
	Follow[3].push_back(')');
	Follow[3].push_back('+');
	Follow[3].push_back('-');	
	Follow[3].push_back('*');
	Follow[3].push_back('/');
	
	/*拓广文法后的产生式*/ 
	R[0] = "S->E";
	R[1] = "E->E+T";
	R[2] = "E->E-T";
	R[3] = "E->T";
	R[4] = "T->T*F";
	R[5] = "T->T/F";
	R[6] = "T->F";
	R[7] = "F->(E)";
	R[8] = "F->n" ;
	R[9] = "F->n.n";
	
	/*预测分析表*/ 
	for(int i = 0; i < stateNum; i++){
		for(int j = 0; j < columnNum; j++){
			AnalyseTable[i][j] = "";
		}
	}
}

/*将字符映射到列*/
int map(char x)
{
	switch(x){
		case '+':
			return 1;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 4;
		case '(':
			return 5;
		case ')':
			return 6;
		case '$':
			return 7;
		case '.':
			return 8;
		case 'E':
			return 9;
		case 'T':
			return 10;
		case 'F':
			return 11;
		default:
			return -1;
	}
}

/*建立分析表*/
void createTable()
{
	
	AnalyseTable[0][0] = "S5";
	AnalyseTable[0][1] = "E1";
	AnalyseTable[0][2] = "E1";
	AnalyseTable[0][3] = "E1";
	AnalyseTable[0][4] = "E1";
	AnalyseTable[0][5] = "S4";
	AnalyseTable[0][6] = "E2";
	AnalyseTable[0][7] = "E1";
	AnalyseTable[0][8] = "E3";
	AnalyseTable[0][9] = "1";
	AnalyseTable[0][10] = "2";
	AnalyseTable[0][11] = "3";
	
	AnalyseTable[1][0] = "E3";
	AnalyseTable[1][1] = "S6";
	AnalyseTable[1][2] = "S7";
	AnalyseTable[1][3] = "E2";
	AnalyseTable[1][4] = "E2";
	AnalyseTable[1][5] = "E3";
	AnalyseTable[1][6] = "E2";
	AnalyseTable[1][7] = "ACC";
	AnalyseTable[1][8] = "E3";
	
	AnalyseTable[2][0] = "R3";
	AnalyseTable[2][1] = "R3";
	AnalyseTable[2][2] = "R3";
	AnalyseTable[2][3] = "S8";
	AnalyseTable[2][4] = "S9";
	AnalyseTable[2][5] = "R3";
	AnalyseTable[2][6] = "R3";
	AnalyseTable[2][7] = "R3";
	AnalyseTable[2][8] = "E3";
	
	AnalyseTable[3][0] = "R6";
	AnalyseTable[3][1] = "R6";
	AnalyseTable[3][2] = "R6";
	AnalyseTable[3][3] = "R6";
	AnalyseTable[3][4] = "R6";
	AnalyseTable[3][5] = "R6";
	AnalyseTable[3][6] = "R6";
	AnalyseTable[3][7] = "R6";
	AnalyseTable[3][8] = "E3";
	
	AnalyseTable[4][0] = "S5";
	AnalyseTable[4][1] = "E1";
	AnalyseTable[4][2] = "E1";
	AnalyseTable[4][3] = "E1";
	AnalyseTable[4][4] = "E1";
	AnalyseTable[4][5] = "S4";
	AnalyseTable[4][6] = "E2";
	AnalyseTable[4][7] = "E1";
	AnalyseTable[4][8] = "E3";
	AnalyseTable[4][9] = "10";
	AnalyseTable[4][10] = "2";
	AnalyseTable[4][11] = "3";
	
	AnalyseTable[5][0] = "R8";
	AnalyseTable[5][1] = "R8";
	AnalyseTable[5][2] = "R8";
	AnalyseTable[5][3] = "R8";
	AnalyseTable[5][4] = "R8";
	AnalyseTable[5][5] = "R8";
	AnalyseTable[5][6] = "R8";
	AnalyseTable[5][7] = "R8";
	AnalyseTable[5][8] = "S16";
	
	AnalyseTable[6][0] = "S5";
	AnalyseTable[6][1] = "E1";
	AnalyseTable[6][2] = "E1";
	AnalyseTable[6][3] = "E1";
	AnalyseTable[6][4] = "E1";
	AnalyseTable[6][5] = "S4";
	AnalyseTable[6][6] = "E2";
	AnalyseTable[6][7] = "E1";
	AnalyseTable[6][8] = "E3";
	AnalyseTable[6][10] = "11";
	AnalyseTable[6][11] = "3";
	
	AnalyseTable[7][0] = "S5";
	AnalyseTable[7][1] = "E1";
	AnalyseTable[7][2] = "E1";
	AnalyseTable[7][3] = "E1";
	AnalyseTable[7][4] = "E1";
	AnalyseTable[7][5] = "S4";
	AnalyseTable[7][6] = "E2";
	AnalyseTable[7][7] = "E1";
	AnalyseTable[7][8] = "E3";
	AnalyseTable[7][10] = "12";
	AnalyseTable[7][11] = "3";
	
	AnalyseTable[8][0] = "S5";
	AnalyseTable[8][1] = "E1";
	AnalyseTable[8][2] = "E1";
	AnalyseTable[8][3] = "E1";
	AnalyseTable[8][4] = "E1";
	AnalyseTable[8][5] = "S4";
	AnalyseTable[8][6] = "E2";
	AnalyseTable[8][7] = "E1";
	AnalyseTable[8][8] = "E3";
	AnalyseTable[8][11] = "13";
	
	AnalyseTable[9][0] = "S5";
	AnalyseTable[9][1] = "E1";
	AnalyseTable[9][2] = "E1";
	AnalyseTable[9][3] = "E1";
	AnalyseTable[9][4] = "E1";
	AnalyseTable[9][5] = "S4";
	AnalyseTable[9][6] = "E2";
	AnalyseTable[9][7] = "E1";
	AnalyseTable[9][8] = "E3";
	AnalyseTable[9][11] = "14";
	
	AnalyseTable[10][0] = "E3";
	AnalyseTable[10][1] = "S6";
	AnalyseTable[10][2] = "S7";
	AnalyseTable[10][3] = "E2";
	AnalyseTable[10][4] = "E2";
	AnalyseTable[10][5] = "E3";
	AnalyseTable[10][6] = "S15";
	AnalyseTable[10][7] = "E4";
	AnalyseTable[10][8] = "E3";
	
	AnalyseTable[11][0] = "R1";
	AnalyseTable[11][1] = "R1";
	AnalyseTable[11][2] = "R1";
	AnalyseTable[11][3] = "S8";
	AnalyseTable[11][4] = "S9";
	AnalyseTable[11][5] = "R1";
	AnalyseTable[11][6] = "R1";
	AnalyseTable[11][7] = "R1";
	AnalyseTable[11][8] = "E3";
	
	AnalyseTable[12][0] = "R2";
	AnalyseTable[12][1] = "R2";
	AnalyseTable[12][2] = "R2";
	AnalyseTable[12][3] = "S8";
	AnalyseTable[12][4] = "S9";
	AnalyseTable[12][5] = "R2";
	AnalyseTable[12][6] = "R2";
	AnalyseTable[12][7] = "R2";
	AnalyseTable[12][8] = "E3";
	
	
	AnalyseTable[13][0] = "R4";
	AnalyseTable[13][1] = "R4";
	AnalyseTable[13][2] = "R4";
	AnalyseTable[13][3] = "R4";
	AnalyseTable[13][4] = "R4";
	AnalyseTable[13][5] = "R4";
	AnalyseTable[13][6] = "R4";
	AnalyseTable[13][7] = "R4";
	AnalyseTable[13][8] = "E3";
	
	AnalyseTable[14][0] = "R5";
	AnalyseTable[14][1] = "R5";
	AnalyseTable[14][2] = "R5";
	AnalyseTable[14][3] = "R5";
	AnalyseTable[14][4] = "R5";
	AnalyseTable[14][5] = "R5";
	AnalyseTable[14][6] = "R5";
	AnalyseTable[14][7] = "R5";
	AnalyseTable[14][8] = "E3";
	
	AnalyseTable[15][0] = "R7";
	AnalyseTable[15][1] = "R7";
	AnalyseTable[15][2] = "R7";
	AnalyseTable[15][3] = "R7";
	AnalyseTable[15][5] = "R7";
	AnalyseTable[15][4] = "R7";
	AnalyseTable[15][6] = "R7";
	AnalyseTable[15][7] = "R7";	
	AnalyseTable[15][8] = "E3";
	
	AnalyseTable[16][0] = "S17";
	AnalyseTable[16][1] = "E1";
	AnalyseTable[16][2] = "E1";
	AnalyseTable[16][3] = "E1";
	AnalyseTable[16][4] = "E1";
	AnalyseTable[16][5] = "E3";
	AnalyseTable[16][6] = "E2";
	AnalyseTable[16][7] = "E1";
	AnalyseTable[16][8] = "E3";
	
	AnalyseTable[17][0] = "R9";
	AnalyseTable[17][1] = "R9";
	AnalyseTable[17][2] = "R9";
	AnalyseTable[17][3] = "R9";
	AnalyseTable[17][4] = "R9";
	AnalyseTable[17][5] = "R9";
	AnalyseTable[17][6] = "R9";
	AnalyseTable[17][7] = "R9";
	AnalyseTable[17][8] = "R9";
}

/*打印状态栈*/ 
void printstack()
{
	string output = "";
	stack<int> temp;
	while(!stateStack.empty()){
		int t = stateStack.top();
		temp.push(t);
		stateStack.pop();
	}
	while(!temp.empty()){
		int t = temp.top();
		char xoxo[10];
		itoa(t, xoxo, 10);
		output = output +"|"+ xoxo;
		stateStack.push(t);
		temp.pop();
	}
	cout<<output;
}

/*打印数据栈*/ 
void printval()
{
	string output = "";
	stack<VAL> temp;
	while(!valStack.empty()){
		VAL t = valStack.top();
		temp.push(t);
		valStack.pop();
	}
	while(!temp.empty()){
		VAL t = temp.top();
		output = output +"|"+ t.value;
		valStack.push(t);
		temp.pop();
	}
	cout<<output;
}

/*把字符串转换为doulbe*/
double stringToDouble(string str)
{
	int len = str.length();
	double outcome = 0;
	double nn = 0;
	int i = 0;
	for(; i < len && str[i] >= '0' && str[i] <='9'; i++){
		outcome = outcome*10 + str[i] - '0';
	}
	if(str[i] == '.'){
		for(int j = len-1; j > i; j--){
			nn = nn*0.1+str[j] - '0';
		}
	}
	nn = nn*0.1;
	outcome = outcome+nn;
	return outcome;
}

/*把double转化成string*/ 
string doubleToString(double d)
{
	ostringstream oss;
	oss << d;
	string str = oss.str();
	return str;
}

/*错误处理*/ 
void error(char kind = 'x')
{
	switch(kind){
		case '1':
			cout<<"缺少运算对象"<<endl;
			stateStack.push(3);
			break;
		case '2':
			cout<<"括号不匹配"<<endl;
			ip++;
			break;
		case '3':
			cout<<"缺少运算符号"<<endl;
			stateStack.push(4);
			break;
		case '4':
			cout<<"缺少右括号"<<endl;
			stateStack.push(9);
			break;
		default:
			cout<<"未知错误"<<endl;
	
	}
}

/*LR分析*/ 
void LR(string w)
{
	int X;
	char a;
	int inta;
	double n = 0;
	int thetype;
	string ss = "";
	ip = 0;
	int step = 0;
	stateStack.push(0);
	VAL vl;
	vl.type = 0;
	vl.value = "-";
	valStack.push(vl);
	inputBuffer = w+"$";
	cout<<left<<setw(10)<<"步骤"<<
	left<<setw(20)<<"栈"<<left<<setw(20)<<"输入"<<left<<setw(20)<<"输出"<<endl; 
	
	do{
		X = stateStack.top();
		a = inputBuffer[ip];
		ss="";
		step++;
		
		cout<<left<<setw(10)<<step;
		cout<<left<<setw(20);
		printstack();
		cout<<endl;
		cout<<left<<setw(10)<<" ";
		cout<<left<<setw(20);
		printval();
		cout<<left<<setw(20)<<inputBuffer.substr(ip);
		
		if(a >= '0' && a <= '9'){
			inta = 0;
			while(a >= '0' && a<='9'){
				ss = ss+a;
				ip++;
				a = inputBuffer[ip];
			}
			if(a == '.'){
				thetype = 2;
				ss=ss+a;
				ip++;
				a = inputBuffer[ip];
				while(a >= '0' && a<='9'){
					ss = ss+a;
					ip++;
					a = inputBuffer[ip];
				}
			} else{
				thetype = 1;
			}
			
			ip--;
		} else{
			inta =  map(a);
		}
		
		if(inta == -1){
			cout<<"非法输入"<<endl;
			return;
		}
		if(AnalyseTable[X][inta][0] == 'S'){
			string t = "";
			for(int i = 1; i < AnalyseTable[X][inta].length(); i++){
				t = t + AnalyseTable[X][inta][i];
			}
			int num = atoi(t.c_str());
			stateStack.push(num);
			if(inta == 0){
				vl.type = thetype;
				vl.value = ss;
				valStack.push(vl);
			} else{
				vl.type = 0;
				vl.value = " ";
				valStack.push(vl);
			}
			
			ip++;
			cout<<"Shift "<<num<<endl;
		} else if(AnalyseTable[X][inta][0] == 'R'){
			int num = int(AnalyseTable[X][inta][1]) - '0';
			int beta = R[num].length()-3;
			for(int i = 0; i < beta; i++){
				stateStack.pop();
			}
			X = stateStack.top();
			a = R[num][0]; 
			inta = map(a);
			cout<<"Reduce by "<<R[num];
	
			string t = "";
			for(int i = 0; i < AnalyseTable[X][inta].length(); i++){
				t = t + AnalyseTable[X][inta][i];
			}
			int state = atoi(t.c_str()); 
			stateStack.push(state);
			VAL temp1,temp2, temp3;
			double d1, d2;
			switch(num){
				case 1:
					temp1 = valStack.top();
					valStack.pop();
					valStack.pop();
					temp2 = valStack.top();
					valStack.pop();
					d1 = stringToDouble(temp1.value);
					d2 = stringToDouble(temp2.value);
					temp3.value = doubleToString(d2+d1);
					if(temp1.type == 1 && temp2.type == 1){
						temp3.type = 1;
						valStack.push(temp3);
					} else{
						temp3.type = 2;
						valStack.push(temp3);
					}
					
					break;
				case 2:
					temp1 = valStack.top();
					valStack.pop();
					valStack.pop();
					temp2 = valStack.top();
					valStack.pop();
					d1 = stringToDouble(temp1.value);
					d2 = stringToDouble(temp2.value);
					temp3.value = doubleToString(d2-d1);
					if(temp1.type == 1 && temp2.type == 1){
						temp3.type = 1;
						valStack.push(temp3);
					} else{
						temp3.type = 2;
						valStack.push(temp3);
					}
					break;
				case 4:
					temp1 = valStack.top();
					valStack.pop();
					valStack.pop();
					temp2 = valStack.top();
					valStack.pop();
					d1 = stringToDouble(temp1.value);
					d2 = stringToDouble(temp2.value);
					temp3.value = doubleToString(d2*d1);
					if(temp1.type == 1 && temp2.type == 1){
						temp3.type = 1;
						valStack.push(temp3);
					} else{
						temp3.type = 2;
						valStack.push(temp3);
					}
					break;
				case 5:
					temp1 = valStack.top();
					valStack.pop();
					valStack.pop();
					temp2 = valStack.top();
					valStack.pop();
					d1 = stringToDouble(temp1.value);
					d2 = stringToDouble(temp2.value);
					temp3.value = doubleToString(d2/d1);
					if(temp1.type == 1 && temp2.type == 1){
						if((int)d2%(int)d1 == 0){
							temp3.type = 1;
							valStack.push(temp3);
						} else{
						 	temp3.type = 2;
							valStack.push(temp3);
						} 
						
					} else{
						temp3.type = 2;
						valStack.push(temp3);
					}
					break;
				case 7:
					valStack.pop();
					temp1 = valStack.top();
					valStack.pop();
					valStack.pop();
					valStack.push(temp1);
					break;
				default:
					break;
			}
			temp1 = valStack.top();
			if(temp1.type == 1){
				cout<<" type:int"<<endl;
			} else if(temp1.type == 2){
				cout<<" type:real"<<endl;
			}
			
		}else if(AnalyseTable[X][inta] == "ACC"){
			cout<<"ACC"<<endl;
			string sss = valStack.top().value;
			cout<<"\n计算结果为:"<<sss<<endl;
			return;
		}
		else if(AnalyseTable[X][inta][0] == 'E'){
			error(AnalyseTable[X][inta][1]);
		}
		else{
			error();
		} 
	}while(1);
}

/*输出*/
void printout()
{
	cout<<"由给定产生式进行语法分析，产生式如下："<<endl;
	cout<<"E->E+T | E-T | T\nT->T*F | T/F | F\nF-> (E) | num | num.num"<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<"拓展文法后："<<endl;
	for(int i = 0; i < Gsize; i++){
		cout<<'('<<i<<')'<<R[i]<<endl;
	}
	cout<<"------------------------------------------------------------------"<<endl;
	
	cout<<"\tFirst\tFollow"<<endl;
	for(int i = 0; i < Nsize; i++){
		cout<<N[i]<<"\t";
		for(int j = 0; j < First[i].size(); j++){
			cout<<First[i][j]<<" ";
		}
		cout<<"\t";
		for(int j = 0; j < Follow[i].size(); j++){
			cout<<Follow[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"------------------------------------------------------------------"<<endl;
	
	string emp = "";
	cout<<left<<setw(6)<<emp;
	for(int j = 0; j < columnNum; j++){
		cout<<left<<setw(6)<<item[j];
	}
	cout<<endl;
	for(int i = 0; i < stateNum; i++){
		cout<<left<<setw(6)<<i;
		for(int j = 0; j < columnNum; j++){
			cout<<left<<setw(6)<<AnalyseTable[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"------------------------------------------------------------------"<<endl;
}

int main()
{

	string w;
	string y;
	cout<<"请输入要分析的符号串：";
	cin>>w;
	
	Init();
	createTable();
	printout();
	LR(w);
	
	return 0;
}
