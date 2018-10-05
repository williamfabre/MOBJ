#ifndef _BOX_H
#define _BOX_H

/****************************************************************************/
/************************** FirstBox definition *****************************/
/****************************************************************************/


namespace tme2
{
class Box {
private:
	std::string name_;
	long x1_;
	long y1_;
	long x2_;
	long y2_;
	static int count;

public:
	/* Const */
	/*constructeur par défaut. Doit construire une boîte vide. */
	Box();
	/* constructeur ordinaire. */
	Box(std::string, long x1, long y1, long x2, long y2);
	/*constructeur par copie. Pour plus de clarté,
	  lorsqu'une boîte sera copiée on s'autorisera
	  à en modifier le nom en y ajoutant le suffixe "_c".*/
	Box(const  Box&);

	/* Dest */
	~Box();

	/* Access */
	std::string getName() const { return name_; }
	inline long getX1() const { return x1_; }
	inline long getY1() const { return y1_; }
	inline long getX2() const { return x2_; }
	inline long getY2() const { return y2_; }
	inline long getWidth() const { return this->isEmpty() ? 0 : x2_ - x1_; }
	inline long getHeight() const { return this->isEmpty() ? 0 : y2_ - y1_; }
	static int getAllocateds() { return count; }
	inline bool isEmpty() const{ return (x1_ > x2_) || (y1_ > y2_); }

	void print(std::ostream&)const;
	std::string toString() const;
	bool intersect(const Box&) const;

	/* Mutate */
	Box& makeEmpty();
	Box& inflate(long dxy);
	Box& inflate(long dx, long dy);
	Box& inflate(long dx1, long dy1, long dx2, long dy2);
	Box getIntersection(const Box&) const;
	//Box getIntersection(Box&);

	Box operator&&(Box& other);
};
}
/* Now that we have a print we need to provide the operator
 * that print our Boxes into a stream with the redirection <<
 * OVERLOAD OPERATOR, outside of the class or it won't work.
 *
 * "You want to define ostream& operator<<(ostream&, const A&)
 * as a non-member function, definitely not as a member of logic
 * since it has nothing to do with that class!"
 * https://stackoverflow.com/questions/10744787/operator-must-take-exactly-one-argument
 */
std::ostream& operator<<(std::ostream& o, const tme2::Box& box);


/****************************************************************************/
/************************** SecondBox definition ****************************/
/****************************************************************************/



namespace tme1Qf
{
class Box {
private:
	std::string name_;
	long x_;
	long y_;
	long width_;
	long height_;
	static int count;

public:
	/* Const */
	/*constructeur par défaut. Doit construire une boîte vide. */
	Box();
	/* constructeur ordinaire. */
	Box(std::string, long x, long y, long width, long height);
	/*constructeur par copie. Pour plus de clarté,
	  lorsqu'une boîte sera copiée on s'autorisera
	  à en modifier le nom en y ajoutant le suffixe "_c".*/
	Box(const  Box&);

	/* Dest */
	~Box();

	/* Access */
	std::string getName() const { return name_; }
	inline long getX() const { return x_; }
	inline long getY() const { return y_; }
	inline long getWidth() const { return width_; }
	inline long getHeight() const { return height_; }
	static int getAllocateds() { return count; }
	inline bool isEmpty() const{ return (width_ == 0) && (height_ == 0); }

	void print(std::ostream&)const;
	bool intersect(const Box&) const;

	/* Mutate */
	Box& makeEmpty();
	Box& inflate(long dxy);
	Box& inflate(long dx, long dy);
	Box& inflate(long dx1, long dy1, long dx2, long dy2);
	Box getIntersection(const Box&) const;
	//Box getIntersection(Box&);

	Box operator&&(Box& other);

};
}

std::ostream& operator<<(std::ostream& o, const tme1Qf::Box& box);

#endif

