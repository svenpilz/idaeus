#include <memory>

using namespace std;

namespace shared_ptr_test {

class Foo {
	
};

bool testCopyConstructor() {
	Foo* f = new Foo;
	
	shared_ptr<Foo> p(f);
	shared_ptr<Foo> p2(p);

	return true;
}

}
