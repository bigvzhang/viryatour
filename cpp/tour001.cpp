#include<iostream>
#include<map>
#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <limits.h>

#include "vtestcommon.h"
#define TOUR_GROUP tour1_

#define DEF_FUNC(X) X(int argc, char* argv[])


#define PRINT_CONTENT(X) {printf("[%4d] %s => %s\n",__LINE__, #X, X.toString().c_str()); running_line = __LINE__ + 1;}
#define EXECUTE_LINE(...) printf("%s ==> \n",#__VA_ARGS__); __VA_ARGS__



BEGIN_UNIT_(hello)

double square(const double x){return x*x;}
void print_square(const double x){
	std::cout << "the squre of " << x << " is " << square(x) << '\n';
}

int main(int argc, char* argv[]){
	std::cout << "Hello, World\n";
	print_square(1.234); // print: the square of 1.234 is 1.52276
	print_square(5.555); // print: the square of 5.555 is 30.858
	return 0;
}
END_UNIT// hello


BEGIN_UNIT_(printf)
int main(int argc, char * argv[]){
	HORIZONTAL_LINE();
	TRACE_CODE(printf("'%c'\n", '\0'));
	TRACE_CODE(printf("'%c'\n", 0));
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT// io




#include <complex>
using namespace std;

BEGIN_UNIT_(var)
int main(int argc, char* argv[]){
    complex<double> c_1   {2,3};  TRACE_E();
    complex<double> c_2 = {1,2};  TRACE_E();
    complex<double> c_3 = {5};    TRACE_E();
	cout << "c_1: " << c_1 << "  c_2: " <<c_2 << "  c_3: " <<c_3 << "\n";
	return 0;
}
END_UNIT // variable

enum WeekDay {Sun, Mon, Tue, Wen, Thur, Fri, Sat};
#define WEEKDAY(X) {#X,X}
const map<const char*, int> map_StrWeekday = {
	WEEKDAY(Sun),
	WEEKDAY(Mon),
	WEEKDAY(Tue),
	WEEKDAY(Wen),
	WEEKDAY(Thur),
	WEEKDAY(Fri),
	WEEKDAY(Sat),
};
#undef WEEKDAY

#define WEEKDAY(X) {X, #X}
const map<int, const char*> map_WeekdayStr = {
	WEEKDAY(Sun),
	WEEKDAY(Mon),
	WEEKDAY(Tue),
	WEEKDAY(Wen),
	WEEKDAY(Thur),
	WEEKDAY(Fri),
	WEEKDAY(Sat),
};
#undef WEEKDAY



const int   GET_WEEKDAY(const char* c){auto it = map_StrWeekday.find(c); return it->second;}
const char* GET_WEEKDAY(const int   c){auto it = map_WeekdayStr.find(c); return it->second;}
constexpr double square1(const double x){return x*x;}
constexpr double square2(double x){return x*x;}
constexpr int    square1(const int x){return x*x;}

#define STRDAY(X) GET_WEEKDAY(X)

BEGIN_UNIT_(const)
int main(int argc, char* []){
	for(int i = 0; i < map_StrWeekday.size(); i++){
		switch(GET_WEEKDAY(GET_WEEKDAY(i))){
		case Sun/*WEEKDAY(Sun)*/: printf("%d => %s\n", i, STRDAY(i)); break;
		}
	}
	constexpr double a1 = square1(8);
	double a2 = square1(9);
	constexpr double a3 = square2(3);
	printf("%5.2f <= %s\n", a1, "constexpr double a1 = square1(8);");
	printf("      => constexpr double square1(const double x){return x*x;}\n");
	printf("      !! constexpr must be specified\n");
	printf("%5.2f <= %s\n", a2, "double a2 = square1(9);");
	printf("     !<= constexpr function can be used for none constexpr\n");
	printf("%5.2f <= %s\n", a3, "constexpr double a3 = square2(8);");
	printf("      => constexpr double square2(double x){return x*x;}\n");
	printf("      !! parameters can be non-const\n");

	constexpr int N = square1(2);
	const int M= square1(3);
	for(int i = 0; i < 20; i++){
		switch(i){
		case N: 
		//case M:
			printf("Got %2d <= constexpr int N = square1(2); switch{case N:} \n", N);
			printf("        !! const int M(%d) = square1(3);                 \n", M);
			printf("        !! M Cannot be used In Switch <!!==   //case M:  \n");
		break;
		case square1(4):
			printf("Got %2d <=  switch{case square1(4):}\n", i);
			break;
		}
	}
	return 0;
}
END_UNIT // const

BEGIN_SECTION(tour1_loop)
int DEF_FUNC(tour1_loop){

	const     double dmv = 17;
	return 0;
}
END_SECTION(tour1_loop)

BEGIN_SECTION(tour1_ptr)
int DEF_FUNC(tour1_ptr){
	int a1[10] = {1,2,3,4,5,6,7,8,9,10};
	int a2[10];
	for (int i = 0; i < 10; i++)
		a2[i] = a1[i];
	
	for(auto x : a2)
		cout << x << " ";
	cout << "\n";
	
	
	for(auto &x : a2)
		x++;

	for(auto x : a2)
		cout << x << " ";
	cout << "\n";
	
	for(auto x : {21,12,15})
		cout << x << " ";
	cout << "\n";
	
	//cout << "NullPtr:" << nullptr << " \n";
	return 0;
}
END_SECTION(tour1_ptr)

BEGIN_UNIT_(enum)

enum class  Color { Red, Blue, Green};
enum class  Traffic_light{Red, Yellow, Green};
enum Coutry{China, Korea, Japan};

ostream& operator<<(ostream&o, const Color& c){
	switch(c){
		case Color::Red:   o<<"Red"  ; break;
		case Color::Blue:  o<<"Blue" ; break;
		case Color::Green: o<<"Green"; break;
		default: throw 1;
	}
	return o;
}

ostream& operator<<(ostream&o, const Traffic_light& c){
	switch(c){
		case Traffic_light::Red:     o<<"Red"    ; break;
		case Traffic_light::Yellow:  o<<"Yellow" ; break;
		case Traffic_light::Green:   o<<"Green"  ; break;
		default: throw 1;
	}
	return o;
}

int main(int argc, char* argv[]){

	Color a = Color::Red;
	Traffic_light light1 = Traffic_light::Green;
	int i1 = (int)light1 ; 
	Coutry c = China;
	int c1 = c;
	cout << "Color    " << a      << "{ostream && operator<<(ostream&c, const Color& c)}\n";
	cout << "Light1   " << light1 << "{ostream && operator<<(ostream&c, const Traffic_light& c)}\n";
	cout << "int      " << i1     << "{int i1 = (int)light1 ; }\n";
	cout << "Coutry   " << c      << "\n";
	cout << "Coutry(i)" << c      << "{int c1 = c;}            \n";

 	return 0;
}
END_UNIT // enum

// modularity
/*
 * 1) Header And Source
 * 2) Separate Compilation
 * 3) Namespace
 */

// Error Handling
/**
 * 1) Exception
 * 2) Invariants, Exception In Constructor
 * 3) Static Assertions
 */
class A{
public:
	int a;
public:
	constexpr A(int param_a):a(param_a){}
	constexpr A():a(0){}
};
BEGIN_SECTION(tour1_assert)
int DEF_FUNC(tour1_assert){
	constexpr double a1 = square1(8);
	constexpr double a2 = square1(9);
	//static_assert(a1 > 64);
	//#define __FUNCDNAME__  __FUNCTION__ 
	printf("FILE, %s %s\n", __FILE__, __FUNCTION__);
	constexpr A x;
	return 0;
}
END_SECTION(tour1_assert)


BEGIN_UNIT_(conversion)
int main(int argc, char * argv[]){
	TRACE_CODE(int a = 1;);
	TRACE_CODE(int b = INT_MIN;);
	TRACE_CODE(int c = INT_MAX;);
	TRACE_CODE(int m = INT_MAX - 1;);
	TRACE_CODE(printf("1) => a:%d b:%d c:%d\n", a, b, c););
	TRACE_CODE(printf("2) => a:%f b:%f c:%f\n", a, b, c););
	TRACE_CODE(int d = float(a););
	TRACE_CODE(int e = float(c););
	TRACE_CODE(printf("3) => a:%d b:%d c:%d d:%d e:%d\n", a, b, c,d,e););
	TRACE_CODE(    e = float(m););
	TRACE_CODE(printf("4) => a:%d b:%d c:%d d:%d e:%d\n", a, b, c,d,e););
	TRACE_CODE(    e = float(999999););
	TRACE_CODE(printf("5) => a:%d b:%d c:%d d:%d e:%d\n", a, b, c,d,e););
	TRACE_CODE(    e = float(9999999););
	TRACE_CODE(printf("6) => a:%d b:%d c:%d d:%d e:%d\n", a, b, c,d,e););
	TRACE_CODE(    e = float(99999999););
	TRACE_CODE(printf("6) => a:%d b:%d c:%d d:%d e:%d\n", a, b, c,d,e););
	return 0;
}
END_UNIT//301_conversion

BEGIN_UNIT_(typelong)
int main(int argc, char * argv[]){
	HORIZONTAL_LINE();
	TRACE_CODE(printf("sizeof long double: %zd\n", sizeof(long double)));
	TRACE_CODE(printf("sizeof double: %zd\n", sizeof(double)));
	TRACE_CODE(printf("sizeof long long: %zd\n", sizeof(long long)));
	TRACE_CODE(printf("sizeof long int: %zd\n", sizeof(long int)));
	TRACE_CODE(printf("sizeof long %zd\n", sizeof(long)));
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT


BEGIN_UNIT_(read_bytes_as_int)
int main(int argc, char * argv[]){
	HORIZONTAL_LINE();
	TRACE_CODE(char mem[] = "1234567890ABCDEFG");
	HORIZONTAL_LINEs();
	ANNOTATE(read mem as unsigned short(unsigned int16));
	for(int i = 0; i < sizeof(mem) - sizeof(int); i++){
		printf("[%2d] %c %d Short(%hu) Int32(%u)\n", i, mem[i], mem[i], 
			((unsigned short)256)*mem[i+1]+mem[i],
			((unsigned int)256*256*256)*mem[i + 3] 
				+((unsigned int)256*256)*mem[i + 2]
				+((unsigned int)256)*mem[i + 1]
				+mem[i]
		);
	}
	HORIZONTAL_LINEs();
	ANNOTATE(read mem as unsigned short(unsigned int16));
	for(int i = 0; i < sizeof(mem) - sizeof(unsigned short); i++){
		printf("[%2d] %hu %#hx\n", i, *((unsigned short*)(mem+i)), *((unsigned short*)(mem+i)));
	}
	HORIZONTAL_LINEs();
	ANNOTATE(read mem as unsigned int(unsigned int32));
	for(int i = 0; i < sizeof(mem) - sizeof(unsigned int ); i++){
		printf("[%2d] %u %#x\n", i, *((unsigned int*)(mem + i)), *((unsigned int*)(mem + i)));
	}
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//read int


BEGIN_UNIT_(pod_type, plain old type)
/**
NAME
    Specifies that the type is POD (Plain Old Data) type. This means the type is compatible with the types used in the C programming language, that is, can be exchanged with C libraries directly, in its binary form.
    NOTE
        the standard doesn't define a named requirement with this name. This is a type category defined by the core language. It is included here as a named requirement only for consistency. 
DEPRECATED
   This type requirement is deprecated in the C++ standard. All of its uses have been replaced by the more refined type requirements, such as TrivialType
REQUIREMENTS
    The following types are collectively called POD types:
    - scalar types
    - POD classes
    - arrays of such types
    - cv-qualified versions of these types 
SEEALSO
    is_pod 
 */
int main(int argc, char* argv[]){
	MANUALb();
	return 0;
}
END_UNIT// pod_type

BEGIN_UNIT_(trivial_type, plain old type)
/**
NAME
    Specifies that a type is a trivial type.
    Note: the standard doesn't define a named requirement with this name. This is a type category defined by the core language. It is included here as a named requirement only for consistency.
REQUIREMENT
   The following types are collectively called trivial types:
    - scalar types
    - trivial class types
    - arrays of such types
    - cv-qualified versions of these types
SEEALSO
    is_trivial
 */
int main(int argc, char* argv[]){
	MANUALb();
	return 0;
}
END_UNIT// trivial_type


BEGIN_UNIT_(lab_trace_es)// virya::ioq ioq; CODE_FORMAT_Help __(CODE_FORMAT_, "++ %-25s");
inline Whistle& operator & (const char* s, Whistle &w){	std::cout << s;  return w;}
inline Whistle& operator & (Whistle &w, const char*s){	std::cout << s;  return w;}
inline Whistle& operator & (int n, Whistle &w){ std::cout << n;  return w; }

#define ECHO_() Whistle::INSTANCE(__FILE__, __LINE__, "&", "++ %s== ") & "\n";
/**
==========================================================
NAME
    lab_trace_es -- trace expressions in a sequence of lines
REFERENCE
    COMPILER_COMPLIANCE
==========================================================
EXPERIMANET 
==========================================================
Is it possible to use lambda? fails find an ideal way.
#define EMPTY(...) {}
#if  defined(__GNUC__)
#define CODE_BEGINg [&]{
#define CODE_ENDg }(); 
#define CODE_BEGINXg EMPTY(
#define CODE_ENDXg   )
#else
#define CODE_BEGINg(...) 
#define CODE_ENDg   
#define CODE_BEGINXg [&]{
#define CODE_ENDXg }(); 
#endif
==========================================================
*/
int main(int argc, char* argv[]){ TRY_MANUAL();
	HEAD1("Standard Predefined Macros")
		__FILE__             & ECHO_()
		__LINE__             & ECHO_()
		__DATE__             & ECHO_()
		__TIME__             & ECHO_()
		__STDC_HOSTED__      & ECHO_()
		__cplusplus          & ECHO_()
		#if	COMPILE_FORm
		_MSC_VER             & ECHO_()
		#endif
		TRACE_ES()
		#if	COMPILE_FORg
		__STDC__             & ECHO_() // == test COMPILE_FORg -- end
		//__STDC_VERSION__     & ECHO_()
		//__OBJC__             & ECHO_() // ONLY for gcc -- comment in source
		//__ASSEMBLER__        & ECHO_() // == test COMPILE_FORg -- end
		#endif
		TRACE_ES() // TODO: merge  and TRACE_ES to one macro
		CODE_FORg(
		__STDC__             & ECHO_() // == test CODE_FORg
		//__STDC_VERSION__     & ECHO_()
		//__OBJC__             & ECHO_()
		//__ASSEMBLER__        & ECHO_() // == test CODE_FORg -- end
		) TRACE_ES() // TODO: merge  and TRACE_ES to one macro
	return HORIZONTAL_LINE();
}
#undef ECHO_
END_UNIT// lab_trace_es


BEGIN_UNIT_(predefined_macros)// virya::ioq ioq; CODE_FORMAT_Help __(CODE_FORMAT_, "++ %-25s");
/**
 * enable __cplusplus: /Zc:__cplusplus https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
 */
inline Whistle& operator & (const char* s, Whistle &w){	std::cout << s;  return w;}
inline Whistle& operator & (Whistle &w, const char*s){	std::cout << s;  return w;}
inline Whistle& operator & (int n, Whistle &w){ std::cout << n;  return w; }

#define ECHO_() Whistle::INSTANCE(__FILE__, __LINE__, "&", "++ %s== ") & "\n";
int main(int argc, char* argv[]){
	HEAD1("Standard Predefined Macros")
		__FILE__             & ECHO_()
		__LINE__             & ECHO_()
		__DATE__             & ECHO_()
		__TIME__             & ECHO_()
		__STDC_HOSTED__      & ECHO_()
		__cplusplus          & ECHO_()
		#if	COMPILE_FORm
		_MSC_VER             & ECHO_()
        _MSVC_LANG           & ECHO_() // specified with such as /std:c++17
		#endif
		TRACE_ES()
		#if	COMPILE_FORg
		__STDC__             & ECHO_()
		//__STDC_VERSION__     & ECHO_() // only for gcc? doc say so, to check
		//__OBJC__             & ECHO_() // only for gcc? doc say so, to check
		//__ASSEMBLER__        & ECHO_() // only for gcc? doc say so, to check
		#endif
		TRACE_ES() // TOCONSIDER: merge TRACE_ES and the #if expression to one macro
	return HORIZONTAL_LINE();
}
END_UNIT// predefined_macros


BEGIN_UNIT_(vocabulary)
/**
rtnent     - return an entity
rtnwo      - an object which is     newed and is returned by a function(neWed object)
 rtnobj
rtnxe      - an object which is NOT newed and is returned by a function(eXpring entity)
 rtnxv     - xv: eXpring value
rvalue     - 
rreference - rvalue reference
rrefwo     - rreference which references an obj
rrefxe     - rreference which references an expring entity
rrefent    - rreference which references an entity|Is it possible?(Yes - see reference declarator)
relay e    - hold the e untill or after the holder is gone(e is entity)
bounce parameter - the function return its input parameter
                   - if the parameter is pure, it's not safe
*/
int main(int argc, char* argv[]){
	MANUALb();
	return 0;
}
END_UNIT// vocabulary
