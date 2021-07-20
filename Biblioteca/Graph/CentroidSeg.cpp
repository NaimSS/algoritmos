// pinta um nó / achar o nó pintado mais distante

struct node{
  int x;
  node operator+(const node &rhs) const{  // exemplo de operador de merge
    node r;
    r.x = max(x,rhs.x);
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(){}

  ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
  void upd(int pos, T val){ // pos 0index
    for(st[pos += n] = val ; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};
#define F first
#define S second
const int inf = 1e9;
template <class T = int>
class Centroid{
public:
  vector<vector<T> > dist;
  vector<vi> pos;
  vector<vi> tree;
  vi pai;
  vi level;
  vector<vi> in; // problem G Dhaka
  vector< ST<node> > op;
  int n;
  vi vis;
  vector<pii> Range;
  Centroid(int n , int LGMAX = 20){
    this->n = n;
    g = vector< vector<pair< int, T> > >(n+1, vector<pair<int, T>>());
    dist = pos = vector< vector<T> > (n+1 , vector<T>(LGMAX , numeric_limits<T>::max()));
    tree = vector<vi> (n+1 , vi());
    vis = level = del = sz = pai = vi(n+1);
    in = vector<vi>(n+1, vi());
    op = vector< ST<node> >(n+1 , ST<node>());
    Range = vector<pii>(n+1);
  }

  void dfstree(int root,int p = -1){
    pos[root][level[root]] = 0;
    in[root].pb(root);
    for(int to : tree[root])if(to!=p){
      dfstree(to,root);
      Range[to].ff = sz(in[root]);
      for(int x : in[to]){
        pos[x][level[root]] = sz(in[root]);
        in[root].pb(x);
      }
      Range[to].ss = sz(in[root]) - 1;
    }

    op[root] = ST<node>(sz(in[root]),{-inf});

  }

  void initq(int root){
    dfstree(root);
  }
  void insert(int x){
    int u = x;
    while(u!=-1){
      op[u].upd(pos[x][level[u]],{dist[x][level[u]]});
      u = pai[u];
    }
  }
  int query(int c){
    int res=0;
    int u = c;
    pii block = pii(0,0);
    while(u != -1){
      int a = dist[c][level[u]];
      if(0<=block.ff - 1){
        node g = op[u].query(0,block.ff-1);
        res = max(res,a + g.x);
      }
      if(block.ss + 1 < sz(in[u])){
        node g = op[u].query(block.ss + 1,sz(in[u])-1);
        res = max(res,a + g.x);  
      }

      block = Range[u];
      u = pai[u];
    }
    return res;
  }
  int calc_sz(int v,int p=-1){
    sz[v] = 1;
    vis[v] = 1;
    for(auto to : g[v])if(to.F!=p and !del[to.F]){
      sz[v]+=calc_sz(to.F,v);
    }
    return sz[v];
  }
  int find_centroid(int v,int p,int tam){
    for(auto to : g[v])if(to.F!=p and !del[to.F]){
      if(sz[to.F]*2>tam)return find_centroid(to.F,v,tam);
    }
    return v;
  }
  void dfs(int v,int root,int lv = 0, int p=-1,T d = 0){
    dist[v][lv] = d;
   // in[root].push_back(v);
    for(auto w : g[v]) if(w.first != p && !del[w.first]){
      dfs(w.first,root,lv,v,d+w.second);
    }
  }
  int decompose(int v , int p = -1 , int lv = 0){
    int tam = calc_sz(v);
    int cent = find_centroid(v,-1,tam); 
    dfs(cent, cent, lv); // answer querys if needed
    del[cent] = 1;
    if(p != -1){
      tree[cent].push_back(p);
      tree[p].push_back(cent);
    }
    pai[cent] = p;
    level[cent] = lv;
    for(auto to : g[cent]){
      if(del[to.F])continue;
      decompose(to.F,cent,lv+1);
    }
    return cent;
  } 
  void add_edge(int x , int y , T z){
    g[x].push_back({y,z});
    g[y].push_back({x,z});
  }

  void build(){
    for(int i=1;i<=n;i++){
      if(!vis[i]){
         int root = decompose(i);
         initq(root);
      }
    }
  }
private:
  vector<vector<pair<int, T>> > g;
  vi del, sz;
};
