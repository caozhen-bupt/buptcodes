/*2班 2014211182 曹桢	第一次编译原理程序*/ 

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include <cstdlib>
#include<vector>

using namespace std;

const int bufferSize = 1000;											//半个缓冲区的大小 

struct ID{															//用户自定义标识符 
	string name;													//标识符名称 
	int pos;														//标识符入口地址 
};

struct Error{														//错误 
	int where;														//错误行数 
	string err;														//错误的字符串 
	int kind;														//错误种类 
};

int state;															//自动机状态 
char C;																//当前读入的字符 
string token;														//当前正在识别的单词字符串 
char buffer1[bufferSize];											//输入缓冲区左半区 
char buffer2[bufferSize];											//输入缓冲区右半区 
char *forward;														//向前指针 
char *lexemebegin;													//指向buffer中当前单词的开始位置
int iskey;															//值为-1，表示识别出的单词是用户自定义标识符，否则，表示识别出的单词是关键字
int line;															//统计行数 
int charactor;														//统计字符总数 
int keychar;														//统计关键字个数 
int relop;															//统计关系运算符个数 
int assign_op;														//统计赋值运算符个数 
int logic_op;														//统计逻辑运算符个数 
int numcount;														//统计常数个数 
int otherchar;														//统计其他字符数 
int idcount;														//统计用户标识符数 
int stringcount;													//统计“”字符串数 
vector <ID> table;													//标识符表 
vector <Error> countError;											//错误信息表 
fstream file;														//源程序 

//根据forward的指示从buffer中读一个字符，并把它放入变量C中，然后，移动forward，使之指向下一个字符。
void get_char(); 
//检查C中的字符是否为空格，若是，则反复调用过程get_char，直到C中进入一个非空字符为止。
void get_nbc();
//把C中的字符连接在token中的字符串后面 
void cat();
//判断C中的字符是否为字母 
bool letter();
//判断C中的字符是否为数字 
bool digit();
//向前指针forward后退一个字符 
bool retract();
//根据token中的单词查关键字表 
int reserve();
//将识别出来的标识符（即token中的单词）插入符号表，返回该单词在符号表中的位置指针 
int table_insert();
//对发现的错误进行相应的处理 
void error(int which);
//自动机 
void automachine();

int main()
{
	line = 1;
	charactor = 0;
	keychar = 0;
	relop = 0;
	assign_op = 0;
	logic_op = 0;
	numcount = 0;
	otherchar = 0;
	idcount = 0;
	stringcount = 0;
	
	state = 0;
	C = ' ';
	token = "";
	buffer1[bufferSize-1] = -1;
	buffer2[bufferSize-1] = -1;
	lexemebegin = buffer1;
	forward = buffer1;
	char filename[100] = "test3.txt";
	
	
	
	file.open(filename, ios::in);													
	if(!file){  																	
		cout<<"Failed to open "<<filename<<"!"<<endl;
		return -1;
	}
	int i = 0;
	while(i < bufferSize-1){											
		buffer1[i]=file.get();
		i++;
	}
	do
	{
		automachine();
	}while(C!=EOF);
	
	cout<<"-----------------------------\n- Statistics:"<<endl;
	cout<<"totoal line: "<<line<<endl;
	cout<<"total charactor:"<<charactor<<endl;
	cout<<"key charactor:"<<keychar<<endl;
	cout<<"relation operator: "<<relop<<endl;
	cout<<"assign operator:"<<assign_op<<endl;
	cout<<"logic operator:"<<logic_op<<endl;
	cout<<"number: "<<numcount<<endl;
	cout<<"other charactor:"<<otherchar<<endl;
	cout<<"how many ids set in code:"<<idcount<<endl;
	cout<<"how many ids set in table:"<<table.size()<<endl;
	cout<<"how many strings: "<<stringcount<<endl;
	
	if(countError.empty()){
		cout<<"-----------------------------\n- Errors: 0"<<endl;
	}
	else{
		cout<<"-----------------------------\n- Errors:"<<endl;
		cout<<"line"<<'\t'<<"Error"<<endl;
		for(int i = 0; i < countError.size(); i++){
			switch(countError[i].kind){
				case 0:
					cout<<countError[i].where<<'\t'<<"[Error]"<<countError[i].err<<"  There should be digits after . to compose a number."<<endl;
					break;
				case 1:
					cout<<countError[i].where<<'\t'<<"[Error]"<<countError[i].err<<"  There should be digits or + or - after E to compose a number."<<endl;
					break;
				case 2:
					cout<<countError[i].where<<'\t'<<"[Error]"<<countError[i].err<<"  There should be digits after + or - to compose a number."<<endl;
					break;
				case 3:
					cout<<countError[i].where<<'\t'<<"[Error]"<<countError[i].err<<"  Invalid character!"<<endl;
					break;
				default:
					cout<<countError[i].where<<'\t'<<"[Error]"<<"Unknown Error!"<<endl;
			}
			
		} 
	}
	
	file.close();	
	return 0;
}


void get_char()
{
	
	if((*forward) == -1){
		if(forward== buffer1+bufferSize-1){
			int i = 0;
			while(i < bufferSize-1){															
				buffer2[i]=file.get(); 
				i++; 
			}
			forward=buffer2;
		}
		else if(forward== buffer2+bufferSize-1){
			int i = 0;
			while( i < bufferSize-1){															
				buffer1[i]=file.get(); 
				i++;
			}
			forward = buffer1;
		}
		else
		{
			file.close();
		}
	}
	C = *forward;
	forward++;
}

void get_nbc()
{
	while(C == ' ' || C == '\t' || C == '\n'){
		if(C == '\n'){
			line++;
		}
		get_char();	
	}
}

void cat()
{
	token = token + C;
}

bool letter()
{
	if(C >= 'A' && C <= 'z') return true;
	else return false;
}

bool digit()
{
	if(C >= '0' && C <= '9') return true;
	else return false;
}

bool retract()
{
	if(forward == buffer1){
		forward = buffer2+bufferSize-1;
	}
	else if(forward == buffer2){
		forward = buffer1+bufferSize-1;
	}
	else{
		forward--;
	} 
}

int reserve()
{
	if( token == "void" || token == "char" || token == "int" || token == "float"
	|| token == "double" || token == "short" || token == "long" || token == "signed"
	|| token == "unsigned" || token == "struct" || token == "union" || token == "enum"
	|| token == "typedef" || token == "sizeof" || token == "auto" || token == "static"
	|| token ==  "register" || token == "extern" || token == "const" || token ==  "volatile"
	|| token == "return" || token ==  "continue" || token == "break" || token == "goto"
	|| token == "if" || token == "else" || token ==  "switch" || token == "case"
	|| token == "default" || token == "for" || token == "do" || token == "while"){
		return 1;
	}
	else return -1;
}

int table_insert()
{
	int len = table.size();
	for(int i = 0; i < len; i++){
		if(table[i].name == token){
			return i;
		}
	}
	ID newid;
	newid.name = token;
	newid.pos = len;
	table.push_back(newid);
	return len;
}

void error(int which)
{
	Error e;
	e.where = line;
	e.err = token;
	e.kind = which;
	countError.push_back(e);
	lexemebegin = forward;	
}

void automachine()
{
	switch ( state ) { 
	    case 0:       
			get_char();
			get_nbc();
			if(letter() || C == '_'){
				state = 1;
			}
			else if(digit()){
				state = 2;
			}
			else{
				switch ( C ) {
		            case '<': state = 8; break;   
		            case '>': state = 9; break;      
					case '!': state = 15; break;  
					case '&': state = 16; break;
					case '|': state = 17; break;
					case '#': state = 18; break;
		            case '/': state = 11; break;   
		            case '=': state = 10; break;      
		            case '+': state = 0; cout << '+' << '\t' << '(' << '+' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;             
		            case '-': state = 0; cout << '-' << '\t' << '(' << '-' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;             
		            case '*': state = 0; cout << '*' << '\t' << '(' << '*' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;             
		            case '(': state = 0; cout << '(' << '\t' << '(' << '(' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;               
		            case ')': state = 0; cout << ')' << '\t' << '(' << ')' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;
					case '[': state = 0; cout << '[' << '\t' << '(' << '[' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;     
					case ']': state = 0; cout << ']' << '\t' << '(' << ']' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;     
					case '{': state = 0; cout << '{' << '\t' << '(' << '{' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;     
					case '}': state = 0; cout << '}' << '\t' << '(' << '}' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;     
		            case ';': state = 0; cout << ';' << '\t' << '(' << ';' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;
					case ':': state = 0; cout << ':' << '\t' << '(' << ':' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;  
					case ',': state = 0; cout << ',' << '\t' << '(' << ',' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;            
		            case '\'': state = 0; cout << '\'' << '\t' << '(' << '\'' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;
		            case '"': state = 19; cout << '"' << '\t' << '(' << '"' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;
		            case '\\': state = 0; cout << '\\' << '\t' << '(' << '\\' << ',' << '-' << ')' << endl; charactor++; otherchar++; lexemebegin = forward; break;
		            default: state = 13; break;
	        	};
			}
	       break;
		case 1:     
	       cat();
	       get_char();
	       if ( letter() || digit() || C == '_')  state = 1;
	       else {  
	            retract();
	            state = 0;
	            iskey = reserve();    
	            if ( iskey == 1 ) {
	            	cout << token << '\t' << '(' << token << ',' << '-' << ')' << endl;
	            	keychar++;
					charactor++;
	            	token.clear();
	            	lexemebegin = forward;
	            }
	            else {    
	                 int identry = table_insert();
	                 cout << token << '\t' << '(' << "ID" << ',' << identry << ')' << endl;
	                 idcount++;
	                 charactor++;
	                 lexemebegin = forward;
	                 token.clear();
					 
	             };
	         };
	      break;
		case 2:
	       cat(); 
	       get_char();
	       if(digit()){
				state = 2;
			}
			else {
				switch ( C ) {
		            case '.' : state=3; break;
		            case 'E': state=5; break;
		            default:   
			            retract(); 
			            state = 0;
			            cout << token << '\t'<< '(' << "NUM" << ',' << atoi(token.c_str()) << ')' << endl;
			            numcount++;
			            charactor++;
	                 	lexemebegin = forward;
			            token.clear();
			            break;
	       		};
			}
	        break;
	    case 3:
			cat(); 
	        get_char();	    
	        if(digit()){
	        	state = 4;
	        }
	        else{
	        	retract();
	        	error(0);
	        	state = 0;
	        	token.clear();
	        }
	        break;
		case 4:
			cat(); 
	        get_char();
	        if(digit()){
	        	state = 4;
	        }
	        else if(C == 'E'){
	        	state = 5;
	        }
	        else{
	        	retract(); 
	            state=0;
	            cout << token << '\t'<< '(' << "NUM" << ',' << atof(token.c_str()) << ')' << endl;
	            numcount++;
	            charactor++;
	            lexemebegin = forward;
	            token.clear();
	        }
	        break;
	    case 5:
	    	cat(); 
	        get_char();
	    	if(digit()){
	        	state = 7;
	        }
	        else if(C == '+' || C == '-'){
	        	state = 6;
	        }
	        else{
	        	retract();
	        	error(1);
	        	state = 0;
	        	token.clear();
	        }
	    	break;
	    case 6:
	    	cat(); 
	        get_char();
	        if(digit()){
	        	state = 7;
	        }
	        else{
	        	retract();
	        	error(2);
	        	state = 0;
	        	token.clear();
	        }
	    	break;
	    case 7:
	    	cat(); 
	        get_char();
	        if(digit()){
	        	state = 7;
	        }
	        else{
	        	retract();
	        	state = 0;
	        	cout << token << '\t'<< '(' << "NUM" << ',' << atof(token.c_str()) << ')' << endl;
	        	numcount++;
	        	charactor++;
	        	lexemebegin = forward;
				token.clear();
	        }
	    	break;
	    case 8:
	    	cat(); 
	        get_char();
	    	if(C == '=') {
	    		state = 0;
	    		cout << "<=" << '\t' << '(' << "relop" << ',' << "LE" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else {
	    		retract();
	    		state = 0;
	    		cout << '<' << '\t' << '(' << "relop" << ',' << "LT" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	break;
		case 9:
			cat(); 
	        get_char();
	    	if(C == '=') {
	    		state = 0;
	    		cout << ">=" << '\t' << '(' << "relop" << ',' << "GE" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else {
	    		retract();
	    		state = 0;
	    		cout << '>' << '\t' << '(' << "relop" << ',' << "GT" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
			break;
		case 10:
			cat(); 
	        get_char();
	    	if(C == '=') {//判断相等 
	    		state = 0;
	    		cout << "==" << '\t' << '(' << "relop" << ',' << "EQ" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else {//赋值 
	    		retract();
	    		state = 0;
	    		cout << '=' << '\t' << '(' << "assign_op" << ',' << '-' << ')' << endl;
	    		assign_op++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
			break;
		case 11:
			cat(); 
	        get_char();
			if(C == '*') {
				state = 12;
			}
			else if(C == '/') {
				state = 14;
			}
			else {
				retract();
	    		state = 0;
	    		cout << '/' << '\t' << '(' << '/' << ',' << '-' << ')' << endl;
	    		otherchar++;
				charactor++;
				lexemebegin = forward;
	    		token.clear();
			}
			break;
		case 12:
			get_char();
			token.clear(); 
			while(C != '*') get_char();
			get_char();
			if(C == '/'){
				state = 0;
			} 
			else state = 12;
			break;
		case 13:
			error(3);
			state = 0;
			break;
		case 14:
			get_char();
			while(C != '\n') get_char();
			line++;
			state = 0;
			break;
		case 15:
			cat(); 
	        get_char();
	    	if(C == '=') {//判断不等 
	    		state = 0;
	    		cout << "!=" << '\t' << '(' << "relop" << ',' << "NE" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else{
	    		retract();
	    		state = 0;
	    		cout << '!' << '\t' << '(' << "logic_op" << ',' << "NOT" << ')' << endl;
	    		logic_op++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    case 16:
	    	cat(); 
	        get_char();
	    	if(C == '&'){
	    		state = 0;
	    		cout << "&&" << '\t' << '(' << "logic_op" << ',' << "AND" << ')' <<endl;
	    		logic_op++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else{
	    		retract();
	    		cout << "&" << '\t' << '(' << "&" << ',' << "-" << ')' <<endl;
	    		state = 0;
	    		otherchar++;
				charactor++;
				lexemebegin = forward;
	    		token.clear();
	    	}
	    	break;
	    case 17:
	    	cat(); 
	        get_char();
	    	if(C == '|'){
	    		state = 0;
	    		cout << "||" << '\t' << '(' << "logic_op" << ',' << "OR" << ')' <<endl;
	    		logic_op++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else{
	    		retract();
	    		error(3);
	    		state = 0;
	    	}
	    	break;
	    case 18:
	    	get_char();
			while(C != '\n') get_char();
			line++;
			state = 0;
			break;
		case 19:
			get_char();
			while(C != '"') {
				cat();
				get_char();
			}
			cout << token << '\t' << '(' << "const string" << ',' << token << ')' <<endl;
			stringcount++;
			charactor++;
			cout << '"' << '\t' << '(' << '"' << ',' << '-' << ')' << endl; 
			otherchar++;
			charactor++;
			lexemebegin = forward;
			token.clear();
			state = 0;
			break;
	} 
}

