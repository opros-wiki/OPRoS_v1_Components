// queue.h: interface for the queue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct{
	int x;
	int y;
}point;

typedef struct node{
	double f;
	double g;
	double h;
	point back;
	point itself;
}node;

typedef struct qdata{
	node data;
	qdata* next;
}qdata;

class queue  
{
public:
	queue();
	virtual ~queue();

public:
	void modifyNodeData(node* ndata);
	void printdata();
	int getnodedata(node* nodedata);
	bool find(node* nd);
	unsigned int size();
	void pop(node* data);
	void push(const node* data);
	void clear();

protected:
	unsigned int qsize;
	qdata* tail;
	qdata* head;
};

#endif // _QUEUE_H_
