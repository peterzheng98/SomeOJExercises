/*
* codeforce 1040A : 贪心裸题
* Status: AC(53/53)
* Time: Sep 8, 2018
*/

#include<iostream>
using namespace std;
const int maxn = 20 + 7;
int n, a, b;
int sum = 0;
int seq[maxn];
int main(){
  cin >> n;
  cin >> a >> b;
  int minAB = (a > b ? b : a);
  for(int i = 0;i < n; ++i) cin >> seq[i];
  if(n % 2 == 1) sum += (seq[(n-1)/2] == 2 ? minAB : 0);
  for(int i = 0,j = n - 1; i < j; ++i, --j){
    if(seq[i] == seq[j] && seq[i] == 2) {
        sum += (minAB * 2);
        continue;
    }
    if(seq[i] == seq[j] && seq[i] != 2) continue;
    if(seq[i] == 2) {
        sum += (seq[j] == 0 ? a : b);
        continue;
    }
    if(seq[j] == 2) {
        sum += (seq[i] == 0 ? a : b);
        continue;
    }
    if(seq[i] != seq[j] && seq[i] != 2 && seq[j] != 2){
      cout << -1;
      exit(0);
    }
  }
  cout << sum;
  return 0;
}
