#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

#define LL long long

const int N=1e6;

const int P=1000000007;

int Qpow(LL x,int y) {
    LL ret=1;
    for(;y>0;y>>=1) {
        if(y&1) ret=ret*x%P;
        x=x*x%P;
    } return ret;
}

int Inv(LL x) {return Qpow(x,P-2);}

void Amod(int &x) {if(x>P) x-=P;}

int Bmod(int x) {if(x>P) return x-P; return x;}

int n,a[N+5],b[N+5],c[N+5],Q;

int exp_dep[N+5]; //expected depth

int lca_helper[N+5];

signed main() {

    scanf("%d%d",&n,&Q);
    for(int i=1;i<n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",c+i);
    for(int i=1;i<n;i++) b[i]=b[i-1]+a[i];
    for(int i=1;i<n;i++) b[i]=Inv(b[i]); //Note it!

    for(int p=2,calc_helper=0;p<=n;p++) {
        Amod(exp_dep[p]=Bmod(c[1]+c[p])+Bmod(calc_helper<<1));
        Amod(calc_helper+=((LL)c[p])*a[p]%P*b[p]%P);
    }
    for(int i=2;i<n;i++) lca_helper[i]=Bmod((((LL)(a[i-1]<<1))*b[i-2]+1ll)%P*
        lca_helper[i-1]%P+((LL)exp_dep[i-1])*a[i-1]%P*a[i-1]%P);
    for(int x=2;x<n;x++) lca_helper[x]=((LL)lca_helper[x])*b[x]%P*b[x-1]%P;
    int x,y;
    while(Q--) {
        scanf("%d%d",&x,&y);
        if(x==y) {puts("0"); continue;}
        if(x>y) swap(x,y);
        int part1=Bmod(exp_dep[x]+exp_dep[y]);
        int part2=Bmod(((LL)a[x])*b[x]%P*exp_dep[x]%P+lca_helper[x]);
        int ans=part1-Bmod(part2<<1);
        if(ans<0) ans+=P;
        printf("%d\n",ans);
    }
    return 0;
}