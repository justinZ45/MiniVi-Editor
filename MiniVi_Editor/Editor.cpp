#include <fstream>
#include "Editor.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

Editor::Editor()
{
}//Editor default constructor ends

Editor::Editor(string _fileName, const string _fileName2) //Constructor to initialize aray, and two files
{
	ifstream inFile(_fileName);
	string line;
	fileName = _fileName; //Set parameter file to fileName variable
	int count = 1;

	if (!inFile)
	{
		cout << "There was an error opening the file."; //Error message if file cannot be opened
	}

	while (!inFile.eof())//Reads until end of file and inserts contents into instance of LinkedList called lines
	{
		getline(inFile, line);
		lines.insert(count, line);//Obtains each line and inserts it into the nodes of lines
		count++;
	}
	inFile.close();

	ifstream in(_fileName2); //Opens second file (keyword)


	string key;

	while (!in.eof()) //While file open, add keywords to binary tree
	{
		getline(in, key);
		keyWordTree.add(key);
	}
	
}

void Editor::colorText(int value) { //Function to color text, will be used to color keywords

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value + 240);

}
void Editor::displayLines() //Updated displayLines funcion, now utilizes binary search to color keywords in the input file
{
	int position;
	string nextLine, nextWord, line;


	// goes through each line in the linked list 
	for (position = 1; position <= lines.getLength(); position++)
	{
		nextLine = lines.getEntry(position);

		int i = 0;
		while (i < nextLine.length()) {
			string word;
			// isolate a word at a time (can contain underscores)
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;
				}
				if (keyWordTree.contains(word)==true)  //found in tree, so color word
					colorText(4);
				else
					colorText(0);
				cout << word;
			}

			else {
				colorText(0);
				cout << nextLine[i];
				i++;
			}

		}

		cout << endl;
	}
	placeCursorAt(userPosition);
} // end displayLines

void Editor::placeCursorAt(Position coordinate) { //function to set a user's cursor location to desired position

	COORD coord;

	coord.X = coordinate.getX();//gets cursor's X value

	coord.Y = coordinate.getY();//gets cursor's Y value

	SetConsoleCursorPosition(

		GetStdHandle(STD_OUTPUT_HANDLE), //Windows function

		coord);
}

void Editor::writeToFile(string _fileName2)//Function to write to original file in order to save the changes made
{
	ofstream outFile(_fileName2);//ofstream for the output
	for (int i = 1; i < lines.getLength() + 1; i++)//For-loop to traverse original nodes and rewrite original file 
	{
		outFile << lines.getEntry(i) << "\n"; // takes entries from nodes and puts in the text file 
	}
}

void Editor::moveDown() //function to move cursor down 
{
	int down = userPosition.getY(); // gets the Y coordinate of the user position 

	string curLine = lines.getEntry(down + 1); // get the current line of the user

	string nextLine = lines.getEntry(down + 2); // gets the next line from where the user is 


	if (down != lines.getLength() - 1) // checks to make sure the user does not go out of bounds
	{
		if (nextLine.length() < curLine.length() && userPosition.getX() > nextLine.length()) //Checks if the next line is shorter than the current one, and checks if the current x position is greater than the length of the next line
		{
			placeCursorAt(Position(nextLine.length() - 1, down + 1)); //Move the cursor to the end of the next line
			userPosition.setX(nextLine.length() - 1);
			userPosition.setY(down + 1);

		}
		else
		{
			userPosition.setY(down + 1); //Increase the user's y position by 1
			placeCursorAt(Position(userPosition.getX(), userPosition.getY())); //Place cursor at the new position
		}
	}
}

void Editor::moveUp()
{

	int up = userPosition.getY(); // gets the Y position of the userposition and sets it to a variable named up

	string curLine = lines.getEntry(up + 1); //gets the entry of the current line the user is at


	if (up != 0) //prevents the user from going out of bounds
	{
		string prevLine = lines.getEntry(up); //gets the entry of the line before the current one the user is at 
		if (prevLine.length() < curLine.length() && userPosition.getX() > prevLine.length()) //If the current line is longer than the previous, and the current x position is greater than the length, the if statement will run
		{
			placeCursorAt(Position(prevLine.length() - 1, up - 1)); //places the cursor at the end of the previous line
			userPosition.setX(prevLine.length() - 1); // sets the X position as the end of the previous line
			userPosition.setY(up - 1);

		}
		else //if there is a character above the one the user is currently at it will just move up
		{
			userPosition.setY(up - 1); //sets Y 
			placeCursorAt(Position(userPosition.getX(), userPosition.getY())); // places the cursor at the position above
		}
	}
}

void Editor::moveLeft()  //function to move the cursor to the left
{
	int left = userPosition.getX();  //gets the user's x position

	if (left != 0)  //checks if the user is out of bounds
	{
		userPosition.setX(left - 1); //sets the cursor's x position to the left 
	}
	placeCursorAt(userPosition); //Places the cursor at the new user position
}

void Editor::moveRight() //function to move the cursor to the right
{
	int right = userPosition.getX(); //Sets variable to the user's current x position
	string move = lines.getEntry(userPosition.getY() + 1);
	if (right != move.length() - 1)
	{
		userPosition.setX(right + 1); //Change the x position to the right once
	}
	placeCursorAt(userPosition); //Place at new cursor position
}

Changes snapShot; //Instance of Changes, that will hold the command, line before any changes, and user position for the undo function
void Editor::deleteLine()
{
	if (_getch() == 'd') // reads in the character d once more 
	{
		int remPosition = userPosition.getY() + 1; // gets the Y coordinate of the line that the user wants to delete 
		string remLine = lines.getEntry(userPosition.getY() + 1); //Creates a string set to the line that will be removed
		snapShot.setLine(remLine); //Uses snapShot to set the line before it is changed 
		lines.remove(remPosition); // removes that line
		snapShot.setCommand('d'); //Sets the command used in snapShot
		system("CLS"); // clears screen 
		displayLines();//Displays the file again
		userPosition.setX(userPosition.getX());
		userPosition.setY(userPosition.getY());
		placeCursorAt(userPosition); //Places the cursor at the user's position
		snapShot.setPos(userPosition); //Sets the userPosition in snapShot, where changes were made
		undoStack.push(snapShot); //Pushes snapShot onto the stack 
	}
}

void Editor::undo()
{
	if (undoStack.isEmpty() == false)//Checks if stack is empty
	{
		snapShot = undoStack.peek(); //Sets snapShot to the stop of stack
		if (snapShot.getCommand() == 'x') //checks to see if the command entered was a 'x'
		{
			userPosition = snapShot.getUndoPos(); //gets the X and Y values of position before changes were made
			placeCursorAt(snapShot.getUndoPos()); //places the cursor at the position that was saved previously
			system("CLS"); //clears the terminal
			lines.remove(userPosition.getY() + 1); //removes the line by getting the Y value of the userPosition
			lines.insert(userPosition.getY() + 1, snapShot.getLineBefore()); //inserts previous line into the linkedList
		}

		else if (snapShot.getCommand() == 'd') //checks if the command entered was a 'd'
		{
			userPosition = snapShot.getUndoPos(); //gets the X and Y values of position before changes were made
			placeCursorAt(snapShot.getUndoPos()); //places the cursor at the position that was saved previously
			system("CLS"); //Clears the screen
			lines.insert(userPosition.getY() + 1, snapShot.getLineBefore()); //inserts the unchanged line into the linked list
		}
		displayLines(); //displays lines
		undoStack.pop();//pop snapShot off of stack
	}
	else
	{
		placeCursorAt(Position(0, lines.getLength() + 3)); //If stack is empty, place cursor below text
		cout << "There is nothing left to undo."; //Print out message
	}
}

void Editor::run()//Function to display lines and also check for various user input
{

	placeCursorAt(Position(0, 0));
	userPosition.setX(0);
	userPosition.setY(0);
	displayLines();//Invoke displayLine function
	bool run = true;
	int bottom = lines.getLength() + 3;//Variable to set the cursor below the displayed lines
	bool change = false;
	while (run)//while loop that runs until the program is quit
	{
		char loop = _getch();
		switch (loop)//switch statement to check for movement input (navigation)
		{
		case 'j': //case for move down
			moveDown();
			break;
		case 'k': // case for move up 
			moveUp();
			break;
		case 'h':
			moveLeft(); // case for move left 
			break;
		case 'l':
			moveRight(); // case for move right 
			break;
		case 'u':
			undo(); //Calls the undo function when the user inputs 'u'
			break;
		}
		if (loop == ':')
		{
			placeCursorAt(Position(0, lines.getLength()+5));//Place the cursor below the displayed lines
			cout << ':';
			char input = _getche(); //Receives user's input and echos it to the screen
			if (input == 'q')  //checks if user input is 'q'
			{
				if (change == false)//If the user did not change anything in the file, the program will end
				{
					return;
				}
				else if (change == true) // If the user did make changes, the program will check for additional input
				{
					cout << "  Your changes will not be saved (add ! to override, press enter to abort) "; //Message output to the user
					string ans2;
					getline(cin, ans2); // reads in ans2

					if (ans2 == "!") // if ! then program ends
					{
						return;
					}
					if (ans2 == "") // if ENTER is pressed
					{
						system("CLS"); // clears system 
						displayLines(); // displays lines
						placeCursorAt(userPosition); // puts cursor at user position 
					}
				}

			}
			else if (input == 'w')//If the input is w, the file's contents are displayed
			{
				cout << endl;
				bottom += 5;//Increase the value of the bottom coordinate
				placeCursorAt(Position(0, 0));//Return the cursor to (0,0)
				userPosition.setX(0);
				userPosition.setY(0);
				writeToFile("Input.txt");//Saves changes made
				change = false; //change is false, since alterations were saved
			}
		}
		else if (loop == 'x')//Checks if the user enters 'x'
		{
			int count = userPosition.getY() - (userPosition.getY() - 1);
			placeCursorAt(userPosition);
			snapShot.setPos(userPosition); //sets the previous user position in snapShot
			string stringEdit = lines.getEntry(userPosition.getY() + 1);//Creates a string that is set to the first node of list
			//char charRemove = stringEdit.at(userPosition.getX()); //Obtains the char that will be deleted
			//string Remove(1, charRemove); //converts that char to a string, so it can be stored in snapShot
			string remCharLine = lines.getEntry(userPosition.getY() + 1); //gets the line that will have the character removed
			snapShot.setLine(remCharLine); //Sets the unchanged line in snapShot
		    stringEdit.erase(userPosition.getX(), count); //Erases the first character of the string
			/*snapShot.setLine(Remove);*/
			snapShot.setCommand('x'); //Sets the command that the user entered in snapShot
			lines.replace(userPosition.getY() + 1, stringEdit);//Replaces the first node with tthe edited string
			change = true; //Changes were made
			system("CLS"); //clears the screen
			displayLines(); //Print out the new edited file
			undoStack.push(snapShot);//pushes snapShot onto the stack
		}

		else if (loop == 'd') //Checks if d is entered once
		{
			deleteLine(); //Calls delete line
			change = true; //changes were made, so the change variable becomes true
		}

	}
}


