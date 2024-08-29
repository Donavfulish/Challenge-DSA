#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include "Sub_function.h"
using namespace std;

wstring stringToWstring(const string& str);
void writeToCSV(string output, vector<Data> D);
vector<Data> loadListFile(string print);
void insert1City(Node*& root, vector<Data>& arrayData);
void insertFromFile(string filename, Node*& root, vector<Data>& arrayData);
void nearestNeighbor(Node*& root, string print, float target[2]);
void rectangular(Node* root, string print, float LeftBottom[2], float TopRight[2]);
void writeFileBin(string output, Node* root);
void printDataList(const vector<Data>& dataList);
vector<Data> getDataListFromTree(Node* root); // Use BFS