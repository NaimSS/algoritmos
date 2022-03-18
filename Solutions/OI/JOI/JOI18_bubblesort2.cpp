#include "bubblesort2.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define ff first
#define ss second
const int MAXN = 1e6 + 100;
int tree[4*MAXN];
int lazy[4*MAXN];
int n;
// answer is max(i - a_i) where a_i would be the value if the numbers
// were in range [0,n)

const int inf = 1e9;

void propagate(int no,int i,int j){
	if(lazy[no]==0)return;
	tree[no]+=lazy[no];
	if(i!=j){
		lazy[2*no]+=lazy[no];
		lazy[2*no+1]+=lazy[no];
	}
	lazy[no] = 0;
}

void update(int no,int i,int j,int a,int b,int v){
	if(a > b)return;
	propagate(no,i,j);
	if(i>b || j<a || i>j)return;
	if(a<=i && j<=b){
		tree[no] += v;
		if(i!=j){
			lazy[2*no]+=v;
			lazy[2*no+1]+=v;
		}
		return;
	}
	int m = (i+j)/2;
	int l = 2*no,r=2*no+1;
	update(l,i,m,a,b,v);
	update(r,m+1,j,a,b,v);	
	tree[no] = max(tree[l],tree[r]);
}

int query(int no,int i,int j,int a,int b){
	if(i>b || j<a || i>j)return -inf;
	
	propagate(no,i,j);
	
	if(a<=i && j<=b)return tree[no];
	
	int m = (i+j)/2;
	int l = 2*no,r=2*no+1;
	
	return max(query(l,i,m,a,b),query(r,m+1,j,a,b));
}

std::vector<int> countScans(std::vector<int> A,std::vector<int> X,std::vector<int> V){
	int Q=X.size();
	std::vector<int> answer(Q);
	vector<pii> vec;
	int n = A.size();
	for(int i=0;i<n;i++){
		vec.push_back(pii(A[i],i));
	}
	for(int i=0;i<Q;i++){
		vec.push_back(pii(V[i],X[i]));
	}
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	int tam = vec.size();
	auto Pos = [&](int id){
		return (lower_bound(vec.begin(),vec.end(),pii(A[id],id)) - vec.begin()) + 1;
	};
	for(int i=0;i<n;i++){
		int pos = Pos(i);
		update(1,1,tam,pos,pos,i);
		update(1,1,tam,pos+1,tam,-1);
	}
	for (int j=0;j<Q;j++) {
		int pos = Pos(X[j]);
		update(1,1,tam,pos,pos,-X[j]);
		update(1,1,tam,pos+1,tam,+1);
		A[X[j]] = V[j];
		pos = Pos(X[j]);
		update(1,1,tam,pos,pos,+X[j]);
		update(1,1,tam,pos+1,tam,-1);
		answer[j] = query(1,1,tam,1,tam);
	}
	return answer;
}
