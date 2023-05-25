#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

class SegmentTree {
    public:
        SegmentTree(int range_size,int *init_array,int modulo) {
            size_=range_size,modulo_=(long long)modulo;
            nodes_=new node[size_<<2]();
            TreeConstruct(init_array,1,size_,1);
        }

        void RangeAdd(int L,int R,int delta){RangeAddBase(L,R,delta,1,size_,1);}

        void RangeMultiply(int L,int R,int times) {
            RangeMultiplyBase(L,R,times,1,size_,1);
        }

        long long RangeSum(int L,int R) {return RangeSumBase(L,R,1,size_,1);}
    private:

        int size_;

        long long modulo_;
        
        struct node {
            long long range_sum;
            long long add_lazy_tag;
            long long mul_lazy_tag;
            node():range_sum(0ll),add_lazy_tag(0ll),mul_lazy_tag(1ll) {}
        };
        node *nodes_;

        void PushUp(int p) {
            nodes_[p].range_sum=nodes_[p<<1].range_sum+nodes_[p<<1|1].range_sum;
        }

        void PushDown(int p,int l,int r) {
            long long add=nodes_[p].add_lazy_tag,mul=nodes_[p].mul_lazy_tag;
            if(add==0ll&&mul==1ll) return ;
            int mid=(l+r)>>1;
            ///由于我们存 add_lazy_tag 的时候并没有存区间长度，因此在此处应该乘上
            ///对应区间长度。正确性可由乘法分配律证明。
            nodes_[p<<1].range_sum=(nodes_[p<<1].range_sum*mul%modulo_+
                add*(mid-l+1)%modulo_)%modulo_;
            nodes_[p<<1|1].range_sum=(nodes_[p<<1|1].range_sum*mul%modulo_+
                add*(r-mid)%modulo_)%modulo_;
            
            ///更新 lazy tag。
            (nodes_[p<<1].mul_lazy_tag*=mul)%=modulo_;
            (nodes_[p<<1].add_lazy_tag*=mul)%=modulo_;
            (nodes_[p<<1].add_lazy_tag+=add)%=modulo_;
            (nodes_[p<<1|1].mul_lazy_tag*=mul)%=modulo_;
            (nodes_[p<<1|1].add_lazy_tag*=mul)%=modulo_;
            (nodes_[p<<1|1].add_lazy_tag+=add)%=modulo_;

            nodes_[p].add_lazy_tag=0ll,nodes_[p].mul_lazy_tag=1ll;
        }

        void TreeConstruct (int *init_,int l,int r,int p) {
            if(l==r) {nodes_[p].range_sum=init_[l]; return ;}
            int mid=(l+r)>>1;
            TreeConstruct(init_,l,mid,p<<1);
            TreeConstruct(init_,mid+1,r,p<<1|1);
            PushUp(p);
        }

        void RangeAddBase(int L,int R,int delta,int l,int r,int p) {
            if(L<=l&&r<=R) {
                (nodes_[p].range_sum+=((long long)delta)*(r-l+1))%=modulo_;
                (nodes_[p].add_lazy_tag+=delta)%=modulo_;
                return ;
            }
            PushDown(p,l,r);
            int mid=(l+r)>>1;
            if(L<=mid) RangeAddBase(L,R,delta,l,mid,p<<1);
            if(mid<R) RangeAddBase(L,R,delta,mid+1,r,p<<1|1);
            PushUp(p);
        }

        void RangeMultiplyBase(int L,int R,int times,int l,int r,int p) {
            if(L<=l&&r<=R) {
                (nodes_[p].range_sum*=times)%=modulo_;
                // cout<<l<<' '<<r<<endl;
                (nodes_[p].add_lazy_tag*=times)%=modulo_;
                (nodes_[p].mul_lazy_tag*=times)%=modulo_;
                return ;
            }
            PushDown(p,l,r);
            int mid=(l+r)>>1;
            if(L<=mid) RangeMultiplyBase(L,R,times,l,mid,p<<1);
            if(mid<R) RangeMultiplyBase(L,R,times,mid+1,r,p<<1|1);
            PushUp(p);
        }

        long long RangeSumBase(int L,int R,int l,int r,int p) {
            if(L<=l&&r<=R) return nodes_[p].range_sum;
            PushDown(p,l,r);
            int mid=(l+r)>>1;
            long long ret=0;
            if(L<=mid) ret=RangeSumBase(L,R,l,mid,p<<1);
            if(mid<R) ret+=RangeSumBase(L,R,mid+1,r,p<<1|1);
            return ret%modulo_;
        }

};

int n,m,p;
int a[100005];

signed main() {
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    SegmentTree *segtree=new SegmentTree(n,a,p);
    int op,x,y,z;
    while(m--) {
        scanf("%d%d%d",&op,&x,&y);
        if(op==1) {
            scanf("%d",&z);
            segtree->RangeMultiply(x,y,z);
        }
        if(op==2) {
            scanf("%d",&z);
            segtree->RangeAdd(x,y,z);
        }
        if(op==3) printf("%lld\n",segtree->RangeSum(x,y));
    }
    delete segtree;
    return 0;
}