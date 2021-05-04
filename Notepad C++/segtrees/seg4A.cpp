#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

#define pb push_back
#define mp make_pair

template <typename T>
struct segtree {
	
	int size;
	vector<T> sums;
	const int DV = 0;
	
	T assoc(T a, T b){
		return a + b;
	}
	
	void init(int n){
		size = 1;
		while(size < n) size*=2;
		sums.assign(2*size, DV);
	}
	
	void init(vector<T> &a){
		init(a.size());
		build(a);
	}
	
	void build(vector<T> &a, int x, int lx, int rx){
		// if in bottom layer, check if within "actual" elems (not added 0s)
		if(rx-lx == 1){
			if(lx < a.size()){
				sums[x] = a[lx];
			}
			return;
		}
		int m = (lx + rx) / 2;
		build(a, 2*x + 1, lx, m);
		build(a, 2*x + 2, m, rx);
		
		sums[x] = assoc(sums[2*x+1], sums[2*x+2]);
	}
	
	void build(vector<T> &a){
		build(a, 0, 0, size);
	}
	
	void set(int i, T v){
		if(i < 0 || i >= size) return;
		set(i, v, 0, 0, size);
	}
	
	void set(int i, T v, int x, int lx, int rx){
		// if x is a leaf, set it directly
		if(rx-lx == 1){
			sums[x] = v;
			return;
		}
		
		int m = (lx+rx)/2;
		// i is in left
		if(i < m){
			// goto left node
			set(i, v, 2*x + 1, lx, m);
		}else{
			// goto right node
			set(i, v, 2*x + 2, m, rx);
		}
		
		// doesn't go o.o.b as x is not a leaf
		sums[x] = assoc(sums[2*x+1], sums[2*x+2]);
	}
	
	T sum(int l, int r){
		return sum(l, r, 0, 0, size);
	}
	
	T sum(int l, int r, int x, int lx, int rx){
		
		// segment is completely outside
		if(rx <= l || lx >= r) return DV;
		
		// segment is completely contained
		if(l <= lx && rx <= r) return sums[x];
		
		// segment is partially contained (recursive case)
		int m = (lx+rx)/2;
		
		return assoc(sum(l, r, 2*x + 1, lx, m), sum(l, r, 2*x + 2, m, rx));
	}
};

void solve() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for(int i = 0; i < n; i++)
		cin >> a[i];
	
	vector<int> evens(n);
	vector<int> odds(n);
	for(int i = 0; i < n; i++){
		if(i&1){
			odds[i] = a[i];
		}else{
			evens[i] = a[i];
		}
	}
	
	segtree<int> est;
	est.init(evens);
	segtree<int> ost;
	ost.init(odds);
	
	int m;
	cin >> m;
	
	for(int q = 0; q < m; q++){
		int o;
		cin >> o;
		if(o == 0){
			int i, j;
			cin >> i >> j;
			i--;
			
			if(i&1){
				ost.set(i, j);
			}else{
				est.set(i, j);
			}
		}else if(o == 1){
			int l, r;
			cin >> l >> r;
			l--;
			
			int ans;
			if(l&1){
				ans = ost.sum(l, r) - est.sum(l, r);
			}else{
				ans = est.sum(l, r) - ost.sum(l, r);
			}
			
			cout << ans << endl;
		}
	}
}

int main() {
	solve();
	return 0;
}