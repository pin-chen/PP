#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main(void){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--){
        long long int n;
        cin >> n;
        long long sum = 1;
        for(int i = 2; i <= sqrt(n); i++){
            if(n % i == 0){
                sum += i;
                sum += n / i;
                if(i * i == n){
                    sum -= i;
                }
            }
        }
        if(sum > n) cout << "abundant\n";
        else if(sum < n) cout << "deficient\n";
        else cout << "perfect\n";
    }
    
    return 0;
}
