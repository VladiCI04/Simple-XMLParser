#pragma once
#include "Parent.h"
#include <fstream>

constexpr unsigned short BUFFERSIZE_CONSTANT = 200;

class HelperFunctions {
protected:
	size_t getFileSize(std::ifstream& in);
	unsigned parseNumber(const String number);
	void printParent(const Parent curParent);
	void printChild(const Child curChild);
	void printParentToFile(std::ofstream& out, const Parent curParent);
	void printChildToFile(std::ofstream& out, const Child curChild);
};