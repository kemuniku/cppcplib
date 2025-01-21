#include <climits>
long long ofmul(long long x, long long y) {
    long long z;
    if (__builtin_mul_overflow(x, y, &z)) {
        if(((x > 0LL) == (y > 0LL))){
            return LLONG_MAX;
        }else{
            return LLONG_MIN;
        }
    } else {
        return z;
    }
}

long long ofadd(long long x, long long y) {
    long long z;
    if (__builtin_add_overflow(x, y, &z)) {
        if(((x > 0LL))){
            return LLONG_MAX;
        }else{
            return LLONG_MIN;
        }
    } else {
        return z;
    }
}