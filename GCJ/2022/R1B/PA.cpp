#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fst first
#define sec second

using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		int n;
		cin >> n;
		int i = 0, j = n - 1;
		vector<int> arr(n);	
		for(auto &x : arr) cin >> x;
		int ans = 0;
		int prev = min(arr[0], arr[n-1]);
		while(i <= j){
			if(arr[i] < arr[j]){
				if(arr[i] >= prev){
					prev = arr[i];
					ans++;
				}
				i++;
			}else{
				if(arr[j] >= prev){
					prev = arr[j];
					ans++;
				}
				j--;
			}
		}
		cout << "Case #" << t << ": ";
		cout << ans << '\n';
	}
	
	return 0;
} 
