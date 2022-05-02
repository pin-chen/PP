#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		int n, k;
		cin >> n >> k;
		int arr[n];
		ll x = 0, y = 0, z = 0;
		for(int i = 0; i < n; i++){
			cin >> arr[i];
			z += arr[i] * arr[i];
			x += arr[i];
		}
		//cout << " zx "<< z << " " << x << '\n';
		cout << "Case #" << t << ": ";
		y = z - x * x;
		if(x == 0){
			if(z == 0){
				cout << 1 << '\n';
			}else{
				cout << "IMPOSSIBLE\n";
			}
		}else{
			if(y % (2 * x) == 0){
				y = y / (2 * x);
				cout << y << '\n';
			}else{
				cout << "IMPOSSIBLE\n";
			}
		}
			
	}
	return 0;
} 
