#pragma once
#include <string>
#include "LinkedList.h"
#include "Position.h"
#include "Changes.h"
#include "LinkedStack.h"
#include "BinarySearchTree.h"

using namespace std;

class Editor
{
private:

	string fileName;	//variable for input file name
	//string keyWords[60];	//array of 60 keywords
	int length;		// variable to store the length of the array
	LinkedList <string> lines;  //String instance of LinkedList
	int numKeywords = 0; //Stores the number of keywords
	Position userPosition;		//Instance of Position that stores cursor coordinates
	const char exit = ':';		//variable that stores exit char
	const char removeChar = 'x';	//variable that stores delete char
	LinkedStack <Changes> undoStack; //Stack to store changes for the undo function 
	BinaryNodeTree <string> keyWordTree; //Instance of binary tree

public:

	Editor();	//default constructor
	Editor(string _fileName, const string _fileName2);	//constructor to initialize length, file, and array
	void colorText(int value);
	void displayLines();	//Prints out the contents of the input file
	void placeCursorAt(Position coordinate);	//function to set the user's cursor in desired location
	void run();		 //displays lines and checks for user input
	void writeToFile(string _fileName2);//Saves changes made
	void moveUp(); //Functions to move up, down, left, right
	void moveDown();
	void moveLeft();
	void moveRight();
	void deleteLine(); //function to delete current line
	void undo(); //Function to undo most recent change 

}; 
