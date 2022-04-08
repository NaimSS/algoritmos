// by yan.silva
#include <bits/stdc++.h>

using namespace std;
typedef long long int lli;

const int MAXN = 500;

struct Point
{
    lli x, y;
    int index;
    bool isCopy;

    Point(lli x = 0, lli y = 0, int i = 0, bool copy = false) 
        : x(x), y(y), index(i), isCopy(copy) {}

    lli operator * (Point a) { return x*a.y - y*a.x; }
    lli operator % (Point a) { return x*a.x + y*a.y; }

    Point operator - (Point a) { return Point( x - a.x , y - a.y , index , isCopy ); } 
    Point operator + (Point a) { return Point( x + a.x , y + a.y , index , isCopy ); } 

    int region()
    {
        if( y > 0 || (y == 0 && x > 0) )
            return 0;

        return 1;
    }

    bool operator < (Point a) const
    {
        Point t = *this;

        if( t.region() != a.region() )
            return t.region() < a.region();

        return t*a > 0;
    }

    bool operator == (Point& a) { return (x == a.x && y == a.y); }

    void print()
    {
        printf("(%lld,%lld)\n",x,y);
    }
};

class FenwickTree
{
    public:

        void update(int i, int x)
        {
            sumAll += x;

            for(i++ ; i <= n ; i += i & -i)
                BIT[i] += x;
        }

        int query(int i)
        {
            int ans = 0;

            for(i++ ; i > 0 ; i -= i & -i)
                ans += BIT[i];

            return ans;
        }

        void clear()
        {
            sumAll = 0;
            
            for(int i = 1 ; i <= n ; i++)
                BIT[i] = 0;
        }

        void init(int N) { n = N; }

        int query(int L, int R)
        {
            if( L <= R )
                return query(R) - query(L - 1);

            return sumAll - query(L - 1) + query(R);
        }

    protected:

        int n, sumAll;
        int BIT[2*MAXN];
};

int n;

int idReal[MAXN][MAXN];
int idCopy[MAXN][MAXN];

lli S;

Point v[MAXN];

vector<Point> radialSweep[MAXN];

FenwickTree BIT[2];

void sortByDistance(Point A, Point B, vector<Point>& points)
{
    vector< pair<lli,Point> > cur;

    for(int i = 0 ; i < (int)points.size() ; i++)
        cur.push_back( { abs((B - A) * (points[i] - A)) , points[i] } );

    sort( cur.begin() , cur.end() );

    for(int i = 0 ; i < (int)points.size() ; i++)
        points[i] = cur[i].second;
}

void dividePoints(Point A, Point B, vector<Point>& leftSide, vector<Point>& rightSide)
{
    for(int i = 1 ; i <= n ; i++)
    {
        if( v[i] == A || v[i] == B )
            continue;
        
        if( (B - A)*(v[i] - A) > 0 )
            leftSide.push_back( v[i] );
        else
            rightSide.push_back( v[i] );
    }
}

vector<Point> makeRadialSweep(int idOrigin, Point origin)
{
    vector<Point> newPoints;

    // printf("idOrigin = %d\n",idOrigin);

    for(int i = 1 ; i <= n ; i++)
    {
        if( origin == v[i] )
            continue;

        newPoints.push_back( v[i] - origin );
        newPoints.push_back( origin - v[i] );

        newPoints.back().index = i;
        newPoints.back().isCopy = true;
    }

    sort( newPoints.begin() , newPoints.end() );

    for(int i = 0 ; i < (int)newPoints.size() ; i++)
    {
        newPoints[i] = newPoints[i] + origin;

        if( !newPoints[i].isCopy )
            idReal[idOrigin][ newPoints[i].index ] = i;
        else
            idCopy[idOrigin][ newPoints[i].index ] = i;
    }

    return newPoints;
}

int countConcave(int idOrigin, int idEndpoint, int idPoint)
{
    int answerOrigin = BIT[0].query( idCopy[idOrigin][idPoint] , idCopy[idOrigin][idEndpoint] );
    int answerEndpoint = BIT[1].query( idCopy[idEndpoint][idOrigin] , idCopy[idEndpoint][idPoint] );

    // printf("answer origin = %d endpoint = %d\n",answerOrigin,answerEndpoint);
    // printf("fazendo query [%d,%d] na origin\n",idCopy[idOrigin][idPoint] , idCopy[idOrigin][idEndpoint]);
    // printf("fazendo query [%d,%d] no endpoint\n", idCopy[idEndpoint][idOrigin] , idCopy[idEndpoint][idPoint]);

    return answerOrigin + answerEndpoint;
}

lli getArea(Point a, Point b, Point c, Point d)
{
    lli area = abs((b - a)*(c - a)) + abs((d - a)*(c - a));
    return area;
}

int main()
{
    scanf("%lld %d",&S,&n); S *= 2;

    BIT[0].init( 2*n );
    BIT[1].init( 2*n );

    for(int i = 1 ; i <= n ; i++)
    {
        int x, y;
        scanf("%d %d",&x,&y);

        v[i] = Point( x , y , i );
    }

    for(int i = 1 ; i <= n ; i++)
        radialSweep[i] = makeRadialSweep( i , v[i] );

    lli cntConvex = 0, cntConcave = 0;

    for(int a = 1 ; a <= n ; a++)
    {
        for(int b = a + 1 ; b <= n ; b++)
        {
            BIT[0].clear();
            BIT[1].clear();

            Point A = v[a], B = v[b];

            // printf("\n---------------- Diagonal %d %d\n",a,b);

            vector<Point> leftSide;
            vector<Point> rightSide;

            dividePoints( A , B , leftSide , rightSide );

            sortByDistance( A , B , leftSide );
            sortByDistance( A , B , rightSide );

            // printf("Left Side:\n");

            // for(int i = 0 ; i < (int)leftSide.size() ; i++)
            //     leftSide[i].print();

            // printf("\nRight Side:\n");

            // for(int i = 0 ; i < (int)rightSide.size() ; i++)
            //     rightSide[i].print();

            // printf("\n");

            int pLeft = (int)leftSide.size() - 1;
            // pLeft = the last index such that the area is less than S

            for(int pRight = 0 ; pRight < (int)rightSide.size() ; pRight++)
            {
                // printf("pLeft = %d pRight = %d\n",pLeft,pRight);
                // if(pLeft >= 0)
                // printf("oiii %lld\n",getArea( A , leftSide[pLeft] , B , rightSide[pRight] ));
                while( pLeft >= 0 && getArea( A , leftSide[pLeft] , B , rightSide[pRight] ) >= S )
                {
                    // pLeft--;

                    BIT[0].update( idReal[a][ leftSide[pLeft].index ] , 1 );
                    BIT[1].update( idReal[b][ leftSide[pLeft].index ] , 1 );

                    pLeft--;
                }

                // printf("pLeft = %d\n",pLeft);

                // rightSide[pRight].print();
                // printf("index = %d\n",rightSide[pRight].index);

                // printf("pRight = %d -> pLeft = %d   %lld\n",pRight,pLeft);

                // leftSide[pLeft + 1], leftSide[pLeft + 2], ... are good

                int cntQuadrilaterals = (int)leftSide.size() - pLeft - 1;

                // printf("pLeft = %d cnt = %d\n",pLeft,cntQuadrilaterals);

                int concaveQuadrilaterals = countConcave( a , b , rightSide[pRight].index );
                int convexQuadrilaterals = cntQuadrilaterals - concaveQuadrilaterals;

                // printf("-> convex = %d concave = %d\n",convexQuadrilaterals,concaveQuadrilaterals);

                cntConvex += convexQuadrilaterals;
                cntConcave += concaveQuadrilaterals;
            }
        }
    }

    lli answer = cntConvex/2 + cntConcave;
    printf("%lld\n",answer);
}
