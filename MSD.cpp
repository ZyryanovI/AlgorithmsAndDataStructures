#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdio>
#define abc_size 256
template<typename T1>
void MyCountingSort(T1 *vect, int *counting_vect, int n, int byte)
{
    for(int i=0; i<abc_size; i++)
    {
        counting_vect[i]=0;
    }
    for(int i=0; i<n; i++)
    {
        counting_vect[vect[i][byte]]++;
    }
    int resoult=0;
    for(int i=1; i<abc_size; i++)
    {
        counting_vect[i]+=counting_vect[i-1];
    }
    T1* resoult_vect = new T1[n];

    for(int i=n-1; i>=0; i--)
    {
        counting_vect[vect[i][byte]]--;
        resoult_vect[counting_vect[vect[i][byte]]]=vect[i];
    }
    for(int i=0; i<n; i++)
    {
        vect[i]=resoult_vect[i];
    }
    delete[] resoult_vect;

}

template<typename T>
void MyMSD(T* vect, int n, int byte)
{
    if(n<=1)
    {
        return;
    }
    int *counting_vect= new int[abc_size+1];
    counting_vect[abc_size]= n-1;

    MyCountingSort(vect, counting_vect, n, byte);

    for(int i=1; i<abc_size; i++)
    {
        MyMSD(vect + counting_vect[i],counting_vect[i+1]-counting_vect[i], byte+1);
    }
    delete[] counting_vect;
}


int main()
{
    std::string* vect = new std::string[100000];
    int i=0;
    while(std::cin>>vect[i])
    {
        i++;
    }
    int n = i;

    MyMSD(vect, n, 0);

    for(int i=0; i<n; i++)
    {
        std::cout<<vect[i]<<std::endl;
    }

    return 0;
}
