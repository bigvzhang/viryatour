#include "vtestcommon.h"
#include "vtest.h"
#define TOUR_GROUP tour101_
// USED for NUMBER library

#include <chrono>
#include <iomanip>
#include <numeric>


BEGIN_UNIT_(distance)
int main(int argc, char* argv[])
{
	std::cout << "std::distance returns the number of hops from first to last. " << std::endl;
	std::vector<int> v{3, 1, 4};
	std::cout << "distance(first, last) = "
		<< std::distance(v.begin(), v.end()) << '\n'
		<< "distance(last, first) = "
		<< std::distance(v.end(), v.begin()) << '\n';
	//the behavior is undefined (until C++11)
	return 0;
}
END_UNIT//distance


BEGIN_UNIT_(reduce)
/**
FUNCTION SYNOPSIS
   reduce(InputIt first, InputIt last)
   reduce(InputIt first, InputIt last, <>initialValue)
   reduce(InputIt first, InputIt last, <>initialValue, <>operator_op)

   reduce(ExceutionPolicy&&, ...) // with policy
*/

auto eval = [](auto title, auto fun) {
	const auto t1 = std::chrono::high_resolution_clock::now();
	const auto result = fun();
	const auto t2 = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> ms = t2 - t1;
	std::cout << std::setw(28) << std::left << title << "sum: "
		<< result << "\t time: " << ms.count() << " ms\n";
};

void basic(){
	{
        const std::vector<double> v(100'000'007, 0.1);

        eval("std::accumulate(double)", [&v]{ return std::accumulate(v.cbegin(), v.cend(), 0.0); });
        //eval("std::reduce(double)", [&v]{ return std::reduce(SEQ v.cbegin(), v.cend(), 0.0); });
        //eval("std::reduce(double)", [&v]{ return std::reduce(PAR v.cbegin(), v.cend(), 0.0); });
    }
    {
        const std::vector<long> v(100'000'007, 1);
 
        eval("std::accumulate(long)", [&v]{ return std::accumulate(v.cbegin(), v.cend(), 0); });
        //eval("std::reduce(long)", [&v]{ return std::reduce(SEQ v.cbegin(), v.cend(), 0); });
        //eval("std::reduce(long)", [&v]{ return std::reduce(PAR v.cbegin(), v.cend(), 0); });
    }
}

std::vector<virya::test::SubEntry> subEntries = {
	{"basic",    basic  }
};

int main(int argc, char* argv[]){TRY_MANUAL();
	return virya::test::submain(subEntries, argc, argv);
}

END_UNIT // reduce
