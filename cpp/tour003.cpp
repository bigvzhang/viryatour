#pragma warning(disable:4996)
#include <stdio.h>
#include <initializer_list>
#include <string>
#include <typeinfo>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream> // for std::basic_stringstream
#include <vector>
#include <list>
#include <regex>
#include <functional>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cmath>
#endif

#include "vtestcommon.h"
#define TOUR_GROUP tour3_



BEGIN_UNIT_(stdlib_name)
int main(int argc, char* argv[]){
	puts("<algorithm>");
	puts("<array>");
	puts("<cmath>");
	puts("<complex>");
	puts("<fstream>");
	puts("<future>");
	puts("<iostream>");
	puts("<iterator>");
	puts("<limits>");
	puts(" <list>");
	puts("<map>");
	puts("<memory> uniqure_ptr shared_ptr allocator");
	puts("<mutext>" );
	puts("<regex>");
	puts("<set> set multiset");
	puts("<sstream>");
	puts("<string>");
	puts("<thread>");
	puts("<unordered_map>");
	puts("<utility>  move(), swap(), pair");
	puts("<valarray> valarray, slice, gslice");
	puts("<vector>   vector");
	return 0;
}
END_UNIT//stdlib_name
	

BEGIN_UNIT_(string)
/**
SUMMARY
    1. member function `length()` is `size()`
    2. strlen(str.c_str()) not aways equals str.length()
    3. will not automatically reduce memory untill calling shrink_to_fit
*/
int main(int argc, char* argv[]){ CODE_FORMAT_Help __(-35);
	#define TRACE_S() TRACE_LINE_(printf("ptr:%p length:%2zu size:%2zu capacity:%2zu strlen:%2zu value:`%s`\n", s.c_str(), s.length(), s.size(), s.capacity(), strlen(s.c_str()), s.c_str()))
	{
		HEAD("Testing std::string s");
		std::string s;	   TRACE_S();
		s ="abcdefgh";     TRACE_S();
		s += "ABCDEFGH";   TRACE_S();
		s += "12345678";   TRACE_S();
		s += "HIJKLMNO";   TRACE_S();
	}
	{
		HEAD("Testing std::string length()");
		std::string s = "abcdefghigklmn"; TRACE_S();
		s[5] = '\0';                      TRACE_S();
	}
	{
		HEAD("Testing std::string reserve");
		std::string s;                    TRACE_S();
		s.reserve(12);                    TRACE_S();
		s.reserve(20);                    TRACE_S();
	}
	{
		HEAD("Testing std::string resize");
		std::string s;                    TRACE_S();
		s.resize(12);                     TRACE_S();
		s.resize(20);                     TRACE_S();
		s.resize(31);                     TRACE_S();
		s.resize(32);                     TRACE_S();
		s.resize(31);                     TRACE_S();
		s.resize(12);                     TRACE_S();
		s.shrink_to_fit();                TRACE_S();
	}

	HORIZONTAL_FRAME(MANUAL(SUMMARY));
	return 0;
	#undef TRACE_S
}
END_UNIT// string


BEGIN_UNIT_(string_initialize)
/**
SUMMARY
    1. string()
    2. string(const char*)
    3. string(n, char)
*/
int main(int argc, char* argv[]){ CODE_FORMAT_Help __(-25);
	#define TRACE_S(s) TRACE_LINE_(printf("ptr:%p length:%2zu size:%2zu capacity:%2zu strlen:%2zu value:`%s`\n", s.c_str(), s.length(), s.size(), s.capacity(), strlen(s.c_str()), s.c_str()))

	HEAD("construct(initialize) object of string");

	using string = std::string;
	string s1;	              TRACE_S(s1);
	string s2("abc");	      TRACE_S(s2);
	string s3(5,'*');	      TRACE_S(s3);
	string s4(5, '\0');	      TRACE_S(s4);
	string s5;s5.resize(5);   TRACE_LINEv(s5==s4);
	HORIZONTAL_FRAME(MANUAL(SUMMARY));
	return 0;
	#undef TRACE_S
}
END_UNIT// string

BEGIN_UNIT_(strstr) using namespace std;
//char* str = "one two three";
//inline void operator &(const char* pos, Whistle &w){
//	pos ? printf("found the needle at position %td\n", pos - str) : printf("the needle was not found\n");
//}

inline string operator & (const char* src, function<string(const char*)>&fn)  { return fn(src); }
//template<class T> inline string operator & (T src, function<string(T)>&fn)  { return fn(src); }// fails
inline Whistle& operator & (string s, Whistle &w)  { std::cout << s;  return w; }
inline string convert_fn(const char* haystack, const char* pos){
	return pos ? virya::format("found the needle at position %td\n", pos - haystack) : "the needle was not found\n";
}

inline void operator &(size_t pos, Whistle &w){
	pos != string::npos ? printf("found the needle at position %td\n",  pos) : printf("the needle was not found\n");
}

#define ECHOfn(...) convertor & Whistle::INSTANCE(__FILE__, __LINE__, ##__VA_ARGS__) // convert

int main(int argc, char* argv[])
{
	HEAD3("c standard function - strstr");           
	{
		const char* str = "one two three";TRACE_E(); function<string(const char*)> convertor = [str](const char* pos)->string{return convert_fn(str, pos); };
		strstr(str, "two")               & ECHOfn();
		strstr(str, "")                  & ECHOfn(); 
		strstr(str, "one")               & ECHOfn();
		strstr(str, "nine")              & ECHOfn(); 
		strstr(str, "n")                 & ECHOfn();
	}

	HEAD3("c++ string::find");
	{
		string str = "one two three";  TRACE_E();
		str.find("two")              & ECHO();
		str.find("")                 & ECHO();
		str.find("one")              & ECHO();
		str.find("nine")             & ECHO();
		str.find("n")                & ECHO();
	}

	HORIZONTAL_LINE();           
	NOTICEf("");
	NOTICEf_("finding empty string returns the first postion of the haystack");
	HORIZONTAL_LINE();           
	return 0;
}
END_UNIT // strstr

BEGIN_UNIT_(strstr1) virya::ioq ioq; CODE_FORMAT_Help __(CODE_FORMAT_, "++ %-35s");
/**
NOTICE
    strstr1 is duplicate of strstr; demonstrates the differences between TRACE_QUE_ and ECHO
*/
void find_str(char const* str, char const* substr)
{
	const char* pos = strstr(str, substr);
	pos ? ioq.printf("found the string '%s' in '%s' at position %td\n",
				 substr, str, pos - str)
		: ioq.printf("the string '%s' was not found in '%s'\n",
			      substr, str);
}

int main(int argc, char* argv[]) {HORIZONTAL1(); MANUAL();
	HORIZONTAL_LINE();           
    char str[] = "one two three";TRACE_LINE()
	find_str(str, "two");        TRACE_QUE_()
	find_str(str, "");           TRACE_QUE_()
	find_str(str, "one");        TRACE_QUE_()
	find_str(str, "nine");       TRACE_QUE_()
	find_str(str, "n");          TRACE_QUE_()
	HORIZONTAL_LINE();           

	return 0;
}
END_UNIT // strstr1

BEGIN_UNIT_(strtok)
/**
NOTICE
    The function is destructive: replaces some elements with character '\0'
*/
int main(int argc, char* arvg[])
{
	HEAD("Test strtok");
	char str[100] = "A bird came down the walk";	TRACE_LINE_(printf("Address:%p Content:{%s}\n", str,str)); TRACE_NXT(3);
	for(char *token = std::strtok(str, " "); token != NULL; token = std::strtok(NULL, " ")) {
		std::cout << token << '\n';
	}
	/*str is modified*/                             TRACE_LINE_(printf("Address:%p Content:{%s}\n", str,str));

	HORIZONTAL_FRAME(MANUAL())
	return 0;
}
END_UNIT//strtok

// Units from split1 to split 5 copied from https://www.techiedelight.com/split-string-cpp-using-delimiter 
BEGIN_UNIT(tour3_split1, use find_first_not_of)
void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
 
int main(int argc, char* argv[])
{
    std::string s = "C*C++*Java";
    const char delim = '*';
 
    std::vector<std::string> out;
    tokenize(s, delim, out);
 
    for (auto &s: out) {
        std::cout << s << '\n';
    }
 
    return 0;
}
END_UNIT  // tour3_split1

BEGIN_UNIT(tour3_split2, use getline)
void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);
 
    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}
 
int main(int argc, char* argv[])
{
    std::string s = "C*C++*Java";
    const char delim = '*';
 
    std::vector<std::string> out;
    tokenize(s, delim, out);
 
    for (auto &s: out) {
        std::cout << s << '\n';
    }
 
    return 0;
}

END_UNIT // tour3_split2

BEGIN_UNIT(tour3_split3, use regex_token_iterator)
int main(int argc, char* argv[])
{
    std::string s = "C*C++*Java";
    std::regex regex("\\*");
 
    std::vector<std::string> out(
                    std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
                    std::sregex_token_iterator()
                    );
 
    for (auto &s: out) {
        std::cout << s << '\n';
    }
 
    return 0;
}
END_UNIT // tour3_split3

BEGIN_UNIT(tour3_split4, use strtok)
void tokenize(std::string const &str, const char* delim,
            std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }
}
 
int main(int argc, char* argv[])
{
    std::string s = "C*C++*Java";
    const char* delim = "*";
 
    std::vector<std::string> out;
    tokenize(s, delim, out);
 
    for (auto &s: out) {
        std::cout << s << '\n';
    }
 
    return 0;
}

END_UNIT // tour3_split4

BEGIN_UNIT(tour3_split5, use find)

void tokenize(const std::string& s, const char delim,
            std::vector<std::string>& out)
{
    std::string::size_type beg = 0;
    for (size_t end = 0; (end = s.find(delim, end)) != std::string::npos; ++end)
    {
        out.push_back(s.substr(beg, end - beg));
        beg = end + 1;
    }
 
    out.push_back(s.substr(beg));
}
 
int main(int argc, char * argv[])
{
    std::string s = "C*C++*Java";
    const char delim = '*';
 
    std::vector<std::string> out;
    tokenize(s, delim, out);
 
    for (auto &s: out) {
        std::cout << s << '\n';
    }
 
    return 0;
}

END_UNIT // tour3_split5



BEGIN_SECTION(tour3_setvbuf)
int DEF_FUNC(tour3_setvbuf)
{
	HEAD("this is just a simple setevbuf test")
	ANNOTATE(TODO, 1. test in linux)
	ANNOTATE(TODO, 2. _IOFBF, _IOLBF, IONBF)
	ANNOTATE(TODO, 3. STUDY tool truss/strace(which is used to monitor syscalls))

	FILE* fp = fopen("test.txt", "r");
	if(fp == NULL) {
		perror("fopen"); return 1;
	}


#ifdef _WIN32
	if(setvbuf(fp, NULL, _IOFBF, 256) != 0) {
		perror("setvbuf failed"); // POSIX version sets errno
		return 1;
	}
#else
	struct stat stats;
	if(fstat(fileno(fp), &stats) == -1) { // POSIX only
		perror("fstat"); return 1;
	}

	printf("BUFSIZ is %d, but optimal block size is %ld\n", BUFSIZ, stats.st_blksize);
	if(setvbuf(fp, NULL, _IOFBF, stats.st_blksize) != 0) {
		perror("setvbuf failed"); // POSIX version sets errno
		return 1;
	}
#endif

	int ch;
	while((ch = fgetc(fp)) != EOF); // read entire file: use truss/strace to
								  // observe the read(2) syscalls used

	fclose(fp);

	HORIZONTAL_LINE();
	return 0;
}
END_SECTION(tour3_setvbuf)


struct Entry{std::string name; int64_t number;};
std::ostream& operator<<(std::ostream&os, const Entry& e){
	return os << "{\"" << e.name << "\","  <<e.number<<"}";
}
std::istream& operator>>(std::istream&is, Entry&e){
	char c,c2;
	if(is>>c && c=='{' && is >>c2 && c2=='"'){
		std::string name;
		while (is.get(c) && c !='"')
			name+=c;
		if(is>>c && c==','){
			int number=0;
			if(is>>number>>c&&c=='}'){
				e = {name,number};
				return is;
			}
		}
	}
	std::cout << std::ios_base::failbit << "\n";
	//is.setf(std::ios_base::failbit);
	return is;
}
BEGIN_SECTION(tour3_io_entry)
int DEF_FUNC(tour3_io_entry){
	Entry e;
	std::cout<<"Please Input E\n";
	std::cin>>e;
	std::cout<<e;
	return 0;
}
END_SECTION(tour3_io_entry)

BEGIN_SECTION(tour3_stl)
void print_book(std::vector<Entry>& book){
	for(auto e : book){
		std::cout << e << "\n";
	}
}
void print_book(std::list<Entry>& book){
	for(auto e : book){
		std::cout << e << "\n";
	}
}
int DEF_FUNC(tour3_stl){
	std::cout << "Using vector<Entry>\n";
	std::vector<Entry> phone_book = {
		{"Vic",  13812345678},
		{"Zhang", 13912345678},
	};
	print_book(phone_book);

	std::cout << "\nUsing list<Entry>\n";
	std::list<Entry> phone_book2 = {
		{"Arman", 13878901234},
		{"Zhang", 13988488848},
	};
	print_book(phone_book2);
	return 0;
}
END_SECTION(tour3_stl)
	
BEGIN_UNIT_(ostream_iterator, std_copy) using namespace std;
/**
NAME
    ostream_iterator - describes an output iterator object that writes successive elements onto the output stream with the extraction operator <<
*/
int main(int argc, char* argv[]){
	HEAD1("basic");	TRACE_SRC(1,4);
	ostream_iterator<string> oo{cout, "~~"};
	*oo = "Hello,";  // operator=  writes object to the associated output sequence
	oo++;            // operator++ does nothing, for legacy purpose
	*oo = "world!";
	cout << "\n";
	
	HEAD1("Work with std::copy");	TRACE_SRC(1, 2);
	vector<int> myvector;	for (int i=1; i<10; ++i) myvector.push_back(i*10);
	copy(myvector.begin(), myvector.end(), ostream_iterator<int>(cout,", "));
	cout << "\n";

	return HORIZONTAL_LINE();
}
END_UNIT


BEGIN_UNIT_(stringstream) using namespace std;
int main(int argc, char* argv[]){
	HEAD1("basic");	TRACE_SRC(1, 3);
	ostringstream oss("a b"); 
	oss << 1;
	cout<< oss.str() <<"\n";

	HEAD1("ate");	TRACE_SRC(1, 3);
	ostringstream ate("a b", ios_base::ate); 
	ate << 1;
	cout << ate.str() << "\n";

	return HORIZONTAL_LINE();
}
END_UNIT

BEGIN_UNIT_(regex_token_iterator)
typedef std::regex_token_iterator<const char *> Myiter;
int main(int argc, char* argv[])
{
	HEAD("regex_token_iterator");
	TRACE_SRC(0,2);
    const char *pat = "QabcXabcYabcZabcQ";
    Myiter::regex_type rx("(a)(b)c");
    Myiter next(pat, pat + strlen(pat), rx);
    Myiter end;

    HEAD("show whole match")
    for (; next != end; ++next)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

	HEAD("show prefix before match")
    next = Myiter(pat, pat + strlen(pat), rx, -1);
    for (; next != end; ++next)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

	HEAD("show (a) submatch only")
    next = Myiter(pat, pat + strlen(pat), rx, 1);
    for (; next != end; ++next)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

	HEAD("show (b) submatch only")
		next = Myiter(pat, pat + strlen(pat), rx, 2);
	for(; next != end; ++next)
		std::cout << "match == " << next->str() << std::endl;
	std::cout << std::endl;

	HEAD("show prefixes and submatches")
    std::vector<int> vec;
    vec.push_back(-1);
    vec.push_back(1);
	vec.push_back(2);
    next = Myiter(pat, pat + strlen(pat), rx, vec);
    for (; next != end; ++next)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

	HEAD("show prefixes and whole matches")
    int arr[] = {-1, 0};
    next = Myiter(pat, pat + strlen(pat), rx, arr);
    for (; next != end; ++next)
        std::cout << "match == " << next->str() << std::endl;
    std::cout << std::endl;

	HEAD("other members")
	TRACE_SRC(0,9)
    Myiter it1(pat, pat + strlen(pat), rx);
    Myiter it2(it1);
    next = it1;

    Myiter::iterator_category cat = std::forward_iterator_tag();
    Myiter::difference_type dif = -3;
    Myiter::value_type mr = *it1;
    Myiter::reference ref = mr;
    Myiter::pointer ptr = &ref;

    dif = dif; // to quiet "unused" warnings
    ptr = ptr;

	HEAD("")

	return (0);
}
END_UNIT//


BEGIN_UNIT_(regex_search)
int main(int argc, char* argv[])
{
	auto test = [](const char* txt, const char* rgx){
		HORIZONTAL_LINE()
		std::string s(txt);
		std::smatch m;
		std::regex e(rgx);   // matches words beginning by "sub"

		std::cout << "Target sequence   : " << txt << std::endl;
		std::cout << "Regular expression: " << rgx << std::endl;
		std::cout << "The following matches and submatches were found:" << std::endl;

		while(std::regex_search(s, m, e)) {
			std::cout << "  [Match Size:" << m.size() << "] => ";
			for(auto x : m) std::cout << std::left << std::setw(40) << x << '|';
			std::cout  << std::endl;
			s = m.suffix().str();
		}
	};
	//auto test = [](const char* txt, const char* rgx){
	//	try
	//	{test_(txt,rgx);}
	//	catch(...){
	//		std::cout <<"Error, invalid regex!\n";
	//	}
	//};
	test("this subject has a submarine as a subsequence", "\\b(sub)([^ ]*)" );
	test("{abc=:xyzm}{best:better}", "\\{[^:]+:[^:]+\\}");
	test("{abc=:xyzm}{best:better}", "\\{([^:]+):([^:]+)\\}");
	test("{continue:return false}{DKXZY<InertiaSS>:mrdkx_lndx_S}{SlopeDX:SlopeDX<DkxTyp>}", "\\{([^:]+):([^:]+)\\}");
	test("{continue:return false}{DKXZY<InertiaSS>:mrdkx_lndx_S}{SlopeDX:SlopeDX<DkxTyp>}", "\\{(.+):(.+)\\}");
	test("{continue:return false}{DKXZY<InertiaSS>:mrdkx_lndx_S}{SlopeDX:SlopeDX<DkxTyp>}", "\\{(.+):(.+?)\\}");
	test("{continue:return false}{DKXZY<InertiaSS>:mrdkx_lndx_S}{SlopeDX:SlopeDX<DkxTyp>}", "\\{(.+?):(.+)\\}");
	test("{continue:return false}{DKXZY<InertiaSS>:mrdkx_lndx_S}{SlopeDX:SlopeDX<DkxTyp>}", "\\{(.+?):(.+?)\\}");
	test("{continue:return false}{DKXZY<InertiaSS>:mrdkx_lndx_S}{SlopeDX:SlopeDX<DkxTyp>}", "\\{([\\w\\s<>]+):([\\w\\s<>]+)\\}");
	test("2345", R"(^\d{4}$)");
	test("2345", R"(^(\d{4})$)");
	test("2021-07-19 10:29:41.400", R"(^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})\s*(.*))");
	test("2021-07-19 10:29:41.400 abc", R"(^(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3})\s*(.*))");
	HORIZONTAL_LINE()

	return 0;
}
END_UNIT


BEGIN_UNIT_(regex_match_basic) using namespace std;
int main (int argc, char* argv[])
{
	HEAD1("match string literal(const char*)") ; 
	regex_match("subject", regex("(subj)(.*)")) & ECHO_K("string literal matched\n", "string literal NOT matched\n");
	regex_match("subject",  regex("(ubj)(.*)")) & ECHO_K("string literal matched\n", "string literal NOT matched\n");
	regex_match("subject", regex("(subj)"))     & ECHO_K("string literal matched\n", "string literal NOT matched\n");
	regex_match("subject",  regex("subj.*"))    & ECHO_K("string literal matched\n", "string literal NOT matched\n");
	ANNOTATE(the match is subject to the whole content)

	HEAD1("match string object "); TRACE_NXT(2)
	string s("subject");
	regex e("(sub)(.*)");
	regex_match (s,e)                     & ECHO_K("string object matched\n", "string object NOT matched\n");
	regex_match (s.begin(), s.end(), e )  & ECHO_K("range matched\n",        "range NOT matched\n");

	HEAD1("cmatch"); TRACE_NXT(3)
	const char cstr[] = "subject";
	cmatch cm;    // same as match_results<const char*> cm;
	regex_match (cstr,cm,e);
	cout << "string literal with " << cm.size() << " matches\n";

	HEAD1("smatch"); TRACE_NXT(2)
	smatch sm;    // same as match_results<string::const_iterator> sm;
	regex_match (s,sm,e);
	cout << "string object with " << sm.size() << " matches\n";

	HEAD1("smatch - range"); TRACE_NXT(2)
	regex_match ( s.cbegin(), s.cend(), sm, e);
	cout << "range with " << sm.size() << " matches\n";

	HEAD1("using explicit flags"); TRACE_NXT()
	regex_match ( cstr, cm, e, regex_constants::match_default );

	HEAD1("print matches"); TRACE_NXT(4)
	for(unsigned i = 0; i < cm.size(); ++i) {
		cout << "[" << cm[i] << "] ";
	}
	cout << endl;

	HORIZONTAL_LINE()
	return 0;
}
END_UNIT



BEGIN_UNIT_(regex_exec, user-defined literals and regex)
using namespace std;
class RegexFunc{
protected:
	regex rgx;
public:
	RegexFunc(const char*s) : rgx(s){}
public:
	auto search(const char* txt){cmatch mr; regex_search(txt, mr, rgx); return mr; }
	auto match(const char* txt){cmatch mr; regex_match(txt, mr, rgx); return mr; }
};

class RegexSearch:public RegexFunc{
public:
	RegexSearch(const char*s) : RegexFunc(s){}
public:
	auto operator()(const char* txt){ cmatch mr; regex_search(txt, mr, rgx); return mr; }
	auto operator()(const char* txt, cmatch&mr){ return regex_search(txt, mr, rgx);}
};

class RegexMatch:public RegexFunc{
public:
	RegexMatch(const char*s) : RegexFunc(s){}
public:
	auto operator()(const char* txt){ cmatch mr; regex_match(txt, mr, rgx); return mr; }
	auto operator^ (const char* txt){ return regex_match(txt, rgx);  }
	auto operator()(const char* txt, cmatch&mr){ return regex_match(txt, mr, rgx);  }
};

RegexFunc   operator "" _rgx(const char* s, size_t size){return RegexFunc(s);}
RegexSearch operator "" _search(const char* s, size_t size){ return RegexSearch(s); }
RegexMatch  operator "" _match(const char* s, size_t size){ return RegexMatch(s); }

void operator "" _print(const char* str, std::size_t){// `const char*` and `std::size_t` required as parameters
	std::cout << str << '\n';
}
long long operator "" _celsius(unsigned long long tempCelsius) {// `unsigned long long` required as parameter
	return std::llround(tempCelsius * 1.8 + 32);
}
int operator "" _int(const char* str, std::size_t) {
	return std::stoi(str);
}

int main(int argc, char* argv[]){HEAD(defintions); TRACE_SRC(-23,-12); 
	
	HEAD("'regex'_search(text)"); 
	TRACE_CODEv("^(\\d+)$"_rgx.search("abc").size())
	TRACE_CODEv(R"(^(\d+)$)"_rgx.search("123").size())
	TRACE_CODEv("^(\\d+)$"_search("abc").size())// override operator()
	TRACE_CODEv(R"(^(\d+)$)"_search("123").size())
	TRACE_CODE(cmatch mr1;)
	TRACE_CODEv(R"(^(\d+)$)"_search("abc", mr1))
	TRACE_CODEv(R"(^(\d+)$)"_search("123", mr1))

	HEAD("'regex'_match(text)"); 
	TRACE_CODEv(R"((\d+))"_match("abc").size())
	TRACE_CODEv(R"((\d+))"_match("abc 123").size())
	TRACE_CODEv(R"((\d+))"_search("abc 123").size())
	TRACE_CODEv(R"((\d+))"_match("123").size())
	TRACE_CODEv(R"((\d+))"_match ^ "123")
	TRACE_CODE(cmatch mr2;)
	TRACE_CODEv(R"(^(\d+)$)"_match("abc", mr2))
	TRACE_CODEv(R"(^(\d+)$)"_match("123", mr2))


	HEAD("Basic user defined literal"); TRACE_SRC(-32, -24);HEAD3s(""); TRACE_SRC(1,3);
	"abc"_print; // run function
	24_celsius;  // == 75; convert
	"24"_int;    // == 24; convert


	HORIZONTAL_LINE()
 
    return 0;
}
END_UNIT // tour3_split3

BEGIN_UNIT_(overloaded_operators)
/**
any of the following operators:
	+ - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=>(since C++20) && || ++ -- , ->* -> () []
*/
int main(int argc, char* argv[]){
	MANUALb();
	return 0;
}
END_UNIT// overloaded_opertators
BEGIN_UNIT_(operator_infer, auto ptr, operator bool)

namespace nm1{
template <class RealObj>
class AutoFree{
private:
	RealObj* _content;
	std::function<void(RealObj*)> func;
public:
	AutoFree(std::function<void(RealObj*)> f, RealObj* param_content = nullptr) : func(f), _content(param_content){}
	AutoFree(RealObj* param_content = nullptr) : _content(param_content){}
	AutoFree(const AutoFree& o) = delete;
	AutoFree& operator=(const AutoFree& o) = delete;
	~AutoFree(){ if(_content) {if(func) func(_content); else delete _content;} }

	operator RealObj* () { printf("Access %s\n", __FUNCTION__); return _content; }
	//operator bool()      { printf("Access %s\n", __FUNCTION__); return _content != nullptr; }
	RealObj* operator->(){ printf("Access %s\n", __FUNCTION__); return _content; }
	RealObj* content()   { return _content; }
	void set(RealObj*o){ if(_content) {if(func) func(_content); else delete _content;} _content = o; }
};
} // namespace nm1

namespace nm2{
template <class RealObj>
class AutoFree{
private:
	RealObj* _content;
	std::function<void(RealObj*)> func;
public:
	AutoFree(std::function<void(RealObj*)> f, RealObj* param_content = nullptr) : func(f), _content(param_content){}
	AutoFree(RealObj* param_content = nullptr) : _content(param_content){}
	AutoFree(const AutoFree& o) = delete;
	AutoFree& operator=(const AutoFree& o) = delete;
	~AutoFree(){ if(_content) {if(func) func(_content); else delete _content;} }

	operator RealObj* () { printf("Access %s\n", __FUNCTION__); return _content; }
	operator bool()      { printf("Access %s\n", __FUNCTION__); return _content != nullptr; }
	RealObj* operator->(){ printf("Access %s\n", __FUNCTION__); return _content; }
	RealObj& operator *(){ printf("Access %s\n", __FUNCTION__); return *_content; }

	RealObj* content()   { return _content; }
	void set(RealObj*o){ if(_content) {if(func) func(_content); else delete _content;} _content = o; }
};
}// namespace nm2

class TEST{};

int main(int argc, char* argv[]){
	REFERENCE("https://en.cppreference.com/w/cpp/memory/shared_ptr")
	HORIZONTAL_LINE();
	{
		ANNOTATEs("operators of class 1");
		TRACE_SRC(-38,-36);
		HORIZONTAL_LINEs();
		ANNOTATEs("access `if(a)` and `*a`")
		nm1::AutoFree<TEST> a1(new TEST());
		if(!a1)
			return 1;
		auto x = *a1;
		HORIZONTAL_LINEs();
		printf("SUMMARY                                                             \n");
		printf("  1) `*a`    calls 'operator A*()'                                  \n");
		printf("  2) `if(a)` calls 'operator bool()' when exists                    \n");
		printf("             or calls 'operator A*()' when the above non-existent   \n");

	}
	HORIZONTAL_LINE();
	{
		ANNOTATEs("operators of class 2");
		TRACE_SRC(-34,-31);
		HORIZONTAL_LINEs();
		ANNOTATEs("access `if(a)` and `*a`");
		nm2::AutoFree<TEST> a1(new TEST());
		if(!a1)
			return 1;
		auto x = *a1;
		HORIZONTAL_LINEs();
		printf("SUMMARY                                                            \n");
		printf("  1) `*a`    will call 'A& operator *()'                           \n");
	}

	HORIZONTAL_LINE();

	return 0;
}
END_UNIT // operator_infer

BEGIN_UNIT_(operator_bool)
class _TC_ACTION_RESULT{
public:
	int                     _req_state;
	bool                    _result;
public:
	_TC_ACTION_RESULT(bool result, int req_state);
	operator bool    (           ) {return _result;}
};

_TC_ACTION_RESULT::_TC_ACTION_RESULT(bool result, int req_state):
	_result(result),
	_req_state(req_state)
{
}

class _TC_ACTION_RESULT2{
public:
	int                     _req_state;
	bool                    _result;
public:
	_TC_ACTION_RESULT2(bool result, int req_state);

};

_TC_ACTION_RESULT2::_TC_ACTION_RESULT2(bool result, int req_state):
	_result(result),
	_req_state(req_state)
{
}

int main(int argc, char* argv[]){
	{
		_TC_ACTION_RESULT r1(true,1);  if(r1)puts("OK");else puts("Bad");
		_TC_ACTION_RESULT r2(true,0);  if(r2)puts("OK");else puts("Bad");
		_TC_ACTION_RESULT r3(false,1); if(r3)puts("OK");else puts("Bad");
		_TC_ACTION_RESULT r4(false,0); if(r4)puts("OK");else puts("Bad");
		bool b1 = r1; if(b1)puts("OK");else puts("Bad");
		bool b2 = r2; if(b2)puts("OK");else puts("Bad");
		bool b3 = r3; if(b3)puts("OK");else puts("Bad");
		bool b4 = r4; if(b4)puts("OK");else puts("Bad");
		printf("%d %d\n", r3._req_state, r3._result);
	}
	{
//		_TC_ACTION_RESULT2 r1(true,1);  if(r1)puts("OK\n");else puts("Bad\n");
//		_TC_ACTION_RESULT2 r2(true,0);  if(r2)puts("OK\n");else puts("Bad\n");
//		_TC_ACTION_RESULT2 r3(false,1); if(r3)puts("OK\n");else puts("Bad\n");
//		_TC_ACTION_RESULT2 r4(false,0); if(r4)puts("OK\n");else puts("Bad\n");
	}
	return 0;
}
END_UNIT //operator_bool

BEGIN_UNIT_(operator_call, call operator, for_each ) using namespace std;
struct Sum
{
    int sum = 0;
    void operator()(int n) { sum += n; }
};
 
int main(int argc, char*argv[]) { HEAD1("call operator");TRACE_SRC(-6,-2); HEAD3("DATA");TRACE_SRC(1,1);
	vector<int> v = {1, 2, 3, 4, 5};

	HEAD1("implement 1"); TRACE_NXT(2);
    Sum s1 = for_each(v.begin(), v.end(), Sum());
    cout << "The sum is " << s1.sum << '\n';

	HEAD1("implement 2"); TRACE_NXT(2);
	Sum s2; for_each(v.begin(), v.end(), s2);
	cout << "The sum is " << s2.sum << '\n';

	HEAD1("implement 3"); TRACE_NXT(2);
	Sum s3; for(auto it = v.begin(); it != v.end(); it++){ s3(*it); }
	cout << "The sum is " << s3.sum << '\n';


	HORIZONTAL5();
	NOTICE("Implement 2 is bad; TODO, find a solution")
	return 0;
}
END_UNIT// call_operator
