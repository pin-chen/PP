#include<bits/stdc++.h>
using namespace std;
int main(){
	int D, R, T;
	cin>>D>>R>>T;
	int a, b, c;
	a = 1;
	b = (1 - 2 * D -2 +3)/2;
	c = (-3*D -6 +D*D +2*D - 12 )/2 -R -T;
	int x = ( -b + sqrt(b*b-4*a*c) ) / (2*a);
	//int x2 = (-b - sqrt(b*b-4*a*c))/(2*a);
	//if(x<0)x=x2;
	//cout<<x<<" "<<x2<<'\n';
	cout<<R-(x*x+x-12)/2<<'\n';
	return 0;
} 
