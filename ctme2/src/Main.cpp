#include <iostream>
using namespace std;

int main (int argc, char* argv[]){
	return 0;
}

Box testFunction(Box ab)
{
	cerr << " + testFunction() called." << endl;
	Box area ("area", 0, 0, 15, 50);
	if (area.intersect(ab)){
		cerr << "  |  Interseciton between:" << endl;
		cerr << "  |    " << area << endl;
		cerr << "  |    " << ab << endl;
		cerr << "  | Gives:" << endl;
		cerr << "  |   " << area.getIntersection(ab) << endl;
	} else
		cout << "  No Intersection" << endl;
	return ab;
}

int main (int argc, char* argv[])
{
	{
		Box b0;
		Box b1 ("b1", 15, 10, 30, 20);
		// cerr << "allocated Boxes:" << Box::getAllocateds() << endl;
		cerr << "\nTest 1:  "; b1.print(cerr); cerr << endl;
		testFunction(b1);

		b1.inflate(5,5,5,5);
		cerr << "\nTest 2:  "; b1.print(cerr); cerr << endl;
		testFunction(b1);

		cerr << "\nTest 3" << endl;
		cerr << "+ Box \"" << endl;
	}
	return 0;
}
