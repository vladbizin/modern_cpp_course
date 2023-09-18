using namespace std;
#include <iostream>



template <size_t index, typename T> class tuple_base
{
private:
    T val;
public:
    tuple_base(T const& v)
    {
        val = v;
    }

    tuple_base(T&& v)
    {
        val = std::move(v);
    }

    T& get()
    {
        return val;
    }
};


//general template
template <size_t index, typename... Types> class tuple_recurr
{
};
//specific template
template <size_t index, typename T, typename... Types> class tuple_recurr <index, T, Types...> : public tuple_base<index, typename remove_reference<T>::type>, public tuple_recurr<index + 1, Types...>
{
public:
    template <typename TArg, typename... TArgs> tuple_recurr(TArg&& arg, TArgs &&... args) : tuple_base<index, typename remove_reference<TArg>::type>(forward<TArg>(arg)), tuple_recurr<index + 1, Types...>(forward<TArgs>(args)...)
    {
    }
};



template <typename T, typename... Types> class Tuple : public tuple_recurr<0, T, Types...>
{
public:
    template <typename... TArgs> Tuple(TArgs &&... args) : tuple_recurr<0, T, Types...>(forward<TArgs>(args)...)
    {
    }
};
//template <typename... TArgs> Tuple(TArgs... args)->Tuple<TArgs...>;



template <size_t index, typename T, typename... Types> struct extract_type_at_index
{
    using type = typename extract_type_at_index<index - 1, Types...>::type;
};
template <typename T, typename... Types> struct extract_type_at_index<0, T, Types...>
{
    using type = T;
};



template <size_t index, typename... Types> auto& get(Tuple<Types...>& t)
{
    return (dynamic_cast<tuple_base<index, typename extract_type_at_index<index, Types...>::type> &>(t)).get();
}



int main()
{
    string a = "hello";
    const char* b = "world";
    double c = 15.521;
    int d = 51;
    //Tuple t(a, b, c, d);
    Tuple<string, const char*, double, int> t(a, b, c, d);
    cout << get<0>(t) << endl << get<1>(t) << endl << get<2>(t) << endl << get<3>(t) << endl;
    return 1;
}