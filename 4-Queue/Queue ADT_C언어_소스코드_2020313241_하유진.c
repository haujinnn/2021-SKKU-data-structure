//1���� �迭�� �̿��� ť ���α׷��Դϴ�.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning(disable : 4996)
#define SIZE 10

typedef struct queue
{
	char data[SIZE];
	int front; //ť�� ù��° ���
	int rear;  //ť�� ������ ���
} Queue;

void clear(Queue *q)
{ //ť �ʱ�ȭ �Լ�
	q->front = -1;
	q->rear = -1;
}

int is_full(Queue *q)
{
	if (q->rear == SIZE - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_empty(Queue *q)
{
	if (q->front == q->rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void enqueue(Queue *q, char data)
{ //ť�� ���� �����͸� �߰��ϴ� �Լ�
	if (is_full(q))
	{
		printf("ERROR (Queue is full)\n");
		exit(-1);
	}
	else
	{
		q->rear++;
		q->data[q->rear] = data;
	}
}

void dequeue(Queue *q, int cnt)
{ //ť�� �� �տ� �ִ� ������ �����Ͽ� ��ȯ
	if (is_empty(q))
		printf("ERROR. Underflow\n");
	else
	{
		printf("return: ");
		for (int i = 0; i < cnt; i++)
		{
			char e = q->data[q->front + 1];
			q->front++;
			printf("%c ", e);
		}
		printf("\n");
	}
}

void print(Queue *q)
{
	int i;
	for (i = q->front + 1; i <= q->rear; i++)
	{
		printf("%c ", q->data[i]);
	}
	printf("\n");
}

void peek(Queue *q)
{
	printf("%c\n", q->data[q->front + 1]);
}

int data_count(Queue *q)
{
	return q->rear - q->front;
}

int head(Queue *q)
{
	return q->front + 2;
}

int tail(Queue *q)
{
	return q->rear + 1;
}

void is_member(Queue *q, char data)
{
	int answer = 0;
	for (int i = q->front + 1; i <= q->rear; i++)
	{
		if (q->data[i] == data)
			answer++;
	}
	printf("%d\n", answer ? 1 : -1);
}

void replace(Queue *q, char data)
{
	q->data[q->rear] = data;
}

void move_end(Queue *q)
{ //front data�� �� �ڷ� �̵���Ű�� front�� rear 1�� ����
	char e = q->data[q->front + 1];
	q->front++;
	enqueue(q, e);
}

void upper_case(Queue *q)
{ //�ҹ��ڸ� ��� �빮�ڷ� ��ȯ
	Queue tmp;
	clear(&tmp);
	char data;

	while (!is_empty(q))
	{
		data = q->data[q->front + 1];
		if (islower(data))
		{
			enqueue(&tmp, toupper(data));
		}
		else
		{
			enqueue(&tmp, data);
		}
		q->front++;
	}
	clear(q);

	for (int i = (&tmp)->front + 1; i <= (&tmp)->rear; i++)
	{
		enqueue(q, (&tmp)->data[i]);
	}
}

void lower_case(Queue *q)
{ //�빮�ڸ� ��� �ҹ��ڷ� ��ȯ
	Queue tmp;
	clear(&tmp);
	char data;

	while (!is_empty(q))
	{
		data = q->data[q->front + 1];
		if (isupper(data))
		{
			enqueue(&tmp, tolower(data));
		}
		else
		{
			enqueue(&tmp, data);
		}
		q->front++;
	}
	clear(q);

	for (int i = (&tmp)->front + 1; i <= (&tmp)->rear; i++)
	{
		enqueue(q, (&tmp)->data[i]);
	}
}

void menu()
{
	printf("==============��MENU��==============\n");
	printf("ENQUEUE			: +(data)\n");
	printf("DEQUEUE			: -\n");
	printf("PRINT			: L\n");
	printf("PEEK			: P\n");
	printf("IS_FULL			: F\n");
	printf("IS_EMPTY		: E\n");
	printf("DATA_COUNT		: #\n");
	printf("HEAD			: H\n");
	printf("TAIL			: T\n");
	printf("IS_MEMBER		: ?(data)\n");
	printf("REPLACE			: =(data)\n");
	printf("CLEAR			: C\n");
	printf("MOVE_END		: M\n");
	printf("UPPER_CASE		: U\n");
	printf("LOWER_CASE		: W\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin \n");
	printf("====================================\n");
}

int main()
{
	Queue my_queue;
	clear(&my_queue);
	menu();

	while (1)
	{
		char arr[20] = {
			'\0',
		};
		printf(">> ");
		scanf("%s", arr);

		if (arr[0] == '+')
			for (int i = 1; i < arr[i] != '\0'; i += 2)
				enqueue(&my_queue, arr[i]);

		else if (arr[0] == 'L')
			print(&my_queue);

		else if (arr[0] == 'P')
			peek(&my_queue);

		else if (arr[0] == '-')
		{
			int cnt = 0;
			for (int i = 0; arr[i] != '\0'; i++)
				if (arr[i] == '-')
					cnt++;
			dequeue(&my_queue, cnt);
		}
		else if (arr[0] == 'F')
			printf("%s\n", is_full(&my_queue) ? "TRUE" : "FALSE");

		else if (arr[0] == 'E')
			printf("%s\n", is_empty(&my_queue) ? "TRUE" : "FALSE");

		else if (arr[0] == '#')
			printf("%d\n", data_count(&my_queue));

		else if (arr[0] == 'H')
			printf("%d\n", head(&my_queue));

		else if (arr[0] == 'T')
			printf("%d\n", tail(&my_queue));

		else if (isdigit(arr[0]))
			dequeue(&my_queue, arr[0] - 48);

		else if (arr[0] == '?')
			is_member(&my_queue, arr[1]);

		else if (arr[0] == '=')
			replace(&my_queue, arr[1]);

		else if (arr[0] == 'C')
			clear(&my_queue);

		else if (arr[0] == 'M')
			move_end(&my_queue);

		else if (arr[0] == 'U')
			upper_case(&my_queue);

		else if (arr[0] == 'W')
			lower_case(&my_queue);

		print(&my_queue);
	}

	return 0;
}