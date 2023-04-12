#include <iostream>
#include <algorithm>
#include <vector>


template <typename T, size_t size_>
class circle_buffer{
private:
    T* arr;
    T* tail;
    T* head;
//    T* ptr_capacity;
    size_t capacity = size_+1;
public:
    char k = false;
    circle_buffer(){
        this->arr = new T[capacity];
        this->tail = &arr[0];
        this->head = &arr[0];
//        this->ptr_capacity = &arr[capacity];
    }
    ~circle_buffer(){
        delete[] this->arr;
    }

    circle_buffer(const circle_buffer& tmp){
        this->arr = tmp.arr;
        this->head = tmp.head;
        this->tail = tmp.tail;
        this->capacity = tmp.capacity;
    }
    void change_capacity(size_t value){
        T* new_arr = new T[value];
        if (this->capacity < value){
            for (int i = 0; i < this->capacity; ++i)
                new_arr[i] = this->arr[i];
        }
        else if (this->capacity > value){
            for (int i = 0; i < value+1; ++i)
                new_arr[i] = this->arr[i];
        }
        else{
            return ;
        }
        this->arr = new_arr;
        head = &arr[0];
        tail = &arr[0];
        this->capacity = value+1;
    }
    void push_back(T value){
//        std::cout << sizeof(T) << std::endl;
        if (this->tail == &arr[capacity-1]) {
            this->tail = &arr[1];
            *(this->tail) = value;

            if (head == &arr[0]){
                head = &arr[1];
            }
        }
        else {
            *(tail + 1) = value;
            this->tail = tail + 1;
        }
        if (this->tail == this->head) {
            if (this->head == &arr[capacity - 1]) {
                this->head = &arr[1];

            }
            else {
                this->head = this->head + 1;
            }
        }
        k = false;
    }


    void push_front(T value) {
//        std::cout << sizeof(T) << std::endl;
        if ((this->head == &arr[1]) || (this->head == &arr[0])) { // для перехода в точке замыкания
            this->head = &arr[capacity - 1];
            *(this->head) = value;

            if (tail == &arr[0]){
                tail = &arr[capacity - 1];
            }

        } else {
            this->head = head-1;
            *(this->head) = value;
        }
        if (this->head == this->tail) { // если таил и хед сошелся
            if (this->tail == &arr[1]) {
                this->tail = &arr[capacity - 1];
            }
            else {
                this->tail = this->tail - 1;
            }
        }
        k = false;
    }

    void pop_back(){
        if (k == true){
            throw std::exception();
        }
        if (this->tail == this->head) {
            k = true;
        }
        if (this->tail == &arr[1]) {
            *(this->tail) = 0;
            this->tail = &arr[capacity-1];
        }
        else {
            *(this->tail) = 0;
            this->tail = tail - 1;
        }
    }
    void pop_front(){
        if (k == true){
            throw std::exception();
        }
        if (this->tail == this->head) {
            k = true;
        }
        if (this->head == &arr[capacity-1]) {
            *(this->head) = 0;
            this->head = &arr[1];
        }
        else {
            *(this->head) = 0;
            this->head = head + 1;
        }
    }
    T operator[](const int x){
        if (x > this->capacity){
            throw std::exception();
        }
        return this->arr[x+1];
    };
    void print_buf(){
        for (int i = 0; i < capacity; ++i) {
            std::cout << this->arr[i] << " ";
        }
    }

private:
    template<typename Iter>
    class Iterator{
        friend class circle_buffer;
    public:
        typedef Iter iterator_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef iterator_type value_type;
        typedef ptrdiff_t difference_type;
        typedef iterator_type& reference;
        typedef iterator_type* pointer;

        iterator_type* value;
        T* arr_;
        T* tail_;
        T* head_;
        size_t capacity_;
    private:
        Iterator(Iter* p, T* arr, T* tail, T* head, size_t capacity) :
        value(p), arr_(arr), tail_(tail), head_(head), capacity_(capacity){ };
    public:
        Iterator(const Iter& it) :
        value(it.value),
        arr_(it.arr_),
        tail_(it.tail_),
        head_(it.head_),
        capacity_(it.capacity_){ };

        Iterator& operator=(Iterator& tmp){
            this->value = tmp.value;
            this->head_ = tmp.head_;
            this->tail_ = tmp.tail_;
            this->arr_ = tmp.arr_;
            this->capacity_ = tmp.capacity_;
            return *this;
        }

        typename Iterator::reference operator*()const {
            return *value;
        }

        bool operator!=(Iterator const & temp) const{
            return this->value != temp.value;
        }

        bool operator==(Iterator& temp){
            return value == temp.value;
        }

        T& get_tail(){
            return this->tail_;
        }

        T& get_head(){
            return this->head_;
        }

        Iterator& operator++(){
            if (this->value == tail_){
                value = &arr_[0];
            }
            else if (value == &arr_[capacity_ - 1]){
                value = &arr_[1];
            }
            else {
                value = value + 1;
            }
            return *this;
        }
        Iterator& operator++(int a){ //постфикс
            Iterator* tmp = this;
            if (this->value == tail_){
                value = &arr_[0];
            }
            else if (value == &arr_[capacity_ - 1]){
                value = &arr_[1];
            }
            else {
                value = value + 1;
            }
            return *tmp;
        }

        Iterator& operator--(){
            if (this->value == head_){
                value = &arr_[0];
            }
            else if (value == &arr_[1]){
                value = &arr_[capacity_ - 1];
            }
            else {
                value = value - 1;
            }
            return *this;
        }

        Iterator& operator--(int a){
            Iterator* tmp = this;
            if (this->value == head_){
                value = &arr_[0];
            }
            else if (value == &arr_[1]){
                value = &arr_[capacity_ - 1];
            }
            else {
                value = value - 1;
            }
            return *tmp;
        }

        Iterator& operator+(int elem){
            for (int i = 0; i < elem; ++i) {
                ++(*this);
            }
            return *this;
        }

        Iterator& operator-(int elem){
            for (int i = 0; i < elem; ++i) {
                (*this);
            }
            return *this;
        }

        Iterator& operator+=(int elem){
            for (int i = 0; i < elem; ++i) {
                ++(*this);
            }
            return *this;
        }

        int& operator-(Iterator const&left){
            Iterator it(value,arr_,tail_ ,head_,capacity_);
            int counter = 0;
            while(it.value != left.value){
                counter++;
                ++it.value;
            }
            return counter;
        }



        bool operator>(Iterator const & tmp){
            return *(this->value) > *(tmp.value);
        }

        bool operator<(Iterator const & tmp){
            return *(this->value) < *(tmp.value);
        }

        bool operator>=(Iterator const & tmp){
            return *(this->value) >= *(tmp.value);
        }

        bool operator<=(Iterator const & tmp){
            return *(this->value) <= *(tmp.value);
        }
    };

public:
    typedef Iterator<T> iterator;
    typedef Iterator<T> const_iterator;
    iterator begin(){
        return iterator(head, arr, tail,head, capacity);
    }
    iterator end(){
        return iterator(&arr[0], arr, tail, head, capacity);
    }
    iterator get_iter_head(){
        return iterator(head, arr, tail, head, capacity);
    }
    iterator get_iter_tail(){
        return iterator(tail, arr, tail, head, capacity);
    }
//    const_iterator begin() const;
//    const_iterator end() const;

};

template<class input_iterator, class unary_predicate>
bool all_of_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first!=last) {
        if (!pred(*first)) return false;
        ++first;
    }
    return true;
    //[](int i){return i%2;}
}

template<class input_iterator, class unary_predicate>
bool any_of_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first!=last) {
        if (pred(*first)) return true;
        ++first;
    }
    return false;
}

template<class input_iterator, class unary_predicate>
bool none_of_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first!=last) {
        if (pred(*first)) return false;
        ++first;
    }
    return true;
}

template<class input_iterator, class unary_predicate>
bool one_of_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    int flag = 0;
    while (first!=last) {
        if (pred(*first)) flag++;
        ++first;
    }
    if (flag == 1)
        return true;
    else
        return false;
}

template <class forward_iterator>
bool is_sorted_my (forward_iterator first, forward_iterator last)
{
    if (first==last)
        return true;
    forward_iterator next = first;
    while (++next!=last) {
        if (*next<*first)     // or, if (comp(*next,*first)) for version (2)
            return false;
        ++first;
    }
    return true;
}

template <class input_iterator, class unary_predicate>
bool is_partitioned_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first!=last && pred(*first)) {
        ++first;
    }
    while (first!=last) {
        if (pred(*first)) return false;
        ++first;
    }
    return true;
}

template<class input_iterator, class unary_predicate>
input_iterator find_not_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    while (first!=last) {
        if (!pred(*first)) return first;
        ++first;
    }
    return last;
}

//проверить
template<class input_iterator, class unary_predicate>
input_iterator find_backward_my (input_iterator first, input_iterator last, unary_predicate pred)
{
//    tmp = &first;
//    first = last;
//    last = *tmp;

    auto tmp = first;

    int flag = 0;
    while (first!=last) {
        if (pred(*first)) {
            tmp = first;
            flag = 1;
        }
        ++first;
    }
    if (flag = 1)
        return tmp;
    else return last;
}

template <class input_iterator, class unary_predicate>
bool is_polindrome_my (input_iterator first, input_iterator last, unary_predicate pred)
{
    std::vector<int> v;
    while (first!=last) {
        v.push_back(pred(*first));
        first++;
    }
    bool flag = true;
    std::vector<int> v_rev = v;
    std::reverse(v_rev.begin(), v_rev.end());

    for (int i = 0; i < v.size(); ++i) {
        if (v_rev[i] != v[i]) {
            flag = false;
            break;
        }
    }
    if (flag)
        return true;
    else
        return false;
}



bool more_4(int a){
    return a>4;
}

int main() {
    circle_buffer<int, 6> buf;
    for (int i = 1; i < 5; ++i) {
        buf.push_back(3);
    }
    buf.push_front(2);
    buf.push_front(7);
    buf.pop_front();
    buf.pop_back();
    buf.push_back(5);
    buf.push_front(7);
//    buf.print_buf();

//    std::cout << buf[1] << std::endl;
//    buf.change_capacity(4);

    buf.print_buf();
    std::cout << std::endl;

    for (auto it = buf.begin();  it != buf.end() ; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    long result = std::count_if(buf.begin(),buf.end(), more_4);

    std::cout << "count if: " <<result << std::endl;

    if (all_of_my(buf.begin(), buf.end(), more_4) )
        std::cout << "Yes.\n";
    else std::cout << "No.\n";
    if(is_polindrome_my(buf.begin(), buf.end(), more_4))
        std::cout << "Polindrome\n";
    else
        std::cout << "No polindrome\n";
//    buf.print_buf();
    return 0;
}