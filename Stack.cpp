/* Дана последовательность N прямоугольников различной ширины и высоты (wi,hi). Прямоугольники расположены, начиная с точки (0, 0),
 на оси ОХ вплотную друг за другом (вправо). Требуется найти M - площадь максимального прямоугольника (параллельного осям координат),
  который можно вырезать из этой фигуры. */
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
/*
class Rectangle{
public:
    int width;
    int height;
    Rectangle(): width(0), height(0)
    {}
    Rectangle(int w=0, int h=0): width(w), height(h)
    {}
    ~Rectangle()
    {}
    int GetWidth()
    {
        return width;
    }
    int GetHeight()
    {
        return height;
    }
    void growWidth(int addw) {
        width += addw;
    }
    int GetArea()
    {
        return width*height;
    }

};
*/

class MyStack{
private:
    int stack_size;
    int buffersize;
    pair<int, int>* buffer = new pair<int, int>[buffersize];
    void grow()
    {
        int new_buffer_size= max(buffersize*2, 1);
        pair<int, int>* new_buffer = new pair<int, int>[new_buffer_size];
        for(int i=0; i<buffersize; i++)
        {
            new_buffer[i]=buffer[i];
        }
        delete[] buffer;
        buffer=new_buffer;
        buffersize=new_buffer_size;
    }
public:
    MyStack(): stack_size(0), buffersize(0)
    {}
    MyStack(int a, int b): stack_size(a), buffersize(b)
    {}
    ~MyStack()
    {
        delete[] buffer;
    }
    int GetSize()
    {
        return buffersize;
    }
    void push(pair<int, int> k)
    {
        if(stack_size==buffersize)
            grow();
        buffer[stack_size]=k;
        stack_size++;
    }
    void pop()
    {
       if(stack_size==0)
            {
                cout<<"Don't do that"<<endl;
            }
           stack_size--;
    }
    pair<int, int> top()
    {
        if(stack_size==0)
        {
            cout<<"Don't do that too"<<endl;
        }
        return buffer[stack_size-1];
    }
    bool isempty()
    {
        if(stack_size==0)
            return 1;
        else
        {
            return 0;
        }
    }
};


int GetMax(vector<pair<int, int> > &vect)
{
    MyStack st;
    st.push(vect[0]);
    int maximum=vect[0].first*vect[0].second;
    for(int i=1; i<vect.size(); i++)
    {
        pair<int, int> last_rect=st.top();
        pair<int, int> cur_rect=vect[i];
        if(cur_rect.second>=last_rect.second)
        {
            st.push(cur_rect);
        }
        else{
            int new_height=last_rect.second;

            while(new_height> cur_rect.second)
            {
                last_rect=st.top();
                st.pop();
                if((last_rect.first*last_rect.second)>maximum)
                {
                    maximum=last_rect.first*last_rect.second;
                }

                if(st.isempty())
                {
                    new_height=cur_rect.second;
                    pair<int, int> r1(make_pair(last_rect.first+cur_rect.first, (new_height=cur_rect.second)));
                 
                    st.push(r1);
                }
                else{
                    pair<int, int> something = st.top();
                    st.pop();
                    something.first+=last_rect.first;
                    st.push(something);
                    
                    int next_height=st.top().second;
                    if(next_height>cur_rect.second)
                    {
                        new_height=next_height;
                    }
                    else{
                        if(next_height==cur_rect.second)
                        {
                            pair<int, int> something = st.top();
                            st.pop();
                            something.first+=cur_rect.first;
                            st.push(something);
                           
                            new_height=cur_rect.second;
                        }
                        else
                        {
                            new_height=cur_rect.second;
                            pair<int, int> r2(make_pair(last_rect.first+cur_rect.first, (new_height=cur_rect.second)));
                            st.push(r2);
                        }
                    }
                }
            }
        }
    }
    return maximum;
}


int main()
{
    int n;
    cin>>n;
    n++;   //чтобы в конце был 0,0 заканчивающий последовательность
    vector<pair<int, int> > vect(n);
    for(int i=0; i<n-1; i++)
    {
        cin>>vect[i].first>>vect[i].second;
    }
    cout<<GetMax(vect);

    return 0;
}
