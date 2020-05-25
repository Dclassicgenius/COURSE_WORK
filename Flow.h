#pragma once
#include <fstream>
#include "List.h"
#include<string>
#include"Map.h"
using namespace std;
class Flow {
public:
	Flow(ifstream& file)
	{
		Map<char, int>* Map_from_char_to_number = new Map<char, int>();
		vertexCount = 0;
		int str_num = 1;
		while (!file.eof()) {
			string s1;
			getline(file, s1);
			if (s1.size() >= 5) {// minimum possible input(two letters, two spaces,one digit)
				if (!((s1[0] >= 'A' && s1[0] <= 'Z') && (s1[1] == ' '))) {
					throw exception("Error entering the first character in the string or missing a space after it. ");
				}
				if (!((s1[2] >= 'A' && s1[2] <= 'Z') && (s1[3] == ' '))) {
					throw exception("Error entering the second character in the string or missing a space after it. ");
				}
				string cur;
				for (int i = 4; i < s1.size(); i++) {
					if (s1[i] >= '0' && s1[i] <= '9')
						cur += s1[i];
					else {
						throw exception("Error entering the third character in the string, the presence of a space after it or a negative number. ");
					}
				}
				if (!Map_from_char_to_number->find_is(s1[0])) {
					Map_from_char_to_number->insert(s1[0], vertexCount);
					++vertexCount;
				}
				if (!Map_from_char_to_number->find_is(s1[2])) {
					Map_from_char_to_number->insert(s1[2], vertexCount);
					++vertexCount;
				}

			}
			else
			{
				throw exception("A data-entry error. Check the correctness of the input in the file. ");
			}
			++str_num;
		}
		if (Map_from_char_to_number->find_is('S'))
			sourceVertex = Map_from_char_to_number->find('S');
		else {
			throw exception("Source is missing");
		}

		if (Map_from_char_to_number->find_is('T'))
			destinationVertex = Map_from_char_to_number->find('T');
		else {
			throw exception("Sink is missing");
		}
		file.clear();
		file.seekg(ios::beg);


		excess_flow = new int[vertexCount];
		height = new int[vertexCount];
		capacity_edge = new int* [vertexCount];
		for (int i = 0; i < vertexCount; i++) {
			excess_flow[i] = 0;
			height[i] = 0;
		}
		for (int i = 0; i < vertexCount; i++) {
			capacity_edge[i] = new int[vertexCount];
			for (int j = 0; j < vertexCount; j++)
				capacity_edge[i][j] = 0;
		}
		str_num = 1;
		while (!file.eof()) {
			string s1;
			int vertex1, vertex2, capacity;
			getline(file, s1);
			vertex1 = Map_from_char_to_number->find(s1[0]);
			vertex2 = Map_from_char_to_number->find(s1[2]);
			if (vertex1 == vertex2)
				throw exception("There is a path from the vertex to itself. ");
			capacity_edge[vertex1][vertex2] = stoi(s1.substr(4));
			++str_num;
		}
	}

	template<typename T>
	T min(T a, T b) {
		return a > b ? b : a;
	}

	int max_flow() {
		if (vertexCount > 2) {
			for (int i = 0; i < vertexCount; i++)
			{
				if (i == sourceVertex)
					continue;
				excess_flow[i] = capacity_edge[sourceVertex][i];
				capacity_edge[i][sourceVertex] += capacity_edge[sourceVertex][i];
			}
			height[sourceVertex] = vertexCount;
			List<int> list;
			int current;
			int current_index = 0;
			int old_height;
			for (int i = 0; i < vertexCount; i++)
				if (i != sourceVertex && i != destinationVertex)
					list.push_front(i);
			current = list.at(0);
			while (current_index < list.get_size())
			{
				old_height = height[current];
				discharge(current);
				if (height[current] != old_height)
				{
					list.push_front(current);
					list.remove(++current_index);
					current = list.at(0);
					current_index = 0;
				}
				++current_index;
				if (current_index < list.get_size())
					current = list.at(current_index);

			}
			if (excess_flow[destinationVertex] > 0)
				return excess_flow[destinationVertex];
			else
				throw exception("There is no path from the source to the sink");
		}
		else
			return capacity_edge[0][1];
	}

	void push(int edge, int vertex)
	{
		int f = min(excess_flow[edge], capacity_edge[edge][vertex]);
		excess_flow[edge] -= f;
		excess_flow[vertex] += f;
		capacity_edge[edge][vertex] -= f;
		capacity_edge[vertex][edge] += f;
	}

	void lift(int edge)
	{
		int min = 2 * vertexCount + 1;

		for (int i = 0; i < vertexCount; i++)
			if (capacity_edge[edge][i] && (height[i] < min))
				min = height[i];
		height[edge] = min + 1;
	}

	void discharge(int edge)
	{
		int vertex = 0;
		while (excess_flow[edge] > 0)
		{
			if (capacity_edge[edge][vertex] && height[edge] == height[vertex] + 1)
			{
				push(edge, vertex);
				vertex = 0;
				continue;
			}
			vertex++;
			if (vertex == vertexCount)
			{
				lift(edge);
				vertex = 0;
			}
		}
	}
	~Flow() {
		delete[] excess_flow;
		delete[] height;
		for (int i = 0; i < vertexCount; ++i)
			delete[] capacity_edge[i];
	}
private:
	int* excess_flow;
	int** capacity_edge;
	int* height;
	int vertexCount, sourceVertex, destinationVertex;
};