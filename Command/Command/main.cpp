﻿#include "command.h"
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++) cout << i << ". " << argv[i] << "." << endl;
	// Thiết lập locale để hỗ trợ UTF-8
	locale::global(locale("en_US.UTF-8"));
	wcout.imbue(locale());

	Node* root = NULL;
	vector<Data> arrayData;
	//wcout << argv[1] << " " << argv[2];
	if (strcmp(argv[1], "load") == 0)
	{
		if (argc != 3) return 0;
		if (strcmp(argv[2], "-cmd") == 0)
		{
			arrayData = loadListFile("-cmd");
			root = buildKDTree(arrayData);
		}
		else
		{
			arrayData = loadListFile("-csv");
			root = buildKDTree(arrayData);
		}
	}
	else if (strcmp(argv[1], "insert") == 0)
	{
		if (argc == 2)
		{
			cout << "insert a city" << endl;
			insert1City(root, arrayData);
		}
		else if (argc == 3)
		{
			insertFromFile(argv[2], root, arrayData);
		}
	}
	else if (strcmp(argv[1], "nearest-neighbor") == 0)
	{
		if (argc != 5) return 0;
		float target[2] = { stof(argv[2]), stof(argv[3]) };
		if (strcmp(argv[4], "-cmd") == 0)
		{
			nearestNeighbor(root, "-cmd", target);
		}
		else
		{
			nearestNeighbor(root, "-csv", target);
		}
	}
	else if (strcmp(argv[1], "rectangular") == 0)
	{
		if (argc != 7) return 0;
		float LeftBottom[2] = { stof(argv[2]), stof(argv[3]) };
		float TopRight[2] = { stof(argv[4]), stof(argv[5]) };
		if (strcmp(argv[6], "-cmd") == 0)
		{
			rectangular(root, "-cmd", LeftBottom, TopRight);
		}
		else
		{
			rectangular(root, "-csv", LeftBottom, TopRight);
		}
	}
	//system("pause");
	return 0;
}

//=========== TEST ============
/*int main()
{
	Node* root = NULL;
	vector<Data> arrayData;
	//loadListFile("-csv");
	arrayData = loadListFile("-csv");
	root = buildKDTree(arrayData);
	nearestNeighbor(root, "-cmd");
	float A[2] = { 35.66, 139.6 };
	float B[2] = { 35.6897, 139.6922 };
	cout << endl << "Pos - Tokyo: " << getDistance(A, B);
	float C[2] = { 33.7333, 135.383 };
	cout << endl;
	cout << "Pos - Tanabe: " << getDistance(A, C);
	return 0;
}*/