#include <iostream>
#include <fstream>
#include <vector>
#include <array>
using namespace std;

const string INPUT = "jungle.in";
const string OUTPUT = "jungle.out";
const int INFINITE = 1000;

array<array<int, 27>, 27> Distances;

struct Node
{
	char Label;
	char Parent;
	int Value;
	bool isChecked;
};

void ZeroOutDistances()
{
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 27; j++)
			Distances[i][j] = INFINITE;
}

void FlipArray()
{
	for (int i = 0; i < 27; i++)
		for (int j = 0; j < 27; j++)
			Distances[j][i] = Distances[i][j];
}

int FindShortestPath(char root, int numberOfRoads)
{
	vector<Node> NodeVector;

	for (int i = 0; i < numberOfRoads; i++)
	{
		Node insertNode;
		insertNode.Label = (char)i + 65;
		insertNode.Parent = NULL;
		insertNode.Value = INFINITE;
		insertNode.isChecked = false;
		NodeVector.push_back(insertNode);
	}

	NodeVector.at(0).Value = 0;

	int row = 0;
	int count = 0;
	while (count < numberOfRoads)
	{
		for (int col = 0; col < numberOfRoads; col++)
		{
			if (Distances[row][col] < NodeVector.at(col).Value &&
				Distances[row][col] != INFINITE &&
				Distances[row][col] > 0)
			{
				if (NodeVector.at(col).Label != NodeVector.at(row).Parent)
				{
					NodeVector.at(col).Parent = NodeVector.at(row).Label;
					NodeVector.at(col).Value = Distances[row][col];
				}
			}
		}

		// Finished checking this Node's value
		NodeVector.at(row).isChecked = true;

		// Find next row but getting smallest value number
		int valueSize = INFINITE;
		char tempLabel;
		for (int i = 0; i < numberOfRoads; i++)
		{
			if (!NodeVector.at(i).isChecked && NodeVector.at(i).Value < valueSize)
			{
				valueSize = NodeVector.at(i).Value;
				tempLabel = NodeVector.at(i).Label;
			}
		}

		if (++count < numberOfRoads)
			row = tempLabel - 65;	
	}

	// add up values
	int total = 0;
	for (int i = 0; i < numberOfRoads; i++)
		total += NodeVector.at(i).Value;

	return total;
}

int main()
{
	ifstream fin(INPUT);
	if (fin)
	{
		ofstream fout(OUTPUT);

		int readSize;

		fin >> readSize;
		while (readSize != 0)
		{
			// clear out array
			ZeroOutDistances();

			char label; int numberOfRoads; int distance;
			bool hasRoot = false;

			fin >> label;
			char root = label; hasRoot = true;
			for (int row = 0; row < readSize - 1; row++)
			{
				if (hasRoot == true)
				{
					fin >> numberOfRoads;
					hasRoot = false;
				}
				else
					fin >> label >> numberOfRoads;

				Distances[row][label - 65] = 0;

				for (int col = 0; col < numberOfRoads; col++)
				{
					fin >> label >> distance;
					Distances[row][label - 65] = distance;
				}
			}

			FlipArray();

			int total = FindShortestPath(root, readSize);

			cout << total << endl;
			fout << total << endl;

			fin >> readSize;
		}

		fout.close();
		fin.close();
	}
	else
	{
		cout << "The input file could not be found." << endl;
	}
}