#include <iostream>
#include "Box.h"

using namespace std;
using namespace tme2;

/* Now that we have a print we need to provide the operator
 * that print our Boxes into a stream with the redirection <<
 * OVERLOAD OPERATOR
 */
ostream& operator<< (ostream& o, const Box& b)
{
	b.print(o);
	return o;
}

Box testFunction(Box ab)
{
	cerr << " + testFunction() called." << endl;
	Box area ("area", 0, 0, 15, 50);
	if (area.intersect(ab)){
		Box boxinter = area and ab;
		cerr << "  |  Interseciton between:" << endl;
		cerr << "  |    " << area << endl;
		cerr << "  |    " << ab << endl;
		cerr << "  | Gives:" << endl;
		cerr << "  |   " << boxinter << endl;
	}
	else
		cout << "  No Intersection" << endl;

	return ab;
}

int main (int argc, char* argv[])
{
	{
		Box b0;
		Box b1 ("b1", 15, 10, 30, 20);
		cerr << "Allocated Boxes:" << Box::getAllocateds() << endl;

		cerr << "\nTest 1:  "; b1.print(cerr); cerr << endl;
		testFunction(b1);

		b1.inflate(5,5,5,5);
		cerr << "\nTest 2:  "; b1.print(cerr); cerr << endl;
		testFunction(b1);

		cerr << "\nTest3: " << endl;
		cerr << "+ Box\"" << b1.getName() << "\" empty:  "
			<< boolalpha << b1.isEmpty() << endl;
		cerr << "+ Box\"" << b1.getName() << "\" width:  "
			<< boolalpha << b1.getWidth() << endl;
		cerr << "+ Box\"" << b1.getName() << "\" height:  "
			<< boolalpha << b1.getHeight() << endl;
		b1.inflate(-11);
		cerr << "+ Box\"" << b1.getName() << "\" empty:  "
			<< boolalpha << b1.isEmpty() << "(inflated -11)\n";
		cerr << "+ Box\"" << b1.getName() << "\" width:  "
			<< boolalpha << b1.getWidth() << endl;
		cerr << "+ Box\"" << b1.getName() << "\" height:  "
			<< boolalpha << b1.getHeight() << endl;

		cerr << "Allocated boxes: " << Box::getAllocateds() << endl;
	}

	return 0;
}
