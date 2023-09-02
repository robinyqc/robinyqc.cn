#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<random>
#include<ctime>
using namespace std;

signed main() {
    vector<int> v;
    cout.precision(13);
    int V=1e7;
    uniform_int_distribution<> dist(1,V);
    cout<<setw(15)<<"n/V"<<' '<<setw(15)<<"Exp"<<endl;
    for(int n=1000;n<=10000000;n*=2) {
        double rr=0;
        for(int sd=1;sd<=10;sd++) {
            mt19937 gen(sd+time(0)+clock());
            v.clear();
            int cnt=0;
            while((int)v.size()<=n-100) {
                while((int)v.size()<n) v.push_back(dist(gen));
                sort(v.begin(),v.end());
                v.erase(unique(v.begin(),v.end()),v.end());
                cnt++;
            }
            rr+=cnt;
        }
        cout<<setw(15)<<double(n)/V<<' '<<setw(15)<<rr/10<<endl;
    }
    return 0;
}