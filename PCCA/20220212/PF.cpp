#include <iostream>
#include <iomanip>
using namespace std;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	char fig[n][m]= {};
	int out[n][m] = {};
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> fig[i][j];
		}
	}
	bool T = true;
	int x = 0;
	while(T){
		x++;
		T = false;
		char temp[n][m] =  {};
		for(int i = 0 + x - 1; i < n - x + 1; i++){
			for(int j = 0 + x - 1; j < m -x + 1; j++){
				temp[i][j] = fig[i][j];
				if(fig[i][j] == 'T'){
					T = true;
					if(	(i == 0 || fig[i-1][j] == '.') ||
						(j == 0 || fig[i][j-1] == '.') || 
						(i == n-1 || fig[i+1][j] == '.') || 
						(j == m-1 || fig[i][j+1] == '.')){
						temp[i][j] = '.';
						out[i][j] = x;
					}
				}
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				fig[i][j] = temp[i][j];
			}
		}
	}
	int t = 1;
	while(x){
		x/=10;
		t++;
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(out[i][j] == 0){
				for(int k = 0; k < t; k++) cout << '.';
			}else{
				cout << std::setfill('.') << std::setw(t) << out[i][j]; 
			}
		}
		cout << '\n';
	}
	return 0;
} 
