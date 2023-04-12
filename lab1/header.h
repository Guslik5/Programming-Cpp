
#ifndef polinom_h_INCLUDED
#define polinom_h_INCLUDED
#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
#include <string>

class polinom
{
private:
    std::vector<int> arr;
public:
    polinom();
    polinom(std::vector<int> &arr);
    ~polinom();
    friend std::ostream &operator<<(std::ostream &stream, const polinom &value);
    friend std::istream &operator>>(std::istream &stream, const polinom &value);
    polinom &operator=(const polinom &tmp);
    polinom operator-(polinom &a);
    polinom operator+(polinom &a);
    bool operator==(const polinom &tmp);
    bool operator!=(const polinom &tmp);
    polinom& operator+=(polinom& a);
    polinom& operator-=(polinom& a);
    polinom& operator*(int x);
    polinom& operator++();
    polinom operator++(int a);
    polinom operator--(int a);
    polinom& operator--();
    polinom operator*=(int a);
    polinom operator/=(int a);
    polinom& operator/(int a);
    int& operator[](int i);
    std::vector<int> Get_vec();
    void Set_v(std::vector<int> v);
    // std::istream &operator>>(istream &stream, polinom &value);
    // std::ostream &operator<<(ostream &out, polinom &value);
};
std::istream &operator>>(std::istream &stream, polinom &value);
std::ostream &operator<<(std::ostream &out, polinom &value);
#endif

