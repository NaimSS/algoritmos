/* Count number of points in Left and Right of the Line
 * No Collinears and without including the line
 * Prefix sum if the Points have values is a good ideia
 * And maybe double the  vector to avoyd %n
 * https://codeforces.com/contest/1284/problem/E
 * https://codeforces.com/contest/1025/submission/77107206
 */
ll go(vector<P> pts){

  sort(all(pts) , [&](P a , P b){
    
    int hp1 = a < P(0,0),hp2 = b<P(0,0);

    if(hp1 != hp2) return hp1 < hp2;
    if(a.cross(b) != 0){
      return a.cross(b)  > 0;
    }
    return a.dist2() < b.dist2();
  });

  int n =pts.size();
  int j=0;
  ll ans = 0;
  rep(i,0,n){
      while(j < i + n and pts[i].cross(pts[j%n])>=0)j++;
      ll left = j-i-1;
      ans+= C(left,3);
  }

  return ans;

}

// Number of collinears
// Tested on Kattis:
int go(vector<P>& pts){
  sort(all(pts) , [&](P a , P b){
    int hp1 = a < P(0,0) , hp2 = b < P(0,0);
    if(hp1 != hp2) return hp1 < hp2;
    if(a.cross(b) != 0){
      return a.cross(b)  > 0;
    }
    return a.dist2() < b.dist2();
  });
  int n = sz(pts);
  auto nxt =[&](int j)->int{
    return (j == n-1 ? 0 : j + 1);
  };
  int res = 1;
  for(int i=0,k = 0;i<n;i++){
    if(i == k)k++;
    while(k < i + n and pts[i].cross(pts[k%n]) == 0)k++;
    res=max(res,1 + k - i );
  }
  return res;
}
