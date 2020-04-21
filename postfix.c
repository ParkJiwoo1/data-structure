#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내 우선순위 */
typedef enum {
	lparen = 0,  /* (  */
	rparen = 9,  /* ) */
	times = 7,   /* * */
	divide = 6,  /* / */
	plus = 5,    /* + */
	minus = 4,   /* -  */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	
char postfixExp[MAX_EXPRESSION_SIZE];	
char postfixStack[MAX_STACK_SIZE];	
int evalStack[MAX_STACK_SIZE];		

int postfixStackTop = -1;  
int evalStackTop = -1;	   

int evalResult = 0;	  

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
	char x;
	if (postfixStackTop == -1)
		return postfixStackTop;
	else {
		x= postfixStack[postfixStackTop--];
	}
	return x;
}


void evalPush(int x)
{
	evalStack[++evalStackTop] = x;
}

int evalPop()
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];
}

void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
	getPriority(infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)
{
	return getToken(x);
}


void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}


void toPostfix()
{
	int cnt = 0;
	/* infixexp의 문자 하나씩 읽기 위한 포인터  */
	char* exp = infixExp;
	char x,y; /* 문자하나를 임시로 저장하기 위한 변수 */
	postfixPush(0);

	for (int i = 0; i < strlen(infixExp); i++) {
		x = exp[i];                              //문자 하나씩 받아서 저장
		if (x >= '0' && x <= '9')                //문자가 0~9사이의 숫자라면
			postfixExp[cnt++] = x;               //배열에 바로 저장
		else {
			switch (x) {
			case '(':                            //문자가 '('일시
				postfixPush(x);                  //임시 배열로 push
				break;
			case ')':                            //문자가 '(일시
				while (1) {                      
					y = postfixPop();            //임시배열 저장문자 가져옴
					if (y == '(')                //문자가 '('가 나올때까지
						break;
					postfixExp[cnt++] = y;       //임시배열 문자 배열에 저장
				}
				break;
			case '+': case'-':case'*':case'/':
				while (postfixStackTop > -1 && getPriority(postfixStack[postfixStackTop]) >= getPriority(x)) {
					//연산자일 경우 임시배열 연산자가 현재 받아온 연산자보다 우선순위가 클때
					postfixExp[cnt++] = postfixPop();      //배열에 저장
				}
				postfixPush(x);     //현재 연산자 배열에 반복문 종료 후 저장
			}
		}
		/*infixexp의 문자를 하나씩 읽어가면서 stack을 이용해 변경 */
	}
	while (postfixStackTop!=-1) {                    //임시 저장 스택을 하나씩 낮춰가면서
		postfixExp[cnt++] = postfixPop();            //배열에 저장
		
	}
	postfixExp[cnt] = '\0';
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		printf("%c  ", postfixStack[i]);
		
	}

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	for (int i = 0; i < strlen(postfixExp); i++) {
		char y = postfixExp[i];
		int ord1, ord2;
		if (y >= '0' && y <= '9') {
			evalPush(y-'0');
		}
		else {                                   //해당 연산자가 나오기 직전 두 숫자를 해당 연산자에 맞게 연산해 배열에 값 저장
			if (y == '+') {
				ord2 = evalPop();
				ord1 = evalPop();
				evalPush(ord1 + ord2);
			}
			else if (y == '-') {
				ord2 = evalPop();
				ord1 = evalPop();
				evalPush(ord1 - ord2);
			}
			else if (y == '*') {
				ord2 = evalPop();
				ord1 = evalPop();
				evalPush(ord1 * ord2);
			}
			else if (y == '/') {
				ord2 = evalPop();
				ord1 = evalPop();
				evalPush(ord1 / ord2);
			}
		}
	}
	evalResult = evalPop();
}


int main()
{
	char command;

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;


}