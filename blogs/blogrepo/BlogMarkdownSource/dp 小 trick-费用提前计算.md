### dp 小 trick——费用提前计算

假设有这样一个 dp 转移方程：
$$
dp_{i,j}=g\bigg(dp_{k,j-1}+s\cdot j\cdot f(k,i)\bigg)
$$
其中，$s$ 是一个常数，函数 $f(a,b)=\sum_\limits{i=a}^b v_i$，$g$ 也是一个函数（比如 $\max$），dp 的目标是 $g(dp_{n,x}),x\in \mathbb{N}$。

那么可以改写这个 dp 式为：
$$
dp_i=g\bigg (dp_k+s\cdot f(k,n)\bigg)
$$
目标是 $dp_n$。此时，$dp_i$ 表示的是执行前 $i$ 个任务分成若干批的最小费用，再加上对以后的影响。

假设转移的集合是 $p \ \text{且}\ p_0=1$，那么转移 $m$ 次到 $p_m$ 时，不涉及 dp 式的部分对答案的增加量为 $s\cdot f(p_0,p_1)+2s\cdot f(p_1,p_2)+3s\cdot f(p_2,p_3)+\dots+m\cdot s\cdot f(p_{m-1},p_m)$。总可以拆成：
$$
s\cdot\sum _{i=1}^m f(p_{i-1},p_i)+s\cdot\sum _{i=1}^m f(p_{i-1},p_i)+\dots+s\cdot\sum _{i=m}^m f(p_{i-1},p_i)
$$
也就是：
$$
s\cdot f(p_0,p_m)+s\cdot f(p_1,p_m)+\dots +s\cdot f(p_{m-1},p_m)
$$
我们已知终点 $p_m=n$。那么每次转移的时候，$f(p_j,n)$ 显然是已知量：$p_j=k$。因此可直接记录下来，加在 $dp_i$ 上。

### 例题：任务安排

经典 DP 题，其中就要运用“费用提前计算”的技巧。