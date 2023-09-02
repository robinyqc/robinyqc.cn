# Generate a Sequence With No Duplicate Uniformly at Random

Given a continuous range - $V$, and the length of the sequence - $n$, how can a sequence with no duplicates be generated uniformly at random?  For a sequence $S$, we say it has no duplicate if and only if $\forall i\neq j, S_i\neq S_j$. 

This is very useful for sampling. For example, you have an array $a$, and you want to select some samples to calculate their variance. The general way is to generate an index sequence and select the element with the generated indices. For example, in Python we use `random.sample` to do this.

Here I will show some ways to generate such a sequence.

### Method One

Let's consider the simplest algorithm. We can put the entire value range directly into an array and then shuffle it. If we take the first $n$ elements, we get a generation complexity of $O(|V|)$. However, shuffling has a high constant factor, so the whole process can be seen as $O(|V|w)$, where $w$ is a constant factor. Is there a better approach?

Actually, there's an even simpler idea, but with a flaw: just randomly pick $n$ numbers to construct a sequence. The flaw here is the possibility of generating duplicate numbers. How can we fix this? A simple solution is to put the entire range of values into a treap, select elements from it, and then remove them. This approach would have a complexity of $O(|V| + n \log n)$, but with a large constant factor, which is not ideal. The solution is also quite simple: put the whole range of values into a `std::vector` $\boldsymbol x$, then randomly choose an index $y$, put the corresponding element $\boldsymbol x[y]$ into the target vector $\boldsymbol z$, swap $\boldsymbol x[y]$ with the last element of $\boldsymbol x$, and then pop it off. The total complexity remains $O(|V| + n)$, but due to constants associated with operations like random number generation, the entire process can be considered as $O(|V| + nw)$. Since $n \leq |V|$, this approach is consistently no worse than the previous one, and may be better in certain cases.

Analyzing correctness: Assuming the current selection is the $i$-th number and the range of values is $n$, then the probability of all previous selections not containing $\boldsymbol z$ is:
$$
\prod_{j=1}^{i-1} \frac {n-j}{n-j+1}=\frac {n-i+1}{n}
$$

The probability of selecting $\boldsymbol z$ at the current step is $\dfrac 1{n-i+1}$. Therefore, the probability of selecting $\boldsymbol z$ is $\dfrac 1n$. This is indeed a uniform distribution.

### Method 2

It's the same naive idea as before: just generate without worrying about duplicates. What if we encounter duplicates? Don't worry about it! Remember how we calculate quadratic residues? We pick a number at random, and if it's a duplicate, we don't care. We can just pick another one. The only concern is that after many selections, we might run into duplicates again and again.

However, since we are picking numbers randomly, randomness is built in :) So we have to calculate the expectation.

First, let's solve a similar problem:

Perform a task. Each time there's a probability $p$ of failure and a probability $1-p$ of success. After a failure, we keep trying until success, then stop. Find the expected number of steps to reach success. The expected number can be calculated as follows
$$
\begin{aligned}
E &= \sum_{x=1}^{\infty} p^{x-1}(1-p)x \\
&= \sum_{x=1}^{\infty} p^{x-1}x - \sum_{x=1}^{\infty} p^xx \\
&= 1 + \sum_{x=1}^{\infty} p^x(x+1) - \sum_{x=1}^{\infty} p^xx \\
&= 1 + \sum_{x=1}^{\infty} p^xx + \sum_{x=1}^{\infty} p^x - \sum_{x=1}^{\infty} p^xx \\
&= \sum_{x=0}^{\infty} p^x
\end{aligned}
$$
This is just a geometric series! It becomes
$$
\lim_{n\to \infty}\frac {p^{n+1}-1}{p-1}=\frac 1{1-p}
$$
Oops! The expected number of successes is the inverse of the probability of success! (Although it's a classic result and seems quite intuitive QwQ)

We want to find the complexity of randomly choosing a number that did not appear, so it suffices to compute an upper bound. Obviously, the maximum complexity occurs when selecting the $n$-th number. At this point, the probability of success is $\dfrac {|V|-n+1}{|V|}$. Let $|V|=(n-1)k$, then the expected complexity is
$$
O(\frac 1{\frac {|V|-n+1}{|V|}})=O(\frac {|V|}{|V|-(n-1)})=O(\frac {k}{k-1})
$$
So if we choose $n$ numbers, the total complexity will be $O(n\cdot\dfrac k{k-1})$. However, checking whether a number has appeared before may require using a self-balancing BST due to the large range of values, resulting in a complexity of $O(n\log n\cdot\dfrac k{k-1})$. By omitting $V$, a significant improvement is achieved!

### Frankenstein's Monster (Patchwork Solution)

However, the above algorithm cannot satisfy all scenarios. For instance, when $n=V$, each selection incurs an enormous cost, leading to a shocking expected complexity of $O(n^2)$.

Then, similar to the approach for some $O(n\sqrt n)$ problems, we can choose the method based on which algorithm is faster. Obviously, if $k$ is larger, the $O(n\log n\cdot\dfrac k{k-1})$ method from the discussion below is preferred; otherwise, the $O(|V|+n)$ method from the previous discussion is adopted. But when exactly? Just by solving the equation below, we can determine the threshold:
$$
|V|+n=kn\leq n\log n\cdot\frac k{k-1}
$$

Which leads to:
$$
k^2n-kn(\log n+1)\leq 0
$$

From this, we derive that $k\leq \dfrac {\log n+1}2$. Therefore, let's set a threshold $B=\dfrac {\log n+1}2$. When $k\leq B$, we adopt the former approach; otherwise, we go with the latter. Analysis of the complexity: when $k\leq 2$, since $|V|=k(n-1)$, the complexity is $O(|V|+n)=O(n \log n)$. When $k>B$, $\dfrac k{k-1}<2$, which can be regarded as a constant, so it's also $O(n \log n)$. The overall complexity is $O(n \log n)$.

### Further Optimization

#### Optimization 1

Of course, there's more room for optimization. For instance, if $n\log n\geq |V|$, we can directly apply the $O(|V|)$ approach discussed earlier, or use `std::sort` for constant factor optimizations in time and space. This results in a time and space complexity of $O(\min \{|V|,n\log n\})$. However, given the reasonable threshold derived earlier, this optimization may not be critical.

#### Optimization 2

Another optimization concerns the time complexity. Checking whether a number has appeared can be done not only with a BST but also with a hash table. This would improve the time complexity, but the constant factors can be very large. In this case, the complexity of the second method would become $O(n\cdot \dfrac k{k-1})$. Solve the equation:
$$
|V|+n=kn\leq n\cdot\frac k{k-1}
$$

$$
k^2n-2kn\leq 0
$$

Solving this, we get $0<k\leq 2$. So, let's set $B=2$. If $k\leq B$, use the first approach; otherwise, use the second one. Further analysis of the complexity: When $k\leq 2$, $|V|=k(n-1)$, and $k$ can be regarded as a constant. Thus, the complexity is $O(|V|+n)=O(n)$; when $k>2$, $\dfrac k{k-1}<2$, which can be seen as a constant, resulting in $O(n)$ complexity. The total complexity is $O(n)$.

#### Optimization 3

Still related to checking whether a number has appeared. When $|V|$ is not large and there's enough memory space, we can use the common 'vis' array for the check. Using `std::bitset` can greatly optimize constants. When $|V|\leq 10^8$, consider using this method for constant optimizations.

#### Optimization 4

In many cases, we don't require such randomness. Therefore, we can divide the value range equally into $K$ blocks and solve each block separately. This keeps the time complexity unchanged while reducing the space complexity to $O(\dfrac nK)$ or $O(\dfrac {|V|}K)$.

### Method 3 / Optimization 5

While I was sleeping I thought of another method, method 3. I'm not sure if it's correct. So if you think it is wrong, please tell me in the comments. Specifically, we first randomly select $n$ numbers, then sort and remove duplicates (use radix sorting to accumulate). Let's say we have $m$ numbers left. Now set $n=m$ and solve recursively. I can't prove the complexity here, so let's just present a table:

```
            n/V             Exp
         0.0001               1
         0.0002               1
         0.0004               1
         0.0008               1
         0.0016               1
         0.0032               1
         0.0064               2
         0.0128               2
         0.0256               2
         0.0512               3
         0.1024               4
         0.2048               6
         0.4096              11
         0.8192            47.7
```

$Exp$ represents the average number of times required to obtain at least $n-100$ numbers using the method mentioned above.

It's evident that when $\dfrac n{|V|}$ is relatively small, the expected number of attempts is very small. Therefore, within the above method, if $k$ is large ($\dfrac n{|V|}$ is very small), applying this method to generate the first $n-100$ or first $x\%$ numbers, and then using *Method 2* to generate the rest, can slightly optimize the constant factors in time and space.

Attached is the code for generating the table: [tester.cpp](./BlogCodeSource/UNIG/tester.cpp).

***

After I wrote the implementation of the method above, I realize that if I replace *Method 2* with *Method 3*, will it be faster?

It seems that in *Method 3*, the constant becomes too large when the ratio is inappropriate. But compared to the constant in *Method 2*, is this constant truly large? In addition, the ratio should be less than 0.5, so the constant reaches a maximum of 20. Is this really more optimal?

Indeed it is.

Here is the table using only *Method 3* (unsigned int): [M3table](./BlogCodeSource/UNIG/M3table).

The table above represents the performance of *Method 3* when fully utilizing $n$. We don't use the `n/V=0.8` group, so it looks good.

Running $6\times 10^6$ data points is 3 to 6 times faster than the hash approach.

It appears be slower in cases where the range of value is very small compared to the code above. However, we have a `std::bitset` approach that strictly outperforms the hash approach for small value ranges. Combining these methods results in an optimal solution!

For *Method 3*, we can still optimize! We noticed that the generated numbers are ordered among themselves, only the newly generated numbers are unordered. So we just need to sort and merge the newly generated numbers. Less constant time, get it!

For *Optimization 3*, there's even more optimization. If we want to generate sequence many times, we can pretreat the bitset for better constants. That is, if you use `std::bitset::reset`, it'll be faster than declaring one.

**Here's the final code: [UNIG.cpp](./BlogCodeSource/UNIG/UNIG.cpp).**

Then we can check whether the program is correct using the program below for $n=10^6,a=1,b=10^9$, where $a$ is the lower bound, $b$ is the upper bound:

```cpp
#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#include<cctype>
#include<iomanip>
using namespace std;

#define int long long

int x[10000005];
int cnt[10000001];

signed main() {
    freopen("test.in","r",stdin);
    int n,V=1e9;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i];
    double avg=0;
    double var=0;
    cout.precision(10);
    for(int i=1;i<=n;i++) avg+=x[i];
    avg/=n;
    cout<<"Average number: "<<avg<<endl;
    for(int i=1;i<=n;i++) var+=(x[i]-avg)*(x[i]-avg);
    cout<<"Variance value: "<<var/(n-1)<<endl;
    return 0;
}
```

Result:
```
Average number: 499849719.6
Variance value: 8.33604178e+16
```

We know [mathematically](https://en.wikipedia.org/wiki/Continuous_uniform_distribution) that the expected mean is $\dfrac {a+b}2$ and the variance is $\dfrac {(b-a+1)^2-1} {12}$. That's consistent with the forecast.

***

In this edition, I only write the important content. There's a [Chinese edition of this article](./随机生成一个不重复序列.html). Also, it's the former one. In this edition, there are more interesting things in it. But they are not important.

Thanks to ChatGPT and DeepL. They helped me to improve the English expression of this blog.