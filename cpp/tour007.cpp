#include <memory>
#include <cstring>

#include "vtestcommon.h"
#define TOUR_GROUP tour7_


BEGIN_UNIT_(enable_shared_from_this)

/**
PRATICE
 1.mke sure the shared_ptr of one object is got from one source
 2.idea: the bud(the shared information) should be like the share_ptr in particular Operation Environment 
 */

struct Good: std::enable_shared_from_this<Good> // note: public inheritance
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
	~Good(){std::cout << "Good::~Good() called\n"; }
};
 
struct Bad
{
    std::shared_ptr<Bad> getptr() {
        return std::shared_ptr<Bad>(this);
    }
    ~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

struct Best: std::enable_shared_from_this<Best>
{
    std::shared_ptr<Best> getptr() {
        return shared_from_this();
    }
	~Best(){std::cout << "Best:~Best() called\n"; }
	static std::shared_ptr<Best> create() { return std::shared_ptr<Best>(new Best()); } // SAFE_CREATOR
private:
	Best() = default;
};

void show(){
	HEAD1("Ddefinitions of classes Good, Bad and Best");	
	TRACE_SRC(-29, -4);
}

void test_good()
{
	HEAD1("Testing enable shared_from this -- using tmplate(enable_shared_from this)"); TRACE_NXT(5, "++");
	// Good: the two shared_ptr's share the same object
	std::shared_ptr<Good> gp1 = std::make_shared<Good>();
	std::shared_ptr<Good> gp2 = gp1->getptr();
	std::cout << "gp1.use_count() = " << gp1.use_count() << '\n';
	std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
}

void test_weak(){
	HEAD1("Testing enable shared_from this -- called without having std::shared_ptr owning the caller")
	// Bad: shared_from_this is called without having std::shared_ptr owning the caller 
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // undefined behavior (until C++17) and std::bad_weak_ptr thrown (since C++17)
        std::cout << "Exception:" << e.what() << '\n';    
    }
}

void test_best(){
	HEAD1("Use as good, but avoid misusing"); TRACE_NXT(6);
	std::shared_ptr<Best> gp1 = Best::create();
	std::shared_ptr<Best> gp2 = gp1->shared_from_this();
	std::cout << "gp1.use_count() = " << gp1.use_count() << '\n';
	std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
	//Best v;) <- Will not compile because Best::Best() is private.
	//share_ptr<Best> v = make_shared<Best>();
}

std::vector<std::shared_ptr<Good>> vct;
void test_reuse()
{
	HEAD1("Testing enable shared_from this -- reuse")
	std::shared_ptr<Good> gp1 = std::make_shared<Good>();
	std::shared_ptr<Good> gp2 = gp1->getptr();
	std::cout << "gp1.use_count() = " << gp1.use_count() << '\n';
	std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';
	vct.push_back(gp1->getptr());
}


void test_bad(){
	HEAD1("Testing Bad -- using shared_ptr direcly")
    // Bad, each shared_ptr thinks it's the only owner of the object
    std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
    std::shared_ptr<Bad> bp2 = bp1->getptr();
    std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';
	ANNOTATE(Testing Bad --  double-delete of Bad)

} // UB: double-delete of Bad

int main(int argc, char* argv[]){
	auto print_help =[] {
		printf("<cmd>\n");
		printf("    good\n");
		printf("    reuse\n");
		printf("    weak\n");
		printf("    best\n");
		printf("    bad\n");
		printf("    show\n");
		printf("    man\n");
		printf("Notice, use good/reuse to compare the results\n");
	};
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i], "help") == 0 || strcmp(argv[i], "--help") == 0){
				print_help();
				return 0;
			} else if(strcmp(argv[i], "good") == 0){
				test_good();
				ANNOTATE(Good::~Good should have been called)
			} else if(strcmp(argv[i], "reuse") == 0){
				test_reuse();
				ANNOTATE(Good::~Good should not be called yet)
			} else if(strcmp(argv[i], "weak") == 0){
				test_weak();
			} else if(strcmp(argv[i], "bad") == 0){
				test_bad();
			} else if(strcmp(argv[i], "best") == 0){
				test_best();
			} else if(strcmp(argv[i], "show") == 0){
				show();
			} else if(strcmp(argv[i], "man") == 0){
				HEAD1("Manual");	MANUAL();
			} else {
				printf("Invalid option(%s)\n", argv[i]);
				return -1;
			}
		}
	}else{
		test_good();
		test_weak();
		test_bad();
	}
	HORIZONTAL_LINE()
	return 0;
}
END_UNIT//_enable_shared_from_this
