#pragma once
#include "AdjMatGraph.h"

//Dijkstra 알고리즘의 최단 경로 탐색기능이 추가된그래프
class WGraphDijkstra : public WGraph {
	int dist[MAX_VTXS];	//시작노드로부터의 최단경로 거리
	bool found[MAX_VTXS];	//방문한 정점 표시
public:
	int chooseVertex() {
		int min = INF;
		int minpos = -1;
		for (int i = 0; i < size; i++)
			if (dist[i] < min && !found[i]) {
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() { 
		for (int i = 0; i < size; i++) {
			if (dist[i] == INF) printf("  INF");
		}
		printf("\n");
	}
	//Dijkstra의 최단 경로 알고리즘:  start 정점에서 시작함.
	void ShortestPath(int start) {
		for (int i = 0; i < size; i++) {
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true;
		dist[start] = 0;

		
		for (int i = 0; i < size - 1; i++) {
			printf("Step %2d:", i + 1);
			printDistance();
			int u = chooseVertex();

			if (u == -1) break; // 더 이상 연결된 정점이 없으면 중단
			found[u] = true;
			for (int w = 0; w < size; w++) {
				if (found[w] == false)
					if (dist[u] + getEdge(u, w) < dist[w])
						dist[w] = dist[u] + getEdge(u, w);
			}
		}
	}
};