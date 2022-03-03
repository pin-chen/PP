#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int graph[55][55];
int Med(int a, int b, int c, int d){
    int tmp[5] = {a, b, c, d};
    sort(tmp, tmp + 4);
    return (tmp[1] + tmp[2]) / 2 % 26;
}
int main(void){
    cin.tie(0);
    cin.sync_with_stdio(0);
    int row, col;
    cin >> row >> col;
    cin.ignore();
    for(int i = 0; i < row; i++){
        string tmp;
        getline(cin, tmp);
        for(int j = 0; j < col; j++){
            graph[i][j] = tmp[j] - 'A';
        }
    }
    long long cnt = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int med = Med(graph[i][j], graph[row - i - 1][j], graph[i][col - j - 1], graph[row - i - 1][col - j - 1]);
            //cout << "(" << i << ", " << j << "), (" << row - i << ", " << j << "), (" << i << ", " << col - j << "), (" << row - i <<", " << col - j <<") " << med << endl;
            cnt += min(abs(graph[i][j] - med), abs((graph[i][j] - med + 26) % 26));
            graph[i][j] = med;
            cnt += min(abs(graph[row - i-1][j] - med), abs((graph[row - i - 1][j] - med + 26) % 26));
            graph[row - i-1][j] = med;
            cnt += min(abs(graph[i][col - j-1] - med), abs((graph[i][col - j-1] - med + 26) % 26));
            graph[i][col - j-1] = med;
            cnt += min(abs(graph[row - i-1][col - j-1] - med), abs((graph[row - i-1][col - j-1] - med + 26) % 26));
            //cout << cnt << endl;
            graph[row - i-1][col - j-1] = med;
        }

    }
    cout << cnt << '\n';
    return 0;
}


