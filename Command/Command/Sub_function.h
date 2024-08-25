#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

#define M_PI 3.14159265358979323846
#define EARTH_RADIUS 6371 // km

struct Data
{
	string Name;
	float Position[2]; // [0]: latitude (vi do), [1]: longitude (kinh do)
};

struct Node
{
	Node* leftNode;
	Node* rightNode;
	Data key;
	// Xu ly insert can theo cong thuc deep mod (number of info field) nen mn can phai cap nhat deep moi khi xu ly
	int depth; // depth bat dau = 0
};

Node* createNode(Data key, int previousDeep);
Data encryption(string temp);
vector<Data> readFile(string fileName);
float getDistance(float A[2], float B[2]);
void rangeSearch(vector<Data>& result, Node* pRoot, float LeftBottom[2], float TopRight[2]);
int numberNode(Node* root);
void insertRecursion(Node*& root, Data D, int depth);
Node* buildBalancedKDTree(vector<Data>& points, int start, int end, int depth);
Node* buildKDTree(const vector<Data>& points);
void Insert(Node*& root, Data D, vector<Data>& arrayData);
void BFS(Node* root);
void searchRecursive(Node*& root, float target[2], Data& best_city);
Data findNearestNeighborSearch(Node*& root, float target[2]);