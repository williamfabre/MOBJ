#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "Timer.h"
#include "GPL_2_text.h"

using namespace std;

template<typename T>
void show(T gpl)
{
	cout << "size() : " << gpl.size() << endl;
	cout << "max_size() : " << gpl.max_size() << endl;
	//cout << "capacity() : " << gpl.capacity() << endl;
	typename T::const_iterator p;

	for (p = gpl.begin(); p != gpl.end(); ++p){
	// for (string s : gpl){
		cout << *p << " ";
	}
	cout << endl;
}


namespace vector_bench
{

void backInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplVector.push_back(string(GPL_2_text[i]));
	}

	sort(gplVector.begin(), gplVector.end());


	cout << "capacity() : " << gplVector.capacity() << endl;
	//show<vector<string>>(gplVector);

}

void frontInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++)
	{
		gplVector.insert(gplVector.begin(), GPL_2_text[i]);
	}

	sort(gplVector.begin(), gplVector.end());
	//show<vector<string>>(gplVector);
}

void sortEachInsert()
{
	vector<string> gplVector;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplVector.push_back(string(GPL_2_text[i]));
		sort(gplVector.begin(), gplVector.end());
	}
	//show<vector<string>>(gplVector);
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

	//show<list<string>>(gplList);
}
void frontInsert()
{
	list<string> gplList;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplList.push_front(string(GPL_2_text[i]));
	}

	gplList.sort();
	//show<list<string>>(gplList);
}
void sortEachInsert()
{
	list<string> gplList;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		gplList.push_back(string(GPL_2_text[i]));
		gplList.sort();
	}
	//show<list<string>>(gplList);
}
}

namespace map_bench
{

class CompareString2
{
public:
	bool operator() (string v1, string v2)
	{
		//return !(std::lexicographical_compare(v1.begin(), v1.end(),
					 //v2.begin(), v2.end()));
		return (v1 > v2);
	}
};


struct CompareString
{
	bool operator() (string v1, string v2)
	{
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
		return std::lexicographical_compare(v1.begin(), v1.end(),
					 v2.begin(), v2.end());
	}
};

void test()
{
	string str;
	string res;
	int sum = 0;
	map<string, int> gplMap;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		str = string(GPL_2_text[i]);
		//it = gplMap.contains(str);
		map<string, int>::iterator it = gplMap.find(str);

		if (it != gplMap.end()){

			it->second++;
		} else {
			gplMap.insert(pair<string,int>(str, 1));
		}
	}

	for (map<string, int>::iterator it = gplMap.begin(); it != gplMap.end(); ++it) {
		sum += it->second;
		res += " " + it->first;
	}
	cout << "Total number of words :" << sum << endl;
	cout << res << endl;
}

/* This function will use the CompareString */
void testCustom()
{
	string str;
	string res;
	int sum = 0;
	map<string, int, CompareString> gplMap;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		str = string(GPL_2_text[i]);
		//it = gplMap.contains(str);
		map<string, int>::iterator it = gplMap.find(str);

		if (it != gplMap.end()){

			it->second++;
		} else {
			gplMap.insert(pair<string,int>(str, 1));
		}
	}

	for (map<string, int>::iterator it = gplMap.begin(); it != gplMap.end(); ++it) {
		sum += it->second;
		res += " " + it->first;
	}
	cout << "Total number of words :" << sum << endl;
	cout << res << endl;
}

void testCustom2()
{
	string str;
	string res;
	int sum = 0;
	map<string, int, CompareString2> gplMap;

	for (int i = 0; GPL_2_text[i] != NULL; i++){
		str = string(GPL_2_text[i]);
		//it = gplMap.contains(str);
		map<string, int>::iterator it = gplMap.find(str);

		if (it != gplMap.end()){

			it->second++;
		} else {
			gplMap.insert(pair<string,int>(str, 1));
		}
	}

	for (map<string, int>::iterator it = gplMap.begin(); it != gplMap.end(); ++it) {
		sum += it->second;
		res += " " + it->first;
	}
	cout << "Total number of words :" << sum << endl;
	cout << res << endl;
}


}


int main (void)
{
	Timer t;

	//VECTOR
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
	cout << "backInsert && Sort each tt: " << t << endl;

	//LIST
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
	cout << "frontInsert && sort each tt: " << t << endl;

	//MAP
	cout << "Map TB" << endl;
	t = t.start();
	map_bench::test();
	t = t.stop();
	cout << "map test : " << t << endl;
	t = t.start();
	map_bench::testCustom();
	t = t.stop();
	cout << "map test with custom, CompareString: " << t << endl;
	cout << endl;
	t = t.start();
	map_bench::testCustom2();
	t = t.stop();
	cout << "map test with custom, CompareString2: " << t << endl;



	return 0;
}
