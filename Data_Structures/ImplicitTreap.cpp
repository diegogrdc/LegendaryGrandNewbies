struct node {
    ll k, p;
    node *l, *r;
    ll sz, sum, cnt;
};
 
typedef node * pnode;
ll idx = 0;
node memo[60*MAX];
pnode root;
 
ll sz(pnode x) {return x == NULL ? 0 : x->sz;}
ll sum(pnode x) {return x == NULL ? 0 : x->sum;}
ll cnt(pnode x) {return x == NULL ? 0 : x->cnt;}
 
void upd(pnode x) {
    if(! x)
        return;
    x->sz = x->cnt + sz(x->l) + sz(x->r);
    x->sum = x->k * x->cnt + sum(x->l) + sum(x->r);
}
 
void split(pnode n , ll k , pnode & l , pnode & r) {
    if(! n)
        l = r = NULL;
    else if(k < n->k) // es mayor
        split(n->l , k , l , n->l), r = n;
    else
        split(n->r , k , n->r , r), l = n;
    
    upd(l);
    upd(r);
}
 
void merge(pnode & n , pnode l , pnode r) {
    if(! l or ! r)
        n = l ? l : r;
    else if(l->p > r->p)
        merge(l->r , l->r , r), n = l;
    else
        merge(r->l , l , r->l), n = r;
    upd(n);
}
 
pnode newNode(ll k) {
    pnode n = & memo[idx++];
    n->p = rand();
    n->k = k;
    n->sz = n->cnt = 1;
    n->sum = k;
    return n;
}
 
bool find(pnode & x , ll v , bool t) {
    if(! x)
        return false;
    if(x->k == v) {
        if(t == 1) {
            x->cnt++;
            upd(x);
            return true;
       }
        else {
            x->cnt--;
            upd(x);
            if(x->cnt == 0)
                return true;
            return false;
       }
   }
    
    bool ok = x->k > v ? find(x->l , v , t) : find(x->r , v , t);
    upd(x);
    return ok;
}
 
void insert(pnode & n , ll k) {
    pnode l, r, x;
    if(! find(root , k , 1)) {
        split(n , k , l , r);
        x = newNode(k);
        merge(n , l , x);
        merge(n , n , r);
   }
}
 
void erase(pnode & n , ll k) {
    pnode l, r, x;
    if(find(root , k , 0)) {
        split(n , k , l , r);
        split(l , k - 1 , l , x);
        merge(n , l , r);
   }
}
 
ll kth(pnode & n , ll k) {
    if(! n)
        return 0;
    if(sz(n->l) >= k)
        return kth(n->l , k);
    else if(sz(n->l) + n->cnt >= k)
        return n->k;
    return kth(n->r , k - sz(n->l) - n->cnt);
}
