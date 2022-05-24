#pragma once
#include <iostream>
#include <string>
class Report
{
public:
	Report(char c, int v, int p) { character = c; value = v; pos = p; };
	char character;
	int value;
	int pos;
};

