// main.cpp
#include "AdjMatGraph.h"     // 기본 그래프 및 DFS 클래스 포함
#include "WGraphMST.h"       // Kruskal 알고리즘 클래스 포함
#include "WGraphPrim.h"      // Prim 알고리즘 클래스 포함
#include "WGraphDijkstra.h"  // Dijkstra 알고리즘 클래스 포함
#include <cstdio>

int main()
{
	
	// [실습 1] 기본 인접 행렬 그래프 및 DFS 탐색 테스트
	
	
	SrchAMGraph g;
	for (int i = 0; i < 5; i++)
		g.insertVertex('A' + i); // 정점 삽입: 'A', 'B', 'C', 'D', 'E'

	g.insertEdge(0, 1);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);
	g.insertEdge(2, 4);
	g.insertEdge(3, 4);

	printf("인접 행렬로 표현한 그래프\n");
	g.display();

	// 파일 출력
	FILE* fp;
	if (fopen_s(&fp, "../text_out.txt", "w") == 0) {
		g.display(fp);
		fclose(fp);
	}

	// DFS 탐색으로 방문
	printf("DFS==> ");
	g.resetVisited();		// 모든 정점을 방문하지 않았다고 하고
	g.DFS(0);				// 0번째 정점(A)에서 깊이 우선 탐색 시작
	printf("\n\n");


	
	//가중치 그래프 알고리즘 (Kruskal, Prim, Dijkstra)

	// Kruskal 알고리즘 테스트
	/*
	WGraphMST wg_mst;
	wg_mst.load("graph.txt");
	printf("MST By Kruskal's Algorithm\n");
	wg_mst.Kruskal();
	printf("\n");
	*/

	/*
	//  Prim 알고리즘 테스트
	WGraphPrim wg_prim;
	wg_prim.load("graph.txt");
	printf("MST By Prim's Algorithm\n");
	wg_prim.Prim(0);          // 정점 0(A)에서 시작
	printf("\n");
	*/

	/*
	// 2-3. Dijkstra 알고리즘 테스트
	WGraphDijkstra wg_dijkstra;
	wg_dijkstra.load("graph_sp.txt");
	printf("Shortest Path By Dijkstra Algorithm\n");
	wg_dijkstra.ShortestPath(0);      // 정점 0(A)에서 시작
	printf("\n");
	*/

	return 0;
}