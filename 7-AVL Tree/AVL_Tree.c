//create까지 구현하였습니다

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)


typedef struct Node {
	int data;
	int height;
	struct Node *left, *right;
}Node;

typedef struct AVL {
	Node *root;
}AVL;

void init(AVL *avl) {
	avl->root = NULL;
}

void create(AVL *avl, int data) {
	Node *new = (Node*)malloc(sizeof(Node));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	avl->root = new;
}

void print(AVL *avl, Node *tmp) {

	if (tmp == NULL) {
		return;
	}

	if (avl->root == tmp) {
		printf("(");
	}

	printf("%d", tmp->data);
	
	if (tmp->left != NULL || tmp->right != NULL) {
		printf("(");
		print(avl, tmp->left);
		printf(",");
		print(avl, tmp->right);
		printf(")");
	}

	if (avl->root == tmp) {
		printf(")\n");
	}
}



Node* get_parent(Node* search, Node* target) {
	if (search == NULL) return NULL;

	if (search->left == target || search->right == target) 
		return search;

	Node* a;

	a = get_parent(search->left, target);
	if (a) return a;

	a = get_parent(search->right, target);
	if (a) return a;

	return NULL;
}

int height_node(Node* root, Node* target) {
	int h = 0;
	while (target != root) {
		target = get_parent(root, target);
		h++;
	}
	return h;
}

void height_tree(Node* root, Node* tmp, int* H) {

	if (tmp == NULL) return;

	height_tree(root, tmp->left, H);
	height_tree(root, tmp->right, H);

	if (height_node(root, tmp) > *H)
		*H = height_node(root, tmp);
}

int balance_factor(Node* root) {
	int LH = -1, RH = -1;

	height_tree(root->left, root->left, &LH);
	height_tree(root->right, root->right, &RH);

	return LH - RH;
}

Node* R_rotate(Node* root) {
	Node* parent = root;
	Node* child = parent->left;

	parent->left = child->right;
	child->right = parent;

	return child;
}

Node* L_rotate(Node* root) {
	Node* parent = root;
	Node* child = parent->right;

	parent->right = child->left;
	child->left = parent;

	return child;
}

Node* LR_rotate(Node* root) {
	Node* parent = root;
	Node* child = parent->left;

	parent->left = L_rotate(child);

	return R_rotate(parent);
}

Node* RL_rotate(Node* root) {
	Node* parent = root;
	Node* child = parent->right;

	parent->right = R_rotate(child);

	return L_rotate(parent);
}

Node* balancing(Node** root) {
	if (*root == NULL) {
		return NULL;
	}
	(*root)->left = balancing(&(*root)->left);
	(*root)->right = balancing(&(*root)->right);

	int bf = balance_factor(*root);

	if (-1 <= bf && bf <= 1) return *root;

	if (bf >= 2) {
		if (balance_factor((*root)->left) >= 1) 
			*root = R_rotate(*root);
		else *root = LR_rotate(*root);
	}

	if (bf <= -2) {
		if (balance_factor((*root)->right) <= -1) 
			*root = L_rotate(*root);
		else *root = RL_rotate(*root);
	}

	return *root;
}

void insert_node(AVL* Mavl, int data) {
	Node* tmp = Mavl->root;
	Node* p = NULL;

	while (tmp != NULL) {
		if (tmp->data == data) {
			printf("Error. 이미 존재하는 data\n");
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

	Mavl->root = balancing(&Mavl->root);
}

Node* search(AVL* Mavl, int data) {
	Node* tmp = Mavl->root;

	while (tmp != NULL) {
		if (data == tmp->data) return tmp;
		else if (data > tmp->data) tmp = tmp->right;
		else tmp = tmp->left;
	}

	return tmp;
}

void inorder_traversal(AVL* Mavl, Node* t) {
	if (t == NULL) return;

	inorder_traversal(Mavl, t->left);
	printf("%d ", t->data);
	inorder_traversal(Mavl, t->right);

	if (Mavl->root == t) printf("\n");
}

void right_root_left_traversal(AVL* Mavl, Node* traverse) {
	if (traverse == NULL) return;

	right_root_left_traversal(Mavl, traverse->right);
	printf("%d ", traverse->data);
	right_root_left_traversal(Mavl, traverse->left);

	if (Mavl->root == traverse) printf("\n");
}

int get_min(AVL* Mavl) {
	Node* tmp = Mavl->root;

	while (tmp->left != NULL) tmp = tmp->left;

	return tmp->data;
}

int get_max(AVL* Mavl) {
	Node* tmp = Mavl->root;

	while (tmp->right != NULL) tmp = tmp->right;

	return tmp->data;
}

void find_node(AVL* avl, Node* target) {
	printf("Root");

	Node* tmp = avl->root;

	while (tmp->data != target->data) {
		if (target->data > tmp->data) {
			printf(" - Right");
			tmp = tmp->right;
		}
		else {
			printf(" - Left");
			tmp = tmp->left;
		}
	}

	printf("\n");
}

void get_right_child(AVL* avl, int data) {
	Node* target = search(avl, data);
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

void get_left_child(AVL* avl, int data) {
	Node* target = search(avl, data);
	if (target == NULL) {
		printf("Error. No such data\n");
		return;
	}
	if (target->left == NULL) {
		printf("NULL\n");
		return;
	}
	Node* tmp = target->left;
	printf("%d\n", tmp->data);
}

int count_node(Node* t) {
	if (t == NULL) return 0;
	return count_node(t->left) + count_node(t->right) + 1;
}

int delete_node(AVL* avl, int data) {
	if (avl->root == NULL) {
		printf("Error. Nothing to delete\n");
		return -1;
	}

	Node* target = search(avl, data);
	if (target == NULL) {
		printf("Error. Can't find target\n");
		return -1;
	}

	int item;

	if (target->left == NULL && target->right == NULL) { 
		if (target == avl->root) {
			item = target->data;
			free(target);
			avl->root = NULL;
		}
		else {
			Node* p_target = get_parent(avl->root, target);

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
	else if (target->left != NULL && target->right == NULL) { 
		if (target == avl->root) {
			avl->root = target->left;
			item = target->data;
			free(target);
		}
		else {
			Node* p_target = get_parent(avl->root, target);

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
	else if (target->left == NULL && target->right != NULL) { 
		if (target == avl->root) {
			avl->root = target->right;
			item = target->data;
			free(target);
		}
		else {
			Node* p_target = get_parent(avl->root, target);

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

		delete_node(avl, heir->data);
		target->data = heir_data;
	}

	return item;
}

void clear(AVL* avl) {
	if (avl->root == NULL) {
		printf("Error. Empty AVL\n");
		return;
	}

	while (1) {
		if (avl->root == NULL) break;
		delete_node(avl, avl->root->data);
	}
}

void menu() {
	printf("==============♥MENU♥==============\n");
	printf("create						: +(data)\n");
	printf("insert_node					: +(data)\n");
	printf("print						: P\n");
	printf("balance_factor			: B\n");
	printf("inorder_traversal	: I\n");
	printf("right_root_left_traversal	: R\n");
	printf("get_min						: N\n");
	printf("get_max						: X\n");
	printf("find_node					: F(data)\n");
	printf("height_tree					: T\n");
	printf("height_node					: H(data)\n");
	printf("get_right_child				: G(data)\n");
	printf("get_left_child				: L(data)\n");
	printf("count_node					: #\n");
	printf("delete_node					: -(data)\n");
	printf("clear						: K\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin \n");
	printf("====================================\n");
}

int main() {
	
	AVL *my_AVL = (AVL*)malloc(sizeof(AVL));
	init(my_AVL);
	menu();
	
	while (1) {
		char arr[20] = { '/0', };
		printf(">> ");
		scanf("%s", arr);

		if (arr[0] == '+') {
			if (my_AVL->root == NULL) {
				create(my_AVL, arr[1] - 48);
			}
			else {
				insert_node(my_AVL, arr[1] - 48);
			}
		}
		else if (arr[0] == 'P') {
			printf("");
		}
		else if (arr[0] == 'B') {
			int tmp = search(my_AVL, arr[1] - 48);
			if (tmp == NULL) {
				printf("Error. Can't find target\n");
				continue;
			}
			printf("%d\n", balance_factor(tmp));
		}
		else if (arr[0] == 'I')
			inorder_traversal(my_AVL, my_AVL->root);

		else if (arr[0] == 'R')
			right_root_left_traversal(my_AVL, my_AVL->root);

		else if (arr[0] == 'N') {
			if (my_AVL->root == NULL)
				printf("Error. Empty AVL\n");
			else
				printf("%d\n", get_min(my_AVL));
		}
		else if (arr[0] == 'X') {
			if (my_AVL->root == NULL)
				printf("  [Error] Empty AVL\n");
			else
				printf("%d\n", get_max(my_AVL));
		}
		else if (arr[0] == 'F') {
			Node* tmp = search(my_AVL, arr[1] - 48);

			if (tmp == NULL) printf("Error. Not Exist!\n");
			else find_node(my_AVL, tmp);
		}
		else if (arr[0] == 'T') {
			if (my_AVL->root == NULL) {
				printf("Error. Empty AVL\n");
				continue;
			}
			int H;
			height_tree(my_AVL->root, my_AVL->root, &H);
			printf("%d\n", H);
		}
		else if (arr[0] == 'H') {
			Node* tmp = search(my_AVL, arr[1] - 48);
			int H = height_node(my_AVL->root, tmp);
			printf("%d\n", H);
		}
		else if (arr[0] == 'G') {
			get_right_child(my_AVL, arr[1] - 48);
		}
		else if (arr[0] == 'L') {
			get_left_child(my_AVL, arr[1] - 48);
		}
		else if (arr[0] == '#') {
			printf("%d\n", count_node(my_AVL->root));
		}
		else if (arr[0] == '-') {
			delete_node(my_AVL, arr[1] - 48);
		}
		else if (arr[0] == 'C') clear(my_AVL);
			

		print(my_AVL, my_AVL->root);
	}

	
	return 0;
}
