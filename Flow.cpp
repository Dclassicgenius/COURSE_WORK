#include <iostream>
#include <fstream>
#include"Flow.h"
int main(int argc, char* argv[])
{
	try {
		ifstream input("TEXT.txt");
		Flow flow(input);
		int max_flow = flow.max_flow();
		cout << "Max flow for the graph is: " << max_flow;
	}
	catch (exception& error) {
		cout << error.what();
	}
	return 0;
}