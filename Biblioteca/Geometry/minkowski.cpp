// CP ALGORITHMS
typedef Point<ll> P;


void reorder_polygon(vector<P> & p){
    size_t pos = 0;
    for(size_t i = 1; i < p.size(); i++){
        if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

vector<P> minkowski( vector<P> &A , vector<P> &B){
  reorder_polygon(A);
  reorder_polygon(B);
    A.push_back(A[0]);
    A.push_back(A[1]);
    B.push_back(B[0]);
    B.push_back(B[1]);
    // main part
    vector<P> result;
    size_t i = 0, j = 0;
    while(i < A.size() - 2 || j < B.size() - 2){
        result.push_back(A[i] + B[j]);
        auto cross = (A[i + 1] - A[i]).cross(B[j + 1] - B[j]);
        if(cross >= 0)
            ++i;
        if(cross <= 0)
            ++j;
    }
    return result;
}
