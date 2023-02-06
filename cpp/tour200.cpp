#include <string_view>
#include <span>
#include <array>
#include <algorithm>
#include "vtestcommon.h"
#define TOUR_GROUP tour200_


BEGIN_UNIT_(cpp20_new_features)
/**
New language features
  - Feature test macro
  - 3-way comparison operator <=> and operator==() = default
  - designated initializers
  - init-statements and initializers in range-for
  - char8_t
  - New attributes: [[no_unique_address]], [[likely]], [[unlikely]]
  - pack-expansions in lambda init-captures
  - removed the requirement to use typename to disambiguate in may contexts
  - consteval, constinit
  - further relaxed constexpr
  - signed integers are 2's complement
  - aggregate initialization using parentheses
  - corotines
  - modules
  - constraints and concepts
  - abbreviated function templates
  - DR: array new can deduce array size
New headers
  - bit
  - compare
  - concepts
  - coroutine
  - format
  - numbers
  - ranges
  - source_location
  - span
  - syncstream
  - version
  - barrier
  - latch
  - semaphore
  - stop_token
Library features
  - library feature-test macros
  - formatting library
  - calendar and time zone
  - source_location
  - span
  - endian
  - array support for make_shared
*/
int main(int argc, char* argv[]){
	MANUALb();
	return 0;
}
END_UNIT// cpp20_new_feautures)

BEGIN_UNIT_(three_way_comparision)

int main(int argc, char* argv[]){
	float a = 0.0;        TRACE_LINE();
	float b = -0.0;       TRACE_LINE();
	auto res = a <=> b;   TRACE_SRC(0,5);
	if (res < 0)
		std::cout << "-0 is less than 0";
	else if (res > 0)
		std::cout << "-0 is greater than 0";
	else if (res == 0)
		std::cout << "-0 and 0 are equal";
	else
		std::cout << "-0 and 0 are unordered";
	std::cout << "\n";
	return HORIZONTAL1();
}

END_UNIT// three_way_comparision

BEGIN_UNIT_(using_enum)

enum class color_channel { red, green, blue, alpha };

namespace nm1{
std::string_view to_string(color_channel channel){
	switch (channel){
	case color_channel::red:    return "red";
	case color_channel::green:  return "green";
	case color_channel::blue:   return "blue";
	case color_channel::alpha:  return "alpha";
	default:                    throw   1;
	}
}
}// end namespace1
namespace nm2{
std::string_view to_string(color_channel channel){
	switch(channel){
	using enum color_channel;
	case red:    return "red";
	case green:  return "green";
	case blue:   return "blue";
	case alpha:  return "alpha";
	default:     throw   1;
	}
}
}// namespace 

int main(int argc, char* argv[]){
	HEAD("Before Cpp20");
	TRACE_SRC(-25, -17);
	HEAD("Cpp20");
	TRACE_SRC(-16, -7);
	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//


BEGIN_UNIT_(consteval, Immediate function)

consteval int func1(int n) { return n + 100; }
constexpr int func2(int n) { return n + 100; }

int main(int argc, char* argv[]){
	HEAD("Defines");
	TRACE_SRC(-5,-4);
	HEAD("USAGE");
	TRACE_SRC(1,7);
	constexpr int a1 = func1(100);  // OK
	constexpr int a2 = func2(100);  // OK
	int b1 = func1(100);	        // OK
	int b2 = func2(100);            // OK	
	int x = 100;
	//int c1 = func1(x);	        // BAD
	int c2 = func2(x);              // OK	
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT//

BEGIN_UNIT_(span) // INCLUDE <span>

void func1(std::span<int> values){
	std::for_each(values.begin(), values.end(), [](auto i){
		std::cout << " " << i;
	});
	std::cout << "\n";
}

int main(int argc, char* argv[]){
	HEAD("Defines and usage");
	TRACE_SRC(-9, -4);
	HEAD1("Usage");
	TRACE_SRC(1, 4);
	std::vector<int> v1  = {1,2,3};
	std::array<int,3> v2 =  {1,2,3};
	func1(v1);	
	func1(v2);	
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT//
