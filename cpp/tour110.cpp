#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <future>
#include <mutex>

#include "vtestcommon.h"
#define TOUR_GROUP tour110_


#define DEF_FUNC(X) X(int argc, char* argv[])
static std::string __code_line;
#define _(...) __VA_ARGS__; __code_line  = #__VA_ARGS__;
#define COMMENT(...)      { printf("%-60s // %s\n",__code_line.c_str(), #__VA_ARGS__);}



BEGIN_UNIT_(cpp11_new_features)

class A{};

int  main(int argc, char* argv[]){
	HEAD1(auto);
		_(auto i = 42;)       COMMENT( i is integer)
		_(auto l = 42LL;)     COMMENT( l is int64)
		_(auto p = new A;) COMMENT( p is a A*)
	
	HEAD1(nullptr);
		_(int *p1 = NULL;)    COMMENT( p1 is good )
		_(int *p2 = nullptr;) COMMENT( p2 is good )

	puts("\n"
		 "range-based for loops => for(auto k : map){}");
	puts("overide final\n");
	puts("Strongly-typed enums:\n");
	_(enum class Options {One,Two, Three};) COMMENT(enum class)
	_(Options o = Options::Two;)            COMMENT(Two is in the enum)
	
	puts("\n\n"
		 "unique_ptr");
	puts("shared_ptr");
	puts("weak_ptr");
	
	puts("\n\n"
		 "lambda");
	puts("non-member begin end");
	std::vector<int> v = {1,2,3};
	_(std::for_each(std::begin(v), std::end(v), [](int n){std::cout<< n << std::endl;} );) COMMENT(lambda, non-member begin and end used ) 
	_(std::for_each(   v.begin(),      v.end(), [](int n){std::cout<< n << std::endl;} );) COMMENT(lambda is used) 
	_(auto pos = std::find_if(v.begin(),v.end(), [](int n){return n%2==0;} ); 
	  if(pos!=v.end()){std::cout<<"Find result:"<< *pos << std::endl;})             COMMENT(lambda is used) 
	
    _(std::function<int(int)> lfib = [&lfib](int n) {return n < 2 ? 1 : lfib(n-1) + lfib(n-2);};)          COMMENT(recursive lymbda)
	//_(std::cout << " 5:" << [lfib](5) << "\n";)  COMMENT(General lambda function is used)
	//_(std::for_each(std::begin(v), std::end(v), [](int n){auto r = lfib(n); std::cout << n << ":" << r << "\n";} );) COMMENT(lymba) 
	
	
	puts("\n\n");
	puts("static assert and type traits");
	puts("	Used in template class, static_assert");
	puts("						   &std::is_integral");
	
	puts("\n\n");
	puts("Move Constructor");

	HEAD1(attribute - introduces implementation-defined attributes for types, objects, code, etc); TRACE_SRC(1,4);
	//   [[attr]] [[attr1, attr2, attr3(args)]] [[namespace::attr(args)]] alignas-specifier
	//Formally, the syntax is
	//  [[ attribute-list ]]		                            (since C++11)
	//  [[ using attribute-namespace : attribute-list ]]		(since C++17)
	HEAD1(constexpr)
	HEAD1(delegating constructor)
	HEAD1(user-defined literals)
	HEAD1(explicit virtual override)
	HEAD1(final specifier)
	HEAD1(default function)
	HEAD1(deleted function)
	HEAD1(range-based for loops)
	HEAD1(special member functions for move semantics)
	HEAD1(converting constructors)
	HEAD1(explicit conversion functions)
	HEAD1(inline namespaces)
	HEAD1(no-static data memeber initializer)
	HEAD1(right angle bracket enhancement)
	HEAD1(ref-qualified member function)
	HEAD1(trailing return type)
	HEAD1(noexcept specifier)
	HEAD1(char32_t and char16_t)
	HEAD1(Raw String Literal);TRACE_SRC(1,6)
	const char* cs1 = R"(Hello\)";  
	const char* cs2 = R"f(Hello\)f"; 
	const char* cs3 = R""(Hello\)"";
	const char* cs4 = R""(Hello\n world!)"";
	const char* cs5 = R"(Hello\
world)";
	HEAD1(std::move);
	HEAD1(std::forward);
	HEAD1(std::thread);
	HEAD1(std::to_string);
	HEAD1(library type traits);
	HEAD1(smart pointers);
	HEAD1(std::chrono);
	HEAD1(tuple);
	HEAD1(std::tie);
	HEAD1(std::array);
	HEAD1(unordered containers);
	HEAD1(std::p);
	HEAD1(std::ref);
	HEAD1(memory model: such as atomic and threads);
	HEAD1(std::async);
	HEAD1(std::begin/end);
	HORIZONTAL_LINE();

	return 0;
}

END_UNIT//

BEGIN_UNIT_(static_assert)
template <typename T, size_t SIZE> 
class X{
	static_assert(SIZE<3,"Size is too small");
	T _points[SIZE];
};
template <typename T1, typename T2>
auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
{
   return t1 + t2;
}
int main(int argc, char* arg[]){
	X<int, 2> x1;
	return 0;
}
END_UNIT// static_assert


BEGIN_UNIT_(lambda)

typedef int (*S)(int);

template<class F>
void g(F f){
	if(f)
		f(1);
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE()

	int x = 0;
	TRACE_CODE( int (*func1)(int) = [](int m){std::cout << __FUNCTION__ << " " << m <<"\n"; return 0;};)
	ANNOTATE(  int (*func2)(int) = [&x](int m){std::cout << __FUNCTION__ << " " << m+x; return 0; };)
	//TRACE_CODE(std::function<int()> func3 = [&x](int m){std::cout << __FUNCTION__ << " " << m+x <<"\n"; return 0; };)
	TRACE_CODE(std::function<int(int)> func3 = [](int m)  {std::cout << __FUNCTION__ << " " << 10 + m << "\n"; return 0; };)
	TRACE_CODE(std::function<int(int)> func4 = [&x](int m){std::cout << __FUNCTION__ << " " << m + x << "\n"; return 0; };)
	ANNOTATE((int(*)(int)nullptr) <= also workable)
	ANNOTATE((std::function<int(int)>)nullptr <= also workable)
	HORIZONTAL_LINE()
	for(;x<5;x++){
		printf("i=%d\n",x);
		g(func1);
		g(func3);
		g(func3);
		g((S)nullptr);
		g((int(*)(int))nullptr);
		g((std::function<int(int)>)nullptr);
	}
	HORIZONTAL_LINE()
	return 0;
}

END_UNIT// lambda


BEGIN_UNIT_(underlying_type, enum underlying type) using namespace  std;
inline Whistle& operator << (const type_info& s, Whistle &w) { printf("%-18s", s.name());  return w;}
inline Whistle& operator << (int n,              Whistle &w) { std::cout << n;  return w; }
inline Whistle& operator << (Whistle &w, const char*s)       { std::cout << s;  return w; }
inline Whistle& operator << (Whistle &w, size_t s)           { std::cout << s;  return w; }
#define ECHO_() Whistle::INSTANCE(__FILE__, __LINE__, "<<", "++ %s => ")

enum e1 {};
enum class e2 {};
enum class e3: unsigned {};
enum class e4: int {};
enum class e5: unsigned long long {};
enum class e6: std::int64_t {};
 
int main(int argc, char* argv[]) {HEAD1("Defintions"); TRACE_SRC(-7,-2)
  HEAD1("underlying type of enum")
  /*
  constexpr bool e1_t = std::is_same_v< std::underlying_type_t<e1>, int >;
  constexpr bool e2_t = std::is_same_v< std::underlying_type_t<e2>, int >;
  constexpr bool e3_t = std::is_same_v< std::underlying_type_t<e3>, int >;
  constexpr bool e4_t = std::is_same_v< std::underlying_type_t<e4>, int >;
  constexpr bool e5_t = std::is_same_v< std::underlying_type_t<e4>, int >;
 
  std::cout
    << "underlying type for 'e1' is " << (e1_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e2' is " << (e2_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e3' is " << (e3_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e4' is " << (e4_t ? "int" : "non-int") << '\n'
    << "underlying type for 'e5' is " << (e5_t ? "int" : "non-int") << '\n'
    ;*/
  typeid(underlying_type_t<e1>) << ECHO_() << "sizeof:" << sizeof(e1) << "\n";
  typeid(underlying_type_t<e2>) << ECHO_() << "sizeof:" << sizeof(e2) << "\n";
  typeid(underlying_type_t<e3>) << ECHO_() << "sizeof:" << sizeof(e3) << "\n";
  typeid(underlying_type_t<e4>) << ECHO_() << "sizeof:" << sizeof(e4) << "\n";
  typeid(underlying_type_t<e5>) << ECHO_() << "sizeof:" << sizeof(e5) << "\n";
  typeid(underlying_type_t<e6>) << ECHO_() << "sizeof:" << sizeof(e6) << "\n";
  sizeof(std::int64_t)          << ECHO_()                            << "\n";
  sizeof(long long)             << ECHO_()                            << "\n";

  return HORIZONTAL_LINE();
}
#undef ECHO_
END_UNIT// underlying_type


BEGIN_UNIT_(constexpr)
/**
NAME
    constexpr - specified the value can appear in constant expressions
DEMOS
    rtnent_relay
    constexpr_if - c++17
*/
int main(int argc, char* argv[]){ MANUALb();
	return 0;
}
END_UNIT// constexpr

BEGIN_UNIT_(for_ranged) using namespace std;
/**
NAME
    for_ranged  - range-based for loop
    stmt_ranged - range-based for statement
*/


inline Whistle& operator >> (vector<int>& a, Whistle &w) { for (int& x : a) {cout << " " <<x;} return w;} 
inline Whistle& operator >> (Whistle &w, const char* s)  { std::cout << s;             return w; }
#define ECHO_() Whistle::INSTANCE(__FILE__, __LINE__, ">>", "++ %s => ") >> "\n";

int main(int argc, char* argv[]){ MANUALb();
	{
		vector<int> a {1, 2, 3, 4, 5};   TRACE_E();
		for (int& x : a) x *= 2      ;   TRACE_E();
		a                            >>  ECHO_();
	}

	HEAD1("Note the difference when using int as opposed to int&")
	{
		vector<int> a {1, 2, 3, 4, 5};   TRACE_E();
		for (int x : a) x *= 2       ;   TRACE_E();
		a                            >>  ECHO_();
	}
	return HORIZONTAL_LINE();
}
END_UNIT // for_ranged

BEGIN_UNIT_(inline_namespace) using namespace std;
/**
DEFINTION
    All members of an inline namespace are treated as if they were part of its 
    parent namespace, allowing specialization of functions and easing the process 
    of versioning. This is a transitive property, if A contains B, which in turn
    contains C and both B and C are inline namespaces, C's members can be used as if they were on A.
*/
inline Whistle& operator >> (int x, Whistle &w) { cout <<x; return w;} 
inline Whistle& operator >> (Whistle &w, const char* s)  { std::cout << s;             return w; }
#define ECHO_() Whistle::INSTANCE(__FILE__, __LINE__, ">>", "++ %s => ") >> "\n";

namespace Program {
namespace Version1 {
	int getVersion()      { return 1; }
	bool isFirstVersion() { return true; }
}
inline namespace Version2 {
	int getVersion()      { return 2; }
	bool isFirstVersion() { return false; }
}
}
int main(int argc, char* argv[]){ MANUALh();HEAD1("Defintion");TRACE_SRC(-10,-1);HORIZONTAL1();
	Program::getVersion()            >> ECHO_() // Uses getVersion() from Version2
    Program::Version1::getVersion()  >> ECHO_() // Uses getVersion() from Version1
    Program::isFirstVersion()        >> ECHO_() // Does not compile when Version2 is added
	return HORIZONTAL_LINE();
}
END_UNIT // inline_namespace

BEGIN_UNIT_(trailing_return)
/**
###########################################################################################
#### C++11 allows functions and lambdas an alternative syntax for specifying their return types.
int f() {
  return 123;
}
// vs.
auto f() -> int {
  return 123;
}
auto g = []() -> int {
  return 123;
};

###########################################################################################
#### This feature is especially useful when certain return types cannot be resolved:
// NOTE: This does not compile!
template <typename T, typename U>
decltype(a + b) add(T a, U b) {
    return a + b;
}
// Trailing return types allows this:
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

###########################################################################################
#### In C++14, decltype(auto) (C++14) can be used instead.
###########################################################################################
*/
int main(int argc, char* argv[]) {MANUAL();
	return 0;
}
END_UNIT // trailing_return

BEGIN_UNIT_(async, std::async) using namespace std;
/**
SELECTION
    1. basic
	2. dctor_wait
NOTICE
    - The implementation may extend the behavior of the first overload of std::async by enabling 
      additional (implementation-defined) bits in the default launch policy.
    - Examples of implementation-defined launch policies are the sync policy (execute
       immediately, within the async call) and the task policy (similar to async, but thread-locals are not cleared)
    - If the std::future obtained from std::async is not moved from or bound to a reference, 
        the destructor of the std::future will block at the end of the full expression until 
        the asynchronous operation completes, essentially making code such as the following synchronous:
*/
 
std::mutex m;
struct X {
    void foo(int i, const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << "foo==" << str << ' ' << i << '\n';
    }
    void bar(const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << "bar==" << str << '\n';
    }
    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << "op()==" << i << '\n';
        std::cout << "op<===" <<10+ i << '\n';
        return i + 10;
    }
};

#if 0
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);
 
    RandomIt mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
void parallel(){
	std::vector<int> v(10000, 1);
	std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
}
#endif
 
void basic() {
 
    X x;
    // Calls (&x)->foo(42, "Hello") with default policy:
    // may print "Hello 42" concurrently or defer execution
    auto a1 = std::async(&X::foo, &x, 42, "Hello");                      TRACE_E(); // concurrent or defer
    // Calls x.bar("world!") with deferred policy
    // prints "world!" when a2.get() or a2.wait() is called
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");   TRACE_E(); // defer
    // Calls X()(43); with async policy
    // prints "43" concurrently
    auto a3 = std::async(std::launch::async, X(), 43);                   TRACE_E(); // concurrent
    a2.wait();                     TRACE_E(); // prints "world!"
    std::cout << a3.get() << '\n'; TRACE_E();// prints "53"
} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here

void f(){
	HEAD5s(f begin...);
	this_thread::sleep_for(chrono::milliseconds(100)); 
	HEAD5s(f end);
}
void g(){
	HEAD5s(g begin...);
	this_thread::sleep_for(chrono::milliseconds(100));
	HEAD5s(g end);
}
void dctor_wait(){HORIZONTAL_FRAME(TRACE_SRC(-10,-1));  TRACE_NXT();
	std::async(std::launch::async, []{ f(); }); TRACE_NXT();// temporary's dtor waits for f()
	std::async(std::launch::async, []{ g(); }); TRACE_NXT();// does not start until f() completes
	auto x= std::async(std::launch::async, []{ f(); }); TRACE_NXT();// holder will not wait
	auto y= std::async(std::launch::async, []{ g(); }); TRACE_NXT();// holder will not wait
	x.wait();                                           TRACE_NXT();
	y.wait();
}

int main(int argc, char* argv[]){
	int subcommand = 1;
	for(int i = 1; i < argc; i++){
		if(regex_match(argv[i], regex("\\d+"))){
			subcommand = atoi(argv[i]);
		}else{
			fprintf(stderr, "%s: unknown option -- '%s'\n", argv[0], argv[i]); return 1;
		}
	}
	switch(subcommand){
	case 1: basic();               break;
	case 2: dctor_wait();          break;
	default: return 1;
	}
	MANUALb(NOTICE)
	return 0;
}
END_UNIT // async

////////////////////////////////////////////////////////////////////////////////////////////////////////
// compatible with msvc14(vs2015) 
//       https://learn.microsoft.com/en-us/previous-versions/hh567368(v=vs.140)
//       https://devblogs.microsoft.com/cppblog/c111417-features-in-vs-2015-rtm/
BEGIN_UNIT_(binary_literal)
int main(int argc, char* argv[]){
	HEAD("msvc14 also support binary literal"); TRACE_SRC(1, 2);
	int a = 0b11111;
	int b = 0b1111'1111;
	return HORIZONTAL_LINE();
}
END_UNIT // binary_literal

BEGIN_UNIT_(generic_lambda)
int main(int argc, char* argv[]){
	HEAD("msvc14 also support generic lambda"); TRACE_SRC(1,3)
	auto identity = [](auto x) { return x; };
	int three = identity(3); // == 3
	std::string foo = identity("foo"); // == "foo"
	return HORIZONTAL_LINE();
}
END_UNIT // generic_lambda

BEGIN_UNIT_(init_capture, lambda capture initializer)
Whistle& operator>>(int a, Whistle& o){std::cout << a; return o;}

int factory(int i ) {return i * 10; }
auto f = [x=factory(2)] { return x; }; // returns 20
auto generator = [x= 0]() mutable {
	return x++;
}; 
int main(int argc, char* argv[]){HEAD(msvc14 also support lambda capture initializer); TRACE_SRC(-5,-1);HORIZONTAL3();
	auto a = generator(); /* == 0*/     TRACE_Ev(a)
	auto b = generator(); /* == 1*/     TRACE_Ev(b)
	auto c = generator(); /* == 2*/     TRACE_Ev(c)
	auto d = f();         /* == 20*/    TRACE_Ev(d)
	auto e = f();         /* == 20*/    TRACE_Ev(e)
	f()                   /* == 20*/ >> ECHO();
	return 0;
}
END_UNIT //init_capture

// compatible with msvc14(vs2015) - end
////////////////////////////////////////////////////////////////////////////////////////////////////////
