#include <array>
#include <algorithm>
#include "vtestcommon.h"
#define TOUR_GROUP tour170_

BEGIN_UNIT_(cpp17_new_features)
/**
New language features
  - u8 character literal
  - made noexcept part of type system
  - new order of evaluation rules
  - lambda capture of *this
  - constexpr
    - compile-time if constexpr
    - constexpr lambda
  - variables
    - inline variables
    - structured binding
    - initializers for if and switch
    - guaranteed copy elison
    - temporary materialization
  - templates
    - fold-expressions -- (...)
    - class template argument deduction -- tuple t(4, 3, 3.5)
    - non-type template parameter declared with auto
  - namespaces
    - simplified nested namespaces
    - using-delcaration declaring multiple names
    - atribute namespace don't have to repeat
  - new attributes 
    - fallthrough
    - maybe_unused
    - nodiscard
  - __has_include 
New Headers
  - <any>
  - <charconv>
  - <execution>
  - <filesystem>
  - <memory_resource>
  - <optional>
  - <string_view>
  - <variant> 
New library features
  Utility types
  - std::tuple
    - std::appy
    - std::make_from_tuple(different than std::make_tuple)
    - deduction guides
  - std::any
  - std::optional
  - std::variant
  - searchers
  - std::as_const
  - std::not_fn
*/

int main(int argc, char* argv[]){
	MANUALb();
	return 0;
}
END_UNIT


BEGIN_UNIT_(fold_expression, parameter_pack_expansion)
	
using namespace std;

void unary_demos();

template<typename T>
int func(T t){ std::cout << "[" << t << "]"; return 0;}

template<class... T>
void dummy(T... t){}

template<typename ...Args>
void printer1(Args&&... args){
	dummy(func(forward<Args>(args))...);	cout << "\n";
}

template<typename ...Args>
void printer2(Args&&... args){
	(func(forward<Args>(args)), ...);
	cout << "\n";
}

template<typename ...Args>
void printer3(Args&&... args){
	(cout << ... << args) << "\n"; 
}

template<typename ...Args>
void print_sum(Args&&... args){
	cout << (0 + ... + args) << "\n"; 
}

void forward_demo(){
	HEAD1("Expand args one by one");
	BANNER(Pre CPP17);TRACE_SRC(-30,-20);TRACE_NXT();	
	printer1(100,200,300,400);
	BANNER(CPP17);    TRACE_SRC(-20,-16);TRACE_NXT();
	printer2(100,200,300,400);
}

void binary_demo(){
	HEAD1("Binary Demo - 1");TRACE_SRC(-19, -16);TRACE_NXT();	
	printer3("800","2xx",300,400,'5');

	HEAD1("Binary Demo - 2");TRACE_SRC(-17, -14);TRACE_NXT();	
	print_sum(100,200,300,400,5);
}

class C {
private:
	static int COUNT;
	const int seq;
	const int id;
	string content;
public:
	C(int i):seq(++COUNT), id(i), content(to_string(i)){}
	C& operator + (C&o){ content += "~"; content+= o.content;                 return *this;}
	C& operator | (C&o){ content = o.content +"~"+ content;                   return *this;}
	C& operator * (C&o){ o.content = (o.content + "~" + to_string(id));       return o;}
	friend ostream& operator<<(ostream&, const C&);
};
int C::COUNT = 0;

ostream& operator<<(ostream& os, const C& x){
    //os << "id:" << x.id << " seq:" << x.seq << " value:" << x.content;
	os << "id:" << x.id << " value:" << x.content;
    return os;
}

template<typename ...Args>
void test1(Args&&... args){	cout<<(...|args)<<endl; }
template<typename ...Args>
void test2(Args&&... args){	cout<<(args|...)<<endl; }
template<typename ...Args>
void test3(Args&&... args){	cout<<(...*args)<<endl; }
template<typename ...Args>
void test4(Args&&... args){	cout<<(args*...)<<endl; }

void unary_demo(){
	HEAD1("Unary demo");TRACE_SRC(-10, -3);TRACE_NXT(4);	
	test1(C{7}, C{8}, C{9});
	test2(C{7}, C{8}, C{9});
	test3(C{7}, C{8}, C{9});
	test4(C{7}, C{8}, C{9});
}

int main(int argc, char* argv[]){
	forward_demo();
	
	binary_demo();
	
	unary_demo();
	
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT// fold_expression

BEGIN_UNIT_(none_type_template_parameter_with_auto) using namespace std;

/**
REFERENCE https://stackoverflow.com/questions/38026884
*/

namespace n1{
template<class Type, Type value> constexpr Type constant = value;
constexpr auto var = constant<int,4>;
}
namespace n2{
template<auto value> constexpr auto constant = value;
constexpr auto var = constant<4>;
}
namespace n1{
template<class...T>      struct HeterogeneousList{};            using l1 = HeterogeneousList<integral_constant<int, 1>, integral_constant<bool, true>>;
template<class T, T...t> struct HomogeneousList{};              using l2 = HomogeneousList<int, 1, 2, 3>;
}
namespace n2{
template<auto...T>                struct HeterogeneousList{};   using l1 = HeterogeneousList<1, true>;
template<auto v, decltype(v)...t> struct HomogeneousList{};     using l2 = HomogeneousList<1, 2, 3>;
}

int main(int argc, char* argv[]){
	HEAD(basic)
		HEAD3(implement before cpp17); TRACE_SRC(-18,-17);
		HEAD3(implement since cpp17);  TRACE_SRC(-15,-14);
	HEAD(with variadic template parameters)
		HEAD3(implement before cpp17); TRACE_SRC(-13,-12);
		HEAD3(implement since cpp17);  TRACE_SRC(-10,-9);
	return HORIZONTAL1();
}

END_UNIT// none_type_template_parameter_with_auto


BEGIN_UNIT_(structured_binding)
using namespace std;

int main(int argc, char* argv[]){
	HEAD1("SYNOPSIS");
	BANNER("Case1: Binding an array");
	BANNER("Case2: Binding a tulpe like type");
	BANNER("Case3: Binding to data members");
	HEAD1("Basic"); TRACE_NXT(2);
	auto v = make_pair<int,int>(5,500);
	auto [first,second] = v; // =v; (v); {v} 
	TRACE_CODEv(first++);
	TRACE_CODEv(second++);
	TRACE_CODEv(v.first);
	TRACE_CODEv(v.second);
	
	HEAD2("Using Reference"); TRACE_NXT(1);
	auto& [a1,a2](v);
	TRACE_CODEv(++a1);
	TRACE_CODEv(++a2);
	TRACE_CODEv(v.first);
	TRACE_CODEv(v.second);

	HORIZONTAL_LINE();
	return 0;
}
	
END_UNIT


BEGIN_UNIT_(if_constexpr)
/**
NAME
    if_constexpr
NOTICE
    1. in the branch not instantialized, unknown name is still NOT allowed; for example,
       for block of `if constexpr(ismsvc)`, the _MS_VER is not valid when compile by gcc.
    2. but unknown member of the object is allowed
       for block of `T a; a.method();`, method can be invalid. 
*/
using namespace std;
inline Whistle& operator >> (int n, Whistle &w){ std::cout << n;  return w; }
inline Whistle& operator >> (Whistle &w, const char*s){	std::cout << s;  return w;}
#define ECHO_() Whistle::INSTANCE(__FILE__, __LINE__, ">>", "++ %s== ") >> "\n";

template <typename T>
auto getValue(T t) {
	if constexpr (std::is_pointer_v<T>){      // (1)
		return *t; // deduces return type to int for T = int*
	} else {                                   // (2)
		return t;  // deduces return type to int for T = int
	}
}
int main(int argc, char* argv[]){TRY_MANUAL(); HEAD1("Function"); TRACE_SRC(-7,-1);
	HEAD1("getValue(int)")
	int a = 1000; getValue(a)      >> ECHO_();
	HEAD1("getValue(int*)")
	int *b = &a;  getValue(b)      >> ECHO_();
	return HORIZONTAL_LINE();
}
END_UNIT // if_constexpr

