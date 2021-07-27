#ifndef _POINT_H
#define _POINT_H

class Point {
	int x = 4, y = 0;
public:
	Point(int _x = 4, int _y = 0) { x = _x; y = _y; }
	void setValue(int& x, int& y);
	Point convert(int _x, int _y) { setValue(_x, _y); return *this; } //converting integers to point type
	int getX()const;
	int getY()const;

};

#endif //_POINT_H