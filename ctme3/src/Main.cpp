#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "Timer.h"
#include "GPL_2_text.h"

using namespace std;

namespace vector_bench
{
void backInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplVector.push_back(string(GPL_2_text[i]));
	}

	cout << "size() : " << gplVector.size() << endl;
	cout << "max_size() : " << gplVector.max_size() << endl;
	cout << "capacity() : " << gplVector.capacity() << endl;
	//cout << gplVector.reserve() << endl;
	sort(gplVector.begin(), gplVector.end());

	for(string s : gplVector) {
		cout << s << " ";
	}
	cout << endl;
}

void frontInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++)
	{
		gplVector.insert(gplVector.begin(), GPL_2_text[i]);
	}

	sort(gplVector.begin(), gplVector.end());
}


}

namespace list_bench
{
}

namespace map_bench
{
}

int main (void)
{
	Timer t;

	cout << "Vector TB" << endl;
	t = t.start();
	vector_bench::backInsert();
	t = t.stop();
	cout << "backInsert tt: " << t << endl;

	t = t.start();
	vector_bench::frontInsert();
	t = t.stop();
	cout << "frontInsert tt: " << t << endl;


	return 0;
}
