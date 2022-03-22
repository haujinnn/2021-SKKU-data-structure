#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

typedef struct tagnode {
	int data;
	struct tagNode *left;
	struct tagNode *right;
}Node;

typedef struct tagBST {
	Node *root;
}BST;

void init(BST *bst) {
	bst->root = NULL;
}

void *create(BST *bst, int data) {
	Node *new = (Node*)malloc(sizeof(Node));

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	bst->root = new;
}

int st_num(char a[], int* i) {
	int num = 0;
	while ('0' <= a[*i] && a[*i] <= '9') {
		num = num * 10;
		num += (a[*i] - '0');
		(*i)++;
	}
	return num;
}

void insert_node(BST* bst, int data) {
	Node* tmp = bst->root;
	Node* p = NULL;

	while (tmp != NULL) {
		if (tmp->data == data) {
			printf("Error. Data already exists\n");
			return;
		}
		p = tmp;

		if (data > tmp->data) tmp = tmp->right;
		else tmp = tmp->left;
	}

	Node* new = (Node*)malloc(sizeof(Node));

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	if (data > p->data) p->right = new;
	else p->left = new;
}

void print(BST* bst, Node* search) {
	if (search == NULL) return;
	if (bst->root == search) printf("(");
	printf("%d", search->data);

	if (search->left != NULL || search->right != NULL) {
		printf("(");
		print(bst, search->left);
		printf(",");
		print(bst, search->right);
		printf(")");
	}

	if (bst->root == search) printf(")\n");
}

void inorder_traversal(BST* bst, Node* t) {
	if (t == NULL) return;

	inorder_traversal(bst, t->left);
	printf("%d ", t->data);
	inorder_traversal(bst, t->right);
	if (bst->root == t) printf("\n");
}

void right_root_left_traversal(BST* bst, Node* t) {
	if (t == NULL) return;
	
	right_root_left_traversal(bst, t->right);
	printf("%d ", t->data);
	right_root_left_traversal(bst, t->left);

	if (bst->root == t) printf("\n");
}

int get_min(BST* bst) {
	Node* tmp = bst->root;
	while (tmp->left != NULL) tmp = tmp->left;

	return tmp->data;
}

int get_max(BST* bst) {
	Node* tmp = bst->root;
	while (tmp->right != NULL) tmp = tmp->right;

	return tmp->data;
}

Node* search(BST* bst, int data) {
	Node* tmp = bst->root;

	while (tmp != NULL) {
		if (data == tmp->data) return tmp;
		else if (data > tmp->data) tmp = tmp->right;
		else tmp = tmp->left;
	}

	return tmp;
}

void find_node(BST* bst, Node* target) {
	printf("Root");

	Node* tmp = bst->root;

	while (tmp->data != target->data) {
		if (target->data > tmp->data) {
			printf(" > Right");
			tmp = tmp->right;
		}
		else {
			printf(" > Left");
			tmp = tmp->left;
		}
	}

	printf("\n");
}

Node* get_parent(BST* bst, Node* search, Node* target) { 

	if (search == NULL) return NULL;

	if (search->left == target || search->right == target) return search;

	Node* a;

	a = get_parent(bst, search->left, target);
	if (a) return a;

	a = get_parent(bst, search->right, target);
	if (a) return a;

	return NULL;
}

int delete_node(BST* bst, int data) {
	if (bst->root == NULL) { //BST empty
		printf("Error. Nothing to delete\n");
		return -1;
	}

	Node* target = search(bst, data);
	if (target == NULL) {
		printf("Error. Can't find target\n");
		return -1;
	}

	int item;

	if (target->left == NULL && target->right == NULL) { //자식노드가 아예 없을 때
		if (target == bst->root) {
			item = target->data;
			free(target);
			bst->root = NULL;
		}
		else {
			Node* p_target = get_parent(bst, bst->root, target);

			if (p_target->right == target) {
				p_target->right = target->left;
				item = target->data;
				free(target);
			}
			else {
				p_target->left = target->left;
				item = target->data;
				free(target);
			}
		}
	}
	else if (target->left != NULL && target->right == NULL) { //왼쪽에만 자식이 있을 때
		if (target == bst->root) {
			bst->root = target->left;
			item = target->data;
			free(target);
		}
		else {
			Node* p_target = get_parent(bst, bst->root, target);

			if (p_target->right == target) {
				p_target->right = target->left;
				item = target->data;
				free(target);
			}
			else {
				p_target->left = target->left;
				item = target->data;
				free(target);
			}
		}

	}
	else if (target->left == NULL && target->right != NULL) { //오른쪽에만 자식이 있을 때
		if (target == bst->root) {
			bst->root = target->right;
			item = target->data;
			free(target);
		}
		else {
			Node* p_target = get_parent(bst, bst->root, target);

			if (p_target->right == target) {
				p_target->right = target->right;
				item = target->data;
				free(target);
			}
			else {
				p_target->left = target->right;
				item = target->data;
				free(target);
			}
		}

	}
	else {
		Node* heir = target->left;

		while (heir->right != NULL) {
			heir = heir->right;
		}

		item = target->data;
		int heir_data = heir->data;

		delete_node(bst, heir->data);
		target->data = heir_data;
	}

	return item;
}

int height_of_node(BST* bst, Node* target) {

	int h = 0;

	while (target != bst->root) {
		target = get_parent(bst, bst->root, target);
		h++;
	}

	return h;
}

void height(BST* bst, Node* tmp, int* Height) {
	if (tmp == NULL) return;

	height(bst, tmp->left, Height);
	height(bst, tmp->right, Height);

	if (height_of_node(bst, tmp) > *Height) 
		*Height = height_of_node(bst, tmp);
}

void get_right_child(BST* Mbst, int data) {
	Node* target = search(Mbst, data);
	if (target == NULL) {
		printf("Error. No such data\n");
		return;
	}
	if (target->right == NULL) {
		printf("NULL\n");
		return;
	}
	Node* tmp = target->right;
	printf("%d\n", tmp->data);
}

void get_left_child(BST* Mbst, int data) {
	Node* target = search(Mbst, data);
	if (target == NULL) {
		printf("Error. No such data\n");
		return;
	}
	if (target->left == NULL) {
		printf("NULL\n");
		return ;
	}
	Node* tmp = target->left;
	printf("%d\n", tmp->data);
}

int count_node(Node* t) {
	if (t == NULL) return 0;
	return count_node(t->left) + count_node(t->right) + 1;
}

void clear(BST* bst) {
	if (bst->root == NULL) {
		printf("Error. Empty BST\n");
		return;
	}

	while (1) {
		if (bst->root == NULL) break;
		delete_node(bst, bst->root->data);
	}
}

void menu() {
	printf("==============♥MENU♥==============\n");
	printf("create						: +(data)\n");
	printf("insert_node					: +(data)\n");
	printf("print						: P\n");
	printf("inorder_traversal			: I\n");
	printf("right_root_left_traversal	: R\n");
	printf("get_min						: N(data)\n");
	printf("get_max						: X\n");
	printf("find_node					: F(data)\n");
	printf("delete_node					: -(data)\n");
	printf("height						: H\n");
	printf("get_right_child				: G(data)\n");
	printf("get_left_child				: L(data)\n");
	printf("clear						: K\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin \n");
	printf("====================================\n");
}

int main() {
	BST *my_BST = (BST*)malloc(sizeof(BST));
	init(my_BST);
	menu();
	
	while (1) {
		char arr[20] = { '\0', };
		printf(">> ");
		scanf("%s", arr);

		if (arr[0] == '+') {
			int i = 1;
			if (my_BST->root == NULL) {
				create(my_BST, st_num(arr, &i));
			}
			else {
				insert_node(my_BST, st_num(arr, &i));
			}
		}
		else if (arr[0] == 'P') printf("");
		else if (arr[0] == 'I') inorder_traversal(my_BST, my_BST->root);
		else if (arr[0] == 'R') right_root_left_traversal(my_BST, my_BST->root);
		else if (arr[0] == 'N') printf("%d\n", get_min(my_BST));
		else if (arr[0] == 'X') printf("%d\n", get_max(my_BST));
		else if (arr[0] == 'F') {
			int i = 1;
			Node* tmp = search(my_BST, st_num(arr, &i));
			if (tmp == NULL) printf("Error. Not Exist!\n");
			else find_node(my_BST, tmp);
		}
		else if (arr[0] == '-') {
			int i = 1;
			delete_node(my_BST, st_num(arr, &i));
		}
		else if (arr[0] == 'H') {
			if (my_BST->root == NULL) {
				printf("Error. Empty BST\n");
				continue;
			}
			int H;
			height(my_BST, my_BST->root, &H);
			printf("%d\n", H);
		}
		else if (arr[0] == 'G') {
			int i = 2;
			get_right_child(my_BST, st_num(arr, &i));
		}
		else if (arr[0] == 'L') {
			int i = 2;
			get_left_child(my_BST, st_num(arr, &i));
		}
		else if (arr[0] == '#') {
			printf("%d\n", count_node(my_BST->root));
		}
		else if (arr[0] == 'C') clear(my_BST);
		
		print(my_BST, my_BST->root);
	}
	
	return 0;
}