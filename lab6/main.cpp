
#include <iostream>
#include <cmath>
#include "gtest/gtest.h"

template <int size_>

class polinom {
private:
    int coefs[size_];
public:
    constexpr polinom(const int temp_arr[size_]) {
        for (int i = 0; i < size_; i++) {
            coefs[i] = temp_arr[i];
        }
    }
    ~polinom() = default;
    friend std::ostream &operator<<(std::ostream &out, const polinom &value) {
        int mas[size_];
        for (int i = 0; i < size_; ++i) {
            mas[i] = value.coefs[i];
        }
        int i = size_ - 1;
        if (i == 0) {
            out << mas[0];
        }

        while (i > 0) {
            if (mas[i] != 0) {
                if (i != size_ - 1 && mas[i] > 0) {
                    out << "+";
                } else if (mas[i] == -1) {
                    out << "-";
                }
                if (mas[i] == 1 || mas[i] == -1) {

                    if (i != 1) {
                        out << "x^";
                        out << i;
                    } else
                        out << "x";
                } else if (i == 1) {
                    out << mas[i];
                    out << "x";
                } else {
                    out << mas[i];
                    out << "x^";
                    out << i;
                }
            }
            i--;
        }
        if (size_ != 1) {

            if (mas[0] > 0) {
                out << "+";
                out << mas[0];
            } else if (mas[0] < 0)
                out << mas[0];
        }
        return out;
    }

    constexpr int Get_x(int i){
        return coefs[i];
    }
    constexpr int calculator(const int x) const {
        int tmp = 0;
        int temp = 1;
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < i; ++j) {
                temp = temp * x;
            }
            tmp += (coefs[i] * (temp));
        }
        return tmp;
    }
};

TEST(polinom1, polinomval1) {
int input[5] = {0,1,2,3,4};
polinom <5> polinom1(input);
EXPECT_EQ(polinom1.calculator(1), 10);
}
TEST(polinom2, polinomval2) {
int input[3] = {-1,-1,-1};
polinom <3> polinom2(input);
EXPECT_EQ(polinom2.calculator(3), -31);
}



int main(int argc, const char * argv[]) {

    constexpr int array[3] = {3,5,7};
    constexpr polinom <3> a(array);
    std::cout << a << std::endl;
    static_assert(a.calculator(1) == 15);
    return RUN_ALL_TESTS();
}