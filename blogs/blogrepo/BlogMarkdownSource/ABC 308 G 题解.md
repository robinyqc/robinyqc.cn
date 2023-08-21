### 题意简述

可重集合 $A$ 最开始是空的。然后你需要支持三种操作：

1. 加入一个数 $x$；
2. 删除一个数 $x$（保证 $x$ 当前一定存在）；
3. 查询从集合中选两个数异或的最小值（保证当前集合中至少存在两个数）。

如果你没有看懂第三个操作的意思，可以**简单理解为**求：
$$
\min_{1\leq i<j\leq n} \{A_i\oplus A_j\}
$$
其中 $\oplus$ 表示按位异或操作。



### 解题思路

第一眼想必大家都想过 01trie 或者线性基。但是删除操作和全局询问实在是不好维护。听机房大佬说可以线段树分治 $O(n\log^2 n)$ 做，但显然这不是一个好的方法~~（而且我不会）~~。

此题的关键其实是找到异或的一个性质：若 $x< y< z$，则 $x\oplus z> \min\{x\oplus y,y\oplus z\}$。

***

#### 证明

设 $v_n$ 表示 $v$ 在二进制表示下从低往高数第 $n+1$ 位，比如 $v_0$ 表示最低位（第一位）。

设 $x$ 和 $z$ 二进制表示下 $k+1$ 位及以后完全相同。那么第 $k$ 位，由于 $x<z$，必定满足 $x_k=0$，$z_k=1$。因此 $(x\oplus z)_k=1$ 并且 $\forall 0<j<k,(x\oplus z)_j=0$。因此 $2^k\leq x\oplus z<2^{k+1}$。

设 $x$ 和 $y$ 在 $i+1$ 位及以后相同，同理 $2^i\leq x\oplus y<2^{i+1}$；设 $y$ 和 $z$ 在 $l+1$ 位及以后相同，同理 $2^l\leq y\oplus z<2^{l+1}$。

因为 $x<y<z$，显然 $i,l\leq k$。并且，若 $y$ 第 $k$ 位为 $1$（即 $i=k$)，那么 $l<k$；若 $y$ 第 $k$ 位为 $0$（即 $l=k$)，那么 $i<k$。也就是，$(i<k)\lor (l<k)$ 恒成立。那么 $(2^{i+1}\leq 2^k)\lor (2^{l+1}\leq2^k)$ 恒成立。因为 $x\oplus y<2^{i+1}$，$y\oplus z<2^{l+1}$ 且 $2^k\leq x\oplus z$。那么不等式的放缩是可行的，$(x\oplus y< x\oplus z)\lor (y\oplus z< x\oplus z)$ 恒成立。也即 $x\oplus z> \min\{x\oplus y,y\oplus z\}$。

证毕。

***

以上的证明可能相对冗长，但是一定详细。相信你已经看懂了。

我们首先把当前存在的数排序，去重，得到一个序列 $B$，根据刚才提到的性质，发现，对于两个不相邻的数 $B_i,B_j$，显然存在：
$$
B_i\oplus B_j>\min\{B_i\oplus B_{j-1},B_{j-1}\oplus B_j\}\geq \min\{B_i\oplus B_{j-2},B_{j-2}\oplus B_{j-1},B_{j-1}\oplus B_j\}\geq\dots\geq \min_{i<k\leq j} \{B_k\oplus B_{k-1}\}
$$
也就是两个不相邻的数异或起来一定不优于某两个相邻的数异或起来！用 `set` 维护一下插入删除，这道题就被解决了！

当然，有一个码量上的优化(?)。发现 `std::set` 自带去重，插入更简单了，但是删除起来不是很方便，还容易 RE。

我们发现不去重并不影响答案：若存在不相邻的两个数相同，则必定存在相邻的相同的两个数。因此不去重，用 `multiset` 维护一下即可。可能会慢点，但绝对好写！



### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;

// bb 储存原始数据，xo 储存异或后的数据
multiset<int> bb,xo;

signed main() {
    ios::sync_with_stdio(false);
    int q,t,x;
    cin>>q;
    while(q--) {
        cin>>t;
        if(t==1) {
            cin>>x;
            auto it=bb.insert(x);
            if(bb.size()>=2) { // 注意各种边界！
                if(it==bb.begin()) xo.insert(*it^*next(it));
                else if(it==prev(bb.end())) xo.insert(*it^*prev(it));
                else {
                    xo.insert(*it^*next(it));
                    xo.insert(*it^*prev(it));
                    xo.erase(xo.find(*prev(it)^*next(it)));
                }
            }
        }
        else if(t==2) {
            cin>>x;
            auto it=bb.find(x);
            if(bb.size()>=2) {
                if(it==bb.begin()) xo.erase(xo.find(*it^*next(it)));
                else if(it==prev(bb.end())) xo.erase(xo.find(*it^*prev(it)));
                else {
                    xo.erase(xo.find(*it^*next(it)));
                    xo.erase(xo.find(*it^*prev(it)));
                    xo.insert(*prev(it)^*next(it));
                }
            }
            bb.erase(it);
        }
        else cout<<*xo.begin()<<endl;
    }
    return 0;
}
```



#### 题外话

[sol_1](https://atcoder.jp/contests/abc308/submissions/43157346) 和 [sol_2](https://atcoder.jp/contests/abc308/submissions/43209332) 两份提交没有任何实质上的区别，但是却差了 400ms （（（