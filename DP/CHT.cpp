// CONVEX HULL TRICK STUFF

struct line
{
    ll m, b;
};

vector<line> ch;
ll opt;

// Regresa true si l3 o l1 esconden a l2 siempre
bool bad(ll l1, ll l2, ll l3)
{
    long double i1 = (long double)(ch[l1].b - ch[l3].b) / (long double)(ch[l3].m - ch[l1].m);
    long double i2 = (long double)(ch[l1].b - ch[l2].b) / (long double)(ch[l2].m - ch[l1].m);
    return i1 < i2;
}

// Agrega una nueva linea ( slope estrictamente menor ) a la estrtuctura
void add(ll m, ll b)
{
    ch.push_back({m, b});
    // Checa si existen lineas irrelevantes
    while (ch.size() >= 3 && bad(ch.size() - 3, ch.size() - 2, ch.size() - 1))
        ch.erase(ch.end() - 2);
}

// Regresa 0 si x esta en el rango de la linea ln , -1 si esta a la izq y 1 si esta a la der
ll inRange(ll ln, ll x)
{
    // Checa si esta a la izq
    // interseccion entre ln y (ln-1) tiene x = (b1-b2)/(m2-m1)
    if (ln > 0 && (long double)x < (long double)(ch[ln].b - ch[ln - 1].b) / (long double)(ch[ln - 1].m - ch[ln].m))
        return -1;
    if (ln + 1 < ch.size() && (long double)(ch[ln + 1].b - ch[ln].b) / (long double)(ch[ln].m - ch[ln + 1].m) < (long double)x)
        return 1;
    return 0;
}

// Regresa el segmento con minimo y para una x dada con las lineas actualmente en la estructura
ll query(ll x)
{
    ll l = 0, r = ch.size() - 1;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        ll donde = inRange(mid, x);
        if (!donde)
            return mid;
        if (donde == -1)
            r = mid - 1;
        else
            l = mid + 1;
    }
}
