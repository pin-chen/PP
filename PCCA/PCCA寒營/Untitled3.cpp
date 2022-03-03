#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <set>
using namespace std;
using pii = pair<int, int>;
using pdd = pair<double, double>;
using ll = long long;
int main(void){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int t;
    ll k;
    cin >> t;
    pii a, p;
    pdd A, P;
    while (t--){
        cin >> a.first >> a.second;
        cin >> p.first >> p.second;
        cin >> k;
        double K = (double)k;
        A.first = (double)a.first, A.second = (double)a.second;
        P.first = (double)p.first, P.second = (double)p.second;
        double d = pow(A.first - P.first, 2) + pow(A.second - P.second, 2);
        //cout << d - pow(2*k, 2) << endl;
        if(d - pow(2*k, 2) > 0.000000001) cout << 0 << '\n'; // d > 2k
        else if(((A.first + P.first) / 2 == (a.first + p.first) / 2 && (A.second + P.second) / 2 == (a.second + p.second) / 2 )&& d - pow(2*k, 2) < 0.000000001 && (d - pow(2*k, 2) >= 0.0)) cout << 1 << '\n';
        else {
            
            double tan1 = (P.second - A.second) / (P.first - A.first);
            double tan2 = sqrt(K*K - (d/2)*(d/2)) / (d/2);
            double mx = (A.first + P.first) / 2, my = (A.second + P.second) / 2;
            double x = (tan1*A.first - tan1*mx + my + tan2*A.first - A.second) / tan2;
            if(x - (int)x < 0.000000001) cout << 0 << '\n';
            else{
                double y = tan1*(x - mx) + my;
                if(x - (int)x < 0.000000001 && y - (int)y < 0.000000001) cout << 1 << '\n';
            }
        }
    }
    
    return 0;
}
