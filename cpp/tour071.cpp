#include <cstring>
#include <initializer_list>
#include <vstring.h>
#include "vtestcommon.h"
#define TOUR_GROUP tour71_

inline Whistle& operator >>(bool a, Whistle& o){std::cout << std::boolalpha << a << std::endl; return o;}

#define macroprint_(s, x) printf("macro %s(%p) => %s(%p)\n", s,s, #x,#x)
#define macroprint(x) macroprint_(#x, x)
#define TEST_MACRO1 "TEST_MACRO1"   // value equals name
#define TEST_MACRO2 TEST_MACRO1     // 
#define TEST_MACRO3 TEST_MACRO2     // 

BEGIN_UNIT_(macro_value)
int main(int argc, char* argv[]){HORIZONTAL1();TRACE_SRC(-7,-3); HORIZONTAL3();

	macroprint(TEST_MACRO1);
	macroprint(TEST_MACRO2);
	macroprint(TEST_MACRO3);
	macroprint(NOT_DEFINED);

	macroprint(__LINE__);
	macroprint(__cplusplus);

	HORIZONTAL5();
	NOTICE  ("");	
	NOTICEf_("the addresses of token are same if it is not defined");
	NOTICEf_("  - therefore it is possible to known whether a token is defined without using #ifdef");
	SEEALSO(is_defined);
	return HORIZONTAL1();;
}
END_UNIT//macro_value

BEGIN_UNIT_(is_defined)
/**
PURPOSE 
    If a token is not defined, we can still use its string value. Therefore we can decide
    whether a token is defined.
USAGE
    - togother with `if contexpr`
    - show the macro, but not reference it
*/
#define isdefined_(s, x) (s != #x)
#define isdefined(x) isdefined_(#x, x)
int main(int argc, char* argv[]){MANUALb(); TRACE_SRC(-2,-1); HORIZONTAL3();
	isdefined(TEST_MACRO1)        >> ECHOn();
	isdefined(TEST_MACRO2)        >> ECHOn();
	isdefined(TEST_MACRO3)        >> ECHOn();
	isdefined(NOT_DEFINED)        >> ECHOn();
	isdefined(__LINE__)           >> ECHOn();
	isdefined(__cplusplus)        >> ECHOn();

	return HORIZONTAL1();
}
END_UNIT//is_defined

#undef macroprint_
#undef macroprint
#define macroprint_(s, x) printf("macro %s => %s\n", s, #x)
#define macroprint(x) macroprint_(#x, x)

BEGIN_UNIT_(combined_macro, concatenate two tokens to one)
/**
NAME
    illustrate how to create one token based other tokens
REASON
    we cannot define define, for example:
      - #define f(x,y) #define x##y (#x "--" #y) 
        then call f(a,b) to create token ab
      - #define f(x,y) x##y
        then call f(a,b) to create token ab
*/
#define JOIN_(X,Y) X##Y
#define JOIN(X,Y) JOIN_(X,Y)
#define VERSION XY123
#define PRODUCT JOIN(MyApplication_,VERSION)
int main(int argc, char* argv[]){TRY_MANUAL();TRACE_SRC(-4,-1); HORIZONTAL3();

	macroprint(PRODUCT);

	return HORIZONTAL1();
}
END_UNIT//combined_macro



BEGIN_UNIT_(define_define, Is there a way to do a #define inside of another #define?)

int main(int argc, char* argv[])
{
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/3314032/is-there-a-way-to-do-a-define-inside-of-another-define")
	HORIZONTAL_LINE();
	ANNOTATE(Impossible to define define)
	ANNOTATEs("#define MACROCREATER(B) MACRO##B B+B")
	ANNOTATE(MACROCREATER(5)) // This should create new macro (#define MACRO5 5+5)
	ANNOTATE(int a = MACRO5;)// this will use new macro
	HORIZONTAL_LINEs();
	ANNOTATE(Possible to define var)
	#define MACROCREATER(B) int MACRO##B = B+B;
	ANNOTATEs("#define MACROCREATER(B) int MACRO##B = B+B;")
	TRACE_CODE(MACROCREATER(5)) // This should create new macro (#define MACRO5 5+5)
	TRACE_CODE(int a = MACRO5;)// this will use new macro
	HORIZONTAL_LINEs();

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT // define_define


BEGIN_UNIT_(variable_name_suffix_macro )

int main(int argc, char* argv[])
{
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/1082192/how-to-generate-random-variable-names-in-c-using-macros");
	HORIZONTAL_LINE();
#define UNIQUE_NAME0(a, b) a##b
#define UNIQUE_NAME(a,b) UNIQUE_NAME0(a,b)
	int UNIQUE_NAME(testvar_, __COUNTER__) = 1;
	int UNIQUE_NAME(testvar_, __LINE__) = 1;
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT


BEGIN_UNIT_(macro_recursive)


void my_print(const char* a, const char* b, const char* c){
	printf("Count: 3 => [ %s %s %s]\n", a, b, c);
}

void my_print(const char* a, const char* b){
	printf("Count: 2 => [ %s %s ]\n", a, b);
}

void my_print(const char* a){
	printf("Count: 1 => [ %s ]\n", a);
}

void my_out(int a, int b, int c){
	printf("!Count: 3 => [ %d %d %d]\n", a, b, c);
}

void my_out(int a, int b){
	printf("!Count: 2 => [ %d %d ]\n", a, b);
}

void my_out(int a){
	printf("!Count: 1 => [ %d ]\n", a);
}

void my_out(){
	printf("!Count: 0\n");
}

int main(int argc, char* argv[])
{

	HORIZONTAL_LINE();

#define F1(a,b) printf("%s,%s\n", a, b)
#if defined(_WIN32) && ! defined(__clang__)
	HEAD("For msvc, cannot repass __VA_ARGS__ to macro func correctly!");
	TRACE_SRC(0, 7)
#define TREE2(X, ...) {printf("Args2:[%s]", #__VA_ARGS__);    X(__VA_ARGS__);}
#define TREE1(x,Y, ...) Y(__VA_ARGS__, virya::format("%d",x).c_str())
	for(int i = 1; i < 4; i++){
		for(int j = 7; j < 10; j++){
			TREE1(i, TREE2,"Missed =>", j, "<=Missed", my_print/*cannot input parameter here*/); 
		}
	}
#else
#define TREE2(X, ...) {printf("Args2:[%s]", #__VA_ARGS__);    X(__VA_ARGS__);}
#define TREE1(x,Y, ...) Y(__VA_ARGS__, virya::format("%d",x).c_str())

	TRACE_SRC(0,5)
	for(int i = 1; i < 4; i++){
		for(int j = 7; j < 10; j++){
			TREE1(i, TREE2,my_print, "PARAM_X1", "PARAM_X2"); 
		}
	}
#endif
	HORIZONTAL_LINE();
	auto echo =[](const char*s){std::cout<<'[' <<s << ']';};
	TRACE_SRC(0, 9)
#define SIMPLE1(X, Y, ...) {echo(#X);my_out(Y,## __VA_ARGS__);}
#define SIMPLE2(X, Y, ...) {echo(#X);SIMPLE1(Y, __VA_ARGS__);}
#define SIMPLE3(X, Y, ...) {echo(#X);SIMPLE2(Y, __VA_ARGS__);}
#define SIMPLE4(X, Y, ...) {echo(#X);SIMPLE3(Y, __VA_ARGS__);}
#define SIMPLE5(X, Y, ...) {echo(#X);SIMPLE4(Y, __VA_ARGS__);}
	SIMPLE2(1, 2, 3, 4, 5);
	SIMPLE3(1, 2, 3, 4, 5);
	SIMPLE4(1, 2, 3, 4, 5);
	SIMPLE5(1, 2, 3, 4, 5, 6);

#ifndef _WIN32 // works for gcc
	HORIZONTAL_LINEs()
	TRACE_SRC(0, 5)
#define SimepleB1(X, ...) {echo(#X);my_out( __VA_ARGS__);}
#define SimepleB2(X, ...) {echo(#X);SimepleB1(__VA_ARGS__);}
#define SimepleB3(X,  ...) {echo(#X);SimepleB2( __VA_ARGS__);}
#define SimepleB4(X,  ...) {echo(#X);SimepleB3( __VA_ARGS__);}
#define SimepleB5(X,  ...) {echo(#X);SimepleB4( __VA_ARGS__);}
	SimepleB2(1, 2, 3, 4, 5);
	SimepleB3(1, 2, 3, 4, 5);
	SimepleB4(1, 2, 3, 4, 5);
	SimepleB5(1, 2, 3, 4, 5);
#endif

	HORIZONTAL_LINE();
	HEAD("For windows, can repass __VA_ARGS__ to function correctly!");

	TRACE_SRC(0, 5)
	for(int i = 1; i < 4; i++){
		for(int j = 7; j < 10; j++){
			TREE1(i, my_print, virya::format("%d",j).c_str(), "Good for any one");
		}
	}
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT

#define PARENTHESIS_LEFT() (
#define PARENTHESIS_RIGHT() )
#define PARENTHESIS_L (  // equals PARENTHESIS_LEFT()
#define PARENTHESIS_R )  // equals PARENTHESIS_RIGHT()
#define PASS_ONE(...) __VA_ARGS__ 
#define CONCAT_P1(a, b) a ## b
#define CONCAT_P2(a, b) CONCAT_P1(a, b)

#define CONCAT(a,b) CONCAT1(a,b)
#define CONCAT1(a,b) CONCAT2(a,b)
#define CONCAT2(a,b) CONCAT3(a,b)
#define CONCAT3(a,b) CONCAT4(a,b)
#define CONCAT4(a,b) a##b


BEGIN_UNIT_(macro_count, count VA_ARGS, str_in)

#if defined(_WIN32) && ! defined(__clang__)
#define PASS_LIST(...) __VA_ARGS__
#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGUMENTS1(...) PASS_ONE(PASS_ONE(ELEVENTH_ARGUMENT)(dummy, __VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define ELEVENTH_ARGUMENT_re(x, ...) PASS_LIST(__VA_ARGS__,9,8,7,6,5,4,3,2,1,0) // 1. if x is there, the last comma(,) in(__VA_ARGS__) will be deleted
#define COUNT_ARGUMENTS2(...)    ELEVENTH_ARGUMENT PARENTHESIS_LEFT()ELEVENTH_ARGUMENT_re(dummy1,3, __VA_ARGS__) PARENTHESIS_RIGHT()// ^2. two dummies to esure the previous(__VA_ARGS__) is not empty
#define PRINT_COUNT_OF_ARGUMENTS(...) printf("%-40s has %d arguments\n", #__VA_ARGS__, COUNT_ARGUMENTS2(__VA_ARGS__));
#define DEBUG_VARIABLE_ARGUMENTS(FORMAT, ...) PASS_ONE(CONCAT(DEBUG_, PASS_ONE(COUNT_ARGUMENTS2(__VA_ARGS__))))(FORMAT, ##__VA_ARGS__)
#define COUNT_ARGUMENTS COUNT_ARGUMENTS2
#else
#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGUMENTS(...) ELEVENTH_ARGUMENT(dummy, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define PRINT_COUNT_OF_ARGUMENTS(...) printf("%-40s has %d arguments\n", #__VA_ARGS__, COUNT_ARGUMENTS(__VA_ARGS__));
#define DEBUG_VARIABLE_ARGUMENTS(FORMAT, ...) CONCAT(DEBUG_, COUNT_ARGUMENTS(__VA_ARGS__))(FORMAT, ##__VA_ARGS__)
#define COUNT_ARGUMENTS1 COUNT_ARGUMENTS
#define COUNT_ARGUMENTS2 COUNT_ARGUMENTS
#endif 

#define METHOD 1 // for windows and linux
#ifndef METHOD 
	#if defined(_WIN32) && ! defined(__clang__)
	#define METHOD 1 // for windows
	#else
	#define METHOD 2 // for linux
	#endif
#endif
#if  METHOD == 1 // method 1
//#define str_in(s, ...)  PASS_ONE(CONCAT(str_in,)COUNT_ARGUMENTS1(__VA_ARGS__)) (s, __VA_ARGS__)
#define str_in(s, ...)  CONCAT(str_in, COUNT_ARGUMENTS2(__VA_ARGS__))(s, ##__VA_ARGS__)
#elif METHOD == 2 // method 2
#define str_in(s, ...)  CONCAT(str_in, COUNT_ARGUMENTS2(__VA_ARGS__))(s, ##__VA_ARGS__)
#else  // method 3
#define str_in(s, ...)  PASS_ONE(CONCAT_P1 PARENTHESIS_L str_in, COUNT_ARGUMENTS(__VA_ARGS__) PARENTHESIS_R ) (s, __VA_ARGS__)
#endif

#define str_in0(s)                      false
#define str_in1(s,s1)                   strcmp(s,s1) == 0
#define str_in2(s,s1,s2)                strcmp(s,s2) == 0 || str_in1(s,s1)
#define str_in3(s,s1,s2,s3)             strcmp(s,s3) == 0 || str_in2(s,s1,s2)   
#define str_in4(s,s1,s2,s3,s4)          strcmp(s,s4) == 0 || str_in3(s,s1,s2,s3)
#define str_in5(s,s1,s2,s3,s4,s5)          strcmp(s,s5) == 0 || str_in4(s,s1,s2,s3,s4)
#define str_in6(s,s1,s2,s3,s4,s5,s6)          strcmp(s,s6) == 0 || str_in5(s,s1,s2,s3,s4,s5)
#define str_in7(s,s1,s2,s3,s4,s5,s6,s7)          strcmp(s,s7) == 0 || str_in6(s,s1,s2,s3,s4,s5,s6)
#define str_in8(s,s1,s2,s3,s4,s5,s6,s7,s8)          strcmp(s,s8) == 0 || str_in7(s,s1,s2,s3,s4,s5,s6,s7)
#define str_in9(s,s1,s2,s3,s4,s5,s6,s7,s8,s9)          strcmp(s,s9) == 0 || str_in8(s,s1,s2,s3,s4,s5,s6,s7,s8)
#define str_in10(s,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10)          strcmp(s,s10) == 0 || str_in9(s,s1,s2,s3,s4,s5,s6,s7,s8,s9)
#define str_in11(s,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11)          strcmp(s,s11) == 0 || str_in10(s,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10)

#define DEBUG_0(FORMAT)                   printf(FORMAT)
#define DEBUG_1(FORMAT, ARG1)             printf(FORMAT, ARG1)
#define DEBUG_2(FORMAT, ARG1, ARG2)       printf(FORMAT, ARG1, ARG2)
#define DEBUG_3(FORMAT, ARG1, ARG2, ARG3) printf(FORMAT, ARG1, ARG2, ARG3)

int test_() {
	HORIZONTAL_LINE();
	REFERENCE("https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/preprocessor/macros/__VA_ARGS__/count-arguments");
	NOTICE("For windows, won't run properly!");
	HEAD("Count __VA_ARGS__");
	int i = COUNT_ARGUMENTS();
	printf("              has %d arguments\n", COUNT_ARGUMENTS());
	printf("one           has %d arguments\n", COUNT_ARGUMENTS(one));
	printf("          1-5 has %d arguments\n", COUNT_ARGUMENTS(1, 2, 3, 4, 5));
	printf("          1-9 has %d arguments\n", COUNT_ARGUMENTS(1, 2, 3, 4, 5, 6, 7, 8, 9));
	printf("          1-10has %d arguments\n", COUNT_ARGUMENTS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
	printf("          1-11has %d arguments\n", COUNT_ARGUMENTS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11));
	printf("foo, bar, baz has %d arguments\n", COUNT_ARGUMENTS(foo, bar, baz));
	printf("\"xyz\",\"abcde\" has %d arguments\n", COUNT_ARGUMENTS("xyz", "abcde"));


	HEAD("PRINT_COUNT_OF_ARGUMENTS");
	//PRINT_COUNT_OF_ARGUMENTS();
	PRINT_COUNT_OF_ARGUMENTS(1, 2, 3, 4);
	PRINT_COUNT_OF_ARGUMENTS("foo", "bar", "baz");
	PRINT_COUNT_OF_ARGUMENTS(x, y, z, "tq84", hello, world, 'etc');

#ifndef _WIN32
	HEAD("DEBUG_VARIABLE_ARGUMENTS");
	DEBUG_VARIABLE_ARGUMENTS("hello, world\n");
	DEBUG_VARIABLE_ARGUMENTS("The number is: %d\n", 42);
	DEBUG_VARIABLE_ARGUMENTS("%d %s\n", 99, "Bottles");
	DEBUG_VARIABLE_ARGUMENTS("%s - %s - %s\n", "foo", "bar", "baz");
#else
	//HEAD("DEBUG_VARIABLE_ARGUMENTS");
	//DEBUG_VARIABLE_ARGUMENTS("hello, world\n");
	//DEBUG_VARIABLE_ARGUMENTS("The number is: %d\n", 42);
	//DEBUG_VARIABLE_ARGUMENTS("%d %s\n", 99, "Bottles");
	//DEBUG_VARIABLE_ARGUMENTS("%s - %s - %s\n", "foo", "bar", "baz");
#endif
	HEAD("str in");
	//const char*  s = "3";
	TRACE_CODEv(str_in("1"));
	TRACE_CODEv(str_in("1", "1"));
	TRACE_CODEv(str_in("2", "1", "2"));
	TRACE_CODEv(str_in("3", "1", "2", "3"));
	TRACE_CODEv(str_in("4", "1", "2", "3", "4"));
	TRACE_CODEv(str_in("5", "1", "2", "3", "4", "5"));
	TRACE_CODEv(str_in("6", "1", "2", "3", "4", "5", "6"));
	TRACE_CODEv(str_in("7", "1", "2", "3", "4", "5", "6", "7"));
	TRACE_CODEv(str_in("8", "1", "2", "3", "4", "5", "6", "7", "8"));
	TRACE_CODEv(str_in("9", "1", "2", "3", "4", "5", "6", "7", "8", "9"));
	EXPLAIN  (str_in("10","1", "2", "3", "4", "5", "6", "7", "8", "9","10") OUT OF RANGE);
	EXPLAIN  (str_in("11","1", "2", "3", "4", "5", "6", "7", "8", "9","10","11") OUT OF RANGE);


	HORIZONTAL_LINE();

	return 0;
}

#ifdef _WIN32
//#define __MR_11TH_re(x, ...) __MA_PASS(__VA_ARGS__,9,8,7,6,5,4,3,2,1,0)                        //  1. if x is there, the last comma(,) in(__VA_ARGS__) will be deleted
//#define __MR_VACOUNT(...)    __MR_11TH __MR_LEFT __MR_11TH_re(dummy1,dummy2, __VA_ARGS__) __MR_RIGHT// ^2. two dummies to esure the previous(__VA_ARGS__) is not empty
#define __MR_VACOUNT1(...)  __MR_11TH(dummy, __VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define __MR_VACOUNT2(...)  __MR_11TH(dummy, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

//      __MR_VACOUNT0
#else
#define __MR_VACOUNT1 __MR_VACOUNT
#define __MR_VACOUNT2 __MR_VACOUNT
#endif

int test_for_muranbase() {
	HEAD("Count __VA_ARGS__");
	int i = __MR_VACOUNT();
	printf("[mthd]  EMPTY has %d arguments\n", __MR_VACOUNT());
	printf("[mthd1] EMPTY has %d arguments\n", __MR_VACOUNT1());
	printf("[mthd2] EMPTY has %d arguments\n", __MR_VACOUNT2());
	printf("one           has %d arguments\n", __MR_VACOUNT(one));
	printf("          1-5 has %d arguments\n", __MR_VACOUNT(1, 2, 3, 4, a));
	printf("          1-9 has %d arguments\n", __MR_VACOUNT(1, 2, 3, 4, a, b, c, d, e));//9
	printf("          1-10has %d arguments\n", __MR_VACOUNT(1, 2, 3, 4, a, b, c, d, e, 'f'));
	printf("[mthd]    1-11has %d arguments\n", __MR_VACOUNT(1, 2, 3, 4, a, b, c, d, e, 'f', 'g'));
	printf("[mthd1]   1-11has %d arguments\n", __MR_VACOUNT1(1, 2, 3, 4, a, b, c, d, e, 'f', 'g'));
	printf("[mthd2]   1-11has %d arguments\n", __MR_VACOUNT2(1, 2, 3, 4, a, b, c, d, e, 'f', 'g'));
	printf("foo, bar, baz has %d arguments\n", __MR_VACOUNT(foo, bar, baz));
	printf("\"xyz\",\"abcde\" has %d arguments\n", __MR_VACOUNT("xyz", "abcde"));
	HORIZONTAL_LINE();
	return 0;
}
int main(int argc, char* argv[]){
	for(int i = 1; i< argc; i++){ if(strcmp(argv[i], "--using-muranbase") == 0) return test_for_muranbase(); }
	return test_();
}
END_UNIT


#ifdef HAVING_BOOST
#include <boost/preprocessor/variadic/size.hpp>
BEGIN_UNIT_(variadic_size__boost)
int main(int argc, char* argv[]){
	HEAD("COUNT __VA_ARGV__, using boost lib");
	TRACE_CODEv(BOOST_PP_VARIADIC_SIZE());
	TRACE_CODEv(BOOST_PP_VARIADIC_SIZE(0));
	TRACE_CODEv(BOOST_PP_VARIADIC_SIZE(1));
	TRACE_CODEv(BOOST_PP_VARIADIC_SIZE("1", "2", "3", "4", "5"));
	HORIZONTAL_LINE();
	NOTICE(if VA_ARGS is empty, the size is also bad, both for Windows and Linux)
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT
#endif

#if __GNUC__ && (! (__GNUC__ == 7 && __GNUC_MINOR__ == 3))
BEGIN_UNIT_(macro_foreach)
#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define ENUM_CASE(name) case name: return #name;
#define MAKE_ENUM(type, ...)                    \
enum type {                                     \
  __VA_ARGS__                                   \
};                                              \
constexpr const char *                          \
to_cstring(type _e)                             \
{                                               \
  switch (_e) {                                 \
  FOR_EACH(ENUM_CASE, __VA_ARGS__)              \
  default:                                      \
    return "unknown";                           \
  }                                             \
}

MAKE_ENUM(TEST, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE);

int main(int argc, char* argv[]) {
	HORIZONTAL_LINE();
	REFERENCE("https://www.scs.stanford.edu/~dm/blog/va-opt.html");
	NOTICE("For windows, won't run properly!");
	HEAD("FOR_EACH C++20");
	HEAD("Define Enum");
	TRACE_SRC(-8,-8);
		
	auto X = [](bool x){return x;};
	if(FOR_EACH(X, true)){
		
	}
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT
#endif



BEGIN_UNIT_(macro_concatenate)
//As mentioned in the other answer, you can write your own OVERLOAD macro. BOOST_PP_OVERLOAD consists of two parts, BOOST_PP_CAT and BOOST_PP_VARIADIC_SIZE. However, unlike Boost, you only care about 2 args. So:

#define OVERLOAD(prefix, ...) CAT(prefix, VARIADIC(__VA_ARGS__))

//CAT will look like:

#define CAT(a, b) KITTY((a, b))
#define KITTY(par) MEOW ## par
#define MEOW(a, b) a ## b

//And VARIADIC:

#define VARIADIC(...) _VARIADIC_(__VA_ARGS__, 2, 1,)
#define _VARIADIC_(e0, e1, size, ...) size
int main(int argc, char* argv[]){
	REFERENCE("https://stackoverflow.com/questions/48045470")
	return 0;
}

END_UNIT//macro_concatenate

BEGIN_UNIT_(macro_pass)

int main(int argc, char* argv[]){
#define CONTENT(X)    #X

	HEAD("PASS_ONE");
	TRACE_CODEv(         CONTENT(A));
	TRACE_CODEv(PASS_ONE(CONTENT(A)));

	TRACE_CODEv(                  CONTENT(CONCAT_P1(A,B)));
	TRACE_CODEv(         PASS_ONE(CONTENT(CONCAT_P1(A,B))));
	TRACE_CODEv(         PASS_ONE(CONTENT(CONCAT_P1(A,)B)));
	TRACE_CODEv(        PASS_ONE(CONTENT)(CONCAT_P1(A,B)));
	TRACE_CODEv(PASS_ONE(PASS_ONE(CONTENT(CONCAT_P1(A,B)))));
	TRACE_CODEv(PASS_ONE(PASS_ONE(CONTENT)(CONCAT_P1(A,B))));
	TRACE_CODEv(PASS_ONE(PASS_ONE(CONTENT))(CONCAT_P1(A,B)));

	TRACE_CODEv(                  CONTENT(CONCAT_P2(A,B)));
	TRACE_CODEv(         PASS_ONE(CONTENT(CONCAT_P2(A,B))));
	TRACE_CODEv(        PASS_ONE(CONTENT)(CONCAT_P2(A,B)));

	TRACE_CODEv(PASS_ONE(CONTENT PARENTHESIS_L CONCAT_P1(A, B) PARENTHESIS_R));
	TRACE_CODEv(PASS_ONE(CONTENT PARENTHESIS_LEFT() CONCAT_P1(A,B) PARENTHESIS_RIGHT() ));

	HORIZONTAL_LINE();
	EXPLAINs("SUMMARY");
	EXPLAINs("  1. PASS_ONE functions like eval in bash                  ");
	EXPLAINs("  2. use PASS_ONE with PARENTHESIS to delay some part-parse");
	HORIZONTAL_LINE();
	
#undef  CONTENT
	return 0;
}

END_UNIT// macro_pass


BEGIN_UNIT_(print_va_args, token adaptive to cstr, token is literal)
/**
QUESTION
    how to use tokens as string
       - print("abc")       => abc
       - print(abc)         => abc
       - print(abc "def")   => abc "def"
SOLUTION
	1. using macro
       - is the tokeing lead with \"    
    2. use constexpr
    3. use __VA_ARGS__ and with an function which trim '\"'
REFERENCE
    https://stackoverflow.com/questions/11623899/can-the-c-preprocessor-tell-whether-a-token-is-a-string
    https://stackoverflow.com/questions/5819217/verify-type-of-string-e-g-literal-array-pointer-passed-to-a-function
    https://stackoverflow.com/questions/7613528/restrict-passed-parameter-to-a-string-literal
*/
//TAG:PLAIN_TOKEN #define heading(...) { if(__MR_VACOUNT(__VA_ARGS__) == 1 && str_lead_with(typeid(decltype(__VA_ARGS__)).name(), "char const [")) muranbase::left_stdout(__VA__ARGS__, 4, 140, '='); \
//					   else muranbase::left_stdout(#__VA_ARGS__, 40, 140,'='); }
inline bool str_begin_with(const char*s1, const char c){ return s1[0] == c; }
inline bool str_end_with(const char*s1, const char c){ return strlen(s1) > 0 ? s1[strlen(s1)-1] == c : false; }
inline bool str_enclosed(const char*s1, const char c){ return str_begin_with(s1, c) && str_end_with(s1,c); }
#define heading(...) { TRACE_E_(); if (__MR_VACOUNT(__VA_ARGS__) == 1){                          \
						if( str_enclosed(#__VA_ARGS__, '\"'))             \
							 virya::left_stdout(virya::TrimCStr(#__VA_ARGS__, "\"").c_str(), 4, 30, '*');       \
						else virya::left_stdout(#__VA_ARGS__, 4, 30,'*');      \
					   }else virya::left_stdout(#__VA_ARGS__, 4, 30,'*'); }
int main(int argc, char* argv[]){TRY_MANUAL(); HEAD1(defintion); TRACE_SRC(-5,-1); HORIZONTAL_LINE()
	heading("hello")
	heading(hello)
	heading(hello world)
	heading("hello" world)
	heading("hello", world)
	heading("hello",   world)
	return HORIZONTAL_LINE();
}

END_UNIT//print_va_args


#if ! _MSC_VER >= 1920
BEGIN_UNIT_(constexpr_string_concatenate, is_literal_type, compile-time string concatenation)

/**
PURPOSE
    concatenate strings at compile time
REFERENCE
    https://www.daniweb.com/programming/software-development/code/482276
*/

class literal_str_list {
private:
  
  const char* const text_ptr;
  unsigned int text_size;
  const literal_str_list* const head;
  
  constexpr char get_char_from_head(unsigned int i, unsigned int hd_size) const {
    return (i < hd_size ? (*head)[i] : (i < (hd_size + text_size) ? text_ptr[i - hd_size] : '\0'));
  };
  
  static constexpr std::size_t fnv_prime  = (sizeof(std::size_t) == 8 ? 1099511628211u : 16777619u);
  static constexpr std::size_t fnv_offset = (sizeof(std::size_t) == 8 ? 14695981039346656037u : 2166136261u);
  
  constexpr std::size_t fnv_1a_hash(unsigned int i) const {
    return (i == 0 ? 
      (head != nullptr ? 
        ((head->fnv_1a_hash(head->text_size-1) ^ text_ptr[0]) * fnv_prime) :
        fnv_offset) :
      ((fnv_1a_hash(i-1) ^ text_ptr[i]) * fnv_prime));
  };
  
  template <typename FwdIter>
  void copy_to_recurse(FwdIter& beg, FwdIter end) const {
    if( head != nullptr )
      head->copy_to_recurse(beg, end);
    for(unsigned int i = 0; (i < text_size) && (beg != end); ++i, ++beg)
      *beg = text_ptr[i];
  };
  
  void copy_to_recurse(char*& beg, char* end) const {
    if( head != nullptr )
      head->copy_to_recurse(beg, end);
    std::size_t sz_to_cpy = (end - beg < text_size ? end - beg : text_size);
    std::memcpy(beg, text_ptr, sz_to_cpy);
    beg += sz_to_cpy;
  };
  
  constexpr literal_str_list(const char* aStr, unsigned int N,
                             const literal_str_list* aHead = nullptr) : 
                             text_ptr(aStr), text_size(N), head(aHead) { };
  
public:
  
  template <unsigned int N>
  constexpr literal_str_list(const char(&aStr)[N],
                             const literal_str_list* aHead = nullptr) : 
                             text_ptr(aStr), text_size(N-1), head(aHead) {
    static_assert(N >= 1, "Invalid string literal! Length is zero!");
  };
  
  constexpr unsigned int size() const {
    return text_size + (head != nullptr ? head->size() : 0);
  };
  
  constexpr char operator[](unsigned int i) const {
    return (head != nullptr ? 
      get_char_from_head(i, head->size()) :
      (i < text_size ? text_ptr[i] : '\0'));
  };
  
  template <unsigned int N>
  constexpr literal_str_list operator+(const char(&aHead)[N]) const {
    return literal_str_list(aHead, this);
  };
  
  constexpr literal_str_list operator+(const literal_str_list& aHead) const {
    return literal_str_list(aHead.text_ptr, aHead.text_size, this);
  };
  
  constexpr std::size_t hash() const {
    return fnv_1a_hash(text_size-1);
  };
  
  template <typename FwdIter>
  void copy_to(FwdIter beg, FwdIter end) const {
    copy_to_recurse(beg, end);
  };
  
  void copy_to(char* beg, char* end) const {
    copy_to_recurse(beg, end);
  };

};

std::string convert_to_string(const literal_str_list& lit) {
  std::string result(lit.size(), ' ');
  lit.copy_to(result.begin(), result.end());
  return result;
};

inline Whistle& operator << (Whistle &w, const literal_str_list& lit) { std::cout << convert_to_string(lit); return w;} 
inline Whistle& operator << (Whistle &w, const char* s)               { std::cout << s;                      return w; }
inline Whistle& operator << (Whistle &w, const char s)                { std::cout << s;                      return w; }
inline Whistle& operator << (Whistle &w, const size_t s)              { std::cout << std::hex << s;          return w; }

#define ECHOv(v) Whistle::INSTANCE(__FILE__, __LINE__, ";", "++ %s => ") << v << "\n" 
#define ECHO_()  Whistle::INSTANCE(__FILE__, __LINE__, ";", "++ %s => ") 

int main(int argc, char* argv[]) {TRY_MANUAL()

    HEAD1(Note, the following are all compile-time constants:)
	constexpr literal_str_list hello = "Hello "            ; ECHOv(hello) ;
	constexpr literal_str_list world = "World!"            ; ECHOv(world) ;
#if COMPILE_FORm
	constexpr literal_str_list lit1 = hello + "World!"     ; ECHOv(lit1) ;
	constexpr literal_str_list lit2 = hello + world        ; ECHOv(lit2) ;
	constexpr char c1 = lit1[6]                            ; ECHO_() << "Senventh character is '" << c1 << "'." << "\n";
	constexpr std::size_t h1 = lit1.hash()                 ; ECHO_() << "Hash value         is '" << h1 << "'." << "\n";
#endif
	TRACE_ES()

    std::is_literal_type<literal_str_list>::value          & ECHO_K("The class is as a literal type!\n", "The class is NOT considered as a literal type!\n");
	
	return HORIZONTAL_LINE();
}

#undef ECHO_
END_UNIT//  constexpr_string_concatenate
#endif

BEGIN_UNIT_(macro_with_constexpr, macro with strcmp)

inline Whistle& operator >> (const char* s, Whistle &w)               { std::cout << s;                      return w; }
inline Whistle& operator >> (int         s, Whistle &w)               { std::cout << s;                      return w; }
inline Whistle& operator << (Whistle &w, const char* s)               { std::cout << s;                      return w; }

#define ECHO_()  Whistle::INSTANCE(__FILE__, __LINE__, ">>", "@@ %s => ") 

// compares two strings in compile time constant fashion
constexpr int c_strcmp( char const* lhs, char const* rhs )
{
    return (('\0' == lhs[0]) && ('\0' == rhs[0])) ? 0
        :  (lhs[0] != rhs[0]) ? (lhs[0] - rhs[0])
        : c_strcmp( lhs+1, rhs+1 );
}
// some compilers may require ((int)lhs[0] - (int)rhs[0])

void usage1(){HEAD1(macro with constexpr -- but not work); TRACE_SRC(2,14); 
#if COMPILE_NOTa
	#define JACK "jack"
	#define QUEEN "queen"

	#define USER "QUEEN"      // or QUEEN, your choice

	constexpr int x = c_strcmp( USER, JACK );
	#if constexpr(0 == c_strcmp( USER, JACK ))
	#define USER_VS QUEEN
	#elif 0 == c_strcmp( USER, QUEEN )
	#define USER_VS JACK
	#else
	#define USER_VS "unknown"
	#endif
	TRACE_SRC(-16,-2)}
	USER                 >> ECHO_() << "\n";
	USER_VS              >> ECHO_() << "\n";
	USER_JACK            >> ECHO_() << "\n";
	USER_QUEEN           >> ECHO_() << "\n";
#endif
#ifdef USER
	#undef USER
	#undef USER_VS
	#undef JACK
	#undef QUEEN
#endif
}

void usage2(){ HEAD1(in macro, compare char, such as 's' == 'j' -- works); TRACE_SRC(2,18)
#if COMPILE_FORa
#define QUEEN 'Q'
#define JACK 'J'

#define CHECK_QUEEN(s) (s==QUEEN)
#define CHECK_JACK(s) (s==JACK)

#define USER 'Q'

#if CHECK_QUEEN(USER)
	auto func = [](){printf("4 queen");};
	#define USER_VS "vs is queen"
#elif CHECK_JACK(USER)
	auto func = [](){printf("4 jack");};
	#define USER_VS "vs is jack"
#elif
     #error "unknown user"
#endif
	USER                 >> ECHO_() << "\n";
	USER_VS              >> ECHO_() << "\n";
	JACK                 >> ECHO_() << "\n";
	QUEEN                >> ECHO_() << "\n";
#undef USER
#undef USER_VS
#undef JACK
#undef QUEEN
#endif
	TRACE_ES() // only a test for TRACE_ES
}

void usage3(){ HEAD1(macro with strcmp -- only for gcc); 
#if COMPILE_FORg
	#define USER "jack"
	#define USER_JACK strcmp(USER, "jack")
	#define USER_QUEEN strcmp(USER, "queen")
	#if $USER_JACK == 0
	#define USER_VS USER_QUEEN
	#elif USER_QUEEN == 0
	#define USER_VS USER_JACK
	#endif
	TRACE_PRV(8)
	USER                 >> ECHO_() << "\n";
	USER_VS              >> ECHO_() << "\n";
	USER_JACK            >> ECHO_() << "\n";
	USER_QUEEN           >> ECHO_() << "\n";
#endif
	TRACE_ES()
}

int main(int argc, char* argv[]){
	usage1();
	usage2();
	usage3();
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/2335888/how-to-compare-strings-in-c-conditional-preprocessor-directives")
	return HORIZONTAL_LINE();
}
END_UNIT //macro_with_constexpr


BEGIN_UNIT_(parse_cmd, simple to parse command line using macro)


#define PARSEGET_str(a, pattern)\
else if(strcmp(argv[i], pattern) == 0){\
		   if(i < argc - 1){\
				i++;\
				a=argv[i];\
			}else{\
				printf("missig argument to `--project'");\
				return 1;\
			}\
    }

#define PARSECMD(...) \
for(int i = 1; i < argc; i++){\
	if(false){}\
	__VA_ARGS__\
	else{\
			printf("Invalid argument - `%s`\n", argv[i]);\
			return 1;\
	}\
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	TRACE_SRC(1,6);
	std::string id;
	std::string name;
	PARSECMD(
		PARSEGET_str(name, "--name")
		PARSEGET_str(id, "--id")
	);
	HORIZONTAL_LINE();
	TRACE_CODEv(name);
	TRACE_CODEv(id);
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT// parse_cmd

BEGIN_UNIT_(test_man)
/**
NAME
    test_man - test manual
SYNOPSIS
	test_man  <= PRINT ALL
	test_man [SECTION...]
OPTION
	OPTION1
	OPTION2
NOTICE
	notice document
*/
int main(int argc, char* argv[]){
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			MANUALs(argv[i]);
		}
		return 0;
	}
	HEAD1("Whole document");
	MANUAL();

	HEAD1("Name part of document");
	MANUAL(NAME);

	HEAD1("NOTICE");
	MANUAL(NOTICE);

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//test_man

BEGIN_UNIT_(test_man2)// Different than test_man: only the manual is compact
/****   NAME
    test_man - test manual
SYNOPSIS
	test_man  <= PRINT ALL
	test_man [SECTION...]
OPTION
	OPTION1
	OPTION2
NOTICE
	notice document ***/
int main(int argc, char* argv[]){
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			HEAD1(argv[i]);
			MANUALs(argv[i]);
			HORIZONTAL_LINE();
		}
		return 0;
	}
	HEAD1("Whole document");
	MANUAL();

	HEAD1("Name part of document");
	MANUAL(NAME);

	HEAD1("NOTICE");
	MANUAL(NOTICE);

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//test_man2





