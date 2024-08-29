#include "command.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;


int main(int argc, char* argv[])
{
	//for (int i = 0; i < argc; i++) cout << i << ". " << argv[i] << "." << endl;
	// Thiết lập locale để hỗ trợ UTF-8
	locale::global(locale("en_US.UTF-8"));
	wcout.imbue(locale());

	// Update Tree and Array
	vector<Data> arrayData = readFile("Treebin");
	Node* root = updateTree("Treebin");

	//wcout << argv[1] << " " << argv[2];
	if (strcmp(argv[1], "load") == 0)
	{
		if (argc != 3) return 0;
		if (strcmp(argv[2], "-cmd") == 0)
		{
			vector<Data> dataList = getDataListFromTree(root);
			printDataList(dataList);
		}
		else if (strcmp(argv[2], "-csv") == 0)
		{
			writeFileBin("listFile.csv", root);
		}
	}
	else if (strcmp(argv[1], "insert") == 0)
	{
		if (argc == 2)
		{
			cout << "------------------------" << endl;
			cout << "INSERT A CITY" << endl;
			cout << "------------------------" << endl;
			insert1City(root, arrayData);
			writeFileBin("Treebin", root);
		}
		else if (argc == 3)
		{
			insertFromFile(argv[2], root, arrayData);
			writeFileBin("Treebin", root);
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
