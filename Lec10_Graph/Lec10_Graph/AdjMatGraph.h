#pragma once
#include <stdio.h>

#define MAX_VTXS 100
#define INF 9999    // 값이 INF 이상이면 간선이 없음

// 기본 인접 행렬 그래프 클래스
class AdjMatGraph {
protected:
	int		size;
	char	vertices[MAX_VTXS];
	int		adj[MAX_VTXS][MAX_VTXS];

public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	// 그래프 초기화 ==> 공백 상태의 그래프
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
			for (int j = 0; j < MAX_VTXS; j++)
				setEdge(i, j, 0);
	}
	// 정점 삽입
	void insertVertex(char name) {
		if (!isFull()) vertices[size++] = name;
		else printf("Error: 그래프 정점 개수 초과\n");
	}
	// 간선 삽입 (무방향 그래프)
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}
	// 그래프 정보 출력
	void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);
		for (int i = 0; i < size; i++) {
			fprintf(fp, " %c ", getVertex(i));
			for (int j = 0; j < size; j++)
				fprintf(fp, "%5d", getEdge(i, j)); // 가중치 출력을 위해 공백 폭을 %5d로 조금 늘렸습니다.
			fprintf(fp, "\n");
		}
	}
};

// 탐색 기능이 추가된 인접 행렬 기반 그래프 클래스 
class SrchAMGraph : public AdjMatGraph
{
	bool visited[MAX_VTXS];	// 정점의 방문 정보

public:
	void resetVisited() {
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}
	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	// 깊이 우선 탐색 함수 
	void DFS(int v) {
		visited[v] = true;
		printf("%c ", getVertex(v));

		for (int w = 0; w < size; w++)
			if (isLinked(v, w) && visited[w] == false)
				DFS(w);
	}
};

// [3] 가중치 그래프를 표현하는 클래스
class WGraph : public AdjMatGraph {
public:
	// 가중치 그래프 전용 초기화 (간선이 없으면 INF, 대각선은 0)
	WGraph() { reset(); }

	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++) {
			for (int j = 0; j < MAX_VTXS; j++) {
				if (i == j) setEdge(i, j, 0);
				else setEdge(i, j, INF);
			}
		}
	}

	void insertEdge(int u, int v, int weight) {
		if (weight > INF) weight = INF; // == 에서 = 으로 수정
		setEdge(u, v, weight);
	}

	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF && i != j); }

	void load(const char* filename) {
		FILE* fp;
		fopen_s(&fp, filename, "r");
		if (fp != NULL) {
			int n, val;
			if (fscanf_s(fp, "%d", &n) == 1) {
				reset(); // 읽기 전 기존 데이터 초기화
				for (int i = 0; i < n; i++) {
					char str[80];
					// fscanf_s 문자열 읽기 형식 수정
					if (fscanf_s(fp, "%s", str, (unsigned int)sizeof(str)) == 1) {
						insertVertex(str[0]);
					}
					for (int j = 0; j < n; j++) {
						if (fscanf_s(fp, "%d", &val) == 1) {
							insertEdge(i, j, val);
						}
					}
				}
			}
			fclose(fp); // 파일 닫기 추가
		}
		else {
			printf("Error: 파일 %s 를 열 수 없습니다.\n", filename);
		}
	}
};