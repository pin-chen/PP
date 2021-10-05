#include<bits/stdc++.h>
using namespace std;
vector<int> arr;

//int arr[MM]={1,2};
int x(int y){
	if(y==1)return 1;
	else if(y%2==1){
		if(arr[3*y+1]==0){
			arr[3*y+1]=x(3*y+1);
		}
		return arr[3*y+1]+1;
	}
	else{
		if(arr[y/2]==0){
			arr[y/2]=x(y/2);
		}
		return arr[y/2]+1;
	} 
}
int main(){
	int n,m;
	arr.resize(1e6+1);
	while(cin>>n>>m){
		cout<<n<<" "<<m<<" ";
		int MAX=0;
		for(int i=n;i<=m;i++){
			arr[i]=x(i);
			MAX=max(MAX,arr[i]);
		}
		cout<<MAX<<'\n';
	}
	return 0;
} 
