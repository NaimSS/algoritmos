/** Usage:
 * persist() to save state. roolback() to go to last persisted 
 * state.
 */

struct event{
  int a,b,pa,sza,ans;
  event(){}
  event(int a,int b,int pa,int sza,int ans):
  a(a),b(b),pa(pa),sza(sza),ans(ans){}
 
};
 
struct DSU{
  vi p,ps;
  stack<event> st;
  int ans;
  DSU(int n){
    p.resize(n + 1);
    ps.resize(n + 1);
    for(int i=1;i<=n;i++){
      p[i] = i,ps[i]=1;
    }
    ans = n;
  }
 
  void foto(int a,int b){
    st.push(event(a,b,p[a],ps[a],ans));
  }
  void persist(){
    st.push(event(-1,-1,-1,-1,-1));
  }
  int f(int x){
    while(p[x]!=x)x=p[x];
	return x;
  }
  bool join(int a,int b){
    a = f(a),b = f(b);
    if(ps[a] > ps[b])swap(a,b);
    foto(a,b);
    if(a!=b){
      ps[b]+=ps[a];
      p[a] = b;
	  ans--;
	  return 1;
    }
	return 0;
  }
  void rollback(){
    while(true){
      assert(!st.empty());
      event t = st.top();
      st.pop();
      if(t.pa == -1)break;
      ps[t.b] -= t.sza;
      ps[t.a] = t.sza;
      p[t.a] = t.pa;
      ans = t.ans;
    }
  }
 
};
