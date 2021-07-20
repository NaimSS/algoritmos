// number of torus

int n,m;
    cin >> n >> m;
    if(n > m)swap(n,m);
    BigInt tot = 0;
    BigInt ans = 0;
    pwr[0] = 1;
    rep(i,1,n*m + 1)pwr[i] = pwr[i-1] + pwr[i-1];
    rep(dx,0,n){ // desviou no x
        rep(dy,0,m){ // desviou no y
            rep(swp,0,2){ // swap
                rep(rot,0,1+(n==m)){ // rotaciona 
                    tot+=1;
                    rep(i,0,n){
                        rep(j,0,m){
                            vis[i][j]=0;
                            int x = i,y = j;

                            if(swp){
                                x = (n-1-x);
                                y = (m-1-y);
                            }
                            if(rot){
                                x = (n-1-x);
                                swap(y,x);
                            }


                            x = (x + dx)%n;
                            y = (y + dy)%m;
                            go[i][j] = pii(x,y);
                        }
                    }


                    int ciclos=0;
                    rep(i,0,n){
                        rep(j,0,m)if(!vis[i][j]){
                            ciclos++;
                            int l = i,c = j;
                            while(!vis[l][c]){
                                vis[l][c]=1;
                                pii r = go[l][c];
                                l=r.F,c=r.S;
                            }
                        }
                    }

                    ans+=pwr[ciclos];


                }
            }
        }
    }
