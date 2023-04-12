//
// Created by Guslik on 26.03.2022.
//

#ifndef LABA_1_SHAPES_H
#define LABA_1_SHAPES_H
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <cmath>
class Point
{
private:
    double x, y;
public:
    Point(double x, double y);
    Point();
    ~Point() = default;
    Point(const Point &temp);
    Point &operator=(const Point &tmp);
    double Get_x();
    double Get_y();
    void Set_x(double x);
    void Set_y(double y);
    void Print();
};

class Polyline {
protected:
    std::vector<Point> arr;

public:
    Polyline();
    Polyline(std::vector<Point> &arr);
    Polyline(const Polyline &tmp);
    Polyline &operator=(const Polyline &tmp);
    ~Polyline() = default;
    void Print_P();
};
class Blockline : public Polyline {
public:
    Blockline();
    Blockline(std::vector<Point> &arr);
    Blockline(Blockline &tmp);
    Blockline &operator=(const Blockline &tmp);
    ~Blockline() = default;
    double Length_BL();
    void Print_Length_BL();
};
class Polygon {
private:
    std::vector<Point> arr;

public:
    Polygon();
    Polygon(const std::vector<Point> &arr);
    Polygon(const Polygon &tmp);
    Polygon &operator=(const Polygon &tmp);
    ~Polygon() = default;
    double perimetr_polygon();
    void Print_perimetr_polygon();
    double square();
    void Print_square_P();
};
class Triangle : public Polygon {
private:
    std::vector<Point> arr;

public:
    Triangle();
    Triangle(std::vector<Point> &arr);
    Triangle(Triangle &tmp);
    Triangle operator=(Triangle &tmp);
    ~Triangle() = default;
};
class Trapezoid : public Polygon {
private:
    std::vector<Point> arr;

public:
    Trapezoid();
    Trapezoid(std::vector<Point> &arr);
    ~Trapezoid() = default;
};
class Regular_polygon : public Polygon {
private:
    std::vector<Point> arr;

public:

    Point vector_cord(Point a, Point b);
    Regular_polygon();
    Regular_polygon(std::vector<Point> &arr);
    Regular_polygon(const Regular_polygon &tmp);
    Regular_polygon &operator=(const Regular_polygon &tmp);
    ~Regular_polygon() = default;
};

#endif //LABA_1_SHAPES_H
