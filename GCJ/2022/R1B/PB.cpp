#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fst first
#define sec second

using namespace std;

ll out;
int n, p;
void next(vector< vector<int> > arr, int i){
	if(i >= n) return;
	do{
		next(arr, i + 1);
		ll ans = 0;
		int prev = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < p; j++){
				ans += abs(arr[i][j] - prev);
				prev = arr[i][j];
			}
		}
		out = min(ans, out);
	}while(next_permutation(arr[i].begin(), arr[i].end()));
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		cin >> n >> p;
		vector< vector<int> > arr(n);
		for(int i = 0; i < n; i++){
			arr[i].resize(p);
			for(int j = 0; j < p; j++){
				cin >> arr[i][j];
			}
			sort(arr[i].begin(), arr[i].end());
		}
		out = 0;
		int prev = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < p; j++){
				out += abs(arr[i][j] - prev);
				prev = arr[i][j];
			}
		}
		next(arr, 0);
		cout << "Case #" << t << ": " << out <<'\n';
	}
	return 0;
}

