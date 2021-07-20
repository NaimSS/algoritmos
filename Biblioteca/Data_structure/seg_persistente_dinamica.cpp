// tested on https://codeforces.com/contest/916/problem/D

struct node{
  node *l,*r;
  int sum;
  node(int v = 0){
    l = r = NULL;
    sum = v;
  }
};
typedef node* pnode;

const int N = 200100;

//pnode prio[N],value[N];//prio-> pras querys,value-> qtd de caras

int sum(pnode no){
  return !no ? 0 : no->sum;
}
void upd(pnode no,pnode old,int i,int j,int p,int v,bool replace){ // replace if replace the current value
// remember that no!=NULL when calling this function

  if(old == NULL) old = new node();
  
  if(i == j){
  
    if(!replace)no->sum = old->sum + v;
    else no->sum = v;
    return;
  }
  int mid = (i+j)>>1;
  if(p<=mid){
    no->r = old->r;
    if(no->l == NULL)no->l = new node();
    upd(no->l,old->l,i,mid,p,v,replace);
  }else{

    no->l = old->l;
    if(no->r == NULL)no->r = new node();
    upd(no->r,old->r,mid+1,j,p,v,replace);
  }

  no->sum = sum(no->l) + sum(no->r);
}

int query(pnode no,int i,int j,int a,int b){
  if(i > j or i > b or j < a or a>b or no == NULL)return 0;
  if(a<=i and j<=b)return no->sum;
  int mid = (i+j)>>1;
  return query(no->l,i,mid,a,b) + query(no->r,mid+1,j,a,b);
}
