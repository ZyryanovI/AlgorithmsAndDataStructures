/*Вовочка ест фрукты из бабушкиной корзины.
В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
 которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину.
  Фрукт массы 1гр он съедает полностью.

Определить за сколько подходов Вовочка съест все фрукты в корзине. */
/* создаем кучу, на ней решаем задачу. В корне хранится наибольший элемент, пока суммарный вес меньше максимального, который может поднять - берем элемент,
 если не 1 - половину кладем в вектор, чтобы случайно не взять половину в этот же ход, поддерживая максимум в корне.Когда набрали максимум - перекладываем все из вектора в кучу и считаем шаг */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class heap{
private:
    int* buffer=new int[0];
    int heap_size=0;
    int buffer_size=0;
    void Grow()
    {
        int new_buffer_size=max(buffer_size*2, 1);
        int* new_buffer= new int[new_buffer_size];
        for(int i=0; i<heap_size; i++)
        {
            new_buffer[i]=buffer[i];
        }
        delete[] buffer;
        buffer=new_buffer;
        buffer_size=new_buffer_size;
    }
public:
    heap(int* data, int data_size)
    {
        while(buffer_size<data_size)
        {
            Grow();
        }
        heap_size=data_size;
        for(int i=0; i<data_size; i++)
        {
            buffer[i]=data[i];
        }
        for(int i= heap_size/2-1; i>=0; i--)
        {
            SiftDown(i);
        }
    }
    ~heap()
    {
        delete[] buffer;
    }

    int GetSize()
    {
        return heap_size;
    }

    int Peek()
    {
        if(heap_size>0)
        {
            return buffer[0];
        }
        return -1;
    }

    int PeekAndPop()
    {
        int element = buffer[0];
        swap(buffer[0], buffer[heap_size]);
        heap_size--;
        SiftDown(0);
        return element;
    }

    void AddElement(int element)
    {
        heap_size++;
        if(heap_size>buffer_size)
        {
            Grow();
        }
        buffer[heap_size]=element;
        SiftUp(heap_size);
    }

    void SiftUp(int index)
    {
        while(index>0)
        {
            int parent= (index-1)/2;
            if(buffer[index]<=buffer[parent])
            {
                return;
            }
            swap(buffer[index], buffer[parent]);
            index=parent;
        }
    }

    void SiftDown(int index)
    {
        int left=index*2+1;
        int right=index*2+2;
        int maxson=index;
        if((left<heap_size)&&(buffer[left]>buffer[index]))
        {
            maxson=left;
        }
        if((right<heap_size)&&(buffer[right]>buffer[maxson]))
        {
            maxson=right;
        }
        if(maxson!=index)
        {
            swap(buffer[index], buffer[maxson]);
            SiftDown(maxson);
        }
    }
};

int CountSteps(int* fruits, int n, int max_weight)
{
    int steps=0;
    int sum_weight=0;
    heap fruits_heap(fruits, n);
    vector<int> vect;
    while(fruits_heap.Peek())
    {
        while((fruits_heap.Peek()+sum_weight <= max_weight)&&(fruits_heap.GetSize()>0))
        {
            sum_weight+=fruits_heap.Peek();
            vect.push_back(fruits_heap.PeekAndPop()/2);
        }
        while(vect.size()>0)
        {
            fruits_heap.AddElement(vect[vect.size()-1]);
            vect.pop_back();
        }
        sum_weight=0;
        steps++;
    }
    return steps;
}


int main()
{
    int n=0;
    cin>>n;
    int* fruits= new int[n];
    for(int i=0; i<n; i++)
    {
        cin>>fruits[i];
    }
    int k=0;
    cin>>k;
    cout<<CountSteps(fruits, n, k);

    delete[] fruits;
    return 0;
}
