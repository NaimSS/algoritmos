// https://github.com/TimonKnigge/Competitive-Programming/blob/master/SPOJ/TREAP.cpp
const ll inf = 1e17;
struct node{
	ll val,mx,mn,mndif;
	node*l,*r;
	ll priority,cnt;
	node(ll x) : val(x),mx(x),mn(x),mndif(inf),cnt(1){
		priority = rand()%(1<<31) + 1;
		r = l = NULL;
	}
};
typedef node* pnode;
int cnt(pnode it){
	if(it==NULL)return 0;
		return it->cnt;
}


int mx(pnode it){
	if(it==NULL)return -inf;
		return it->mx;
}
int mn(pnode it){
	if(it==NULL)return inf;
		return it->mn;
}
int mndif(pnode it){
	if(it==NULL)return inf;
		return it->mndif;
}

void update(pnode t){
	if(!t)return;
	t->cnt = 1 + cnt(t->l) + cnt(t->r);
	//
	t->mx = max(mx(t->l),mx(t->r));
	t->mx = max(t->mx,t->val);
	//
	t->mn = min(mn(t->l),mn(t->r));
	t->mn = min(t->mn,t->val);
	//
	t->mndif = inf;
	if(t->l != NULL){
		t->mndif = min(t->mndif,min(t->val - mx(t->l),mndif(t->l)));
	}
	if(t->r != NULL){
		t->mndif = min(t->mndif,min(mn(t->r) - t->val,mndif(t->r)));
	}
	
}

void splitat(pnode t,pnode &l,pnode &r,ll at){
	if(!t){
		l = r = NULL;
		return;
	}
	int key = cnt(t->l);
	if(key > at){
		splitat(t->l,l,t->l,at);
		r = t;
	}else{
		splitat(t->r,t->r,r,at - 1 - key);
		l = t;
	}
	update(t);
}



void merge(pnode &t,pnode l,pnode r){
	if(l==NULL || r==NULL){
		if(l==NULL)t = r;
		else t =l;
	}else if(l->priority > r->priority){
		merge(l->r,l->r,r);
		t = l;
	}else{
		merge(r->l,l,r->l);
		t = r;
	}
	update(t);
}

ll queryMN(pnode t,int i,int j){
	pnode l,r;
	splitat(t,l,t,i-1);
	splitat(t,t,r,j-i);
	ll res = mndif(t);
	merge(t,l,t);
	merge(t,t,r);
	if(res<=0 || res>=1e15)return -1;
		return res;
}
ll queryMX(pnode t,int i,int j){
	pnode l,r;
	splitat(t,l,t,i-1);
	splitat(t,t,r,j-i);
	ll res = mx(t) - mn(t);
	merge(t,l,t);
	merge(t,t,r);
	if(res>=1e15 || res<=0)return -1;
	return res;
}

void split(pnode t,pnode &l,pnode &r,ll val){
	if(t==NULL){l=r=NULL;return;}
	if(t->val>=val){
		split(t->l,l,t->l,val);
		r = t;
	}else{
		split(t->r,t->r,r,val);
		l = t;
	}
	update(t);
}

void insert(pnode &t,ll val){
	pnode n = new node(val);
	node *l,*r;
	split(t,l,t,val);
	split(t,t,r,val+1);
	merge(t,l,n);
	merge(t,t,r);
}
void erase(pnode &t,ll val,bool del = true){
	pnode l,r;
	split(t,t,l,val);
	split(l,r,l,val+1);
	merge(t,t,l);
	if(del && r!=NULL)delete r;
}

void inorder(pnode t){
	if(t==NULL)return;
	inorder(t->l);
	cout<<t->val<<" ";
	inorder(t->r);
}
