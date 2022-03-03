#include <bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		int n, m;
		cin >> n >> m;
		int arr[2][m];
		for(int i = 0; i < m; i++){
			cin >> arr[0][i] >> arr[1][i];
		}
		cout << m << '\n';
		for(int i = 0; i < m; i++){
			cout << "0 " << arr[0][i] << " " << arr[1][i] << '\n';
		}

	}
	return 0;
} 
