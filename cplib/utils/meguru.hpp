#include <cmath>
template<typename F> long long meguru_bisect(long long ok, long long ng, F is_ok){
    while(std::abs(ok - ng) > 1){
        long long mid = (ok + ng) / 2;
        if(is_ok(mid)){
            ok = mid;
        }else{
            ng = mid;
        }
    }
    return ok;
}