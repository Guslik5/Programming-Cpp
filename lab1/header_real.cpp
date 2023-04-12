
#include "header.h"

polinom::polinom() {};

polinom::polinom(std::vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        this->arr.push_back(arr[i]);
    }
}

// friend ostream &operator<<(ostream &stream, const polinom &value);
// friend istream &operator>>(istream &stream, const polinom &value);

polinom::~polinom() {};

polinom &polinom::operator=(const polinom &tmp) {
    for (int i = 0; i < tmp.arr.size(); i++) {
        this->arr.push_back(tmp.arr[i]);
    }
    return *this;
}

polinom polinom::operator-(polinom &a) {
    std::vector<int> v_a = this->arr;
    std::vector<int> v_b = a.Get_vec();
    std::vector<int> V_RAZ;
    for (int i = 0; i < v_a.size(); i++) {
        if (i >= v_a.size()) {
            v_a.push_back(0);
        }
        if (i >= v_b.size()) {
            v_b.push_back(0);
        }
        V_RAZ.push_back(v_a[i] - v_b[i]);
    }
    for (int i = 0; i < V_RAZ.size(); i++) {

    }

    polinom raz;
    raz.Set_v(V_RAZ);
    // if (/* condition */)
    // {
    //     /* code */
    // }

    return raz;
}

polinom polinom::operator+(polinom &a) {
    std::vector<int> v_a = this->arr;
    std::vector<int> v_b = a.Get_vec();
    std::vector<int> V_SUM;
    for (int i = 0; i < std::max(v_a.size(), v_b.size()); i++) {
        if (i >= v_a.size()) {
            v_a.push_back(0);
        }
        if (i >= v_b.size()) {
            v_b.push_back(0);
        }
        V_SUM.push_back(v_a[i] + v_b[i]);
    }
    polinom suma;
    suma.Set_v(V_SUM);
    return suma;
}

bool polinom::operator==(const polinom &tmp) {
    if (tmp.arr.size() != this->arr.size()) {
        return false;
    }
    bool flag = true;
    for (int i = 0; i < tmp.arr.size(); i++) {
        if (tmp.arr[i] != this->arr[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}

//a+b
bool polinom::operator!=(const polinom &tmp) {
    if (!(*this == tmp)) return true;
    else return false;

    // if (tmp.arr.size() != this->arr.size())
    // {
    //     return true;
    // }
    // bool flag = false;
    // for (int i = 0; i < tmp.arr.size(); i++)
    // {
    //     if (tmp.arr[i] != this->arr[i])
    //     {
    //         flag = true;
    //         break;
    //     }
    // }
    // return flag;
}

polinom &polinom::operator+=(polinom &a) {
    *this = *this + a;
    return *this;
}

polinom &polinom::operator-=(polinom &a) {
    *this = *this - a;
    return *this;
}

polinom &polinom::operator*(int x) {
    for (int i = 0; i < this->arr.size(); i++) {
        this->arr[i] = arr[i] * x;
    }
    return *this;
}

polinom &polinom::operator++() {
    for (int i = 0; i < this->arr.size(); i++) {
        this->arr[i] = this->arr[i] + 1;
    }
    return *this;
}

polinom &polinom::operator--() {
    for (int i = 0; i < this->arr.size(); i++) {
        this->arr[i] = this->arr[i] - 1;
    }
    return *this;
}

polinom polinom::operator++(int a){
    polinom temp = *this;
    for (int i = 0; i < this->arr.size(); i++) {
        this->arr[i] = this->arr[i] + 1;
    }
    return temp;
}

polinom polinom::operator--(int a){
    polinom temp = *this;
    for (int i = 0; i < this->arr.size(); i++) {
        this->arr[i] = this->arr[i] - 1;
    }
    return temp;
}

polinom polinom::operator*=(int a) {
    return *this * a;
}

polinom polinom::operator/=(int a) {
    return *this / a;
}

polinom &polinom::operator/(int a) {
    for (int i = 0; i < this->arr.size(); i++) {
        this->arr[i] = arr[i] / a;
    }
    return *this;
}

int &polinom::operator[](int i) {
    int &x = this->arr[i];
    return x;
}


std::vector<int> polinom::Get_vec() {
    return this->arr;
}

void polinom::Set_v(std::vector<int> v) {
    this->arr = v;
}


std::istream &operator>>(std::istream &stream, polinom &value) {
    std::vector<int> v;
    std::string str;
    stream >> str;
    short sign = 1;
    // if (str[0] = '-') sign = true;

    // 25334x^3
    int i = 0;
    while (i < str.size()) {
        std::string buffer;
        if (str[i] == '-') {
            sign = -1;
            i++;
            continue;
        }
        if (str[i] == '+') {
            sign = 1;
            i++;
            continue;
        }

        while (str[i] != 'x' && str[i] != '-' && str[i] != '+' && (i < str.size())) {
            buffer.push_back(str[i]);
            i++;
        }
        if (str[i] == '-' || str[i] == '+' || (i >= str.size())) {
            if (v.size() == 0) {
                v.push_back(0);
            }

            v[0] = (stoi(buffer) * sign);
            continue;
        }
        if (str[i] == 'x') {
            if (str[i + 1] == '^') {

                if (i + 2 <= str.size()) {
                    std::string tem;
                    while (((str[i + 2] != '-') && (str[i + 2] != '+')) && (i + 2 <= str.size())) {
                        tem.push_back(str[i + 2]);
                        i++;
                    }

                    int tmp = 0;
                    tmp = std::stoi(tem);

                    // for (int j = i+2; (str[j]!='+') && (str[j]!='-') && (j<=str.size()); ++j)
                    // {
                    //     tmp = (str[j]-'0')*(10^(j-i-2));
                    // }

                    if (tmp != 1) {

                        while (v.size() < tmp + 1) {
                            v.push_back(0);
                        }
                        if (buffer.size() == 0) {
                            v[tmp] = 1 * sign;
                        } else
                            v[tmp] = (stoi(buffer) * sign);
                        i++;
                        i++;
                    } else
                        v[1] = stoi(buffer) * sign;
                } else {
                    if (buffer.size() == 0)
                        v[1] = 1 * sign;
                    else
                        v[1] = stoi(buffer) * sign;
                }
            } else {
                while (v.size() < 2)
                    v.push_back(0);
                if (buffer.size() == 0)
                    v[1] = 1 * sign;
                else
                    v[1] = stoi(buffer) * sign;
            }
        }
        // i++;
    }
    // for (int j = 0; j < v.size(); j++)
    // {
    //     cout << " " << v[j];
    // }

    value.Set_v(v);
    return stream;
}

std::ostream &operator<<(std::ostream &out, polinom &value) {
    std::vector<int> v = value.Get_vec();
    int i = v.size() - 1;
    if (i == 0) {
        out << v[0];
    }

    while (i > 0) {
        if (v[i] != 0) {
            if (i != v.size() - 1 && v[i] > 0) {
                out << "+";
            } else if (v[i] == -1) {
                out << "-";
            }
            if (v[i] == 1 || v[i] == -1) {

                if (i != 1) {
                    out << "x^";
                    out << i;
                } else
                    out << "x";
            } else if (i == 1) {
                out << v[i];
                out << "x";
            } else {
                out << v[i];
                out << "x^";
                out << i;
            }
        }
        i--;
    }
    if (v.size() != 1) {

        if (v[0] > 0) {
            out << "+";
            out << v[0];
        } else if (v[0] < 0)
            out << v[0];
    }

    return out;
}