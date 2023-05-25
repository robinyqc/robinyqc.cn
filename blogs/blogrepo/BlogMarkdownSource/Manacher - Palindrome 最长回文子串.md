## Manacher - Palindrome 最长回文子串

例题：[POJ3974](http://poj.org/problem?id=3974 "POJ3974")

Manacher，俗称马拉车（谐音），用于计算最长回文子串长度，时间复杂度与代码量相较其它解决此问题的算法有压倒性优势。线性时间复杂度。

我们发现偶回文串（长度为偶数的回文串）相较奇回文串更加麻烦。因此我们可以做一个预处理，把原字符串转化成易处理的：在字符串两头和每对相邻字符见加一个特殊字符，比如 '#' 或者 '&' 等等。这样这个字符串无论怎样都是奇回文串了。

然后运行马拉车算法。可以去看这篇 [blog](https://zhuanlan.zhihu.com/p/404216115 "blog")。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char str[1000005],s[2000005],END[3]={'E','N','D'};
int d[2000005],ans,cnt;
void initialize(int len){
	for(int i=0,j=1;i<len;i++,j++)
		s[j]=str[i],s[++j]='#';
}
signed main(){
	scanf("%s",str);
	while(strcmp(str,END)){
		s[0]='#',initialize(strlen(str)),ans=0;memset(d,0,sizeof(d));
		for(int i=0,j,l=0,r=-1,n=2*strlen(str)+1;i<n;i++){
			j=l+r-i,d[i]=max(min(d[j],j-l+1),0);
			if(j-d[j]<l){
				while(i-d[i]>=0&&i+d[i]<n&&s[i-d[i]]==s[i+d[i]])d[i]++;
				l=i-d[i]+1,r=i+d[i]-1;
			}ans=max(ans,d[i]);
		}printf("Case %d: %d\n",++cnt,ans-1);
		scanf("%s",str);
	}
	return 0;
}