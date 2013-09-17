#ifndef _STACK_H_
#define _STACK_H_

#include "priority_queue.h"

class stack : public priority_queue  
{
public:
	stack();
	virtual ~stack();

public:
	void push(const node* data);
	void pop(node *data);
};

#endif // _STACK_H_