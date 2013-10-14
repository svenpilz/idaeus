#include <memory>

#define ASSERT_EQUAL(msg, expected, actual) if (actual != expected) { printf("\n%s:%u: %s (%s != %s)\n", __FILE__, __LINE__, msg, #expected, #actual); return false; }

using namespace std;

namespace shared_ptr_test {

class Foo {
public:
	bool& _destruct;
	
	Foo(bool& destruct) :_destruct(destruct) {}
	
	~Foo() {
		_destruct = true;
	}
};

bool testCopyConstructor() {
	bool destruct = false;
	Foo* f = new Foo(destruct);
	
	{
		shared_ptr<Foo> p1(f);
		ASSERT_EQUAL("get()", f, p1.get());
		ASSERT_EQUAL("unique()", true, p1.unique());
		ASSERT_EQUAL("!destruct", false, destruct);
	
		{
			shared_ptr<Foo> p2(p1);
			ASSERT_EQUAL("get()", f, p1.get());
			ASSERT_EQUAL("get()", f, p2.get());
			ASSERT_EQUAL("p1.unique()", false, p1.unique());
			ASSERT_EQUAL("p2.unique()", false, p2.unique());
			ASSERT_EQUAL("p1.use_count()", 2, p1.use_count());
			ASSERT_EQUAL("p2.use_count()", 2, p2.use_count());
			ASSERT_EQUAL("!destruct", false, destruct);
		}
	
		ASSERT_EQUAL("get()", f, p1.get());
		ASSERT_EQUAL("unique()", true, p1.unique());
		ASSERT_EQUAL("!destruct", false, destruct);
	}
	
	ASSERT_EQUAL("destruct", true, destruct);
	
	return true;
}

}
