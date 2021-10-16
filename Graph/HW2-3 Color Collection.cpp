//ref: https://github.com/cormacpayne/Data-Structures-and-Algorithms/blob/master/dynamic-programming/bitmask-dynamic-programming/bitmask-dynamic-programming.md
#include <iostream>
using namespace std;
int adj[20][20] = {};
int color[20] = {};
int dp[1 << 20][20];
int n, K;
int tsp( int bitmask, int pos, int colormask ){
    if ( dp[ bitmask ][ pos ] != -1 )
        return dp[ bitmask ][ pos ];
    if ( colormask == (1 << K) - 1 )
		return 0;
    int minDistance = 2147483647;
    for( int k = 0; k < n; k++ ){
        if( (bitmask & ( 1 << k )) == 0 ){
            minDistance = min( minDistance, adj[ pos ][ k ] + tsp( bitmask | ( 1 << k ), k, colormask | (1 << color[k]) ) );
        }
    }
    return dp[ bitmask ][ pos ] = minDistance;
}
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int m ,i, j, p;
	cin >> n >> m >> K;
	for (i = 0; i < 1 << n; i++) {
		for (j = 0; j < n; j++) {
			dp[i][j] = -1;
		}
	}
	for (i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		color[i] = x;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) adj[i][j] = 0;
			else adj[i][j] = 2147483647;
		}
	}
	for (i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		adj[a][b] = c;
		adj[b][a] = c;
	}
	for(p = 0; p < n; p++){
		for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				if (adj[i][j] > adj[i][p] + adj[p][j] && adj[i][p] != 2147483647 && adj[p][j] != 2147483647) {
					adj[i][j] = adj[i][p] + adj[p][j];
				}
			}
		}
	}
	int Min = 2147483647;
	for(i = n-1; i >=0; i--){
		int temp = tsp(1<<i, i,  (1<<color[i]));
		if(Min > temp) Min = temp;
	}
	cout << Min << '\n';
	return 0;
}
