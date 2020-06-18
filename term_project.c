

#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTEX 20
typedef struct Vertex {
	int num;                 //vertex number
	struct Vertex* link;     //link to a next adjacent vertext
	
} Vertex;
typedef struct VertexHead {
	Vertex* Head;            //linked list of all adjacent vertices
	int Flag;
}VertexHead;
typedef struct Graph {
	int v;
	int* visited;
	VertexHead* vlist;       //list of all vertices:vlist[Max_Vertex]
}Graph;
typedef struct queue {         //breadthFS를 위한 큐 구조체 생성
	int item[MAX_VERTEX];
	int front;
	int rear;
}Queue;


Graph* createGraph(int);
Graph* insertVertex(Graph*,int);
void insertEdge(Graph*,int,int);
Graph* deleteVertex(Graph*,int);
void printGraph(Graph*);
Vertex* newnode(int);
Graph* deleteEdge(Graph*,int,int);
void depthFS(Graph*,int);
void breadthFS(Graph*,int);
void destroyGraph(Graph*);


int main()
{
	char command;
	int num,n;
	Graph* graph;
	srand(time(NULL));
	printf("-----[2016031032]-----[Park_Jiwoo]-----\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Graph                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" CreateGraph    = c           DestroyGraph   = d\n");
		printf(" InsertVertex   = i           DeleteVertex   = v\n");
		printf(" InsertEdge     = e           DeleteEdge     = g\n");
		printf(" DepthFS        = f           BreadthFS      = s\n");
		printf(" PrintGraph     = p           Quit           = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'c': case 'C': 
			graph = createGraph(MAX_VERTEX);
			break; 
		case 'i': case 'I': {
			
			printf("input Vertex number to activate(0~19) : ");
			scanf("%d", &num);
			insertVertex(graph,num);
			break; }
		case 'e': case 'E': {
			int a, b;
			printf("input two vertex number to create edge between vertex ex(0 2) : ");
			scanf("%d %d", &a, &b);
			insertEdge(graph, a, b);
			break; }
		case 'p': case 'P':
			printGraph(graph);
			break;
		case 'v': case 'V': {
			printf("input vertex number to delete vertex: ");
			scanf("%d", &n);
			deleteVertex(graph, n);
			break; }
		case 'g': case 'G': {
			printf("input two vertex number to delete edge ex(0 2) : ");
			scanf("%d %d", &n,&num);
			deleteEdge(graph,n,num);
			break; }
		case 'f': case 'F': {
			printf("starting vertex number : ");
			scanf("%d", &n);
			for (int i = 0; i < 20; i++)
				graph->visited[i] = 0;
			depthFS(graph, n);
			break; }
		case 's': case 'S': {
			printf("starting vertex number : ");
			scanf("%d", &n);
			for(int i=0;i<20;i++)
			graph->visited[i] = 0;
			breadthFS(graph,n);
			break; }
		case 'd': case 'D':
			destroyGraph(graph);
			break;
		case 'q':case'Q':
			exit(1);
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}
struct Vertex* newnode(int n) {
	Vertex* newNode = (Vertex*)malloc(sizeof(Vertex));
	newNode->num = n;
	newNode->link = NULL;
	return newNode;
}
struct Graph* createGraph(int n) {
	
	  Graph* graph=(Graph*)malloc(sizeof(Graph));                //그래프 동적할당
	 graph->vlist = (VertexHead*)malloc(sizeof(VertexHead)*n);   //동적할당 된 그래프의 헤드부분 최대 vertex개수 만큼 동적할당
	 graph->visited = (VertexHead*)malloc(sizeof(VertexHead) * n);  //그래프 검색 시 지나간 vertex정보 저장용도
	 graph->v = n;
	 return graph;
}

struct Graph* insertVertex(Graph* graph, int num) {

	if (num > 20) {                                      //vertex 최대번호 20번 초과시
		printf("한계초과\n");                            //한계초과 출력
		return -1;
	}
	graph->vlist[num].Head = NULL;                   
	graph->vlist[num].Flag = 1;                          //해당번호 vertex 활성화 시 flag 1로 설정
	graph->visited[num] = 0;
	return graph;
}
struct Graph* deleteVertex(Graph* graph, int v) {
	for (int i = 0; i < 20; i++) {
		if (i != v) {                                    //삭제할 본인 vertex를 제외하고 검색
			if (graph->vlist[i].Flag == 1) {             //flag를 통해 활성화 된 vertex들만 진행
				Vertex* dele = graph->vlist[i].Head;
				Vertex* pre = dele;
				if (dele->num == v) {                    //헤드의 값과 삭제하고자 하는 vertex 번호가 동일할때
					if (graph->vlist[i].Head->link == NULL) {    // head에 연결된 노드가 없을때
						graph->vlist[i].Head = NULL;              //헤드 삭제
					}
					else {
						graph->vlist[i].Head = graph->vlist[i].Head->link; // head부분 연결 끊기
					}

				}
				else {
					while (dele->num != v) {             //삭제하고자 하는 vertex 번호 찾을때까지
						pre = dele;
						if (dele == NULL)
							break;;
						dele = dele->link;               //link옮겨가며 검색
					}
					if (dele->num == v) {
						if (dele->link == NULL) {       //해당 노드가 마지막 노드일때
							pre->link = NULL;            
						}
						else {
							pre->link = dele->link;     //해당 노드 이전 노드와 다음 노드와 연결해 해당 노드 연결 끊기
						}
						
					}
				}
			}
		}
	}
	free(graph->vlist[v].Head);
	graph->vlist[v].Flag = 0;                          //삭제된 vertex의 flag는 0으로 바꿔줌
	return graph;
}
struct Graph* deleteEdge(Graph* graph,int from,int to) {
	
		Vertex* del1 = graph->vlist[from].Head;
		Vertex* pre1=del1;
		if (del1->num == to) {                        //헤드의 값과 연결을 끊고자 하는 vertex 번호가 동일할때
			if (graph->vlist[from].Head->link == NULL) {  // head에 연결된 노드가 없을때
				graph->vlist[from].Head = NULL;
			}
			else {
				graph->vlist[from].Head = graph->vlist[from].Head->link;   //헤드 연결된 노드를 헤드로 지정해 기존 헤드 연결 끊기
			}
			free(del1);
		}
		else {
			while (del1->num != to) {             //연결 끊고자 하는 vertex 번호 찾을때까지
				pre1 = del1;
				if (del1 == NULL) {
					printf("not found");
					break;
				}
				del1 = del1->link;
			}
			if (del1->num == to) { 
				if (del1->link == NULL) {         //해당 노드가 마지막 노드일때
					pre1->link = NULL;
				}
				else {
					pre1->link = del1->link;      //해당 노드 이전 노드와 다음 노드와 연결해 해당 노드 연결 끊기
				}
				free(del1);
			}
		}
		Vertex* del2 = graph->vlist[to].Head;           //위와 같은 방식이나 위는 from번째 list에서 to번 vertex번호를 찾는 것 이였다면
		Vertex* pre2 = del2;                            //밑은 to번째 list에서 from번 vertex번호를 찾는 것
		if (graph->vlist[to].Head->num == from) {
			if (graph->vlist[to].Head->link == NULL) {
				graph->vlist[to].Head = NULL;
			}
			else {
				graph->vlist[to].Head = graph->vlist[to].Head->link;
			}
			free(del2);
		}
		else {
			while (del2->num != from) {
				pre2 = del2;
				del2 = del2->link;
			}
			if (del2->num == from) {
				if (del2->link == NULL) {
					pre2->link = NULL;
				}
				else {
					pre2->link = del2->link;
				}
				free(del2);
			}
		}
		return graph;
}


void insertEdge(Graph* graph,int from,int to) {
	Vertex* node = newnode(to);                //newnode함수 이용 입력값에 해당하는 vertex번호를 가진 node 생성
	Vertex* tmp = graph->vlist[from].Head;      //from 번째 list에 대하여
	if (graph->vlist[from].Head == NULL) {      //헤드가 비었다면
		graph->vlist[from].Head = node;         //노드를 헤드에 대입
		graph->vlist[from].Head->link = node->link;
	}
	else {
		while (tmp->link != NULL) {           //마지막 노드까지 검색
			tmp = tmp->link;
		}
		tmp->link = node;                  //마지막 노드와 생성된 node 연결
	}

	node = newnode(from);                  //위와 같은 방식이나 밑은 to번째 list에 from값 담긴 node 생성 후 연결
	Vertex* temp = graph->vlist[to].Head;
	if (graph->vlist[to].Head == NULL) {
		graph->vlist[to].Head = node;
		graph->vlist[to].Head->link = node->link;
	}
	else {
		
		while (temp->link != NULL) {
			temp = tmp->link;
		}
		temp->link = node;
	}
}
void depthFS(Graph* graph, int vertex) {
	Vertex* Graph = graph->vlist[vertex].Head;       //입력받은 vertex번째 vertex를 검색 시작 vertex로 지정
	Vertex* temp = Graph;

	graph->visited[vertex] = 1;                      //지나친 vertex를 visited[]를 1로 바꿔줘 지나갔다고 표시
	printf("Visited %d \n", vertex);

	while (temp != NULL) {
		int connectedVertex = temp->num;

		if (graph->visited[connectedVertex] == 0) {       //head와 연결된 노들이 visted[]값이 0이면
			depthFS(graph, connectedVertex);              //재귀함수 이용해 연결된 노드들 이어서 검색
		}
		temp = temp->link;
	}
}
int isEmpty(struct queue* q) {
	if (q->rear == -1)
		return 1;
	else
		return 0;
}
void enqueue(struct queue* q, int value) {
	if (q->rear == MAX_VERTEX - 1)
		printf("\nQueue is Full!!");
	else {
		if (q->front == -1)
			q->front = 0;
		q->rear++;                 //queue의 rear값을 1 올리고
		q->item[q->rear] = value;  //queue의 rear번째 칸에 값 넣기
	}
}

int dequeue(struct queue* q) {
	int item;
	if (isEmpty(q)) {
		printf("Queue is empty");
		item = -1;
	}
	else {
		item = q->item[q->front];        //queue front번째 칸에 저장된 값 돌려줌
		q->front++;
		if (q->front > q->rear) {
			q->front = q->rear = -1;     //front값 1 줄이기
		}
	}
	return item;
}

void breadthFS(Graph* graph, int vertex) {
	struct queue* q = malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;

	graph->visited[vertex] = 1;
	enqueue(q, vertex);                       //검색 시작 vertex queue에 저장
	while (!isEmpty(q)) {
		int curvertex = dequeue(q);
		printf("Visited %d\n", curvertex);

		Vertex* temp = graph->vlist[curvertex].Head;

		while (temp) {
			int ver = temp->num;
			if (graph->visited[ver] == 0) {
				graph->visited[ver] = 1;
				enqueue(q, ver);               //해당 vertex에 인접한 vertex 정보 보두 enqueue
			}
			temp = temp->link;
		}
	}
}
void destroyGraph(Graph* graph) {
	for (int i = 0; i < 20; i++) {         //그래프 생성서 최대 vertex만큼 동적할당 해주어 최대 vertex 개수 만큼 반복
		Graph* tmp;
		if (graph->vlist[i].Flag == 1) {
			while (graph->vlist[i].Head != NULL) {
				tmp = graph->vlist[i].Head;
				graph->vlist[i].Head = graph->vlist[i].Head->link;
				free(tmp);                   //i번째 list에 연결된 노드 모두 메모리 해제
			}
		}
		graph->vlist[i].Flag = 0;           //i번째 list의 flag값 0으로 돌려줌
	}
	printf("grpah destroyed\n");
	free(graph);                         //graph 메모리 해제
}
void printGraph(Graph* graph) {
	for (int i = 0; i < 20; i++) {
		Vertex* flag = graph->vlist[i].Flag;
		if (flag == 1) {                       //flag를 통해 활성화 된 vertex번호에 해당 list만 실행
			Vertex* show = graph->vlist[i].Head;
			printf("\n Adjacency list of vertex %d\n head ", i);

			while (show) {
				printf("-> %d", show->num);
				show = show->link;
			}
			printf("\n");
		}
	}
}


