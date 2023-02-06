#include "vtestcommon.h"
#define TOUR_GROUP tour8_

#include <stdio.h>
#include <initializer_list>
#include <string>
#include <iostream>
#include <functional>
#include <random>
#include <memory>
#include <regex>
#include <utility>


BEGIN_UNIT_(reference, reference declerator, glvalue, rvalue, lvalue,  xvalue, prvalue, decltype, is_reference)
virya::ioq& operator<<(virya::ioq& o, const char* s){o.printf("%s", s); return o;}
//virya::ioq& endx(virya::ioq& o){ o.printf("%s\n"); return o; }
virya::ioq ioq; CODE_FORMAT_Help __(CODE_FORMAT_, "++ %-35s");
using namespace std;

void f(int& x)  { ioq << "called by " << __FUNCSIG__ << "\n";}
void f(int&& x) { ioq << "called by " << __FUNCSIG__ << "\n";}

void g(int   x) { ioq << "called by " << __FUNCSIG__ << "\n"; }
//void g(int&  x) { cout << "called by " << __FUNCSIG__ << endl; }
void g(int&& x) { ioq << "called by " << __FUNCSIG__ <<  "\n"; }

void h(int   x) { ioq << "called by " << __FUNCSIG__ << "\n"; }
void h(int&  x) { ioq << "called by " << __FUNCSIG__ << "\n"; }
//void h(int&& x) { cout << "called by " << __FUNCSIG__ << endl; }

void l(int   x) { ioq << "called by " << __FUNCSIG__ << "\n"; }
void m(int&  x) { ioq << "called by " << __FUNCSIG__ << "\n"; }
void n(int&& x) { ioq << "called by " << __FUNCSIG__ << "\n"; }

#define TYPECONST(T)  (is_const<decltype(T)>::value ? 'C' : (is_volatile<decltype(T)>::value ? 'V' : '?')) 
#define TYPEREFERENCE(T)  (is_rvalue_reference<decltype(T)>::value ? 'R' : (is_lvalue_reference<decltype(T)>::value ? 'L' : '-')) 
#define TRACE_TYPENAME(T)  {printf("[%-3s] Typename:%s[%c][%c] Address:%p\n", #T, typeid(T).name(),TYPEREFERENCE(T), TYPECONST(T), &T);} // 
#define TRACE_TYPENAME_(T) {printf(       "Typename:%s[%c][%c] Address:%p\n",     typeid(T).name(),TYPEREFERENCE(T), TYPECONST(T), &T);} //^^ without var's name 

int main(int argc, char* argv[]){
	HEAD1("reference declarator")
	int x = 0;               TRACE_E() // `x` is an object of lvalue of type `int`
	int& xl = x;             TRACE_E() // `xl` is an lvalue reference of type `int&`
	/*int&& xr1 = x;*/       TRACE_Ew() // compiler error -- `x` is an lvalue
	int&& xr2 = 0;           TRACE_E() // `xr2` is a rvalue reference of universal object `0`
	auto    y1 = x;          TRACE_E() // `yl1` is int
	auto &  y2 = x;          TRACE_E() // `yl2` is int&
	auto && yr1 = x;         TRACE_E() // ! allowed, different from `int &&`
	auto && yr2 = 0;         TRACE_E() // ! &yr2 != &xr2
	TRACE_TYPENAME(x);
	TRACE_TYPENAME(xl);
	TRACE_TYPENAME(xr2);
	TRACE_TYPENAME(y1);
	TRACE_TYPENAME(y2);
	TRACE_TYPENAME(yr1);
	TRACE_TYPENAME(yr2);

	HEAD1(reference declarator in function defintion)
	{
		HEAD3s(in normal function defintion)
		EXPLAIN(l-reference <= void f(int&))	
		EXPLAIN(r-reference <= void f(int&&))	
		HEAD3s(in template function defintion)
		EXPLAIN(l-reference <= tempalte<class T> void f(T&))	
		EXPLAIN(r-reference <= tempalte<class T> void f(int&&))	
		EXPLAIN(forwarding- <= tempalte<class T> void f(T&&))
		EXPLAIN(const r-    <= tempalte<class T> void f(const T&&))
	}
	HEAD1(reference declarator with auto)
	{
		EXPLAIN(forwarding- <= auto && x = f())
	}

	HEAD1("use `r&l`value reference as parameters(pass them to functions)")
    {
	HEAD3("pass varialbe to functions: void f(int&), void f(int&&)")
	f(x);                           TRACE_QUE_()
	f(xl);                          TRACE_QUE_()
	f(3);              				TRACE_QUE_()
	f(std::move(x));                TRACE_QUE_()
	f(xr2);                         TRACE_QUE_()
	f(std::move(xr2));              TRACE_QUE_()
	f(yr1);              			TRACE_QUE_()
	f(yr2);                         TRACE_QUE_()
	NOTICE(Due to call FUNC(int &) NO MATTER whether the variable is r- or l-reference)
	}

	{
	HEAD3("pass to functions : void g(int), void g(int&&)")
	g(x);                              TRACE_QUE_()             
	g(xl);                             TRACE_QUE_()              
	/*g(3);*/                          TRACE_Ew() // ambiguous call to overloaded function
	/*g(std::move(x));*/               TRACE_Ew() // ambiguous call to overloaded function  
	g(xr2);                            TRACE_QUE_()             
	/*g(std::move(xr2));*/             TRACE_Ew() // ambiguous call to overloaded function  
	}

	{
	HEAD3("pass to functions : void h(int), void h(int&)")
	CODE_ERRc(h(x);)                   TRACE_QUE()                        
	CODE_ERRc(h(xl);)                  TRACE_QUE() 
	h(3);                              TRACE_QUE_()
	h(std::move(x));                   TRACE_QUE_()    
	CODE_ERRc(h(xr2);)                 TRACE_QUE()           
	h(std::move(xr2));                 TRACE_QUE_() 
	}

	{
	HEAD3("pass to one function : void l(int)")
	l(x);                              TRACE_QUE_()              
	l(xl);                             TRACE_QUE_()             
	l(3);                              TRACE_QUE_()
	l(std::move(x));                   TRACE_QUE_()    
	l(xr2);                            TRACE_QUE_()            
	l(std::move(xr2));                 TRACE_QUE_() 
	}

	{
	HEAD3("pass to one function : void m(int&)")
	m(x);                              TRACE_QUE_()              
	m(xl);                             TRACE_QUE_()             
	CODE_ERRc(m(3);)                   TRACE_QUE()
	CODE_ERRc(m(std::move(x));)        TRACE_QUE()
	m(xr2);                            TRACE_QUE_()            
	CODE_ERRc(m(std::move(xr2));)      TRACE_QUE()
	}

	{
	HEAD3("pass to one function : void n(int&&)")
	CODE_ERRc(n(x);)                   TRACE_QUE() 
	CODE_ERRc(n(xl);)                  TRACE_QUE()             
	n(3);                              TRACE_QUE_()	
	n(std::move(x));                   TRACE_QUE_()     
	CODE_ERRc(n(xr2);)                 TRACE_QUE()           
	n(std::move(xr2));                 TRACE_QUE_()   
	}

	HORIZONTAL3()
	EXPLAINs("- `rvalue reference` is lvalue as well as `lvalue reference` for function")
	EXPLAINs("- complete functions");
	EXPLAINs("    1. If {{void F(int)                }} is  there, all types of variables are processed.");
	EXPLAINs("    2. If {{void F(int&),void F(int&&) }} are there, all types of variables are processed.");
	EXPLAINs("    3. Otherwise, conflicts may occur!");

	HORIZONTAL_LINE();
	SEEALSO((foward))	
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//

BEGIN_UNIT_(ref_qualified, reference-qualified member function)

struct Bar {
  // ...
};

struct Foo {
  Bar getBar() & { return bar; }
  Bar getBar() const& { return bar; }
  Bar getBar() && { return std::move(bar); }
private:
  Bar bar;
};

int main(int argc, char* argv[]){HORIZONTAL_FRAME(TRACE_SRC(-12,-2)); TRACE_SRC(1,10); HORIZONTAL1();
	Foo foo{};
	Bar bar = foo.getBar();   // calls `Bar getBar() &`

	const Foo foo2{};
	Bar bar2 = foo2.getBar(); // calls `Bar Foo::getBar() const&`

	Foo{}.getBar();           // calls `Bar Foo::getBar() &&`
	std::move(foo).getBar();  // calls `Bar Foo::getBar() &&`

	std::move(foo2).getBar(); // calls `Bar Foo::getBar() const&`
	return 0;
}

END_UNIT// ref_qualified


BEGIN_UNIT_(rtnent_category, bounce parameter, decltype, template variable) using namespace std;
/**
FUNCTIONS
    1. decltype(auto) f(int i){ return  i;}
    2. decltype(auto) f(int i){ return (i);}
NOTICE
    - safety
	  - 
        function 1 will return int;
        function 2 will return the parameter i;
      - 
        nerver return its parameter which is normal(non-object or lvalue-reference)
    - decltype(expression)
      - it will not execute expression
CATEGORY
    - return value or value of expression
      - lvalue
      - xvalue
      - prvalue
    - variable
      - lrefvar  - variable referenced to 
		            1. left value(for all toolchains)
                    2. right value(only for msvc)
         - clrefvar - const variable referenced to left-right value 
      - rrefvar  - variable referenced to right value
      - purevar  - pure variable
    - parameter represents
      - coloned e   - pure parameter
      - original e  - defined by &
      - temporary e - defined by &&
REFERENCE
    https://www.scs.stanford.edu/~dm/blog/decltype.html
*/
template<typename T> constexpr const char *category = "prvalue";
template<typename T> constexpr const char *category<T&> = "lvalue";
template<typename T> constexpr const char *category<T&&> = "xvalue";
#define SHOWrc(E) std::cout << #E << ": " << category<decltype((E))> << '[' << TYPEREFERENCE(E) << ']' << std::endl // return value's category
#define SHOWec(E) SHOWrc(E) // expression's category
template<typename T> constexpr const char *vcategory      = "purevar";
template<typename T> constexpr const char *vcategory<T&>  = "lrefvar";
template<typename T> constexpr const char *vcategory<T&&> = "rrefvar";
#define SHOWvc(E) std::cout << #E << ": " << vcategory<decltype((E))> << '[' << TYPEREFERENCE(E) << ']' << std::endl // variable category

decltype(auto) fn_A(int i) { return i; }
decltype(auto) fn_B(int i) { return (i); }
decltype(auto) fn_C(int i) { return (i+1); }
decltype(auto) fn_D(int i) { return i++; }
decltype(auto) fn_E(int i) { return ++i; }
decltype(auto) fn_F(int i) { return (i >= 0 ? i : 0); }
decltype(auto) fn_G(int i, int j) { return i >= j ? i : j; }
struct S { 
	int i = 0; 
	//S(){printf("S::S()\n");}
	~S(){i = -1; printf("S::~S()\n");}
};

#if __cplusplus > 201400
#define SUPPORT_XVALUE
#endif
#ifdef SUPPORT_XVALUE
decltype(auto) fn_H() { return (S{}); }
decltype(auto) fn_I() { return (S{}.i); }
#endif
decltype(auto) bounce(S s) { printf("bounce(param:%p content:%d)\n", &s, s.i); return (s); }
S fetchs() { return S{}; }

int main(int argc, char* argv[]){TRY_MANUAL()
	HEAD1("function return category")
	SHOWrc(fn_A(0));
	SHOWrc(fn_B(0));
	SHOWrc(fn_C(0));
	SHOWrc(fn_D(0));
	SHOWrc(fn_E(0));
	SHOWrc(fn_F(0));
	SHOWrc(fn_G(0,1));
#ifdef SUPPORT_XVALUE
	SHOWrc(fn_H());
	SHOWrc(fn_I());
#endif
	HEAD1("test the function bounce - which return its pure INPUT parameter");
	{
		S s1; s1.i = 100;
		printf("(input:%p content:%d)\n", &s1, s1.i);
		SHOWrc(bounce(s1));
		S& r1 = bounce(s1);
		printf("(rtn:%p content:%d)\n", &r1, r1.i);
		NOTICEf("this function is not safe!");
		NOTICEf_("- nerver return the function's input normal parameter!");
	}
	HEAD1("testing expressions related to `S{}.i`")
	{
		HEAD3s("value category of `S{}.i`")
		{
			SHOWrc(S{});
			SHOWrc((S{}));
			SHOWrc(S{}.i);
			SHOWrc((S{}.i));
		}
		HEAD3s("S&& s= S{}")
		{
			S&& s= S{};
			printf("leaving\n");	
		}
		HEAD3s("int i= S{}.i")
		{
			int i= S{}.i;
			printf("leaving\n");	
		}
#ifdef SUPPORT_XVALUE
		HEAD3s("int&& i= S{}.i")
		{
			int&& i= S{}.i;
			printf("leaving\n");	
		}
#endif
	}
	HEAD1("testing expressions related to `S{returned by fetchs()}.i`")
	{
		HEAD3s("S&& s= fetchs()")
		{
			S&& s= fetchs();
			printf("leaving\n");	
		}
		HEAD3s("int i= fetchs().i")
		{
			int i= fetchs().i;
			printf("leaving\n");	
		}
		HEAD3s("int&& i= fetchs().i")
		{
			int&& i= fetchs().i;
			printf("leaving\n");	
		}
	}
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//rtnent_category

BEGIN_UNIT_(rtnent_relay, rvalue reference, std_ref) using namespace std;
/**
SUBCOMMAND
   1 - rreference relay 
   2 - const lreference relay 
   3 - container of reference relay 
EXPERIMENT
    - rreference relay
      - relay xe   returned by func(major)
      - relay lref returned by func
      - relay rref returned by func
      - relay wo   returned by func 
    - const lreference relay
NOTICE
    - rvalue reference can only relay prvalue returned by function
       - and  the value(entity) relayed is lvalue
    - const lvalue reference can only relay prvalue returned by function
	- container(such as vector) of reference, fails to relay all rref
	   - local variable rref                        
	   - return variable(prvalue)
VOCABULARY
    relay something - expand something's lifetime
*/
struct A {
	A()    { printf("A::A()\n");   }
	A(A&o) { printf("A::A(A&)\n"); }
	~A()   { printf("A::~A()\n");  }
};
A   f () { A a; return a; }
A&  g () { A a; return a; }
//A&& d1 () { A a = A(); return a; }
//A&& d2 () { A& a = A(); return a; }
//A&& d3()  { A&& a = A(); return a; }
A&& d4 () { return A(); }
template<class F>
void tour(F func){
	HORIZONTAL_LINE('/', 60)
	{
		EXPLAIN(\/\/\/\/ calling `func()`)
		func();
		EXPLAIN(\\\\\\\\ ending of `func()`)
	}
	HORIZONTAL_LINE('/', 60)
	{
		EXPLAIN(\/\/\/\/ calling `A&& x = func()`)
		A&& x = func();
		EXPLAIN(\\\\\\\\ ending of `A&& x = func()`)
	}
}
int rref_relay(){HORIZONTAL_FRAME(TRACE_SRC(-15,-1))
	#define HEADx(X) HEAD1(X); EXPLAIN_(**** FUNCTION => ); TRACE_SRC(-23,-23); 
    HEADx("relay xe");         tour(&f);   NOTICE(WORK)
	HEADx("relay lref");     /*tour(&g);*/ NOTICE(NOT support - 'initializing': cannot convert from A to A&&)
	HEADx("relay rref - 1"); /*tour(&d1)*/ NOTICE(Cannot convert from A(A a)  to A&&)
	HEADx("relay rref - 2"); /*tour(&d1)*/ NOTICE(Cannot convert from A(A&a)  to A&&)
	HEADx("relay rref - 3"); /*tour(&d1)*/ NOTICE(Cannot convert from A(A&&a) to A&&)
	HEADx("relay rref - 4");   tour(&d4);  NOTICE(NOT work)

	return 0;
	#undef HEADx
}

template<class F>
void ltour(F func){
	HORIZONTAL_LINE('/', 60)
	{
		EXPLAIN(\/\/\/\/ calling `const A& x = func()`)
		const A& x = func(); // for msvc, A&x also works; Notice: is_const fails
		EXPLAIN(\\\\\\\\ ending of `const A& x = func()`)
	}
}
int lref_relay(){HORIZONTAL_FRAME(TRACE_SRC(-9,-1))
	#define HEADx(X) HEAD1(X); EXPLAIN_(**** FUNCTION => ); TRACE_SRC(-44,-44); 
    HEADx("relay xe");         ltour(&f);   NOTICE(WORK)
	HEADx("relay lref");       ltour(&g);   NOTICE(NOT work)
	//HEADx("relay lref - 1"); /*ltour(&d1)*/ NOTICE(Cannot convert from A(A a)  to A&&)
	//HEADx("relay lref - 2"); /*ltour(&d1)*/ NOTICE(Cannot convert from A(A&a)  to A&&)
	//HEADx("relay lref - 3"); /*ltour(&d1)*/ NOTICE(Cannot convert from A(A&&a) to A&&)
	HEADx("relay lref - 4");   ltour(&d4);  NOTICE(NOT work)

	return 0;
	#undef HEADx
}

void vector_of_reference_(){
	HEAD3(function begin)
	vector<reference_wrapper<A>> vec;            TRACE_LINE();
		HEAD5s(block 1 begin - relay local var); TRACE_SRC(2,3);
		{
			A v;                    
			vec.push_back(ref(v));  
			HEAD5s(block 1 leaving)
		}
		HEAD5s(block 1 end)

		HEAD5s(block 2 begin - relay local var); TRACE_SRC(2,4);
		{
			A v;                    
			auto r = ref(v);
			vec.push_back(r);  
			HEAD5s(block 2 leaving)
		}
		HEAD5s(block 2 end)

		HEAD5s(block 3 begin - relay prvalue); TRACE_SRC(2,3);
		{
			A&& r = f();
			vec.push_back(r);  
			HEAD5s(block 3 leaving)
		}
		HEAD5s(block 3 end)
	HEAD3(function leaving)
};
void vector_of_reference(){
	HEAD1(function calling)
		vector_of_reference_();
	HEAD1(function calling...end)
	// CONCLUSION, cannot relay any object referenced(see NOTICE)
}


int main(int argc, char* argv[]){ TRY_MANUAL();
	int subcommand = 1;
	for(int i = 1; i < argc; i++){
		if(regex_match(argv[i], regex("\\d+"))){
			subcommand = atoi(argv[i]);
		}else{
			fprintf(stderr, "%s: unknown option -- '%s'\n", argv[0], argv[i]);
			return 1;
		}
	}
	switch(subcommand){
	case 1: rref_relay();          break;
	case 2: lref_relay();          break;
	case 3: vector_of_reference(); break;
	default: return 1;
	}
	MANUALb(NOTICE)
	return 0;
}
END_UNIT

BEGIN_UNIT_(rtnobj_auto_management, unique_ptr, shared_ptr, robj)
/**
PURPOSE
    Implement one mechanism: if the return object is not captured, the resource will be freed automatically!
SULUTION
	To implement a class like unique_ptr or shared_ptr is a good method.
REFERENCE
	https://stackoverflow.com/questions/6876751/differences-between-unique-ptr-and-shared-ptr
*/
int main(int argc, char* argv[]){ MANUALb();
	return 0;
}
END_UNIT

BEGIN_UNIT_(rvalue_fullfill_object, pass rvalue to a function which requires an object(pointer))
/**
NAME
    rvalue_fullfill_object - subtitute object-parameter with rvalue's address
TIPS
    OK    - msvc
    FAILS - clang/gcc
*/
int main(int argc, char* argv[]){ MANUALb();
	return 0;
}
END_UNIT//

BEGIN_UNIT_(bestow, forwarding reference, std::forward, auto) using namespace std;

/**
NAME
    pass arguments to function
SYNONYM
   fulfill
   afford
   confer
   bestow
*/

typedef const int CINT;
int  get_r(){return 1;}
int& get_l(){static int i = 1; return i;}
template<class T> void func1(T&& v){cout << "In func1(T&&v) "; TRACE_TYPENAME_(v);}
template<class T> void func2(T   v){cout << "In func1(T  v) "; TRACE_TYPENAME_(v);}
template<class T> void func3(T&& v){cout << "In func3(T&&v) --> "; func1(forward<T>(v)); }
template<class T> void func4(T   v){cout << "In func4(T  v) --> "; func1(forward<T>(v)); }

int main(int argc, char* argv[]){HEAD3(definitions); TRACE_SRC(-5,-2);
	{   
		HEAD(param of `forwarding reference`);TRACE_NE_();
		int   i=0; func1(i);               TRACE_NE_();
		int&& j=1; func1(j);               TRACE_NE_();
		int&  k=i; func1(k);               TRACE_NE_();
		/*      */ func1(forward<int>(k)); TRACE_NE_();
		/*      */ func1(100);             TRACE_NE_();
		CINT  l=0; func1(l);               TRACE_NE_();
		/*      */ func1(forward<CINT>(l));TRACE_NE_();
		/*      */ func1(get_r());         TRACE_NE_();
		/*      */ func1(get_l());         TRACE_NON();
	}
	{   
		HEAD(param of `normal`);           TRACE_NE_();
		int   i=0; func2(i);               TRACE_NE_();
		int&& j=1; func2(j);               TRACE_NE_();
		int&  k=i; func2(k);               TRACE_NE_();
		/*      */ func2(forward<int>(k)); TRACE_NE_();
		/*      */ func2(100);             TRACE_NE_();
		CINT  l=0; func2(l);               TRACE_NE_();
		/*      */ func2(forward<CINT>(l));TRACE_NE_();
		/*      */ func2(get_r());         TRACE_NE_();
		/*      */ func2(get_l());         TRACE_NON();
	}
	{   
		HEAD(forward twice);               TRACE_NE_();
		int   i=0; func3(i);               TRACE_NE_();
		int&& j=1; func3(j);               TRACE_NE_();
		int&  k=i; func3(k);               TRACE_NE_();
		/*      */ func3(forward<int>(k)); TRACE_NE_();
		/*      */ func3(100);             TRACE_NE_();
		CINT  l=0; func3(l);               TRACE_NE_();
		/*      */ func3(forward<CINT>(l));TRACE_NE_();
		/*      */ func3(get_r());         TRACE_NE_();
		/*      */ func3(get_l());         TRACE_NON();
	}
	{   
		HEAD(call twice);                  TRACE_NE_();
		int   i=0; func4(i);               TRACE_NE_();
		int&& j=1; func4(j);               TRACE_NE_();
		int&  k=i; func4(k);               TRACE_NE_();
		/*      */ func4(forward<int>(k)); TRACE_NE_();
		/*      */ func4(100);             TRACE_NE_();
		CINT  l=0; func4(l);               TRACE_NE_();
		/*      */ func4(forward<CINT>(l));TRACE_NE_();
		/*      */ func4(get_r());         TRACE_NE_();
		/*      */ func4(get_l());         TRACE_NON();
	}
	return HORIZONTAL1();
}
END_UNIT // bestow

BEGIN_UNIT_(call_by_value) using namespace std;
/**
The call by value method of passing arguments to a function copies the
 actual value of an argument into the formal parameter of the function.
 In this case, changes made to the parameter inside the function have 
 no effect on the argument.
By default, C++ uses call by value to pass arguments. In general, this 
means that code within a function cannot alter the arguments used to call the function.
*/

// function definition to swap the values.
void swap(int x, int y) {
   int temp;

   temp = x; /* save the value of x */
   x = y;    /* put y into x */
   y = temp; /* put x into y */
  
   return;
}
void test () {
   // local variable declaration:
   int a = 100;
   int b = 200;
 
   cout << "Before swap, value of a :" << a << endl;
   cout << "Before swap, value of b :" << b << endl;
 
   // calling a function to swap the values.
   swap(a, b);
 
   cout << "After swap, value of a :" << a << endl;
   cout << "After swap, value of b :" << b << endl;
}

int main(int argc, char* argv[]){TRY_MANUAL(); HEAD1(defintions); TRACE_SRC(-25,-2);HORIZONTAL1();
	test();
	return 0;
}

END_UNIT// call_by_value


BEGIN_UNIT_(std_ref, bind ref, bind cref)
/**
NOTE
	Function templates ref and cref are helper functions that generate an object of type std::reference_wrapper,
	using template argument deduction to determine the template argument of the result.
*/
void f(int& n1, int& n2, const int& n3)
{
    std::cout << "    In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
    // ++n3; // compile error
}
 
int main(int argc, char* argv[]) {HEAD1("Testing std::ref/std::cref"); HEAD2(Defintion); TRACE_SRC(-8,-2);HEAD2("")
    int n1 = 100, n2 = 200, n3 = 300;                                               TRACE_E();
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));  TRACE_E();

    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();                                                                      TRACE_E();              
    std::cout << " After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';

	HORIZONTAL5();
	NOTICEf("std::bind will bind variable as non-reference by default");
	return HORIZONTAL_LINE();
}
END_UNIT

BEGIN_UNIT_(bind)
KEYWORDS(bind, smartptr)
void f(int n1, int n2, int n3, const int& n4, int n5)
{
	std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1)
{
	return -n1;
}

struct Foo {
	void print_sum(int n1, int n2)
	{
		std::cout << n1 + n2 << '\n';
	}
	int data = 10;
};

int main(int argc, char* argv[])
{
	HEAD("Testing std::bind -- basic");

	using namespace std::placeholders;  // for _1, _2, _3...

	ANNOTATE( demonstrates argument reordering and pass-by-reference)
	TRACE_CODE(int n = 7;)
	ANNOTATE(_1 and _2 are from std::placeholders, and represent future)
	ANNOTATE(arguments that will be passed to f1)
	TRACE_CODE(auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);)
	TRACE_CODE(n = 10;)
	TRACE_CODE(f1(1, 2, 1001);)// 1 is bound by _1, 2 is bound by _2, 1001 is unused
					// makes a call to f(2, 1, 42, n, 7)

	HEAD("Testing std::bind -- subexpressions");
	// nested bind subexpressions share the placeholders
	TRACE_CODE(auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);)
	TRACE_CODE(f2(10, 11, 12);) // makes a call to f(12, g(12), 12, 4, 5);

	HEAD("Testing std::bind -- RNG");
	// common use case: binding a RNG with a distribution
	TRACE_CODE(std::default_random_engine e;)
	TRACE_CODE(std::uniform_int_distribution<> d(0, 10);)
	TRACE_CODE(auto rnd = std::bind(d, e);) // a copy of e is stored in rnd
	for(int n = 0; n < 10; ++n)
		std::cout << rnd() << ' ';
	std::cout << '\n';

	HEAD("Testing std::bind -- a pointer to function member");
	Foo foo;
	TRACE_CODE(auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);)
	TRACE_CODE(f3(5);)

	HEAD("Testing std::bind -- a pointer to data member");
	TRACE_CODE(auto f4 = std::bind(&Foo::data, _1);)
	TRACE_CODE(std::cout << f4(foo) << '\n';)

	HEAD("Testing std::bind -- a smpart pointer");
	TRACE_CODE(std::cout << f4(std::make_shared<Foo>(foo)) << std::endl);
	TRACE_CODE(std::cout << f4(std::make_unique<Foo>(foo)) << std::endl);

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT

BEGIN_UNIT_(bind_tfunc)
KEYWORDS(bind, variadic template, function as template parameter)

template<class...T> 
void add(T&...t){
	std::cout << "triggered" << __FUNCSIG__ << '\n';
	auto foo=[](auto& v)->int{v++; return 0;};
	std::vector<int>  dummy = { foo(t)...};
}

template <class F, class ... Args>
auto p(F f, Args&... args){
	std::cout<< "triggered" << __FUNCSIG__<< '\n';
	return f(args...);
}

template <class RTN, class ... Args, typename F>// = T*(Args) <=== msvc support
auto q( F f, Args&... args){
	std::cout << "triggered" << __FUNCSIG__ << '\n';
	return f(args...);
}

template <class RTN, class ... Args>
auto r(RTN(*f)(Args&...), Args&... args){
	std::cout << "triggered" << __FUNCSIG__ << '\n';
	return f(args...);
}

template <class F, class ... Args>
auto u(F f, Args&... args){
	std::cout << "triggered" << __FUNCSIG__ << '\n';
	return f(args...);
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	int     a1 = 100;
	double  a2 = 200;
	int64_t a3 = 300;
	auto print_vars =[&](const char* info){printf("%s : (a1 a2 a3) = (%d %f %lld)\n", info, a1, a2, a3);};

	print_vars("  Original");
	HORIZONTAL_LINEs()
	TRACE_CODE(
	auto f1 = std::bind(
		&add<int, double, int64_t>,
		std::ref(a1), std::ref(a2), std::ref(a3));)
	f1();
	print_vars("After f1()");

	HORIZONTAL_LINEs()
	TRACE_CODE(
	auto f2 = std::bind(
		&p<void(int&,double&,int64_t&),	int, double, int64_t>, 
		&add<int,double,int64_t>,
		std::ref(a1), std::ref(a2), std::ref(a3));)
	f2();
	print_vars("After f2()");

	HORIZONTAL_LINEs()
	TRACE_CODE(
	q<void,int, double, int64_t>(&add<int,double,int64_t>, a1, a2, a3);
	//q(&add<int, double, int64_t>, a1, a2, a3);
	)
	print_vars(" After q()");

	HORIZONTAL_LINEs()
	TRACE_CODE(
	//r<void,int, double, int64_t>(&add<int,double,int64_t>, a1, a2, a3);
	r(&add<int, double, int64_t>, a1, a2, a3);
	)
	print_vars(" After r()");

	HORIZONTAL_LINEs()
	TRACE_CODE(
	auto f3 = std::bind(
		&r<void,int, double, int64_t>, 
		&add<int,double,int64_t>,
		std::ref(a1), std::ref(a2), std::ref(a3));
	)
	f3();
	print_vars("After f3()");

	HORIZONTAL_LINEs()
	TRACE_CODE(
	u(&add<int, double, int64_t>, a1, a2, a3);
	)
	print_vars(" After u()");

	HORIZONTAL_LINEs()
	TRACE_CODE(
	auto f4 = std::bind(
		&u<void(int&,double&,int64_t&),	int, double, int64_t>, 
		&add<int,double,int64_t>,
		std::ref(a1), std::ref(a2), std::ref(a3));)
	f4();
	print_vars("After f4()");

	HORIZONTAL_LINE();
	EXPLAIN (r is the simplest!);
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT
