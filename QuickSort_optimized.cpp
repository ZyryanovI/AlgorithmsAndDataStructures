#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <stack>

template<typename TS>
int BinarySearch (std::vector<TS> &vect, int low, int high, int key)
{
    int mid;

    if (low == high)
        return low;

    mid = low + ((high - low) / 2);

    if (key > vect[mid])
        return BinarySearch (vect, mid + 1, high, key);
    else{ if (key < vect[mid]){
        return BinarySearch (vect, low, mid, key);
    }
    }

    return mid;
}

template<typename TB>
void BinaryInsertionSort (std::vector<TB> &vect, int left, int right)
{
    int ins, i, j;
    int tmp;

    for (i = left; i <=right; ++i) {
        ins = BinarySearch (vect, left, i, vect[i]);
        if (ins < i) {
            tmp = vect[i];
            for (j = i - 1; j >= ins; j--)
                vect[j + 1] = vect[j];
            vect[ins] = tmp;
        }
    }
}

template<typename TI>
void MyInsertionSort(std::vector<TI> &vect, int left, int right)
{
    for(int i=left; i<=right; ++i)
    {
        TI cur;
        cur=vect[i];
        TI current;
        for(int j=i; j>0 && cur<vect[j-1]; --j)
        {
            current=vect[j];
            vect[j]=vect[j-1];
            vect[j-1]=current;
        }
    }
}

template<typename TP>
void MyPartition(std::vector<TP> &vect, int left, int right)
{
    if(right-left<15)
    {
        MyInsertionSort(vect, left, right);
        return;
    }

    int pivot=vect[left];
    std::swap(vect[left], vect[right]);
    int i=left;
    int j=right-1;
    while(i<=j)
    {
        while(vect[i]<pivot)
            ++i;
        while(vect[j]>=pivot && j>=0)
            --j;
        if(i<j)
        {
            std::swap(vect[i], vect[j]);
            ++i;
            --j;
        }
    }
    std::swap(vect[i], vect[right]);
    MyPartition(vect, left, i-1);
    MyPartition(vect, i+1, right);
}

int main()
{
    std::vector<int> vect;
    int elem;
    while(scanf("%d", &elem)>0)
    {
        vect.push_back(elem);
    }

    MyPartition(vect, 0, vect.size()-1);

    for(int i=9; i<vect.size(); i+=10)
    {
        printf("%d ", vect[i]);
    }


    return 0;
}
