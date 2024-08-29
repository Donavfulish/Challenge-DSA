#include <iostream>
#include <string>
#include <string.h>
#include <codecvt>
#include <queue>
#include <iomanip>
#include "Sub_function.h"
using namespace std;

// Hàm chuyển đổi std::string sang std::wstring
wstring stringToWstring(const string& str) {
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}

void writeToCSV(string output, vector<Data> D)
{
	ofstream f;
	f.open(output, ios::out);
	if (!f.is_open())
	{
		wcout << "File not found\n";
		return;
	}
	else
	{
		for (int i = 0; i < D.size(); i++)
		{
			f << D[i].Name << "," << D[i].Position[0] << "," << D[i].Position[1] << "\n";
		}
	}
	f.close();
	return;
}

void writeFileBin(string fileName, Node* root) {
	ofstream outFile(fileName, ios::binary | ios::out );
	if (!outFile) {
		cerr << "Không thể mở tệp để ghi." << endl;
		return;
	}
	else
	{
		queue<Node*> q;
		q.push(root);
		int level = 0;

		while (!q.empty())
		{
			vector<Node*> levelList;

			while (!q.empty())
			{
				Node* curNode = q.front();
				levelList.push_back(curNode);
				q.pop();
				Data city = curNode->key;
				size_t nameSize = city.Name.size();
				outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
				outFile.write(city.Name.c_str(), nameSize);
				outFile.write((char*)&(city.Position[0]), sizeof(city.Position[0]));
				outFile.write((char*)&(city.Position[1]), sizeof(city.Position[1]));
			}


			for (Node* node : levelList)
			{
				if (node->leftNode != nullptr) q.push(node->leftNode);
				if (node->rightNode != nullptr) q.push(node->rightNode);
			}
		}
	}
	outFile.close();
	return;
}



vector<Data> loadListFile(string print)
{
	vector<Data> data = readFile("DATA.txt");
	if (print == "-cmd")
	{
		for (int i = 0; i < data.size(); i++)
		{
			wcout << stringToWstring(data[i].Name) << "," << data[i].Position[0] << "," << data[i].Position[1] << endl;
		}
	}
	else
	{
		writeToCSV("listFile.csv", data);
	}
	return data;
}

void insert1City(Node*& root, vector<Data>& arrayData)
{
	string city;
	float x_cordinate, y_cordinate;
	wcout << "City's Name: ";
	getline(cin, city);
	//cin.ignore();
	wcout << "Latitude: ";
	cin >> x_cordinate;
	wcout << "Longtitude: ";
	cin >> y_cordinate;

	Data D;
	D.Name = city;
	D.Position[0] = x_cordinate;
	D.Position[1] = y_cordinate;

	Insert(root, D, arrayData);
	return;
}

void insertFromFile(string filename, Node*& root, vector<Data>& arrayData)
{
	vector<Data> newFile = readFile(filename);
	for (int i = 0; i < newFile.size(); i++)
	{
		Insert(root, newFile[i], arrayData);
	}
	return;
}

void nearestNeighbor(Node*& root, string print, float target[2])
{
	Data D = findNearestNeighborSearch(root, target);
	if (print == "-cmd")
	{
		wcout << "Nearest City: " << stringToWstring(D.Name) << endl;
		wcout << "Position: (" << D.Position[0] << "," << D.Position[1] << ")" << endl;
		wcout << "Distance: " << fixed << setprecision(2) << (double)getDistance(target, D.Position) << " km" << endl;
	}
	else
	{
		ofstream f;
		f.open("nearestNeighbor.csv", ios::out);
		if (!f.is_open())
		{
			wcout << "File not found\n";
			return;
		}
		else
		{
			f << "City,Latitude,Longitude,Distance" << endl;
			f << D.Name << "," << D.Position[0] << "," << D.Position[1] << "," << getDistance(target, D.Position) << endl;
		}
		f.close();
	}
	return;
}
void rectangular(Node* root, string print, float LeftBottom[2], float TopRight[2])
{
	vector<Data> result;
	rangeSearch(result, root, LeftBottom, TopRight);
	if (print == "-cmd")
	{
		if (result.size() == 0) cout << "No cities found in the range." << endl;
		for (int i = 0; i < result.size(); i++)
		{
			wcout << i + 1 << ". " << stringToWstring(result[i].Name) << ": (" << result[i].Position[0] << "," << result[i].Position[1] << ")" << endl;
		}
	}
	else
	{
		ofstream f;
		f.open("rectangular.csv", ios::out);
		if (!f.is_open())
		{
			wcout << "File not found\n";
			return;
		}
		else
		{
			f << "Cities,Latitude,Longitude" << endl;
			for (int i = 0; i < result.size(); i++)
			{
				f << result[i].Name << "," << result[i].Position[0] << "," << result[i].Position[1] << endl;
			}
		}
		f.close();
	}
	return;
}
