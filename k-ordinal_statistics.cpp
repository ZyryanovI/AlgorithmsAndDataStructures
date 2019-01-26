#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdio.h>

template<typename TC>
void ChoosePivot(std::vector<TC> &vect, int left_iter, int right_iter)
{
    int mid_iter = (left_iter+right_iter)/2;

    if(vect[mid_iter]>vect[right_iter])
    {
        std::swap(vect[mid_iter], vect[right_iter]);
    }
    if(vect[left_iter]<vect[mid_iter])
    {
        std::swap(vect[left_iter], vect[mid_iter]);
    }
    if(vect[left_iter]>vect[right_iter])
    {
        std::swap(vect[left_iter], vect[right_iter]);
    }
}

template<typename TP>
int MyPartition(std::vector<TP> &vect, int left1, int right1)
{
    ChoosePivot(vect, left1, right1);

    int i=right1;
    int j=right1;
    int counter=0;
    while(j>left1)
    {
        while((vect[j]==vect[left1])&&(j>left1))  ///j
        {
            if(counter==1)
            {
                std::swap(vect[i], vect[j]);
                i--;
                j--;
            }
            else{
                j--;
                if(counter==0)
            {
                counter=1;
            }
            else{
                counter=0;
            }
            }
        }

        while((vect[j]<vect[left1])&&(j>left1))
        {
            j--;
        }

        while((vect[j]>vect[left1])&&(j>left1))
        {
            std::swap(vect[j], vect[i]);
            i--;
            j--;
        }
    }
    std::swap(vect[left1], vect[i]);

    return i;
}

template<typename T>
T FindOrderStatistics(std::vector<T> &vect, int n, int k)
{
    int left=0;
    int right=n;
    int pivot = -1;
    while(pivot!=k)
    {
        pivot= MyPartition(vect, left, right);
        if(pivot<k)
        {
            left=pivot+1;
        }
        else{
            right=pivot-1;
        }
    }
    return vect[k];
}

int main()
{
    int n=0, k=0;
    std::cin>>n>>k;
    std::vector<int> vect(n);
    for(int i=0; i<n; i++)
    {
        std::cin>>vect[i];
    }

    std::cout<<FindOrderStatistics(vect, n-1, k);
    return 0;
}
