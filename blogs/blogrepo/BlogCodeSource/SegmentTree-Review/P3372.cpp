#include<cstdio>

/// @brief 一颗普普通通加法线段树
class SegmentTree {
    public:
        /**
         * @brief Construct a new Segment Tree object
         * 
         * @param range_size 维护序列大小
         * @param init_array 维护的初始序列
         */
        SegmentTree(int range_size,int *init_array) {
            //这里注意了！最好开 4 倍结点避免爆空间。
            nodes_=new node[range_size<<2]();
            size_=range_size;
            TreeInitialConstruct(init_array,1,size_,1);
        }

        /**
         * @brief 示例：区间加操作
         * 
         * @param L 需要修改的范围左端点
         * @param R 需要修改的范围右端点 
         * @param delta 增量
         */
        void RangeAdd(int L,int R,int delta) {
            RangeAddBase(L,R,delta,1,size_,1);
        }

        /// @brief 示例：区间查询区间和（内部成员函数）
        /// @param L 需要查询的范围左端点
        /// @param R 需要查询的范围右端点 
        long long RangeSum(int L,int R) {
            return RangeQueryBase(L,R,1,size_,1);
        }

        /// @brief Destroy the Segment Tree object
        ~SegmentTree() {delete []nodes_;}
    private:
        
        int size_;

        struct node {
            long long data;
            long long add_lazy_tag;
            node() {data=add_lazy_tag=0ll;}
        };
        node* nodes_;

        /// @brief 示例：维护区间和
        void PushUp(int p) {
            nodes_[p].data=nodes_[p<<1].data+nodes_[p<<1|1].data;
        }

        /// @brief 示例：区间增加的 push down
        /// @note l,r 并不一定要有，只是这个示例需要。
        void PushDown(int p,int l,int r) {
            long long &tag=nodes_[p].add_lazy_tag;
            int mid=(l+r)>>1;
            nodes_[p<<1].add_lazy_tag+=tag;
            nodes_[p<<1].data+=tag*(mid-l+1);
            nodes_[p<<1|1].add_lazy_tag+=tag;
            nodes_[p<<1|1].data+=tag*(r-mid);
            tag=0;
        }

        /// @brief 示例：区间加法的建树
        /// @param init_array_ 初始的序列
        void TreeInitialConstruct(int *init_array_,int l,int r,int p) {
            if(l==r) {nodes_[p].data=init_array_[l]; return ;}
            int mid=(l+r)>>1;
            TreeInitialConstruct(init_array_,l,mid,p<<1);
            TreeInitialConstruct(init_array_,mid+1,r,p<<1|1);
            PushUp(p);
        }

        /// @brief 示例：区间查询区间和（内部成员函数）
        /// @param L 需要查询的范围左端点
        /// @param R 需要查询的范围右端点 
        long long RangeQueryBase(int L,int R,int l,int r,int p) {
            //这一条保证了最多分成 O(log n) 个节点
            if(L<=l&&r<=R) return nodes_[p].data;
            //注意这里有 push down 哦！
            PushDown(p,l,r);
            int mid=(l+r)>>1;
            long long ret=0;
            if(L<=mid) ret=RangeQueryBase(L,R,l,mid,p<<1);
            if(mid<R) ret+=RangeQueryBase(L,R,mid+1,r,p<<1|1);
            return ret;
        }

        /**
         * @brief 示例：区间加操作（内部成员函数）
         * 
         * @param L 需要修改的范围左端点
         * @param R 需要修改的范围右端点 
         * @param delta 增量
         */
        void RangeAddBase(int L,int R,int delta,int l,int r,int p) {
            if(L<=l&&r<=R) {
                nodes_[p].data+=(r-l+1)*delta;
                nodes_[p].add_lazy_tag+=delta;
                return ;
            }
            PushDown(p,l,r); //注意 push down！
            int mid=(l+r)>>1;
            if(L<=mid) RangeAddBase(L,R,delta,l,mid,p<<1);
            if(mid<R) RangeAddBase(L,R,delta,mid+1,r,p<<1|1);
            PushUp(p);
        }
};

int n,m,a[100005];

signed main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    SegmentTree *segtree=new SegmentTree(n,a);
    int op,x,y,k;
    while(m--) {
        scanf("%d%d%d",&op,&x,&y);
        if(op==1) {
            scanf("%d",&k);
            segtree->RangeAdd(x,y,k);
        }
        else printf("%lld\n",segtree->RangeSum(x,y));
    }
    delete segtree;
    return 0;
}