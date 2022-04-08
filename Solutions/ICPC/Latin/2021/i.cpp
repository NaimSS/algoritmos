#include <bits/stdc++.h>
using namespace std;

int delta[] = {30,30,30,32,31};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    string s;
    cin >> s;
    int n;
    cin >> n;
    int ini=-1;
    if(s=="Mon")ini=0;
    if(s=="Tue")ini=1;
    if(s=="Wed")ini=2;
    if(s=="Thu")ini=3;
    if(s=="Fri")ini=4;
    if(s=="Sat")ini=5;
    if(s=="Sun")ini = 6;
    assert(ini!=-1);
    int res = 1e9;
    int agr = (1000 * 1000 * 1000);
    agr = agr + 7 - (agr%7);
    agr+=ini;

    while(n--){
        int d;
        cin >> d;
        int antes = agr - d;
        antes+=delta[antes%7];

        while(antes < agr){
            assert((antes%7) < 5);
            if(agr - antes <= 100 || (antes%7!=0)){
                antes+=delta[antes%7];
            }else{
                int put = (agr - antes)/91 * 91;
                antes += put;
            }
        }
        res = min(res,antes - agr);
    }
    cout << res << "\n";
}
