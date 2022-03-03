#include<iostream>
#include<string>
using namespace std;

int n;
char table[101][101];
char temp[101][101];

void RR(){
	
}

void RL(){
	
}

void FH(){
	
}

void FV(){
	
}

void FMD(){
	
}

void FAD(){
	
}

void STAR(){
	
}

int main(){
	while(cin >> n){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin >> table[i][j];
			}
		}
		cin.ignore();
		string s;
		getline(cin, s);
		s.push_back(' ');
		s.push_back(' ');
		char prevC = s[0];
		string op;
		for(int i = 2; i < s.size() - 2; i+=2){
			switch(prevC){
				case '<':{
					switch(s[i]){
						case '<':{
							prevC = s[i+2];
							i+=2;
							op.push_back('*');
							break;
						}
						case '>':{
							prevC = s[i+2];
							i+=2;
							break;
						} 
						case '-':{
							prevC = '\\';
							break;
						} 
						case '|':{
							prevC = '/';
							break;
						} 
						case '/':{
							prevC = '-';
							break;
						} 
						case '\\':{
							prevC = '|';
							break;
						}
					}
					break;
				}
				case '>':{
					switch(s[i]){
						case '<':{
							prevC = s[i+2];
							i+=2;
							break;
						}
						case '>':{
							prevC = s[i+2];
							i+=2;
							op.push_back('*');
							break;
						} 
						case '-':{
							prevC = '/';
							break;
						} 
						case '|':{
							prevC = '\\';
							break;
						} 
						case '/':{
							prevC = '|';
							break;
						} 
						case '\\':{
							prevC = '-';
							break;
						}
					}
					break;
				} 
				case '-':{
					switch(s[i]){
						case '<':{
							prevC = '/';
							
							break;
						}
						case '>':{
							prevC = '\\';
							break;
						} 
						case '-':{
							prevC = s[i+2];
							i+=2;
							break;
						} 
						case '|':{
							prevC = s[i+2];
							i+=2;
							op.push_back('*');
							break;
						} 
						case '/':{
							prevC = '<';
							break;
						} 
						case '\\':{
							prevC = '>';
							break;
						}
					}
					break;
				} 
				case '|':{
					switch(s[i]){
						case '<':{
							prevC = '\\';
							
							break;
						}
						case '>':{
							prevC = '/';
							break;
						} 
						case '-':{
							prevC = s[i+2];
							i+=2;
							op.push_back('*');
							
							break;
						} 
						case '|':{
							prevC = s[i+2];
							i+=2;
							break;
						} 
						case '/':{
							prevC = '>';
							break;
						} 
						case '\\':{
							prevC = '<';
							break;
						}
					}
					break;
				}
				case '/':{
					switch(s[i]){
						case '<':{
							prevC = '|';
							
							break;
						}
						case '>':{
							prevC = '-';
							break;
						} 
						case '-':{
							prevC = '>';
							
							break;
						} 
						case '|':{
							prevC = '<';
							
							break;
						} 
						case '/':{
							prevC = s[i+2];
							i+=2;
							break;
						} 
						case '\\':{
							prevC = s[i+2];
							i+=2;
							op.push_back('*');
							break;
						}
					}
					break;
				} 
				case '\\':{
					switch(s[i]){
						case '<':{
							prevC = '-';
							
							break;
						}
						case '>':{
							prevC = '|';
							break;
						} 
						case '-':{
							prevC = '<';
							
							break;
						} 
						case '|':{
							prevC = '>';
							break;
						} 
						case '/':{
							prevC = s[i+2];
							i+=2;
							op.push_back('*');
							break;
						} 
						case '\\':{
							prevC = s[i+2];
							i+=2;
							
							break;
						}
					}
					break;
				}
			}
			cout << i << ":" << op << '\n';
		}
		cout << op << '\n';
		op.push_back(prevC);
		cout << op << '\n';
		while(op.find("* * ") < n ){
			op = op.replace(op.find("* * "), 4, "");
		}
		
		cout << op << '\n'; 
		
		for(int i = 0; i < n; i+=2){
			switch(op[i]){
				case '<':{
					RL();
					break;
				}
				case '>':{
					RR();
					break;
				} 
				case '-':{
					FV();
					break;
				} 
				case '|':{
					FH();
					break;
				} 
				case '/':{
					FMD();
					break;
				} 
				case '\\':{
					FAD();
					break;
				}
				case '*':{
					STAR();
					break;
				}
			}
		}
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << table[i][j];
			}
		}
	}
	
	return 0;
} 



 



