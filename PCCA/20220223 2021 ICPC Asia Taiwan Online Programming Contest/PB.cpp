#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	int ans[n];
	for(int i = 0; i < n; i++){
		int num, x = 1;
		cin >> num;
		for(int j = 2; j <= sqrt(n); j++){
			if(num % j == 0){
				x += j;
				x += num / j;
			}
		}
		if(x > num){
			ans[i] = 1;
		}else if( x < num){
			ans[i] = 2;
		}else{
			ans[i] = 3;
		}
	}
	for(int i = 0; i < n; i++){
		if(ans[i] == 1){
			cout << "abundant\n";
		}else if(ans[i] == 2){
			cout << "deficient\n";
		}else{
			cout << "perfect\n";
		}
	}
	return 0;
}
