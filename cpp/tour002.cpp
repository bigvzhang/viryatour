#include <numeric>
#include <iterator>
#include "vtestcommon.h"
#include <vsys.h>
#define TOUR_GROUP tour2_
/**
 *Class
 *  1) concrete classes
 *  2) abstract classes
 *  3) classes in class hiearachies
 */

BEGIN_UNIT_(copy_constructor)
/**
NAME
    A copy constructor of class T is a non-template constructor whose first parameter is 
	T&, const T&, volatile T&, or const volatile T&, and either there are no other 
	parameters, or the rest of the parameters all have default values.
*/
struct A {
    int n;
    A(int n = 1) : n(n) { }
    A(const A& a) : n(a.n) { } // user-defined copy ctor
};
 
struct B : A {
    // implicit default ctor B::B()
    // implicit copy ctor B::B(const B&)
};
 
struct C : B {
     C() : B() { }
 private:
     C(const C&); // non-copyable, C++98 style
                  // C(const C&) = delete; C++11 style
};
 
int main(int argc, char* argv[]) {
	TRY_MANUAL(); HORIZONTAL_FRAME(TRACE_SRC(-19, -3)); TRACE_SRC(1,10);	HORIZONTAL_LINE();
    A a1(7);  // calls direct 
    A a2(a1); // calls the copy ctor
    B b;
    B b2 = b;
    A a3 = b; // conversion to A& and copy ctor
    volatile A va(10);
    // A a4 = va; // compile error
 
    C c;
    // C c2 = c; // compile error
	return 0;
}
END_UNIT // copy_constructor

BEGIN_UNIT_(explicit_constructor)
namespace n1{
class A
{
public:
	A(){};
	A(int){};
	A(const char*, int = 0){};
};
void test(){
	HEAD1("converting constructors");TRACE_SRC(-8, -2); HORIZONTAL4s(); TRACE_SRC(+1, +7);
	A a1;
	A a2 = A(1);
	A a3(1);
	A a4 = A("Venditti");
	A* p = new A(1);
	A a5 = (A)1;
	A a6 = static_cast<A>(1);

	A c = 1;
	A d = "Venditti";
}
}

namespace n2{
class A
{
public:
	explicit A(){};
	explicit A(int){};
	explicit A(const char*, int = 0){};
};
void test() {
	HEAD1("explicit constructors"); TRACE_SRC(-8,-2); HORIZONTAL4s(); TRACE_SRC(+1,+7);
	A a1;
	A a2 = A(1);
	A a3(1);
	A a4 = A("Venditti");
	A* p = new A(1);
	A a5 = (A)1;
	A a6 = static_cast<A>(1);
}
}

namespace n3{
class A
{
public:
	template <class Fn, class... Args>
	explicit A(Fn&& fn, Args&&... args){
		std::invoke(fn, args...);
	}
};

void f(){std::cout<< "executing " <<__FUNCTION__<< std::endl;}

void test() {
	HEAD1("explicit constructors in template function"); TRACE_SRC(-12, +2); HORIZONTAL4s(); TRACE_SRC(+1,+1);
	A a(&f);
}

}


int main(int argc, char* argv[]){

	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/25680461/variadic-template-pack-expansion");
	REFERENCE("https://www.cplusplus.com/reference/thread/thread/thread/");
	n1::test();
	n2::test();
	n3::test();
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT // explicit_constructor


BEGIN_UNIT_(converting_constructor)

struct A
{
    A() { }         // converting constructor (since C++11)  
    A(int) { }      // converting constructor
    A(int, int) { } // converting constructor (since C++11)
};
 
struct B
{
    explicit B() { }
    explicit B(int) { }
    explicit B(int, int) { }
};
 
int main(int argc, char* argv[]){
	HORIZONTAL_FRAME(REFERENCE("https://en.cppreference.com/w/cpp/language/converting_constructor")); TRACE_SRC(-16,+18); HORIZONTAL1();
    A a1 = 1;      // OK: copy-initialization selects A::A(int)
    A a2(2);       // OK: direct-initialization selects A::A(int)
    A a3{4, 5};    // OK: direct-list-initialization selects A::A(int, int)
    A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
    A a5 = (A)1;   // OK: explicit cast performs static_cast, direct-initialization
 
//  B b1 = 1;      // error: copy-initialization does not consider B::B(int)
    B b2(2);       // OK: direct-initialization selects B::B(int)
    B b3{4, 5};    // OK: direct-list-initialization selects B::B(int, int)
//  B b4 = {4, 5}; // error: copy-list-initialization selected an explicit constructor
                   //        B::B(int, int)
    B b5 = (B)1;   // OK: explicit cast performs static_cast, direct-initialization
    B b6;          // OK, default-initialization
    B b7{};        // OK, direct-list-initialization
//  B b8 = {};     // error: copy-list-initialization selected an explicit constructor
                   //        B::B()
    return 0;
}
END_UNIT//

BEGIN_UNIT_(default_constructor)//

template<typename... Xs>
struct unison : public Xs...{
	//unison(Xs&&...args) :Xs(args)...{}
	unison(const Xs&...args) :Xs(args)...{}
	//unison(){}
};

class class1{ 
public:
	void print1() {printf("%s\n", __CLASS_NAME__);}
};

class class2{
private:
	int member;
public:
	class2(int x){member=x;}
public:
	void print2() { printf("class:%s, member:%d\n", __CLASS_NAME__, member); }
};

class class3{
private:
	int member;
public:
	class3(){member=300;}
	class3(int x){member=x;}
public:
	void print3() { printf("class:%s, member:%d\n", __CLASS_NAME__, member); }
};

int main(int argc, char* argv[]){
	HEAD1("Definitions")
	TRACE_SRC(-26,-4);

	HEAD1("We can use default constructors of class1 and class3");TRACE_SRC(1,10, "++");
	class1 c1;   // OK
	class2 c2(250); // OK
	class2 c2A(); // BAD; for gcc, warning: empty parentheses were disambiguated as a function declaration  
	//class2 c2B; // ERR
	class2 c2C(c2); // OK
	class3 c3;   // OK

	c1.print1();
	c2.print2();
	//c2A.print();  // ERR
	c3.print3();

	HEAD1("We can use default copy constructors of class2 when referened as a base class or member!");TRACE_SRC(1, 4, "++");
	unison<class1, class2, class3> bond(c1,c2,c3);
	bond.print1();
	bond.print2();
	bond.print3();

	HORIZONTAL_LINE();
	EXPLAINs("SUMMARY");
	EXPLAINs("   - if any form of constructor is defined, the default constructor is gone          ");
	EXPLAINs("                                            but the default copy constructor is there");

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//default_constructor

BEGIN_UNIT_(delegating_constructor)
struct S{
	int n;
	S(int n):n(n){}      // constructor definition
	S() : S(7)   {}      // using delegating constructor
};
int main(int argc, char* argv[]){TRACE_SRC(-5,-1)
	return 0;
}
END_UNIT //delegating_constructor

BEGIN_UNIT_(copy_initialization, constructor) virya::ioq ioq(" $ ");
namespace n1 { 
struct A {
	A(int i) { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	~A()     { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
};
}
namespace n2 { 
struct A { 
	A(int i) { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	A(A& k)  { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	~A()     { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
};
}
namespace n3 {
struct A {
	A(int i) { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	A(A& k)  = delete;
	~A()     { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
};
}
namespace n4 { 
struct A {
	explicit A(int i) { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	explicit A(A& k)  { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	~A()     { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
};
}
namespace n5 {
struct A {
	A()      { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	A(int i) { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	A(A& k)  { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	~A()     { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
};
}
namespace n6 {
struct A {
	explicit A()      { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	explicit A(int i) { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	explicit A(A& k)  { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
	~A()     { ioq.printf("executing %s \n", __PRETTY_FUNCTION__); }
};
}

int main(int argc, char* argv[]){TRACE_SRC(-44, -2); HORIZONTAL1(); CODE_FORMAT_Help __(-30);
	HEAD5s("expression: A a = 1");
	         { n1::A a = 1; }         TRACE_QUE();
	CODE_NOTk( n2::A a = 1; )         TRACE_QUE();
	CODE_NOTk( n3::A a = 1; )         TRACE_QUE();
	CODE_ERRc( n4::A a = 1; )         TRACE_QUE();
	HEAD5s("expression: A a = {1}");
	{ n1::A a = {1}; }                TRACE_QUE();
	{ n2::A a = {1}; }                TRACE_QUE();
	{ n3::A a = {1}; }                TRACE_QUE();
	CODE_ERRc( n4::A a = {1}; )       TRACE_QUE();
	HEAD5s("expression: A a; a = 1  -- copy assignment");
	CODE_ERRc( n1~n4           )      TRACE_QUE();
	         { n5::A a; a = 1; }      TRACE_QUE();
	CODE_ERRc( n6::A a; a = 1; )      TRACE_QUE();
	HEAD5s("expression: A a; a ={1} -- copy assignment");
	CODE_ERRc( n1~n4             )    TRACE_QUE();
	         { n5::A a; a = {1}; }    TRACE_QUE();
	CODE_ERRc( n6::A a; a = {1}; )    TRACE_QUE();
	         { n6::A a;a=n6::A{1}; }  TRACE_QUE();
	return HORIZONTAL1();
}
END_UNIT//copy_initialization

BEGIN_UNIT_(vector_copy, =move_constructor, =std_initializer_list, copy constructor, move assignment)
virya::ioq ioq;

#define TEST_MOVE_FUNCTIONS

class Vector_size_mismatch{
	
};

class Vector{
	friend Vector operator-(const Vector& t, const Vector& o);
	friend Vector operator*(const Vector& t, int);

private:
	double*elem;
	int sz;
public:
	Vector(int s);
	Vector(const std::initializer_list<double> a);
	
	Vector(const Vector&o);
	Vector& operator=(const Vector&o);

#ifdef TEST_MOVE_FUNCTIONS	
	Vector(Vector&&o);               // Move 
	Vector& operator=(Vector&&o);
#endif
	
	
	~Vector(){delete[] elem;}


	double & operator[](int i);
	const double& operator[](int i) const;
	int size() const;
	std::string toString();
	
	Vector  operator+(const Vector&o);
	
	double* begin(){return elem;}
	double* end()  {return elem + sz;}

};

Vector::Vector(int s)
	:
	sz(s){
	elem = new double[s];
}

Vector::Vector(const std::initializer_list<double> a)
	:
	elem(new double[a.size()]), sz(a.size())
{
	std::copy(a.begin(),a.end(), elem);
}

Vector::Vector(const Vector&o)
	:
	sz(o.sz){
	elem = new double[sz];
	for(int i = 0; i < sz; ++i){
		elem[i] = o.elem[i];
	}
}

Vector& Vector::operator=(const Vector& o){
	double* p = new double[o.sz];
	for(int i = 0; i < o.sz; ++i){
		p[i] = o.elem[i];
	}
	delete[] elem;
	elem = p;
	sz = o.sz;
	return *this;
}

#ifdef TEST_MOVE_FUNCTIONS
Vector::Vector(Vector&&o)
	:
	sz(o.sz){
	elem=o.elem;
	o.sz=0;
	o.elem=nullptr;
	ioq.printf("Move Constructor Called\n");
}


#define switch_value(x,y) {auto z=x; x=y; y=z;}
Vector& Vector::operator=(Vector&& o){
	switch_value(o.sz,   sz)
	switch_value(o.elem, elem)
	ioq.print("Move Assignment Called");
	return *this;
}
#endif

Vector Vector::operator+(const Vector& o){
	if(sz != o.sz)
		throw 2;// Vector_size_mismatch{};
	
	Vector rtn = *this;
	for(int i = 0; i < o.sz; ++i){
		rtn.elem[i] += o.elem[i];
	}
	
	return rtn;
}

Vector operator*(const Vector& t, int n){
	Vector rtn = t;
	for(size_t i = 0; i < rtn.sz; ++i){
		rtn.elem[i] *= n;
	}
	return rtn;
}

Vector operator-(const Vector& t, const Vector& o){
	if(t.sz != o.sz)
		throw 2;// Vector_size_mismatch{};
	
	Vector rtn = t;
	for(int i = 0; i < o.sz; ++i){
		rtn.elem[i] = t.elem[i] - o.elem[i];
	}
	
#define USING_MULTIPATH
#ifdef  USING_MULTIPATH
	// The Following Will Use Move Constructor
	if(2>1)
		return rtn; // 
	else
		return t;
#else
	// The Following Will Use Move Assignment
	// The Compilor  Will Tue Performance For This Case
	return rtn;
#endif
}

double & Vector::operator[](int i){
	return elem[i];
}

const double& Vector::operator[](int i) const{
	return elem[i];
}

int Vector::size() const{
	return sz;
}

std::string Vector::toString(){
	std::string s;
	for(int i = 0; i < sz; i++){
		s  += " ";
		s  += std::to_string(elem[i]);
	}
	return s;
}

Vector f(){
	Vector x = {1,2,3};// PRINT_CONTENT(x);
	Vector y = {4,5,6};// PRINT_CONTENT(y);
	Vector z = {7,8,9};// PRINT_CONTENT(z);
	z = x;
	//SET_RUNNING_LINE(); y = std::move(x);
	//SET_RUNNING_LINE(); 
	return z;
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	try{CODE_FORMAT_Help __(-40);
		Vector v1 = {1, 2, 3, 4};  TRACE_QUEm(v1);
		Vector v2 = {5, 6, 7, 8};  TRACE_QUEm(v2)
		Vector v3 = v1+v2;         TRACE_QUEm(v3)
		Vector v4(5);              TRACE_QUEm(v4)
		Vector v5{5,6};            TRACE_QUEm(v5)
		v5 = v1+v2;                TRACE_QUEm(v5)
		Vector v6 = v1*2;          TRACE_QUEm(v6)
			
		HORIZONTAL_LINEs();
		Vector v7 = f();           TRACE_QUEm(v7)
		Vector v8 = {0,0};         TRACE_QUEm(v8)
		v8 = f();                  TRACE_QUEm(v8)
		Vector v9 = v2-v1;         TRACE_QUEm(v9)

		HORIZONTAL_LINEs();
		Vector vA = std::move(v1); TRACE_QUEm(vA)
		                           TRACE_QUEm(v1)
		Vector vB = {8,3,2};       TRACE_QUEm(vB)
		vB = std::move(v2);        TRACE_QUEm(vB)
		/* vB != v2 */             TRACE_QUEm(v2)
		vB = v2;                   TRACE_QUEm(vB)
		/* vB == v2 */	 		   TRACE_QUEm(v2)
			

	}catch(...){
		printf("Caught Exception\n");
	}

	HORIZONTAL_LINE();
	EXPLAINs("1. `C v = f()`     will NOT call move constructor(named return value optimization)")
	EXPLAINs("2. `C v = v1 + v2` will     call move constructor(NRVO fails)")
	EXPLAINs("3. `C v = v1 * n`  will NOT call move constructor(NRVO works)")
	HORIZONTAL_LINE();
	
	return 0;
}
END_UNIT//vector_copy

BEGIN_UNIT_(iota)
class Value {
private:
	int i;
public:
	Value(int x): i(x){}
public:
	Value& operator ++(){i+=10; return *this;}
	operator int(){return i;}
};
using namespace std;
int main(int argc, char* argv[]){
	HORIZONTAL_LINE()
	{
		HEAD("SIMPLE");
		TRACE_SRC(0, 3);
		vector<int> test1(10);
		iota(test1.begin(), test1.end(), 100);
		copy(test1.begin(), test1.end(), ostream_iterator<int>(cout, "~"));
		cout << "\n";
	}
	{
		HEAD("using value of class which overrides ++value");
		TRACE_SRC(-22,-14);
		HORIZONTAL_LINE('.', 60)
		TRACE_SRC(0, 3);
		vector<int> test1(10);
		Value v(500);
		iota(test1.begin(), test1.end(), v);
		copy(test1.begin(), test1.end(), ostream_iterator<int>(cout, "~"));
		cout << "\n";
	}
	HORIZONTAL_LINE()
	return 0;
}
END_UNIT

BEGIN_UNIT_(vector_append)
#define TRACE_vector(vct)    {\
	printf("%s => { ",  #vct); \
	for(auto& m: vct) std::cout << m << " ";\
	std::cout<<"}\n";}

using namespace std;
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector");
	HORIZONTAL_LINE();
	vector<int> a{1,2,3};
	vector<int> b{100};
	vector<int> c{200};
	vector<int> d{300};
	TRACE_SRC(-4, -1); HORIZONTAL_LINEs(); 
	ANNOTATE(There are following 3 methods to append one vector to the other:)
	TRACE_SRC(+1, +3); HORIZONTAL_LINEs();
	b.insert(b.end(), a.begin(), a.end());
	c.insert(end(c),  begin(a) , end(a));
	copy(a.begin(), a.end(), back_inserter(d));
	ANNOTATE(Check the result after run!)
	TRACE_vector(a);
	TRACE_vector(b);
	TRACE_vector(c);
	TRACE_vector(d);
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT

BEGIN_UNIT_(vector_insert)
KEYWORDS(vector, insert, emplace)
class F {
public:
	int x;
	int y;
public:
	F(int x, int y):x(x),y(y){}
};

using std::ostream;
ostream& operator<<(ostream&o, const F& a){
	o<< "[" << a.x <<":" <<a.y << "]";
	return o;
}


using namespace std;
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	HEAD1("1. Insert at head");
	TRACE_SRC(0,5)
	vector<int> v;
	for(int i = 1; i <=5; i++){
		v.insert(v.begin(), i);
	}
	TRACE_vector(v);
	HEAD1("2. Insert at tail");
	v.clear();
	TRACE_SRC(0, 4)
	for(int i = 1; i <= 5; i++){
		v.insert(v.end(), i);
	}
	TRACE_vector(v);
	HEAD1("3. Emplace at begin");
	v.clear();
	TRACE_SRC(0, 4)
		for(int i = 1; i <= 5; i++){
			v.emplace(v.begin(), i);
		}
	TRACE_vector(v);
	HEAD1("4. Emplace vs insert");
	TRACE_SRC(0, 8);
	vector<F> f1;
	vector<F> f2;
	for(int i = 1; i <= 5; i++){
		f1.emplace(f1.begin(), i, i * 100);
	}
	for(int i = 1; i <= 5; i++){
		f2.insert(f2.begin(), F(i, i * 100));// specify constructor
	}
	TRACE_vector(f1);
	TRACE_vector(f2);

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT


BEGIN_UNIT_(vector_initialize)
KEYWORDS(vector, insert, emplace)

class Array {
public:
	std::vector<int> content;
public:
	Array(const std::initializer_list<int> m):content{m}{}
public:
	void print(){
		for(int i  = 0; i < content.size(); i++){
			if(i==0)
				printf("%d",content[i]);
			else
				printf(", %d", content[i]);
		}
		printf("\n");
	}
};

using namespace std;
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	HEAD("List(Aggregate) initialization");
	TRACE_SRC(-17, -17)
	TRACE_SRC(0, 1)
	Array a{3,4,5};
	a.print();

	return 0;
}

END_UNIT


BEGIN_UNIT_(initializer_list, range-based for loop) using namespace std;
/**
NAME
    A std::initializer_list object is automatically constructed when:
     - a braced-init-list is used to list-initialize an object, where the corresponding constructor accepts an std::initializer_list parameter
     - a braced-init-list is used as the right operand of assignment or as a function call argument, and the corresponding assignment operator/function accepts an std::initializer_list parameter
     - a braced-init-list is bound to auto, including in a ranged for loop
 */
int main(int argc, char* argv[]){
	MANUALb();
	
	NOTICE(member function begin returns pointer, quite different than class vector); TRACE_SRC(1,6);
	initializer_list<int> c1 = {1,2,3,4};
	const int* c1_ptr = c1.begin();       //`begin()` returns int*      
	c1_ptr++;
	c1_ptr++;
	vector<int> v1 = {1,2,3,4};
	//vector.begin return iterator: expression `const int* v1_ptr = v1.cbegin()` will fail
	REFERENCE("https://docs.microsoft.com/en-us/cpp/standard-library/initializer-list-class");
	HORIZONTAL_LINE();
	
	return 0;
}
END_UNIT//

BEGIN_UNIT_(forward_list) using namespace std;
/**
NAME
    1. header <forward_list> defines the container class template forward_list and several supporting templates.
    2. std::forward_list is a container that supports fast insertion and removal of elements from anywhere in the 
       container. Fast random access is not supported. It is implemented as a singly-linked list. Compared to std::list 
       this container provides more space efficient storage when bidirectional iteration is not needed.
DEMO
    variadic template parameter
*/
int main(int argc, char* argv[]){
	
	MANUALb();
		
	return 0;
}
END_UNIT//

BEGIN_UNIT_(constructors, member initializer list) using namespace std;
/**
DEFINE
    Constructor is a special non-static member function of a class that is used to initialize objects of its class type.
    In the definition of a constructor of a class, member initializer list specifies the initializers for direct and virtual bases and non-static data members. (Not to be confused with std::initializer_list.)
    A constructor must not be a coroutine.(since C++20)
INITIALIZATION.ORDER
    The order of member initializers in the list is irrelevant: the actual order of initialization is as follows:
      1) If the constructor is for the most-derived class, virtual bases are initialized in the order in which they appear in depth-first left-to-right traversal of the base class declarations (left-to-right refers to the appearance in base-specifier lists)
      2) Then, direct bases are initialized in left-to-right order as they appear in this class's base-specifier list
      3) Then, non-static data member are initialized in order of declaration in the class definition.
      4) Finally, the body of the constructor is executed
*/
int main(int argc, char* argv[]){
	MANUALb();return 0;
}
END_UNIT//

BEGIN_UNIT_(initialization)
/**
NAME
    copy elision
    converting constructor
    copy assignment
    copy constructor
    default constructor
    destructor
    explicit
    initialization
        aggregate initialization
        constant initialization
        copy initialization
        default initialization
        direct initialization
        list initialization
        reference initialization
        value initialization
        zero initialization
    move assignment
    move constructor
    new
*/

int main(int argc, char* argv[]){
	MANUALb(); return 0;
}
END_UNIT//initialization


BEGIN_UNIT_(default_initialization)
/**
NAME
    This is the initialization performed when an object is constructed with no initializer.
SYNTAX
    T object;
    new T;
SITUATION
    Default initialization is performed in three situations:
    1) when a variable with automatic, static, or thread-local storage duration is declared with no initializer;
    2) when an object with dynamic storage duration is created by a new-expression with no initializer;
    3) when a base class or a non-static data member is not mentioned in a constructor initializer list and that constructor is called.
TIP
    Default initialization of a const object
    1) POD object(with implicit default ctor) cannot be defined without copy-initialization, while non-POD object can
*/

struct T1 { int mem; };
 
struct T2
{
    int mem;
    T2() { } // "mem" is not in the initializer list
};
 
int n; // static non-class, a two-phase initialization is done:
       // 1) zero initialization initializes n to zero
       // 2) default initialization does nothing, leaving n being zero
 
void main()
{
    int n;            // non-class, the value is indeterminate
    std::string s;    // class, calls default ctor, the value is "" (empty string)
    std::string a[2]; // array, default-initializes the elements, the value is {"", ""}
//  int& r;           // error: a reference
//  const int n;      // error: a const non-class
//  const T1 t1;      // error: const class with implicit default ctor
    T1 t1;            // class, calls implicit default ctor
    const T2 t2;      // const class, calls the user-provided default ctor
                      // t2.mem is default-initialized (to indeterminate value)
}
int main(int argc, char* argv[]){
	TRACE_SRCb(-25,-2); 
	
	MANUALt(TIP)
	return 0;
}
END_UNIT//initialization


BEGIN_UNIT_(virtual_destructor) using namespace std;
/**
NAME
	virtual desctructor	
*/
class B0 {
public:
	virtual ~B0(){printf("~B0\n");}
};
class B1 : public B0{
public:
	 ~B1(){ printf("~B1\n"); }
};
class B2 : public B0{
};

int main(int argc, char* argv[]){
	B0 b0;
	B1 b1;
	B2 b2;
	return 0;
}
END_UNIT//
	
/**
 *Templates
 *  1) parameterized tempaltes => template<typename T> class X{};
 *  2) Function Templates      => template<class A, class B> void f(A a, B b){}
 *  3) Function Objects        => template<class X> class A{ bool opertor()(X x){reutnr x > _content;}};
 *  4) Variadic Templates
 *  5) Alias
 */



BEGIN_UNIT_(guidelines)

/**
 * 1. Express ideas directly in code;
 * 2. Define classes to represent application concetps directly in code
 * 3. Use concrete classes for simple concepts and performace critical components
 * 4. Avoid "naked" new and delete operations
 * 5. Use resource handles and RAII to manage resources
 * 6. Use abstract classes as interfaces when complete separation of interface and implementation is needed
 * 7. Use class hierachies to represent concepts with an inherent hierachical structure
 * 8. When designing a class hierachy, distinguish between implementation inheritance and interface inheritance
 * 9. Control construction, copy, move and destruction of objects
 * 10. Use containers, defined as resource handle template, to hold collections of values of the same type
 * 11. Use function templates to represent general algorithms
 * 12. Use function objects, including lambda, to represent policies and actions
 * 13. Use type and template aliases to provide a uniform notation for types that may vary among similar types or among implementations
 */

int main(int argc, char* argv[]){
	REFERENCE("https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines");
	TRACE_SRC(-17,-5);
	return 0;
}
END_UNIT//


BEGIN_UNIT_(recommendations)

/**
FACTORY|SAFE_CREATOR
    1. No public constructor, only a factory function, so there's no way to have getptr return nullptr.
	2. if return shared_ptr, Not using std::make_shared<Best> because the c'tor is private.
    Demo - beset of enable_shared_from_this
 */
int main(int argc, char* argv[]){
	MANUAL();
	return 0;
}
END_UNIT//
