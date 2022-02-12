#include <iostream>
using namespace std;
int main(){
	int n, p;
	cin >> n >> p;
	int arr[n];
	int sum = 0;
	for(int i = 0; i < n; i++){
		cin >> arr[i];
		sum += arr[i];
	}
	if(p >= 100){
		cout << "impossible\n";
	}else{
		int ans = (double) (n * p - sum) / (100 - p) + 0.99;
		cout << ans << '\n';
	}
	
	return 0;
}
