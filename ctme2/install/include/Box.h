class Box {
public:
	Box();
	Box(std::string name, long x1, long y1, long y2);
	box(const Box&);
	~Box();
	inline bool isEmpty() const;
	std::string getName() const;
	long getX1() const;
	bool intersect(const Box&) const;
	Box& inflate(long dxy);
	Box getIntersection(const Box&) const;

private:
	std::string name_;
	long x1_;
	long y1_;
	long x2_;
	long y2_;
};
