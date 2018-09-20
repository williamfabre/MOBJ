#include <iostream>
#include "Box.h"
using namespace std;

void swap(long* a, long* b)
{
	long tmp = *a; *a = *b; *b = tmp;
}

long min(long a, long b)
{
	return (a > b) ? b : a;
}

long max(long a, long b)
{
	return (a > b) ? a : b;
}

Box::Box()
{
	name_ = "Unknow";
	x1_ = 1;
	y1_ = 1;
	x2_ = 1;
	y2_ = 1;
}

Box::Box(string name, long x1, long y1, long x2, long y2)
{
	name_ = name;
	x1_ = x1;
	y1_ = y1;
	x2_ = x2;
	y2_ = y2;
}

Box::Box(const Box& other)
{
	name_ = other.name_;
	x1_ = other.x1_;
	y1_ = other.y1_;
	x2_ = other.x2_;
	y2_ = other.y2_;
}

Box::~Box(){
	return;
}

inline bool Box::isEmpty() const
{ return (x1_ > x2_) || (y1_ > y2_); }


string Box::getName() const
{
	return name_;
}

long Box::getX1() const
{
	return x1_;
}

bool Box::intersect(const Box&) const
{
	return 0;
}

Box& Box::inflate(long dxy)
{
	x1_ -= dxy;
	y1_ -= dxy;
	x2_ += dxy;
	y2_ += dxy;
	//PROBLEM
}

Box Box::getIntersection(const Box& box) const
{
	//PROBLEM
	return Box();
}
