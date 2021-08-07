/*
 * Bunch of line things
 * Status: Not tested
 * Source: https://vlecomte.github.io/cp-geo.pdf
 */
template<class T>
struct line{
  P v;
  T c;
  // Line(t) = v*t + C 
  line( P v,T c) : v(v),c(c){}
  // From equation ax + by = c !!!! NOT AX + BY + C = 0 !!!
  line(T a,T b, T c) : v(P(b,-a)), c(c) {}
  // From two points
  line(P p, P q) : v(q-p),c(v.cross(p)) {};
  
  /* Normalize the line (for map and shit):
    //
    void norm(){
    assert(v.x!=0 or v.y!=0);
    ll g = gcd(v.x,v.y);

    v.x/=g;v.y/=g;
    if(v.x<0)v.x*=-1,v.y*=-1;
  }
  Line(P p,P q){
      v = (q-p);
      norm();
      // do this only after normalizing!
      c = (v.cross(p));
  }
  //
  */

  T side(P p){
    return v.cross(p) - c;
    // 0 if in line, >0 if at left, <0 if left (depending on orientation of v)
  }
  double dist(P p){return abs(side(p))/v.dist();}

  double dist2(P p){return side(p)*side(p)/(double)v.dist2();}

  // linha perpendicular passando por p
  line perpThrough(P p){return {p,p + v.perp()};}

  // sort points in the line:
  bool cmpProj(P p,P q){
    return v.dot(p) < v.dot(q);
  }

  // translate by a vector t:
  // side(P) = v*P -c = 0, side(P + t) = v*(P+t) - c' =0;
  // c' = v*(P+t) = v*P + v*t = c + v*t
  line translate(P t){return {v,c + v.cross(t)};}

  line shiftLeft(double dist){return {v,c + dist*v.dist()};}

  bool inter(line l1,line l2,P& out){
    auto d = l1.v.cross(l2.v);
    if(d==0)return false;
    out = (double)(l2.v*l1.c - l1.v*l2.c)/d;
    return true;
  }
  // project p in the line
  P proj(P p){return p - v.perp()*side(p)/v.dist();}

  P refl(P p){return p - v.perp()*2*side(p)/v.dist();}

  // interior -> entre os dois, exterior -> outside
  // from fact that bisector is at equal distance from both lines
  line bisector(line l1,line l2,bool interior=0){
    assert(l1.v.cross(l2.v)!=0);
    double sign = interior ? 1 : -1;
    return {l2.v.unit() + l1.v.unit()*sign,l2.c/l2.v.dist() + l1.c/l1.v.dist() * sign};
  }

  bool onSegment(P a,P b,P p){
    return a.cross(b,p)==0 and (a-p).dot(b-p)<=0;
  }

};
