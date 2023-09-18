//Container Adapter
//Priority Queue
#include <iostream>
#include <algorithm>

#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>



template<class T, class Container, class Compare = std::less<T> > //vector and deque
class p_queue : protected Container
{
public:

    void push(const T val)
    {
        this->push_back(val);
        std::push_heap(this->begin(), this->end(), Compare());
    }

    T top() const
    {
        return *(this->begin());
    }

    void pop()
    {
        std::pop_heap(this->begin(), this->end(), Compare());
        this->pop_back();
    }

    void print() const
    {
        for (auto x : *this)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    }
};



template<class T, class Compare>                                //forward_list
class p_queue<T, std::forward_list<T>, Compare> : protected std::forward_list<T>
{
public:

    void push(const T val)
    {
        auto itm = this->before_begin();
        for_each(this->begin(), this->end(), [&itm, &val](T& v)
            {
                if (val <= v) itm++;
            }
        );
        this->insert_after(itm, val);
    }

    T top()
    {
        return this->front();
    }

    void pop()
    {
        this->erase_after(this->before_begin());
        this->max_to_first();
    }

    void print() const
    {
        for (auto x : *this)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    }

    void max_to_first()
    {
        auto max_it = std::max_element(this->begin(), this->end(), Compare());
        auto before_max_it = this->end();
        size_t pos = 0;
        for (auto it = this->begin(); it != this->end(); it++)
        {
            if (it == max_it) break;
            pos++;
        }
        pos -= 1;
        if (pos == -1)
        {
            before_max_it = this->before_begin();
        }
        else
        {
            auto it = this->begin();
            for (size_t i = 0; i < pos + 1; i++)
            {
                if (i == pos)
                {
                    before_max_it = it;
                    break;
                }
                it++;
            }
        }


        T to_push = *max_it;
        this->erase_after(before_max_it);
        this->push_front(to_push);
    }
};






template<class T, class Compare>                                //list
class p_queue<T, std::list<T>, Compare> : protected std::list<T>
{
public:

    void push(const T val)
    {
        this->push_back(val);
        this->max_to_first();
    }

    T top() const
    {
        return this->front();
    }

    void pop()
    {
        this->pop_front();
        this->max_to_first();
    }

    void print() const
    {
        for (auto x : *this)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    }

    void max_to_first()
    {
        auto max_it = std::max_element(this->begin(), this->end(), Compare());
        T to_push = *max_it;
        this->erase(max_it);
        this->push_front(to_push);
    }
};






template<class T, class Compare>                                //set
class p_queue<T, std::set<T, Compare>, Compare> : protected std::set<T, Compare>
{
public:

    void push(const T val)
    {
        this->insert(val);
    }

    T top() const
    {
        return *this->rbegin();
    }

    void pop()
    {
        this->erase(std::prev(this->end()));
    }

    void print() const
    {
        for (auto x : *this)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    }
};






template<class T, class Compare>                                //multiset
class p_queue<T, std::multiset<T, Compare>, Compare> : protected std::multiset<T, Compare>
{
public:

    void push(const T val)
    {
        this->insert(val);
    }

    T top() const
    {
        return *this->rbegin();
    }

    void pop()
    {
        this->erase(std::prev(this->end()));
    }

    void print() const
    {
        for (auto x : *this)
        {
            std::cout << x << ' ';
        }
        std::cout << std::endl;
    }
};




int main()
{

    p_queue<double, std::forward_list<double>> p;

    p.push(1);
    p.push(0.5);
    p.push(0);
    p.push(10);

    p.print();
    std::cout << p.top() << std::endl;

    p.pop();

    p.print();
    std::cout << p.top() << std::endl;

    p.pop();

    p.print();
    std::cout << p.top() << std::endl;




}
