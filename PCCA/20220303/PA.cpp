#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	
	int m = n * n;
	int arr[m];
	int color[n + 2] = {};
	vector<vector<int>> c2i(n+2);
	int ans[m];
	for(int i = 0; i < m; i++){
		cin >> arr[i];
		color[arr[i]]++;
		c2i[arr[i]].push_back(i);
	}
	set<pair<int, int>> com;
	for(int i = 1; i < n + 2; i++){
		com.insert(make_pair(color[i], i));
	}
	int box = 1;
	while(com.size() != 0){
		pair<int, int> small = *com.begin();
		com.erase(small);
		if(com.size() == 0){
			if(small.first % n != 0){
				cout << "NO";
				return 0;
			} else {	
				while(small.first >= n){
					small.first -=n ;
					for(int abc = 0; abc < n; abc ++) {
						ans[c2i[small.second].back()] = box;
						c2i[small.second].pop_back();
					}
					box++;
				}
			}
			break;
		}
		pair<int, int> big = *com.rbegin();
		com.erase(big);
		while(small.first >= n){
			small.first -=n ;
			for(int abc = 0; abc < n; abc ++) {
				ans[c2i[small.second].back()] = box;
				c2i[small.second].pop_back();
			}
			box++;
		}
		if(small.first != 0 and small.first < n){
			big.first -= (n - small.first);
			if(big.first < 0){
				cout << "NO";
				return 0;
			}
			for(int abc = 0; abc < n - small.first; abc ++) {
				ans[c2i[big.second].back()] = box;
				c2i[big.second].pop_back();
			}
			for(int abc = 0; abc < small.first; abc ++) {
				ans[c2i[small.second].back()] = box;
				c2i[small.second].pop_back();
			}
			box++;
		}
		if(big.first != 0)
			com.insert(big);
	}
	cout << "YES" << endl;
	for(int i = 0; i < m; i++)
		cout << ans[i] << ' ';
	return 0;
} 
