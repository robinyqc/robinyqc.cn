/**
 * @file P1253 扶苏的问题.cpp
 * @author robinyqc (robinyqc@163.com)
 * @brief Luogu P1253 OI Problem
 * @version 0.1
 * @date 2023-05-11
 */
#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const long long kINTINF=((long long)(1e18))+1;

/**
 * @brief 线段树维护区间加，区间赋值，区间查询最大值。
 */
class SegmentTree {
    public:
        
        /**
         * @brief Construct a new Segment Tree object
         * 
         * @param range_size 维护的值域，比如数组 a[1..n]，那么 range_size=n。
         * @param init_array 初始的值，比如数组 a[1..n]，那么 init_array=a。
         */
        SegmentTree(int range_size,int *init_array) {
            nodes_=new node[range_size<<2]();
            TreeConstruct(init_array,1,size_,1);
        }

        /**
         * @brief 区间赋值
         * 
         * @param left_bound 区间赋值需求的左端点
         * @param right_bound 区间赋值需求的右端点
         * @param assign_val 这个区间成 assign_val
         */
        void RangeAssign(int left_bound,int right_bound,int assign_val) {
            RangeAssignBase(left_bound,right_bound,assign_val,1,size_,1);
        }

        /**
         * @brief 区间加法
         * 
         * @param left_bound 区间增加要求的左端点
         * @param right_bound 区间增加要求的右端点
         * @param delta 区间增加的增量（可以为负数）
         */
        void RangeAdd(int left_bound,int right_bound,int delta) {
            RangeAddBase(left_bound,right_bound,delta,1,size_,1);
        }
        
        /**
         * @brief 区间查询最大值
         * 
         * @param left_bound 所查询区间的左端点
         * @param right_bound 所查询区间的右端点
         * @return long long 查询的区间的最大值
         */
        long long RangeMax(int left_bound,int right_bound) {
            return RangeMaxBase(left_bound,right_bound,1,size_,1);
        }

        /**
         * @brief Destroy the Segment Tree object
         */
        ~SegmentTree() {delete []nodes_;}

    private:

        /// @brief 线段树维护的值域，比如数组 a[1..n]，那么 size_=n。
        int size_;
        
        /**
         * @brief 线段树节点
         * 
         * @note 
         * 由于是加法，这里就不写 is_add 了，只需把 add_lazy_tag 赋 0 即可。  
         * 由于维护的最大值，并不需要一个具体的赋值 lazy tag。  
         * 如果有赋值，max_val 本身就是 tag。  
         * 
         * @attention
         * 注意，如果是新类型的线段树，没有把握，想要代码不出错，  
         * 建议不要省略 tag,并且对每个 tag 开一个 bool 判断 tag 是否作用。 
         * 
         */
        struct node {
            /// @brief 维护的区间内的最大值
            long long max_val; 

            /// @brief 加法 lazy tag
            long long add_lazy_tag; 

            ///@brief 判断整个区间是否全部相等
            ///@details 注意 Assign 优先级大于 Add.
            bool is_same; 

            node():max_val(-kINTINF),add_lazy_tag(0ll),is_same(false) {}
        };
        node *nodes_;
        
        /// @brief 接收子节点信息
        /// @param p 当前节点编号
        void PushUp(int p) {
            nodes_[p].max_val=max(nodes_[p<<1].max_val,nodes_[p<<1|1].max_val);
        }
        /// @brief  下传当前节点懒标记
        /// @param p 当前节点编号
        void PushDown(int p) {
            if(nodes_[p].is_same) {
                nodes_[p<<1].max_val=nodes_[p<<1|1].max_val=nodes_[p].max_val;
                nodes_[p<<1].is_same=nodes_[p<<1|1].is_same=true;
                nodes_[p<<1].add_lazy_tag=nodes_[p<<1|1].add_lazy_tag=0ll;
            }
            else {
                long long add_tag=nodes_[p].add_lazy_tag;
                //注意以下都是 += 而不是 =
                nodes_[p<<1].max_val+=add_tag;
                nodes_[p<<1|1].max_val+=add_tag;
                nodes_[p<<1].add_lazy_tag+=add_tag;
                nodes_[p<<1|1].add_lazy_tag+=add_tag;
            } 
            nodes_[p].add_lazy_tag=0;
        }
        /**
         * @brief 建立初始线段树
         * 
         * @param init_ 初始数组
         * @param l 当前节点对应区间左边界
         * @param r 当前节点对应区间右边界
         * @param p 当前节点编号
         */
        void TreeConstruct(int *init_,int l,int r,int p) {
            if(l==r) {nodes_[p].max_val=init_[l]; return ;}
            int mid=(l+r)>>1;
            TreeConstruct(init_,l,mid,p<<1);
            TreeConstruct(init_,mid+1,r,p<<1|1);
            PushUp(p);
        }

        /**
         * @brief 区间赋值的实现部分
         * 
         * @param L 要赋值的区间的左边界
         * @param R 要赋值的区间的右边界
         * @param val 要赋的值
         * @param l 当前节点对应区间左边界
         * @param r 当前节点对应区间右边界
         * @param p 当前节点编号
         */
        void RangeAssignBase(int L,int R,int val,int l,int r,int p) {
            if(L<=l&&r<=R) {
                nodes_[p].max_val=val;
                nodes_[p].is_same=true;
                nodes_[p].add_lazy_tag=0; //注意区间赋值需要清空加法 tag。
                return ;
            }
            PushDown(p);
            nodes_[p].is_same=false; //不被完全覆盖，不能确定是否完全相等。
            int mid=(l+r)>>1;
            if(L<=mid) RangeAssignBase(L,R,val,l,mid,p<<1);
            if(mid<R) RangeAssignBase(L,R,val,mid+1,r,p<<1|1);
            PushUp(p);
        }

        /**
         * @brief 区间加法的实现部分
         * 
         * @param L 要加的区间的左边界
         * @param R 要加的区间的右边界
         * @param val 要加的增量
         * @param l 当前节点对应区间左边界
         * @param r 当前节点对应区间右边界
         * @param p 当前节点编号
         */
        void RangeAddBase(int L,int R,int delta,int l,int r,int p) {
            if(L<=l&&r<=R) {
                nodes_[p].max_val+=delta;
                nodes_[p].add_lazy_tag+=delta;
                return ;
            }
            PushDown(p);
            nodes_[p].is_same=false;
            int mid=(l+r)>>1;
            if(L<=mid) RangeAddBase(L,R,delta,l,mid,p<<1);
            if(mid<R) RangeAddBase(L,R,delta,mid+1,r,p<<1|1);
            PushUp(p);
        }

        /**
         * @brief 区间查询的实现部分
         * 
         * @param L 要查询的区间左边界
         * @param R 要查询的区间右边界
         * @param l 当前节点对应的区间的左边界
         * @param r 当前节点对应的区间的右边界
         * @param p 当前节点编号
         * @return long long 当前区间对应的最大值
         */
        long long RangeMaxBase(int L,int R,int l,int r,int p) {
            if(L<=l&&r<=R) return nodes_[p].max_val;
            PushDown(p);
            int mid=(l+r)>>1;
            long long ret=-kINTINF;
            if(L<=mid) ret=RangeMaxBase(L,R,l,mid,p<<1);
            if(mid<R) ret=max(ret,RangeMaxBase(L,R,mid+1,r,p<<1|1));
            return ret;
        }
};

int a[1000005];

signed main() {
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    SegmentTree *segtree=new SegmentTree(n,a);
    int op,l,r,x;
    while(q--) {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) {
            scanf("%d",&x);
            segtree->RangeAssign(l,r,x);
        }
        if(op==2) {
            scanf("%d",&x);
            segtree->RangeAdd(l,r,x);
        }
        if(op==3) printf("%lld\n",segtree->RangeMax(l,r));
    }
    delete segtree;
    return 0;
}