#include "tickets.h"
#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
const int N = 1550;
int L[N],R[N];
int ptL[N],ptR[N];

long long find_maximum(int k, std::vector<std::vector<int>> x) {
	int n = x.size();
	int m = x[0].size();
	std::vector<std::vector<int>> ans(n,vector<int>(m,-1));
	long long sum=0;
	vector<pii> vals;
	for(int i=0;i<n;i++){
		ptL[i]=0,ptR[i] = m-1;
		L[i] = 0;
		R[i] = k;
		for(int j=0;j<k;j++){
			vals.push_back(pii(x[i][j] + x[i][m-k+j],i));
		}
	}
	sort(vals.begin(),vals.end());
	for(int i=0;i<n*k/2;i++){
		auto it = vals[i];
		L[it.second]++;
		R[it.second]--;
	}
	for(int r=0;r<k;r++){
		vector<pii> pos;
		vector<int> vis(n);
		for(int i=0;i<n;i++){
			if((pos.size()) == n/2)break;
			if(R[i] > 0){
				vis[i] = 1;
				pos.push_back(pii(0,i));
			}	
		}
		for(int i=0;i<n;i++)if(!vis[i])pos.push_back(pii(0,i));
		for(int i=0;i<n;i++){
			int id = pos[i].second;
			if(i < n/2){
				// R:
				R[id]--;
				sum += x[id][ptR[id]];
				ans[id][ptR[id]--] = r;
			}else{
				L[id]--;
				sum -= x[id][ptL[id]];
				ans[id][ptL[id]++] = r;
			}
		}

	}
	allocate_tickets(ans);
	return sum;
}
