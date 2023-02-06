#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>

#include "vtestcommon.h"
#define TOUR_GROUP  tour204_

//#define tour_ns__(a,b) a##b
//#define tour_ns_(a,b) tour_ns__(a,b)
//#define tour_ns(x) tour_ns_(TOUR_GROUP, x)


BEGIN_UNIT_(template_adaptive_ptr, recognize type of pointer automatically)

class A{
public:
	void a(){printf("object(%p) %s\n", this, __FUNCTION__);}
	int  echo(int echo){return echo;}
	std::string toString(){return "";}
	size_t address(){return (size_t)this;}
};

template <class T, class = void>
struct element_type {
    using type = T;
};

template <class T>
struct element_type<T, std::void_t<typename std::pointer_traits<T>::element_type>> {
    using type = typename std::pointer_traits<T>::element_type;
};


template<class T>
class W {
public:
using element_type_t = typename element_type<T>::type;
using MEM_FUNC = int (element_type_t::*)(int);//using MEM_FUNC = typename int (element_type_t::*)(int);
private:
	//element_type_t m;
	T o;
	MEM_FUNC f;
public:
	W(T o, MEM_FUNC f);//:m(m){}	
	//W(T o, MEM_FUNC f):o(o),f(f){}
	void w(){printf("Object:%zu %d\n", o->address(),  std::invoke(f,o, 5));}
	void p(){ printf("Object:%zu %d\n", o->address(), (o->*f)(5)); }

};
template<class T>
W<T>::W(T o, MEM_FUNC f):o(o), f(f){}
template<class T>
W<T> construct_W(T o, typename W<T>::MEM_FUNC f){ return W<T>(o, f); }


template <class T>
using element_type_t = typename element_type<T>::type;

template<class T>
void foo(T t){
	element_type_t<T> x;
	t->a();
	x.a();
}
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/a/41961885");
	REFERENCE("class template type parameters deducation => https://social.msdn.microsoft.com/Forums/en-US/91fd1924-330d-4451-ab2e-2b65a6b75905/error-c2955-use-of-class-template-requires-template-argument-list");
	HORIZONTAL_LINE();

	A* a1 = new A();
	auto a2 = std::make_shared<A>();
	foo(a1);
	foo(a2);
	W<decltype(a1)> w1(a1, &A::echo);
	W<decltype(a2)> w2(a2, &A::echo);
	auto w3 = construct_W(a1, &A::echo);
	w1.w(); w1.p();
	w2.w(); //w2.p();
	w3.w();
	return 0;
}

END_UNIT
