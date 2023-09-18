#include<iostream>
using uint = unsigned int;
#include<vector>;

template<class T> class shared_ptr
{
private:

    T* ptr = nullptr;
    uint* counter = nullptr;

    void clear_data()
    {
        (*this->counter)--;
        if ((*this->counter) <= 0)
        {
            if (this->ptr != nullptr)
                delete ptr;
             delete counter;
        }
    }

public:
    
    shared_ptr() : ptr(nullptr), counter(new uint(0)) //default constructor
    {
    }

    

    ~shared_ptr()
    {
        clear_data();
    }

    shared_ptr(T* ptr) : ptr(ptr), counter(new uint(1)) //constructor with args
    {
    }

    shared_ptr(const shared_ptr& obj)  //copy constructor
    {
        this->ptr = obj.ptr;
        this->counter = obj.counter;
        if (obj.ptr != nullptr)
        {
            (*this->counter)++;
        }
    }

    shared_ptr& operator=(const shared_ptr& obj) //assign operator
    {
        clear_data();
        this->ptr = obj.ptr;
        this->counter = obj.counter;
        if (obj.ptr != nullptr)
        {
            (*this->counter)++;
        }
    }

    shared_ptr(shared_ptr&& obj) //copy constructor with move semantics
    {
        this->ptr = obj.ptr;
        this->counter = obj.counter;
        obj.ptr = nullptr;
        obj.counter = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& obj) //assign constructor with move semantic
    {
        clear_data();
        this->ptr = obj.ptr;
        this->counter = obj.counter;
        obj.ptr = nullptr;
        obj.counter = nullptr;
    }
    
    T& operator*() const
    {
        return *(this->ptr);
    }

    uint use_count() const
    {
        return (* this->counter);
    }
    
    T* get() const
    {
        return this->ptr;
    }

};




template<class T> using sp= shared_ptr<T>;
using string = std::string;
template<class T> using vector = std::vector<T>;

int main()
{
    sp<string> pPete(new string("Pete"));
    std::cout << pPete.use_count() << std::endl;

    sp<string> pAnn(new string("Ann"));
    std::cout << pAnn.use_count() << std::endl;

    vector <sp<string>> people;
    people.push_back(pPete);
    people.push_back(pAnn);
    people.push_back(pPete);
    people.push_back(pAnn);

    std::cout << pPete.use_count() << std::endl;
    std::cout << pAnn.use_count() << std::endl;

    people.pop_back();

    std::cout << pPete.use_count() << std::endl;
    std::cout << pAnn.use_count() << std::endl;

    std::cout << *pPete << std::endl;

    return 0;
}
