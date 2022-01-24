#ifndef bengisuozdemir_Ozdemir_Bengisu_hw4_header_h
#define bengisuozdemir_Ozdemir_Bengisu_hw4_header_h
#include <iostream>
#include <string>
using namespace std;
struct cellStruct
{
	char ch;
	bool check;
	//default constructor
	cellStruct()
		:ch(), check()
	{}
	//constructor
	cellStruct (char ch,bool check)
		:ch(0), check(false)
	{}
};
struct position
{
	int x;
	int y;
	//default constructor
	position()
		:x(),y()
	{}
	//constructor
	position(int _x, int _y)
		:x(_x), y(_y)
	{}
};
struct StackNode
{
	position pos;
	StackNode * next;
	//default constructor
	StackNode()
		:pos(), next()
	{}
	//constructorlisteye 
	StackNode (position pos,StackNode* next)
		:pos(pos.x, pos.y), next(nullptr)
	{}
};
class CharStack
{
private:
	StackNode * top;

public:
	CharStack(); //Constructor
	~CharStack(); //Destructor
	void push(int x, int y); //To push intigers to the stack
	void pop(int &x, int &y); //To pop intigers from the stack
	bool isEmpty(); //To check is the stack is empty
};
#endif bengisuozdemir_Ozdemir_Bengisu_hw4_header_h