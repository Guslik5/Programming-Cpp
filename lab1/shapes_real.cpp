//
// Created by Guslik on 26.03.2022.
//
#include "shapes.h"

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

Point::Point()
{
    this->x = 0;
    this->y = 0;
}
Point::Point(const Point &temp)
{
    this->x = temp.x;
    this->y = temp.y;
}
Point& Point::operator=(const Point &tmp)
{
    this->x = tmp.x;
    this->y = tmp.y;
    return *this;
}
double Point::getX()
{
    return this->x;
}
double Point::getY()
{
    return this->y;
}
void Point::setX(double x)
{
    this->x = x;
}
void Point::setY(double y)
{
    this->y = y;
}
void Point::Print()
{
    std::cout << "x = " << getX();
    std::cout << std::endl;
    std::cout << "y = " << getY();
}

Polyline::Polyline()
{
    arr.push_back(Point(0, 0));
    arr.push_back(Point(1, 1));
}
Polyline::Polyline(std::vector<Point> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
}
Polyline::Polyline(const Polyline &tmp)
{
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(tmp.arr[i]);
    }
};
Polyline& Polyline::operator=(const Polyline &tmp)
{
    // Выполняем копирование значений
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(tmp.arr[i]);
    }
    // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
    return *this;
}

void Polyline::Print_P()
{
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << std::endl
                  << i << ":" << std::endl;
        arr[i].Print();
    }
}

Blockline::Blockline() : Polyline()
{
    arr.push_back(arr[0]);
}

Blockline::Blockline(std::vector<Point> &arr) : Polyline(arr)
{
    arr.push_back(arr[0]);
}
Blockline::Blockline(Blockline &tmp) : Polyline(tmp){}

Blockline& Blockline::operator=(const Blockline &tmp)
{
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(tmp.arr[i]);
    }
    // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
    return *this;
}

double Blockline::Length_BL()
{
    double l = 0;
    for (int i = 0; i < arr.size() - 1; i++)
    {
        l = l + sqrt(((arr[i].getX() - arr[i + 1].getX()) * (arr[i].getX() - arr[i + 1].getX())) +
                     ((arr[i].getY() - arr[i + 1].getY()) * (arr[i].getY() - arr[i + 1].getY())));
    }
    return l;
}

void Blockline::Print_Length_BL()
{
    std::cout << Length_BL();
}

Polygon::Polygon()
{
    arr.push_back(Point(0, 0));
    arr.push_back(Point(0, 1));
    arr.push_back(Point(1, 1));
}

Polygon::Polygon(const std::vector<Point> &arr)
{
    if (arr.size() < 3)
    {
        throw std::exception();
    }
    for (int i = 0; i < arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
    // this -> arr.push_back((arr[0]));
}

Polygon::Polygon(const Polygon &tmp)
{
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
}
Polygon& Polygon::operator=(const Polygon &tmp)
{
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
    return *this;
}

double Polygon::perimetr_polygon()
{
    double l = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        l = l + sqrt(((arr[i].getX() - arr[i + 1].getX()) * (arr[i].getX() - arr[i + 1].getX())) +
                     ((arr[i].getY() - arr[i + 1].getY()) * (arr[i].getY() - arr[i + 1].getY())));
    }
    return l;
}
void Polygon::Print_perimetr_polygon()
{
    std::cout << perimetr_polygon() << std::endl;
}

double Polygon::square()
{
    double sum = 0;
    double temp = arr[0].getY() * arr[arr.size() - 1].getX();
    for (int i = 0; i < arr.size() - 1; i++)
    {
        temp += arr[i].getX() * arr[i + 1].getY();
    }
    double tmp = -(arr[0].getX() * arr[arr.size() - 1].getY());
    for (int i = 0; i < arr.size(); i++)
    {
        tmp -= arr[i + 1].getX() * arr[i].getY();
    }
    sum = abs(temp + tmp);
    return sum / 2;
}

void Polygon::Print_square_P()
{
    std::cout << square() << std::endl;;
}


Triangle::Triangle() : Polygon(){};

Triangle::Triangle(std::vector<Point> &arr) : Polygon(arr)
{
    if (arr.size() != 3)
    {
        throw std::exception();
    }
    // this -> arr.push_back(arr[0]);
};

Triangle::Triangle(triangle &tmp) : Polygon(arr){};

Triangle Triangle::operator=(Triangle &tmp)
{
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
    return *this;
}


Trapezoid::Trapezoid() : Polygon()
{
    arr.push_back(Point(2, 0));
}

Trapezoid::Trapezoid(std::vector<Point> &arr) : Polygon(arr)
{
    // если вершин не 4, то это не четырехугольник
    if (arr.size() != 4)
    {
        throw std::exception();
    }
    // получился параллелограмм(каждые 2 противоположных стороны параллельны)
    if (((arr[1].getY() - arr[0].getY()) * (arr[3].getX() - arr[2].getX()) ==
         (arr[3].getY() - arr[2].getY()) * (arr[1].getX() - arr[0].getX())) &&
        ((arr[2].getY() - arr[1].getY()) * (arr[3].getX() - arr[0].getX()) ==
         (arr[3].getY() - arr[0].getY()) * (arr[2].getX() - arr[1].getX())))
    {
        throw std::exception();
    }
    // получился просто четырехугольник(все стороны не параллельны)
    if (((arr[1].getY() - arr[0].getY()) * (arr[3].getX() - arr[2].getX()) !=
         (arr[3].getY() - arr[2].getY()) * (arr[1].getX() - arr[0].getX())) &&
        ((arr[2].getY() - arr[1].getY()) * (arr[3].getX() - arr[0].getX()) !=
         (arr[3].getY() - arr[0].getY()) * (arr[2].getX() - arr[1].getX())))
    {
        throw std::exception();
    }
    for (int i = 0; i < arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
}


Point Regular_polygon::vector_cord(Point a, Point b)
{
    Point vec;
    vec.setX(b.getX() - a.getX());
    vec.setY(b.getY() - a.getY());
    return vec;
}
Regular_polygon::Regular_polygon() : Polygon()
{
    arr.push_back(Point(1, 0));
};

Regular_polygon::Regular_polygon(std::vector<Point> &arr) : Polygon(arr)
{

    for (int i = 0; i < arr.size() - 2; i++)
    {
        double a = sqrt(pow((arr[i + 1].getX() - arr[i].getX()), 2) +
                        pow((arr[i + 1].getY() - arr[i].getY()), 2));
        double v = sqrt(pow((arr[i + 2].getX() - arr[i + 1].getX()), 2) +
                        pow((arr[i + 2].getY() - arr[i + 1].getY()), 2));

        if (sqrt(pow((arr[i + 1].getX() - arr[i].getX()), 2) +
                 pow((arr[i + 1].getY() - arr[i].getY()), 2)) !=
            (sqrt(pow((arr[i + 2].getX() - arr[i + 1].getX()), 2) +
                  pow((arr[i + 2].getY() - arr[i + 1].getY()), 2))))
        {
            throw std::exception();
        }
    }
    double cosin_start = 0;
    double cosin_finish = 0;
    for (int i = 0; i < arr.size() - 2; i++)
    {
        Point a = vector_cord(arr[i], arr[i + 1]);
        Point b = vector_cord(arr[i + 1], arr[i + 2]);
        double t1 = (a.getX() * b.getX());
        double t2 = (a.getY() * b.getY());
        double t3 = sqrt(pow(a.getX(), 2) + pow(a.getY(), 2));
        double t4 = sqrt(pow(b.getX(), 2) + pow(b.getY(), 2));

        cosin_start = (t1 + t2) / (t3 * t4);
        if ((cosin_start != cosin_finish) && (i != 0))
        {
            throw std::exception();
        }
        cosin_finish = (t1 + t2) / (t3 * t4);

        // double n = ((arr[i + 1].getX() * arr[i + 2].getX()) + (arr[i + 1].getY() * arr[i + 2].getY())) /
        //            (sqrt(pow(arr[i + 1].getX(), 2) + pow(arr[i + 1].getY(), 2)) *
        //             sqrt((pow(arr[i + 2].getX(), 2) + pow(arr[i + 2].getY(), 2))));

        // if (((arr[i].getX() * arr[i + 1].getX()) + (arr[i].getY() * arr[i + 1].getY())) /
        //         (sqrt(pow(arr[i].getX(), 2) + pow(arr[i].getY(), 2)) *
        //          sqrt(pow(arr[i + 1].getX(), 2) + pow(arr[i + 1].getY(), 2))) !=
        //     ((arr[i + 1].getX() * arr[i + 2].getX()) + (arr[i + 1].getY() * arr[i + 2].getY())) /
        //         (sqrt(pow(arr[i + 1].getX(), 2) + pow(arr[i + 1].getY(), 2)) *
        //          sqrt(pow(arr[i + 2].getX(), 2) + pow(arr[i + 2].getY(), 2))))
        // {
        //     throw exception();
        // }
    }
};

Regular_polygon::Regular_polygon(const Regular_polygon &tmp) : Polygon(tmp){};

Regular_polygon& Regular_polygon::operator=(const Regular_polygon &tmp)
{
    for (int i = 0; i < tmp.arr.size(); i++)
    {
        this->arr.push_back(arr[i]);
    }
    return *this;
}


