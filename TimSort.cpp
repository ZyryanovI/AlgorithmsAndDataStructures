#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <stack>
struct segment{
    int start;
    int lenght;
    segment()
    {}
    segment (int f, int l): start(f), lenght(l)
    {}
};


void selection_sort(std::vector<int> &vect, int left, int right) {
  for (int i=left; i<right;++i) {
    int min_pos = i;
    for (int j=i+1; j<right; ++j) {
      if (vect[j] < vect[min_pos])
        min_pos = j;
    }
    std::swap(vect[i],vect[min_pos]);
  }
}

int GetMinRun(int n)
{
    int r=0;
    while(n>=64)
    {
        n>>=1;
        r|=n&1;
    }
    return r+n;
}

void MyMerge(std::vector<int> &vect, std::vector<segment> &segments, std::vector<int> &tmp, bool is_xy)
{
    segment second;
    segment first=segments[segments.size()-2];
    if(is_xy)
    {
        second=segments[segments.size()-1];
    }
    else{
        second=segments[segments.size()-3];
    }
    if(first.start>second.start)
    {
        std::swap(first, second);
    }
    int position_first=0;
    int position_second=second.start;
    int position= first.start-1;
    int last_first=first.lenght;
    int last_second=second.start+second.lenght;
    copy(vect.begin()+first.start+position_first, vect.begin()+first.start+last_first, tmp.begin());
    int first_amount=0;
    int second_amount=0;
    while(position_first<last_first && position_second<last_second)
    {
        if(tmp[position_first]<vect[position_second])
        {
            ++position;
            vect[position]=tmp[position_first];
            ++position_first;
            ++first_amount;
            second_amount=0;
            if(first_amount==7)
            {
                std::vector<int>::iterator it= upper_bound(tmp.begin()+position_first, tmp.begin()+last_first, vect[position_second]);
                copy(tmp.begin()+position_first, it, vect.begin()+position+1);
                position+= it-(tmp.begin()+position_first);
                position_first+= it-(tmp.begin()+position_first);
            }
        }
        else{
            ++position;
            vect[position]=vect[position_second];
            ++position_second;
            first_amount=0;
            ++second_amount;
            if(second_amount==7)
            {
                std::vector<int>::iterator it = upper_bound(vect.begin()+position_second, vect.begin()+last_second, tmp[position_first]);
                copy(vect.begin()+position_second, it, vect.begin()+position+1);
                position+=it-(vect.begin()+position_second);
                position_second+=it-(vect.begin()+position_second);
            }
        }
    }
    copy(tmp.begin()+position_first, tmp.begin()+last_first, vect.begin()+position+1);
}

void Chek_Merge(std::vector<int> &vect, std::vector<segment> &segments, std::vector<int> &tmp, bool is_merge=false)
{
    while(segments.size()>1)
    {
        int x, y, z;
        x=segments[segments.size()-1].lenght;
        if(segments.size()<2)
        {
            y=0;
        }
        else{
            y=segments[segments.size()-2].lenght;
        }
        if(segments.size()<3)
        {
            z=0;
        }
        else{
           z=segments[segments.size()-3].lenght;
        }
        if(segments.size()>=3 && z<=x+y)
        {
            if(z<x)
            {
                MyMerge(vect, segments, tmp, false);
                segments[segments.size()-3].lenght+=segments[segments.size()-2].lenght;
                segments[segments.size()-2]=segments[segments.size()-1];
                goto POP_BACK;
                
            }
            else{
                MyMerge(vect, segments, tmp, true);
                segments[segments.size()-2].lenght+=segments[segments.size()-1].lenght;
                goto POP_BACK;
              
            }
        }
        else{
            if(is_merge || y<=x)
            {
                MyMerge(vect, segments, tmp, true);
                segments[segments.size()-2].lenght+=segments[segments.size()-1].lenght;
                goto POP_BACK;
                
            }
            else{
                break;
            }
        }
POP_BACK: segments.pop_back();
    }
}


void MyTimSort(std::vector<int> &vect)
{
    int n= vect.size();
    std::vector<int> tmp(n);
    int min_size=GetMinRun(n);
    int start=0;
    int s_size=min_size;
    std::vector<segment> segments;
    segments.reserve((n-1)/min_size +1);

    for(int i=0; i<n; i+=min_size)
    {
        s_size=std::min(min_size, n-i);
        selection_sort(vect, i, i+s_size);
        segments.push_back(segment(i, s_size));
        Chek_Merge(vect, segments, tmp, false);
    }

    while(segments.size()!=1)
    {
        Chek_Merge(vect, segments, tmp, true);
    }
}

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
        while((vect[j]==vect[left1])&&(j>left1))
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

int chek(const void *first, const void *second)
{
    return (*(int*)first - *(int*)second);
}

int main()
{
    std::vector<int> vect;
    int elem;
    while(scanf("%d", &elem)>0)
    {
        vect.push_back(elem);
    }
    std::sort(vect.begin(), vect.end());
    for(int i=9; i<vect.size(); i+=10)
    {
        printf("%d ", vect[i]);
    }

    return 0;
}


