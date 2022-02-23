#include <iostream>
#include <iomanip>
using namespace std;
int main(){
	
	double ans[301] = {0, 0, 1, 0.75};
	
	for(int i = 4; i < 301; i++){
		double x = i;
		ans[i] =(double) (1.0/(x-1.0))+((x-2.0)/(x-1.0))*0.5; 
		//cout << setprecision(20) << ans[i] << '\n';
	}
	
	int n;
	cin >> n;
	cout << setprecision(20) << ans[n] << '\n';
	return 0;
}
