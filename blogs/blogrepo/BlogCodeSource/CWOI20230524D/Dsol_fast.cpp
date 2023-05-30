/**
 * @file Dsol_fast.cpp
 * @author robinyqc (robinyqc@163.com)
 * @brief 代码使用了线性推逆元。
 * @version 0.1
 * @date 2023-05-27
 * 
 */
#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

#define LL long long

namespace myio {

    char buf[1<<15],*p1=buf,*p2=buf,obuf[1<<24],*O=obuf;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<14,stdin),p1==p2)?EOF:*p1++)

    template<typename T=int>
    T read_int() {
        T x=0;char ch;
        while(!std::isdigit(ch=getchar())) ;
        do x=(x<<1)+(x<<3)+ch-'0';
        while(std::isdigit(ch=getchar()));
        return x;
    }
    #undef getchar

    template<typename T>
    void __print(T x) {
        if(x<=9) *O++=(x+'0');
        else __print(x/10),*O++=(x%10+'0');
    }
    template<typename T>
    void print_int(T x) {
        __print(x);
        *O++=('\n');
    }

    void end_print() {fwrite(obuf,O-obuf,1,stdout);}
}

const int N=1e6;

const int P=1000000007;

int Qpow(LL x,int y) {
    LL ret=1;
    for(;y>0;y>>=1) {
        if(y&1) ret=ret*x%P;
        x=x*x%P;
    } return ret;
}

void Amod(int &x) {if(x>P) x-=P;}

int Bmod(int x) {if(x>P) return x-P; return x;}

int n,a[N+1],b[N+1],c[N+1],Q;

int exp_dep[N+1]; //expected depth

int lca_helper[N+1];

int preprod[N+1],inv_preprod[N+1];

signed main() {

    n=myio::read_int();
    Q=myio::read_int();
    for(int i=1;i<n;i++) a[i]=myio::read_int();
    for(int i=1;i<=n;i++) c[i]=myio::read_int();

    for(int i=1;i<n;i++) b[i]=b[i-1]+a[i];
    preprod[0]=1;
    for(int i=1;i<n;i++) preprod[i]=((LL)preprod[i-1])*b[i]%P;
    inv_preprod[n-1]=Qpow(preprod[n-1],P-2);
    for(int i=n-1;i>=1;i--) inv_preprod[i-1]=((LL)inv_preprod[i])*b[i]%P;
    for(int i=1;i<n;i++) b[i]=((LL)inv_preprod[i])*preprod[i-1]%P;

    for(int p=2,calc_helper=0;p<=n;p++) {
        Amod(exp_dep[p]=Bmod(c[1]+c[p])+Bmod(calc_helper<<1));
        Amod(calc_helper+=((LL)c[p])*a[p]%P*b[p]%P);
    }
    for(int i=2;i<n;i++) lca_helper[i]=Bmod((((LL)(a[i-1]<<1))*b[i-2]+1ll)%P*
        lca_helper[i-1]%P+((LL)exp_dep[i-1])*a[i-1]%P*a[i-1]%P);
    for(int x=2;x<n;x++) lca_helper[x]=((LL)lca_helper[x])*b[x]%P*b[x-1]%P;
    int x,y;
    while(Q--) {
        x=myio::read_int();
        y=myio::read_int();
        if(x==y) {myio::print_int(0); continue;}
        if(x>y) swap(x,y);
        int part1=Bmod(exp_dep[x]+exp_dep[y]);
        int part2=Bmod(((LL)a[x])*b[x]%P*exp_dep[x]%P+lca_helper[x]);
        int ans=part1-Bmod(part2<<1);
        if(ans<0) ans+=P;
        myio::print_int(ans);
    }
    myio::end_print();
    return 0;
}