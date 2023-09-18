//FwdIterator, RvsIterator
//find algorithm example
using namespace std;
#include <iostream>


template <typename T> class LinkedList
{
private:

    class Node
    {
        T data;
        Node* Next_p;
        friend class LinkedList;
    };                                                          

    static Node* Root_p;

    Node* Node_Create(T data)
    {
        Node* NewNode_p = new Node;
        NewNode_p->data = data;
        NewNode_p->Next_p = nullptr;

        return NewNode_p;
    }

    Node*& Get_Root_Node()
    {                                   
        return Root_p;                  
    }

public:

    LinkedList<T>()
    {
        Root_p = nullptr;
    }

    class FwdIterator
    {
    private:
        Node* Bound_Node_p;
    public:
        using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        FwdIterator() : Bound_Node_p(Root_p) { }

        FwdIterator(Node* Node_p) : Bound_Node_p(Node_p) { }

        FwdIterator(FwdIterator const& it) :Bound_Node_p(it.Bound_Node_p) { }

        FwdIterator& operator=(const FwdIterator& it)
        {
            this->Bound_Node_p = it.Bound_Node_p;
            return *this;
        }

        // Prefix ++ overload
        FwdIterator& operator++()
        {
            if (Bound_Node_p)
                Bound_Node_p = Bound_Node_p->Next_p;
            return *this;
        }

        // Postfix ++ overload
        FwdIterator operator++(int)
        {
            FwdIterator it = *this;
            ++(*this);
            return it;
        }

        bool operator!=(const FwdIterator& it)
        {
            return this->Bound_Node_p != it.Bound_Node_p;
        }

        bool operator==(const FwdIterator& it)
        {
            return this->Bound_Node_p == it.Bound_Node_p;
        }

        value_type operator*()
        {
            return Bound_Node_p->data;
        }

        Node* operator->()
        {
            return Bound_Node_p;
        }
    };
    FwdIterator begin()
    {
        return FwdIterator(Root_p);
    }

    FwdIterator end()
    {
        return FwdIterator(nullptr);
    }


    
    class RvsIterator
    {
    private:
        Node* Bound_Node_p;
    public:
        using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        RvsIterator() : Bound_Node_p(Root_p) { }

        RvsIterator(Node* Node_p) : Bound_Node_p(Node_p) { }

        RvsIterator(RvsIterator const& it) :Bound_Node_p(it.Bound_Node_p) { }

        RvsIterator& operator=(const RvsIterator& it)
        {
            this->Bound_Node_p = it.Bound_Node_p;
            return *this;
        }

        // Prefix r++ overload
        RvsIterator& operator++()
        {
            if (this->Bound_Node_p == nullptr)
            {
                return* this;
            }
            else if (this->Bound_Node_p != Root_p)\
            {
                size_t iterations = 0;
                Node* through_p = Root_p;
                while (through_p != this->Bound_Node_p)
                {
                    iterations++;
                    through_p = through_p->Next_p;
                }
                through_p = Root_p;
                size_t i = 0;
                while (i<iterations-1)
                {
                    i++;
                    through_p = through_p->Next_p;
                }
                this->Bound_Node_p = through_p;
                return *this;
            }
            else
            {
                this->Bound_Node_p = nullptr;
                return *this;
            }
        }

        // Postfix r++ overload
        RvsIterator operator++(int)
        {
            RvsIterator it = *this;
            ++(*this);
            return it;
        }

        bool operator!=(const RvsIterator& it)
        {
            return this->Bound_Node_p != it.Bound_Node_p;
        }

        bool operator==(const RvsIterator& it)
        {
            return this->Bound_Node_p == it.Bound_Node_p;
        }

        value_type operator*()
        {
            return Bound_Node_p->data;
        }

        Node* operator->()
        {
            return Bound_Node_p;
        }
    };

     
    RvsIterator rbegin()
    {
        if (Get_Root_Node())
        {
            Node* through_p = Get_Root_Node();
            while (through_p->Next_p)
            {
                through_p = through_p->Next_p;
            }
            return RvsIterator(through_p);
        }
        else
        {
            return RvsIterator(nullptr);
        }
    }

    
    RvsIterator rend()
    {
        return RvsIterator(nullptr);
    }
    






                                                                    


    void push_back(T data)
    {
        Node* Temp_p = Node_Create(data);
        if (Get_Root_Node())
        {
            Node* through_p = Get_Root_Node();
            while (through_p->Next_p)
            {
                through_p = through_p->Next_p;
            }
            through_p->Next_p = Temp_p;
        }
        else
        {
            Get_Root_Node() = Temp_p;
        }
    }


    
    void pop_back()
    {
        if (Get_Root_Node())
        {
            Node* through_p = Get_Root_Node();
            while (through_p->Next_p->Next_p)
            {
                through_p = through_p->Next_p;
            }

            delete through_p->Next_p;
            through_p->Next_p = nullptr;
        }
        else
        {
            throw "EMPTY";
        }
    }
    
};
template <typename T> typename LinkedList<T>::Node* LinkedList<T>::Root_p = nullptr;





int main()
{
    try {
        LinkedList<double> list;
        list.push_back(2.71);
        list.push_back(3.14);
        list.push_back(1.62);
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        cout << "LinkedList output using FwdIterator" << endl;
        for (LinkedList<double>::FwdIterator iterator = list.begin(); iterator != list.end(); iterator++)
        {
            cout << *iterator << " ";
        }
        cout << endl;

        
        cout << "LinkedList output using RvsIterator" << endl;
        for (LinkedList<double>::RvsIterator iterator = list.rbegin(); iterator != list.rend(); iterator++)
        {
            cout << *iterator << " ";
        }
        cout << endl;
        

        double to_find1 = 3.14;

        auto res1 = find(list.begin(), list.end(), to_find1);
        (res1 != list.end()) ? cout << "LinkedList contains " << to_find1 << " (done with FwdIterator)" << '\n' : cout << "LinkedList does not contain " << to_find1 << " (done with FwdIterator)" << '\n';

        
        double to_find2 = 1.41;
        auto res2 = find(list.rbegin(), list.rend(), to_find2);
        (res2 != list.rend()) ? cout << "LinkedList contains " << to_find2 << " (done with RvsIterator)" << '\n' : cout << "LinkedList does not contain " << to_find2 << " (done with RvsIterator)" << '\n';
        
        return 0;
    }
    catch (const char* error)
    {
        cerr << '\n' << error << '\n';
        return 1;
    }
}
