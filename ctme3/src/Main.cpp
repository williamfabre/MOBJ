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

void show(vector<string> gplVector)
{
	cout << "size() : " << gplVector.size() << endl;
	cout << "max_size() : " << gplVector.max_size() << endl;
	cout << "capacity() : " << gplVector.capacity() << endl;

	for(string s : gplVector) {
		cout << s << " ";
	}
	cout << endl;

}

void backInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplVector.push_back(string(GPL_2_text[i]));
	}

	sort(gplVector.begin(), gplVector.end());
	//show(gplVector);

}

void frontInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++)
	{
		gplVector.insert(gplVector.begin(), GPL_2_text[i]);
	}

	sort(gplVector.begin(), gplVector.end());
	//show(gplVector);
}

void sortEachInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplVector.push_back(string(GPL_2_text[i]));
		sort(gplVector.begin(), gplVector.end());
	}
	//show(gplVector);

}

}

namespace list_bench
{

void backInsert()
{
	list<string> gplList;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplList.push_back(string(GPL_2_text[i]));
	}

	gplList.sort();
}
void frontInsert()
{
	list<string> gplList;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplList.push_front(string(GPL_2_text[i]));
	}

	gplList.sort();
}
void sortEachInsert()
{
	list<string> gplList;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplList.push_back(string(GPL_2_text[i]));
		gplList.sort();
	}
}
}

namespace map_bench
{

void test()
{
	string str;
	map<string, int> gplMap;
	map<string, int>::iterator it;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		str = string(GPL_2_text[i]);
		it = gplMap.find(str);

		if (it != gplMap.end()){
			it->second++;
		} else {
			gplMap.insert(pair<string,int>(str,1));
		}
	}
}

}

int main (void)
{
	Timer t;

	/* VECTOR */
	cout << "Vector TB" << endl;
	t = t.start();
	vector_bench::backInsert();
	t = t.stop();
	cout << "backInsert tt: " << t << endl;

	t = t.start();
	vector_bench::frontInsert();
	t = t.stop();
	cout << "frontInsert tt: " << t << endl;

	t = t.start();
	vector_bench::sortEachInsert();
	t = t.stop();
	cout << "frontInsert tt: " << t << endl;

	/* LIST */
	cout << "List TB" << endl;
	t = t.start();
	list_bench::backInsert();
	t = t.stop();
	cout << "backInsert tt: " << t << endl;

	t = t.start();
	list_bench::frontInsert();
	t = t.stop();
	cout << "frontInsert tt: " << t << endl;

	t = t.start();
	list_bench::sortEachInsert();
	t = t.stop();
	cout << "frontInsert tt: " << t << endl;

	/* MAP */
	cout << "Map TB" << endl;
	t = t.start();
	map_bench::test();
	t = t.stop();
	cout << "map test : " << t << endl;

	return 0;
}
