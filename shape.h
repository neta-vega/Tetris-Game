#ifndef _SHAPE_H
#define _SHAPE_H

#include "point.h"
enum Input; 
class Board;
class Point;

class Shape {
	int height, width;
	Point coordinate;
	bool canMove = true;
	Point point_arr[4];
	Point prev_point_arr[4];
	int which_shape;
public:
	int getWhichShape() const { return which_shape; }
	void setWhichShape(int which) { which_shape = which; }
	Point* getPointArr() { return point_arr; }
	void setPointArr(Point p1, Point p2, Point p3, Point p4);
	Point* getPrevPointArr() { return prev_point_arr; }
	void setPrevPointArr(Point p1, Point p2, Point p3, Point p4);
	int getHeight();
	int getWidth();
	void setHeightWidth(const int& h, const int& w);
	char curr_shape[4][4];
	char prev_shape[4][4];
	void generateShapes(int random);
	void rotate(Shape& actual_shape, Board& board, Input direction);
	void savePrevShape(Shape& actual_shape);
	int firstOccurenceOfCurrShapeK(Shape& curr_shape);
	int firstOccurenceOfCurrShapeL(Shape& curr_shape);
	void ableToMove(Shape& curr_shape, Board& board);
	bool getCanMove() const { return canMove; };
	void setCanMove(bool& _canMove) { canMove = _canMove; };
	int getCoordinateX() { return coordinate.getX(); }
	int getCoordinateY() { return coordinate.getY(); }
	void setCoordinate(int& _x, int& _y) { coordinate.setValue(_x, _y); }
};

#endif //_SHAPE_H
