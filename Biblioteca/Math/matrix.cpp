// from viniciustht
struct matrix{
	int n,m;
	vector<vector<int>> mat;
	matrix(){}
	matrix(int l,int c){
		n = l;
		m = c;
		mat.resize(n, vector<int>(m));
	}
	void nsize(int l,int c){
		n = l;
		m = c;
		mat.resize(n, vector<int>(m));
	}
};
void print(matrix ma){
    for(int i=0;i<ma.n;i++){
      cout<<"[";
      for(int j=0;j<ma.m;j++){
        cout << ma.mat[i][j];
        if(j==ma.m-1)cout<<"]\n";
        else cout<<", ";
      }
    }
} 
matrix operator*(const matrix& A,const matrix& B){
    matrix ret(A.n,B.m);
    for(int i=0;i<A.n;i++)
        for(int j=0;j<B.m;j++)
            for(int k=0;k<A.m;k++){
                ret.mat[i][j] += (A.mat[i][k] * B.mat[k][j])%M;
                ret.mat[i][j]%=M;
            }
    return ret;
}
matrix def; // def = matriz Identidade
matrix expo(matrix a,int b){
    if(b==0) return def;
    if(b==1){
        return a;
    }
    matrix now = expo(a,b/2);
    if(b&1){
        return a*now*now;
    }
    else return now*now;
}
