#include<iostream>
#include <string>
#include <algorithm>
using namespace std;


struct country{
	int a, b, c;
	string s;
};

bool cmp1(country& a, country&b){
	if(a.a != b.a){
		return a.a > b.a;
	}else{
		if(a.b != b.b){
			return a.b > b.b;
		}else{
			return a.c > b.c;
		}
	}
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	cin.ignore();
	country rank[n];
	for(int i = 0; i < n; i++){
		string x;
		
		getline(cin, x);
		int numC = 0;
		for(int j = 0; j < 3; j++){
			int t = 0;
			while( x[numC] >= '0' && x[numC] <= '9'){
				
				t *= 10;
				t += x[numC] - '0';
				numC++;
			}
			numC++;
			if(j == 0){
				rank[i].a = t;
			}else if (j == 1){
				rank[i].b = t;
			}else{
				rank[i].c = t;
			}
		}
		rank[i].s = x.erase(0,numC);
		//cout << rank[i].a << rank[i].b << rank[i].c << rank[i].s;
	}
	
	sort(rank, rank+n, cmp1);
	cout << rank[0].s << '\n';
	return 0;
}
