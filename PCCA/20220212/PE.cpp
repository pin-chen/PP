#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(){
	string s;
	getline(cin, s);
	
	int n;
	cin >> n;
	cin.ignore();
	
	string str[n];
	for(int i = 0; i < n; i++) getline(cin, str[i]);
	int x = 0;
	s = str[0];
	vector<string> arr;
	for(int i = 0; i <= s.size(); i++){
		if( i == s.size() || s[i] == ','){
			arr.push_back(s.substr(x, i - x));
			x = i + 2;
		}
	}
	int num = arr.size();
	string sub[n][num];
	for(int k = 0; k < n; k++){
		for(int i = 0; i < num; i++){
			sub[k][i] = arr[i];
		}
		if(k >= n-1) break;
		arr.clear();
		s = str[k + 1];
		x = 0;
		for(int i = 0; i <= s.size(); i++){
			if( i == s.size() || s[i] == ','){
				arr.push_back(s.substr(x, i - x));
				x = i + 2;
			}
		}
	}
	int amount[n] = {};
	
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			int c = 0;
			for(int k = 0; k < num; k++){
				if(sub[i][k] != sub[j][k]){
					c++;
				}
			}
			amount[i] = max(amount[i], c);
			amount[j] = max(amount[j], c);
		}
	}
	int Min = amount[0];
	for(int i = 1; i < n; i++){
		Min = min(amount[i], Min);
	}
	
	for(int i = 0; i < n; i++){
		if(amount[i] == Min){
			cout << str[i] << '\n';
		}
	}
	
	return 0;
}
