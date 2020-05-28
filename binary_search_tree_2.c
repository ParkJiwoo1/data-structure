#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


//void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
	printf("------[2016031032]------[Park_Jiwoo]------\n");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			//printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for (;;) {
		for (; node; node = node->left) {
			push(node);
		}
			node = pop();
		
			if (!node) {
				break;
			}
			printf(" [%d] ", node->key);
			node = node->right;
		
	}
	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) {
		return 0;
	}
	enQueue(ptr);
	for (;;) {
		ptr = deQueue();
		if (ptr) {
			printf(" [%d] ", ptr->key);
			if (ptr->left) {
				enQueue(ptr->left);
			}
			if (ptr->right) {
				enQueue(ptr->right);
			}
		}
		else
		 break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	
	if (head->left == NULL) {
		printf("node is empty\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;
	Node* parentNode = NULL;
	Node* min = NULL;
	Node* node = NULL;
	Node* tmp = NULL;
	if (ptr->key == key) {                                       //노드가 헤드노드 left node인 ptr일때
		if (ptr->left == NULL && ptr->right == NULL) {           //ptr노드가 자식노드가 없을때
			free(ptr);
			ptr = NULL;
		}
		else if (ptr->left != NULL && ptr->right == NULL) {      //ptr노드가 left node만 가질때
			head->left = ptr->left;
			free(ptr);
			ptr = NULL;
		}
		else {
			min = ptr->right;
			parentNode = min;
			if (min->left == NULL) {                         //ptr노드의 오른쪽 자식 min노드가 최소 노드일때
				head->left = min;                            //제거되는 ptr노드 자리에 min노드 삽입
				min->left = ptr->left;
				free(ptr);
				ptr = NULL;
			}
			else {
				while (min->left != NULL) {                  //ptr노드 오른쪽 자식 min이 최소 노드가 아닐경우
					parentNode = min;
					min = min->left;                         //min노드 밑에 최소노드 검색
				}
				parentNode->left = min->right;               //최소노드를 ptr자리에 삽입
				ptr->left = min->left;
				head->left = min;
				ptr->right = min->right;
				free(ptr);
				ptr = NULL;
			}
			return 0;
		}
		return 0;
	}
	else {                                 //트리의 헤드노드 left노드 밑에 있는 노드일때
		node = ptr;

		while (node->key != key) {         //key값에 해당하는 노드를 찾을때까지 검색
			parentNode = node;
			if (node->key > key) {
				node = node->left;
			}
			else if (node->key < key) {
				node = node->right;
			}
		}
		if (node->left == NULL && node->right == NULL) {           //노드가 leaf노드 일때
			free(node);
			node = NULL;
		}
		else if (node->left != NULL && node->right == NULL) {      //node 왼쪽자식이 존재할때
			if (parentNode->key > node->key) {                     //parent 노드와 node노드 자식 연결
				parentNode->left = node->left;
			}
			else {
				parentNode->right = node->left;
			}
			free(node);
			node = NULL;
		}
		else {                                                     //node의 오른쪽 자식이 존재할때
			min = node->right;
			tmp = min;
			if (min->left == NULL) {                               //parent 노드와 node노드 자식 연결
				if (parentNode->key > node->key) {                
					parentNode->left = min;
					node->left = min->left;
				}
				else {
					parentNode->right = min;
					min->left = node->left;
				}
				free(node);
				node = NULL;
			}
			else {
				while (min->left != NULL) {                      //오른쪽 자식의 최소 노드 검색
					tmp = min;
					min = min->left;
				}
				tmp->left = min->right;
				if (parentNode->key < node->key) {
					parentNode->right = min;
				}
				else {
					parentNode->left = min;
				}                                               //node위치에 최소노드 삽입
				node->right = min->right;
				node->left = min->left;
				free(node);
				node = NULL;
			}
			return 0;
		}
		return 0;
	}

	
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	
	if (top == -1) {
		return 0;
	}
	return stack[top--];               //top값을 1씩 감소시키며 stack[top]에 저장된 값 리턴
	
}

void push(Node* aNode)
{
	if (top==MAX_STACK_SIZE-1) {       //stack이 꽉찼을때 실행안함
		return 0;
	}
	else {
		top++;
		stack[top] = aNode;            //stack[0]부터 순차적으로 노드 저장
	}
}



Node* deQueue()
{
	if (front == rear) {                //front와 rear가 같으면 queue가 비었다는 뜻
		return 0;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;      
	if (front == rear) {              //front와 rear가 같으면 queue가 꽉찼다는 뜻
		return 0;
	}
	queue[rear] = aNode;
	return queue[rear];
}
