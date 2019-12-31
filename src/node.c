/* ================================================================== */
/* ===         Defines the basic linked list using strcutures     === */
/* ================================================================== */

#include <iostream>

typedef struct node node;
struct node
{
	int val;
	node *next;
};


//This is an example of the node structure used for implementation of linked list in C: 
struct node_struct
{
	int val;
	struct node_struct *next;
};

/* --------------------------------------------------------------- */
int main(int narg, char **arg)
{ 
	node linkedlist;
	//node_struct ll;
	node *ptr;
	
	linkedlist.val=4;
	
	printf("First linked list has been created its data field contains %d", linkedlist.val);
  

  return 0;
}



