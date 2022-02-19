#include<iostream>
#include<string>
using namespace std;

int n;
char table[101][101];
char temp[101][101];



void FH(){
	
}

void FV(){
	
}

void FMD(){
	
}

void FAD(){
	
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
		
		while(s.find("< > ") < n ){
			s = s.replace(s.find("< > "), 4, "");
		}
		while(s.find("> < ") < n ){
			s = s.replace(s.find("> < "), 4, "");
		}
		while(s.find("- - ") < n ){
			s = s.replace(s.find("- - "), 4, "");
		}
		while(s.find("| | ") < n ){
			s = s.replace(s.find("| | "), 4, "");
		}
		while(s.find("\\ \\ ") < n ){
			s = s.replace(s.find("\\ \\ "), 4, "");
		}
		while(s.find("/ / ") < n ){
			s = s.replace(s.find("/ / "), 4, "");
		}
		while(s.find("/ \\ ") < n ){
			s = s.replace(s.find("/ \\ "), 4, "> > ");
		}
		while(s.find("\\ / ") < n ){
			s = s.replace(s.find("\\ / "), 4, "> > ");
		}
		while(s.find("< < ") < n ){
			s = s.replace(s.find("< < "), 4, "> > ");
		}
		while(s.find("| - ") < n ){
			s = s.replace(s.find("| - "), 4, "> > ");
		}
		while(s.find("- | ") < n ){
			s = s.replace(s.find("- | "), 4, "> > ");
		}
		while(s.find("> > > > ") < n ){
			s = s.replace(s.find("> > > > "), 8, "");
		}
		while(s.find("> > > ") < n ){
			s = s.replace(s.find("> > > "), 6, "< ");
		}
		
		for(int i = 0; i < n; i+=2){
			switch(s[i]){
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
				case '\\':{
					FMD();
					break;
				} 
				case '/':{
					FAD();
					break;
				}
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout >> table[i][j];
			}
		}
	}
	
	return 0;
} 


 



