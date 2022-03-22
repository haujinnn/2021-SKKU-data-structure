#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)

typedef struct ListNode {
	char data;
	struct ListNode *link;
}ListNode;


size = 0;
cp = -1;

ListNode *init(char); //노드를 생성하고 받은 데이터를 노드에 저장
void print(ListNode*);
ListNode* add_tail(ListNode*, char);
void get_data(ListNode*);
void traverse_front(ListNode*, char);
ListNode* move_end(ListNode*); //현재위치의 노드를 마지막 위치로 이동
ListNode* move_first(ListNode*); //현재 위치의 노드를 첫번째 위치로 이동
ListNode* letter_change(ListNode*); //문자의 대소변경

ListNode *init(char data) {
	ListNode *new = (ListNode*)malloc(sizeof(ListNode));
	new->data = data;
	new->link = NULL;
	return new;
}

void print(ListNode *head) {
	int i = 0;
	ListNode *p = head;
	while (p) {
		if (i == cp) {
			printf("(%c) ", p->data);
		}
		else {
			printf("%c ", p->data);
		}
		p = p->link;
		i++;
	}
	printf("\n");
}



void get_data(ListNode *head) {
	int i;
	ListNode* tmp = head;
	for (i = 0; i < cp; i++) {
		tmp = tmp->link;
	}
	printf("return: %c\n", tmp->data);
}

void traverse_front(char cnt) {
	int i;
	cp = 0;
	for (i = 0; i < cnt; i++) {
		cp++;
	}
}

void traverse_rear(char cnt) {
	int i;
	cp = size-1;
	for (i = 0; i < cnt; i++) {
		cp--;
	}
}

ListNode *delete_list(ListNode *head) {
	ListNode* removed;
	ListNode *pre = head;

	if (cp == 0) {
		removed = head;
		head = removed->link;
	}
	else {
		for (int i = 0; i < cp - 1; i++) {
			pre = pre->link;
		}
		removed = pre->link;
		pre->link = removed->link;
	}
	
	free(removed);
	size--;
	return head;
}

ListNode* add_tail(ListNode* head, char data) { //현재노드의 다음 노드에 값추가
	
	ListNode *p = head;
	p = init(data);
	ListNode *pre = head;
	for (int i = 0; i < cp ; i++) {
		pre = pre->link;
	}
	p->link = pre->link;
	pre->link = p;

	cp++;
	size++;

	return head;
}

ListNode *add(ListNode *head, char data) {
	ListNode *p=head;
	p = init(data);
	ListNode *pre = head;
	for (int i = 0; i < cp-1; i++) {
		pre = pre->link;
	}
	p->link = pre->link;
	pre->link = p;
	
	size++;
	return head;
}

ListNode *add_first(ListNode *head, char data) {
	ListNode *p = head;
	p = init(data);
	p->data = data;
	p->link = head;
	head = p;
	size++;
	return head;
}

ListNode *replace(ListNode *head, char data) {
	int i;
	ListNode* tmp = head;
	for (i = 0; i < cp; i++) {
		tmp = tmp->link;
	}
	tmp->data = data;
	return head;
}

void data_count(ListNode *head) {
	int count=1;

	ListNode* tmp = head;
	while (tmp->link != NULL) {
		count++;
		tmp = tmp->link;
	}
	printf("return: %d\n", count);
}

void is_member(ListNode *head, char data) {
	int count = 0;
	ListNode* tmp = head;
	while (tmp->link != NULL) {
		tmp = tmp->link;
		count++;
		if (tmp->data == data) {
			printf("return: %d ", count+1);
			cp = count;
		}
	}
	printf("\n");
}

int is_empty(ListNode *head) {
	if (head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

ListNode* move_end(ListNode *head) {
	char data;
	ListNode* p = head;
	for (int i = 0; i < cp; i++) {
		p = p->link;
	}
	data = p->data;
	delete_list(head);
	cp = size - 1;
	head=add_tail(head, data);

	return head;
}
ListNode* move_first(ListNode *head) {
	char data;
	ListNode* p = head;
	for (int i = 0; i < cp; i++) {
		p = p->link;
	}
	data = p->data;
	delete_list(head);
	cp = 0;
	head=add_first(head, data);

	return head;
}
ListNode* letter_change(ListNode *head) {
	char data;
	for (ListNode* p = head; p!=NULL; p=p->link) {
		data = p->data;
		if (isupper(data)) {
			p->data = tolower(data);
		}
		else {
			p->data = toupper(data);
		}
	}

	return head;
}

int main() {
	//공백 없이

	ListNode *my_list = NULL;
	int i;

	printf("==============♥MENU♥==============\n");
	printf("INSERT			: +(data)\n");
	printf("DELET			: -\n");
	printf("PRINT			: L\n");
	printf("GET_DATA		: G\n");
	printf("TRAVERSE_FRONT		: <\n");
	printf("TRAVERSE_REAR		: >\n");
	printf("REPLACE			: =(data)\n");
	printf("DATA_COUNT		: #\n");
	printf("IS_MEMBER		: ?(data)\n");
	printf("CLEAR			: C\n");
	printf("IS_EMPTY		: E(data)\n");
	printf("MOVE_END		: Mn\n");
	printf("MOVE_FIRST		: Mf\n");
	printf("LETTER_CHANGE		: U\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin ♡\n");
	printf("====================================\n");

	while (1) {
		char arr[30] = { '\0', }; //배열 초기화
		printf(">> ");
		gets(arr);

		if (arr[0] == '+') {
			if (cp == 0) {
				my_list = add_first(my_list, arr[1]);
				for (i = 3; arr[i] != '\0'; i += 2) {
					my_list = add_tail(my_list, arr[i]);
				}
			}
			else if (size==0) {
				my_list = init(arr[1]);
				cp++;
				size++;
				for (i = 3; arr[i] != '\0'; i += 2) {
					my_list = add_tail(my_list, arr[i]);
				}
			}
			else {
				my_list = add(my_list, arr[1]);
				for (i = 3; arr[i] != '\0'; i += 2) {
					my_list = add_tail(my_list, arr[i]);
				}
			}
			
		}
		else if (arr[0] == 'L') {
			print(my_list);
		}
		else if (arr[0] == 'G') {
			get_data(my_list);
		}
		else if (arr[0] == '<') {
			int count = 0;
			for (i = 0; arr[i] != '\0'; i++) {
				if (arr[i] == 'N') {
					count++;
				}
			}
			traverse_front(count);
			if (arr[1] == '+') {
				my_list = add_first(my_list, arr[2]);
				for (i = 4; arr[i] != '\0'; i=i + 2) {
					my_list= add_tail(my_list, arr[i]);
				}
			}
		}
		else if (arr[0] == '-') {
			my_list=delete_list(my_list);
			if (cp + 1 > size) {
				cp = 0;
			}
		}
		else if (arr[0] == 'N') {
			for (i = 2; arr[i] != '\0'; i += 2) {
				my_list = add_tail(my_list, arr[i]);
			}
		}
		else if (arr[0] == '>') {
			int count = 0;
			for (i = 0; arr[i] != '\0'; i++) {
				if (arr[i] == 'P') {
					count++;
				}
			}
			traverse_rear(count);
		}
		else if (arr[0] == '=') {
			my_list=replace(my_list, arr[1]);
		}
		else if (isdigit(arr[0])) {
			int count = arr[0]-48;
			traverse_front(count-1);
			if (arr[1] == 'G') {
				get_data(my_list);
			}
			else if (arr[1] == '=') {
				my_list = replace(my_list, arr[2]);
			}
		}
		else if (arr[0] == '#') {
			data_count(my_list);
		}
		else if (arr[0] == '?') {
			is_member(my_list, arr[1]);
		}
		else if (arr[0] == 'C') {
			cp = 0;
			while (cp < size) {
				my_list = delete_list(my_list);
			} 
			size = 0;
			cp = -1;
		}
		else if (arr[0] == 'E') {
			if (is_empty(my_list)) {
				printf("TRUE\n");
			}
			else {
				printf("FALSE\n");
			}
		}
		else if (arr[0] == 'M') {
			if (arr[1] == 'n') {
				my_list=move_end(my_list);
			}
			else if (arr[1] == 'f') {
				my_list = move_first(my_list);
			}
		}
		else if (arr[0] == 'U') {
		my_list = letter_change(my_list);
		}

		print(my_list);
	}


	return 0;
}