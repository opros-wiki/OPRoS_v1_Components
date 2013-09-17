#include <iostream>
#include "queue.h"

using namespace std;

queue::queue()
{
	head=NULL;
	tail=NULL;
	qsize=0;
}

queue::~queue()
{
	qdata* temp;

	while(qsize!=0)
	{
		temp=head->next;
		delete head;
		head=temp;
		qsize-=1;
	}
}

void queue::push(const node *data)
{
	qdata* temp;

	if(qsize==0)
	{
		head=new qdata;
		head->data=*data;
		tail=head;
		head->next=NULL;
		qsize+=1;
	}
	else
	{
		temp=new qdata;
		temp->data=*data;
		tail->next=temp;
		tail=temp;
		tail->next=NULL;
		qsize+=1;
	}
}

void queue::pop(node *data)
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
		temp=head->next;
		data->f=head->data.f;
		data->g=head->data.g;
		data->h=head->data.h;
		data->back=head->data.back;
		data->itself=head->data.itself;

		delete head;
		head=temp;
		qsize-=1;
	}
}

unsigned int queue::size()
{
	return qsize;
}

bool queue::find(node* nd)
{
	bool ret=0;
	qdata *p;

	if(head == NULL || qsize == 0) return 0;

	p = head;
	while(p != NULL) {
		if((p->data.itself.x == nd->itself.x) && (p->data.itself.y == nd->itself.y)) {
			*nd = p->data;
			ret = 1;
			return 1;
		}
		p = p->next;
	}

	return ret;
}


int queue::getnodedata(node *nodedata)
{
	int ret=0;
	qdata* temp;

	temp=head;

	do{ 
		if( (temp->data.itself.x == nodedata->itself.x )&&( temp->data.itself.y==nodedata->itself.y ) )
		{
			ret=1;
			*nodedata=temp->data;
		}
		temp=temp->next;
	}while( temp != NULL );

	return ret;
}

void queue::printdata()
{
	node temp;
	qdata* index;
	
	index=head;

	while( index != NULL )
	{
		temp=index->data;
		cout<<"itself pointer :  "<< temp.itself.x << "     "<<temp.itself.y<<"   "<<"back Pointer:  "<<temp.back.x<< "    " << temp.back.y << endl;
		index=index->next;
	}
}

void queue::modifyNodeData(node *ndata)
{
	qdata* temp;

	temp=head;
	
	while( temp != NULL )
	{
		if( qsize == 0 ) break;
		if( (temp->data.itself.x == ndata->itself.x )&&( temp->data.itself.y==ndata->itself.y ) )
		{
			temp->data=*ndata;
			break;
		}
		temp=temp->next;
	}

}
void queue::clear()
{
	node temp;

	if( size() == 0 ) {
		head = NULL;
		tail = NULL;
	}
	else{
		while( size() ) pop(&temp);
	}
}
