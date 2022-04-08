#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 1000; // suficiente?
const int M = 1e9 + 7;
ll exp(ll b,ll e,ll m){
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}
const int DB = 0;

ll fat[N],inv[N];
ll pwr2[N];
void precompute(){
    pwr2[0] = 1;
    for(int i=1;i<N;i++)pwr2[i] = pwr2[i-1] * 2ll %M;
    fat[0] = 1;
    for(int i=1;i<N;i++)fat[i] = 1ll * i * fat[i-1] % M;
    inv[N-1] = exp(fat[N-1],M-2,M);
    for(int i=N-2;i>=0;i--)inv[i] = 1ll * (i+1) * inv[i+1] % M;
}
ll C(int n,int k){
    if(k > n || n<0 || k<0)return 0;
    return fat[n] * (ll) inv[k] %M * inv[n-k] %M;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n,gg,ee,ii;
    cin >> n >> gg >> ii >> ee;
    precompute();
    gg = min(gg,2*n),ee=min(ee,2*n),ii=min(ii,2*n);
    ll tot=0;
    for(int dois = 0;dois <= n;dois++){
        int g = gg,i=ii,e=ee;
        // tem "dois" pares onde G pegou os dois;
        int um = g - 2 * dois;
        int vazio = n - dois - um;
        if(um < 0)continue; 
        if(n - dois < um)continue; // nao tem tanto lugar pra so 1
        // modos de pegar isso:
        ll modos = C(n,dois) * C((n-dois),um)%M * pwr2[um]%M;

        
        // felicidade do estado:
        ll fel = g;//g todos bem

        // colocar os E:
        int mn = min(um,e);
        um-=mn,e-=mn;
        fel += mn;
        if(DB)cout << dois <<" "<<modos <<" "<<mn<<endl;

        if(e > 0){
            // colocar mais E nos vazios agr:
            int consegue_dois = min(vazio,e/2);
            vazio -= consegue_dois;
            e-= consegue_dois * 2;
            fel += consegue_dois * 2;
        }
        if(fel == 2 * n){
            // ta tudo cheio já
            if(DB){
                cout<<"FINAL "<<modos<<" "<<fel<<" "<<dois << endl;
            }
            (tot += modos * fel%M)%=M;
            continue;
        }
        int bomUm = 0;
        if(e > 0){
            assert(e==1);// so tem eu de solo
            assert(vazio > 0);
            e--;
            bomUm = 1; // se alguem sentar comigo sobe em 1
            assert(um == 0);
            vazio--;
        }

        // colocar os i's
        mn = min(vazio,i);
        i-=mn,vazio-=mn;
        if(DB)cout << vazio<<" "<<mn<<" "<<i<<endl;
        fel+=mn;
        int badUm = mn;

        if(i > 0){
            // ainda tem que colocar :(
            // coloca primeiro no bomUm
            mn = min(bomUm,i);
            i-=mn,bomUm-=mn,fel+=mn;
            if(DB)cout <<"BomUm "<<mn<<endl;
            //coloca no um normal == g sozinho
            mn = min(um,i); 
            i-=mn,um-=i;


            if(DB)cout <<"Normal "<<mn<<endl;
            //coloca no badUm == i sozinho
            mn = min(badUm,i);
            i-=mn,badUm-=mn,fel-=mn;

            if(DB)cout<<"Bad "<<mn<<endl;
        }
        // final!
        if(DB)cout<<"FINAL: "<<modos<<" "<<fel<<endl;
        (tot += modos * fel %M)%=M;
    }
    // achar e dividir pelos modos de conseguir:
    tot = tot*exp(C(2*n,gg),M-2,M)%M;
    tot%=M;
    if(tot<0)tot+=M;
    cout << tot << endl;
}
