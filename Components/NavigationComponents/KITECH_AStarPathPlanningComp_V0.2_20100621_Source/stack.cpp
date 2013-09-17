#include <iostream>
#include "stack.h"

stack::stack()
{
	head=NULL;
	tail=NULL;
	qsize=0;
}

stack::~stack()
{
	//queue::~queue();
}

void stack::pop(node *data)
{
	qdata* temp;

	if(qsize==0)
	{
		data->f=-1;
		data->g=-1;
		data->h=-1;
	}
	else
	{
		temp=findPrenode(tail);
		data->f=tail->data.f;
		data->g=tail->data.g;
		data->h=tail->data.h;
		data->back=tail->data.back;
		data->itself=tail->data.itself;

		delete tail;
		tail=temp;
		if( tail == NULL) ;
		else tail->next=NULL;
		qsize-=1;
	}
}

void stack::push(const node *data)
{
	queue::push(data);
}
