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
#include "Sub_function.h"

using namespace std;

#define M_PI 3.14159265358979323846
#define EARTH_RADIUS 6371 // km

Node* createNode(Data key, int previousDeep)
{
	Node* newNode = new Node;
	newNode->leftNode = NULL;
	newNode->rightNode = NULL;
	newNode->key = key;
	newNode->depth = previousDeep + 1;
	
	return newNode;
}
Data encryption(string temp)
{
	stringstream ss(temp);
	string word;
	Data key;
	int pos = 0;

	while (getline(ss, word, ','))
	{
		if (pos == 0)
			key.Name = word;

		else if (pos == 1)
			key.Position[0] = stof(word);

		else if (pos == 2)
			key.Position[1] = stof(word);

		else if (pos > 2)
			break;

		pos++;
	}

	return key;
}

vector<Data> readFile(string fileName)
{
	fstream fs(fileName.c_str());
	vector<Data> setof_City;
	if (!fs.is_open())
	{
		cout << "File not found\n";
		return { };
	}

	else
	{
		string temp;
		getline(fs, temp);

		while (getline(fs, temp))
			setof_City.push_back(encryption(temp));

		return setof_City;
	}
}

// calculating distance between two points A and B (using Haversine formula)
float getDistance(float A[2], float B[2])
{
	float latitudeGap = abs(A[0] - B[0]) * M_PI / 180;
	float longitudeGap = abs(A[1] - B[1]) * M_PI / 180;
	double a = sin(latitudeGap / 2) * sin(latitudeGap / 2) + cos(A[0] * M_PI / 180) * cos(B[0] * M_PI/ 180) * sin(longitudeGap / 2) * sin(longitudeGap / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	double distance = EARTH_RADIUS * c; // km
	return static_cast<float>(distance);
}

void rangeSearch(vector<Data>& result, Node* pRoot, float LeftBottom[2], float TopRight[2])
{
	if (pRoot == nullptr) return;
	
	int dimension = pRoot->depth % 2; // dimension = 0 -> X, 1 -> Y
	float dimensionPos = pRoot->key.Position[dimension]; // the value of current dimension
	float X = pRoot->key.Position[0];
	float Y = pRoot->key.Position[1];

	if ( X >= LeftBottom[0] && X <= TopRight[0]
		&& Y >= LeftBottom[1] && Y <= TopRight[1])
	{
		result.push_back(pRoot->key);
	}

	if (dimensionPos >= LeftBottom[dimension])
		rangeSearch(result, pRoot->leftNode, LeftBottom, TopRight);
	if (dimensionPos <= TopRight[dimension])
		rangeSearch(result, pRoot->rightNode, LeftBottom, TopRight);
}
int numberNode(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return 1 + numberNode(root->leftNode) + numberNode(root->rightNode);
}
/*void collectPoints(Node* node, std::vector<Data>& points) {
	if (!node) return;

	collectPoints(node->leftNode, points);
	points.push_back(node->key);
	collectPoints(node->rightNode, points);
}*/
void insertRecursion(Node*& root, Data D, int depth)
{
	if (root == NULL)
	{
		root = createNode(D, depth);
		return;
	}

	int dim = root->depth % 2;
	if (dim == 0)
	{
		if (D.Position[0] > root->key.Position[0])
			insertRecursion(root->rightNode, D, depth + 1);
		else if (D.Position[0] < root->key.Position[0])
			insertRecursion(root->leftNode, D, depth + 1);
	}
	else if (dim == 1)
	{
		if (D.Position[1] > root->key.Position[1])
			insertRecursion(root->rightNode, D, depth + 1);
		else if (D.Position[1] < root->key.Position[1])
			insertRecursion(root->leftNode, D, depth + 1);
	}
}
Node* buildBalancedKDTree(vector<Data>& points, int start, int end, int depth) {
	if (start > end) return nullptr;

	int axis = depth % 2;

	// Sort points based on current axis
	std::sort(points.begin() + start, points.begin() + end + 1, [axis](const Data& a, const Data& b) {
		return a.Position[axis] < b.Position[axis];
		});

	// Find median point
	int medianIndex = (start + end) / 2;
	Data medianData = points[medianIndex];

	// Create new node and recursively build subtrees
	Node* node = createNode(medianData, depth);
	node->leftNode = buildBalancedKDTree(points, start, medianIndex - 1, depth + 1);
	node->rightNode = buildBalancedKDTree(points, medianIndex + 1, end, depth + 1);

	return node;
}

Node* buildKDTree(const vector<Data>& points) {
	vector<Data> pointsCopy = points;
	return buildBalancedKDTree(pointsCopy, 0, pointsCopy.size() - 1, 0);
}
void Insert(Node*& root, Data D, vector<Data>& arrayData)
{
	insertRecursion(root, D, 0);
	arrayData.push_back(D);
	int left = numberNode(root->leftNode);
	int right = numberNode(root->rightNode);
	float checkBalanced = max(left, right) / min(left, right);
	if (checkBalanced >= 4.0)
	{
		root = buildKDTree(arrayData);
	}
}
void BFS(Node* root)
{
	stack<Node*> s;
	s.push(root);
	int level = 0;

	while (!s.empty())
	{
		vector<Node*> levelList;

		cout << "Level " << ++level << ":" << endl;
		while (!s.empty())
		{
			Node* curNode = s.top();
			levelList.push_back(curNode);
			s.pop();
			Data x = curNode->key;
			cout << x.Name << ": (" << x.Position[0] << "," << x.Position[1] << ")" << endl;
		}

		for (Node* node : levelList)
		{
			if (node->leftNode != nullptr) s.push(node->leftNode);
			if (node->rightNode != nullptr) s.push(node->rightNode);
		}
		cout << endl;
	}

}
//==========================Luan===============================================================================
void searchRecursive(Node*& root, float target[2], Data& best_city)
{

	if (root == NULL) return;
	//Trục phân chia tại độ sâu hiện tại
	int axis = root->depth % 2;

	// Cập nhật best nếu điểm tại node hiện tại gần hơn
	if (getDistance(target, best_city.Position) > getDistance(target, root->key.Position))
	{
		best_city = root->key;
	}

	// Chọn nhánh tiếp tục dựa trên trục phân chia
	if (target[axis] < root->key.Position[axis])
	{
		searchRecursive(root->leftNode, target, best_city);
		// Kiểm tra nhánh đối diện nếu có khả năng chứa điểm gần hơn

		float dis_opp_branch = EARTH_RADIUS * cos(target[1 - axis]) * abs(target[axis] - root->key.Position[axis]);
		if (dis_opp_branch < getDistance(target, best_city.Position))
		{
			searchRecursive(root->rightNode, target, best_city);
		}
	}
	else
	{
		searchRecursive(root->rightNode, target, best_city);
		// Kiểm tra nhánh đối diện nếu có khả năng chứa điểm gần hơn

		float dis_opp_branch = EARTH_RADIUS * cos(target[1 - axis]) * abs(target[axis] - root->key.Position[axis]);
		if (dis_opp_branch < getDistance(target, best_city.Position))
		{
			searchRecursive(root->leftNode, target, best_city);
		}
	}

}

Data findNearestNeighborSearch(Node*& root)
{
	Data rs;
	if (root == NULL) return rs;
	rs = root->key;
	float target[2];
	do
	{
		cout << "Enter latitude: ";
		cin >> target[0];
		cout << "Enter longitude: ";
		cin >> target[1];
		if (target[0] > 90 || target[0] < -90 || target[1] > 180 || target[1] < -180) cout << "Pleas, enter again !\n";
	} while (target[0] > 90 || target[0] < -90 || target[1] > 180 || target[1] < -180);
	searchRecursive(root, target, rs);
	return rs;
}
//==========================Luan===============================================================================

int main()
{
	// Au test -----------------------------------------------------------------------------------
	vector<Data> data = readFile("DATA.txt");
	Node* root = buildKDTree(data);
	/*for (Data x : data)
	{
		cout << x.Name << ": (" << x.Position[0] << "," << x.Position[1] << ")" << endl;
	}*/
	BFS(root);
	
	return 0;

	// -------------------------------------------------------------------------------------------
}
