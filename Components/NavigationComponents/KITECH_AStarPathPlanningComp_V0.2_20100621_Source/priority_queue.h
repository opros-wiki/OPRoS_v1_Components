#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "queue.h"

class priority_queue : public queue  
{
public:
	priority_queue();
	virtual ~priority_queue();

public:
	qdata* findPrenode(qdata* curnode);
	void push(const node* data);
};

#endif // _PRIORITY_QUEUE_H_
