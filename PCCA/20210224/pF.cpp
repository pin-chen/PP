#include<bits/stdc++.h>
using namespace std;
char arr[102][102] = {};
void dfs(int i, int j){
	if(i<0||j<0)return;
	if(arr[i][j]=='.'){
		return;
	}
	arr[i][j] = '.';
	dfs(i+1,j);
	dfs(i+1,j+1);
	dfs(i,j+1);
	dfs(i-1,j+1);
	dfs(i-1,j);
	dfs(i-1,j-1);
	dfs(i,j-1);
	dfs(i+1,j-1);	
}
int main(){
	int m,n;
	cin>>m>>n;
	int ans = 0;
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cin>>arr[i][j];
		}
	}
	for(int i = 0; i <= m; i++){
		arr[i][n] = '.';
	}
	for(int i = 0; i <= n; i++){
		arr[m][i] = '.';
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(arr[i][j] == '#'){
				dfs(i,j);
				ans++;
			}
		}
	}
	cout<<ans<<'\n';
	return 0;
} 
