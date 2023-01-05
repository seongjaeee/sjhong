#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__ )
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

typedef struct node {
	char* data;
	struct node* link;
}Node;

Node* head;
void show_all() {
	printf("head");
	for (Node* n = head; n != NULL; n = n->link)
		printf(" - %s", n->data);
	printf(" - null\n\n");
}
void get_Rand(char* str, int size) {
	int i;
	for (i = 0; i < size; i++)
		str[i] = 'a' + rand() % 26;
	str[i] = 0;
}
int insert_by_index(int index) {
	int size = rand() % 50 + 10;

	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) { printf("(insert): 동적 할당 실패 "); return -1; }

	char* str = (char*)malloc(sizeof(char) * size + 1);
	if (str == NULL) { printf("(insert(str)): 동적 할당 실패"); return -1; }
	get_Rand(str, size);

	if (index == 0) {
		new_node->data = str;
		new_node->link = head;
		head = new_node;

		show_all();
		return 0;
	}
	else {
		Node* tmp = head;
		while (index - 1 != NULL) {
			tmp = tmp->link;
			index--;
		}

		new_node->data = str;
		new_node->link = tmp->link;
		tmp->link = new_node;

		show_all();
		return 0;
	}
}
int delete_by_index(int index) {
	Node* tmp;
	if (index == 0) {
		tmp = head;
		head = tmp->link;

		free(tmp->data);
		free(tmp);
		show_all();
		return 0;
	}
	else {
		tmp = head->link;
		while (index - 1 != NULL) {
			tmp = tmp->link;
			index--;
		}
		head->link = tmp->link;
		free(tmp->data);
		free(tmp);
		show_all();
		return 0;
	}
}
void delete_all() {
	Node* del = head;
	while (del != NULL) {
		Node* tmp = del->link;
		free(del->data);
		free(del);
		del = tmp;
	}
	printf(" 전체 노드 삭제 완료\n");
}
void error_check(int val) {
	if (val == -1) {
		delete_all();
		printf("오류 발생 : 프로그램 종료");
		exit(1);
	}
	else;
}

//		head -> n1 -> n2 -> n3 ...
//		index:	 0     1     2 ...
int main() {
	head = NULL;
	srand((unsigned int)time(0));

	// 0번째 인덱스 위치 삽입
	error_check(insert_by_index(0));

	// 1번째 인덱스 위치 삽입
	error_check(insert_by_index(1));

	// 0번째 인덱스 위치 삽입
	error_check(insert_by_index(0));

	// 0번째 인덱스 위치 삭제
	error_check(delete_by_index(0));

	// 1번째 인덱스 위치 삭제
	error_check(delete_by_index(1));

	delete_all();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}