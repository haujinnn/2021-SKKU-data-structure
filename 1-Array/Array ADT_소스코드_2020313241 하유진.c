#include <stdio.h>
#include <ctype.h>
#pragma warning(disable: 4996)

int cp=-1; //current point�� ��Ÿ���� ��������
int len = 0; //my_array �迭�� ���� 
void insert(char arr[], char data); //arr[]�� data�� ������� �ִ� �Լ�
void delete(char arr[]); //current point�� ���� ����
void traverse_front(char array[], int count); //�迭�� ó������ �����ؼ� N ��ŭ ���������� �̵�
void traverse_rear(char array[], int count); //�迭�� �� �ں��� �����ؼ� P ��ŭ �������� �̵�
void get_data(char arr[]); //current point�� ���� ���
void replace(char arr[], char data); //current point�� ���ڸ� data�� �ٲ�
void empty(char arr[]); //�迭�� �ִ� ���Ҹ� ��� ����
void move(char arr[], int new_position); //current point�� ���ڸ� �Է��� new_position ��ġ�� �̵�
void data_count(char arr[], char data); //current point�� ���ڸ� �ǵڷ�, ������, �ڷ� �̵�
void print(char arr[]); //�迭 ��ü ���
void letter_change(char arr[]); //�迭�� ���� ��ҹ��� �ٲ��ֱ�
void find(char arr[], char data); //�迭�� �ִ� ���� Ž��
void backwards(char arr[]); //�迭 ������ �ݴ��


void menu() {
	printf("================MENU================\n");
	printf("INSERT			: +(data)\n");
	printf("DELET			: -\n");
	printf("TRAVERSE_FRONT		: <\n");
	printf("TRAVERSE_REAR		: >\n");
	printf("GET_DATA		: @\n");
	printf("REPLACE			: =(data)\n");
	printf("EMPTY			: E\n");
	printf("MOVE			: M(position)\n");
	printf("MOVE END		: Mn\n");
	printf("MOVE PREV		: MP\n");
	printf("MOVE NEXT		: MN\n");
	printf("PRINT			: L\n");
	printf("LETTER_CHANGE		: C\n");
	printf("FIND			: F(data)\n");
	printf("BACKWARDS		: B\n");
	printf("PROGRAM_END		: P\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin\n");
	printf("====================================\n");
}

void insert(char arr[], char data) {
	int i;
	if (cp != len - 1) {
		for (i = len-1 ; i > cp; i--) {
			arr[i+1] = arr[i];
		}
	}
	arr[cp+1] = data;
	
}

void traverse_front(char array[], int count) {
	cp = count;
}

void traverse_rear(char array[], int count) {
	cp = count;
}

void delete(char arr[]) {
	int i;
	for (i = cp; i < len; i++) {
		arr[i] = arr[i + 1];
	}
	len--;
}

void get_data(char arr[]) {
	printf("return: %c\n", arr[cp]);
}

void replace(char arr[], char data) {
	arr[cp] = data;
}

void empty(char arr[]) {
	int i;
	for (i = 0; i < len; i++) {
		arr[i] = arr[len];
	}
}

void move(char arr[], int new_position) {
	int i;
	char cnt;
	cnt = arr[cp];
	if (new_position > cp) {
		for (i = cp; i < new_position; i++) {
			arr[i] = arr[i + 1];
		}	
	}
	else {
		for (i = cp; i > new_position; i--) {
			arr[i] = arr[i - 1];
		}
	}
	arr[new_position] = cnt;
	cp = new_position;
}

void data_count(char arr[], char data) {
	char cnt;
	int i;
	cnt = arr[cp];
	if (data == 'n') {
		for (i = cp; i < len; i++) {
			arr[i] = arr[i + 1];
		}
		arr[len - 1] = cnt;
		cp = len - 1;
	}
	else if (data == 'P') {
		arr[cp] = arr[cp - 1];
		arr[cp - 1] = cnt;
		cp = cp - 1;
	}
	else if (data = 'N') {
		arr[cp] = arr[cp + 1];
		arr[cp + 1] = cnt;
		cp = cp + 1;
	}
}

void print(char arr[]) {
	int i;
	for (i = 0; i < len; i++) {
		if (i == cp) {
			printf("(%c) ", arr[i]);
		}
		else {
			printf("%c ", arr[i]);
		}
	}
	if (len == 0) {
		printf("empty array");
	}
	printf("\n");
}

void letter_change(char arr[]) {
	int i;
	for (i = 0; i < len; i++) {
		if (isupper(arr[i])) { //�빮���϶�
			arr[i] = tolower(arr[i]); //�ҹ��ڷ� �ٲ۴�
		}
		else if (islower(arr[i])) { //�ҹ��� �϶� 
			arr[i] = toupper(arr[i]); //�빮�ڷ� �ٲ۴�.
		}
	}
}

void find(char arr[], char data) {
	int i;
	for (i = 0; i < len; i++) {
		if (arr[i] == data) {
			printf("location: %d\n", i);
		}
	}
}

void backwards(char arr[]) {
	char cnt[30];
	int i;

	for (i = 0; i < len; i++) {
		cnt[i] = arr[len - 1 - i];
	}
	for (i = 0; i < len; i++) {
		arr[i] = cnt[i];
	}

}

int main() {
	char my_array[30];
	int i;

	menu();

	while (1) {
		
		char arr[50] = {'\0', }; //arr �迭 �ʱ�ȭ
		printf(">> ");
		gets(arr); 

		if (arr[0] == '+') {
			for (i = 0; i < 30; i++) {
				if (arr[i] == '+') {
					insert(my_array, arr[i + 1]);
					cp++;
					len++;
				}
			}
		}
		else if (arr[0] == '<') {
			int count = 0;
			for (i = 0; i < 30; i++) {
				if (arr[i] == 'N') {
					count++;
				}
			}
			traverse_front(my_array, count);
		}
		else if (arr[0] == '>') {
			int count = len-1;
			for (i = 0; i < 30; i++) {
				if (arr[i] == 'P') {
					count--;
				}
			}
			traverse_rear(my_array, count);
		}
		else if (arr[0] == '-') {
			delete(my_array);
			if (len - 1 < cp) {
				cp = 0;
			}
		}
		else if (arr[0] == '@') {
			get_data(my_array);
		}
		else if (arr[0] == '=') {
			replace(my_array, arr[1]);
		}
		else if (arr[0] == 'E') {
			empty(my_array);
			len = 0;
			cp = -1;
		}
		else if (arr[0] == 'M') {
			if (arr[1] == 'n'|| arr[1] == 'P'|| arr[1] == 'N') {
				data_count(my_array, arr[1]);
			}
			else {
				int position = arr[1] - 48;
				move(my_array, position);
			}
		}
		else if (arr[0] == 'L') {
			print(my_array);
		}
		else if (arr[0] == 'C') {
			letter_change(my_array);
		}
		else if (arr[0] == 'F') {
			find(my_array, arr[1]);
		}
		else if (arr[0] == 'B') {
			backwards(my_array);
		}
		else if (arr[0] == 'P') {
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
		
		
		for (i = 0; i < len; i++) {
			if (i == cp) {
				printf("(%c) ", my_array[i]);
			}
			else {
				printf("%c ", my_array[i]);
			}
		}
		if (len == 0) {
			printf("empty array");
		}
		printf("\n");
	}
	
	return 0;
}

