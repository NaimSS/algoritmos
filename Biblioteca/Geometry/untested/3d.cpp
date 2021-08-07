// not tested... from https://vlecomte.github.io/cp-geo.pdf

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct p3{
  typedef p3 P;
  T x,y,z;
  explicit p3(T x=0, T y=0,T z=0) : x(x), y(y),z(z) {}
  P operator+(P p) const { return P(x+p.x, y+p.y,z+p.z); }
  P operator-(P p) const { return P(x-p.x, y-p.y,z-p.z); }
  P operator*(T d) const { return P(x*d, y*d,z*d); }
  P operator/(T d) const { return P(x/d, y/d,z/d); }

  bool operator==(p3 p){return tie(x,y,z)==tie(p.x,p.y,p.z);}
  bool operator!=(p3 p){return !operator==(p);}

  T operator|(P p){//dot product
    return x * p.x + y * p.y + z * p.z;
  }
  P operator*(P p){// cross product
    return
      P(y * p.z - z * p.y , 
        z * p.x - x * p.z ,
        x * p.y - y * p.x 
      );
  }
  T sq(P p){return p|p;} // or dist2
  double abs(P p){return sqrt(sq(p));} // or dist
  P unit(P p){return p/abs(p);}

  double angle(P p){
    double co = (*this|p)/abs(*this)/abs(p);
    return acos(max(-1.0,min(1.0,co)));
  }

  T orient(P p,P q,P r, P s){ 
    // positive -> above plane PQR, 0 on plane, negative -> beow PQR
    // se orient !=0 PQ e RS sao reversas
    return (q-p)*(r-p)|(s-p); // mixed product
  }

};

template<class T>
struct plane{
  typedef p3<T> P;
  P n;T d;
  // ax + by + cz = d -> n|P = d
  // From normal n and offset d
  plane(P n,T d):n(n),d(d){}
  // From normal and point P
  plane(P n,P p):n(n),d(n|p){}
  // From three non-collinear points 
  plane(P p,P q,P r):plane((q-p)*(r-p),p){}

  // lado do plano que ta: positive -> above, zero -> on plane
  T side(P p){return (n|p) - d;} 

  double dist(P p){
    return abs(side(p))/abs(n);
  }
  plane translate(P t){//translate by a vector t
    return {n,d + (n|t)};
  }
  plane shiftUp(double dist){
    return {n,d + dist  * abs(n)};
  }
  // projection reflection
  P proj(P p){
    return p - n*side(p)/sq(n);
  }
  P refl(P p){
    return p - n*2*side(p)/sq(n);
  }
};


template<class T>
struct line3d{
  typedef p3<T> P;
  P o,d; // origem, direcao
  line3d(P p,P q):d(q-p),o(p){}

  line3d(plane<T> p1,plane<T> p2){
    d = p1.n*p2.n;
    o = (p2.n * p1.d - p1.n * p2.d)*d/sq(d);
  }
  double sqDist(P p){
    return sq(d*(p-o))/sq(d);
  }
  double dist(P p){
    return sqrt(sqDist(p));
  }
  bool cmpProj(P p,P q){
    return (d|p) < (d|q); // sort along the line
  }
  P proj(P p){
    return o + d*(d|(p-o))/sq(d);
  }
  P refl(P p){
    return proj(p)*2 - p;
  }
  P inter(plane<T> p){
    return o - d*p.side(o)/(p.n|d);
  }

  double dist(line3d l1,line3d l2){
    P n = l1.d*l2.d;
    if(n==P(0,0,0))//parallel
      return l1.dist(l2.o);
    return abs((l2.o - l1.o)|n)/abs(n);
  }
  P closestOnL1(line3d l1,line3d l2){
    P n2 = l2.d *(l1.d*l2.d);
    return l1.o + l1.d*((l2.o-l1.o)|n2)/(l1.d|n2);
  }

};
