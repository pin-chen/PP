#include<bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int t;
	cin>>t;
	for(int i = 0; i < t; i++){
		int a, b, k;
		cin>>a>>b>>k;
		int boy[k] = {};
		int girl[k] = {};
		for(int j = 0; j < k; j++){
			cin>>boy[j];
		}
		for(int j = 0; j < k; j++){
			cin>>girl[j];
		}
		int ans = 0;
		for(int j = 0; j < k - 1; j++){
			for(int q = j + 1; q < k; q++){
				if(boy[j] == boy[q] || girl[j] == girl[q]){
					continue;
				}else{
					//cout<<boy[j]<<" "<<girl[j]<<'\n';
					//cout<<boy[q]<<" "<<girl[q]<<'\n'; 
					ans++;
				}
			}
		}
		cout<<ans<<'\n';
	} 
	return 0;
} 
