/*2�� 2014211182 ����	��һ�α���ԭ�����*/ 

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdio>
#include <cstdlib>
#include<vector>

using namespace std;

const int bufferSize = 1000;											//����������Ĵ�С 

struct ID{															//�û��Զ����ʶ�� 
	string name;													//��ʶ������ 
	int pos;														//��ʶ����ڵ�ַ 
};

struct Error{														//���� 
	int where;														//�������� 
	string err;														//������ַ��� 
	int kind;														//�������� 
};

int state;															//�Զ���״̬ 
char C;																//��ǰ������ַ� 
string token;														//��ǰ����ʶ��ĵ����ַ��� 
char buffer1[bufferSize];											//���뻺��������� 
char buffer2[bufferSize];											//���뻺�����Ұ��� 
char *forward;														//��ǰָ�� 
char *lexemebegin;													//ָ��buffer�е�ǰ���ʵĿ�ʼλ��
int iskey;															//ֵΪ-1����ʾʶ����ĵ������û��Զ����ʶ�������򣬱�ʾʶ����ĵ����ǹؼ���
int line;															//ͳ������ 
int charactor;														//ͳ���ַ����� 
int keychar;														//ͳ�ƹؼ��ָ��� 
int relop;															//ͳ�ƹ�ϵ��������� 
int assign_op;														//ͳ�Ƹ�ֵ��������� 
int logic_op;														//ͳ���߼���������� 
int numcount;														//ͳ�Ƴ������� 
int otherchar;														//ͳ�������ַ��� 
int idcount;														//ͳ���û���ʶ���� 
int stringcount;													//ͳ�ơ����ַ����� 
vector <ID> table;													//��ʶ���� 
vector <Error> countError;											//������Ϣ�� 
fstream file;														//Դ���� 

//����forward��ָʾ��buffer�ж�һ���ַ����������������C�У�Ȼ���ƶ�forward��ʹָ֮����һ���ַ���
void get_char(); 
//���C�е��ַ��Ƿ�Ϊ�ո����ǣ��򷴸����ù���get_char��ֱ��C�н���һ���ǿ��ַ�Ϊֹ��
void get_nbc();
//��C�е��ַ�������token�е��ַ������� 
void cat();
//�ж�C�е��ַ��Ƿ�Ϊ��ĸ 
bool letter();
//�ж�C�е��ַ��Ƿ�Ϊ���� 
bool digit();
//��ǰָ��forward����һ���ַ� 
bool retract();
//����token�еĵ��ʲ�ؼ��ֱ� 
int reserve();
//��ʶ������ı�ʶ������token�еĵ��ʣ�������ű����ظõ����ڷ��ű��е�λ��ָ�� 
int table_insert();
//�Է��ֵĴ��������Ӧ�Ĵ��� 
void error(int which);
//�Զ��� 
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
	    	if(C == '=') {//�ж���� 
	    		state = 0;
	    		cout << "==" << '\t' << '(' << "relop" << ',' << "EQ" << ')' << endl;
	    		relop++;
				charactor++;
				lexemebegin = forward;
				token.clear();
	    	}
	    	else {//��ֵ 
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
	    	if(C == '=') {//�жϲ��� 
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

