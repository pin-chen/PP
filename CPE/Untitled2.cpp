#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,num;
	unsigned int F[11]={0,1,1};
	for(int i=3;i<11;i++){
		F[i]=F[i-2]*F[i-2]+F[i-1]*F[i-1];
	} 
	num=1;
	while(cin>>n){
		cout<<"case "<<num<<":"<<'\n';
		if(n<10)cout<<F[n]<<'\n';
		else cout<<"overflow"<<'\n';
		num++;
	}

	return 0;
} 
