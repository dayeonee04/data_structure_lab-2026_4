#pragma once
#include "AdjMatGraph.h"

class WGraphPrim : public WGraph { // WgraphPrim -> WGraphPrim 대소문자 수정
public: // public; -> public: 수정
	int getMinVertex(bool* selected, int* dist) { // 함수명 대소문자 일치 (getMinvertex -> getMinVertex)
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v < size; v++)
			if (!selected[v] && dist[v] < mindist) {
				mindist = dist[v];
				minv = v;
			}
		return minv;
	}
	void Prim(int s) {
		bool selected[MAX_VTXS];
		int dist[MAX_VTXS];

		// [필수 추가] dist와 selected 배열 초기화 루프
		for (int i = 0; i < size; i++) {
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0; // 시작 정점의 거리는 0으로 설정하여 먼저 선택되도록 함

		for (int i = 0; i < size; i++) {
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] == INF) return;
			printf("%c ", getVertex(u)); // 공백을 한 칸 주어 가독성 보완
			for (int v = 0; v < size; v++)
				if (getEdge(u, v) != INF)
					if (!selected[v] && getEdge(u, v) < dist[v])
						dist[v] = getEdge(u, v);
		}
		printf("\n"); // pringf -> printf 오타 수정
	}
};