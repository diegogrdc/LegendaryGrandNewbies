struct Line
{
    ll m, b;
    Line(ll _m, ll _b)
    {
        m = _m;
        b = _b;
    }

    ll eval(ll x)
    {
        return m * x + b;
    }
};

const int SZ = 1e6;
struct node
{
    Line ln;
    node *l;
    node *r;
    node() : l(nullptr), r(nullptr), ln(Line(1e9, 1e9)){};
};

const ll INF = 1e18;
typedef node *pnode;
node memo[MAX * 10];
int disp;
int N;
pii a[MAX];
pnode root;

pnode newpnode(Line x)
{
    pnode nw = &memo[disp++];
    nw->ln = x;
    return nw;
}

void add_line(pnode nd, int l, int r, Line nw)
{
    int m = (l + r) / 2;
    bool lf = nw.eval(l) < nd->ln.eval(l);
    bool md = nw.eval(m) < nd->ln.eval(m);
    // t[idx] should keep lower in one side where not intersection
    if (md)
        swap(nd->ln, nw);
    if (l == r)
        return;

    if (nd->l == nullptr)
        nd->l = newpnode(nd->ln);
    if (nd->r == nullptr)
        nd->r = newpnode(nd->ln);

    if (lf != md)
        add_line(nd->l, l, m, nw);
    else
        add_line(nd->r, m + 1, r, nw);
}

ll get(pnode nd, int l, int r, int x)
{
    if (nd == nullptr)
        return INF;
    int m = (l + r) / 2;
    if (l == r)
        return nd->ln.eval(x);
    else if (x < m)
        return min(nd->ln.eval(x), get(nd->l, l, m, x));
    else
        return min(nd->ln.eval(x), get(nd->r, m + 1, r, x));
}
