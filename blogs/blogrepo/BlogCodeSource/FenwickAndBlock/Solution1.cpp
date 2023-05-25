#include<cstdio>
#include<iostream>
#include<vector>
#include<cctype>

namespace myio{
	const char enter='\n';
	const char space=' ';
	char buf[1<<15],*p1=buf,*p2=buf;
	#define getchar() (p1==p2&&(p2=buf+fread(\
	p1=buf,1,1<<15,stdin),p1==p2)?-1:*p1++)
	long long read_int(){
		long long x=0;char ch,f=1;
		while(!std::isdigit(ch=getchar())) if(ch=='-') f=0;
		do x=(x<<1)+(x<<3)+ch-'0';
		while(std::isdigit(ch=getchar()));
		return (f==1?x:-x);
	}
	#undef getchar
	template<typename T>
	void PRINT(T x){
		if(x<=9) putchar(x+'0');
		else PRINT(x/10),putchar(x%10+'0');
	}
	template<typename T>
	void print_int(T x,char endch='\n'){
		if(x<0) putchar('-'),PRINT(-x);
		else PRINT(x);
		putchar(endch);
	}
	template<typename T>
	void print_int(T x,T y,char sepch=' ',char endch='\n') {
		print_int(x,sepch),print_int(y,endch);
	}
	#if __cplusplus >= 201103L
	template<typename T>
	void print_int(const std::initializer_list<T> &vec,
		char sepch=' ',char endch='\n') {
		for(auto items:vec) print_int(items,sepch);
		putchar(endch);
	}
	#endif
	#if __cplusplus >= 201103L
	template<typename T>
	void print_int(std::vector<T> &vec,char sepch=' ',char endch='\n') {
		for(auto items:vec) print_int(items,sepch);
		putchar(endch);
	}
	#else
	template<typename T>
	void print_int(std::vector<T> &vec,char sepch=' ',char endch='\n') {
		typename std::vector<T>::iterator it=vec.begin();
		for(;it!=vec.end();it++) print_int(*it,sepch);
		putchar(endch);
	}
	#endif
	template<typename T>
	void print_int(T* begin,T* end,char sepch=' ',char endch='\n') {
		for(T* it=begin;it!=end;it++) myio::print_int(*it,sepch);
		putchar(endch);
	}
	template<typename T>
	void print_by_bit(T x,short len=32,char endch='\n') {
		for(int i=0;i<len;i++) putchar((x&1)+'0'),x>>=1;
		putchar(enter);
	}
}

#include<cstring>
#include<algorithm>
#define LL	long long
#define Re	myio::read_int()
using namespace std;

const int kN=2e6+6,INF=2e9;
const LL INFLL=9e18;

int n,K;
LL D,H[kN],dp[kN],p[kN];
int T[kN];

void tMax(LL &x,LL y) {if(x<y) x=y;}

class BITcore {
	private:
		LL *mem;
		int size;
	public:
		BITcore() {}
		BITcore(int _size) {
			size=_size+1;
			mem=new LL[size+1];
			for(int i=0;i<=size;i++) mem[i]=-INFLL;
		}
		void toMax(int x,LL data) {for(x++;x<=size;x+=x&-x) tMax(mem[x],data);}
		LL query(int x) {
			LL ret=-INFLL; 
			for(x++;x>0;x-=x&-x) tMax(ret,mem[x]);
			return ret;
		}
}; 

BITcore **BIT=NULL;
BITcore *forall=NULL;

int Q[kN],hd=1,tl=0;
void pushQ(int y) {
	while(tl>=hd&&dp[Q[tl]]<dp[y]) tl--;
	Q[++tl]=y;
}
void popQ(int x) {if(Q[hd]>=x) hd++;}
LL prefix() {if(hd<=tl) return dp[Q[hd]]; return -INFLL;}

int pos(int x,int y) {int tmp=x/K*K+y; while(tmp>x) tmp-=K; return tmp/K;}
LL BIT_prefix_query(int i) {return BIT[i%K]->query(pos(i+T[i],i%K)-1);}
LL query_for_block(int i) {return BIT_prefix_query(i)-D*(n/K-i/K);}
LL query_for_all(int i) {return forall->query(i+T[i])-D*(T[i]/K);}
void solve(int i) {
	if(i+K<n) popQ(i+K);
	LL tmp;
	if(T[i]/K<1) tmp=query_for_all(i);
	else tmp=max(max(query_for_block(i),query_for_all(i)),prefix());
	if(i<n-1) dp[i]=H[i]+tmp;
	pushQ(i); p[i]=prefix();
	BIT[i%K]->toMax(i/K,p[i]+D*(n/K-i/K));
	forall->toMax(i,dp[i]);  
}

signed main() {
	n=Re,K=Re,D=Re;
	for(int i=0;i<n;i++) H[i]=Re;
	for(int i=0;i<n-1;i++) T[i]=Re;
	forall=new BITcore(n),BIT=new BITcore*[K]();
	for(int i=0;i<K;i++) BIT[i]=new BITcore(n/K);
	memset(p,0xc0,sizeof(p));
	dp[n-1]=H[n-1]; 
	for(int i=n-1;i>=0;i--) solve(i);
	LL ans=0;
	for(int i=0;i<n;i++) ans^=dp[i]+i+1;
	myio::print_int(ans);
	return 0;
}

