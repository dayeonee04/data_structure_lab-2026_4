#include "Location2D.h"
#include <stack>
#include <deque>
#include <iostream>

using namespace std;

#define MAZE_SIZE 6

char map[MAZE_SIZE][MAZE_SIZE]{
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1','0', '0', '1'},
	{'1', '0', '0','0', '1', '1'},
	{'1', '0', '1','0', '1', '1'},
	{'1', '0','1', '0', '0','x'},
	{'1', '1','1', '1', '1', '1'},
};

bool isValidLoc(int r, int c)
{
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
	else return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
	int ds_num;
	printf_s("DFS 데이터 구조 라이브러리 선택: 1)stack, 2)deque \n");
	scanf_s("%d", &ds_num);

	// main 시작 부분의 locStack 선언은 유지 (case 1 내부 중복 선언은 제거)
	stack<Location2D> locStack;

	switch (ds_num) {
	case 1: { // 중괄호 블록 추가
		//stack 데이터구조 사용
		Location2D entry(1, 0);
		locStack.push(entry);

		while (locStack.empty() == false) {
			Location2D here = locStack.top();
			locStack.pop();

			int r = here.row, c = here.col;
			printf_s("(%d,%d) ", r, c);
			if (map[r][c] == 'x') {
				printf_s("미로 탐색 성공\n");
				return 0; // return; 에서 return 0;으로 수정
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locStack.push(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locStack.push(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locStack.push(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locStack.push(Location2D(r, c + 1));
			}
		}
		printf_s("미로 탐색 실패\n");
		break;
	} // 중괄호 블록 닫기

	case 2: { // 중괄호 블록 추가 (void main(); 제거)
		//Deque 데이터구조 사용
		deque<Location2D> locDeque;	//위치 덱 객체 생성
		Location2D entry(1, 0);	//입구 객체
		locDeque.push_front(entry);	//덱에 입구 위치 삽입

		while (locDeque.empty() == false) {	//덱이 비어있지 않는 동안
			Location2D here = locDeque.front();	//덱의 front 상단 객체 복사
			locDeque.pop_front();	//덱의 상단 객체 삭제

			int r = here.row, c = here.col;
			::printf("(%d,%d) ", r, c);
			if (map[r][c] == 'x') {
				::printf("미로탐색 성공\n");
				return 0; // return 0;으로 수정
			}
			else {						//출구가 아니면 현재 위치를
				map[r][c] = '.';		//현재 위치를 "지나옴" 처리
				if (isValidLoc(r - 1, c)) locDeque.push_front(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locDeque.push_front(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locDeque.push_front(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locDeque.push_front(Location2D(r, c + 1));
			}
		}
		::printf("미로탐색실패\n");
		break; // break 추가하여 아래 BFS가 바로 실행되지 않도록 차단
	} // 중괄호 블록 닫기
	}

	// 1번이나 2번 선택 시 위에서 성공하면 return 0;로 끝나지만, 
	// 만약 switch에 해당하지 않는 번호를 입력하면 아래 BFS가 실행됩니다.
	::printf("BFS 미로탐색\n");
	//BFS로 미로탐색 구현
	{ // void main(); 제거 후 블록 유지
		deque<Location2D> locDeque;
		Location2D entry(1, 0);
		locDeque.push_back(entry);

		while (locDeque.empty() == false) {
			Location2D here = locDeque.front();
			locDeque.pop_front();

			int r = here.row, c = here.col;
			printf("(%d,%d) ", r, c);
			if (map[r][c] == 'x') {
				printf("미로탐색 성공\n");
				return 0; // return 0;으로 수정
			}
			else {
				map[r][c] = '.';
				if (isValidLoc(r - 1, c)) locDeque.push_back(Location2D(r - 1, c));
				if (isValidLoc(r + 1, c)) locDeque.push_back(Location2D(r + 1, c));
				if (isValidLoc(r, c - 1)) locDeque.push_back(Location2D(r, c - 1));
				if (isValidLoc(r, c + 1)) locDeque.push_back(Location2D(r, c + 1));
			}
		}
		printf("미로탐색실패\n");
	}

	return 0;
}