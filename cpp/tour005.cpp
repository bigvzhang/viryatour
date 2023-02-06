#include "vtestcommon.h"
#define TOUR_GROUP tour5_

#include "experimental/vmemory.h"
#include "vutility.h"


BEGIN_UNIT_(exception_safety)

using namespace virya::experimental;
using namespace virya::utility;

class X{
static int seq;
int num;
public:
	X():num(++seq){}
	~X(){
		printf("%d is destructed!\n", num);
	}
};
int X::seq = 0;

void g(){
	HEAD1("Entering g!"); TRACE_NXT(3);
	TimeRecord time_record;
	X x2;
	throw std::exception();
	HEAD1("Leaving g!");
}

void f(){
	HEAD1("Entering f!"); TRACE_NXT(4);
	TimeRecord time_record;
	X x1;
	unique_ptr<X> s1(new X);
	g();
	HEAD1("Leaving f!");
}

int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	EXPLAINs("All the variables of TimeRecords and X");
	HORIZONTAL_LINE();TRACE_NXT(6);
	TimeRecord time_record;
	try{
		f();
	}catch(...){
		HEAD1("Captured exception");
	}
	unique_ptr<X> s(new X);
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT// exception_safety
