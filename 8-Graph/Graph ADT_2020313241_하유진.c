
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)

typedef struct vertex {
	struct vertex* next;
	char data;
	struct edge* connect;
	int count_edge;
	int visited;
}VERTEX;

typedef struct edge {
	VERTEX* vertex;
	struct edge* more;
}EDGE;

typedef struct graph {
	int count_vertex;
	VERTEX* head;
}GRAPH;

void create(GRAPH* MG) {
	MG->head = NULL;
	MG->count_vertex = 0;
}

void print(GRAPH* MG) {
	VERTEX* tmp = MG->head;
	printf("  (");

	while (tmp) {
		printf("%c", tmp->data);

		EDGE* tmp2 = tmp->connect;
		while (tmp2) {
			if (tmp2 == tmp->connect) printf("(");
			printf("%c", tmp2->vertex->data);

			if (tmp2->more != NULL) printf(",");
			tmp2 = tmp2->more;
			if (tmp2 == NULL) printf(")");
		}

		if (tmp->next != NULL) 
			printf(", ");
		tmp = tmp->next;
	}
	printf(")\n");
}

void insert_vertex(GRAPH* MG, char data) {
	if (!is_empty(MG) && is_exist_vertex(MG, data)) {
		printf("Error. Already Exist Data\n");
		return;
	}

	VERTEX* new_vertex = (VERTEX*)malloc(sizeof(VERTEX));
	new_vertex->connect = NULL;
	new_vertex->visited = 0;
	new_vertex->next = NULL;
	new_vertex->data = data;
	new_vertex->count_edge = 0;

	if (is_empty(MG)) 
		MG->head = new_vertex;
	else {
		VERTEX* target = MG->head;

		while (target->next != NULL) 
			target = target->next;
		target->next = new_vertex;
	}
	MG->count_vertex++;
}

int is_exist_vertex(GRAPH* MG, char data) {
	VERTEX* tmp = MG->head;

	while (1) {
		if (tmp == NULL) return 0;
		if (tmp->data == data) return 1;
		tmp = tmp->next;
	}
}

int is_empty(GRAPH* MG) {
	if (MG->head == NULL) return 1;
	else return 0;
}

VERTEX* search_vertex(GRAPH* MG, char data) {
	if (!is_exist_vertex(MG, data)) {
		printf("Error. Vertex 가 없습니다.\n");
		return NULL;
	}
	VERTEX* result = MG->head;

	while (1) {
		if (result->data == data) return result;
		result = result->next;
	}
}

int is_exist_edge(GRAPH* MG, char data1, char data2) { //쓸 때 data 둘 다 이미 있는 거 알고 있어야 함
	VERTEX* tmp = search_vertex(MG, data1);
	EDGE* tmp2 = tmp->connect;

	while (1) {
		if (tmp2 == NULL) return 0;

		if (tmp2->vertex->data == data2) return 1;
		tmp2 = tmp2->more;
	}
}

void add_edge(GRAPH* MG, char data1, char data2) {
	if (!is_exist_vertex(MG, data1) || !is_exist_vertex(MG, data2)) {
		printf("Error. Vertex doesn't Exist\n");
		return;
	}
	if (is_exist_edge(MG, data1, data2)) {
		printf("Error. Edge already Exist\n");
		return;
	}

	VERTEX* target1 = search_vertex(MG, data1);
	VERTEX* target2 = search_vertex(MG, data2);

	EDGE* new1 = (EDGE*)malloc(sizeof(EDGE));
	new1->more = NULL;
	new1->vertex = target2;

	if (target1->connect == NULL) 
		target1->connect = new1;
	else {
		EDGE* target3 = target1->connect;

		while (target3->more != NULL) 
			target3 = target3->more;

		target3->more = new1;
	}
	target1->count_edge++;

	EDGE* new2 = (EDGE*)malloc(sizeof(EDGE));
	new2->more = NULL;
	new2->vertex = target1;

	if (target2->connect == NULL)
		target2->connect = new2;
	else {
		EDGE* target4 = target2->connect;

		while (target4->more != NULL) 
			target4 = target4->more;

		target4->more = new2;
	}
	target2->count_edge++;
}


int degree_of_vertex(GRAPH* MG, char data) {
	VERTEX* tmp = search_vertex(MG, data);

	if (tmp == NULL) return -1;
	else return tmp->count_edge;
}

int is_connected(GRAPH* MG) {
	VERTEX* tmp = MG->head;

	while (tmp) {
		if (tmp->count_edge == 0) return 0;
		tmp = tmp->next;
	}
	return 1;
}

void adjacent(GRAPH* MG, char data) {

	VERTEX* target = search_vertex(MG, data);
	if (target == NULL) return;
	EDGE* tmp = target->connect;

	printf("{");
	while (1) {
		if (tmp == NULL) break;
		printf("%c", tmp->vertex->data);

		if (tmp->more != NULL) 
			printf(", ");
		tmp = tmp->more;
	}
	printf("}\n");
}

void delete_vertex(GRAPH* MG, char data) {
	VERTEX* target = search_vertex(MG, data);
	if (target == NULL) {
		return;
	}
	if (target->connect == NULL) {
		if (MG->head == target) {
			MG->head = MG->head->next;
			free(target);
		}
		else {
			VERTEX* tmp = MG->head;
			while (tmp->next != target) {
				tmp = tmp->next;
			}
			tmp->next = tmp->next->next;
			free(target);
		}
	}
	else {
		int A;
		printf("Edge가 있음, 1.무시  2. 취소\n  : ");
		scanf("%d", &A);
		getchar();

		if (A == 2) return;
		else {

			EDGE* dt = target->connect;
			printf("  Deleted Edge: (");
			printf("%c", dt->vertex->data);
			for (int i = 1; i < target->count_edge; i++) {
				dt = dt->more;
				printf(",%c", dt->vertex->data);
			}
			printf(")\n");

			EDGE* e_target = target->connect;
			VERTEX* v_target = NULL; 
			EDGE* e_v_target = NULL; 

			EDGE* d_e_v_target = NULL;
			EDGE* d_e_target = NULL;

			while (e_target) {
				v_target = search_vertex(MG, e_target->vertex->data);
				e_v_target = v_target->connect;

				if (e_v_target->vertex->data == target->data) {
					d_e_v_target = e_v_target;
					v_target->connect = v_target->connect->more;
				}
				else {
					while (e_v_target->more->vertex->data != target->data) {
						e_v_target = e_v_target->more;
					}
					d_e_v_target = e_v_target->more;
					e_v_target->more = e_v_target->more->more;
				}

				v_target->count_edge--;
				free(d_e_v_target);

				d_e_target = e_target;
				target->connect = target->connect->more;
				e_target = target->connect;

				target->count_edge--;
				free(d_e_target);
			}
			if (MG->head == target) {
				MG->head = MG->head->next;
				free(target);
			}
			else {
				VERTEX* tmp = MG->head;
				while (tmp->next != target) {
					tmp = tmp->next;
				}
				tmp->next = tmp->next->next;
				free(target);
			}
		}
	}
	MG->count_vertex--;
}




int path_exist(GRAPH* MG, VERTEX* d1, VERTEX* d2) {
	if (d1 == d2) return 1;

	EDGE* tmp = d1->connect;
	d1->visited = 1;

	while (tmp) {
		if (!tmp->vertex->visited) {
			if (path_exist(MG, tmp->vertex, d2))
				return 1;
		}
		tmp = tmp->more;
	}
	return 0;
}

void visited_initialize(GRAPH* MG) {
	VERTEX* tmp = MG->head;

	for (int i = 0; i < MG->count_vertex; i++) {
		tmp->visited = 0;
		tmp = tmp->next;
	}
}

int num_of_vertex(GRAPH* MG) {
	return MG->count_vertex;
}

int num_of_edge(GRAPH* MG) {
	int count = 0;

	VERTEX* tmp = MG->head;

	for (int i = 0; i < num_of_vertex(MG); i++) {
		count += tmp->count_edge;
		tmp = tmp->next;
	}

	return (count / 2);
}

void delete_edge(GRAPH* MG, char data1, char data2) {
	VERTEX* target1 = search_vertex(MG, data1);
	VERTEX* target2 = search_vertex(MG, data2);

	if (target1 == NULL || target2 == NULL) {
		return;
	}

	if (!is_exist_edge(MG, data1, data2)) {
		printf("  [Error] Edge already Not Exist\n");
		return;
	}

	EDGE* tmp1 = target1->connect;
	EDGE* del1 = NULL;

	if (tmp1->vertex->data == data2) {
		del1 = tmp1;
		target1->connect = target1->connect->more;
	}
	else {
		while (tmp1->more->vertex->data != data2) {
			tmp1 = tmp1->more;
		}
		del1 = tmp1->more;
		tmp1->more = tmp1->more->more;
	}

	target1->count_edge--;
	free(del1);

	EDGE* tmp2 = target2->connect;
	EDGE* del2 = NULL;

	if (tmp2->vertex->data == data1) {
		del2 = tmp2;
		target2->connect = target2->connect->more;
	}
	else {
		while (tmp2->more->vertex->data != data1)
			tmp2 = tmp2->more;
		del2 = tmp2->more;
		tmp2->more = tmp2->more->more;
	}

	target2->count_edge--;
	free(del2);
}

void rename_vertex(GRAPH* MG, char old, char new) {
	VERTEX* target_v = search_vertex(MG, old);
	if (target_v == NULL) return;
	
	if (is_exist_vertex(MG, new)) {
		printf("  [Error] New Data already Exist\n");
		return;
	}

	target_v->data = new;

	EDGE* target_e = target_v->connect;
	EDGE* search = NULL;

	while (target_e) {
		search = target_e->vertex->connect;
		while (search) {
			if (search->vertex->data == old) 
				search->vertex->data = new;
			
			search = search->more;
		}
		target_e = target_e->more;
	}
}

void clear(GRAPH* MG) {
	if (is_empty(MG)) {
		printf("Error. Empty Graph\n");
		return;
	}
	while (!is_empty(MG)) 
		delete_vertex_for_clear(MG, MG->head->data);
	printf("  Clear Finished\n");
}

void delete_vertex_to_clear(GRAPH* MG, char data) {
	VERTEX* target = search_vertex(MG, data);
	if (target == NULL) return;
	if (target->connect == NULL) {
		if (MG->head == target) {
			MG->head = MG->head->next;
			free(target);
		}
		else {
			VERTEX* tmp = MG->head;
			while (tmp->next != target) 
				tmp = tmp->next;
			tmp->next = tmp->next->next;
			free(target);
		}
	}
	else {
		EDGE* dt = target->connect;

		EDGE* e_target = target->connect;
		VERTEX* v_target = NULL; 
		EDGE* e_v_target = NULL; 

		EDGE* d_e_v_target = NULL;
		EDGE* d_e_target = NULL;

		while (e_target) {
			v_target = search_vertex(MG, e_target->vertex->data);
			e_v_target = v_target->connect;

			if (e_v_target->vertex->data == target->data) {
				d_e_v_target = e_v_target;
				v_target->connect = v_target->connect->more;
			}
			else {
				while (e_v_target->more->vertex->data != target->data) 
					e_v_target = e_v_target->more;
				d_e_v_target = e_v_target->more;
				e_v_target->more = e_v_target->more->more;
			}
			v_target->count_edge--;
			free(d_e_v_target);

			d_e_target = e_target;
			target->connect = target->connect->more;
			e_target = target->connect;

			target->count_edge--;
			free(d_e_target);
		}
		if (MG->head == target) {
			MG->head = MG->head->next;
			free(target);
		}
		else {
			VERTEX* tmp = MG->head;
			while (tmp->next != target) 
				tmp = tmp->next;
			
			tmp->next = tmp->next->next;
			free(target);
		}
	}
	MG->count_vertex--;
}

int main() {
	char arr[30];
	GRAPH* my_graph = (GRAPH*)malloc(sizeof(GRAPH));

	while (1) {
		printf(">> ");
		scanf("%s", arr);

		/*if (arr[0] == 'G') {
			create(my_graph);
		}
		else if (arr[0] == '+') {
			insert_vertex(my_graph, arr[1]);
		}
		else if (arr[0] == 'E') {
			add_edge(my_graph, arr[2], arr[4]);
		}
		else if (arr[0] == 'L') {
			continue;
		}
		else if (arr[0] == 'P') {
			VERTEX* V1 = search_vertex(my_graph, arr[2]);
			VERTEX* V2 = search_vertex(my_graph, arr[4]);
			if (path_exist(my_graph, V1, V2)) {
				printf("True\n");
				visited_initialize(my_graph);
			}
			else printf("False\n");
			visited_initialize(my_graph);
		}
		else if (arr[0] == 'X') 
			printf("%d\n", num_of_vertex(my_graph));
		
		else if (arr[0] == 'H') 
			printf("%d\n", num_of_edge(my_graph));
		
		else if (arr[0] == 'D') 
			delete_edge(my_graph, arr[2], arr[4]);
		
		else if (arr[0] == 'R') 
			rename_vertex(my_graph, arr[2], arr[4]);
		
		else if (arr[0] == 'K') 
			clear(my_graph);
		
		else if (arr[0] == 'Q') {
			printf("Exit Program\n");
			break;
		}*/
		print(my_graph);
	}

	return 0;
}

