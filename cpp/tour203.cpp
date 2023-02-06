#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <functional>

#include "vtestcommon.h"
#define TOUR_GROUP  tour203_

#define tour_ns__(a,b) a##b
#define tour_ns_(a,b) tour_ns__(a,b)
#define tour_ns(x) tour_ns_(TOUR_GROUP, x)


BEGIN_UNIT_(simple_tuple1, variadic class template, tuple, unisqon, sizeof tuple)
KEYWORDS(variadic template struct, variadic template class)

template<size_t idx, typename T>
struct GetHelper;


struct member{

};

template<typename T>
struct memberT : member{
	memberT(T&x):o(x){}
	T& o;
};

template<typename ... T>
struct MyTuple{

	MyTuple(){}

	MyTuple(std::vector<member>* indexes){}
};



template<typename T, typename ... Rest>
struct MyTuple<T, Rest ...>
{
	MyTuple(const T& first, const Rest& ... rest)
		: first(first)
		, rest(rest...)
	{}
	
	MyTuple(std::vector<member>* indexes, const T& first, const Rest& ... rest)
		: first(first)
		, rest(indexes, rest...)
	{
		indexes->push_back(memberT<T>(this->first));
	}

	T first;
	MyTuple<Rest ... > rest;

	template<size_t idx>
	auto get()
	{
		return GetHelper<idx, MyTuple<T, Rest...>>::get(*this);
	}
};


template<typename ... T>
struct MyTupleN
{
};

template<typename T, typename ... Rest>
struct MyTupleN<T, Rest ...> : public std::vector<member>, public MyTuple<T, Rest...>
{
	MyTupleN(T t, Rest ...r):
		MyTupleN(this, t, r ...)
	{
	}

};


template<typename T, typename ... Rest>
struct GetHelper<0, MyTuple<T, Rest ... >>
{
	static T get(MyTuple<T, Rest...>& data)
	{
		return data.first;
	}
};

template<size_t idx, typename T, typename ... Rest>
struct GetHelper<idx, MyTuple<T, Rest ... >>
{
	static auto get(MyTuple<T, Rest...>& data)
	{
		return GetHelper<idx - 1, MyTuple<Rest ...>>::get(data.rest);
	}
};

struct A {
	int         m1; 
	double      m2; 
	bool        m3;
	std::string m4;
};

struct A2 {
	char        m1;
	double      m2;
	char        m3;
	long        m4;
	char        m5;
	int         m6;
};

template<typename... Xs>
struct unison : public Xs...{
	unison(Xs&&...args) :Xs(args)...{}
	unison(const Xs&...args) :Xs(args)...{}
	unison(){}
};

template <typename T, int n=0>
struct Wrap {
	Wrap(T v) : x(v){}
	T x;
};

int main(int argc, char* argv[])
{
	HORIZONTAL_LINE();
	REFERENCE("https://riptutorial.com/cplusplus/example/19276/variadic-template-data-structures");
	HORIZONTAL_LINE();

	TRACE_CODE(MyTuple<int, double, bool, std::string> data(1, 2.1, true, "Hello"););
	TRACE_CODE(std::tuple<   int, double, bool, std::string>  t(1, 2.1, true, "Hello"););
	TRACE_CODE(unison<Wrap<int>, Wrap<double>, Wrap<bool>, std::string> u(1, 2.1, true, "Hello"););

	TRACE_CODE(MyTuple<char, double, char,long,char, int> data2('a', 1, 'b', 2, 'c', 3););
	TRACE_CODE(std::tuple<   char, double, char,long,char, int>    t2('a', 1, 'b', 2, 'c', 3););
	TRACE_CODE(unison< Wrap<char,0>, Wrap<double,1>, Wrap<char,2>,  Wrap<long,3>, Wrap<char,4>, Wrap<int,5>>   u2('a', 1, 'b', 2, 'c', 3););

	HORIZONTAL_LINEs();
	printf("sizeof     data: %zu\n", sizeof(data));
	printf("sizeof    tuple: %zu\n", sizeof(t));
	printf("sizeof   unison: %zu\n", sizeof(u));
	printf("sizeof struct A: %zu\n", sizeof(A));
	printf("sizeof    data2: %zu\n", sizeof(data2));
	printf("sizeof    tuple: %zu\n", sizeof(t2));
	printf("sizeof   unison: %zu\n", sizeof(u2));
	printf("sizeof structA2: %zu\n", sizeof(A2));
	ANNOTATEs("sizeof(std::tuple) == sizeof(struct) == sizeof(unison)");
	ANNOTATEs("sizeof(std::tuple) != sizeof(simple_tuple)");
	HORIZONTAL_LINEs();

	TRACE_CODE(std::cout << data.get<0>() << std::endl;)
	TRACE_CODE(std::cout << data.get<1>() << std::endl;)
	TRACE_CODE(std::cout << data.get<2>() << std::endl;)

	HORIZONTAL_LINE();
	return 0;
}

END_UNIT// variadic_members



BEGIN_UNIT_(simple_tuple2, variadic class template, implemented by class override)
KEYWORDS(variadic template struct, variadic template class)

template<size_t idx, typename T>
struct GetHelper;

//
//template<0, typename ... T>
//struct MyTupleData{
//
//	MyTupleData(){}
//
//	//MyTuple(std::vector<member>* indexes){}
//};
//
//
//
//template<int N, typename T, typename ... Rest>
//struct MyTupleData<T, Rest ...> : MyTupleData<N-1, Rest ...>
//{
//	MyTupleData(const T& first, const Rest& ... rest)
//		: first(first)
//		//, MyTupleData<N-1, Rest>
//	{}
//	
//	//MyTuple(std::vector<member>* indexes, const T& first, const Rest& ... rest)
//	//	: first(first)
//	//	, rest(indexes, rest...)
//	//{
//	//	indexes->push_back(memberT<T>(this->first));
//	//}
//
//	T first;
//
//	//MyTupleData<Rest ... > rest;
//
//
//	//template<size_t idx>
//	//auto get()
//	//{
//	//	return GetHelper<idx, MyTuple<T, Rest...>>::get(*this);
//	//}
//};

//
//template<typename ... T>
//struct MyTuple{
//
//};

/**
template<typename ... Args>
struct MyTuple<Args.. args>  {

	//MyTuple(Args& ... args)

	//{}

	MyTupleData<sizeof...args, args>
};*/

//template<typename T, typename ... Args>
//struct MyTuple<T, Args...> {
//	//MyTupleData<T, Args...> myfirst;
//};


//
//template<typename ... T>
//struct MyTupleN
//{
//};
//
//template<typename T, typename ... Rest>
//struct MyTupleN<T, Rest ...> : public std::vector<member>, public MyTuple<T, Rest...>
//{
//	MyTupleN(T t, Rest ...r):
//		MyTuple(this, t, r ...)
//	{
//	}
//
//};
//
//
//template<typename T, typename ... Rest>
//struct GetHelper<0, MyTuple<T, Rest ... >>
//{
//	static T get(MyTuple<T, Rest...>& data)
//	{
//		return data.first;
//	}
//};
//
//template<size_t idx, typename T, typename ... Rest>
//struct GetHelper<idx, MyTuple<T, Rest ... >>
//{
//	static auto get(MyTuple<T, Rest...>& data)
//	{
//		return GetHelper<idx - 1, MyTuple<Rest ...>>::get(data.rest);
//	}
//};

struct A {
	int         m1; 
	double      m2; 
	bool        m3;
	std::string m4;
};

struct A2 {
	char        m1;
	double      m2;
	char        m3;
	long        m4;
	char        m5;
	int         m6;
};

int main(int argc, char* argv[])
{
	HORIZONTAL_LINE();
	REFERENCE("https://riptutorial.com/cplusplus/example/19276/variadic-template-data-structures");
	HORIZONTAL_LINE();

	//TRACE_CODE(MyTuple<int, double, bool, std::string> data(1, 2.1, true, "Hello"););
	//TRACE_CODE(std::tuple<   int, double, bool, std::string>  t(1, 2.1, true, "Hello"););
	//TRACE_CODE(MyTuple<char, double, char,long,char, int> data2('a', 1, 'b', 2, 'c', 3););
	//TRACE_CODE(std::tuple<   char, double, char,long,char, int>    t2('a', 1, 'b', 2, 'c', 3););

	HORIZONTAL_LINEs();
	//printf("sizeof     data: %zu\n", sizeof(data));
	//printf("sizeof    tuple: %zu\n", sizeof(t));
	//printf("sizeof struct A: %zu\n", sizeof(A));
	//printf("sizeof     data: %zu\n", sizeof(data2));
	//printf("sizeof    tuple: %zu\n", sizeof(t2));
	//printf("sizeof struct A: %zu\n", sizeof(A2));

	HORIZONTAL_LINEs();

	//TRACE_CODE(std::cout << data.get<0>() << std::endl;)
	//TRACE_CODE(std::cout << data.get<1>() << std::endl;)
	//TRACE_CODE(std::cout << data.get<2>() << std::endl;)

	HORIZONTAL_LINE();
	return 0;
}

END_UNIT// variadic_template_class



namespace tool1{

template<size_t N>
struct Apply {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T && t, A &&... a)
		-> decltype(Apply<N - 1>::apply(
			std::forward<F>(f), std::forward<T>(t),
			std::get<N - 1>(std::forward<T>(t)), std::forward<A>(a)...
		)) // fails if F is class member function on MSVC2015
	{
		return Apply<N - 1>::apply(std::forward<F>(f), std::forward<T>(t),
			std::get<N - 1>(std::forward<T>(t)), std::forward<A>(a)...
		);
	}

};

template<>
struct Apply<0> {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T && dummy, A &&... a)
		-> decltype(std::forward<F>(f)(std::forward<A>(a)...))
	{
		//return std::forward<F>(f)(std::forward<A>(a)...);
		return std::invoke(std::forward<F>(f), std::forward<A>(a)...);
	}
};


template<typename F, typename T>
inline auto apply(F && f, T && t)
-> decltype(Apply< std::tuple_size<
	typename std::decay<T>::type
>::value>::apply(std::forward<F>(f), std::forward<T>(t)))
{
	return Apply< std::tuple_size<
		typename std::decay<T>::type
	>::value>::apply(std::forward<F>(f), std::forward<T>(t));
}

} // end namespace tool


namespace tool2{

// different than tool1
//   1. use invoke to call the function
//   2. the function apply will return auto
// achivement on msvc2015
//   1. function can be class member 


template<size_t N>
struct Apply {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T && t, A &&... a)
	{
		return Apply<N - 1>::apply(std::forward<F>(f), std::forward<T>(t),
			std::get<N - 1>(std::forward<T>(t)), std::forward<A>(a)...
		);
	}

};

template<>
struct Apply<0> {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T && dummy, A &&... a)
	{
		return std::invoke(std::forward<F>(f), std::forward<A>(a)...);
	}
};


template<typename F, typename T>
inline auto apply(F && f, T && t)
{

	//std::cout << "[return type of apply] => " << typeid(Apply<std::tuple_size<typename std::decay<T>::type>::value>
	//		    ::apply(std::forward<F>(f), std::forward<T>(t))).name() << "\n";
	//std::cout << "[       type of F    ] => " << typeid(F).name() << "\n";
	//std::cout << "[       type of f    ] => " << typeid(f).name() << "\n";
	//std::cout << "[       type of T    ] => " << typeid(T).name() << "\n";
	//std::cout << "[       type of t    ] => " << typeid(t).name() << "\n";

	return Apply< std::tuple_size<
		typename std::decay<T>::type
	>::value>::apply(std::forward<F>(f), std::forward<T>(t));
}

} // end namespace tool2


BEGIN_UNIT_(apply_tuple1, pass tuple members to function)
KEYWORDS(apply tuple, invoke)

using namespace tool1;

void foo(int a, bool b, int c){printf("%d %d %d\n", a, b, c);}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/687490/how-do-i-expand-a-tuple-into-variadic-template-functions-arguments/12650100#12650100");
	HORIZONTAL_LINE(); TRACE_SRC(2,3);

	std::tuple<int, bool, int> t = std::make_tuple(20, false, 200);
	tool1::apply(&foo, t);


	HORIZONTAL_LINE();
	return 0;
}
END_UNIT

BEGIN_UNIT_(apply_tuple2, All the tuple members are void(X::*)())

using namespace tool2;

class X {
public:
	void f1() { std::cout << __FUNCSIG__ << '\n'; }
	void f2() { std::cout << __FUNCSIG__ << '\n'; }
	void f3() { std::cout << __FUNCSIG__ << '\n'; }
	void f4() { std::cout << __FUNCSIG__ << '\n'; }
public:

	template<class ...Cs>
	void caller(Cs...args){
		auto print_line = [&](auto p) {
			(this->*p)();
			return 0;
		};
		std::vector<int> rslt = {print_line(std::forward<Cs>(args))...};
	}

};


template<class A, class ...Cs>
void caller(A* a, Cs...args){
	auto print_line = [&](auto p) {
		(a->*p)();
		return 0;
	};
	std::vector<int> rslt = {print_line(std::forward<Cs>(args))...};
}
//
//template <class F, class Args...>
//void batch_run(F f, Args){
//
//}

typedef void (X::*MFUNC)();
int main(int argc, char* argv[]){

	HORIZONTAL_LINE();
	TRACE_CODE(X v);
	HORIZONTAL_LINE();
	ANNOTATE(Use function to apply!);
	TRACE_CODE(auto t1 = std::make_tuple(&v, &X::f1, &X::f2, &X::f3, &X::f4));
	std::cout<< "type of t1 => " << typeid(t1).name() << "\n";
	TRACE_CODE(auto c1 = & caller<X, MFUNC, MFUNC, MFUNC, MFUNC>;);
	std::cout << "type of c1 => " <<typeid(c1).name() << "\n";
	TRACE_CODE(tool2::apply(c1, t1););

	HORIZONTAL_LINEs();
	ANNOTATE(Use class member function to apply on pointer of object!);
	TRACE_CODE(auto t2 = std::make_tuple(&v, &X::f1, &X::f2, &X::f3, &X::f4));
	std::cout << "type of t2 => " << typeid(t2).name() << "\n";
	TRACE_CODE(auto c2 = &X::caller<void (X::*)(), void (X::*)(), void (X::*)(), void (X::*)()>;);
	std::cout << "type of c2 => " << typeid(c2).name() << "\n";
	TRACE_CODE(tool2::apply(c2, t2););

	HORIZONTAL_LINEs();
	ANNOTATE(Use class member function to apply on reference of object!);
	TRACE_CODE(auto t3 = std::make_tuple(std::ref(v), &X::f1, &X::f2, &X::f3, &X::f4));
	std::cout << "type of t3 => " << typeid(t3).name() << "\n";
	TRACE_CODE(auto c3 = &X::caller<MFUNC, MFUNC, MFUNC, MFUNC>;);
	std::cout << "type of c3 => " << typeid(c3).name() << "\n";
	TRACE_CODE(tool2::apply(c3, t3););

	HORIZONTAL_LINE('*');

	HORIZONTAL_LINE();
	ANNOTATE(Use functional to call!);


	return 0;
}

END_UNIT


BEGIN_UNIT_(apply_tuple3, All the tuple members are void(X::*)(int))

using namespace tool2; // why i could reach tool namespace

class X {
public:
	int f1(int n) { std::cout << __FUNCSIG__ << " running against: " << n << '\n'; return 100; }
	int f2(int n) { std::cout << __FUNCSIG__ << " running against: " << n << '\n'; return 200; }
	int f3(int n) { std::cout << __FUNCSIG__ << " running against: " << n << '\n'; return 300; }
	int f4(int n) { std::cout << __FUNCSIG__ << " running against: " << n << '\n'; return 400; }
public:

	template<class N, class ...Cs>
	void caller(N  n, Cs...args){
		auto print_line = [&](auto p) {
			(this->*p)(n);
			return 0;
		};
		std::vector<int> rslt = {print_line(std::forward<Cs>(args))...};
	}

};


template<class A, class N, class ...Cs>
void caller(A* a, N n, Cs...args){
	auto print_line = [&](auto p) {
		(a->*p)(n);
		return 0;
	};
	std::vector<int> rslt = {print_line(std::forward<Cs>(args))...};
}



typedef int (X::*MFUNC)(int);
int main(int argc, char* argv[]){

	HORIZONTAL_LINE();
	TRACE_CODE(X v);
	TRACE_CODE(int n = 88009900);
	HORIZONTAL_LINE();
	ANNOTATE(Use function to apply!);
	TRACE_CODE(auto t1 = std::make_tuple(&v, n, &X::f1, &X::f2, &X::f3, &X::f4));
	std::cout<< "type of t1 => " << typeid(t1).name() << "\n";
	TRACE_CODE(auto c1 = & caller<X, int, MFUNC, MFUNC, MFUNC, MFUNC>;);
	std::cout << "type of c1 => " <<typeid(c1).name() << "\n";
	TRACE_CODE(tool2::apply(c1, t1););

	HORIZONTAL_LINEs();
	ANNOTATE(Use class member function to apply on pointer of object!);
	TRACE_CODE(auto t2 = std::make_tuple(&v, n, &X::f1, &X::f2, &X::f3, &X::f4));
	std::cout << "type of t1 => " << typeid(t2).name() << "\n";
	TRACE_CODE(auto c2 = &X::caller<int, MFUNC, MFUNC, MFUNC, MFUNC>;);
	std::cout << "type of c1 => " << typeid(c2).name() << "\n";
	TRACE_CODE(tool2::apply(c2, t2););

	HORIZONTAL_LINEs();
	ANNOTATE(Use class member function to apply on reference of object!);
	TRACE_CODE(auto t3 = std::make_tuple(std::ref(v), n, &X::f1, &X::f2, &X::f3, &X::f4));
	std::cout << "type of t1 => " << typeid(t3).name() << "\n";
	TRACE_CODE(auto c3 = &X::caller<int, MFUNC, MFUNC, MFUNC, MFUNC>;);
	std::cout << "type of c1 => " << typeid(c3).name() << "\n";
	TRACE_CODE(tool2::apply(c3, t3););

	HORIZONTAL_LINE('*');



	HORIZONTAL_LINE();

	return 0;
}

END_UNIT



BEGIN_UNIT_(iterate_tuple)
using namespace std;

// Function to iterate through all values 
// I equals number of values in tuple 
template <size_t I = 0, typename... Ts>
typename enable_if<I == sizeof...(Ts),
	void>::type
	printTuple(tuple<Ts...> tup)
{
	// If iterated through all values 
	// of tuple, then simply return. 
	return;
}

template <size_t I = 0, typename... Ts>
typename enable_if<(I < sizeof...(Ts)),
	void>::type
	printTuple(tuple<Ts...> tup)
{

	// Print element of tuple 
	cout << I << ": " << get<I>(tup) << "\n";

	// Go to next element 
	printTuple<I + 1>(tup);
}

// Driver Code 
int main(int argc, char* argv[])
{
	HORIZONTAL_LINE();
	REFERENCE("https://www.geeksforgeeks.org/how-to-iterate-over-the-elements-of-an-stdtuple-in-c/");
	HORIZONTAL_LINE();

	// Creating the tuple 
	auto tup = make_tuple(
		1,2,3,4,5,
		"Geeks",
		"for",
		"Geeks");

	// Function call 
	printTuple(tup);
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT
