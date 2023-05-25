#include<cstdio>
#include<cctype>
#include<cstring>
using namespace std;
namespace myio{
    char buf[1<<15],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
    #define getchar() (p1==p2&&(p2=(p1=buf)+\
fread(buf,1,1<<15,stdin),p1==p2)?EOF:*p1++)
    int read_int() {
        int x=0; char ch;
        while(!std::isdigit(ch=getchar()));
        do x=(x<<1)+(x<<3)+ch-'0';
        while(std::isdigit(ch=getchar()));
        return x;
    }
    #undef getchar
    template<typename T>
    void PRINT(T x) {
        if(x>9) PRINT(x/10);
        *O++=x%10+'0';
    }

    void end_print() {fwrite(obuf,O-obuf,1,stdout);}
    template<typename T>
    void print_int(T x,char endch) {
        PRINT(x);
        *O++=endch;
    }
}
#define LL long long
const int P=998244353;
enum InitialMagic {kNihility,kOrigin};
enum MagicDivision {kActivate,kEnhance,kRelease};
enum MagicElementType {kAqua,kFlame,kTerra};
void Amod(int &x) {if(x>P) x-=P;}
int Bmod(int x) {if(x>P) return x-P; return x;}
int tmp_mat[16];
class Matrix {
    public:
        Matrix() {
            member[1]=member[2]=member[3]=member[4]=member[6]=member[7]=
            member[8]=member[9]=member[11]=member[12]=member[13]=member[14]=0;
            member[0]=member[5]=member[10]=member[15]=1; //0,0; 1,1; 2,2; 3,3
        }
        void reset() {
            member[1]=member[2]=member[3]=member[4]=member[6]=member[7]=
            member[8]=member[9]=member[11]=member[12]=member[13]=member[14]=0;
            member[0]=member[5]=member[10]=member[15]=1; //0,0; 1,1; 2,2; 3,3
        }
        void set(MagicDivision division,MagicElementType element_type,
            int enhance_value=-1) {
            reset();
            if(division==kActivate) {
                if(element_type==kAqua) member[1]=1; //0,1
                if(element_type==kFlame) member[6]=1; //1,2
                if(element_type==kTerra) member[8]=1; //2,0
            }
            if(division==kEnhance) {
                if(element_type==kAqua) member[3]=enhance_value; //0,3
                if(element_type==kFlame) member[5]=enhance_value; //1,1
                if(element_type==kTerra) 
                    member[10]=0,member[11]=enhance_value; //2,2; 2,3
            }
        }
        int member[16];
};
long long now_tar;
void operator *=(Matrix& source,Matrix& target) {
    memset(tmp_mat,0,64);
	if(target.member[0]!=0) {
		now_tar=target.member[0];
		Amod(tmp_mat[0]+=now_tar*source.member[0]%P);
		Amod(tmp_mat[1]+=now_tar*source.member[1]%P);
		Amod(tmp_mat[2]+=now_tar*source.member[2]%P);
		Amod(tmp_mat[3]+=now_tar*source.member[3]%P);
	}
	if(target.member[1]!=0) {
		now_tar=target.member[1];
		Amod(tmp_mat[0]+=now_tar*source.member[4]%P);
		Amod(tmp_mat[1]+=now_tar*source.member[5]%P);
		Amod(tmp_mat[2]+=now_tar*source.member[6]%P);
		Amod(tmp_mat[3]+=now_tar*source.member[7]%P);
	} 
	if(target.member[2]!=0) {
		now_tar=target.member[2];
		Amod(tmp_mat[0]+=now_tar*source.member[8]%P);
		Amod(tmp_mat[1]+=now_tar*source.member[9]%P);
		Amod(tmp_mat[2]+=now_tar*source.member[10]%P);
		Amod(tmp_mat[3]+=now_tar*source.member[11]%P);
	} 
	if(target.member[3]!=0) {
		now_tar=target.member[3];
		Amod(tmp_mat[0]+=now_tar*source.member[12]%P);
		Amod(tmp_mat[1]+=now_tar*source.member[13]%P);
		Amod(tmp_mat[2]+=now_tar*source.member[14]%P);
		Amod(tmp_mat[3]+=now_tar*source.member[15]%P);
	} 
	if(target.member[4]!=0) {
		now_tar=target.member[4];
		Amod(tmp_mat[4]+=now_tar*source.member[0]%P);
		Amod(tmp_mat[5]+=now_tar*source.member[1]%P);
		Amod(tmp_mat[6]+=now_tar*source.member[2]%P);
		Amod(tmp_mat[7]+=now_tar*source.member[3]%P);
	}
	if(target.member[5]!=0) {
		now_tar=target.member[5];
		Amod(tmp_mat[4]+=now_tar*source.member[4]%P);
		Amod(tmp_mat[5]+=now_tar*source.member[5]%P);
		Amod(tmp_mat[6]+=now_tar*source.member[6]%P);
		Amod(tmp_mat[7]+=now_tar*source.member[7]%P);
	} 
	if(target.member[6]!=0) {
		now_tar=target.member[6];
		Amod(tmp_mat[4]+=now_tar*source.member[8]%P);
		Amod(tmp_mat[5]+=now_tar*source.member[9]%P);
		Amod(tmp_mat[6]+=now_tar*source.member[10]%P);
		Amod(tmp_mat[7]+=now_tar*source.member[11]%P);
	} 
	if(target.member[7]!=0) {
		now_tar=target.member[7];
		Amod(tmp_mat[4]+=now_tar*source.member[12]%P);
		Amod(tmp_mat[5]+=now_tar*source.member[13]%P);
		Amod(tmp_mat[6]+=now_tar*source.member[14]%P);
		Amod(tmp_mat[7]+=now_tar*source.member[15]%P);
	} 
	if(target.member[8]!=0) {
		now_tar=target.member[8];
		Amod(tmp_mat[8]+=now_tar*source.member[0]%P);
		Amod(tmp_mat[9]+=now_tar*source.member[1]%P);
		Amod(tmp_mat[10]+=now_tar*source.member[2]%P);
		Amod(tmp_mat[11]+=now_tar*source.member[3]%P);
	}
	if(target.member[9]!=0) {
		now_tar=target.member[9];
		Amod(tmp_mat[8]+=now_tar*source.member[4]%P);
		Amod(tmp_mat[9]+=now_tar*source.member[5]%P);
		Amod(tmp_mat[10]+=now_tar*source.member[6]%P);
		Amod(tmp_mat[11]+=now_tar*source.member[7]%P);
	} 
	if(target.member[10]!=0) {
		now_tar=target.member[10];
		Amod(tmp_mat[8]+=now_tar*source.member[8]%P);
		Amod(tmp_mat[9]+=now_tar*source.member[9]%P);
		Amod(tmp_mat[10]+=now_tar*source.member[10]%P);
		Amod(tmp_mat[11]+=now_tar*source.member[11]%P);
	} 
	if(target.member[11]!=0) {
		now_tar=target.member[11];
		Amod(tmp_mat[8]+=now_tar*source.member[12]%P);
		Amod(tmp_mat[9]+=now_tar*source.member[13]%P);
		Amod(tmp_mat[10]+=now_tar*source.member[14]%P);
		Amod(tmp_mat[11]+=now_tar*source.member[15]%P);
	} 
	if(target.member[12]!=0) {
		now_tar=target.member[12];
		Amod(tmp_mat[12]+=now_tar*source.member[0]%P);
		Amod(tmp_mat[13]+=now_tar*source.member[1]%P);
		Amod(tmp_mat[14]+=now_tar*source.member[2]%P);
		Amod(tmp_mat[15]+=now_tar*source.member[3]%P);
	}
	if(target.member[13]!=0) {
		now_tar=target.member[13];
		Amod(tmp_mat[12]+=now_tar*source.member[4]%P);
		Amod(tmp_mat[13]+=now_tar*source.member[5]%P);
		Amod(tmp_mat[14]+=now_tar*source.member[6]%P);
		Amod(tmp_mat[15]+=now_tar*source.member[7]%P);
	} 
	if(target.member[14]!=0) {
		now_tar=target.member[14];
		Amod(tmp_mat[12]+=now_tar*source.member[8]%P);
		Amod(tmp_mat[13]+=now_tar*source.member[9]%P);
		Amod(tmp_mat[14]+=now_tar*source.member[10]%P);
		Amod(tmp_mat[15]+=now_tar*source.member[11]%P);
	} 
	if(target.member[15]!=0) {
		now_tar=target.member[15];
		Amod(tmp_mat[12]+=now_tar*source.member[12]%P);
		Amod(tmp_mat[13]+=now_tar*source.member[13]%P);
		Amod(tmp_mat[14]+=now_tar*source.member[14]%P);
		Amod(tmp_mat[15]+=now_tar*source.member[15]%P);
	} 
    memcpy(source.member,tmp_mat,64);
}
int tmp_vec[4];
class Vector {
    public:
        Vector() {member[0]=member[1]=member[2]=0; member[3]=1;}
        void set(int aqua_energy,int flame_energy,int terra_energy) {
            member[0]=aqua_energy,member[1]=flame_energy,member[2]=terra_energy;
        }
        int& operator [](int pos) {return member[pos];}
        void operator *=(Matrix& target) {
            memset(tmp_vec,0,16);
            Amod(tmp_vec[0]+=((LL)member[0])*target.member[0]%P);
            Amod(tmp_vec[0]+=((LL)member[1])*target.member[1]%P);
            Amod(tmp_vec[0]+=((LL)member[2])*target.member[2]%P);
            Amod(tmp_vec[0]+=((LL)member[3])*target.member[3]%P);
            Amod(tmp_vec[1]+=((LL)member[0])*target.member[4]%P);
            Amod(tmp_vec[1]+=((LL)member[1])*target.member[5]%P);
            Amod(tmp_vec[1]+=((LL)member[2])*target.member[6]%P);
            Amod(tmp_vec[1]+=((LL)member[3])*target.member[7]%P);
            Amod(tmp_vec[2]+=((LL)member[0])*target.member[8]%P);
            Amod(tmp_vec[2]+=((LL)member[1])*target.member[9]%P);
            Amod(tmp_vec[2]+=((LL)member[2])*target.member[10]%P);
            Amod(tmp_vec[2]+=((LL)member[3])*target.member[11]%P);
            Amod(tmp_vec[3]+=((LL)member[0])*target.member[12]%P);
            Amod(tmp_vec[3]+=((LL)member[1])*target.member[13]%P);
            Amod(tmp_vec[3]+=((LL)member[2])*target.member[14]%P);
            Amod(tmp_vec[3]+=((LL)member[3])*target.member[15]%P);
            memcpy(member,tmp_vec,16);
        }
        void AssignSum(Vector& aa,Vector& bb) {
            member[0]=Bmod(aa[0]+bb[0]); member[1]=Bmod(aa[1]+bb[1]);
            member[2]=Bmod(aa[2]+bb[2]); member[3]=Bmod(aa[3]+bb[3]);
        }
        int member[4];
};

int aqua_ans,flame_ans,terra_ans;
int n,m,A[250005],B[250005],C[250005];
class SegmentTree {
    public:
        SegmentTree(int range_size)
            :size_(range_size),temp_mul_mat() {
            nodes_=new node[range_size<<2] ();
            TreeConstruct(1,size_,1);
        }
        void RangeMultiply(int L,int R,MagicDivision division,
            MagicElementType type,int val=-1) {
            temp_mul_mat.set(division,type,val);
            RangeMultiplyBase(L,R,1,size_,1);
        }
        void RangeSum(int L,int R) {
            return RangeSumBase(L,R,1,size_,1);
        }
        ~SegmentTree() {delete []nodes_;}
    private:
        int size_;
        Matrix temp_mul_mat;
        struct node {
            Vector energy;
            Matrix multiply_lazy_tag;
            node():energy(),multiply_lazy_tag() {}
        };
        node *nodes_;
        void TreeConstruct(int l,int r,int p) {
            if(l==r) {nodes_[p].energy.set(A[l],B[l],C[l]); return ;}
            int mid=(l+r)>>1;
            TreeConstruct(l,mid,p<<1);
            TreeConstruct(mid+1,r,p<<1|1);
            nodes_[p].energy.AssignSum(nodes_[p<<1].
                energy,nodes_[p<<1|1].energy);
        }
        void RangeMultiplyBase(int L,int R,int l,int r,int p) {
            if(L<=l&&r<=R) {
                nodes_[p].energy*=temp_mul_mat;
                nodes_[p].multiply_lazy_tag*=temp_mul_mat;
                return ;
            }
            nodes_[p<<1].energy*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1|1].energy*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1].multiply_lazy_tag*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1|1].multiply_lazy_tag*=nodes_[p].multiply_lazy_tag;
            nodes_[p].multiply_lazy_tag.reset();
            int mid=(l+r)>>1;
            if(L<=mid) RangeMultiplyBase(L,R,l,mid,p<<1);
            if(mid<R) RangeMultiplyBase(L,R,mid+1,r,p<<1|1);
            nodes_[p].energy.AssignSum(nodes_[p<<1].
                energy,nodes_[p<<1|1].energy);
        }
        void RangeSumBase(int L,int R,int l,int r,int p) {
            if(L<=l&&r<=R) {
                aqua_ans=(aqua_ans+nodes_[p].energy[0])%P;
                flame_ans=(flame_ans+nodes_[p].energy[1])%P;
                terra_ans=(terra_ans+nodes_[p].energy[2])%P;
                return ;
            }
            nodes_[p<<1].energy*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1|1].energy*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1].multiply_lazy_tag*=nodes_[p].multiply_lazy_tag;
            nodes_[p<<1|1].multiply_lazy_tag*=nodes_[p].multiply_lazy_tag;
            nodes_[p].multiply_lazy_tag.reset();
            int mid=(l+r)>>1;
            if(L<=mid) RangeSumBase(L,R,l,mid,p<<1);
            if(mid<R) RangeSumBase(L,R,mid+1,r,p<<1|1);
        }
};



signed main() {
    n=myio::read_int();
    for(int i=1;i<=n;i++) {
        A[i]=myio::read_int();
        B[i]=myio::read_int();
        C[i]=myio::read_int();
    }
    SegmentTree *segtree=new SegmentTree(n);
    int op,l,r,v;
    m=myio::read_int();
    while(m--) {
        op=myio::read_int();
        l=myio::read_int();
        r=myio::read_int();
        if(op==1) segtree->RangeMultiply(l,r,kActivate,kAqua);
        if(op==2) segtree->RangeMultiply(l,r,kActivate,kFlame);
        if(op==3) segtree->RangeMultiply(l,r,kActivate,kTerra);
        if(op>3&&op<=6) {
            v=myio::read_int();
            if(op==4) segtree->RangeMultiply(l,r,kEnhance,kAqua,v);
            if(op==5) segtree->RangeMultiply(l,r,kEnhance,kFlame,v);
            if(op==6) segtree->RangeMultiply(l,r,kEnhance,kTerra,v);
        }
        if(op==7) {
            aqua_ans=flame_ans=terra_ans=0;
            segtree->RangeSum(l,r);
            myio::print_int(aqua_ans,' ');
            myio::print_int(flame_ans,' ');
            myio::print_int(terra_ans,'\n');
        }
    }
    myio::end_print();
    return 0;
}