#include "Changes.h"
#include <string>



Changes::Changes() // default constructor
{
}

Changes::Changes(string lineBefore, char commandUsed, Position previousPos)
{
	lineBeforeChanges = lineBefore; 
	command = commandUsed;
	undoPos = previousPos;
}

void Changes::setLine (string lineBefore) //sets the line that was passed as a parameter
{
	lineBeforeChanges = lineBefore;
}

void Changes::setCommand(char commandUsed) //sets the command that was used
{
	command = commandUsed;
}

void Changes::setPos(Position previousPos) //sets the position before any changes was done 
{
	undoPos = previousPos;
}

char Changes::getCommand() const //gets the command that was used
{
	return command;
}

string Changes::getLineBefore() const //get the line that was changed
{
	return lineBeforeChanges;
}

Position Changes::getUndoPos() const //gets the position before making changes 
{
	return undoPos;
}
