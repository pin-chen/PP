#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> 
using namespace std;

bool BFS(vector< vector<int> >& adj, vector<int>& color){
	for(int i = 0; i < color.size(); i++){
		if(color[i] != 0) continue;
		queue<int> q;
		color[i] = 1;
		q.push(i);
		while(q.size() != 0){
			for(int i = 0; i < adj[q.front()].size(); i++){
				if(color[adj[q.front()][i]] == 0){
					q.push(adj[q.front()][i]);
					if(color[q.front()] == 1){
						color[adj[q.front()][i]] = 2;
					}else{
						color[adj[q.front()][i]] = 1;
					}
				}else{
					if(color[q.front()] == 1){
						if(color[adj[q.front()][i]] != 2) return false;
					}else{
						if(color[adj[q.front()][i]] != 1) return false;
					}
				}
			}
			q.pop();
		}
	}		
	return true;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj;
	vector<int> color;
	adj.resize(n);
	color.resize(n);
	while(m--){
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	if(BFS(adj, color) == true){
		cout << count(color.begin(), color.end(), 1) << " " << count(color.begin(), color.end(), 2) <<'\n';
	}else{
		cout << "-1" << '\n'; 
	} 
	return 0;
}
