#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

#define LL long long

const int P=998244353;

/// @brief 初始矩阵种类
/// @details 中二之魂爆发！世界尽头的魔法：虚无魔法，本源魔法！
///                                     ⬇       ⬇
///          注：                      空矩阵   单位矩阵
enum InitialMagic {kNihility,kOrigin};

/// @brief 魔法种类
/// @details 中二之魂爆发！激活魔法，强化魔法，释放魔法，还原魔法！
enum MagicDivision {kActivate,kEnhance,kRelease};

/// @brief 魔法元素种类
/// @details 中二之魂爆发！水元素，火元素，土元素，和虚空元素！
enum MagicElementType {kAqua,kFlame,kTerra};

int integer_pool[20005005];
int *integer_pool_pointer=integer_pool;
int* IntegerAllocte(int size__) {
    int *tmp=integer_pool_pointer;
    integer_pool_pointer+=size__;
    return tmp;
}

int *int_pointer_pool[4000505];
int **int_pointer_pool_pointer=int_pointer_pool;
int** IntPointerAllocate(int size__) {
    int **tmp=int_pointer_pool_pointer;
    int_pointer_pool_pointer+=size__;
    return tmp;
}

int tmp_mat[4][4];

/// @brief 4*4 矩阵。
/// @details 由于本题是一个 4 维向量，因此只需要 4*4 的方阵即可。
///          这个方阵对应乘的向量形式是:
///                                 -- --
///                                 | A |
///                                 | B |
///                                 | C |
///                                 | 1 |
///                                 -- --
class Matrix {
    public:
        /// @brief 默认构造函数，构造一个空/单位矩阵。
        /// @param init 初始魔法种类
        Matrix(InitialMagic init) {
            member=IntPointerAllocate(4);
            for(int i=0;i<4;i++) member[i]=IntegerAllocte(4);
            if(init==kOrigin) for(int i=0;i<4;i++) member[i][i]=1;
        }
        
        /**
         * @brief 设置矩阵类型
         * 
         * @param division 魔法种类
         * @param element_type 元素种类
         * @param enhance_value 如果不是增强魔法，请不要填，默认为 -1.
         *                      如果是，填入增强值v.
         */
        void set(MagicDivision division,MagicElementType element_type,
            int enhance_value=-1) {
            for(int i=0;i<4;i++) for(int j=0;j<4;j++) member[i][j]=0;
            for(int i=0;i<4;i++) member[i][i]=1;
            if(division==kActivate) {
                int tmp_type=element_type; //方便下面计算。
                member[tmp_type][(tmp_type+1)%3]=1;
            }
            if(division==kEnhance) {
                if(element_type==kAqua) member[0][3]=enhance_value;
                if(element_type==kFlame) member[1][1]=enhance_value;
                if(element_type==kTerra) 
                    member[2][2]=0,member[2][3]=enhance_value;
            }
        }

        void reset() {
            for(int i=0;i<4;i++) for(int j=0;j<4;j++) member[i][j]=0;
            for(int i=0;i<4;i++) member[i][i]=1;
        }

        int* operator [](int pos) {return member[pos];}

        void operator *=(Matrix& target) const {
            memset(tmp_mat,0,sizeof(tmp_mat));
            for(int i=0;i<4;i++) for(int k=0;k<4;k++) 
                if(target[i][k]!=0) for(int j=0;j<4;j++) 
                    (tmp_mat[i][j]+=(((LL)target[i][k])*member[k][j])%P)%=P;//
            for(int i=0;i<4;i++)for(int j=0;j<4;j++) member[i][j]=tmp_mat[i][j];
        }

        void print() {
            for(int i=0;i<4;i++) {
                for(int j=0;j<4;j++) cout<<member[i][j]<<' ';
                cout<<endl;
            } cout<<endl;
        }

    private:
        int **member;
};

int tmp_vec[4];

/// @brief 4 维向量
/// @details 其实向量也算矩阵。但是由于笔者太懒不想单独设置和判断矩阵的宽和高,
///          就把向量和矩阵分开写了。其实没有太大影响。
class Vector {
    public:
        /// @brief 默认构造一个空的向量。
        Vector() {member=IntegerAllocte(4); member[3]=1;}

        /**
         * @brief 设置向量
         * 
         * @param aqua_energy 水元素初始能量
         * @param flame_energy 火元素初始能量
         * @param terra_energy 土元素初始能量
         */
        void set(int aqua_energy,int flame_energy,int terra_energy) {
            member[0]=aqua_energy,member[1]=flame_energy,member[2]=terra_energy;
        }

        int& operator [](int pos) {return member[pos];}

        void operator *=(Matrix& target) {
            memset(tmp_vec,0,sizeof(tmp_vec));
            for(int i=0;i<4;i++) for(int j=0;j<4;j++) 
                (tmp_vec[i]+=((LL)member[j])*target[i][j]%P)%=P;
            for(int i=0;i<4;i++) member[i]=tmp_vec[i]; //哼啊啊啊啊！
        }

        /// @brief 赋给当前向量 aa+bb，节省空间。
        /// @param aa 第一个加数
        /// @param bb 第二个加数
        void AssignSum(Vector& aa,Vector& bb) {
            for(int i=0;i<4;i++) member[i]=(aa[i]+bb[i])%P;
        }
        
        void print() {
            for(int i=0;i<4;i++) cout<<member[i]<<' ';
            cout<<endl;
        }

    private:
        int* member;
};

class SegmentTree {
    public:

        SegmentTree(int range_size,int *aqua,int *flame,int *terra)
            :size_(range_size),temp_mul_mat(kOrigin) {
            nodes_=new node[range_size<<2] ();
            TreeConstruct(aqua,flame,terra,1,size_,1);
        }

        void RangeMultiply(int L,int R,MagicDivision division,
            MagicElementType type,int val=-1) {
            temp_mul_mat.set(division,type,val);
            RangeMultiplyBase(L,R,1,size_,1);
        }

        void RangeSum(int L,int R,int &a,int &b,int &c) {
            return RangeSumBase(L,R,1,size_,1,a,b,c);
        }

        ~SegmentTree() {delete []nodes_;}

    private:

        int size_;

        Matrix temp_mul_mat;

        struct node {
            Vector energy;
            Matrix multiply_lazy_tag;
            /// @details 这个构造函数应当使用初始化成员列表节省空间。
            node():energy(),multiply_lazy_tag(kOrigin) {}
        };
        node *nodes_;

        void PushUp(int p) {
            nodes_[p].energy.AssignSum(nodes_[p<<1].
                energy,nodes_[p<<1|1].energy);
        }

        void PushDown(int p) {
            // nodes_[p].multiply_lazy_tag.print();
            nodes_[p<<1].energy*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1|1].energy*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1].multiply_lazy_tag*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1|1].multiply_lazy_tag*=nodes_[p].multiply_lazy_tag;
            nodes_[p].multiply_lazy_tag.reset();
        }

        void TreeConstruct(int *A,int *B,int *C,int l,int r,int p) {
            if(l==r) {nodes_[p].energy.set(A[l],B[l],C[l]); return ;}
            int mid=(l+r)>>1;
            TreeConstruct(A,B,C,l,mid,p<<1);
            TreeConstruct(A,B,C,mid+1,r,p<<1|1);
            PushUp(p);
        }

        void RangeMultiplyBase(int L,int R,int l,int r,int p) {
            if(L<=l&&r<=R) {
                nodes_[p].energy*=temp_mul_mat;
                nodes_[p].multiply_lazy_tag*=temp_mul_mat;
                return ;
            }
            PushDown(p);
            int mid=(l+r)>>1;
            if(L<=mid) RangeMultiplyBase(L,R,l,mid,p<<1);
            if(mid<R) RangeMultiplyBase(L,R,mid+1,r,p<<1|1);
            PushUp(p);
        }

        void RangeSumBase(int L,int R,int l,int r,int p,int &a,int &b,int &c) {
            if(L<=l&&r<=R) {
                a=(a+nodes_[p].energy[0])%P;
                b=(b+nodes_[p].energy[1])%P;
                c=(c+nodes_[p].energy[2])%P;
                return ;
            }
            PushDown(p);
            int mid=(l+r)>>1;
            if(L<=mid) RangeSumBase(L,R,l,mid,p<<1,a,b,c);
            if(mid<R) RangeSumBase(L,R,mid+1,r,p<<1|1,a,b,c);
        }

};


int n,m,A[250005],B[250005],C[250005];
signed main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d%d",A+i,B+i,C+i);
    SegmentTree *segtree=new SegmentTree(n,A,B,C);
    int op,l,r,v,a,b,c;
    scanf("%d",&m);
    while(m--) {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1) segtree->RangeMultiply(l,r,kActivate,kAqua);
        if(op==2) segtree->RangeMultiply(l,r,kActivate,kFlame);
        if(op==3) segtree->RangeMultiply(l,r,kActivate,kTerra);
        if(op>3&&op<=6) {
            scanf("%d",&v);
            if(op==4) segtree->RangeMultiply(l,r,kEnhance,kAqua,v);
            if(op==5) segtree->RangeMultiply(l,r,kEnhance,kFlame,v);
            if(op==6) segtree->RangeMultiply(l,r,kEnhance,kTerra,v);
        }
        if(op==7) {
            a=0,b=0,c=0;
            segtree->RangeSum(l,r,a,b,c);
            printf("%d %d %d\n",a,b,c);
        }
        
    }
    delete segtree;
    return 0;
}
