#include<stdio.h>
#include<stdlib.h>
#include <assert.h>

typedef struct node nodeStruct;

struct node
{
	int data;
	nodeStruct *next;
} *head = 0; //we must initialize the pointer

int sizeOfNodes = 0; //we need to initialize the counter

#define OK           0
#define ALLOC_ERROR  1
/**
 * adds the data in the last place of the list
 * @param dataToAdd the data to add
 */
int addToEnd(int dataToAdd)
{
	// Should never occur, but should be checked.
	assert(head != 0);

	nodeStruct *temp = 0, *right = 0; // better to initialize immediately
	temp = (struct node *) malloc(sizeof(struct node));

	// check if allocation succeeded
	if (temp == NULL){
		return ALLOC_ERROR;
	}

	// this line did not compile and was also not correct
	//temp->data = (int) malloc(sizeof(int));

	temp->data = dataToAdd;
	right = head; // no need for cast

	while (right->next != NULL) { // should use brackets even for one statement
		right = right->next;
	}

	right->next = temp;
	right = temp;
	right->next = NULL;

	return OK;
}

/**
 * adds the data in the first place of the list
 * @param dataToAdd the data to add
 */
int addFirst(int dataToAdd)
{
	nodeStruct *tempNode;
	tempNode = (struct node *) malloc(sizeof(struct node));

	// check that allocation succeeded
	if (tempNode == NULL){
		return ALLOC_ERROR;
	}
	/* danielle - incorrect and not used*/
	//tempNode->data = (int) malloc(sizeof(int));

	tempNode->data = dataToAdd;
	tempNode->next = head;
	head = tempNode;

	return OK;
}

/**
 * adds a new data in a given place to add
 * @param dataToAdd the data to add
 * @param placeToAdd the place to add
 */
void addInPlace(int dataToAdd, int placeToAdd)
{
	int i = 0; //danielle - we must initialize
	nodeStruct *temp, *left, *right;
	right = head;

	/*danielle - we need to initialize left*/
	left = 0;

	for (i = 1; i < placeToAdd; i++)
	{
		left = right;
		/* danielle - this should be in the loop in order to advance left and right*/
		right = right->next;
	}

	temp = (struct node *) malloc(sizeof(struct node));

	/* danielle - incorrect and not used*/
	//temp->data = (int) malloc(sizeof(int));

	temp->data = dataToAdd;

	if (left != 0)
	{
		left->next = temp;
	}
	left = temp;
	left->next = right;
	return;
}


/**
 * inserts a new data number
 * the data is inserted in ascending order, from the lowest to highest
 * @param dataToAdd the data to insert
 * @param numberOfNodes the current number of nodes
 */
void insert(int dataToAdd, int *numberOfNodes)
{
	int c = 0;
	nodeStruct *temp;
	temp = head;
	if (temp == NULL)
	{
		addFirst(dataToAdd);
	}
	else
	{
		/*danielle - I added the if condition to the while condition, because it didn't handle
	 	* the case in which we want to add a node with a number that already exists (it
	 	* caused an endless loop)*/
		while (temp != NULL && temp->data <= dataToAdd)
		{
			c++;
			temp = temp->next;
		}

		if (c == 0)
		{
			addFirst(dataToAdd);
		}

		else if (c < *numberOfNodes)
		{
			addInPlace(dataToAdd, ++c);
		}
		else
			addToEnd(dataToAdd);
	}

	(*numberOfNodes)++; //danielle - numberOfNodes++ is not good. we have to count (*numberOfNodes),
	// and not the pointer
}


/**
 * deletes the first node with the number num
 * @param dataToDelete the data to delete
 * @param numberOfNodes the number of nodes
 * @return
 */
int delete(int dataToDelete, int *numberOfNodes)
{
	nodeStruct *temp, *prev;
	temp = head;
	while (temp != NULL)
	{
		if (temp->data == dataToDelete)
		{
			if (temp == head)
			{
				head = temp->next;
				free(temp);

			}
			else
			{
				prev->next = temp->next;
				free(temp);
			}
			/*danielle - numberOfNodes++ is not good. we have to count (*numberOfNodes),
			* and not the pointer */
			(*numberOfNodes)--;
			return 1;

		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}

	return 0;
}

/**
 * should print all the nodes in the linked list in this format:
 * number of nodes: <numberOfNodes>\n
 * <firstNodeData> --> <secondNodeData> --> .... <lastNodeData>\n
 * @param startingNodeToPrint the first node to print
 */
void display(nodeStruct *startingNodeToPrint)
{
	printf("number of nodes: %d\n", sizeOfNodes);
	if (startingNodeToPrint == NULL)
	{
		return;
	}
	while (startingNodeToPrint != NULL)
	{

		printf("%d --> ", startingNodeToPrint->data);
		startingNodeToPrint = startingNodeToPrint->next;
	}
	printf("NULL\n");
}


void basicTest()
{
	int data0 = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;

	insert(data1, &sizeOfNodes);
	insert(data2, &sizeOfNodes);
	insert(data3, &sizeOfNodes);
	insert(data2, &sizeOfNodes);
	insert(data1, &sizeOfNodes);
	insert(data2, &sizeOfNodes);
	insert(data1, &sizeOfNodes);
	insert(data0, &sizeOfNodes);

	display(head);

	delete(data1, &sizeOfNodes);
	delete(data2, &sizeOfNodes);
	display(head);
	delete(data2, &sizeOfNodes);
	delete(data3, &sizeOfNodes);
	delete(data2, &sizeOfNodes);
	display(head);
	delete(data1, &sizeOfNodes);
	delete(data1, &sizeOfNodes);
	delete(data0, &sizeOfNodes);
	display(head);
}

void hardTest()
{
	for (int i = 0; i < 100; i++)
	{
		insert(i, &sizeOfNodes);
	}
	display(head);

	for (int i = 0; i < 100; i++)
	{
		insert(i, &sizeOfNodes);
	}

	display(head);
	for (int i = 0; i < 100; i++)
	{
		delete(i, &sizeOfNodes);
	}
	display(head);
	for (int i = 0; i < 100; i++)
	{
		delete(i, &sizeOfNodes);
	}
	display(head);
}

int main()
{
	basicTest();
	hardTest();

	return 0;
}