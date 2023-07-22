// Comments by collares

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Código de biblioteca
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

struct node
{
    ll val;
    int sz, cnt;
    int qtd_nos;
    node *l, *r;
    ll p;

    node(ll Val = 0, int Cnt = 0) : val(Val), sz(Cnt), cnt(Cnt), qtd_nos(1),
                                    l(NULL), r(NULL)
    {
        p = rng();
    }

    ~node()
    {
        delete l;
        delete r;
    }

    void update()
    {
        sz = cnt;
        qtd_nos = 1;
        if (l)
            sz += l->sz, qtd_nos += l->qtd_nos;
        if (r)
            sz += r->sz, qtd_nos += r->qtd_nos;
    }
};

void
join(node* l, node* r, node*& i)
{
    // assume que l < r
    if (!l or !r)
        return void(i = l ? l : r);
    if (l->p > r->p)
        join(l->r, r, l->r), i = l;
    else
        join(l, r->l, r->l), i = r;
    i->update();
}

void
split(node* i, node*& l, node*& r, ll v)
{
    // <v em L
    if (!i)
        return void(r = l = NULL);
    if (i->val < v)
        split(i->r, i->r, r, v), l = i;
    else
        split(i->l, l, i->l, v), r = i;
    i->update();
}

pii
countEq(node* treap, ll val)
{
    if (treap == NULL)
        return pii(0, 0);
    if (treap->val == val)
        return pii(1, treap->cnt);
    if (treap->val > val)
        return countEq(treap->l, val);
    return countEq(treap->r, val);
}

void
add_at(node*& treap, ll val, int qtd)
{
    if (treap->val == val) {
        treap->cnt += qtd;
        return treap->update();
    }
    if (treap->val > val)
        add_at(treap->l, val, qtd);
    else
        add_at(treap->r, val, qtd);
    treap->update();
}

void
insert(node*& treap, ll val, int qtd)
{
    if (countEq(treap, val).first) {
        add_at(treap, val, qtd);
        treap->update();
    } else {
        node *L, *R;
        split(treap, L, R, val);
        node* at = new node(val, qtd);
        join(L, at, L);
        join(L, R, treap);
    }
    if (countEq(treap, val).second == 0) {
        node *L, *M, *R;
        split(treap, M, R, val + 1);
        split(M, L, M, val);
        if (M)
            delete M;
        join(L, R, treap);
    }
    if (treap == NULL)
        treap = new node(0, 0);
}

ll
countLeq(node*& treap, ll val)
{
    node *L, *R;
    split(treap, L, R, val + 1); // menor ou igual a val em L
    ll res = (L == NULL ? 0 : L->sz);
    join(L, R, treap);
    return res;
}

void
merge(node*& treap1, node*& treap2)
{
    if (treap1->cnt) {
        insert(treap2, treap1->val, treap1->cnt);
    }
    if (treap1->l)
        merge(treap1->l, treap2);
    if (treap1->r)
        merge(treap1->r, treap2);
}

struct dsu
{
    vi p, ps;

    dsu(int n)
    {
        p = vi(n + 1), ps = vi(n + 1, 1);
        for (int i = 0; i < n + 1; i++)
            p[i] = i;
    }

    int find(int x)
    {
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    int join(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y)
            return y;
        if (ps[x] > ps[y])
            swap(x, y);
        p[x] = y, ps[y] += ps[x];
        return y;
    }
};

// *** COMEÇO DE VERDADE ***

// _Teorema_: Um par de folhas (a, b) é um par inválido (que não
// satisfaz as condições do problema) se e somente se existem c no
// caminho a-b e folha d tal que o caminho c-d é aresta-disjunto de
// a-b satisfazendo dist(c, d) * L > min(dist(a, c), dist(c, b)) * R.
//
// Prova:
//
// (<=, parte trivial) Se existe c no caminho a-b e folha d tal que
// a-b e c-d são aresta-disjuntos mas dist(c, d) * L > dist(a, c) * R,
// digamos, então o caminho a-c-d teria peso maior que o caminho a-c-b
// (que é só a-b) mesmo que coloquemos o menor peso possível nas
// arestas do caminho c-d.
//
// (=>) suponha que a-b não é um diâmetro mesmo colocando peso R em
// a-b e L no resto da árvore. seja x-y um diâmetro.
//
// * se x-y for vértice-disjunto de a-b, então temos
//
//            dist(a, b) * R < dist(x, y) * L
//
//   como os caminhos x-y e a-b são disjuntos, existem vértices c em
//   a-b e v em x-y tal que o caminho c-v é vértice disjunto de x-y e
//   a-b a menos dos extremos. suponha (trocando os rótulos de x e y
//   se necessário) que dist(v, x) >= dist(v, y). então
//
//     dist(c, x) = dist(c, v) + dist(v, x) >= dist(c, v) + dist(x, y)/2
//
//   e portanto, tomando d = x,
//
//     dist(c, d) * L >= dist(x, y) * L/2
//                    >= dist(a, b) * R/2
//                    >  min(dist(a, c), dist(c, b) * R.
//
// * se x-y intersecta a-b, o argumento é similar: basta olhar para o
//   P = (maior caminho em E(x-y) \ E(a-b)) e escolher c e d como as
//   pontas desse caminho apropriadamente.
//                                                              \qed
//
// O teorema acima motiva as seguintes definições.
//
// _Definição 1_: Uma folha f da subárvore de v é $v$-ativa se
//
//     (altura[f] - altura[v]) * R >= subindo[v] * L.
//
// Note que se uma folha é $v$-ativa, ela é $pai[v]$-ativa.
//
// _Definição 2_: Uma folha f da subárvore de v é $v$-anulada se
// existe caminho f-f2 na subárvore de v com
//
//     (altura[f] - altura[w]) * R < (altura[f2] - altura[w]) * L
//
// onde w = lca(f, f2). Uma folha f não $v$-anulada é dita ser
// $v$-válida.
//
// _Corolário_: Se f e f2 são folhas $v$-ativas e $v$-válidas com
// lca(f, f2) == v, então (f, f2) é um par que deve ser contado na
// resposta.
//
// Prova: Como a folha é $v$-ativa, a condição do teorema não pode
// valer para c = v.  Todas as outras escolhas de c são tais que os
// únicos caminhos c-d aresta-disjuntos de f-f2 são "para baixo", e a
// condição de ser $v$-válida garante que a condição do teorema também
// não vale.

const int N = 200100;

int n;
ll L, R;
vi g[N];

// distancia a root (uma não folha fixada no main)
ll altura[N];

// eh folha?
int leaf[N];

// subindo[v] = comprimento do maior caminho que começa com a aresta (v, pai[v]).
int subindo[N];

// depth[v] = max_(w descendente de v) altura[w]
int depth[N];

// novoX[w] = max_{w2 != w, w2 irmão de w} (depth[w2] - altura[pai[w]])*L - altura[pai[w]]*R;
ll novoX[N];

void
pre_calc(int v, int p = -1)
{
        depth[v] = altura[v];
        leaf[v] = (g[v].size() == 1);

        for (int w : g[v])
            if (w != p) {
                altura[w] = 1 + altura[v];
                pre_calc(w, v);
                depth[v] = max(depth[v], depth[w]);
            }
}

void
calc_subindo(int v, int p = -1)
{
    vector<pii> depths;

    depths.push_back(pii(0, v));
    for (int w : g[v])
        if (w != p)
            depths.push_back(make_pair(depth[w] - altura[v], w));

    sort(depths.begin(), depths.end(), greater<pii>());

    for (int w : g[v])
        if (w != p) {
            subindo[w] = subindo[v] + 1;

            // w -> v -> outra subarvore
            int other_depth = depths[0].first;
            if (depths[0].second == w)
                other_depth = depths[1].first;

            subindo[w] = max(subindo[w], other_depth + 1);
            novoX[w] = (ll)other_depth * L - (ll)altura[v] * R;
            calc_subindo(w, v);
        }
}

// Definição: Para toda folha f na subárvore de v, definimos a função
//
//     X'(f) = max_{d folha : d na subárvore de v}
//                    dist(d, lca(f, d)) * L - dist(lca(f, d), v) * R.
//
// Invariante: Ao solve(v) retornar, cinco estruturas estão atualizadas:
//
// * DSU, uma estrutura union-find tal que X(a) = X(b) se e só se
//   DSU.find(a) = DSU.find(b).
//
// * Um array X tal que X[DSU.find(f)] = X'(f) - altura[v] * R.
//
//   XXX(collares): Acho que não há garantia de que X[f] = X'(f) -
//   altura[v] * R se f != DSU.find(f).
//
// * dsu_root[v][val] é uma folha f (ativa ou inativa, tanto faz) da
//   subárvore de v tal que X[val] == f e DSU.find(f) == f.
//
//   O objetivo desse map é poder suportar a seguinte operação: Dados
//   val < cur, toda folha f da subérvore de v que tem X[f] == val
//   passa a ter X[f] = cur.
//
//   XXX(collares): A solução de referência tem um parâmetro extra e
//   (eu acho que) não garante que os elementos do array são raízes do
//   DSU.
//
// * fs_por_h_ativ[v][b] = { (altura[f], f) :
//               f folha (ativa se b=1/inativa se b=0) na subarvore de v }
//
// * Um treap guardando (com multiplicidade) X[f] para toda folha f
//   $v$-ativa e $v$-válida.

dsu DSU(N);
ll X[N];
map<ll, int> dsu_root[N];
multiset<pll> fs_por_h_ativ[N][2];
node* treap[N];

ll res = 0;
int subarvore[N]; // dada uma folha, qual filho de v contem ela como subarvore

void
solve(int v, int p = -1)
{
    if (leaf[v]) {
        // folhas começam trivialmente inativas
        fs_por_h_ativ[v][0].insert(pll(altura[v], v));
        X[v] = -altura[v] * R;
        dsu_root[v][X[v]] = v;

        return;
    }

    // Filhos ordenados por profundidade, pai por último.
    sort(g[v].begin(), g[v].end(), [&](int a, int b) {
        if (a == p)
            return false;
        if (b == p)
            return true;
        return depth[a] > depth[b];
    });

    for (auto w : g[v])
        if (w != p) {
            solve(w, v);

            // Mover caras de fs_por_h_ativ se eles viraram ativos
            while (fs_por_h_ativ[w][0].size()) {
                auto [h_folha, folha] = *fs_por_h_ativ[w][0].rbegin();

                if ((h_folha - altura[v]) * R >= subindo[v] * L) {
                    // inativo -> ativo
                    fs_por_h_ativ[w][0].erase(
                      fs_por_h_ativ[w][0].find(make_pair(h_folha, folha)));
                    fs_por_h_ativ[w][1].insert(make_pair(h_folha, folha));

                    insert(treap[w], X[DSU.find(folha)], 1);
                } else
                    break;
            }
        }

    int num_ativos = 0;

    // para determinar se uma folha f acabou de virar $v$-anulada,
    // temos que considerar folhas f2 com lca(f, f2) = v e
    //
    //   (altura[f2] - altura[v]) * L > (altura[f] - altura[v]) * R
    //
    // "sai" vai conter as folhas f que são anuladas por exatamente
    // uma subárvore de v (isto é, tais que se w é o filho de v tal
    // que f é descendente de w, existe um único w2 != w que contém
    // folha f2 que anula f).
    vector<pii> sai;

    // Vê quem vai ser anulado e por quantos
    for (int i = 0; i < g[v].size(); i++) {
        int w = g[v][i];
        if (w == p)
            continue;

        for (int k = 0; k < 2; k++) {
            while (fs_por_h_ativ[w][k].size()) {
                auto [h_folha, folha] = *fs_por_h_ativ[w][k].begin();

                int num_anuladores = 0;
                int indice_subarvore_anuladora = -1;

                // precisa de 3 só, porque o p está no final da ordem
                // (w e dois anuladores). mas 4 obviamente funciona.
                for (int j = 0; j < min(4, (int)g[v].size()); j++)
                    if (i != j) {
                        int w2 = g[v][j];
                        if (w2 == p || w2 == w)
                            continue;

                        // como depth está ordenado por altura, obviamente se
                        // isso bater vai bater para j == 1 (se i == 0) ou j ==
                        // 0 (se i > 0).
                        if ((depth[w2] - altura[v]) * L > (h_folha - altura[v]) * R) {
                            num_anuladores++;
                            indice_subarvore_anuladora = j;
                        }
                    }

                // como eles estao ordenados por h_folha e a condição
                // é monótona (para w fixo), podemos parar.
                if (num_anuladores == 0)
                    break;

                fs_por_h_ativ[w][k].erase(
                  fs_por_h_ativ[w][k].find(make_pair(h_folha, folha)));

                if (k) {
                    // a treap guarda só folhas ativas e não-anuladas
                    insert(treap[w], X[DSU.find(folha)], -1);

                    // folhas anuladas por duas subárvores diferentes
                    // não podem mais fazer partes de pares. Talvez
                    // folhas anuladas por uma única subárvore possam
                    // (com outras folhas da subárvore que a anula).
                    if (num_anuladores == 1) {
                        subarvore[folha] = w;
                        sai.push_back(pii(folha, indice_subarvore_anuladora));
                    }
                }
            }
        }

        // se f e f2 são folhas com lca(f, f2) == v e ambas são
        // ativas, então certamente o par (f, f2) é válido.
        res += (ll)fs_por_h_ativ[w][1].size() * num_ativos;
        num_ativos += fs_por_h_ativ[w][1].size();
    }

    // anuladores[pii(w, w2)] são as folhas da subárvore de w que são
    // anuladas por alguém de w2.
    map<pii, vi> anuladores;

    for (auto [folha, indice_subarvore_anuladora] : sai) {
        int w = subarvore[folha];
        int w2 = g[v][indice_subarvore_anuladora];
        anuladores[pii(w, w2)].push_back(folha);
    }

    for (auto [folha, indice_subarvore_anuladora] : sai) {
        int w2 = g[v][indice_subarvore_anuladora];

        // folha foi anulada, mas só por folhas de uma subárvore (w2). as
        // folhas de treap[w] não foram anuladas.
        //
        // suponha que queremos parear com uma folha f2 da subarvore
        // de w2. analisando a prova do teorema, precisamos mostrar
        // que para toda folha d da subárvore de w2, tomando c =
        // lca(d, f2) no que segue, temos que
        //
        // dist(c, d) * L <= min(dist(folha, c), dist(c, f2)) * R.
        //
        // o fato de que dist(c, d) * L <= dist(c, f2) * R segue do
        // fato de que treap[w2] só contém vértices não $w2$-anulados.
        // para contar quantas folhas f2 satisfazem para toda folha d
        //
        //       dist(c, d) * L <= dist(folha, c) * R,
        //
        // lembre que dist(folha, c) = dist(folha, v) + 1 + dist(w2,
        // c). Assim, a condição é que para toda folha d
        //
        //   dist(c, d) * L - dist(c, w2) * R <= R + dist(folha, v) * R
        //
        // Lembrando da definição de X',
        //
        // X'(f2) = max_{d folha : d na subárvore de w2}
        //                 dist(d, c) * L - dist(c, w2) * R,
        //
        // e que X[f2] = X'(f2) - altura[w]*R, vemos que queremos
        //
        // X[f2] + altura[w] * R = X'(f2) <= R + dist(folha, v) * R
        // <=> X[f2] <= -(altura[w] - 1) * R + dist(folha, v) * R
        // <=> X[f2] <= altura[folha] * R - 2*altura[v]*R.
        res +=
          countLeq(treap[w2], altura[folha] * R - 2 * altura[v] * R);
    }

    // O caso de par (f, f2) em que tanto f quanto f2 foram anulados
    // por apenas uma subárvore não existe, e verificamos isso aqui.
    for (auto [p, _] : anuladores) {
        auto [w1, w2] = p;

        // w1 < w2 é tal que w anula w2 e w2 anula w
        if (w1 > w2)
            continue;

        // No que segue, toda vez que tiver um vértice com índice i, está
        // na subárvore do w_i. Seja f1 uma folha que é anulada pela
        // subárvore w2 e g2 uma folha que é anulada pela subárvore
        // w1. Temos que existem fohas g1 e f2 tais que
        //
        // (1) (altura[f1] - altura[v]) * R < (altura[f2] - altura[v]) * L
        // (2) (altura[g2] - altura[v]) * R < (altura[g1] - altura[v]) * L.
        //
        // Seja yi = lca(fi, gi) (que está na subárvore do wi). Pelo
        // algoritmo, a gente só estaria considerando f1 não w1-anulado e
        // g2 não w2-anulado. Assim, vale que
        //
        // (3) (altura[f1] - altura[y1]) * R >= (altura[g1] - altura[y1]) * L
        // (4) (altura[g2] - altura[y2]) * R >= (altura[f2] - altura[y2]) * L.
        //
        // Mas fazendo (1) + (2) - (3) - (4), conclui-se que
        //
        // (altura[y1] + altura[y2] - 2*altura[v]) * R <
        //     (altura[y1] + altura[y2] - 2*altura[v]) * L,
        //
        // o que é absurdo porque (altura[y1] + altura[y2] - 2*altura[v]) > 0. 
        assert(!anuladores.count(pii(w2, w1)));
    }

    // Lembre que atualmente, se f é descendente de w (w filho de v),
    //
    //   X'(f) = max_(d folha : d na subárvore de w)
    //                      dist(d, lca(f, d)) * L - dist(lca(f, d), w) * R.
    //
    // Assim, para atualizar X' precisamos fazer
    //
    //   X'(f) := max(X'(f) - R,
    //                max_(c folha : v = lca(f, c)) dist(c, v) * L),
    //
    // Lembre também que guardamos X[f] = X'(f) - altura[v] * R. Logo,
    //
    //   X[f] = max(X[f] + altura[w] * R - R,
    //                max_(c folha : v = lca(f, c)) dist(c, v) * L) - altura[v] * R,
    //        = max(X[f],
    //             max_(c folha : v = lca(f, c)) dist(c, v) * L - altura[v] * R).
    //        = max(X[f], novoX[w]).
    for (auto w : g[v])
        if (w != p) {
            ll cur = novoX[w]; // novoX[w] = other_depth*L - altura[v]*R;

            while (dsu_root[w].size()) {
                auto [val, rep] = *dsu_root[w].begin();
                
                if (val < cur) {
                    int id = DSU.find(rep);
                    int cnt = countEq(treap[w], X[id]).second;

                    if (cnt) {
                        insert(treap[w], X[id], -cnt);
                        insert(treap[w], cur, +cnt);
                    }

                    dsu_root[w].erase(val);

                    if (dsu_root[w].count(cur))
                        dsu_root[w][cur] = DSU.join(dsu_root[w][cur], id);
                    else
                        dsu_root[w][cur] = id;
                    X[dsu_root[w][cur]] = cur;
                } else
                    break;
            }
        }

    // Small to large
    for (auto w : g[v])
        if (w != p) {
            for (int j = 0; j < 2; j++) {
                if (fs_por_h_ativ[w][j].size() > fs_por_h_ativ[v][j].size())
                    swap(fs_por_h_ativ[w][j], fs_por_h_ativ[v][j]);

                for (auto x : fs_por_h_ativ[w][j])
                    fs_por_h_ativ[v][j].insert(x);
                fs_por_h_ativ[w][j].clear();
            }

            if (dsu_root[w].size() > dsu_root[v].size())
                swap(dsu_root[w], dsu_root[v]);

            for (auto [val, rep] : dsu_root[w])
                if (dsu_root[v].count(val))
                    dsu_root[v][val] = DSU.join(dsu_root[v][val], rep);
                else
                    dsu_root[v][val] = rep;

            if (treap[w]->qtd_nos > treap[v]->qtd_nos)
                swap(treap[w], treap[v]);

            merge(treap[w], treap[v]);
        }
}

int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> L >> R;
    assert(n > 2 and n <= 200000);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // Precalc
    for (int i = 0; i < N; i++)
        treap[i] = new node(0, 0);

    int root = 1;
    while (g[root].size() == 1)
        root++;

    pre_calc(root);
    calc_subindo(root);
    solve(root);

    cout << res << endl;
}
