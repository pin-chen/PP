#include<iostream>
#include<set>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	int a, b, c;
	cin >> n >> k >> a >> b >> c;
	int player[n] = {};
	multiset<int> MAXMIN;
    int score[n][n];
    const int point[3] = {b, a, c};
    int MAX = 0, MIN = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> score[i][j];
			if(i == j)continue;
			player[i] += point[score[i][j]];
		}
        MAXMIN.insert(player[i]);
	}
    
    for(int i = 0; i < k; i++){
        int x, y, z, g;
        cin >> x >> y >> z;
        x--; y--; 
		g = z == 2 ? z : !z;
		MAXMIN.erase(MAXMIN.find(player[x]));
		MAXMIN.erase(MAXMIN.find(player[y]));
        player[x] = player[x] - point[score[x][y]] + point[z];
        player[y] = player[y] - point[score[y][x]] + point[g];
        score[x][y] = z;
        score[y][x] = g;
        MAXMIN.insert(player[x]);
        MAXMIN.insert(player[y]);
        cout << *MAXMIN.rbegin() - *MAXMIN.begin() << " ";
    }
	cout << '\n';
	return 0;
}
