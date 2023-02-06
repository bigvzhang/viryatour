#include "vtestcommon.h"
#define TOUR_GROUP tour6_


BEGIN_UNIT_(nm_1)

#define EXEC_CODE0(...) printf("%-30s ",#__VA_ARGS__); __VA_ARGS__

namespace n1{
class A{};
}
namespace n2{
class B{};
}
namespace n3{
using namespace n1;
class C{};
}

namespace m1{
using namespace n1;
void f(){
	TITLE2("using namespace n1" )
	EXEC_CODE0(A a;)     ANNOTATE(not need explict namespace n1)
	EXEC_CODE0(n2::B b;) ANNOTATE(need explict namespace n2)
	EXEC_CODE0(n3::C c;) ANNOTATE(need explict namespace n3)
}
}

namespace m2{
using namespace n2;
void f(){
	TITLE2("using namespace n2")
	EXEC_CODE0(n1::A a;) ANNOTATE(need explict namespace n1)
	EXEC_CODE0(B b;)     ANNOTATE(not need explict namespace n2)
	EXEC_CODE0(n3::C c;) ANNOTATE(need explict namespace n3)
}
}


namespace m3{
using namespace n3;
void f(){
	TITLE2("using namespace n3")
	EXEC_CODE0(A a;)     ANNOTATE(not need explict namespace n1! for n3 uses namespace n1!)
	EXEC_CODE0(n2::B b;) ANNOTATE(need explict namespace n2)
	EXEC_CODE0(C c;)     ANNOTATE(not need explict namespace n3)
}
}

int main(int argc, char* argv[]){
	TITLE("namespace testing 1")
	EXPLAINs("There're three namespaces:");
	EXPLAINs("  n1: contains class A");
	EXPLAINs("  n2: contains class B");
	EXPLAINs("  n3: contains class C and uses n1");

	m1::f();
	m2::f();
	m3::f();
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT//nm_1
