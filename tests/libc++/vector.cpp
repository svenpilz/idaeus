#include <vector>

#define ASSERT_EQUAL(msg, expected, actual) if (actual != expected) { printf("\n%s:%u: %s (%s != %s)\n", __FILE__, __LINE__, msg, #expected, #actual); return false; }

using namespace std;

namespace vector_test {

class Foo {
public:
	bool& _destruct;
	
	Foo(bool& destruct) :_destruct(destruct) {}
	
	~Foo() {
		_destruct = true;
	}
};

bool testPushBack() {
	vector<int> v;
	ASSERT_EQUAL("empty()", true, v.empty());
	
	v.push_back(5);
	ASSERT_EQUAL("empty()", false, v.empty());
	ASSERT_EQUAL("size()", 1, v.size());
	ASSERT_EQUAL("at(0)", 5, v.at(0));
	ASSERT_EQUAL("[0]", 5, v[0]);
	
	v.push_back(42);
	ASSERT_EQUAL("empty()", false, v.empty());
	ASSERT_EQUAL("size()", 2, v.size());
	ASSERT_EQUAL("at(0)", 5, v.at(0));
	ASSERT_EQUAL("[0]", 5, v[0]);
	ASSERT_EQUAL("at(1)", 42, v.at(1));
	ASSERT_EQUAL("[1]", 42, v[1]);
	
	return true;
}

}
