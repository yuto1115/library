template<typename T,typename MERGE,typename UPDATE>
class lazy_segtree {
    int n;
    vector<T> val,lazy;
    T identity_merge,identity_update;
    MERGE merge; // (T,T) -> T
    // update value for specified times
    UPDATE _update; // (T,T,int) -> T
    void eval(int k,int l,int r) {
        if(lazy[k] == identity_update) return;
        if(k < n-1) {
            lazy[k*2+1] = _update(lazy[k*2+1],lazy[k],1);
            lazy[k*2+2] = _update(lazy[k*2+2],lazy[k],1);
        }
        val[k] = _update(val[k],lazy[k],r-l);
        lazy[k] = identity_update;
    }

public:
    lazy_segtree(int _n,vector<T> init,T identity_merge,T identity_update,
                 MERGE merge,UPDATE update)
            :identity_merge(identity_merge),identity_update(identity_update),merge(merge),_update(update) {
        n = 1;
        while(n < _n) n *= 2;
        val = vector<T>(2*n-1,identity_merge);
        lazy = vector<T>(2*n-1,identity_update);
        rep(i,_n) val[i+n-1] = init[i];
        rrep(i,n-1) val[i] = merge(val[i*2+1],val[i*2+2]);
    }
    void update(int a,int b,T x,int k = 0,int l = 0,int r = -1) {
        if(r == -1) r = n;
        eval(k,l,r);
        if(a <= l && r <= b) {
            lazy[k] = _update(lazy[k],x,1);
            eval(k,l,r);
        } else if(a < r && l < b) {
            update(a,b,x,k*2+1,l,(l+r)/2);
            update(a,b,x,k*2+2,(l+r)/2,r);
            val[k] = merge(val[k*2+1],val[k*2+2]);
        }
    }
    // segment [a,b)
    T query(int a,int b,int k = 0,int l = 0,int r = -1) {
        if(r == -1) r = n;
        eval(k,l,r);
        if(b <= l || r <= a) return identity_merge;
        if(a <= l && r <= b) return val[k];
        T t1 = query(a,b,2*k+1,l,(l+r)/2);
        T t2 = query(a,b,2*k+2,(l+r)/2,r);
        return merge(t1,t2);
    }
    pair<T,T> operator[](int i) const { return make_pair(val[i],lazy[i]); }
};
