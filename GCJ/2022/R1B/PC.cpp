#include <bits/stdc++.h>
using namespace std;
int main(){
	int x;
	string out = "00000001";
	int T;
	cin >> T;
	while(T--){
		cout << out << '\n';
		while(cin >> x){
			if(x == 0 || x == -1) break;
			for(int i = 0; i < 8; i++){
				out[i] = '0';
	 		}
	 		if( x != 0 && x <= 4){
	 			for(int i = 0; i < 8; i += (8 / x) ){
		 			out[i] = '1';
				}
			}else{
				for(int i = 0; i < min(x, 8); i++){
		 			out[i] = '1';
				}
			}
			cout << out << '\n';
		}
	}
	return 0;
}
