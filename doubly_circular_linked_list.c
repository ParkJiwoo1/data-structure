#include<stdio.h>
#include<stdlib.h>
/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �⑥닔 由ъ뒪�� */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;
	    printf("[--------[Park_jiwoo]--------[2016031032]--------]");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
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


int initialize(listNode** h) {

	//headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
	if (*h != NULL)
		freeList(*h);

	//headNode에 대한 메모리를 할당하여 리턴
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 硫붾え由� �댁젣 */
int freeList(listNode* h) {
	listNode* f = h;
	listNode* n = NULL;

	while (f->rlink != h) {
		n = f;
		f = f->rlink;
		free(n);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	
	if (h->rlink == h) {              //헤드노드만 존재한다면
		h->rlink = node;
		h->llink = node;
		node->llink = h;
		node->rlink = h;
		return 1;                     //원형으로 각자의 링크를 연결
	}
	listNode* n = h;
	
	while (n->rlink != h) {           //헤드노드로 돌아오기 직전 노드 검색
		n=n->rlink;
	}
	node->rlink = n->rlink;           
	node->llink = n;
	n->rlink->llink = node;
	n->rlink = node;
	                                  //마지막 노드 뒤에 node노드 연결 및 node노드 와 헤드노드 연결
	
}


int deleteLast(listNode* h) {
	if (h->rlink == h) {
		printf("nothing to delete\n");
		return 0;
	}
	listNode* node = h->rlink;
	listNode* n = NULL;
	if (h->llink==h->rlink) {         //헤드 노드외에 하나의 노드만 존재한다면
		deleteFirst(h);
		return 0;
	}
	while (node->rlink != h) {
		n = node;
		node = node->rlink;
	}
	n->rlink = h;                     //마지막 노드인 node노드 이전 n노드를 헤드노드와 연결
	h->llink = n;
	free(node);                       //node노드 해제
	return 1;
}


/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if (h->rlink == h) {              //헤드노드만 존재한다면 node와 circular하게 연결
		h->rlink = node;
		h->llink = node;
		node->llink = h;
		node->rlink = h;
		return 1;
	}
	
	node->rlink = h->rlink;          //헤드노드 양방향 링크와 node노드 양방향 링크 연결
	node->llink = h->rlink->llink;
	h->rlink->llink = node;
	h->rlink = node;
	
	return 0;
	
}

/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(listNode* h) {
	if (h->rlink == h) {
		printf("nothing to delete\n");
		return 0;
	}
	listNode* node = h->rlink;       //헤드노드가 가리키는 노드를 node로 설정
	h->rlink = node->rlink;          //헤드노드의 rlink는 node노드의 rlink로 변경
	node->rlink->llink = h;          //llink도 동일
	free(node);                      //node노드 해제

	return 1;

}


int invertList(listNode* h) {
if (h->rlink == h) {
		printf("nothing to invert\n");
		return 1;
	}
	listNode* node = h;
	listNode* temp = NULL;
	
	do {
		temp = node->rlink;
		node->rlink = node->llink;       //노드의 rlink,link가 가리키는 곳을 서로 바꿔줌
		node->llink = temp;
		node = temp;                     //node를 그다음 노드로 이동
	} while (node != h);                 //노드가 처음 시작으로 돌아올때까지

	return 0;
}


int insertNode(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	
	if (h->rlink == h) {
		h->rlink = node;
		h->llink = node;
		node->llink = h;
		node->rlink = h;
		return 0;
	}
	listNode* n = h;

	while (h->rlink!=h) {                //헤드노드가 돌아 본인에게 돌아올때까지
		if (n->key > key) {             //검색한 key값이 입력 key값보다 클때
			node->rlink = n;            //검색한 노드 llink에 node노드 rlink를 연결
			node->llink = n->llink;
			n->llink->rlink = node;
			n->llink = node;
			return 0;
		}
		if (n->rlink == h) {            //검색한 노드가 마지막 노드라면
			insertLast(h, key);
			return 0;
		}
		n = n->rlink;
	}
	return 0;
}


int deleteNode(listNode* h, int key) {
	if (h->rlink == h) {
		printf("nothing to delete\n");
		return 0;
	}
	listNode* node = h;
	listNode* n = h;

	while(n->rlink!=h) { 
		if (node->key == key) {                 //검색한 노드의 key값과 입력값이 같을때
			node->llink->rlink = node->rlink;   //검색한 노드의 양 옆 노드들을 연결시킨다
			node->rlink->llink = node->llink;   //검색한 노드 해제
			free(node);
			return 0;
		}
		n = node;
		node = node->rlink;
	}
	printf("can not find the node for key=%d\n", key);
	return 0;
}