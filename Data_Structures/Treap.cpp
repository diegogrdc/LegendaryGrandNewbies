struct item
{
    int key, prior;
    item *l, *r;
    item() {}
    item(int key) : key(key), prior(rand()), l(NULL), r(NULL) {}
    item(int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) {}
};
typedef item *pitem;

void split(pitem t, int key, pitem &l, pitem &r)
{
    if (!t)
        l = r = NULL;
    else if (t->key <= key)
        split(t->r, key, t->r, r), l = t;
    else
        split(t->l, key, l, t->l), r = t;
}

void insert(pitem &t, pitem it)
{
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split(t, it->key, it->l, it->r), t = it;
    else
        insert(t->key <= it->key ? t->r : t->l, it);
}

void merge(pitem &t, pitem l, pitem r)
{
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
}

void erase(pitem &t, int key)
{
    if (t->key == key)
    {
        pitem th = t;
        merge(t, t->l, t->r);
        delete th;
    }
    else
        erase(key < t->key ? t->l : t->r, key);
}
