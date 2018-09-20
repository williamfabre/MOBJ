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


