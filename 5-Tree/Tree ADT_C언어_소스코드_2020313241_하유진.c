#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)
#define N 10

//전위순환. 무조건 왼쪽부터
//왼쪽 자식 오른쪽 형재
typedef struct tagNode {
	char data;
	struct tagNode *left, *right;
}Node;

typedef struct tagTree {
	Node *root[10]; 
	int current; //현재 노드 degree
	int count; //전체 노드 개수
}Tree;

void init(Tree *tree) {
	for (int i=0;i<10;i++) tree->root[i] = NULL;
	tree->current = -1; 
	tree->count = 0;
}

void *create(Tree *tree, char data) { //루트노드 root[0] 생성 
	Node *new = (Node*)malloc(sizeof(Node));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	tree->root[0] = new;
	tree->current = 0;
	tree->count = 1;
}

Node *search(Node *tmp1, char data) { //data가 들어 있는 노드 리턴
	if (tmp1 == NULL) 
		return NULL;
	if (tmp1->data == data) 
		return tmp1;

	Node *tmp2 = (Node*)malloc(sizeof(Node));

	tmp2 = search(tmp1->left, data);
	if (tmp2) return tmp2;

	tmp2 = search(tmp1->right, data);
	if (tmp2) return tmp2;

	return NULL;
}

void insert_node(Tree *tree, Node *p, char c) { //left가 비어있으면 data를 추가하고 아니면 node->left의 right에 data 추가
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->data = c;
	newNode->left = NULL;
	newNode->right = NULL;

	if (p == NULL) return NULL;

	if (p->left == NULL) {
		p->left = newNode;
	}
	else {
		Node *tmp = p->left;
		while (tmp->right != NULL) {
			tmp = tmp->right;
		}
		tmp->right = newNode;
	}
	tree->count++;
}

void print(Node *root, Node *tmp1) {

	if (root == tmp1) printf("(%c", root->data);

	if (root->left == NULL) {
		printf(")\n");
		return;
	}

	Node *tmp2 = tmp1->left;
	printf("(");

	while (tmp2) {
		printf("%c", tmp2->data);
		if (tmp2->left != NULL) print(root, tmp2);
		tmp2 = tmp2->right;
	}

	printf(")");

	if (root == tmp1) printf(")\n");
}

Node *get_parent(Node *root, Node *target) {
	if (root == target) return NULL;

	Node *search = root->left;
	Node *answer = root;

	while (search) {
		Node *tmp = search;
		while (search) {
			if (search == target) {
				return answer;
			}
			if (search != tmp && search->left != NULL) {
				Node *answer2 = get_parent(search, target);
				if (answer2)
					return answer2;
			}
			search = search->right;
		}
		answer = tmp;
		search = tmp->left;
	}
}

void get_sibling(Tree *tree, Node *target) {//형제노드 찾기
	Node *search = get_parent(tree->root[tree->current], target)->left;
	printf("{");
	while (search) {
		if (search != target) {
			printf("%c", search->data);
		}
		search = search->right;
	}
	printf("}\n");
}

void get_child(Tree *tree, Node *target) {
	Node *search = target->left;
	if (search == NULL) {
		printf("자식 노드가 없습니다.");
	}
	else {
		printf("{");
		while (search != NULL) {
			printf("%c", search->data);
			search = search->right;
		}
		
		printf("}\n");
	}
}

int level_of_node(Tree *tree, Node *target) {
	Node *search = target;
	int i = -1;
	while (search) {
		search = get_parent(tree->root[tree->current], search);
		i++;
	}
	return i;
}

void level_of_tree(Tree *tree, Node *search, int *level) {
	if (search == NULL) return;
	level_of_tree(tree, search->left, level);
	level_of_tree(tree, search->right, level);

	if (level_of_node(tree, search) > *level) {
		*level = level_of_node(tree, search);
	}
}

void delete_node(Tree* tree, Node* target) {
	if (target->left != NULL) {
		printf("Error. parent node는 삭제할 수 없습니다.\n");
		return;
	}

	if (tree->root[tree->current] == target) {
		tree->root[tree->current] = NULL;
		printf("Delete finished : %c\n", target->data);
		free(target);
	}
	else {
		Node* tmp = get_parent(tree->root[tree->current], target);

		if (tmp->left == target) {
			tmp->left = tmp->left->right;
			free(target);
			return;
		}
		else {
			tmp = tmp->left;
			while (tmp->right != target) {
				tmp = tmp->right;
			}
			tmp->right = tmp->right->right;
			free(target);
		}
	}
	return;
}

void get_ancestors(Tree* tree, Node* target) {
	if (target == tree->root[tree->current]) {
		printf("Error. Root 입니다.\n");
		return;
	}
	Node* tmp = target;

	while (1) {
		tmp = get_parent(tree->root[tree->current], tmp);

		printf("%c ", tmp->data);

		if (tmp == tree->root[tree->current]) {
			break;
		}
	}
	printf("\n");
}

void get_descendants(Node* target) {

	if (target->left == NULL) {
		printf("Error. child가 없습니다.\n");
		return;
	}

	Node* tmp = target->left;

	while (tmp) {
		printf("%c ", tmp->data);

		if (tmp->left != NULL) {
			print(target, tmp);
		}
		tmp = tmp->right;
	}

	printf("\n");
}

int degree_of_node(Tree* tree, Node* target) {
	int d = 0;
	Node* search = target->left;
	while (search) {
		d+=1;
		search = search->right;
	}
	return d;
}

void degree_of_tree(Tree* tree, Node *search, int* d) {
	if (search == NULL) return;
	
	degree_of_tree(tree, search->left, d);
	degree_of_tree(tree, search->right, d);

	if (degree_of_node(tree, search) > *d) *d = degree_of_node(tree, search);
}

int count_node(Node* search) {
	if (search == NULL) return 0;
	return count_node(search->left) + count_node(search->right) + 1;
}

void insert_sibling(Tree* Mtree, Node* target, char data) {
	Node* new = (Node*)malloc(sizeof(Node));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	Node* tmp = target;
	while (tmp->right) tmp = tmp->right;
	tmp->right = new;
}

Node* copy(Node* search) {
	if (search == NULL) return NULL;
	else {
		Node* new = (Node*)malloc(sizeof(Node));
		new->data = search->data;
		new->left = NULL;
		new->right = NULL;

		new->left = copy(search->left);
		new->right = copy(search->right);

		return new;
	}
}

void join_trees(Tree* Mtree, char data, int index1, int index2) {
	if (Mtree->root[index1] == NULL || Mtree->root[index2] == NULL) 
		printf("Error.\n");
	else {
		create(Mtree, data);
		Node* left = copy(Mtree->root[index1]);
		Node* right = copy(Mtree->root[index2]);

		Mtree->root[Mtree->current]->left = left;
		left->right = right;
	}
}

void clear(Node* search) {
	if (search == NULL) {
		return;
	}

	clear(search->left);
	clear(search->right);

	free(search);
}

void menu() {
	printf("==============♥MENU♥==============\n");
	printf("create			: +^(data)\n");
	printf("insert_node		: +(node)(data list)\n");
	printf("get_sibling		: S\n");
	printf("print			: T\n");
	printf("get_parent		: P\n");
	printf("get_child		: C\n");
	printf("level_of_node	: L(data)\n");
	printf("level_of_tree	: L\n");
	printf("delete_node		: -(data)\n");
	printf("get_ancestors	: A(data)\n");
	printf("get_descendants	: D(data)\n");
	printf("degree_of_node	: G(data)\n");
	printf("degree_of_tree	: G\n");
	printf("count_node		: #\n");
	printf("insert_sibling	: =+(node)(s_list)\n");
	printf("join_trees		: J(new_root, t1, t2)\n");
	printf("	t1, t2 is index numbers (0~10)\n");
	printf("clear			: K\n");
	printf("------------------------------------\n");
	printf("* Don't make space between commands\n");
	printf("* Programed by Ha Yujin \n");
	printf("====================================\n");
}

int main() {
	Tree *my_tree = (Tree*)malloc(sizeof(Tree));
	init(my_tree);
	menu();

	while (1) {
		//쉽표 없이

		char arr[20] = { '\0', };
		printf(">> ");
		scanf("%s", arr);

		if (arr[0] == '+') {
			if (arr[1] == '^') {
				create(my_tree, arr[2]);
			}
			else if (arr[2] == '(') {
				Node *target = search(my_tree->root[my_tree->current], arr[1]);
				if (target == NULL) {
					printf("Error. data를 찾을 수 없습니다.\n");
				}
				for (int i = 3; arr[i] != ')'; i++) {
					if (search(my_tree->root[my_tree->current], arr[i]) != NULL) {
						printf("이미 있는 값입니다.\n");
						continue;
					}
					insert_node(my_tree, target, arr[i]);
				}
			}
		}
		else if (arr[0] == 'S') {
			Node *target = search(my_tree->root[my_tree->current], arr[2]);
			if (target == NULL) {
				printf("Error. data를 찾을 수 없습니다.\n");
				continue;
			}
			get_sibling(my_tree, target);
		}
		else if (arr[0] == 'T') {
			if (my_tree->count > 0)
				print(my_tree->root[my_tree->current], my_tree->root[my_tree->current]);
			else
				printf("출력할 값이 없습니다.\n");
		}
		else if (arr[0] == 'P') {
			Node *target = search(my_tree->root[my_tree->current], arr[2]);
			if (target == NULL) {
				printf("Error. data를 찾을 수 없습니다.\n");
				continue;
			}
			printf("%c\n", get_parent(my_tree->root[my_tree->current], target)->data);
		}
		else if (arr[0] == 'C') {
			Node *target = search(my_tree->root[my_tree->current], arr[2]);
			if (target == NULL) {
				printf("Error. data를 찾을 수 없습니다.\n");
				continue;
			}
			get_child(my_tree, target);
		}
		else if (arr[0] == 'L') {
			if (arr[1] !='(') {
				int level = 0;
				level_of_tree(my_tree, my_tree->root[my_tree->current], &level);
				printf("%d\n", level);
			}
			else {
				Node *target = search(my_tree->root[my_tree->current], arr[2]);
				if (target == NULL) {
					printf("Error. data를 찾을 수 없습니다.\n");
					continue;
				}
				printf("%d\n", level_of_node(my_tree, target));
			}
		}
		else if (arr[0] == '-') {
			Node *target = search(my_tree->root[my_tree->current], arr[1]);
			if (target == NULL) {
				printf("Error. data를 찾을 수 없습니다.\n");
				continue;
			}
			delete_node(my_tree, target); 
		}
		else if (arr[0] == 'A') {
			Node* target = search(my_tree->root[my_tree->current], arr[2]);
			if (target == NULL) {
				printf("  Error. data를 찾을 수 없습니다.\n");
				continue;
			}
			get_ancestors(my_tree, target);
		}
		else if (arr[0] == 'D') {
			Node* target = search(my_tree->root[my_tree->current], arr[2]);
			if (target == NULL) {
				printf("  Error. data를 찾을 수 없습니다.\n");
				continue;
			}
			get_descendants(target);
		}
		else if (arr[0] == 'G') {
			if (arr[1] == '(') {
				Node* target = search(my_tree->root[my_tree->current], arr[2]);
				if (target == NULL) {
					printf("  Error. data를 찾을 수 없습니다.\n");
					continue;
				}
				printf("%d\n", degree_of_node(my_tree, target));
			}
			else {
				int degree = 0;
				degree_of_tree(my_tree, my_tree->root[my_tree->current], &degree);
				printf("%d\n", degree);
			}
		}
		else if (arr[0] == '#') {
			printf("%d\n", count_node(my_tree->root[my_tree->current]));
		}
		else if (arr[0] == '=') {
			Node* target = search(my_tree->root[my_tree->current], arr[2]);

			if (target == NULL) {
				printf("Error. data를 찾을 수 없습니다.\n");
				continue;
			}

			for (int i = 4; arr[i] != ')'; i++) {
				if (search(my_tree->root[my_tree->current], arr[i]) != NULL) {
					printf("Error. %c already exist\n", arr[i]);
					continue;
				}
				insert_sibling(my_tree, target, arr[i]);
			}
		}
		else if (arr[0] == 'J') join_trees(my_tree, arr[2], arr[4] - '0', arr[6] - '0');
		else if (arr[0] == 'K') clear(my_tree->root[my_tree->current]);
		else {
			printf("잘못 입력하셨습니다.\n");
		}

		if (my_tree->count > 0) 
			print(my_tree->root[my_tree->current], my_tree->root[my_tree->current]);
		else 
			printf("Nothing to print\n");
	}
	return 0;
}

//쉼표 없이!!