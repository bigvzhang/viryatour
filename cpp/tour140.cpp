#include <array>
#include <algorithm>
#include "vtestcommon.h"
#define TOUR_GROUP tour140_


BEGIN_UNIT_(variable_template)
/**
NOTICE
	Until variable templates were introduced in C++14, parametrized variables were typically 
	implemented as either static data members of class templates or as constexpr function 
	templates returning the desired values.
	Variable templates cannot be used as template template arguments.
 */
int main(int argc, char* argv[]){
	HORIZONTAL_LINE();
	MANUAL(NOTICE);
	HORIZONTAL_LINE();
	return 0;
}

END_UNIT//

