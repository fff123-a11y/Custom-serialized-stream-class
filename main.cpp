#include<iostream>
#include"SDataStream.h"
using namespace std;

int main()
{
	SDataStream stream;
	stream << 12345 << 5.23 << "hello word" << std::string("string");
	cout << stream.str() << endl;
	auto s = stream.str();
	cout << stream << endl;
	return 0;
}
