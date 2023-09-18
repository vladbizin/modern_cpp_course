//Bizin Vladislav 335 
//myvector template with size, reverse, clear, push_back, pop_back, swap, sort
//instanced with mystring class

#include <iostream>
#include <vector>
using namespace std;


template <class T, size_t defsize = 0> class MyVector
{
private:

	T* p;
	size_t len;

public:

	MyVector(size_t size=defsize) :len(size), p(nullptr)
	{
		if (this->len != 0)
		{
			this->p = new T[this->len];
		}
	};

	MyVector(const MyVector<T, defsize>& obj) : len(obj.len)
	{
		if (this->len == 0) p = nullptr;
		else
		{
			this->p = new T[this->len];
		}

		for (size_t i = 0; i < this->len; i++)
		{
			(this->p)[i]=obj.p[i];
		}

	}
	~MyVector()
	{
		delete[] p;
	}

	void clear()
	{
		delete[] this->p;
		this->p = nullptr;
		this->len = 0;
	}

	const size_t size() const
	{
		return this->len;
	}

	void reverse()
	{
		for (size_t i = 0, j = this->len - 1; i < (this->len) / 2; i++, j--)
		{
			T tmp = (this->p)[i];
			(this->p)[i] = (this->p)[j];
			(this->p)[j] = tmp;
		};
	};

	void push_back(const T& in)
	{
		T* newp = new T[++(this->len)];
		for (size_t i = 0; i < this->len-1; i++)
		{
			newp[i] = (this->p)[i];
		}
		newp[this->len - 1] = in;
		delete[] this->p;
		this->p = newp;
	};

	void pop_back()
	{
		T* newp=new T[--(this->len)];
		for (size_t i = 0; i < this->len; i++)
		{
			newp[i] = (this->p)[i];
		}
		delete[] this->p;
		this->p = newp;
	}

	void swap(MyVector<T, defsize>& obj)
	{
		T* tmp = obj.p;
		size_t tmplen = obj.len;
		obj.p = this->p;
		obj.len = this->len;
		this->p = tmp;
		this->len = tmplen;
	}

	void sort()
	{
		for (size_t i = 0; i < this->len; i++)
		{
			for (size_t j = 0; j < this->len; j++)
			{
				if ((this->p)[i] < (this->p)[j])
				{
					T tmp = (this->p)[i];
					(this->p)[i] = (this->p)[j];
					(this->p)[j] = tmp;
				}
			}
		}

	}

	T& operator[](const size_t indx)
	{
		return (this->p)[indx];
	}

	T operator[](const size_t indx) const
	{
		return (this->p)[indx];
	}
};


template<class T, int defsize = 0>
ostream& operator<<(ostream& os, const MyVector<T, defsize>& obj)
{
	for (size_t i = 0; i < obj.size(); i++)
	{
		os << i <<": " << obj[i] << '\n';
	}
	return os;
}





class mystring :public vector<char>
{
public:

	mystring()
	{}

	mystring(const char* str) :vector<char>(strlen(str))
	{
		for (size_t i = 0; i < strlen(str); i++)
		{
			this->at(i) = str[i];
		}
	}

	
	char& operator[] (size_t indx)
	{
		return this->at(indx);
	}
	
	char operator[] (size_t indx) const
	{
		return this->at(indx);
	}
	
};

ostream& operator<<(ostream& os, const mystring& obj)
{
	for (size_t i=0; i<obj.size(); i++)
	{
		os << obj[i];
	}
	return os;
}

bool operator<(const mystring& objl, const mystring& objr)
{
	int minlen = (objl.size() < objr.size() ? objl.size() : objr.size());
	for (int i = 0; i < minlen; i++)
	{
		if (objl[i] < objr[i]) return true;
		if (objl[i] > objr[i]) return false;
	}
	if (minlen == objl.size()) return true; else return false;
}

bool operator>(const mystring& objl, const mystring& objr)
{
	int minlen = (objl.size() < objr.size() ? objl.size() : objr.size());
	for (int i = 0; i < minlen; i++)
	{
		if (objl[i] > objr[i]) return true;
		if (objl[i] < objr[i]) return false;
	}
	if (minlen == objl.size()) return false; else return true;
}









int main()
{
	
	mystring a("Hello");
	mystring b("world");
	mystring c("Alice");
	mystring d("Bob");
	MyVector<mystring, 3> v;
	v[0] = a;
	v[1] = b;
	v[2] = c;

	mystring a1("veni");
	mystring b1("vidi");
	mystring c1("vici");
	MyVector<mystring, 3> v1;
	v1[0] = a1;
	v1[1] = b1;
	v1[2] = c1;


	cout << v << endl;
	cout << v1 << endl;

	v.push_back(d);
	cout <<"pushed back with \'"<< d << "\': \n" << v << endl;

	v.sort();
	cout <<"sorted: \n"<< v << endl;

	v.reverse();
	cout << "reversed: \n" << v << endl;

	v.pop_back();
	cout << "popped back: \n" << v << endl;

	v.swap(v1);

	cout << "swapped:\n" << v << '\n' << v1 << endl;

	return 1;
}