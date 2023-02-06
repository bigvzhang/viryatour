#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iostream>
#include <vector>

#include "vtestcommon.h"



#define DEF_FUNC(X) X(int argc, char* argv[])

#define PRINT_CONTENT(X) {printf("[%4d] %s => %s\n",__LINE__, #X, X.toString().c_str()); running_line = __LINE__ + 1;}
#define EXECUTE_LINE(...) printf("%s ==> \n",#__VA_ARGS__); __VA_ARGS__


BEGIN_SECTION(tour102_rtnref)
class A {
public:
	A()                 { printf("A Constructor    [%p]\n", this); }
	A(const A&o)        { printf("A CopyConstructor[%p]\n", this); }
	~A()                { printf("A Destructor     [%p]\n", this); }
	virtual void speak(){ printf("I'm A            [%p]\n", this); }

};

class C : public A {
public:
	C()                 { printf("C Constructor    [%p]\n", this); }
	C(const A&o)        { printf("C CopyConstructor[%p]\n", this); }
	~C()                { printf("C Destructor     [%p]\n", this); }
	virtual void speak(){ printf("I'm C            [%p]\n", this); }
};

A&  f0() {
	A a;
	return a;
}

#if ! _MSC_VER >= 1920
A & f1(){
	return A();
}
A & f2(){
	return (A&)C();
}
#endif
int DEF_FUNC(tour102_rtnref){

#if ! _MSC_VER >=1920
	{
		auto t1 = f1();
		t1.speak();
	}
	{
		auto t2 = f2();
		t2.speak();
	}
	{
		f1().speak();
	}
	{
		f2().speak();
	}
	auto t1 = f1();
	auto t2 = f2();
#else

	printf("Unix=> /cygdrive/d/MyTour/VicCPPTour/src/tourA02.cpp:32:9: warning: reference to local variable 'a' returned [-Wreturn-local-addr]");
	printf("Unix=> error: cannot bind non-const lvalue reference of type 'tour102_rtnref::A&' to an rvalue of type 'tour102_rtnref::A'\n");
	

	
	HORIZONTAL_LINE();
	{
		TRACE_CODE(A t1 = f0();)
		t1.speak();
	}
	HORIZONTAL_LINE();
	{
		TRACE_CODE(auto t1 = f0();)
		t1.speak();
	}
	HORIZONTAL_LINE();
	{
		TRACE_CODE(A& t1 = f0();)
		t1.speak();
	}
	HORIZONTAL_LINE();
	{
		TRACE_CODE(f0().speak();)
	}
	HORIZONTAL_LINE();
#endif
	
	return 0;

}
END_SECTION(tour102_rtnref)


BEGIN_UNIT(tour102_assignref)
class A {
public:
	A()                 { printf("A Constructor    [%p]\n", this); }
	A(const A&o)        { printf("A CopyConstructor[%p]\n", this); }
	~A()                { printf("A Destructor     [%p]\n", this); }
	virtual void speak(){ printf("I'm A            [%p]\n", this); }
};


A&  f0() {
	static A a;
	return a;
}

A  f1() {
	static A a;
	return a;
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	ANNOTATE(A& f0();)
	ANNOTATE(A  f1();)
	HORIZONTAL_LINE();
	{
		TRACE_CODE(auto t1 = f0();)
		t1.speak();
	}
	HORIZONTAL_LINE();
	{
		TRACE_CODE(auto& t1 = f0();)
		t1.speak();
	}
	HORIZONTAL_LINE();
	{
		TRACE_CODE(auto t1 = f1();)
		t1.speak();
	}
	HORIZONTAL_LINE();
	{
#if ! _MSC_VER >= 1920
		TRACE_CODE(auto& t1 = f1();)
		t1.speak();
#endif
		ANNOTATE(auto& t1 = f1(); <= is not acceptable in gcc(LINUX))
	}
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//(tour102_assignref)
