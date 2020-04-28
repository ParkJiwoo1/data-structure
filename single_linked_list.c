#include<stdio.h>
#include<stdlib.h>

/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �⑥닔 由ъ뒪�� */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
	printf("-----[2016031032]----[Park_Jiwoo]----\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	
	if (h != NULL)
		freeList(h);

	
	headNode* temp = (headNode*)malloc(sizeof(headNode));    //Head node 생성
	temp->first = NULL;                                      //Head node초기값 NULL설정
	return temp;
}

int freeList(headNode* h) {
	
	listNode* p = h->first;                                   //p는 초기 Head node부터

	listNode* prev = NULL;
	while (p != NULL) {                                      //p를 리스트 끝까지 검색
		prev = p;
		p = p->link;                                         //link를 따라 리스트 이어감
		free(prev);                                          //list를 순차적으로 free시켜줌
	}
	free(h);                                                 //마지막 Head node free
	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;          

	node->link = h->first;                                 //Head node 앞에 노드 배치
	h->first = node;

	return 0;
}


int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) {
		h->first = node;
		return 0;
	}
	listNode* cur = h->first;
	listNode* tail = h->first;
	
	while (cur != NULL) {
		if (cur->key >= key) {                   //key값 순으로 배치해야 하기 때문에
			if (cur==node) {                     
				h->first = node;                 //Head노드에 node노드값 줌
				node->link = cur->link;          //Head노드 link가 node노드 link와 동일
			}
			else {
				node->link = cur;               //node노드 다음 cur노드 연결
				tail->link = node;              //tail노드 다음 node노드 연결
	
			}
			return 0;
		}
		tail = cur;                              //tail노드에 cur노드 정보 저장
		cur = cur->link;                         //cur노드를 다음노드로 넘어감
	}
	tail->link = node;                           //key값이 cur->key값보다 크면 순서대로 link에 연결
	return 0;
}


int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) {
		h->first = node;
	}
	listNode* cur = h->first;
	while (cur->link != NULL) {
		cur = cur->link;                         //cur노드를 마지막 노드 가리키도록 이동
	}
	cur->link = node;                            //마지막 노드 다음이 node노드가 되도록 배치
	return 0;
}



int deleteFirst(headNode* h) {
	if (h->first == NULL) {
		printf("can not be deleted\n");
	}
	listNode* cur = h->first;                     //Head노드 값이 NULL이될 임시노드 할당
	h->first = cur->link;                         //cur노드 link가 Head node가 가리키도록 함
	free(cur);                                    //임시노드 해제
	return 0;
}


int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {
		printf("can not be deleted\n");
	}
	listNode* cur = h->first;
	listNode* tail = NULL;
	
	while (cur != NULL) {
		if (cur->key == key) {
			if (cur == h->first) {                
				h->first = cur->link;             //cur노드가 Head노드와 같을때 cur노드 link가 Head노드 가리키게 함
			}
			else {
				tail->link = cur->link;           //원래 tail노드 link가 cur노드였으나 cur노드의 link가 tail노드의 link가 되도록 설정
			}
			free(cur);
			return 0;
		}
		tail = cur;                               //cur노드 tail에 임시저장
		cur = cur->link;                          //cur노드 다음 노드로 이동
	}
	
	return 0;

}


int deleteLast(headNode* h) {
	if (h->first == NULL) {
		printf("can not be deleted");
	}
	listNode* cur = h->first;
	listNode* tail = NULL;

	if (cur->link == NULL) {
		h->first = NULL;                          //Head노드 혼자있을경우
		free(cur);
	}
	while (cur->link != NULL) {
		tail = cur;                    
		cur = cur->link;                         //cur노드가 마지막이 아닌경우 다음노드로 이동
	}
	tail->link = NULL;
	free(cur);
	return 0;
}



int invertList(headNode* h) {
	if (h->first == NULL) {
		printf("can not be moved");
	}
	listNode* cur = h->first;
	listNode* tail = NULL;
	listNode* tmp = NULL;

	while (cur != NULL) {                       //swap형식 이용해 순서를 반대로하여 invert
		tail = tmp;
		tmp = cur;
		cur = cur->link;
		tmp->link = tail;
	}
	h->first = tmp;
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}