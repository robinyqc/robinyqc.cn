#include<iostream>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<random>
#include<queue>
#include<ext/pb_ds/priority_queue.hpp>

template<typename Tp>
class RandomMaker {
    public:

        RandomMaker(int seed):dist(1,1000000000),gen(seed) {}

        Tp operator()() {puts("Not Defined!"); std::exit(1);}

    private:
        std::uniform_int_distribution<> dist;
        std::mt19937 gen;
};

template<>
class RandomMaker<int> {
    public:

        RandomMaker(int seed):dist(1,1000000000),gen(seed) {}

        int operator()() {return dist(gen);}

    private:
        std::uniform_int_distribution<> dist;
        std::mt19937 gen;
};

template<>
class RandomMaker<std::pair<int,int> > {
    public:

        RandomMaker(int seed):dist(1,1000000000),gen(seed) {}

        std::pair<int,int> operator()() {
            return std::make_pair(dist(gen),dist(gen));
        }

    private:
        std::uniform_int_distribution<> dist;
        std::mt19937 gen;
};



template<typename Tp=int,typename Cmp=std::less<Tp>,typename RdMaker=RandomMaker<Tp> >
class PriorityQueueClock{

    public:

        PriorityQueueClock(FILE *output_file,int rd_seed):
            fp(output_file),random(rd_seed),gen(rd_seed) {
            
            printf("Input data size: ");
            scanf("%d",&length);
            printf("Input merge number (If you don't wanna merge input 0): ");
            scanf("%d",&mergecnt);
            if(mergecnt>0) {
                printf("Input merge data size (properly don't exceed 100): ");
                scanf("%d",&mergesize);
            }
            if(((long long)mergesize)*((long long)mergecnt)>5e6) {
                puts("Your PC will boom under this size of data!!!!!");
                puts("Criterion: (merge data size) * (merge number)");
#ifdef __WIN32__
                system("pause");
#endif
                exit(114514);
            }
            puts("Program preparing...\n");
            vec.reserve(length);
            vecto.reserve(length);
            vecind1.reserve(length);
            vecind2.reserve(length);
            vectmp.reserve(mergesize);
            it1.reserve(length);
            it2.reserve(length);
            it3.reserve(length);
            it4.reserve(length);
            it5.reserve(length);
            QQ1.resize(mergecnt);
            QQ2.resize(mergecnt);
            QQ3.resize(mergecnt);
            QQ4.resize(mergecnt);
            QQ5.resize(mergecnt);
            
            puts("Data making...\n");
            for(int i=0;i<length;i++) vec.push_back(random());
            for(int i=0;i<length;i++) vecto.push_back(random());
            for(int i=0;i<length;i++) vecind1.push_back(i);
            std::shuffle(vecind1.begin(),vecind1.end(),gen);
            for(int i=0;i<length;i++) vecind2.push_back(i);
            std::shuffle(vecind2.begin(),vecind2.end(),gen);

            for(int i=0;i<mergecnt;i++) {
                vectmp.clear();
                for(int j=0;j<mergesize;j++) vectmp.push_back(random());
                for(Tp j:vectmp) QQ1[i].push(j);
                for(Tp j:vectmp) QQ2[i].push(j);
                for(Tp j:vectmp) QQ3[i].push(j);
                for(Tp j:vectmp) QQ4[i].push(j);
                for(Tp j:vectmp) QQ5[i].push(j);
            }
            puts("Preparation complete.\n");

#ifdef __WIN32__
            system("pause");
#endif
            puts("");
        }

        

        void PushClock() {

            clock_t start,finish;

            start=clock();
            for(Tp val:vec) Q1.push(val);
            finish=clock();
            fprintf(fp,"Pairing heap operation push time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(Tp val:vec) Q2.push(val);
            finish=clock();
            fprintf(fp,"Thin heap operation push time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(Tp val:vec) Q3.push(val);
            finish=clock();
            fprintf(fp,"Binomial heap operation push time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(Tp val:vec) Q4.push(val);
            finish=clock();
            fprintf(fp,"Binary heap operation push time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(Tp val:vec) Q5.push(val);
            finish=clock();
            fprintf(fp,"Redundant counter binomial heap operation push time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(Tp val:vec) Q6.push(val);
            finish=clock();
            fprintf(fp,"STL heap operation push time usage: %ld ms\n\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

        } 

        void PopClock() {

            clock_t start,finish;

            start=clock();
            while(!Q1.empty()) Q1.pop();
            finish=clock();
            fprintf(fp,"Pairing heap operation pop time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            while(!Q2.empty()) Q2.pop();
            finish=clock();
            fprintf(fp,"Thin heap operation pop time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            while(!Q3.empty()) Q3.pop();
            finish=clock();
            fprintf(fp,"Binomial heap operation pop time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            while(!Q4.empty()) Q4.pop();
            finish=clock();
            fprintf(fp,"Binary heap operation pop time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            while(!Q5.empty()) Q5.pop();
            finish=clock();
            fprintf(fp,"Redundant counter binomial heap operation pop time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            while(!Q6.empty()) Q6.pop();
            finish=clock();
            fprintf(fp,"STL heap operation pop time usage: %ld ms\n\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

        }

        void ModifyClock() {

            for(Tp val:vec) it1.push_back(Q1.push(val));

            for(Tp val:vec) it2.push_back(Q2.push(val));

            for(Tp val:vec) it3.push_back(Q3.push(val));

            // for(Tp val:vec) it4.push_back(Q4.push(val)); 

            for(Tp val:vec) it5.push_back(Q5.push(val));

            clock_t start,finish;

            start=clock();
            for(int i:vecind1) Q1.modify(it1[i],vecto[i]);
            finish=clock();
            fprintf(fp,"Pairing heap operation modify time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(int i:vecind1) Q2.modify(it2[i],vecto[i]);
            finish=clock();
            fprintf(fp,"Thin heap operation modify time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(int i:vecind1) Q3.modify(it3[i],vecto[i]);
            finish=clock();
            fprintf(fp,"Binomial heap operation modify time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            // start=clock();
            // for(int i:vecind1) {
            //     if((clock()-start)/CLOCKS_PER_SEC>=30) {printf("(TLE) "); break;}
            //     Q4.modify(it4[i],vecto[i]);
            // }
            // finish=clock();
            // fprintf(fp,"Binary heap operation modify time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));
            fprintf(fp,"You see binary heap may RE when modifying...\n");

            start=clock();
            for(int i:vecind1) Q5.modify(it5[i],vecto[i]);
            finish=clock();
            fprintf(fp,"Redundant counter binomial heap operation modify time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));
            
            fprintf(fp,"STL heap cannot modify...\n\n");

        }

        void EraseClock() {

            clock_t start,finish;
            start=clock();
            for(int i:vecind2) Q1.erase(it1[i]);
            finish=clock();
            fprintf(fp,"Pairing heap operation erase time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));\

            start=clock();
            for(int i:vecind2) Q2.erase(it2[i]);
            finish=clock();
            fprintf(fp,"Thin heap operation erase time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(int i:vecind2) Q3.erase(it3[i]);
            finish=clock();
            fprintf(fp,"Binomial heap operation erase time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            // start=clock();
            // for(int i:vecind2) {
            //     if((clock()-start)/CLOCKS_PER_SEC>=30) {printf("(TLE) "); break;}
            //     Q4.erase(it4[i]);
            // }
            // finish=clock();
            // fprintf("fp,Binary heap operation erase time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));
            fprintf(fp,"You see binary heap may RE when erasing...\n");

            start=clock();
            for(int i:vecind2) Q5.erase(it5[i]);
            finish=clock();
            fprintf(fp,"Redundant counter binomial heap operation erase time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            fprintf(fp,"STL heap cannot erase...\n\n");
            
        }


        void MergeClock() {

            if(mergecnt==0) return ;

            for(Tp val:vec) Q1.push(val);

            for(Tp val:vec) Q2.push(val);

            for(Tp val:vec) Q3.push(val);

            for(Tp val:vec) Q4.push(val); 

            for(Tp val:vec) Q5.push(val); 
            
            clock_t start,finish;
            start=clock();
            for(auto& i:QQ1) Q1.join(i);
            finish=clock();
            fprintf(fp,"Pairing heap operation merge time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(auto& i:QQ2) Q2.join(i);
            finish=clock();
            fprintf(fp,"Thin heap operation merge time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(auto& i:QQ3) Q3.join(i);
            finish=clock();
            fprintf(fp,"Binomial heap operation merge time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(auto& i:QQ4) {
                if((clock()-start)/CLOCKS_PER_SEC>=30) {fprintf(fp,"(TLE) "); break;}
                Q4.join(i);
            }
            finish=clock();
            fprintf(fp,"Binary heap operation merge time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            start=clock();
            for(auto& i:QQ5) Q5.join(i);
            finish=clock();
            fprintf(fp,"Redundant counter binomial heap operation merge time usage: %ld ms\n",(long)(1.0*(finish-start)/CLOCKS_PER_SEC*1000));

            fprintf(fp,"STL heap cannot merge...\n\n");
        }

    private:
        FILE *fp;

        int length,mergecnt,mergesize;

        __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::pairing_heap_tag> Q1;
        std::vector<__gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::pairing_heap_tag> > QQ1;

        __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::thin_heap_tag> Q2;
        std::vector<__gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::thin_heap_tag> > QQ2;

        __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::binomial_heap_tag> Q3;
        std::vector<__gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::binomial_heap_tag> > QQ3;

        __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::binary_heap_tag> Q4;
        std::vector<__gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::binary_heap_tag> > QQ4;

        __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::rc_binomial_heap_tag> Q5;
        std::vector<__gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::rc_binomial_heap_tag> > QQ5;

        std::priority_queue<Tp> Q6;


        std::vector<Tp> vec,vecto,vectmp;
        std::vector<int> vecind1,vecind2;


        RdMaker random;
        std::mt19937 gen;


        std::vector<typename __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::pairing_heap_tag>::point_iterator> it1;
        std::vector<typename __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::thin_heap_tag>::point_iterator> it2;
        std::vector<typename __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::binomial_heap_tag>::point_iterator> it3;
        std::vector<typename __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::binary_heap_tag>::point_iterator> it4;
        std::vector<typename __gnu_pbds::priority_queue<Tp,Cmp,__gnu_pbds::rc_binomial_heap_tag>::point_iterator> it5;

};


signed main(int argc, char **argv) {
    FILE *fpn = stdout;
    if (argc == 2) {
        fpn = fopen(argv[1], "w");
    }
    PriorityQueueClock<std::pair<int,int> > PQC(fpn,std::time(0));

    PQC.PushClock();
    PQC.PopClock();
    PQC.ModifyClock();
    PQC.EraseClock();
    PQC.MergeClock();
    printf("Calculation finished.\n\n");
    if (argc == 2) {
        printf("\nYou can find the result in %s\n", argv[1]);
    }
#ifdef __WIN32__
    system("pause");
#endif
    return 0;
}
