#include<stdio.h>
#include<stdlib.h>
/* 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �⑥닔 由ъ뒪�� */

/* note: initialize 이중포인터를 매개변수로 받음
		 singly-linked-list�� initialize�� 李⑥씠�먯쓣 �댄빐 �좉쾬 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜다른지
		 - �댁쨷�ъ씤�곕� 留ㅺ컻蹂��섎줈 諛쏆븘�� �댁젣�� �� �덉쓣 寃� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;
printf("-----2016031032-----Park_Jiwoo-----");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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


int initialize(headNode** h) {                          //호출하는 곳에서의 값 변경을 위해 이중포인터 사용
	if (*h != NULL)
		freeList(*h);
	*h = (headNode*)malloc(sizeof(headNode));           //Head node 생성
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h) { 
	listNode* f = h->first;                           //초기 Head node부터

	listNode* n = NULL;
	while (f != NULL) {                               //리스트 끝까지 검색
		n = f;                                        //f리스트 n에 임시저장
		f = f->rlink;                                 //rlink따라 위치이동
		free(n);
	}
	free(h);
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}





int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if (h->first == NULL) {                 
		h->first = node;
		return 0;
	}
	listNode* l = h->first;

	while (l->rlink != NULL) {               //리스트 마지막노드까지 반복
		l = l->rlink;
	}
	l->rlink = node;                         //null자리에 node삽입
	node->llink = l;                         //node의 llink를 l리스트에 연결
	return 0;
}



/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 0;
	}
	listNode* node = h->first;
	listNode* p = NULL;

	if (node->rlink == NULL) {               //노드가 하나밖에 없을때
		h->first = NULL;
		free(node);
		return 0;
	}

	while (node->rlink != NULL) {             //리스트 마지막노드까지 반복
		p = node;                             //node정보 p에 저장
		node = node->rlink;                   //node는 rlink를 따라 위치이동
	}
	p->rlink = NULL;
	free(node);
	return 0;
}



/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if (h->first == NULL) {
		h->first = node;
		return 1;
	}
	node->rlink = h->first;                //head 노드가 가리키는곳이 node의 rlink가 가리키는곳으로 설정

	listNode* f = h->first;
	f->llink = node;                      //f노드의 llink가 가리키는곳이 node노드
	h->first = node;                      //node노드가 첫번째 노드가됨
	return 0;
}

/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 0;
	}
	listNode* node = h->first;            //head 노드가 가리키는곳이 node노드
	h->first = node->rlink;               //node노드의 rlink가 가리키는 곳이 head 노드가 가리키는곳
	free(node);
	return 0;
}



/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
int invertList(headNode* h) {
	if (h->first == NULL) {
		printf("nothing to invert\n");
		return 0;
	}
	listNode* node = h->first;
	listNode* temp = NULL;
	listNode* n = NULL;

	while (node != NULL) {
		temp = n;
		n = node;                        
		node = node->rlink;              //node노드는 rlink따라 위치 이동
		n->rlink = temp;                 //temp노드는 결국 리스트의 마지막 null값이됨
		n->llink = node;                 //기존 리스트와 순서 바뀜
	}
	h->first = n;
	return 0;
}



/* list검색하여 입력받음 key보다 큰값이 나오는 노드 바로앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = NULL;
	node->rlink = NULL;

	if (h->first == NULL) {
		h->first = node;
		return 0;
	}
	listNode* n = h->first;

	while (n != NULL) {
		if (n->key >= key) {             // key값이 n노드 값보다 작거나 같을때
			if (n==h->first) {           //n노드가 첫번째 노드일때
				insertFirst(h, key);
			}
			else {
				node->rlink = n;        //node노드의 rlink가 가리키는곳이 n노드가됨
				node->llink = n->llink; //n노드의 llink가 가리키던곳은 node노드의 llink와 연결
				n->llink->rlink = node; //n노드의 llink의 rlink가 가리키는곳은 node노드가됨
			}
			return 0;
		}
		n = n->rlink;
	}
	insertLast(h, key);                //숫자크기 순이라 숫자가 리스트중에서 젤크면 마지막에 삽입
	return 0;
}


/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣z
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {
		printf("nothing to delete\n");
		return 1;
	}
	listNode* node = h->first;

	while (node != NULL) {
		if (node->key >= key) {            // key값이 n노드 값보다 작거나 같을때
			if (node == h->first) {        //node노드가 첫번째 노드라면
				deleteFirst(h);            //맨앞노드 삭제함수 적용해도 같은결과
			}
			else if (node->rlink == NULL){    //node가 마지막 노드라면
				deleteLast(h);
			}
			else {
				node->llink->rlink = node->rlink;  //node 양옆의 링크끼리 연결시켜 
				node->rlink->llink = node->llink;  //node노드와 주변노드 연결끊기
				free(node);
			}
			return 1;
		}
		node = node->rlink;
	}
	printf("cannot find the node for key=%d\n", key);
	return 1;
}