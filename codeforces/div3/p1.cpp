#include<bits/stdc++.h>
#define int long long
using namespace std;
int32_t main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int T;
	int n;
	cin>>T;
	for(int i = 0; i < T; i++){
		cin>>n;
		int ans = 0;
		for(int j = 1; j <= 1e14; j = j << 1){
			//cout<<j<<'\n';
			if(n & j){
				ans += 1;
				//cout<<"aa";
			}
		}
		if(ans == 1){
			cout<<"NO"<<'\n';
		}else{
			cout<<"YES"<<'\n'; 
		}
	}
	return 0;
} 
