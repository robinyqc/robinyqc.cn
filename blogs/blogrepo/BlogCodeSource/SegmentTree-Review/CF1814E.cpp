#include<cstdio>
#include<iostream>
#include<vector>

namespace myio{
	const char enter='\n';
	const char space=' ';

	namespace fast_read{
		bool if_fast_read=false;
		char *buf=NULL,*p1=NULL,*p2=NULL;
		void SetFreadOn() {
			buf=new char[1<<23]();
			p1=buf,p2=buf;
			if_fast_read=true;
		}
		char getchar() {return (p1==p2&&(p2=(p1=buf)+fread(buf, \
			1,1<<21,stdin),p1==p2)?EOF:*p1++);}
	}
	long long read_int(){
		if(fast_read::if_fast_read) {
			long long x=0;char ch,f=1;
			while(!std::isdigit(ch=fast_read::getchar())) if(ch=='-') f=0;
			do x=(x<<1)+(x<<3)+ch-'0';
			while(std::isdigit(ch=fast_read::getchar()));
			return (f==1?x:-x);
		}
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
}
#include<cstring>
#define int long long
#define R myio::read_int()
const int INF=9e16;

void tMin(int &x,int y) {if(x>y) x=y;}

struct matrix {
	int mat[2][2];
	matrix() {mat[0][0]=mat[0][1]=mat[1][0]=mat[1][1]=INF;}
	matrix(int x) {mat[0][0]=INF,mat[0][1]=0,mat[1][0]=mat[1][1]=x<<1;}
	matrix operator *(const matrix &tar) const {
		matrix ret;
		for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<2;k++)
			tMin(ret.mat[i][j],mat[i][k]+tar.mat[k][j]);
		return ret;
	}
};

class SegmentTree {
	private:
		matrix *nodes;
		int size;
		void PUSH_UP(int p) {nodes[p]=nodes[p<<1]*nodes[p<<1|1];}
		void BUILD(int *_init,int l,int r,int p) {
			if(l>=r) {
				nodes[p]=matrix(_init[l]);
				return ;
			}
			int mid=(l+r)>>1;
			BUILD(_init,l,mid,p<<1);
			BUILD(_init,mid+1,r,p<<1|1);
			PUSH_UP(p);
		}
		void MODIFY(int X,int D,int l,int r,int p) {
			if(l>=r) {
				nodes[p]=matrix(D);
				return ;
			}
			int mid=(l+r)>>1;
			if(X<=mid) MODIFY(X,D,l,mid,p<<1);
			else MODIFY(X,D,mid+1,r,p<<1|1);
			PUSH_UP(p);
		}
	public:
		SegmentTree(int _size,int *_init) {
			size=_size;
			nodes=new matrix[size*4+10]();
			BUILD(_init,1,size,1);
		}
		void modify(int x,int d) {MODIFY(x,d,1,size,1);}
		int query() {return nodes[1].mat[1][0];}
		~SegmentTree() {delete []nodes;}
};

int n,a[200005],q;
signed main() {
	n=R;
	for(int i=1;i<n;i++) a[i]=R;
	q=R;
	int k,x;
	SegmentTree *segtree=new SegmentTree(n-1,a);
	while(q--) {
		k=R,x=R;
		segtree->modify(k,x);
		myio::print_int(segtree->query());
	}
	delete segtree;
	return 0;
}

