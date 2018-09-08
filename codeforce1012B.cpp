/*
* codeforce 1012B(Round #500 Div.1 B) : 并查集
由(x1, y1) 可以建立x1===y1
插入(x1, y2)后可以建立x1===y1===y2
插入(x2, y1)后可以建立x1===y1===y2===x2
此时(x2, y2)已经建立。
故可以将纵坐标变化成n+1 -> n+m，然后使用上述方法解决。
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, m, q, x, y;

const int maxn = 1e6+7;
int fa[maxn];
inline int fin(int x){
	return fa[x] == x ? x : fa[x] = fin(fa[x]);
}
inline void unite(int x,int y){
	int xx = fin(x);
	int yy = fin(y);
	if (xx != yy) fa[xx] = yy;
}
inline void init(int n){
	for(int i = 1; i <= n;++i) fa[i] = i;
}

int main() {
	cin >> n >> m >> q;
	init(n + m);
	for (int i = 0; i < q; i++) {
		cin >> x >> y;
		unite(x, y + n);
	}
	int ans = 0;
	int root = fin(1);
	for (int i = 2; i <= n + m; i++) {
		if (fin(i) != root) {
			ans++;
			fa[fin(i)] = root;
		}
	}
	cout << ans << endl;
	return 0;
}
