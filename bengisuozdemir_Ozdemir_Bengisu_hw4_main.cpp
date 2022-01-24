#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "bengisuozdemir_Ozdemir_Bengisu_hw4_header.h"
/*Bengisu Ozdemir 26683
The purpose of this homework is to search bit strings within given bit matrix in left and/or down directions.
Finding appropriate paths and printing them to the user.*/

using namespace std;
void printSolution(cellStruct ** myMat, int row, int col);
bool prompt(void);
bool findPos(cellStruct ** myMat, int x, int y, char bit);
bool inLimit(int x, int y, int row, int col);
void reset(CharStack &stack);
int main()
{
	int row, column;
	string fileName, bits, lines;
	cout << "Please enter the number of rows: ";
	cin >> row;
	cout << "Please enter the number of columns: ";
	cin>> column;
	cout << "Please enter the name of the input file that contains the matrix: ";
	cin >> fileName;
	ifstream input;
	input.open(fileName.c_str());
	while (input.fail())
	{//To check if the file is opened, if not take the fileName again.
		cout << "File cannot be opened." << endl << "Please enter the name of the input file again: ";
		cin.clear();
		cin >> fileName;
		input.open(fileName.c_str());
	}
	cellStruct ** myMat; //The actual matrix stack that contains the information from txt files
	CharStack myList; //The list that is to store locations of paths
	CharStack temp; //A temporary list that is to use printing stack in reverse order

	//building the informative container matrix:
	myMat = new cellStruct*[row];
	for (int i = 0; i < row; i++)
	{
		myMat[i] = new cellStruct[column];
	}
	int i = 0;
	while(getline(input, lines))
	{
		for (int j = 0; j <column; j++)
		{
			myMat[i][j].ch = lines[j];
		}
		i++;
	}
	//end of building process
	while (prompt() && cin>>bits)
	{//printing the prompt and taking inputs until cin fails.
		for (int i = 0; i < row; i++) //reinitializing all flags to false
		{
			for (int j = 0; j < column; j++)
			{
				myMat[i][j].check = false;
			}
		}
		if(myMat[0][0].ch != bits[0])
		{//if the first char of the builded matrix is no equal to first char of the string "bits" print the error message and terminate the loop
			myMat[0][0].check = true;
			cout << "The bit string " << bits << " could not be found." << endl;
			cout << "---------------------------------------------------------"<< endl;
			reset(myList);
		}
		else
		{//continuing with the second char of the string "bits"
			myList.push(0, 0); //if no error with the first char, push the locaiton to the list as (0,0)
			int x=0, y=0, len = 1; //starting row=0, starting column = 0, starting lenght= 1 since we already placed the first char of "bits"
			char bit; //to represent single char of the string "bits"
			while(len < bits.length() && myMat[0][0].check != true)
			{
				bit = bits[len];
				if(inLimit(x, y+1, row, column) && findPos(myMat, x, y+1, bit))
				{//checking if the right cell is available
					y++; //updating y-coordinate
					len++; //updating length
					myList.push(x,y); // push the available location
				}
				else
				{
					if(inLimit(x+1, y, row, column) && findPos(myMat, x+1, y, bit))
					{//checking if the bottom cell is available
						x++; //uptading x-coordinate
						len++; //updating length
						myList.push(x, y); // push the available location to the stack
					}
					else
					{//if no cell is available then mark this position to unavaliable and roll-back
						
						myMat[x][y].check = true; //marking current cell to unavailable
						myList.pop(x, y); //removing it from the stack
						myList.pop(x, y); //updating x and y to previous location /do not wanted to remove this coordinates only for relocating the pointer
						myList.push(x,y); //replacing them to the stack because we did not wanted to remove them
						len--; //since we popped, decrease the length
					}
				}
			}
			if(myMat[0][0].check == true)
			{//if cursor returns the starting point without finding any suitable path:
				cout << "The bit string " << bits << " could not be found." << endl;
				cout << "---------------------------------------------------------"<< endl;
				reset(myList);
			}
			else
			{//if there is no problem with finding path print them here
				int a, b;
				cout << "The bit string "<<bits<<" is found following these cells:"<<endl;
				//to print the stack in reverse order, the formely created temp CharStack is being used to store them and print them here
				while(!myList.isEmpty())
				{
					myList.pop(a, b);
					temp.push(a, b);
				}
				while(!temp.isEmpty())
				{
					temp.pop(a, b);
					cout << "("<<a<<"," << b << ") ";
				}
				cout << endl <<"---------------------------------------------------------"<< endl;
			}
		}
	}
	if(cin.fail())
	{//if the input does not fail and user types CTRL+Z, terminate the program
		cout << "Program ended successfully!" <<endl<<endl;
		return 0;
	}
	//deleting the container matrix. Beginning: Taken by matrixnoclass.cpp
	for (int i = 0; i < row; i++)
		delete [] myMat[i];
	delete [] myMat;
	//Ending: matrixnoclass.cpp
	return 0;
}
bool inLimit(int x, int y, int row, int col)
{//To check if x and y values in limits of row and column values
	if(x>= 0 && x<row && y>=0 && y<col)
		return true;
	return false;
}
bool findPos(cellStruct ** myMat, int x, int y, char bit)
{//To check if the position has the same bit value with the string and to check the flags of this position
	if(myMat[x][y].check == false && myMat[x][y].ch == bit)
		return true;
	else
		return false;
}
bool prompt(void)
{//To print repetetive prompt
	cout << "Please enter a string of bits to search (CTRL+Z to quit): ";
	return true;
}
void reset(CharStack &stack)
{//To reset stack
	int x,y;
	while(!stack.isEmpty())
	{
		stack.pop(x, y);
	}
}