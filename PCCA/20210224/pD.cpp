#include<bits/stdc++.h>
using namespace std;
int main(){
	int e, f, c;
	cin>>e>>f>>c;
	e += f;
	int ans = 0;
	while(e >= c){
		ans += (e / c);
		e = e / c + e % c;
	}
	cout<<ans<<'\n';
	return 0;
} 
