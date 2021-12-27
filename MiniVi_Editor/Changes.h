#include <string>
#include "Position.h"

using namespace std;

class Changes 
{
private:
	Position undoPos; // X and Y coordinates before making any changes
	string lineBeforeChanges; //the unchanged string
	char command; //command that was typed ('x' or 'd')

public:
	Changes(); //default constructor 
	Changes(string lineBeforeChanges, char command, Position undoPos); // constructor that takes in the string that was changed, the command typed, and userPosition
	void setLine(string lineBeforeChanges); //set function that takes in a line
	void setCommand(char commandUsed); //set function for command
	void setPos(Position undoPos); // set function for position
	char getCommand() const; // get function for command that was typed
	string getLineBefore() const; // get function for string 
	Position getUndoPos() const; // get function for position

};
