#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { //노드 구조체 선언 데이터와 이전,다음 주소를 가리키는 링크가 들어 있음
	int key; //데이터  
	struct Node* llink; // link 필드 자신과 동일한 타입을 가르켜야 함 //이전 노드 
	struct Node* rlink; //  원형 링크 라서 링크가 두개 앞쪽 뒤쪽 연결하여 회전을 가능하게 한다. //다음 노드
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); //초기화
int freeList(listNode* h); //종료 동적 할당 해제
int insertLast(listNode* h, int key); // list에 key에 대한 노드하나를 마지막에 추가
int deleteLast(listNode* h); // list의 마지막 노드 삭제
int insertFirst(listNode* h, int key); // list 처음에 key에 대한 노드하나를 추가
int deleteFirst(listNode* h); // list의 첫번째 노드 삭제
int invertList(listNode* h); // 리스트의 링크를 역순으로 재 배치

int insertNode(listNode* h, int key); // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int deleteNode(listNode* h, int key); /// list에서 key에 대한 노드 삭제

void printList(listNode* h); // 리스트를 출력



int main()
{
	char command; // 문자형 변수 선언
	int key; // int형 변수 선언 이중 연결 리스트에 넣을  데이터을 받음
	listNode* headnode=NULL; //처음 노드를 가르키는 first Head 구조체 선언 원형 구조를 갖게 하기 위해서 해드노드도 왼쪽 오른쪽 링크를 만든다.
	printf("[----- [kim dongmin] [2017038093] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //기능 선택

		switch(command) {
		case 'z': case 'Z': //초기화 
			initialize(&headnode);
			break;
		case 'p': case 'P': //출력 리스트
			printList(headnode);
			break;
		case 'i': case 'I': // 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
			printf("Your Key = "); 
			scanf("%d", &key); //데이터 입력 받음
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = "); //list에서 key에 대한 노드 삭제
			scanf("%d", &key); //데이터 입력 받음
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //list에 key에 대한 노드하나를 마지막에 추가
			printf("Your Key = "); 
			scanf("%d", &key); //데이터 입력 받음
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // list의 마지막 노드 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': // list 처음에 key에 대한 노드하나를 추가
			printf("Your Key = ");
			scanf("%d", &key); //데이터 입력 받음
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // list의 첫번째 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //리스트의 링크를 역순으로 재 배치
			invertList(headnode);
			break;
		case 'q': case 'Q': //종료 및 동적 할당 해제
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //잘못입력에 대한 오류 처리
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q' && 'Q' 이면 반복문 종료

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) //조건문 h가 NULL이 아니면 할당된 메모리 모두 헤제
		freeList(*h); //할당한 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));  //동적 할당
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1; //1 리턴
}

int freeList(listNode* h){ // 할당한 메모리 해제

	if(h->rlink == h) //해드 가 rlink 자신일때 
	{
		free(h);  //해드 동적할당 해제 
		return 1; //1 리턴
	}

	listNode* p = h->rlink; // listNode형 포인터 p에 첫번쩨 주소 h 대입

	listNode* prev = NULL;   // listNode형 포인터 prev에 NULL 대입
	while(p != NULL && p != h) { //p가 NULL p가 해드가 될때까지 반복
		prev = p;
		p = p->rlink;
		free(prev); //동적할당 해제
	}
	free(h); //동적할당 해제
	return 0; //리턴 0
}



void printList(listNode* h) {  // 리스트를 출력하는 함수
	int i = 0; //정수형 i 선언
	listNode* p;  //listNode형 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { // Nothing to print 오류 처리
		printf("Nothing to print....\n"); //Nothing to print
		return;
	}

	p = h->rlink; // p에 처음노드

	while(p != NULL && p != h) {  //p가 NULL p가 해드가 될때까지 반복
		printf("[ [%d]=%d ] ", i, p->key); //i 번째 와 데이터 출력
		p = p->rlink; //다음 노드
		i++;  //i값 증가
	}
	printf("  items = %d\n", i); //노드의 갯수


	/* print addresses */
	printf("\n---checking addresses of links\n"); //주소 확인
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); //해드노드의  llink headrlink 출력
    
	i = 0; //i에 0대입
	p = h->rlink;  // p에 처음노드
	while(p != NULL && p != h) {  //p가 NULL p가 해드가 될때까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); //노드의  llink node rlink출력
		p = p->rlink; //다음 노드
		i++; //i값 증가
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {  // list에 key에 대한 노드하나를 마지막에 추가

	if (h == NULL) return -1; //해드가 NULL일때 return -1

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당 
	node->key = key; //노드에 key 데이터를 받음
	node->rlink = NULL;  // rlink 링크 NULL 
	node->llink = NULL; // llink 링크 NULL 

	if (h->rlink == h) /* 첫 노드로 삽입 */ //해드의 rlink이 자신일때 
	{
		h->rlink = node; // 해드의 rlink에 다음노드 추가한 노드
		h->llink = node; //  해드의 llink에 이전노드 추가한 노드
		node->rlink = h; // 노드의  rlink에 다음노드 해드
		node->llink = h; //노드의  llink에 다음노드 해드 // 원형구조 
	} else { //아닐때 
		h->llink->rlink = node; // 해드 llink의rlink에 넣음
		node->llink = h->llink; // 추가한 노드의 이전노드에 원래 마지막 노드를 가리킴
		h->llink = node; // 해드노드의 이전링크는 추가한 노드를 가리킴
		node->rlink = h; // 노드에 다음링크에 해드를 가리킴
	}

	return 1; //리턴 1
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) { //list의 마지막 노드 삭제하는 함수

	if (h->llink == h || h == NULL) //해드의 llink가해드를 가리키거나 해드가 NULL일때 오류처리
	{
		printf("nothing to delete.\n"); // nothing to delete. 지울게 없음
		return 1;//리턴 1
	}

	listNode* nodetoremove = h->llink; //listNode형 포인터 nodetoremove 선언한고 해드의 llink를 넣음

	/* link 정리 */
	nodetoremove->llink->rlink = h; //nodetoremove의llink의rlink는 해드
	h->llink = nodetoremove->llink; // 해드 llink에 nodetoremove의 llink 넣음

	free(nodetoremove); //동적할당 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) { // list 처음에 노드하나를 추가 하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //동적할당
	node->key = key; //노드에 key 데이터를 받음
	node->rlink = NULL;  // rlink 링크 NULL
	node->llink = NULL;  // llink 링크 NULL


	node->rlink = h->rlink; //노드의 다음 링크가 해드가 가리키던 다음노드를 가리킴
	h->rlink->llink = node; // 해드가 가르키던 다음노드의 이전노드에 추가한 노드를 가리킴
	node->llink = h; // 노드의 이전노드는 해드
	h->rlink = node; //해드의 다음 노드는 추가한 노드


	return 1; // 리턴 1
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) { //첫번째 노드 삭제하는 함수

	if (h == NULL || h->rlink == h) //해드의 rlink가해드를 가리키거나 해드가 NULL일때 오류처리
	{
		printf("nothing to delete.\n"); //nothing to delete.
		return 0; //리턴 0
	}

	listNode* nodetoremove = h->rlink;  //listNode형 포인터 nodetoremove 선언한고 해드의 rlink를 넣음

	/* link 정리 */
	nodetoremove->rlink->llink = h; //두번째 노드의 이전노드가 해드를 가리킴
	h->rlink = nodetoremove->rlink; // 해드의 다음노드 에 두번째 노드를 가리킴

	free(nodetoremove); //동적할당 해제

	return 1; // 리턴 0

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) { //리스트의 링크를 역순으로 재 배치하는 함수


	if(h->rlink == h || h == NULL) { //해드의 rlink가해드를 가리키거나 해드가 NULL일때 오류처리
		printf("nothing to invert...\n"); //nothing to invert.
		return 0; //리턴 0
	}
	listNode *n = h->rlink; // listNode형 포인터 n 선언 첫번째 노드를 포인트
	listNode *trail = h; // listNode형 포인터 trail 선언히고 해드
	listNode *middle = h; // listNode형 포인터 middle 선언하고 해드

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; // 해드llink에 해드 rlink을 넣음

	while(n != NULL && n != h){ //널이되고 해드가 될때까지 반복
		trail = middle; //trail에 middle저장
		middle = n; //middle 에 n
		n = n->rlink; //다음 n이 가리키고 있는 노드
		middle->rlink = trail; //  rlink링크 역순
		middle->llink = n; //  llink링크 역순
	}

	h->rlink = middle;  // middle가 처음 노드

	return 0; //리턴 0
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; //해드가 NULL이면 리턴 -1

	listNode* node = (listNode*)malloc(sizeof(listNode));  //동적할당
	node->key = key;  //노드에 key 데이터를 받음
	node->llink = node->rlink = NULL; // 이전, 다음 링크 NULL

	if (h->rlink == h) //해드 다음이 해드일때 
	{
		insertFirst(h, key); // 노드를 첫번째에다 넣음
		return 1;  //리턴 1
	}

	listNode* n = h->rlink; //listNode형 포인터 n 선언 후 first 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { // n이 NULL이고 h 맞을 때까지 반복
		if(n->key >= key) { //조건문 크기 비교
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { //n이 해드 다음포인트일 경우
				insertFirst(h, key); // 노드를 첫번째에다 넣음
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0; //리턴 0
		}

		n = n->rlink; //다음 링크
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // 마지막에 삽입
	return 0; //리턴 0
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {  //list에서 key에 대한 노드 삭제하는 함수

	if (h->rlink == h || h == NULL) // 없을때 오류 처리
	{
		printf("nothing to delete.\n"); // nothing to delete
		return 0; //리턴 0
	}

	listNode* n = h->rlink; // listNode형 포인터 n 선언 하고 첫번째 노드를 넣음

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //첫번째 노드 삭재
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); //마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n); //동적 할당 해제
			}
			return 0; //리턴 1
		}

		n = n->rlink; //다음노드를 n에 넣음
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //오류 처리
	return 0; //리턴 0
}