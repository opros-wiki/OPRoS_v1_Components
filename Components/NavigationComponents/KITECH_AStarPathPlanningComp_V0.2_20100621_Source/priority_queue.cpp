#include <iostream>
#include "priority_queue.h"

priority_queue::priority_queue()
{
	head=NULL;
	tail=NULL;
	qsize=0;
}

priority_queue::~priority_queue()
{
	//queue::~queue();
}

void priority_queue::push(const node *data)
{
	qdata* temp;
	qdata* prenode;
	qdata* index;

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
		index=head;
		temp=new qdata;
		temp->data=*data;
		do{
			if( index->data.f >= temp->data.f )
			{
				prenode=findPrenode(index);
				if(prenode == NULL )
				{
					head=temp;
					temp->next=index;
				}
				else
				{
					prenode->next=temp;
					temp->next=index;
				}
				break;
			}
			else 
			{
				if( head == tail )
				{
					tail->next=temp;
					temp->next=NULL;
					tail=temp;
					break;
				}
				else if( index==tail )
				{
					tail->next=temp;
					temp->next=NULL;
					tail=temp;
					break;
				}

			}
			index=index->next;
		}while(index != NULL);
		qsize+=1;
	}
}

qdata* priority_queue::findPrenode(qdata *curnode)
{
	qdata* ret=NULL;
	qdata* temp;

	temp=head;

	do{ 
		if( temp->next == curnode )
		{
			ret=temp;
		}
		temp=temp->next;
	}while( temp != NULL );

	return ret;
}
