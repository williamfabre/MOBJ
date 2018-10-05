#include <iostream>
#include "Box.h"

using namespace std;
using namespace tme2;

/* Now that we have a print we need to provide the operator
 * that print our Boxes into a stream with the redirection <<
 * OVERLOAD OPERATOR
 */
//ostream& operator<< (ostream& o, const Box& b)
//{
	//b.print(o);
	//return o;
//}

/* Attention cette fonction va appeler ab une Box par reference et pas par
 * copie. Si on avait laisse Box et pas Box& on aurait une copie et donc un
 * appelle a un constructeur en supplementaire dans l'affichage et donc un objet
 * supplementaire a creer // detruire FAIRE TRES ATTENTION A CE GENRE DE BETISE
 */
Box testFunction(Box& ab)
{
	cerr << " + testFunction() called." << endl;
	Box area ("area", 0, 0, 15, 50);
	cerr << "  |  Interseciton between:" << endl;
	cerr << "  |    " << area << endl;
	cerr << "  |    " << ab << endl;
	cerr << "  | Gives:" << endl;

	if (area.intersect(ab)){
		Box boxinter = area and ab;
		cerr << "  |   " << boxinter << endl;
	}
	else
		cout << "  No Intersection" << endl;

	return ab;
}

/* Le programme cree une copie de l'objet quand il entre dans une nouvelle
 * fonction
 */

int main (int argc, char* argv[])
{
	{
		Box b0;
		Box b1 ("b1", 15, 10, 30, 20);
		//cerr << "Allocated Boxes:" << Box::getAllocateds() << endl;

		cerr << "\nTest 1:  \n"; b1.print(cerr); cerr << endl;
		testFunction(b1);

		b1.inflate(5,5,5,5);
		cerr << "\nTest 2:  \n"; b1.print(cerr); cerr << endl;
		testFunction(b1);

		cerr << "\nTest3: \n" << endl;
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

		//cerr << "Allocated boxes: " << Box::getAllocateds() << endl;
	}

	return 0;
}
