#include "Position.h"

Position::Position()//default constructor
{
}

Position::Position(int inX, int inY)//constructor sets x and y values
{
	x = inX;
	y = inY;
}

int Position::getX() const // function to return the cursor's x position
{
	return x;
}

int Position::getY() const//function to return the cursor's y position
{
	return y;
}

void Position::setX(int inX)//sets the cursor's x position
{
	x = inX;
}

void Position::setY(int inY)//sets the cursor's y position
{
	y = inY;
}