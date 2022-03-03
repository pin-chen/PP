#include <iostream>
using namespace std;
int main(){
	long long int T;
	long long int t, x;
	cin >> T;
	while(T--){
		cin >> t >> x;
		if(x < 0){
			if( 0 - x > t){
				cout << "impossible\n";
			}else if((x+t)%2 == 0){
				cout << "right\n";
			}else{
				cout << "left\n";
			}
		}else{
			if( x > t){
				cout << "impossible\n";
			}else if((x-t)%2 == 0){
				cout << "right\n";
			}else{
				cout << "left\n";
			}
		}
			
	}
	return 0;
} 
