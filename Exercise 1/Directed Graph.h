#pragma once
#include <iostream>
using namespace std;

template<typename TnodeInfo>
class Graph {
public:
	int N;
	char** adjacencyMatrix;
	TnodeInfo* nodeInfo;

	Graph(int numOfNodes) {
		int x, y;

		N = numOfNodes;

		adjacencyMatrix = new char* [N];
		for (x = 0; x < N; x++) {
			adjacencyMatrix[x] = new char[N];
			for (y = 0; y < N; y++) {
				adjacencyMatrix[x][y] = 0;
			}
		}

		nodeInfo = new TnodeInfo[N];
	}

	void setNodeInfo(int index, TnodeInfo info) {
		nodeInfo[index] = info;
	}

	TnodeInfo getNodeInfo(int index) {
		return nodeInfo[index];
	}

	void addEdge(int x, int y) {
		adjacencyMatrix[x][y] = 1;
	}

	void removeEdge(int x, int y) {
		adjacencyMatrix[x][y] = 0;
	}

	~Graph() {
		int index;
		for (index = 0; index < N; index++) {
			delete adjacencyMatrix[index];
		}
		delete adjacencyMatrix;
		delete nodeInfo;
	}
};