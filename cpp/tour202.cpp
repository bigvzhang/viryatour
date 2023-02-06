#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "vtestcommon.h"
#define TOUR_GROUP tour202_

BEGIN_UNIT_(parameter_pack_expansion)

template<class... T>
void dummy(T... t){}


template<typename... Args>
static void foo(Args &&... args){
	double rslt = 0;
	auto sum = [&](double t)->double{
		rslt += t;
		return rslt;
	};

	HEAD1("There are two special places where a pack expansion can occur");

	BANNER(1. inside a brace); TRACE_NXT();
	std::vector<double> vct = {sum(std::forward<Args>(args)) ...};
	TRACE_CODEv(rslt);

	for(int i = 0; i < vct.size(); i++){
		std::cout << "vct[" << i << "] = " << vct[i] << "\n";
	}

	BANNER(2. inside a parenthesis); TRACE_NXT(2);
	dummy(sum(std::forward<Args>(args)) ...);
	//CPP17 => (sum(std::forward<Args>(args)), ...); <= see: tour `fold_expression`
	TRACE_CODEv(rslt);

	BANNER(2.1. tricky: expansion with comma, also see tour `comma`); TRACE_NXT(2);
	//{std::vector<double> dummy_vct = {(sum(std::forward<Args>(args)),100.0L) ...};} // compile with warnings,TODO: find why 
	{std::vector<int>    dummy_vct = {(sum(std::forward<Args>(args)),  100) ...};}
	//{std::vector<double> dummy_vct = {(void, sum(std::forward<Args>(args))) ...};}
	{std::vector<double> dummy_vct = {(1, sum(std::forward<Args>(args))) ...};}
	TRACE_CODEv(rslt);
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	REFERENCE("https://stackoverflow.com/questions/25680461/variadic-template-pack-expansion");
	HORIZONTAL_LINE();

	foo(1.0, 2.0, 3.0, 88, 99);
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT

BEGIN_UNIT_(variadic_constructor)
class A {
public:
	A()                 { printf("A    1st ctor    [%p] %s\n", this, __FUNCTION__); }
	A(int a)            { printf("A    2nd ctor    [%p] %s\n", this, __FUNCTION__); }
	A(int a, int b)     { printf("A    3rd ctor    [%p] %s\n", this, __FUNCTION__); }
	A(int a, int b, int){ printf("A    4th ctor    [%p] %s\n", this, __FUNCTION__); }
	A(const A&o)        { printf("A Copy   ctor    [%p] %s\n", this, __FUNCTION__); }
	~A()                { printf("A  Destructor    [%p] %s\n", this, __FUNCTION__); }
	virtual void speak(){ printf("I'm A            [%p] %s\n", this, __FUNCTION__); }
};

template<class T>
class X : public T {
public:
	template<class... ARGS>
	X(ARGS... args):
		T(args...){
		 printf(" X       ctor    [%p] %s\n", this, __FUNCTION__); 
	}
	virtual void speak(){ printf("I'm X            [%p] %s\n", this, __FUNCTION__); }
};
template<class T>
class Y : public T {
public:

	Y() :
		T(){
		printf(" Y   1st ctor    [%p] %s\n", this, __func__);
	}

	template<class... ARGS>
	Y(ARGS... args) :
		T(args...){
		printf(" Y   2nd ctor    [%p] %s\n", this, __FUNCTION__);
	}
	virtual void speak(){ printf("I'm Y            [%p] %s\n", this, __FUNCTION__); }

};


int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	ANNOTATE(A has four constructors!);
	TRACE_CODEn(A a0);
	TRACE_CODEn(A a1{});          // use A v{} instead of A v(); 
	TRACE_CODEn(A a2(1));
	TRACE_CODEn(A a3(1,2));
	TRACE_CODEn(A a4(1,2,3));
	TRACE_CODEn(A a5(a0));

	HORIZONTAL_LINE(); // X
	ANNOTATE(X has one constructor: template variadic constructor);
	TRACE_CODEn(X<A> x0);
	TRACE_CODEn(X<A> x1{});       // use A v{} instead of A v();
	TRACE_CODEn(X<A> x2(1));
	TRACE_CODEn(X<A> x3(1, 2));
	TRACE_CODEn(X<A> x4(1, 2, 3));
	TRACE_CODEn(X<A> x5(x0));
	HORIZONTAL_LINEs(); // new
	ANNOTATE(test new X);
	TRACE_CODEn(new X<A>);
	TRACE_CODEn(new X<A>());      // new A() == new A{}
	TRACE_CODEn(new X<A>(1));
	TRACE_CODEn(new X<A>(1, 2));
	TRACE_CODEn(new X<A>(1, 2, 3));


	HORIZONTAL_LINE(); // Y
	ANNOTATE(Y has two constructors: one is template variadic constructor, the other is non-template constructor);
	TRACE_CODEn(Y<A> y0);
	TRACE_CODEn(Y<A> y1{});            // use A v{} instead of A v();
	TRACE_CODEn(Y<A> y2(1));
	TRACE_CODEn(Y<A> y3(1, 2));
	TRACE_CODEn(Y<A> y4(1, 2, 3));
	TRACE_CODEn(Y<A> y5(y0));
	HORIZONTAL_LINEs(); // new
	ANNOTATE(test new Y);
	TRACE_CODEn(new Y<A>);
	TRACE_CODEn(new Y<A>());
	TRACE_CODEn(new Y<A>(1));
	TRACE_CODEn(new Y<A>(1, 2));
	TRACE_CODEn(new Y<A>(1, 2, 3));


	HORIZONTAL_LINE();
	ANNOTATE(call virtual function speak);
	TRACE_CODEn(a0.speak());
	TRACE_CODEn(x0.speak());
	TRACE_CODEn(y0.speak());

	HORIZONTAL_LINE(); // END
	ANNOTATE(ending)
	HORIZONTAL_LINE(); // END
	return 0;
}
END_UNIT//varadic_constructor

BEGIN_UNIT_(class_unison, tuple, variadic class template)
template<typename... Xs>
struct unison : public Xs...{
	unison(Xs&&...args):Xs(args)...{}
	unison(const Xs&...args):Xs(args)...{}
	unison(){}
};
using namespace std;
int main(int argc, char* argv[]){
	HEAD1("Definition 1");
	TRACE_SRC(-8,-4);

	BANNER(Demo);
	TRACE_SRC(1,2);
	//unison<string, int, double> demo1;
	unison<vector<int>, string> demo2;

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT


