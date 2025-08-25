#include <vector>
#include <cassert>

class UnionFind{
    std::vector<int> arr; // rootならば-(連結成分のサイズ) rootでない時は親ノードのid
    public:
        int n;
        int cnt;
        UnionFind(int N) : n(N),cnt(N),arr(N,-1){}

        int root(int x){
            assert(0 <= x && x < n);
            if(arr[x] < 0) return x;
            return arr[x] = root(arr[x]);
        }

        bool issame(int x,int y){
            assert(0 <= x && x < n);
            assert(0 <= y && y < n);
            return root(x) == root(y);
        }

        int unite(int x,int y){
            // xとyをつなぐ。新たな連結成分のrootを返す。
            assert(0 <= x && x < n);
            assert(0 <= y && y < n);
            x = root(x);y = root(y);
            if(x == y) return x;
            if(arr[x] > arr[y]) std::swap(x,y);
            arr[x] += arr[y];
            arr[y] = x;
            cnt--;
            return x;
        }

        int size(int x){
            // 頂点xが含まれる連結成分のサイズを返す。
            assert(0 <= x && x < n);
            x = root(x);
            return -arr[x];
        }
};