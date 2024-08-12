#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Data
{
	string City_Name;
	vector<float> position;
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
	newNode->deep = previousDeep + 1;
	
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
			key.City_Name = word;

		else if (pos == 1)
			key.position[0] = stof(word);

		else if (pos == 2)
			key.position[1] = stof(word);

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
