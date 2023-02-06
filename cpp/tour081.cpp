#include "vtestcommon.h"
#define TOUR_GROUP tour81_

#include <typeindex>
#include <functional>

BEGIN_UNIT_(template_doc)
/**
ENTRY
    functiontemplate        ftemplate         [function][template]
    classtemplate           ctemplate            [class][template]
    memberfunctiontemplate  mtemplate   [memberfunction][template]
	function as template parameter ftparam
*/
int main(int argc, char* argv[]){
	MANUAL()
	return 0;
}
END_UNIT//


BEGIN_UNIT_(template)
using namespace std;
class A0{
protected:
	string name;
public:
	A0(const char* name):name(name){}
	void a0() {printf("From A0:: %s\n", __FUNCTION__);}
	void say(){printf("From A0:: %s\n", __FUNCTION__);}
	virtual void whoami(){puts("I'm A0");}
	virtual void hello(){puts("From A0");}
};

class B0{
protected:
	string name;
public:
	B0(const char* name):name(name){}
	void b0() {printf("From B0:: %s\n", __FUNCTION__);}
	void say(){printf("From B0:: %s\n", __FUNCTION__);}
	virtual void whoami(){puts("I'm B0");}
	virtual void hello() {puts("From B0");}
};

template<class Z> class C0 : public Z{
public:
	using Z::name;
	using Z::say;
	C0(const char*name):Z(name){}
	void speak();

	virtual void hello() {puts("From C0");}
};
template<class Z>
void C0<Z>::speak(){
	printf("%s => ",Z::name.c_str());
	Z::say();
}

int main(int argc, char* argv[]){
	C0<A0> ca("C0A0");
	C0<B0> cb("C0B0");
	ca.speak();
	cb.speak();
	ca.whoami();
	cb.whoami();
	ca.hello();
	cb.hello();
	return 0;
}
END_UNIT
	
BEGIN_UNIT_(template_hierarchy)
using namespace std;

class BaseObject{
protected:
	string hierarchy;
public:
	BaseObject():hierarchy("BASE"){}
	virtual string get_hierarchy(){return hierarchy;}
	virtual void whoami() = 0;
	virtual void func1()   = 0;
};

class A : public BaseObject{
public:
	A(){hierarchy = "A"; }
	virtual void whoami() {puts("I'm A!");}
	virtual void func1()   {puts("A Rocks!\n");}
};

class B : public BaseObject{
public:
	B(){hierarchy = "B"; }
	virtual void whoami() {puts("I'm B!");}
	virtual void func1()   {puts("B Rocks!\n");}
};

template<class BASE> class R : public BASE{
public:
	R(){BASE::hierarchy += ".R";}
	virtual void whoami() {puts("I'm R!");}
};

template<class BASE> class S : public BASE{
public:
	S(){BASE::hierarchy += ".S";}
	virtual void whoami() {puts("I'm S!");}
};
template<class BASE> class T : public BASE{
public:
	T(){BASE::hierarchy += ".T";}
	virtual void whoami() {puts("I'm T!");}
};

#define FEATURE_T(X) (r ? (new T<X>()) : (new X()))
#define FEATURE_S(X) (s ? FEATURE_T(S<X>) : FEATURE_T(X))
#define FEATURE_R(X) (t ? FEATURE_S(R<X>) : FEATURE_S(X))

int main(int argc, char* argv[]){
	for(int t = 0; t < 2; t++){
		for(int s = 0; s < 2; s++){
			for(int r = 0; r < 2; r++){
				BaseObject* a  = FEATURE_R(A);
				BaseObject* b  = FEATURE_R(B);
				printf("[%d:%d:%d:] %20s %20s  =>", t,s,r, a->get_hierarchy().c_str(), b->get_hierarchy().c_str());
				a->whoami();
				delete(a);
				delete(b);
			}
		}
	}
	return 0;
}
END_UNIT //template_hierarchy)

BEGIN_UNIT_(function_as_tp, function as template parameter) // tp == template parameter
KEYWORDS(function as template parameter)

template<class T> T add(T m, T n) { return m + n;}

template <class F,   class ... Args> auto func1(F f, Args... args){return f(args...);}
template <class RTN, class ... Args> RTN  func2(RTN(*f)(Args... args), Args... args){ return f(args...); }

int main(int argc, char* argv[]){
	HORIZONTAL_LINE()
	REFERENCE("https://stackoverflow.com/questions/1174169");
	HORIZONTAL_FRAME(TRACE_SRC(-8, -5));
	int i1=3, i2=4;
	TRACE_CODEv( func1( &add<int>, i1, i2 ));
	TRACE_CODEv( func2( &add<int>, i1, i2 ));
	
	HORIZONTAL_LINE(); 
	return 0;
}
END_UNIT

namespace virya{

namespace xp1 {
template <typename...> struct mfn_traits;

template < typename O, typename A, typename R, typename... Args>
struct mfn_traits <R (O::*)(A, Args...)> {
	using result_type = R;
	using arg1_type = A;
};

template < typename O, typename A, typename R, typename... Args>
struct mfn_traits <R (O::*)(A, Args...) const> {
	using result_type = R;
	using arg1_type = A;
};

#if _MSC_VER >= 1920
template < typename O, typename A, typename R, typename... Args>
struct mfn_traits <R (O::*)(A, Args...) const noexcept> {
	using result_type = R;
	using arg1_type = A;
};
#endif
} // namespace virya.xp1


namespace xp2{
template <typename...> struct mfn_traits;

template < typename O, typename R, class A1>
struct mfn_traits <R(O::*)(A1)  > {
	using result_type = R;
	using arg1_type   = A1; // std::remove_reference<A>::type;
	int v;
};
template < typename O, typename R, class A1, class A2>
struct mfn_traits <R(O::*)(A1, A2)  > {
	using result_type = R;
	using arg1_type   = A1; // std::remove_reference<A>::type;
	using arg2_type   = A2; // std::remove_reference<A>::type;
	int v;
};
} // namespace virya.xp2


namespace xp = xp1;


namespace detail {
// COPYFORM boost/.../function_traits.hpp

#define BOOST_STATIC_CONSTANT(t, expression) const static t expression 

template<typename Function> struct function_traits_helper;

template<typename R>
struct function_traits_helper<R (*)(void)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 0);
  typedef R result_type;
};

template<typename R, typename T1>
struct function_traits_helper<R (*)(T1)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 1);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T1 argument_type;
};

template<typename R, typename T1, typename T2>
struct function_traits_helper<R (*)(T1, T2)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 2);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T1 first_argument_type;
  typedef T2 second_argument_type;
};

template<typename R, typename T1, typename T2, typename T3>
struct function_traits_helper<R (*)(T1, T2, T3)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 3);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4>
struct function_traits_helper<R (*)(T1, T2, T3, T4)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 4);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 5);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 6);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 7);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 8);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 9);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9,
         typename T10>
struct function_traits_helper<R (*)(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
{
  BOOST_STATIC_CONSTANT(unsigned, arity = 10);
  typedef R result_type;
  typedef T1 arg1_type;
  typedef T2 arg2_type;
  typedef T3 arg3_type;
  typedef T4 arg4_type;
  typedef T5 arg5_type;
  typedef T6 arg6_type;
  typedef T7 arg7_type;
  typedef T8 arg8_type;
  typedef T9 arg9_type;
  typedef T10 arg10_type;
};
}// end namespace virya.detail

template<typename Function>
struct function_traits : 
  public detail::function_traits_helper<typename std::add_pointer<Function>::type>
{
};

} // namespace virya

BEGIN_UNIT_(get_func_arg_type, get_mfn_arg_type, first_argument_type)

using namespace virya;
using namespace virya::xp;

Whistle& operator >> (const std::type_info& a, Whistle& o) { std::cout << a.name(); return o; }
Whistle& operator >> (const char* a, Whistle& o)           { std::cout << a;        return o; }

class A {
public:
	int f(int a1)       { return 0; }
	int g(int a1) const { return 0; }

	bool operator()(const float& a, double b){return false;}
};
// [get type of first (second, etc...) argument, similar to result_of](https://stackoverflow.com/questions/27879815)
// [Get argument type of template callable object](https://stackoverflow.com/questions/22630832)
// [What is the replacement for std::function::argument_type](https://stackoverflow.com/questions/52556432)
// [Type of the first parameter of a member function](https://stackoverflow.com/questions/27159187)
// [How to pass const member function as non-const member function](https://stackoverflow.com/questions/53596067)
int main(int argc, char* argv[]){
	typeid(function_traits<decltype(atoi)>::arg1_type)                      >> ECHOn();
	typeid(function_traits<decltype(atoi)>::result_type)                    >> ECHOn();

	//typeid(mfn_traits<decltype(&A::f)>)                                   >> ECHOn();
	typeid(mfn_traits<decltype(&A::f)>::arg1_type)                          >> ECHOn();
	typeid(mfn_traits<decltype(&A::f)>::result_type)                        >> ECHOn();
	//typeid(mfn_traits<decltype(&A::operator())>)                          >> ECHOn();
	typeid(mfn_traits<decltype(&A::operator())>::arg1_type)                 >> ECHOn();
	//typeid(mfn_traits<decltype(&A::operator())>::arg2_type)               >> ECHOn();

	//typeid(mfn_traits<decltype(&std::less<int>::operator())>)             >> ECHOn();
	typeid(mfn_traits<decltype(&std::less<int>::operator())>::arg1_type)    >> ECHOn();
	typeid(mfn_traits<decltype(&std::less<int>::operator())>::result_type)  >> ECHOn();


	return 0;
}

END_UNIT//

BEGIN_UNIT_(simple_variadic_func)
template<typename T> void g(T x) {std::cout << x << "<== Type is " << typeid(x).name() << " Function "<< __PRETTY_FUNCTION__ << "\n";}
template<typename T> void f(T x) {std::cout << x << "<== Type is " << typeid(x).name() << " Function "<< __PRETTY_FUNCTION__ << "\n";}
void f() {printf("None Parameters Function => %s\n", __PRETTY_FUNCTION__);}

template <typename T, typename... M>
void f(T head, M... m){
	g(head);
	f(m...);
}

using my_uinit = unsigned int; // alias

int main(int argc, char* argv[]){
	std::cout << "It's variadic template tests... => " <<" f(1,\"5\", \"6\", 5.0,8.0); "<< std::endl;
	EXECUTE_LINE(f(1,"5", "6", 5.0,8.0));
	EXECUTE_LINE(f(8));
	EXECUTE_LINE(f(9.8));
	EXECUTE_LINE(f(9.7));
	EXECUTE_LINE(f(true));
	EXECUTE_LINE(f());
	EXECUTE_LINE(my_uinit v1 = -1);
	EXECUTE_LINE(std::cout << v1 << " Type is:" << typeid(v1).name() << "\n");
	return 0;
}
END_UNIT//


BEGIN_UNIT_(comma, "(void comma x)", simulate as fold expression in c++17)
void f(){}

template<typename T>
void bar(T t) {
	std::cout<<__FUNCTION__ << "         type:" <<typeid(T).name() << " value:" << t << '\n';
}

template<typename... Args>
void foo(Args &&... args)
{
	HEAD1("Entering foo...");
	TRACE_CODE(std::vector<int>  d1 = {((void)bar(std::forward<Args>(args)), 0) ...};);

	ANNOTATE(content of d1 : )
	for(auto i : d1){
		std::cout << i << "\n";
	}

	HORIZONTAL_LINEs();
	TRACE_CODE(std::vector<int>  d2 = {(1,2),(3,4),(5,6)});
	ANNOTATE(content of d2:)
	for(auto i : d2){
		std::cout << i << "\n";
	}
	HEAD1("Leaving foo...");
}

int main(int argc, char * argv[]){
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/25680461/variadic-template-pack-expansion");
	HORIZONTAL_LINE();
	TRACE_CODEw(int n1 = (1, 2););
	TRACE_CODE (int n2[] =             {1,(2, 3), 9});
	TRACE_CODEw(int n3[] =             {1,(2, 3), (void, 4), 9});
	TRACE_CODE (int n4[] =             {1,(2, 3), (f(),  4), 9});
	TRACE_CODE (std::vector<int>  n5 = {1,(2, 3), 9});
	TRACE_CODEw(std::vector<int>  n6 = {1,(2, 3), (void, 4), 9});
	TRACE_CODE (std::vector<int>  n6 = {1,(2, 3), (f(),  4), 9});

	HORIZONTAL_LINEs();
	TRACE_CODE(int a=1,b=2,c=3;)
	TRACE_CODE(double d=4,e=5,f=6;)
	TRACE_CODE(foo(a, b, c,d,e,f);)

	HORIZONTAL_LINE();
	EXPLAIN(Conclusion: `(void, x)` is OK in some expression!)
	EXPLAIN(    1: (void,       x) is BAD in brace expression {} and parameter pack)
	EXPLAIN(    2: (`int`,      x) is OK  in brace expression {} and parameter pack)
	EXPLAIN(    3: (`void F()`, x) is OK  in brace expression {} and parameter pack)
	EXPLAIN(    4: (`int  F()`, x) is OK  in brace expression {} and parameter pack)

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT
