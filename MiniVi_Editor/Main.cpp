#include <iostream>
#include "Editor.h"
#include "LinkedStack.h"
#include <memory>
#include <string>

using namespace std;
//template <typename Type>

int main(int argc, char* argv[])
{
	system("CLS");
	Editor miniVi(argv[1],"KeyWords.txt");	//Create an instance of Editor class using input file and keywords file
    miniVi.run();	//Invoke run function on instance of Editor class, called miniVi

	return 0;
}

