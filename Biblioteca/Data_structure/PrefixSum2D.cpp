/* Author: Me
 * 2D-prefix sum;
 * Só caso eu me confunda em alguma questao
 * https://cses.fi/problemset/result/2481603/
 * Depois de usar o mark e 1 prefix sum, qtd nao funciona!!
 * com so 1 init, pre[i][j] = quantos retangulos pegam i,j.
 * Para usar qtd fazer 2 prefix sum
*/

void mark_rectangle(int li,int lj,int ri,int rj){ 
// add 1 to every point in [li,ri]x[lj,rj]
// after this do another prefix sum
            pre[li][lj]++;
            pre[li][rj+1]--;
            pre[ri+1][lj]--;
            pre[ri+1][rj+1]++;
}

int qtd(int li,int lj,int ri,int rj){ // se tiver usando o mark, tem q usar init 2x
  if(li<=0 or lj<=0 or ri>n or rj>m)return 0;

  int val = pre[ri][rj] - pre[ri][lj-1] - pre[li-1][rj] + pre[li-1][lj-1];
  return val;
}


void init(){
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
                // se tem valor inicial, so precisa usar isso 1 vez
      pre[i][j]= (mat[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1]);
                // se ta usando o mark: rodar 2 vezes para usar o qtd.
                //pre[i][j] += (pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1]);
    }
  }
}
