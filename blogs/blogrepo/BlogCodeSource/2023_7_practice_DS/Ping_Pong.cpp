#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF=2e9,N=100000;

int n;

struct Interval {int l,r;};
Interval seg[N+5];

void tMax(int &x,int y) {if(x<y) x=y;}
void tMin(int &x,int y) {if(x>y) x=y;}

int fa[100005],L[100005],R[100005],siz[100005];
int getfa(int x) {while(x!=fa[x]) x=fa[x]=fa[fa[x]]=fa[fa[fa[x]]]; return x;}
void merges(int x,int y) {
    x=getfa(x),y=getfa(y);
    if(x!=y) {
        if(siz[x]<siz[y]) fa[x]=y,tMin(L[y],L[x]),tMax(R[y],R[x]),siz[y]+=siz[x];
        else fa[y]=x,tMin(L[x],L[y]),tMax(R[x],R[y]),siz[x]+=siz[y];
    }
}

class ZkwSegmentTree {
    public:
        void set_size(int _size) {size_=(1<<__lg(_size))<<1;}

        void cover(int l,int r,int id) {
            for(l+=size_-1,r+=size_+1;l^r^1;l>>=1,r>>=1) {
                if(~l&1) cs[l^1].push_back(id);
                if(r&1) cs[r^1].push_back(id);
            }
        }
        
        void merge(int p,int id) {
            for(p+=size_;p;p>>=1) {
                if(cs[p].empty()) continue;
                for(int v:cs[p]) merges(v,id);
                cs[p].clear(); cs[p].push_back(id);
            } 
        }

    private:
        int size_;
        vector<int> cs[2100000]; //covered_segment
};

ZkwSegmentTree segtree;

struct Query {int o,x,y;} q[N+1];

vector<int> ls;

signed main() {
    memset(L,0x3f,sizeof(L));
    scanf("%d",&n);
    for(int i=1;i<=n;++i) fa[i]=i,siz[i]=1;
    ls.reserve(n<<1);
    for(int i=1;i<=n;++i) {
        scanf("%d%d%d",&q[i].o,&q[i].x,&q[i].y);
        if(q[i].o==1) ls.push_back(q[i].x),ls.push_back(q[i].y);
    }
    sort(ls.begin(),ls.end());
    ls.erase(unique(ls.begin(),ls.end()),ls.end());
    segtree.set_size(ls.size()+10);
    int op,x,y,c=0; 
    for(int i=1;i<=n;++i) {
        op=q[i].o,x=q[i].x,y=q[i].y;
        if(op==1) {
            x=lower_bound(ls.begin(),ls.end(),x)-ls.begin()+1;
            y=lower_bound(ls.begin(),ls.end(),y)-ls.begin()+1;
            ++c; fa[c]=c,L[c]=x,R[c]=y;
            segtree.merge(x,c),segtree.merge(y,c);
            if(x<y-1) segtree.cover(x+1,y-1,c);
        }
        else {
            x=getfa(x),y=getfa(y);
            if(x==y||(L[x]>L[y]&&L[x]<R[y])||(R[x]>L[y]&&R[x]<R[y])||
                (L[x]==L[y]&&R[x]==R[y]&&siz[x]>1)) puts("YES"); //spec hack
            else puts("NO");
        }
    }
    return 0;
}