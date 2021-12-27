
#pragma once
class Position
{
private://cursor's x and y position values
	int x;
	int y;

public:
	Position();//default constructor
	Position(int inX, int inY);//constructor sets x and y values
	void setX(int inX);//sets user's x values
	void setY(int inY);//sets user's y values
	int getX() const;//obtains user's x value
	int getY() const;//obtains user's y value
};
