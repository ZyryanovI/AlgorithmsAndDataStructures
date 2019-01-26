#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdio.h>

template<typename T>
class HeapForSort{
private:
    int buffer_size=0;
    T* heap_buffer;

public:
    void MakeMyHeap(int new_size)
    {
        buffer_size= new_size;
        for(int i=buffer_size/2 - 1; i>=0; i--)
        {
            SiftDown(i);
        }
    }
    void SiftDown(int index)
    {
        int right=2*index +2;
        int left=2*index +1;
        int biggest=index;
        if(left<buffer_size && heap_buffer[left]>heap_buffer[index])
        {
            biggest=left;
        }
        if(right<buffer_size && heap_buffer[right]>heap_buffer[biggest])
        {
            biggest=right;
        }
        if(biggest != index)
        {
            std::swap(heap_buffer[biggest], heap_buffer[index]);
            SiftDown(biggest);
        }
    }
    T TakeTopAndPop()
    {
        T first= heap_buffer[0];
        heap_buffer[0]=heap_buffer[buffer_size-1];
        heap_buffer[buffer_size-1]=first;
        buffer_size--;
        SiftDown(0);
        return first;
    }

    void HeapSort(T* sorting_arr, int sorting_size)
    {
        heap_buffer=sorting_arr;
        MakeMyHeap(sorting_size);
        T current;
        for(int i=1; i<sorting_size; i++)
        {
            current = TakeTopAndPop();
            heap_buffer[buffer_size]=current;
        }
    }
};


class PersonInformation{
private:
    int date=0;
    int month=0;
    int year=0;
    bool birth_or_death=false;
public:
    int GetDate()
    {
        return date;
    }
    int GetMonth()
    {
        return month;
    }
    int GetYear()
    {
        return year;
    }
    bool GetBirth_Or_Death()
    {
        return birth_or_death;
    }
    void SetDate(int date_new)
    {
        date=date_new;
    }
    void SetMonth(int month_new)
    {
        month=month_new;
    }
    void SetYear(int year_new)
    {
        year=year_new;
    }
    void SetBirth_Or_Death(bool what)
    {
        birth_or_death=what;
    }

    bool operator==(PersonInformation& person)
    {
        return ((this->GetDate() == person.GetDate())&&(this->GetMonth() == person.GetMonth())&&(this->GetYear() == person.GetYear())&&(this->GetBirth_Or_Death()==person.GetBirth_Or_Death()));
    }
    bool operator<(PersonInformation& person)
    {
        return ((this->GetYear()< person.GetYear())||((this->GetYear() == person.GetYear())&&((this->GetMonth()<person.GetMonth())||((this->GetMonth()==person.GetMonth())&&(this->GetDate()<person.GetDate())||((this->GetDate()==person.GetDate())&&(this->GetBirth_Or_Death()<person.GetBirth_Or_Death()))))));
    }
    bool operator>(PersonInformation& person)
    {
        return ((this->GetYear() > person.GetYear())||((this->GetYear() == person.GetYear())&&((this->GetMonth()>person.GetMonth())||((this->GetMonth()==person.GetMonth())&&(this->GetDate()>person.GetDate())||((this->GetDate()==person.GetDate())&&(this->GetBirth_Or_Death()>person.GetBirth_Or_Death()))))));
    }
    PersonInformation operator-(PersonInformation &person)
    {
        this->date=this->date-person.date;
        this->month=this->month-person.month;
        this->year=this->year-person.year;
        return *this;
    }
};

int MyHeapSortForDatesAndCounting(PersonInformation* people, int n)
{

    for(int i=0; i<n; )
    {
        people[i].SetYear(people[i].GetYear()+18);

        if(!(people[i]<people[i+1]))
        {
            std::swap(people[i], people[n-2]);
            std::swap(people[i+1], people[n-1]);
            n-=2;
        }
        else{
            PersonInformation somebirth=people[i];
            somebirth.SetYear(somebirth.GetYear()+62);
            if(!(people[i+1]<somebirth))
            {
                people[i+1].SetDate(somebirth.GetDate());
                people[i+1].SetMonth(somebirth.GetMonth());
                people[i+1].SetYear(somebirth.GetYear());
            }
            i+=2;
        }
    }

    HeapForSort<PersonInformation> heap;
    heap.HeapSort(people, n);

    int maximum=0;
    int quantity=0;

    for(int i=0; i<n; ++i)
    {
        if(people[i].GetBirth_Or_Death())
        {
            ++quantity;
        }
        else
        {
            --quantity;
        }
        if(quantity>maximum)
        {
            maximum=quantity;
        }
    }

    return maximum;
}

int main()
{
    int n=0;
    std::cin>>n;
    PersonInformation* people= new PersonInformation[2*n];
    for(int i=0; i<2*n; )
    {
        int a, b, c;
        std::cin>>a>>b>>c;
        people[i].SetBirth_Or_Death(true);
        people[i].SetDate(a);
        people[i].SetMonth(b);
        people[i].SetYear(c);
        ++i;
        std::cin>>a>>b>>c;
        people[i].SetBirth_Or_Death(false);
        people[i].SetDate(a);
        people[i].SetMonth(b);
        people[i].SetYear(c);
        ++i;
    }

    std::cout<<MyHeapSortForDatesAndCounting(people, 2*n);

    delete[] people;

    return 0;
}
