template<class Node>
class lazy_segtree {
    using V = typename Node::value_structure;
    using VT = typename V::value_type;
    using O = typename Node::operate_structure;
    using OT = typename O::value_type;
    
    int n;
    vector<Node> tree;
    
    void propagate(int k, int l, int r) {
//        if (tree[k].op.value == O::identity) return;
        if (k < n) {
            tree[k * 2].op.value = O::operate(tree[k * 2].op.value, tree[k].op.value);
            tree[k * 2 + 1].op = O::operate(tree[k * 2 + 1].op.value, tree[k].op.value);
        }
        OT ot = O::duplicate(tree[k].op.value, r - l);
        tree[k].value.value = Node::operate(tree[k].value.value, ot);
        tree[k].op.value = O::identity;
    }

public:
    VT get(int i) { return Node::operate(tree[i].value.value, tree[i].op.value); }
    
    lazy_segtree(int _n, const vector<VT> &init = vector<VT>()) {
        n = 1;
        while (n < _n) n *= 2;
        tree.assign(n * 2, Node{V::identity, O::identity});
        if (init.size()) rep(i, _n) tree[i + n].value.value = init[i];
        rrep(i, n) tree[i].value.value = V::operate(tree[i * 2].value.value, tree[i * 2 + 1].value.value);
    }
    
    void update(int a, int b, OT x, int k = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        propagate(k, l, r);
        if (a <= l && r <= b) {
            tree[k].op.value = O::operate(tree[k].op.value, x);
            propagate(k, l, r);
        } else if (a < r && l < b) {
            update(a, b, x, k * 2, l, (l + r) / 2);
            update(a, b, x, k * 2 + 1, (l + r) / 2, r);
            tree[k].value.value = V::operate(tree[k * 2].value.value, tree[k * 2 + 1].value.value);
        }
    }
    
    // segment [a,b)
    VT fold(int a, int b, int k = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        propagate(k, l, r);
        if (b <= l || r <= a) return V::identity;
        if (a <= l && r <= b) return tree[k].value.value;
        VT lt = fold(a, b, k * 2, l, (l + r) / 2);
        VT rt = fold(a, b, k * 2 + 1, (l + r) / 2, r);
        return V::operate(lt, rt);
    }
};

class Value_structure {
public:
    using value_type = ;
    
    value_type value;
    
    Value_structure(value_type value) : value(value) {}
    
    static constexpr value_type identity = ;
    
    static constexpr value_type operate(const value_type &l, const value_type &r) {
        return ;
    }
};

class Operate_structure {
public:
    using value_type = ;
    
    value_type value;
    
    Operate_structure(value_type value) : value(value) {}
    
    static constexpr value_type identity = ;
    
    static constexpr value_type operate(const value_type &l, const value_type &r) {
        return ;
    }
    
    static constexpr value_type duplicate(const value_type &v, int len) {
        return ;
    }
};

class Node {
public:
    using value_structure = Value_structure;
    using operate_structure = Operate_structure;
    
    value_structure value;
    operate_structure op;

private:
    using V = value_structure::value_type;
    using O = operate_structure::value_type;

public:
    Node(V value, O op) : value(value), op(op) {}
    
    static constexpr V operate(const V &l, const O &r) {
        return ;
    }
};
