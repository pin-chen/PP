#include<bits/stdc++.h>
using namespace std;
int main(){
	int arr[8] = {};
	int Pri[8] = {2, 3, 5, 7, 11, 13, 17, 19};
	int x[8] = {0, 2, 6, 30, 210 ,2310, 30030, 510510};
	int ans = 0;
	
	for(int i = 0; i < 8; i++){
		cin>>arr[i];
	}
	for(int i = 0; i < 8; i++){
		int t = (Pri[i] - arr[i] - 1) * x[i];
		ans += t ; 
		//cout<<t<<'\n';
		//ans *= (Pri[i] - arr[i]);
	}
	cout<<ans+(1-arr[0])<<'\n';
	
	
	return 0;
} 
