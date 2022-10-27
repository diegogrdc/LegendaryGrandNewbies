// Li Chao Tree 
// Finds Min for linear functions for x in range (1, SZ)
// Can also be done for big coords with dynamic segtree

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

struct LCT
{
    vector<Line> t;
    int N;

    LCT(int _N) : N(_N)
    {
        t.resize(4 * N, Line(1e9, 1e9));
    }

    void add_line(int idx, int l, int r, Line nw)
    {
        int m = (l + r) / 2;
        bool lf = nw.eval(l) < t[idx].eval(l);
        bool md = nw.eval(m) < t[idx].eval(m);
        // t[idx] should keep lower in one side where not intersection
        if (md)
            swap(t[idx], nw);
        if (l == r)
            return;
        else if (lf != md)
            add_line(2 * idx + 1, l, m, nw);
        else
            add_line(2 * idx + 2, m + 1, r, nw);
    }

    ll get(int idx, int l, int r, int x)
    {
        int m = (l + r) / 2;
        if (l == r)
            return t[idx].eval(x);
        else if (x < m)
            return min(t[idx].eval(x), get(2 * idx + 1, l, m, x));
        else
            return min(t[idx].eval(x), get(2 * idx + 2, m + 1, r, x));
    }
};
