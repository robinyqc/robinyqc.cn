#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
#define endl '\n'

class PresistentSegmentTree {
    #define new_node (++ntop)
    public:
        PresistentSegmentTree(int _range,int _qsize):ntop(),rn() {
            t=new Node[(_range<<5)+1]();
            rt=new int[_qsize+1]();
            rt[0]=new_node,rg=_range;
            build(1,_range,1);
        }

        void set(int x) {
            rt[++rn]=new_node; 
            set_base(x,1,rg,rt[rn-1],rt[rn]);
        }

        int query(int x,int y) {return query_base(x,1,rg,rt[y],rt[rn]);}

        pair<bool,int> kth_l(int L,int R,int k,int y) {
            int j=find_seg_l(L,R,k,1,rg,rt[y],rt[rn]);
            if(j!=-1) return pair{false,j};
            return pair{true,bin_search_l(ta.l,ta.r,ta.q,ta.p,ta.k)};
        }

        pair<bool,int> kth_r(int L,int R,int k,int y) {
            int j=find_seg_r(L,R,k,1,rg,rt[y],rt[rn]);
            if(j!=-1) return pair{false,j};
            return pair{true,bin_search_r(ta.l,ta.r,ta.q,ta.p,ta.k)};
        }
    private:
        struct Node {
            int cnt;
            int l,r;
            Node():cnt(),l(),r() {}
        };
        Node *t;
        int *rt;
        int ntop,rn,rg;
        struct TmpAns {
            int l,r,q,p,k;
        } ta;

        void push_up(int p) {t[p].cnt=t[t[p].l].cnt+t[t[p].r].cnt;}

        void build(int l,int r,int p) {
            if(l==r) {t[p].cnt=0; return ;}
            t[p].l=new_node,t[p].r=new_node;
            int mid=(l+r)>>1;
            build(l,mid,t[p].l),build(mid+1,r,t[p].r);
        }

        void set_base(int X,int l,int r,int q,int p) {
            if(l==r) {t[p].cnt=1; return ;}
            int mid=(l+r)>>1;
            if(X<=mid) {
                t[p].r=t[q].r;
                t[p].l=new_node;
                set_base(X,l,mid,t[q].l,t[p].l);
            }
            else {
                t[p].l=t[q].l;
                t[p].r=new_node;
                set_base(X,mid+1,r,t[q].r,t[p].r);
            }
            push_up(p);
        }

        int query_base(int X,int l,int r,int q,int p) {
            if(l==r) return t[p].cnt-t[q].cnt;
            int mid=(l+r)>>1;
            if(X<=mid) return query_base(X,l,mid,t[q].l,t[p].l);
            return query_base(X,mid+1,r,t[q].r,t[p].r);
        }

        int find_seg_l(int L,int R,int k,int l,int r,int q,int p) {
            if(L<=l&&r<=R) {
                if(k<=r-l+1+t[q].cnt-t[p].cnt) {
                    ta=TmpAns{l,r,q,p,k};
                    return -1;
                }
                return r-l+1+t[q].cnt-t[p].cnt;
            }
            int mid=(l+r)>>1,s1=0,s2=0;
            if(L<=mid) s1=find_seg_l(L,R,k,l,mid,t[q].l,t[p].l);
            if(s1==-1) return -1;
            if(mid<R) s2=find_seg_l(L,R,k-s1,mid+1,r,t[q].r,t[p].r);
            if(s2==-1) return -1;
            return s1+s2;
        }

        int bin_search_l(int l,int r,int q,int p,int k) {
            if(l==r) return l;
            int mid=(l+r)>>1,ls=mid-l+1+t[t[q].l].cnt-t[t[p].l].cnt;
            if(k<=ls) return bin_search_l(l,mid,t[q].l,t[p].l,k);
            return bin_search_l(mid+1,r,t[q].r,t[p].r,k-ls);
        }

        int find_seg_r(int L,int R,int k,int l,int r,int q,int p) {
            if(L<=l&&r<=R) {
                if(k<=r-l+1+t[q].cnt-t[p].cnt) {
                    ta=TmpAns{l,r,q,p,k};
                    return -1;
                }
                return r-l+1+t[q].cnt-t[p].cnt;
            }
            int mid=(l+r)>>1,s1=0,s2=0;
            if(mid<R) s2=find_seg_r(L,R,k,mid+1,r,t[q].r,t[p].r);
            if(s2==-1) return -1;
            if(L<=mid) s1=find_seg_r(L,R,k-s2,l,mid,t[q].l,t[p].l);
            if(s1==-1) return -1;
            return s1+s2;
        }

        int bin_search_r(int l,int r,int q,int p,int k) {
            if(l==r) return l;
            int mid=(l+r)>>1,rs=r-mid+t[t[q].r].cnt-t[t[p].r].cnt;
            if(k<=rs) return bin_search_r(mid+1,r,t[q].r,t[p].r,k);
            return bin_search_r(l,mid,t[q].l,t[p].l,k-rs);
        }
    #undef new_node
};

const int N=100005;

struct Edge {
    int v,nxt;
};
Edge e[N<<1];
int tot,h[N];
void add_edge(int u,int v) {
    e[++tot].nxt=h[u];
    h[u]=tot,e[tot].v=v;
}

int dep[N],fa[N],siz[N],dfn[N],top[N],rk[N],son[N],dtop;

void dfs1(int rt) {
    siz[rt]=1;
    for(int i=h[rt];i;i=e[i].nxt) {
        int to=e[i].v;
        if(e[i].v==fa[rt]) continue;
        dep[to]=dep[rt]+1,fa[to]=rt;
        dfs1(to);
        siz[rt]+=siz[to];
        if(siz[to]>siz[son[rt]]) son[rt]=to;
    }
}

void dfs2(int rt) {
    dfn[rt]=++dtop; rk[dtop]=rt;
    if(!son[rt]) return ;  // important
    top[son[rt]]=top[rt];
    dfs2(son[rt]);
    for(int i=h[rt];i;i=e[i].nxt) {
        int to=e[i].v;
        if(to!=fa[rt]&&to!=son[rt]) {
            top[to]=to;
            dfs2(to);
        }
    }
}

vector<pair<int,int> > rev,seg;
void get_segs(int x,int y) {
    rev.clear(),seg.clear();
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) {
            rev.push_back({dfn[top[y]],dfn[y]});
            y=fa[top[y]];
        }
        else {
            seg.push_back({dfn[top[x]],dfn[x]});
            x=fa[top[x]];
        }
    }
    if(dep[x]<dep[y]) rev.push_back({dfn[x],dfn[y]});
    else seg.push_back({dfn[y],dfn[x]});
    reverse(rev.begin(),rev.end());
}

int year[N];

signed main() {
    ios::sync_with_stdio(false);
    int n,m;
    rev.reserve(500),seg.reserve(1000);
    cin>>n;
    for(int i=1,v;i<=n;i++) {
        cin>>v;
        if(v==0) continue;
        add_edge(i,v);
        add_edge(v,i);
    }
    top[1]=1;
    dfs1(1),dfs2(1);
    cin>>m;
    PresistentSegmentTree segtree(n,m);
    int t,a,b,c,d;
    for(int y=1;y<=m;y++) {
        cin>>t;
        if(t==1) {
            cin>>a;
            year[y]=year[y-1]+1;
            segtree.set(dfn[a]);
        }
        else {
            cin>>a>>b>>c>>d;
            get_segs(a,b);
            d=year[d];
            if(!segtree.query(dfn[a],d)) c++;
            for(auto &s:seg) {
                auto p=segtree.kth_r(s.first,s.second,c,d);
                if(p.first) {
                    if(rk[p.second]!=b) cout<<rk[p.second]<<endl; 
                    else cout<<-1<<endl;
                    goto no_print;
                }
                else c-=p.second;
            }
            for(auto &s:rev) {
                auto p=segtree.kth_l(s.first,s.second,c,d);
                if(p.first) {
                    if(rk[p.second]!=b) cout<<rk[p.second]<<endl; 
                    else cout<<-1<<endl;
                    goto no_print;
                }
                else c-=p.second;
            }
            cout<<-1<<endl;
            no_print:;
            year[y]=year[y-1];
        }
    }
    return 0;
}