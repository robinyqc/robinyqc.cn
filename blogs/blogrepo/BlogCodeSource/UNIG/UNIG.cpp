/**
 * @author robinyqc (robinyqc@163.com)
 * @brief random uniform nonredundant sequence generation
 * @link https://www.luogu.com.cn/blog/robinyqc-blog/sui-ji-sheng-cheng-yi-ge-shang-sheng-xu-lie
 * also on codeforces.
 */
#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
#include<random>
#include<limits>
#include<cmath>
#include<bitset>

const int MAXLEN=1<<26;

/// @brief LSD radix sorting impl
namespace RadixSort {

namespace __RadixSort {
int cnt[32][256],n,cc=0;
template<typename Iter1,typename Iter2> 
void __radix_sort(Iter1 a,Iter2 b,int len) {
    int tim=n>>3,dt=len<<3;
    auto nw=a+n-1;
    while(tim--){
        b[--cnt[len][nw[0]>>dt&255]]=nw[0];
        b[--cnt[len][nw[-1]>>dt&255]]=nw[-1];
        b[--cnt[len][nw[-2]>>dt&255]]=nw[-2];
        b[--cnt[len][nw[-3]>>dt&255]]=nw[-3];
        b[--cnt[len][nw[-4]>>dt&255]]=nw[-4];
        b[--cnt[len][nw[-5]>>dt&255]]=nw[-5];
        b[--cnt[len][nw[-6]>>dt&255]]=nw[-6];
        b[--cnt[len][nw[-7]>>dt&255]]=nw[-7];
        nw-=8;
        
    }
    switch(n&7){
        case 7:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
        case 6:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
        case 5:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
        case 4:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
        case 3:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
        case 2:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
        case 1:{b[--cnt[len][*nw>>dt&255]]=*nw;--nw;}
    }

}
}

/**
 * @brief radix sort for unsigned integer [st,ed)
 * 
 * @tparam IntType an unsigned int type
 * @tparam Iter iterator type
 * @tparam chkmx use chkmx for small range size to imporve efficiency
 * @param st An iterator.
 * @param ed Another iterator.
 */
template<typename IntType,typename Iter,bool chkmx=false> 
void radix_sort(Iter st,Iter ed) {
    typedef IntType T;
    static_assert(std::is_unsigned<T>::value&&std::is_integral<T>::value,
        "Need unsigned integer. Pleas use to_unsigned to access.");
    T rmx=std::numeric_limits<IntType>::max()>>8;
    T mx=0,*b=new T[ed-st](),v=1;
    Iter a=st;
    int tot=1;
    for(T i=1;i<rmx;i<<=8) tot++;
    if(chkmx) {for(auto nw=st;nw!=ed;nw++) if(*nw>mx) mx=*nw;}
    else mx=std::numeric_limits<IntType>::max();
    __RadixSort::n=ed-st,v=0;
    for(int len=0;len<tot;len++,v=(len<<3)) {
        memset(__RadixSort::cnt[len],0,sizeof(__RadixSort::cnt[len]));
        for(auto nw=st;nw!=ed;++nw) ++__RadixSort::cnt[len][*nw>>v&255];
    }
        
    for(int len=0;len<tot;len++) for(int i=1;i<256;++i) {
        __RadixSort::cnt[len][i]+=__RadixSort::cnt[len][i-1];
    }
    bool p=1;
    v=1;
    for(int len=0;len<tot;len++,p^=1,v<<=3) {
        if(p) __RadixSort::__radix_sort(a,b,len);
        else __RadixSort::__radix_sort(b,a,len);
        if(v>=mx) break;
    }
    if(!p) for(int i=0;i<__RadixSort::n;i++) a[i]=b[i];
    delete []b;
}

}

namespace UNIG {

namespace __UNIG {

void* bs[27];

bool is_pret=false;

/**
 * @brief Get the std::bitset object
 * 
 * @tparam len trick to get variable length bitset
 * @param idx bitset index in bs
 */
template<int len=1>
void get_bitset(int idx=0) {
    bs[idx]=new std::bitset<len>();
    if(MAXLEN>len) {
        get_bitset<std::min(len<<1,MAXLEN)>(idx+1);
        return;
    }
}

}

/// @brief pretreat std::bitset
void pret_bitset() {__UNIG::get_bitset<1>(0); __UNIG::is_pret=true;}

/**
 * @brief Generate a sequence with no duplicates
 * 
 * @tparam IntType an integer type. unsigned type would be faster.
 * @tparam UniformIntDistrbution=std::uniform_int_distribution
 * <typename std::make_unsigned<IntType>::type> uniform int distribution to generate the numbers
 */
template<typename IntType=int,
         class UniformIntDistrbution=std::uniform_int_distribution 
            <typename std::make_unsigned<IntType>::type> >
class UniformNonredundantIntGenration {
    typedef IntType T;
    typedef typename std::make_unsigned<T>::type UT;
    static_assert(std::is_integral<T>::value, 
        "IntType must be a supported integer type");
    public:
        /**
         * @brief Construct a new Uniform Nonredundant Int Genration object
         * 
         * @param mn lower bound
         * @param mx upper bound
         */
        UniformNonredundantIntGenration(T mn=std::numeric_limits<T>::min(),T mx=std::numeric_limits<T>::max())
            :lwb_(to_unsigned(mn)),upb_(to_unsigned(mx)) {V=upb_-lwb_;}

        /// @brief set lower bound and upper bound
        /// @param mn lower bound
        /// @param mx upper bound
        void set_bound(T mn,T mx) {lwb_=to_unsigned(mn),upb_=to_unsigned(mx),V=upb_-lwb_;}

        /// @param n sequence length
        /// @param gen random int generator like std::mt19937
        /// @return The required sequence.
        template<typename URNG>
        std::vector<T> operator ()(int n,URNG &gen) {
            auto x=get(n,gen);
            std::vector<T> ans(n);
            for(int i=0;i<n;i++) ans[i]=to_ori(x[i]);
            return ans;
        }
        
    private:
        UT lwb_,upb_;
        UT V;
        // Main function to get UNIG
        template<typename URNG>
        std::vector<UT> get(int n,URNG &gen) {
            double B=2.0;
            if((double)V+1>=B*(n-1)) {
                if(V<=MAXLEN) {
                    std::vector<UT> ret;
                    ret.reserve(n);
                    bitset_opt_sparse_gen(n,gen,ret);
                    return ret;
                }
                return sparse_gen(n,gen);
            }
            return dense_gen(n,gen);
        }

        /// @brief Used when n:V is small.
        template<typename URNG>
        std::vector<UT> sparse_gen(int n,URNG &gen) {
            UniformIntDistrbution dist(lwb_,upb_);
            std::vector<UT> ans;
            ans.reserve(n);
            auto ansb=ans.end();
            while((int)ans.size()<n) {
                while((int)ans.size()<n) ans.push_back(dist(gen));
                robin_sort(ansb,ans.end());
                std::inplace_merge(ans.begin(),ansb,ans.end());
                ans.erase(std::unique(ans.begin(),ans.end()),ans.end());
                ansb=ans.end();
            }
            return ans;
        }
        /// @brief Optimization of sparse gen using std::bitset.
        template<typename URNG,int len=1>
        void bitset_opt_sparse_gen(int n,URNG &gen,std::vector<UT> &ans,int idx=0) {
            if(V>len) {
                bitset_opt_sparse_gen<URNG,std::min(MAXLEN,len<<1)>(n,gen,ans,idx+1);
                return ;
            }
            UniformIntDistrbution dist(lwb_,upb_);
            std::bitset<len> *vis=nullptr;
            if(!__UNIG::is_pret) vis=new std::bitset<len>();
            else vis=(std::bitset<len>*)__UNIG::bs[idx],vis->reset();
            for(int i=1;i<=n;i++) {
                UT nw;
                do nw=dist(gen);
                while(vis->operator[](nw-lwb_));
                ans.push_back(nw);
                vis->operator[](nw-lwb_)=1;
            }
            delete vis;
        }

        /// @brief Used when n:V is large.
        template<typename URNG>
        std::vector<UT> dense_gen(int n,URNG &gen) {
            std::vector<UT> ans;
            ans.reserve(n);
            std::vector<UT> rng((unsigned long long)V+1);
            for(UT i=lwb_;i<=upb_;i++) rng[i-lwb_]=i;
            for(int i=1;i<=n;i++) {
                UniformIntDistrbution dist(0,rng.size()-1);
                int nw=dist(gen);
                ans.push_back(rng[nw]);
                std::swap(rng[nw],rng.back());
                rng.pop_back();
            }
            return ans;
        }
        
        /// @brief sort a list
        /// Do not care the function name. It's just for less constant.
        template<typename Iter>
        void robin_sort(Iter st,Iter  ed) {
            if(ed-st<=30000) std::sort(st,ed);
            else RadixSort::radix_sort<UT>(st,ed);
        }

        UT to_unsigned(T x) {
            if(std::is_same<T,UT>::value) return x;
            UT y;
            if(x<0) y=x+std::numeric_limits<T>::max()+1;
            else y=x,y+=(UT)std::numeric_limits<T>::max()+1;
            return y;
        }

        T to_ori(UT x) {
            if(std::is_same<T,UT>::value) return x;
            T y;
            if(x>(UT)std::numeric_limits<T>::max()) 
                y=x-(UT)std::numeric_limits<T>::max()-1;
            else y=x,y-=std::numeric_limits<T>::max(),y--;
            return y;
        }
};
}

/// @brief UNIG e.g.
signed main() {
    // freopen("test.in","w",stdout);
    int Q=1;
    // std::cin>>Q;
    std::mt19937 gen(1993);
    UNIG::UniformNonredundantIntGenration<int> unig;
    while(Q--) {
        int n=1e6,a=1,b=1e9;
        // std::cin>>a>>b>>n;
        unig.set_bound(a,b);
        auto v=unig(n,gen);
        // std::cout<<n<<'\n';
        // for(auto i:v) std::cout<<i<<' ';
        // std::cout<<'\n';
    }
    return 0;
}