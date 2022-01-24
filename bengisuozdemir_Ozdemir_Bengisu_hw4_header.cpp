#include "bengisuozdemir_Ozdemir_Bengisu_hw4_header.h"
CharStack::CharStack()
{//Constructor
	top = NULL;
}
CharStack::~CharStack()
{//Destructer
	int a=0, b=0;
	while(!isEmpty())
	{
		pop(a,b);
	}
}
void CharStack::push(int x, int y)
{//beginning: taken from stacksqueues slide page 23.
	StackNode * ptr;
	ptr = new StackNode(position(x, y), nullptr);
	if(isEmpty())
	{
		top = ptr;
		ptr->next = nullptr;
	}
	else
	{
		ptr->next = top;
		top = ptr;
	}

}//ending: stacksqueues slide page 23.
bool CharStack::isEmpty()
{//beginning: taken from stacksqueues slide page 25.
	if(top==nullptr)
	{return true;}
	else
	{return false;}
}//ending: stacksqueues slide page 25.
void CharStack::pop(int &x, int &y)
{//beginning: taken from stacksqueues slide page 24. Modified by Bengisu Ozdemir.
	StackNode * temp;
	if(isEmpty())
	{/*stack is empty, nothing to pop*/}
	else
	{
		x = top->pos.x;
		y = top->pos.y;
		temp = top->next;
		delete top;
		top = temp;
	}
}//ending: stacksqueues slide page 24.