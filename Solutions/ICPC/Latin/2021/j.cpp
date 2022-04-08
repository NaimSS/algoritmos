#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
#define mt make_tuple
typedef tuple<int,int,int,int> tp;
typedef pair<int,int> pii;

int n,m;
int bom(int x,int y){
    return x==0 || x==n || y==0 || y==m;
}
int quad(pii a){
    if(a.ff == 0)return 0;
    if(a.ss == m)return 1;
    if(a.ff == n)return 2;
    return 3;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m;
    int k;
    cin >> k;
    vector<tp> v;
    vector<pii> pt;
    for(int i=0;i<k;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(bom(a,b) && bom(c,d)){
            v.push_back(mt(a,b,c,d));
            pt.push_back(pii(a,b));
            pt.push_back(pii(c,d));
        }
    }
    sort(pt.begin(),pt.end(),[&](pii a,pii b){
        if(quad(a) != quad(b))
            return quad(a) < quad(b);
        if(a.ff == b.ff){
            if(a.ff == 0)return a.ss < b.ss;
            return a.ss > b.ss;
        }
        if(a.ss == m){
            return a.ff < b.ff;
        }
        return a.ff > b.ff;
    });
    map<pii,int> pos;
    int cnt=0;
    for(auto it : pt){
        pos[it] = cnt++;
    }
    vector<pii> ev;
    for(auto [a,b,c,d] : v){
        int l = pos[pii(a,b)];
        int r = pos[pii(c,d)];
        
        if(l > r)
            swap(l,r);
        ev.push_back(pii(l,r));
        ev.push_back(pii(r,-1));
    }

    sort(ev.begin(),ev.end());
    multiset<int> Rs;
    for(auto it : ev){
        if(it.ss == -1){
            Rs.erase(Rs.find(it.ff));
        }else{
            Rs.insert(it.ss);
            if(!Rs.empty() && *Rs.begin() < it.ss){
                cout << "N\n";
                return 0;
            }
        }
    }
    cout<<"Y\n";
}
