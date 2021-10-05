#include<bits/stdc++.h>
using namespace std;
int main(){
	int arr[11]={1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796};
	int n;int t=0;
	while(cin>>n){
		if(t)cout<<'\n';
		cout<<arr[n]<<'\n';
	}
	return 0;
} 
