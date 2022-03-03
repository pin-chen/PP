#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	if(n == 1){
		cout << 2 << '\n';
		cout << 1 << '\n';
		cout << 1 << '\n';
		return 0;
	}
	cout << n + n - 1 << '\n';
	int arr[n-1][n-1] = {};
	int num = 3;
	for(int i = 0; i < n-1; i++){
		for(int j = 0; j < n-1; j++){
			arr[i][j] = num++;
		}
	}
	
	for(int i = 0; i < n - 1; i++){
		cout << "1";
		for(int j = 0; j < n - 1; j++){
			cout << " " << arr[i][j];
		}
		cout << '\n';
	}
	
	for(int j = 0; j < n - 1; j++){
		cout << "2";
		for(int i = 0; i < n - 1; i++){
			cout << " " << arr[i][j];
		}
		cout << '\n';
	}
	cout << "1 2";
	for(int i = 0; i < n - 2; i++){
		cout << " " << num + i;
	}
	cout << '\n';
	
	
	return 0;
} 
