#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

const int N = 20;
char mat[N][N];

int d[N][N][4][N][N][4];

struct coisa{
    int i,j,k,l,d1,d2;
    coisa(){}
    coisa(int i,int j,int d1,int k,int l,int d2):
    i(i),j(j),k(k),l(l),d1(d1),d2(d2){}
};

int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
inline int mod(const int &x,const int& m){
    int ret = x%m;
    if(ret<0)ret+=m;
    return ret;
}
int n;
coisa turn(coisa C,int v){
    coisa d = C;
    if(C.i!=n-1 || C.j!=n-1)d.d1=mod(d.d1 + v,4);
    if(C.k!=n-1 || C.l!=n-1)d.d2=mod(d.d2 + v,4);
    return d;
}
inline bool bad(const int& x){
    return x<0 or x>=n;
}
coisa move(coisa C){
    
    coisa c = C;
    if(c.i!=n-1 or c.j!=n-1){
    c.i+=dx[c.d1];
    c.j+=dy[c.d1];
    if(bad(c.i) || bad(c.j) || mat[c.i][c.j] == 'H'){
        c.i = C.i;
        c.j = C.j;
    }

    }
    if(c.k!=n-1 or c.l!=n-1){
    c.k+=dx[c.d2];
    c.l+=dy[c.d2];
    if(bad(c.k) || bad(c.l) || mat[c.k][c.l]=='H'){
        c.k = C.k;
        c.l = C.l;
    }
    }
    return c;
}

inline void go(int di,coisa c,queue<coisa>&q){
    if(d[c.i][c.j][c.d1][c.k][c.l][c.d2] > di + 1){
        d[c.i][c.j][c.d1][c.k][c.l][c.d2] = di + 1;
        q.push(c);
    }
}

int32_t main(){
    
    ifstream cin("cownav.in");
    ofstream cout("cownav.out");
    
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n;

    rep(i,0,N)rep(j,0,N)rep(d1,0,4){
        rep(k,0,N)rep(l,0,N)rep(d2,0,4){
            d[i][j][d1][k][l][d2] = 1e9;
        }
    }

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            cin >> mat[i][j];
        }
    }

    queue<coisa> q;
    q.push(coisa(0,0,0,0,0,1));
    d[0][0][0][0][0][1] = 0;

    while(!q.empty()){
        coisa c = q.front();
        q.pop();
        int cur = d[c.i][c.j][c.d1][c.k][c.l][c.d2];
        if(c.i == n -1 and c.j == n-1 and c.k == n-1 and c.l == n-1){
            cout << cur << "\n";
            return 0;
        }
        coisa c1 = turn(c,-1);
        coisa c2 = turn(c,+1);
        coisa c3 = move(c);
        go(cur,c1,q);go(cur,c2,q);go(cur,c3,q);
  //     cout << c.i<<" "<<c.j<<" "<<c.d1<<" "<<c.k<<" "<<c.l<<" "<<c.d2 <<" == "<<cur<<endl;
    }

   // cout <<"KRL VELHO" <<endl;

}
