#include<bits/stdc++.h>
#define int long long 
using namespace std;
int32_t main(){
	//cin.tie(0);
	//ios_base::sync_with_stdio(false);
	int t;
	cin>>t;
	for(int i = 0; i < t; i++){
		int n, k;
		cin>>n>>k;
		int a = k;
		while(n>k){
			/* 
			for(int j = 2; j <= n; j++){
				if(n%j){
					continue;
				}else{
					n /= j;
					break;
				}
			}*/
			k+=a;
		}
		int ans = 0;
		ans += (k / n) + (1 && (k % n) );
		//cout<<k<<" "<<n<<" "<<k%n<<" "<<k/n<<'\n';
		cout<<ans<<'\n';
	}
	return 0;
} 
