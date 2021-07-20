// 0-index !!!!!!
const int inf_rand = 2e9;
struct node{
  int prior,cnt;
  int val;
  ll sum;
  bool rev;
  node* l,*r;

  node(int vv = 0){
    prior = rand()%(inf_rand);
    val = sum = vv;
    cnt = 1;
    rev=0;
    l = r = NULL;
  }
};
typedef node* pnode;
typedef node*& node_t;

int cnt(pnode it){
  return it ? it->cnt : 0;
}
ll sum(pnode it){
  return it ? it->sum : 0;
}
void upd(pnode it){
  if(!it)return;
  it->cnt = cnt(it->l) + cnt(it->r)  + 1;
  it->sum = sum(it->l) + sum(it->r) + it->val;
}

void unlazy(pnode it){
  if(!it)return;
  if(it->rev){
    it->rev = 0;
    swap(it->l,it->r);
    if(it->l)it->l->rev^=true;
    if(it->r)it->r->rev^=true;
  }
}

void split(pnode t,node_t l,node_t r,int pos,int add = 0){
  if(!t)return void(l = r = NULL);
  unlazy(t);
  int cur = add + cnt(t->l);
  if(cur>=pos)split(t->l,l,t->l,pos,add),r=t;
  else split(t->r,t->r,r,pos,cur+1),l = t;
  
  upd(t);
}
void merge(node_t t,pnode l,pnode r){
  unlazy(l);unlazy(r);
  if(!l || !r)t = (l ? l : r);
  else if(l->prior > r->prior)merge(l->r,l->r,r),t = l;
  else merge(r->l,l,r->l),t = r;

  upd(t);
}

void insert(node_t t,int pos,int val){
  pnode novo = new node(val);
  pnode t1=NULL,t2=NULL;

  unlazy(t);
  split(t,t1,t2,pos);
  merge(t1,t1,novo);
  merge(t,t1,t2);
  
  upd(t);
}

void erase(node_t t,int pos,int add = 0){
  unlazy(t);
  int cur = add + cnt(t->l);
  if(cur == pos)merge(t,t->l,t->r);
  else if(cur > pos)erase(t->l,pos,add);
  else erase(t->r,pos,cur + 1);

  upd(t);
}

void inorder(pnode t){
  if(!t)return;
  unlazy(t);
  inorder(t->l);
  cerr << t->val<<" ";
  inorder(t->r);
}

void reverse(node_t t,int l,int r){
  pnode t1,t2,t3;
  split(t,t1,t2,l);
  split(t2,t2,t3,r-l+1);


  t2->rev^=1;
  merge(t,t1,t2);
  merge(t,t,t3);
}


int find(node_t t,int l,int r){
  pnode t1,t2,t3;
  t1 = t2 = t2 = NULL;
  split(t,t1,t2,l);
  split(t2,t2,t3,r-l+1);

  int v = t2->sum;
  
  merge(t2,t2,t3);
  merge(t,t1,t2);
  return v;
}

void Rotate(pnode& t,int l,int r){
  // cyclic right shift
  int val = find(t,r,r);
  erase(t,r);
  insert(t,l,val);
}
