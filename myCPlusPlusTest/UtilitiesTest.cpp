#include "UtilitiesTest.h"
#include <memory>
#include <iostream>
using std::shared_ptr;
using std::weak_ptr;

Ret PairTest()
{
	Ret r1(1, "222");

	Ret r2 = make_pair(2, "3");

	return r1;

}


void Shared_ptrTest()
{
	shared_ptr<int> p(new int(10));
	weak_ptr<int> w(p);
	while (!w.expired()) {
		cout << w.use_count() << endl;
		shared_ptr<int> t = w.lock();
		cout << *t << endl;
		cout << w.use_count() << endl;
		if (w.use_count() == 2) {
			break;
		}
	}
	w.reset();
	cout << w.expired() << endl;
}


