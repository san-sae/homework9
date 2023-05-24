/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

// 노드에 대한 구조체
typedef struct node {
	int key; // 키 값
	struct node *left; // 왼쪽 자식 노드를 가리키는 포인터
	struct node *right; // 오른쪽 자식 노드를 가리키는 포인터
} Node;

int initializeBST(Node** h); // 트리 초기화 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main(){

	printf("[----- [Choi Yoolim] [2020022001] -----]");

	char command; // 명령어
	int key; // 입력할 키 값
	Node* head = NULL; // 트리의 헤드노드
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령어 입력

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // 트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head); // 동적 할당 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 사용자로부터 키 값 입력 받음
			insert(head, key); // key값을 가진 노드를 트리에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // 사용자로부터 키 값 입력 받음
			deleteLeafNode(head, key); // key값을 가진 노드를 트리에서 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // 사용자로부터 키 값 입력 받음
			ptr = searchIterative(head, key); // 비재귀 방식으로 노드 탐색
			if(ptr != NULL) // 같은 키값을 가진 노드가 있는 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else  // 같은 키값을 가진 노드가 없는 경우
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); // 사용자로부터 키값 입력 받음
			ptr = searchRecursive(head->left, key); // 재귀 방식으로 탐색 
			if(ptr != NULL) // 같은 키값을 가진 노드가 있는 경우
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else // 같은 키값을 가진 노드가 없는 경우
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 'i': case 'I':
			inorderTraversal(head->left); // 중위 순회 방식
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 전위 순회 방식
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 후위 순회 방식
			break;
		default: // 그 이외의 명령어는 유효하지 않음
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

// 트리 초기화 함수
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h); // 트리에 대한 동적할당 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 헤드노드에 대한 동적 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; // 자신을 가리킴
	(*h)->key = -9999; // BST의 루트를 가리키는 역할, 데이터 저장X
	return 1;
}

// 중위 순회 방식으로 트리의 노드 출력하는 함수
// 왼쪽 서브트리 -> 루트 노드 -> 오른쪽 서브트리
void inorderTraversal(Node* ptr){
	if(ptr) { // ptr(현재 노드)이 존재하는 경우
		inorderTraversal(ptr->left); // ptr(주소값)이 가리키는 왼쪽 자식 노드를 재귀 호출
		printf(" [%d] ", ptr->key); // ptr의 키 값 출력
		inorderTraversal(ptr->right); // ptr의 오른쪽 자식 노드를 재귀 호출
	}
}

// 전위 순회 방식으로 트리의 노드 출력하는 함수
// 루트 노드 -> 왼쪽 서브트리 -> 오른쪽 서브트리
void preorderTraversal(Node* ptr){
	if(ptr) { // ptr(현재 노드)이 존재하는 경우
		printf(" [%d] ", ptr->key); // ptr의 키 값 출력
		preorderTraversal(ptr->left); // ptr의 왼쪽 자식 노드를 재귀 호출
		preorderTraversal(ptr->right); // ptr의 오른쪽 자식 노드를 재귀 호출
	}
}

// 후위 순회 방식으로 트리의 노드 출력하는 함수
// 노드의 끝에서 시작하여 왼쪽 서브트리 -> 오른쪽 서브트리 -> 루트 노드
void postorderTraversal(Node* ptr){ 
	if(ptr) { // ptr(현재 노드)이 존재하는 경우
		postorderTraversal(ptr->left); // ptr의 왼쪽 자식 노드를 재귀 호출
		postorderTraversal(ptr->right); // ptr의 오른쪽 자식 노드를 재귀 호출
		printf(" [%d] ", ptr->key); // ptr의 키 값 출력
	}
}

// 입력받은 key값을 가진 노드 삽입 함수
int insert(Node* head, int key){

	if(head == NULL){ // 트리에 대한 할당된 메모리가 없는 경우
		printf("Nothing to allocate....");
		return 1; 
	}

	// 삽입할 노드에 대한 동적할당 및 노드 구조체의 필드값 초기화
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { // 트리에 노드가 존재하지 않는 경우
		head->left = newNode; // 헤드노드의 왼쪽에 삽입
		return 0;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	// 부모노드에 대한 포인터
	Node* parentNode = NULL;

	// 노드 ptr이 존재하는 경우
	// 노드를 삽입할 위치 찾는 과정
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		// 입력한 값을 가진 노드가 존재하지 않는 경우
		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// 노드 삽입
	/* linking the new node to the parent */
	if(parentNode->key > key) // 삽입한값이 부모노드의 키값보다 큰 경우
		parentNode->left = newNode; // 부모노드의 왼쪽에 삽입
	else // 그 외의 경우
		parentNode->right = newNode; // 부모노드의 오른쪽에 삽입 
	return 1;
}

// 입력받은 키값을 가진 리프 노드 삭제 함수
int deleteLeafNode(Node* head, int key){
	if (head == NULL) { // 트리가 존재하지 않는 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // 트리에 노드가 없는 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // ptr(현재 노드)이 루트 노드를 가리키도록 설정


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; // 현재노드의 부모노드를 가리키도록 설정

	while(ptr != NULL) { // 노드가 존재할 때까지 트리 순회

		if(ptr->key == key) { // 현재노드의 키값과 입력받은 키값이 일치하는 경우
			if(ptr->left == NULL && ptr->right == NULL) { // 현재노드의 양쪽 자식노드가 모두 존재하지 않는 경우(즉, ptr이 리프노드인 경우)

				/* root node case */
				if(parentNode == head) // 루트 노드인 경우
					head->left = NULL; // 루트 노드를 NULL로 초기화하여 삭제

				/* left node case or right case*/
				if(parentNode->left == ptr) // 현재노드가 부모노드의 왼쪽 자식노드일 경우
					parentNode->left = NULL; // 해당 노드 삭제
				else // 그외
					parentNode->right = NULL; // 해당 노드 삭제

				free(ptr); // 현재 노드에 대한 동적 할당 해제 
			}
			else { // 현재노드가 리프 노드가 아닌 경우
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; // 부모 노드를 현재 노드로 설정

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // 현재 노드의 키값보다 입력받은 키값이 큰 경우
			ptr = ptr->right; // 오른쪽 서브트리로 이동
		else // 현재 노드의 키값보다 입력받은 키값이 작은 경우
			ptr = ptr->left; // 왼쪽 서브트리로 이동
	}

	// 입력된 키값과 동일한 키값을 가진 노드를 찾을 수 없는 경우
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

// 재귀 방식으로 입력받은 키값을 가진 노드를 찾는 함수
Node* searchRecursive(Node* ptr, int key){
	if(ptr == NULL) // 현재 노드가 존재하지 않는 경우
		return NULL; // 함수 종료

	if(ptr->key < key) // 현재노드의 키값보다 입력받은 키값이 큰 경우
		ptr = searchRecursive(ptr->right, key); // 재귀 방식으로 오른쪽 서브트리 탐색 
	else if(ptr->key > key) // 현재 노드의 키값보다 입력받은 키값이 작은 경우
		ptr = searchRecursive(ptr->left, key); // 재귀 방식으로 왼쪽 서브트리 탐색

	/* if ptr->key == key */
	return ptr; // 현재노드에 대한 포인터 값 반환
}

// 비재귀 방식으로 입력받은 키값을 가진 노드를 찾는 함수
Node* searchIterative(Node* head, int key){
	/* root node */
	Node* ptr = head->left; // 현재노드를 루트노드로 설정

	while(ptr != NULL){ // 현재노드가 존재하지 않는 경우
		if(ptr->key == key) // 현재노드의 키값과 입력받은 키값이 일치하는 경우
			return ptr; // 현재노드에 대한 포인터 값 반환

		if(ptr->key < key) // 현재노드의 키값보다 입력받은 키값이 큰 경우
			ptr = ptr->right; // 오른쪽 자식 노드로 이동
		else // 현재노드의 키값보다 입력받은 키값이 작은 경우
			ptr = ptr->left; // 왼쪽 자식 노드로 이동
	}

	// 일치하는 노드를 찾지 못한 경우
	return NULL;
}

// 노드에 대한 동적할당 해제
void freeNode(Node* ptr){
	if(ptr) { // ptr(현재 노드)이 존재하는 경우
		freeNode(ptr->left); // ptr의 왼쪽 자식 노드에 대한 동적할당 해제를 재귀호출을 통해 실행
		freeNode(ptr->right); // ptr의 오른쪽 자식 노드에 대한 동적할당 해제를 재귀호출을 통해 실행
		free(ptr); // 현재노드인 ptr에 대한 동적할당 해제 함수 실행
	}
}

// 트리에 대한 동적 할당 해제 함수
int freeBST(Node* head){

	if(head->left == head){ // 트리에 노드가 없는 경우
		free(head); // 헤드노드에 대한 동적 할당 해제
		return 1;
	}

	Node* p = head->left; // 현재노드가 루트노드가 되도록 설정

	freeNode(p); // 트리의 모든 노드 해제하는 함수

	free(head); // 마지막으로 헤드노드에 대한 동적 할당 해제
	return 1;
}