#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;
	vector<string> arr;
	map<string, int> dic;
	while(getline(cin, s) ){
		if(s[0] == '0'){
			break;
		}
		string NEW;
		NEW.resize(s.size());
		int x = 0;
		for(int i = 0; i < s.size(); i++){
			if(s[i] == ' '){
				arr.push_back(NEW);
				NEW.resize(i);
				x = 0;
			}else if(s[i] == '+'){
				
			}else if(s[i] == '='){
				
			}else{
				NEW[x] = s[i];
			}
		}
	}
	
	return 0;
} 
