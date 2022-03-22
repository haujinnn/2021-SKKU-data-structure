//�迭�� �̿��� ���� ���α׷��Դϴ�.

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define SIZE 100
typedef struct stack {
	char data[SIZE]; //data�� �Է¹޴� ����Ʈ
	int top; //list���� top�� ��ġ
}Stack;

void init(Stack); //���� �ʱ�ȭ �Լ�
void push(Stack, char);
char *pop(Stack);
int is_full(Stack);
int is_empty(Stack);

void init(Stack *stack) { 
	stack->top = -1;
}

int is_full(Stack *stack) { 
	return (stack->top) == SIZE - 1; 
}

void push(Stack *stack, char data) {
	if (is_full(stack)) {
		printf("������ ���� á���ϴ�.");
	}
	else {
		stack->top++;
		stack->data[stack->top] = data;
	}
}

int is_empty(Stack *stack) {
	if (stack->top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

char *pop(Stack *stack) {
	char e;
	if (is_empty(stack)) {
		printf("������ ������ϴ�.\n");
		exit(-1);//�Լ� �ߴ�
	}
	else {
		e = stack->data[stack->top];
		stack->top--;
		return e;
	}
}

char peek(Stack *stack) {
	return stack->data[stack->top];
}

void print(Stack *stack) {
	Stack tmp;
	init(&tmp);

	if (is_empty(stack)) {
		printf("EMPTY STACK\n");
	}
	else {
		while (!is_empty(stack)) {
			push(&tmp, pop(stack));
		}

		while (!is_empty(&tmp)) {
			push(stack, pop(&tmp));
			printf("%c ", peek(stack));
		}

		printf("(top: %d)\n", stack->top);
	}
}

void element_count(Stack *stack) {
	printf("%d\n", stack->top + 1);
}

void top(Stack *stack) {
	printf("(%d, %c)\n", stack->top + 1, stack->data[stack->top]);
}

void is_member(Stack *stack, char data) {
	Stack tmp;
	init(&tmp);

	while (!is_empty(stack)) {
		push(&tmp, pop(stack));
	}

	while (!is_empty(&tmp)) {
		push(stack, pop(&tmp));
		if (data == peek(stack)) {
			printf("TRUE\n");
		}
	}
}

void replace(Stack *stack, char data) {
	pop(stack);
	push(stack, data);
}

void clear(Stack *stack) {
	while (stack->top > -1) {
		pop(stack);
	}
}

Stack reverse(Stack *stack) { //���� ���� �Ųٷ�
	Stack tmp;
	init(&tmp);

	while (!is_empty(stack)) {
		push(&tmp, pop(stack));
	}

	return tmp;
}

void letter_change(Stack *stack) { //������ ��� ����
	Stack tmp;
	init(&tmp);

	char data;

	while (!is_empty(stack)) {
		data = pop(stack);
		if (isupper(data)) {
			push(&tmp, tolower(data));
		}
		else {
			push(&tmp, toupper(data));
		}
	}

	while (!is_empty(&tmp)) {
		push(stack, pop(&tmp));
	}
}

void twice(Stack *stack) { //���Ҹ� �ι�� �ø�
	Stack tmp;
	init(&tmp);

	while (!is_empty(stack)) {
		push(&tmp, pop(stack));
	}

	while (!is_empty(&tmp)) {
		push(stack, peek(&tmp));
		push(stack, pop(&tmp));
	}

}

int main() {

	int i;
	Stack my_stack; //Stack my_stack
	init(&my_stack); //init(&my_stack);

	printf("==============��MENU��==============\n");
	printf("PUSH			: +(data)\n");
	printf("POP			: -\n");
	printf("PRINT			: L\n");
	printf("PEEK			: P\n");
	printf("IS_FULL			: F\n");
	printf("IS_EMPTY		: E\n");
	printf("REPLACE			: =(data)\n");
	printf("ELEMENT_COUNT		: #\n");
	printf("IS_MEMBER		: ?(data)\n");
	printf("CLEAR			: C\n");
	printf("TOP			: T(data)\n");
	printf("REVERSE			: R\n");
	printf("LETTER_CHANGE		: U\n");
	printf("TWICE			: W\n");
	printf("END_PROGRAM		: X\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin \n");
	printf("====================================\n");

	

	
	while (1) {

		int i;
		char arr[30] = {'\0', };
		printf(">> ");
		scanf("%s", arr);
		
		if (arr[0] == '+') {
			if (is_full(&my_stack)) {
				printf("Error(stack is full)\n");
			}
			else {
				for (i = 1; arr[i]!='\0'; i+=2) {
					push(&my_stack, arr[i]);
				}
			}
		}
		else if (arr[0] == 'L') {
			print(&my_stack);
		}
		else if (arr[0] == 'P') {
			printf("%c\n", peek(&my_stack));
		}
		else if (arr[0] == '-') {
			if (is_empty(&my_stack)) {
				printf("Error (nothing to pop)\n");
			}
			else {
				printf("return: ");
				for (i = 0; arr[i] != '\0'; i++) {
					if (arr[i] == '-') {
						printf("%c ", pop(&my_stack));
					}
				}
				printf("\n");
			}
			
		}
		else if (arr[0]=='F') {
			if (is_full(&my_stack)) {
				printf("TRUE\n");
			}
			else {
				printf("FALSE\n");
			}
		}
		else if (arr[0] == 'E') {
			if (is_empty(&my_stack)) {
				printf("TRUE\n");
			}
			else {
				printf("FALSE\n");
			}
		}
		else if (arr[0] == '#') {
			element_count(&my_stack);
		}
		else if (arr[0]=='T'){
			top(&my_stack);
		}
		else if (isdigit(arr[0])) {//������ ���
			int count = arr[0] - 48;
			printf("return: ");
			for (i = 0; i < count; i++) {
				printf("%c ", pop(&my_stack));
			}
			printf("\n");
		}
		else if (arr[0] == '?') {
			is_member(&my_stack, arr[1]);
		}
		else if (arr[0] == '=') {
			replace(&my_stack, arr[1]);
		}
		else if (arr[0] == 'C') {
			clear(&my_stack);
		}
		else if (arr[0] == 'R') {
			my_stack=reverse(&my_stack);
		}
		else if (arr[0] == 'U') {
			letter_change(&my_stack);
		}
		else if (arr[0] == 'W') {
			twice(&my_stack);
		}
		else if (arr[0]=='X') {
			printf("���α׷��� �����մϴ�.");
			break;
		}

		print(&my_stack);
	}

	
	return 0;
}