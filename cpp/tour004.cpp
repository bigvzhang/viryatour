#include <fstream>
#include <functional>
#include <vtime.h> // replacement of chrono
#include <varg.h>
#include <vutility.h>


#include <vtestcommon.h>
#define TOUR_GROUP tour4_

BEGIN_UNIT_(stream_simple, cin, getline)
/**
*/
int test_(int argc, char* argv[]){
	HEAD1("A basic test of c++ stream");
	auto method1=[]{
		std::string name;
		BANNER("Method2: getline(std::cin, name)");
		std::cout << "Please Input Your Second Name" << "\n";
		getline(std::cin, name);
		std::cout << "Your Second Name: " << name << "!\n";
	};
	auto method2=[](){
		std::string name;
		BANNER("Method1: std::cin >> name");
			std::cout << "Please Input Your First Name" << "\n";
		std::cin >> name;
		std::cout << "Your First Name: " << name << "!\n";
	};
	return 0;
}
int main(int argc, char* argv[]){
	TRY_MANUAL();
	HEAD1("A basic test of c++ stream");
	std::string name;

	BANNER("Method2: getline(std::cin, name)")
	std::cout << "Please Input Your Second Name" << "\n";
	getline(std::cin, name);
	std::cout << "Your Second Name: " << name << "!\n";

	BANNER("Method1: std::cin >> name")
	std::cout << "Please Input Your First Name" << "\n";
	std::cin  >> name;
	std::cout << "Your First Name: " << name << "!\n";

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//stream_simple

BEGIN_SECTION(tour4_ofstream)

using vtime = virya::vtime;

int DEF_FUNC(tour4_ofstream){
	HEAD1("Testing For ofstream");
	std::string name;
	std::cout << "Please  Input output stream name:" << "\n"; 
	getline(std::cin, name);
	std::ofstream my_out;
	//if((my_out.rdstate() & std::ifstream::failbit) != 0)
	//	std::cerr << "Init state is fail\n";
	HEAD1("Using ios_base::app to apend to the file");
	TRACE_CODE(my_out.open(name.c_str(), std::ios_base::out | std::ios_base::app));
	//if((my_out.rdstate() & std::ifstream::failbit) != 0)
	//	std::cerr << "Open failed'\n";

	if(!my_out.fail()){
		my_out << "Hello, World! " << std::endl << vtime() << "!\n";
		my_out.close();
		std::cout << "Compeleted, please check the output in file: " << name << std::endl;
	}else{
		std::cerr << "Cannot open file:" << name << "!\n";
	}
	HORIZONTAL_LINE();
	return 0;
}
END_SECTION(tour4_ofstream)

BEGIN_UNIT_(op_manipulator, operator on a function or an function-like object, tuple, lambda) using namespace std;

#define ECHOl(...)  Whistle::INSTANCE(__FILE__, __LINE__, ";;",  ##__VA_ARGS__) // whole line

Whistle& operator<<(const char* s, Whistle& o){ cout << s; return o; }
Whistle& operator<<(Whistle& o, const char* s){ cout << s; return o; }


Whistle& operator<<(Whistle& o, Whistle& (*func)(Whistle&)){return func(o);}
Whistle& func(Whistle& o){cout << "calling func"; return o;}

struct func1{ // simulate as function
	int n;
	func1(int n):n(n){}
	friend
	Whistle& operator<<(Whistle& o, func1 f){cout << "class func1 - parameter:" << f.n; return o;}
};

struct func2_{ // it's object simulate as function
	int n = 0;
	func2_& operator()(int n){this->n = n; return *this;} 
	friend
	Whistle& operator<<(Whistle& o, func2_ f){cout << "class func2 - parameter:" << f.n; return o;}
};

int base(){
	HEAD3(manipulator implemented by function, which have no parameters);TRACE_SRC(-18,-17);
	HEAD3(manipulator implemented by help-class, whose construtor can have parameters);TRACE_SRC(-16,-11);
	HEAD3(manipulator implemented by help-object, whose class override opertor());TRACE_SRC(-10,-5);HORIZONTAL5();

	"hello " << ECHOl() << func << "\n"                    ;;
	"hello " << ECHOl() << func1(100) << "\n"              ;;
	func2_ func2; "hello " << ECHOl() << func2(200) << "\n";;
	return HORIZONTAL5();
}

template<class ... Types>
struct tuple_helper{
	typedef tuple_helper<Types...> THIS_TYPE;
	tuple<Types...> tuple_;
	Whistle& (*func)(Whistle&, Types...);
	tuple_helper(Whistle& (*func)(Whistle&, Types...)): func(func){}

	THIS_TYPE& operator()(Types...args){ tuple_ = tuple<Types...>(args...); return *this; }

	friend
	Whistle& operator<<(Whistle& o, THIS_TYPE f){ virya_tuple2::apply(f.func, f.tuple_, o);  return o; }
};

Whistle& func3_(Whistle& o, int p1)        { printf("calling func3 p1:%d", p1);           return o; }
Whistle& func4_(Whistle& o, int p1, int p2){ printf("calling func4 p1:%d p2:%d", p1, p2); return o; }

tuple_helper<int> func3(&func3_);
tuple_helper<int,int> func4(&func4_);

int using_tuple(){HORIZONTAL1();
	HEAD3(generic manipulator - implemented by tuple);TRACE_SRC(-20,-3);HORIZONTAL1();
	"hello " << ECHOl() << func3(300)      << "\n"            ;;
	"hello " << ECHOl() << func4(400, 500) << "\n"            ;;
	return HORIZONTAL1();
}

Whistle& operator<<(Whistle& o, function<void(Whistle&)>func ){ func(o); return o; }
function<void(Whistle&)> func5(int p1){ return [p1](Whistle&o){ 
	printf("calling func5 p1:%d", p1);           
};}
function<void(Whistle&)> func6(int p1, int p2){ return [p1, p2](Whistle&o){ 
	printf("calling func6 p1:%d p2:%d", p1, p2);           
};}

int using_lambda(){HORIZONTAL1();
	HEAD3(manipulator implemented by returnning lamdba function);TRACE_SRC(-9,-3);HORIZONTAL1();
	"hello " << ECHOl() << func5(300)      << "\n"            ;;
	"hello " << ECHOl() << func6(400, 500) << "\n"            ;;
	return HORIZONTAL1();
}

int main(int argc, char* argv[]){
	if(argc == 1) base();
	else if(argc == 2 && strcmp(argv[1], "base") == 0)  base();
	else if(argc == 2 && strcmp(argv[1], "tuple") == 0) using_tuple();
	else if(argc == 2 && strcmp(argv[1], "lambda") == 0) using_lambda();
	else {printf("op_manipulator: invalid arguments"); return 1;}

	SEEALSO(<base> <tuple> <lambda>)
	return 0;
}

END_UNIT//op_manipulator

BEGIN_UNIT_(vtime, chrono, strftime, localftime_, gmftime_, put_time, ctime)
/**
SUMMARY
    1. chrono::time_point is generally a int64 object
       virya::time_point extends chrono::time_point
       virya::stime is alias of instantialization of system_clock
       virya::htime is alias of instantialization of high_resolution_clock
       virya::ytime is alias of instantialization of steady_clock
    2. there's no function to convert time_point to string(till c++20), solution:
       2.1 override chrono::time_point
       2.2 convert to time_t, then to tm, then use put_time(but not ctime) or strftime
*/

int main(int argc, char* argv[]){
	HEAD1("Test virya::time_point");
	TRACE_CODEv(virya::vtime());
	TRACE_CODEv(virya::htime());
	TRACE_CODEv(virya::ytime());

	HEAD1("Test virya::fmtgtime");
	std::time_t t = time(NULL);                             TRACE_LINE();
	auto s1 = virya::fmtgtime("%Y-%m-%d %H:%M:%S GMT" ,t);  TRACE_LV(s1);
	HEAD1("Test virya::fmtltime");
	auto s2 = virya::fmtltime("%Y-%m-%d %H:%M:%S", t);      TRACE_LVm(s2, c_str);

	HORIZONTAL_FRAME(MANUAL())
	return 0;
}

END_UNIT//vtime
