#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const string INPUT = "jungle.in";
const string OUTPUT = "jungle.out";

struct Node
{
	char Label;
	char Parent;
	int Value;
};

void main()
{
	ifstream fin(INPUT);
	if (fin)
	{
		ofstream fout(OUTPUT);
		
		vector<vector<Node>> NodeVector;
		int readSize;

		fin >> readSize;
		while (readSize != 0)
		{
			if (readSize >= 1 && readSize < 27)
			{
				// get each line and insert into 2D NodeVector
				char label; int numberOfRoads; int value;
				for (int i = 0; i < readSize - 1; i++)
				{
					vector<Node> temp;
					fin >> label >> numberOfRoads;
					cout << label << numberOfRoads << " ";
					
					Node tempParent;
					tempParent.Label = label;
					tempParent.Parent = NULL;
					tempParent.Value = 0;

					temp.push_back(tempParent);

					for (int j = 0; j < numberOfRoads; j++)
					{
						fin >> label >> value;
						cout << label << value << " ";

						Node connectedNode;
						connectedNode.Label = label;
						connectedNode.Parent = NULL;
						connectedNode.Value = value;

						temp.push_back(connectedNode);
					}

					NodeVector.push_back(temp);
					cout << endl;
				}
			}

			//Node Root;
			//Root.Label;
			//Root.Parent = NULL;
			//Root.Value = 0;

			fin >> readSize;
		}


		fout.close();
		fin.close();
	}
	else
	{
		cout << "Input file not found." << endl;
	}
}