#include <typeinfo> // for typeid
#include <typeindex>
#include <assert.h>
#include <unordered_map>
#include <memory>

#include "vtestcommon.h"
#define TOUR_GROUP tour9_

BEGIN_UNIT_(lengthof_array)
KEYWORDS(sizeof, array length)
typedef char TypChrArr[11];
typedef int  TypIntArr[5];
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	NOTICE("Please notice difference between as parameter and as normal!")
	HEAD("Basic"); TRACE_SRC(1,3)
	std::cout <<
		"char[11]  => sizeof: " << sizeof(char[11]) << " lengthof: " << sizeof(char[11])/sizeof(char) << "\n"
		"int[5]    => sizeof: " << sizeof(int[5])   << " lengthof: " << sizeof(int[5])/sizeof(int)   << "\n"
	;

	HEAD("Using indenfier"); TRACE_SRC(1, 3)
	std::cout <<
		"char[11]  => sizeof: " << sizeof(TypChrArr) << " lengthof: " << sizeof(TypChrArr) / sizeof(char) << "\n"
		"int[5]    => sizeof: " << sizeof(TypIntArr) << " lengthof: " << sizeof(TypIntArr) / sizeof(int) << "\n"
		;

	HEAD("Using indenfier"); TRACE_SRC(1, 5);
	TypChrArr v1;
	TypIntArr v2;
	std::cout <<
		"char[11]  => sizeof: " << sizeof(v1) << " lengthof: " << sizeof(v1) / sizeof(v1[0]) << "\n"
		"int[5]    => sizeof: " << sizeof(v2) << " lengthof: " << sizeof(v2) / sizeof(v2[0]) << "\n"
		;

	HEAD("Parameter as TypXXXArr"); TRACE_SRC(1, 5)
	auto func1 = [](TypChrArr v1, TypIntArr v2){
	std::cout <<
		"char[11]  => sizeof: " << sizeof(v1) << " lengthof: " << sizeof(v1) / sizeof(v1[0]) << "\n"
		"int[5]    => sizeof: " << sizeof(v2) << " lengthof: " << sizeof(v2) / sizeof(v2[0]) << "\n"
		;
	};
	func1(v1, v2);

	HEAD("Parameter as TypXXXArr&"); TRACE_SRC(1, 5)
	auto func2 = [](TypChrArr&v1, TypIntArr& v2){
	std::cout <<
		"char[11]  => sizeof: " << sizeof(v1) << " lengthof: " << sizeof(v1) / sizeof(v1[0]) << "\n"
		"int[5]    => sizeof: " << sizeof(v2) << " lengthof: " << sizeof(v2) / sizeof(v2[0]) << "\n"
		;
	};
	func2(v1, v2);
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT


BEGIN_UNIT_(alignment, Test alignment and sizeof)
KEYWORDS(alignment, sizeof, alignof)

struct Foo {
    int   i;
    float f;
    char  c;
};
 
struct Empty {};

struct alignas(8)  Empty8  {};
struct alignas(32) Empty32 {};
struct alignas(64) Empty64 {};

struct alignas(8)  Char51Alignas8 { char name[51]; };
struct alignas(32) Char51Alignas32 { char name[51]; };
struct alignas(64) Char51Alignas64 { char name[51]; };


int main(int argc, char* argv[]){
    std::cout << "Alignment of"  "\n"
        "- char             : " << alignof(char)    << "\n"
        "- pointer          : " << alignof(int*)    << "\n"
        "- class Foo        : " << alignof(Foo)     << "\n"
        "- empty class      : " << alignof(Empty)   << "\n"
        "- alignas(8)  Empty: " << alignof(Empty8) << "\n"
        "- alignas(32) Empty: " << alignof(Empty32) << "\n"
        "- alignas(64) Empty: " << alignof(Empty64) << "\n"
		"- alignas(8)  CHR51: " << alignof(Char51Alignas8) << "\n"
		"- alignas(32) CHR51: " << alignof(Char51Alignas32) << "\n"
		"- alignas(64) CHR51: " << alignof(Char51Alignas64) << "\n";
    std::cout << "Sizeof of"  "\n"
        "- char             : " << sizeof(char)    << "\n"
        "- pointer          : " << sizeof(int*)    << "\n"
        "- class Foo        : " << sizeof(Foo)     << "\n"
        "- empty class      : " << sizeof(Empty)   << "\n"
        "- sizeof(8 ) Empty : " << sizeof(Empty8)  << "\n"
        "- sizeof(32) Empty : " << sizeof(Empty32) << "\n"
        "- sizeof(64) Empty : " << sizeof(Empty64) << "\n"
		"- sizeof(8)  CHR51 : " << sizeof(Char51Alignas8) << "\n"
		"- sizeof(32) CHR51 : " << sizeof(Char51Alignas32) << "\n"
		"- sizeof(64) CHR51 : " << sizeof(Char51Alignas64) << "\n";

	return 0;
}
END_UNIT 

BEGIN_SECTION(tour9_std_align)
template <std::size_t N>
struct MyAllocator
{
    char data[N];
    void* p;
    std::size_t sz;
    MyAllocator() : p(data), sz(N) {}
    template <typename T>
    T* aligned_alloc(std::size_t a = alignof(T))
    {
        if (std::align(a, sizeof(T), p, sz))
        {
            T* result = reinterpret_cast<T*>(p);
            p = (char*)p + sizeof(T);
            sz -= sizeof(T);
            return result;
        }
        return nullptr;
    }
};
 
int DEF_FUNC(tour9_std_align){
    MyAllocator<64> a;
 
    // allocate a char
    char* p1 = a.aligned_alloc<char>();
    if (p1)
        *p1 = 'a';
    std::cout << "allocated a char at " << (void*)p1 << '\n';
 
    // allocate an int
    int* p2 = a.aligned_alloc<int>();
    if (p2)
        *p2 = 1;
    std::cout << "allocated an int at " << (void*)p2 << '\n';
 
    // allocate an int, aligned at 32-byte boundary
    int* p3 = a.aligned_alloc<int>(32);
    if (p3)
        *p3 = 2;
    std::cout << "allocated an int at " << (void*)p3 << " (32 byte alignment)\n";
	return 0;
}	
END_SECTION(tour9_std_align)

BEGIN_UNIT_(inner_type)
template<class T> struct Z { typedef T type; };

int main(int argc, char* argv[]){

	HEAD("We can use inner type to define variables!");

	TRACE_CODE(Z<int>::type t1 = 2;)
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT // inner_type

#if ! _MSC_VER >= 1920
BEGIN_UNIT_(decltype)
struct A { double x; };
const A* a;

decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) // return type depends on template parameters
									  // return type can be deduced since C++14
{
	return t + u;
}

int foo(int y){ return y*y;}



struct S {
	double operator()(char, int&);
	float operator()(int) { return 1.0; }
};

struct X{
	int m;
};


/*template <class T>  //** 1. decltype(T().begin()) 
					//^^ 2. decltype(declval<T&>().begin())
                    //^^ 3. decltype(((T*)nullptr)->begin())
                    //^^ 4.TOVERIFY: This decltype(mem_fun(&T::begin()))::result_type
//inline bool iterator_is_last(T& o, decltype(((T*)nullptr)->begin()) iter){ // iter must not equal o.end
inline bool iterator_is_last(T& o, decltype(declval<T&>().begin()) iter){ // iter must not equal o.end
	if(++iter == o.end()){
		return true;
	}
	return false;
}*/

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	EXPLAINs("Content:");
	EXPLAINs("  1. decltype of variable");
	EXPLAINs("  2. decltype of lambda");
	EXPLAINs("  3. get return type of member operator()");
	EXPLAINs("  4. get type of class data member pointer");
	EXPLAINs("  5. use type of class member pointer as template type parameter");
	EXPLAINs("  6. use return type of class function member pointer as template type parameter");
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/5580253/get-return-type-of-member-function-without-an-object")
	HORIZONTAL_LINE();

	HEAD("1. Basic Test");
	TRACE_CODE(int i = 33;)
	TRACE_CODE(decltype(i) j = i * 2;)

	std::cout << "i = " << i << ", "
		<< "j = " << j << '\n';

	HEAD("2. Decltype of lambda");

	auto f = [](int a, int b) -> int
	{
		return a * b;
	};
	auto ff = [](int a, int b) -> int
	{
		return a + b;
	};

	decltype(f) g = f; TRACE_SRC(0,2, "++");// the type of a lambda function is unique and unnamed
	i = f(5, 6);
	j = g(7, 8);


	std::cout << "i = " << i << ", "
		<< "j = " << j << '\n';

	HEAD("3. get return type of member operator()");
	TRACE_TYPE(std::result_of<S(int)>::type);
	TRACE_TYPE(std::result_of<S(char, int&)>::type);
	TRACE_CODE(std::result_of<S(int)>::type m = 5;)
	//std::result_of<std::invoke_result(memPtr)>::type n = 5;

	X x = {10};
	int X::* p= &X::m;
	std::cout << x.*p << "\n";

	HEAD("4. get type of class member pointer");
	TRACE_TYPE(p);
	TRACE_TYPE(decltype(p)(X));
	TRACE_TYPE(std::result_of<decltype(p)(X)>);
	TRACE_CODE(std::result_of<decltype(p)(X)>::type n = 5;)
	HEAD("5. use type of class member pointer as template type parameter");
	TRACE_TODO();
	HEAD("6. use return type of class function member pointer as template type parameter");
	TRACE_TODO();
	HORIZONTAL_LINE();

	return 0;
}
END_UNIT //(tour9_decltype)
#endif


BEGIN_UNIT_(typeid)
struct Base {}; // non-polymorphic
struct Derived : Base {};

struct Base2 { virtual void foo() {} }; // polymorphic
struct Derived2 : Base2 {};

int main(int argc, char* argv[]) {
	HEAD("note");
	TRACE_CODE(const std::type_info& ti1 = typeid(Base);)
	TRACE_CODE(const std::type_info& ti2 = typeid(Base);)
	TRACE_CODE_(assert(&ti1 == &ti2);) ANNOTATE( not guaranteed)
	TRACE_CODE_(assert(ti1.hash_code() == ti2.hash_code());) ANNOTATE(guaranteed)
	TRACE_CODE_(assert(std::type_index(ti1) == std::type_index(ti2));) ANNOTATE( guaranteed)
	HORIZONTAL_LINEs();


	HEAD("basic testing");
	TRACE_CODE(int myint = 50;)
	TRACE_CODE(std::string mystr = "string";)
	TRACE_CODE(double *mydoubleptr = nullptr;)


	std::cout << "myint has type: " << typeid(myint).name() << '\n'
		<< "mystr has type: " << typeid(mystr).name() << '\n'
		<< "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n';
	HORIZONTAL_LINEs();


	HEAD("glvalue testing");
	ANNOTATE("std::cout << myint" is a glvalue expression of polymorphic type; it is evaluated)
	TRACE_CODE(const std::type_info& r1 = typeid(std::cout << myint);)
	std::cout << "!!!myint(50) printed!!!\n\"std::cout << myint\" has type : " << r1.name() << '\n';

	ANNOTATE("std::printf()" is not a glvalue expression of polymorphic type; NOT evaluated)
	TRACE_CODE(const std::type_info& r2 = typeid(std::printf("%d\n", myint));)
	std::cout << "!!!myint(50) not printed!!!\n\"printf(\"%d\\n\",myint)\" has type : " << r2.name() << '\n';
	HORIZONTAL_LINEs();

	HEAD("lvalue testing");
	ANNOTATE(Non-polymorphic lvalue is a static type)
	TRACE_CODE(Derived d1;)
	TRACE_CODE(Base& b1 = d1;)
	std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';

	TRACE_CODE(Derived2 d2;)
	TRACE_CODE(Base2& b2 = d2;)
	std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';
	HORIZONTAL_LINEs();

	HEAD("null pointer testing");
	try {
		ANNOTATE(dereferencing a null pointer: okay for a non-polymorphic expression)
		TRACE_CODE_(std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n';)
		ANNOTATE(dereferencing a null pointer: not okay for a polymorphic lvalue)
		TRACE_CODE(Derived2* bad_ptr = nullptr;)
		TRACE_CODE(
		std::cout << "bad_ptr points to... " << typeid(*bad_ptr).name() << '\n';
		)
	} catch(const std::bad_typeid& e) {
		std::cout << " caught " << e.what() << '\n';
	}
	HORIZONTAL_LINE();

	return 0;
}
END_UNIT//typeid

BEGIN_UNIT_(type_index)
struct A {	virtual ~A() {} };
struct B : A {};
struct C : A {};

struct R {};
struct S : R {};
struct T : R {};


int main(int argc, char* argv[])
{
	std::unordered_map<std::type_index, std::string> type_names;

	type_names[std::type_index(typeid(int))] = "int";
	type_names[std::type_index(typeid(double))] = "double";
	type_names[std::type_index(typeid(A))] = "A";
	type_names[std::type_index(typeid(B))] = "B";
	type_names[std::type_index(typeid(C))] = "C";
	type_names[std::type_index(typeid(R))] = "R";
	type_names[std::type_index(typeid(S))] = "S";
	type_names[std::type_index(typeid(T))] = "T";

	//CODE_FORMAT_Help __(-40);
	CODE_FORMAT_Help __2(CODE_FORMAT_, "%-40s");

	TRACE_CODE(int i;)
	TRACE_CODE(double d;)
	TRACE_CODE_(A a;)                         ANNOTATE(A, B and C are virtual)
	TRACE_CODE_(std::unique_ptr<A> b(new B);) ANNOTATE(note that we are storing pointer to type A)
	TRACE_CODE_(std::unique_ptr<A> c(new C);) ANNOTATE(note that we are storing pointer to type A)
	TRACE_CODE_(R r;)                         ANNOTATE(R, S and T are not virtual)
	TRACE_CODE_(std::unique_ptr<R> s(new S);) ANNOTATE(note that we are storing pointer to type R)
	TRACE_CODE_(std::unique_ptr<R> t(new T);) ANNOTATE(note that we are storing pointer to type R)

	std::cout << " i is " << type_names[std::type_index(typeid(i))] << '\n';
	std::cout << " d is " << type_names[std::type_index(typeid(d))] << '\n';
	std::cout << " a is " << type_names[std::type_index(typeid(a))] << '\n';
	std::cout << "*b is " << type_names[std::type_index(typeid(*b))] << '\n';
	std::cout << "*c is " << type_names[std::type_index(typeid(*c))] << '\n';
	std::cout << " r is " << type_names[std::type_index(typeid(r))] << '\n';
	std::cout << "*s is " << type_names[std::type_index(typeid(*s))] << '\n';
	std::cout << "*t is " << type_names[std::type_index(typeid(*t))] << '\n';
	return 0;
}
END_UNIT//type_index

BEGIN_UNIT_(is_defined_class__method1)

template<typename... Ts> struct make_void { typedef void type; };
template<typename... Ts> using void_t = typename make_void<Ts...>::type;

template <typename T, typename Enabler = void>
struct is_complete : std::false_type {};

template <typename T>
struct is_complete<T, void_t<decltype(sizeof(T) != 0)>> : std::true_type {};

class A;
class B{public: B(){std::cout<<"I am an object of B" << std::endl;}};

class C : public std::conditional<is_complete<A>::value, A, B>::type {
public: C(){std::cout<<"I am an object of C" << std::endl;}
};

class M{
public:
	virtual void f(B){printf("From M::f(B*)\n");}
};
class N : public M{
public:
	 void f(std::conditional<is_complete<A>::value, A, B>::type){ printf("From N::f(B*)\n"); }
};

int main(int argc, char* argv[]){
	HEAD("Test bool function");
	TRACE_CODE_(std::cout << is_complete<A>::value << std::endl);
	TRACE_CODE_(std::cout << is_complete<B>::value << std::endl);
	TRACE_CODE_(std::conditional<is_complete<A>::value, A, B>::type o);
	HEAD("Definition");
	TRACE_CODE(C x);
	TRACE_CODE(M m);
	TRACE_CODE_(m.f(o));
	TRACE_CODE_(m.f(x));
	TRACE_CODE(N n);
	TRACE_CODE_(n.f(o));
	TRACE_CODE_(n.f(x));

	TRACE_CODE(M* p = new N);
	TRACE_CODE_(p->f(o));
	TRACE_CODE_(p->f(x));

//	HEAD("The following messages is testing macro");
//#if is_complete<A> tour9_is_defined_class__method1
//	printf("A is a completed TYPE\n");
//#else
//	printf("A is not a completed TYPE\n");
//#endif
//
//#if is_complete<B> 
//	printf("B is a completed TYPE\n");
//#else
//	printf("B is not a completed TYPE\n");
//#endif
//	HEAD("The following messages is testing macro END");
//
	return 0;
}
END_UNIT//is_defined_class__method1


BEGIN_UNIT_(is_defined_class__method2)

/**
TOVERIFY 
    This mehtod is not working for C++11
TODO     
    Test Function For: <<decltype(A,B)>>
NOTICE
    template variable is supported since c++14
*/

template<typename T, typename = void>
constexpr bool is_defined = false;

template<typename T>
constexpr bool is_defined<T, decltype(typeid(T), void())> = true;

struct C1 {}; // i.e. `complete` is defined.
struct C2;    // not defined, just a forward declaration

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	MANUAL()

	HEAD1("Definition");
	TRACE_SRC(-14,-7);
	HEAD1("Usage");

	TRACE_CODE_(std::cout <<  is_defined<C1>   << std::endl);
	TRACE_CODE_(std::cout <<  is_defined<C2>   << std::endl);

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//is_defined_class__method2


BEGIN_UNIT_(auto)
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	REFERENCE("https://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html");
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT
