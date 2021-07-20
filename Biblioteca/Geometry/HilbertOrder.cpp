// Source : codeforces : https://codeforces.com/blog/entry/61203?#comment-522213
 
 long long hilbertorder(int x, int y)
{
  long long d = 0;
  for (int s = 1 << (logn - 1); s; s >>= 1)
  {
    bool rx = x & s, ry = y & s;
    d = d << 2 | rx * 3 ^ static_cast<int>(ry);
    if (!ry)
    {
      if (rx)
      {
        x = maxn - x;
        y = maxn - y;
      }
      swap(x, y);
    }
  }
  return d;
}

 for(int i=0;i<n;i++){
    cin >> v[i].x>>v[i].y;
    v[i].id = i+1;
    val[v[i].id] = hilbertorder(v[i].x,v[i].y);
  }

  sort(v.begin(),v.end(),[&](P a,P b){
    return val[a.id] < val[b.id];
  });
