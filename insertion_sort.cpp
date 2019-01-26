/* Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
Предполагается, что никакие три точки не лежат на одной прямой.
Стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек несколько, то используйте точку с наименьшей координатой y.
Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
Для сортировки точек реализуйте алгоритм сортировки вставками. */

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define pi 3.14

class MyPoint{
private:
    double x;
    double y;
    double angle;
public:
    void SetX(double x1)
    {
        x=x1;
    }
    void SetY(double y1)
    {
        y=y1;
    }
    double GetX()
    {
        return x;
    }
    double GetY()
    {
        return y;
    }
    void SetAngle(double angle1)
    {
        angle=angle1;
    }
    double GetAngle()
    {
        return angle;
    }
    bool operator>(MyPoint &point)
    {
        return this->GetAngle()>point.GetAngle();
    }

    bool operator<(MyPoint &point)
    {
        if(this->GetX()==point.GetX())
        {
            return this->GetY()<point.GetY();
        }
        return this->GetX()<point.GetX();
    }
    void swap (MyPoint &point2)
    {
        std::swap(this->angle, point2.angle);
        std::swap(this->x, point2.x);
        std::swap(this->y, point2.y);
    }
    MyPoint operator=(MyPoint &point)
    {
        this->SetX(point.GetX());
        this->SetY(point.GetY());
        this->SetAngle(point.GetAngle());
        return *this;
    }
};


void FindFirst(std::vector<MyPoint> &vect, int n)
{
    MyPoint first_element = vect[0];
    int j=0;
    for(int i=0; i<n; i++)
    {
        if(vect[i]<first_element)
        {
            first_element=vect[i];
            j=i;
        }
    }
    MyPoint curr;
    curr=vect[j];
    vect[j]=vect[0];
    vect[0]=curr;
}

void SetAnglesFuntion(std::vector<MyPoint> &vect, int n)
{
    for(int i=1; i<n; i++)
    {
        if(vect[i].GetX()==vect[0].GetX())
        {
            vect[i].SetAngle(pi*2);
        }
        else{
                vect[i].SetAngle(atan((vect[i].GetY()-vect[0].GetY())/(vect[i].GetX()-vect[0].GetX())));
        }
    }

}

template<typename T>
void MyInsertionSort(T &vect, int n)
{
    for(int i=1; i<n; i++)
    {
        T cur(1);
        cur[0]=vect[i];
        T current(1);
        for(int j=i; j>1 && cur[0]>vect[j-1]; j--)
        {
            current[0]=vect[j];
            vect[j]=vect[j-1];
            vect[j-1]=current[0];
           //std::swap(vect[j], vect[j-1]);
        }
    }
}


void SortOfPoints(std::vector<MyPoint> &vect, int n)
{
    FindFirst(vect, n);
    SetAnglesFuntion(vect, n);
    MyInsertionSort(vect, n);
}


int main()
{
    int n=0;
    std::cin>>n;
    std::vector<MyPoint> vect(n);

    for(int i=0; i<n; i++)
    {
        double a=0;
        double b=0;
        std::cin>>a>>b;
        vect[i].SetX(a);
        vect[i].SetY(b);
    }

    SortOfPoints(vect, n);

    for(int i=0; i<n; i++)
    {
        std::cout<<vect[i].GetX()<<" "<<vect[i].GetY()<<'\n';
    }

    return 0;
}
