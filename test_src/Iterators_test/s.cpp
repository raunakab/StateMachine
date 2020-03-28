#include <stdlib.h>
#include <stdio.h>
#include <vector>

static int objects = 0;

class A {
	private:
		int const id = -1;

	public:
		A();
		A(int const id);
		A(A const & other);
		~A();

		int const getID() const;
};

A::A() { printf("dflt., obj: %d\n",++objects); return; }
A::A(int const id) : id(id) { printf("rglr., obj: %d\n", ++objects); return; }
A::A(A const & other) { printf("copy, obj: %d\n",++objects); return; }
A::~A() { printf("dstr., obj: %d\n",--objects); return; }

int const A::getID() const { return this->id; }



int main() {
	printf("%d\n",objects);
	std::vector<A *> v;

	A && test_0 = A(1);
	int const id = test_0.getID();
	printf("%d\n",id);

	//printf("pushing:\n");
	//for (int i=0; i<1; ++i) v.push_back(&A(i));
	//printf("finished.\n");

	return 0;
}
