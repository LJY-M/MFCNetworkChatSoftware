#pragma once
#include <afxsock.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

class SemanticPrsing
{
public:
	SemanticPrsing() {};
	~SemanticPrsing() {};

	int receivingOrder(vector<string> receivingOrderVector);
};

