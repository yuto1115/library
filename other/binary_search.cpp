auto f = [&](int x) {
    // edit here
};
while(abs(ok-ng) > 1) {
    int mid = (ng+ok)/2;
    if(f(mid)) ok = mid;
    else ng = mid;
}
