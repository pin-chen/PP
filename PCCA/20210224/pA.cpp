#include<bits/stdc++.h>
using namespace std;
int main(){
	int A, B, C, D;
	cin>>A>>B>>C>>D;
	int P, M, G;
	cin>>P>>M>>G;
	int p = 0, m = 0, g = 0;
	if(P % (A + B) <= A &&P % (A + B)!=0) p++;
	if(P % (C + D) <= C&&P % (C + D)!=0) p++;
	if(M % (A + B) <= A&&M % (A + B)!=0) m++;
	if(M % (C + D) <= C&&M % (C + D)!=0) m++;
	if(G % (A + B) <= A&&G % (A + B)!=0) g++;
	if(G % (C + D) <= C&&G % (C + D)!=0) g++;
	if(p == 0) cout<<"none"<<'\n';
	else if (p == 1) cout<<"one"<<'\n';
	else if (p == 2) cout<<"both"<<'\n';
	if(m == 0) cout<<"none"<<'\n';
	else if (m == 1) cout<<"one"<<'\n';
	else if (m == 2) cout<<"both"<<'\n';
	if(g == 0) cout<<"none"<<'\n';
	else if (g == 1) cout<<"one"<<'\n';
	else if (g == 2) cout<<"both"<<'\n';
	return 0;
} 
