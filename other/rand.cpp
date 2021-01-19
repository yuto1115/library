random_device rnd;
mt19937_64 mt(rnd());

template<class T>
T rand(T min_val, T max_val) {
    assert(min_val <= max_val);
    uniform_int_distribution<T> dist(min_val, max_val);
    return dist(mt);
}
