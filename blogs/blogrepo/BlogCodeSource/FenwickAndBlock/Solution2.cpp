#include<cstdio>
#include<iostream>
#include<vector>
#include<cctype>

namespace myio{
	const char enter='\n';
	const char space=' ';
	long long read_int(){
		long long x=0;char ch,f=1;
		while(!std::isdigit(ch=getchar())) if(ch=='-') f=0;
		do x=(x<<1)+(x<<3)+ch-'0';
		while(std::isdigit(ch=getchar()));
		return (f==1?x:-x);
	}
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
#define LL	long long
#define Re	myio::read_int()

const int kN=2e6+6,INF=2e9;
const LL INFLL=9e18;

int n,K;
LL D,H[kN],dp[kN];
int T[kN];

void tMax(LL &x,LL y) {if(x<y) x=y;}

class BIT {
	private:
		LL *mem;
		int size;
	public:
		BIT() {}
		BIT(int _size) {
			size=_size+100;
			mem=new LL[size+100];
			for(int i=0;i<=size;i++) mem[i]=-INFLL;
		}
		void toMax(int x,LL data) {for(x++;x<=size;x+=x&-x) tMax(mem[x],data);}
		LL query(int x) {
			LL ret=-INFLL; 
			for(x++;x>0;x-=x&-x) tMax(ret,mem[x]);
			return ret;
		}
}; 

#define block(x) ((x)/(K))

BIT *blocks=NULL;
BIT *forall=NULL;
int blocksize,blocknow;
LL pre;
LL preblock[kN];

LL solveMiddle(int st,int ed,int mod) {
	st=block(st)+1,ed=block(ed)-1;
	if(st>ed) return -INFLL;
	return blocks[mod].query(ed)-(n/K-st)*D;
}

LL solveSuffix(int ed,int mod) {
	int eddl=block(ed)*K+mod; 
	if(eddl>ed) return preblock[ed];
	LL tmp=(eddl%K==0?-INFLL:preblock[eddl-1]); 
	return std::max(preblock[ed]-D,tmp);
}

LL getmax(int i) {
	int t=i+T[i];
	if(block(t)==block(i)) return forall->query(t);
	LL mid=solveMiddle(i,t,i%K);
	LL suf=solveSuffix(t,i%K)-D*std::max(block(t)-block(i)-1,0);
	return std::max(std::max(pre,mid),suf);
}

void insertBlock(int i) {
	if(i%K==0) {
		LL maxdp=-INFLL,sufdp=-INFLL; 
		preblock[i]=dp[i]; int ed=std::min(n,i+K);
		for(int j=i+1;j<ed;j++) preblock[j]=std::max(preblock[j-1],dp[j]);
		for(int j=ed-1;j>=i;j--) tMax(sufdp,dp[j]-D), \
			maxdp=std::max(sufdp,preblock[j-1]), \
			blocks[j%K].toMax(block(i),maxdp+(n/K-block(i))*D);
		pre=-INFLL;
	}
	else tMax(pre,dp[i]);
	forall->toMax(i,dp[i]);
}

signed main() {
	n=Re,K=Re,D=Re;
	forall=new BIT(n+1);
	for(int i=0;i<n;i++) H[i]=Re;
	for(int i=0;i<n-1;i++) T[i]=Re;
	blocksize=K; blocks=new BIT[blocksize]();
	for(int i=0;i<blocksize;i++) blocks[i]=BIT(block(n)+10);
	for(int i=0;i<=n;i++) preblock[i]=-INFLL;
	dp[n-1]=H[n-1]; insertBlock(n-1);
	for(int i=n-2;i>=0;i--) dp[i]=H[i]+getmax(i),insertBlock(i);
	LL ans=0;
	myio::print_int(dp,dp+n);
	for(int i=0;i<n;i++) ans^=dp[i]+i+1;
	myio::print_int(ans);
	return 0;
}

