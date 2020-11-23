const double eps = 1e-10;

// return the rank of the matrix
// O(h * w^2)
template<class T>
int GaussJordan(matrix<T> &a, bool isExtended, bool isDouble) {
    int rank = 0;
    rep(col, a.w) {
        if (isExtended and col == a.w - 1) break;
        int pivot = -1;
        T mx = (isDouble ? eps : 0);
        rep2(row, rank, a.h) {
            if (isDouble) {
                if (abs(a[row][col]) > mx) {
                    mx = abs(a[row][col]);
                    pivot = row;
                }
            } else {
                if (a[row][col] != 0) {
                    pivot = row;
                }
            }
        }
        if (pivot == -1) continue;
        
        swap(a[pivot], a[rank]);
        
        // fix the value of pivot 1
        rrep(col2, a.w) a[rank][col2] /= a[rank][col];
        
        rep(row, a.h) {
            if (row == rank) continue;
            if (isDouble) {
                if (abs(a[row][col]) <= eps) continue;
            } else {
                if (a[row][col] == 0) continue;
            }
            T fac = a[row][col];
            rep(col2, a.w) {
                a[row][col2] -= a[rank][col2] * fac;
            }
        }
        rank++;
    }
    return rank;
}

// solve ax = b     reference: https://drken1215.hatenablog.com/entry/2019/03/20/202800
// if there is no solution, return empty vector
// otherwise, return one solution (all parameters is fixed 0)
// if T is mint, calculate the numbers of solutions by 'mod^(n-rank)'
template<class T>
// if T is mint, mod must be a prime
vector<T> linear_equation(matrix<T> &a, vector<T> &b, bool isDouble) {
    assert(a.h == (int)b.size());
    matrix<T> m(a.h, a.w + 1, 0);
    rep(i, a.h) {
        rep(j, a.w) {
            m[i][j] = a[i][j];
        }
        m[i][a.w] = b[i];
    }
    int rank = GaussJordan(m, true, isDouble);
    
    vector<T> res;
    rep2(row, rank, a.h) {
        if (isDouble) {
            if (abs(m[row][a.w]) > eps) return res;
        } else {
            if (m[row][a.w] != 0) return res;
        }
    }
    
    res.assign(a.w, 0);
    rep(i, rank) {
        rep(j, a.w) {
            if (isDouble) {
                if (abs(m[i][j]) > eps) {
                    res[j] = m[i][a.w];
                    break;
                }
            } else {
                if (m[i][j] != 0) {
                    res[j] = m[i][a.w];
                    break;
                }
            }
        }
    }
    return res;
}
