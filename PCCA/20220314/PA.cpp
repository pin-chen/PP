#include <bits/stdc++.h>
#define int long long
using namespace std;
int32_t main(){
	int n;
	cin >> n;
	//cin.ignore();
	string a, b;
	cin >> a >> b;
	int dp[n] = {};
	int dp2[n] = {};
	if(a[0] < b[0]){
		dp[0] = 1;
	}else if(a[0] == b[0]){
		dp2[0] = 1;
	}
	for(int i = 1; i < n; i++){
		dp[i] = dp[i-1];
		if(a[i] < b[i]){
			dp[i] += dp2[i-1] + 1;
		}else if(a[i] == b[i]){
			dp2[i] = dp2[i-1] + 1; 
		}
	}
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += dp[i];
	}
	cout << sum << '\n';
	return 0;
} 

