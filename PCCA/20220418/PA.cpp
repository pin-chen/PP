#include <bits/stdc++.h>
#define ll long long
#define fra pair<ll, ll>
#define fst first
#define sec second
using namespace std;

fra rec(fra f){
	return make_pair(f.sec, f.fst);
}

fra sol(ll x, fra f){//(a+b/c)
	fra new_f = make_pair(x * f.sec + f.fst, f.sec);
	return new_f;
}

fra yuefen(fra x){
	int z = abs(__gcd(x.fst, x.sec));
	if(x.fst * x.sec < 0)
		return {-abs(x.fst / z), abs(x.sec / z)};
	return {abs(x.fst / z), abs(x.sec / z)};
}

fra op1(fra a, fra b){//a*d+ b *c/b*d
	if(a.sec == b.sec){
		return yuefen({a.fst + b.fst, a.sec});
	}
	return yuefen({a.fst * b.sec + a.sec * b.fst, a.sec * b.sec});
}

fra op2(fra a, fra b){//a*d- b *c/b*d
	if(a.sec == b.sec){
		return yuefen({a.fst - b.fst, a.sec});
	}
	return yuefen(make_pair(a.fst * b.sec - a.sec * b.fst, a.sec * b.sec));
}

void print(fra x){
	// cout << x.fst << ", " << x.sec << ": ";
	if(x.fst < 0){
		cout << (x.fst - x.sec + 1) / x.sec << ' ';
		x.fst %= x.sec;
		x.fst += x.sec;
		x = {x.sec, x.fst % x.sec}; 
	} else if(x.fst == 0){
		cout << 0 << '\n';
		return;
	}
	while(x.sec != 0) {
		fra y = {x.sec, x.fst % x.sec};
		cout << (x.fst / x.sec) << ' ';
		x = y;
		// cout << x.fst << ", " << x.sec << ": ";
	}
	
	cout << '\n';
}


fra mult(fra x, fra y) {
	return yuefen({x.fst * y.fst, x.sec * y.sec});
}

fra div(fra x, fra y){
	return mult(x, {y.sec, y.fst});
}
int main(){
	int n1, n2;
	int cnt = 1;
//	print({1, 1});
//	print({1, 2});
//	print({2, 1});
//	print({0, 1});
//	print({0, 2});
	//print({-10, 2});
//	print({-6, 5});
//	
	//return 0;
	while(cin >> n1 >> n2 && (n1 != 0 && n2 != 0) ){
		cout << "Case " << cnt++ << ":\n";
		ll fr1[n1];
		ll fr2[n2];
		for(int i = 0; i < n1; i++){
			cin >> fr1[i];
		}
		for(int i = 0; i < n2; i++){
			cin >> fr2[i];
		}
		
		fra f1 = make_pair(1, fr1[n1 - 1]);
		fra f2 = make_pair(1, fr2[n2 - 1]);
		for(int i = n1 - 2; i >= 0; i--){
			f1 = sol(fr1[i], f1);
			f1 = rec(f1);
		}
		f1 = rec(f1);
		for(int i = n2 - 2; i >= 0; i--){
			f2 = sol(fr2[i], f2);
			f2 = rec(f2);
		}
		f2 = rec(f2);
		print(op1(f1,f2));
		print(op2(f1,f2));
		print(mult(f1,f2));
		print(div(f1,f2));
		//print({-1, 2});
		//cout << f1.fst << " " << f1.sec << '\n';
		//cout << f2.fst << " " << f2.sec << '\n';
		//print(f1);
		//print(f2);
		
	}
		
	return 0;
} 
