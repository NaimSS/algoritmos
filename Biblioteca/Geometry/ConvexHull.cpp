 
struct Point{
  int x,y;
  int id;
  Point(){}
  Point(int _x,int _y,int _id){
	  x = _x;
	  y = _y;
	  id = _id;
  }	
  Point operator-(Point& a){
	  return Point(x - a.x,y-a.y,id);
  }
  Point operator+(Point& b){
	  return Point(x + b.x,y+b.y,id);
  }
  
 
  
  
  
   bool operator<(const Point &a) const{
	  return (this->x < a.x || (this->x == a.x && this->y < a.y));
  }
  
};
 
struct Convex_Hull{
	vector<Point> Hull;
	int N;
	
       int sign(int x){
		  if(x<0)return -1;
		  if(x==0)return 0;
		  return 1;
      }
      int cross(Point a,Point b){
		  return a.x*b.y - a.y*b.x; // A x B == ^n |A||B| sen(o)
	  }
	  int dot(Point a,Point b){
		  return a.x*b.x + a.y*b.y; // A.B == |A||B| cos(o) 
	  }
	  int CCW(Point O,Point A,Point B){
		  return sign(cross(A-O,B-O));
	  }
	  double dist(Point A,Point B){
		  return sqrt((A.x-B.x)*(A.x-B.x) + (A.y - B.y)*(A.y-B.y));
	  }
	
	vector<Point> init(vector<Point> P){
		int n = P.size();
		sort(P.begin(),P.end());
		vector<Point> H(2*n);
		int k=0;
		//build Lower
		for(int i=0;i<n;i++){
			while(k>=2 && CCW(H[k-2],H[k-1],P[i])<=0)k--;
			H[k++] = P[i];
		}
		//build Upper
		for(int i=n-2,t=k+1;i>=0;i--){
			while(k>=t && CCW(H[k-2],H[k-1],P[i])<=0)k--;
			H[k++] = P[i];
		}
		H.resize(k-1);
		return H;
	}
	
	void iniciar(vector<Point> P){
		Hull = init(P);
		N = Hull.size();
	}
	
	double peri(){
		
		double r=0;
		for(int i=0;i<N;i++){
			r+=dist(Hull[i],Hull[(i+1)%N]);
		}
		
		return r;
	}
	
	double area(){
		int r=0;
		
		for(int i=1;i<N;i++){
			r+=cross(Hull[(i+1)%N] - Hull[0],Hull[i] - Hull[0]);
		}
		return abs(r);
	}
	
};
