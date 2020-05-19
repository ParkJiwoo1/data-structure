#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
printf("-----[Park_Jiwoo]-----[2016031032]");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	(*h)->left = NULL;	/* head */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)

{
	if(ptr == NULL)                   //leaf노드에서 left,right검색 시 NULL일 경우 부모 노드 복귀
		return 0;
	inorderTraversal(ptr->left);      //트리 왼쪽 노드부터 우선적 검색
	printf("[%d]", ptr->key);
	inorderTraversal(ptr->right);     //왼쪽 노드 이후 부모 노드 후 오른쪽 노드
}

void preorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return 0;
	printf("[%d]", ptr->key);
	preorderTraversal(ptr->left);
	preorderTraversal(ptr->right);     //부모노드, 왼쪽 자식, 오른쪽 자식 순으로 검색
}

void postorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return 0;
	postorderTraversal(ptr->left);
	postorderTraversal(ptr->right);
	printf("[%d]", ptr->key);          //왼쪽 자식, 오른쪽 자식, 부모 순으로 검색
}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	
	if (head->left == NULL) {       //초기 head노드만 있을경우
		head->left = node;
		return 0;
	}
	else {
		Node* n = head->left;
		
		while (n->left != NULL || n->right != NULL) {     //leaf노드에 도달할때까지
			if (n->key > key) {
				n = n->left;
			}
			else {
				n = n->right;
			}
		}                                 //head부터 노드가 삽입될 leaf노드 검색
		if (n->key > key) {
			n->left = node;
		}
		else {
			n->right = node;
		}                               //key값 비교로 leaf노드의 삽입방향 설정
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* n = head->left;
	Node* tmp=NULL;
	do {
		tmp = n;                                      //tmp는 n의 부모노드가 되도록
		if (n->key > key) {
			n = n->left;

		}
		else {
			n = n->right;
		}
	} while (n->left != NULL || n->right != NULL);      //n노드가 leaf노드에 도달할때까지
	if (n->key==key) {
		if (tmp->key < key) {
			printf("leaf node [%d] deleted", n->key);
			tmp->right == NULL;
			free(tmp->right);                          //삭제 후 메모리 해제
		}
		else {
			printf("leaf node [%d] deleted", n->key);
			tmp->left = NULL;
			free(tmp->left);
		}
		return 0;
	}
	else {
		printf("[%d]is not leaf node", n->key);         //찾는 key값이 없다면
		return 0;
	}

}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr == NULL)                         //leaf노드에서 검색했을때 노드반환
		return NULL;
	if (ptr->key == key)
		return ptr;
	else if (ptr->key > key)                 //key값으로 왼쪽,오른쪽 검색 방향 재귀적으로 검색
		return searchRecursive(ptr->left, key);
	else
		return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	if (head->key == -9999) {                       
		return searchIterative(head->left, key);   //head노드의 left노드에서 시작되므로
	}

	if (head == NULL)
		return NULL;
	if (head->key == key)
		return head;
	else if (head->key > key)
		return searchIterative(head->left, key);
	else
		return searchIterative(head->right, key);
}


int freeBST(Node* head)
{
	while (1) {
		if (head == NULL) {
			break;
		}
		else if (head->left != NULL) {
			freeBST(head->left);
			head->left = NULL;
		}
		else if (head->right != NULL) {
			freeBST(head->right);
			head->right = NULL;
		}
		else {
			free(head);
			return;
		}
	}
}
