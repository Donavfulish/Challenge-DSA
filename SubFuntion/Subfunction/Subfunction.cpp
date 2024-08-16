#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <cmath>

using namespace std;

#define M_PI 3.14159265358979323846
#define EARTH_RADIUS 6371 // km

struct Data
{
	string Name;
	float Position [2]; // [0]: latitude (vi do), [1]: longitude (kinh do)
};

struct Node
{
	Node* leftNode;
	Node* rightNode;
	Data key;
	// Xu ly insert can theo cong thuc deep mod (number of info field) nen mn can phai cap nhat deep moi khi xu ly
	int depth;
};

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
	double a = sin(latitudeGap / 2) * sin(latitudeGap / 2) + cos(A[1] * M_PI / 180) * cos(B[1] * M_PI/ 180) * sin(longitudeGap / 2) * sin(longitudeGap / 2);
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

int main()
{
	// Au test -----------------------------------------------------------------------------------
	vector<Data> data = readFile("DATA.txt");
	for (Data x : data)
	{
		cout << x.Name << ": (" << x.Position[0] << "," << x.Position[1] << ")" << endl;
	}
	return 0;
	// -------------------------------------------------------------------------------------------
}
