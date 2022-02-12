#include <iostream>
using namespace std;
int main(){
	int n, k;
	cin >> n >> k;
	int arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	int Max = 0;
	int stillwork = 0;
	for(int i = 0; i < n; i++){
		int j;
		for(j = stillwork; j < i; j++){
			if(arr[j] > arr[i] - 1000) break;
		}
		stillwork = j;
		Max = max(Max, i - stillwork + 1);
	}
	int ans = Max / k + (Max % k ? 1 : 0);
	cout << ans << '\n';
	return 0;
} 
