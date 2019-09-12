#include <iostream>
#include <fstream>

using namespace std;


void resize(int *&arrayPtr, int &capacity)
{
	int newCapacity = capacity*2;
  cout << "Resizing from " << capacity << " to " << newCapacity << endl;

	int *newArray = new int[newCapacity];

  for (int i = 0; i < capacity; i++) {
    newArray[i] = arrayPtr[i];
  }

	arrayPtr = newArray;
	capacity = newCapacity;

}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		return -1;
	}
	string filename = argv[1];
	ifstream data;
	data.open(filename.c_str());

	int capacity = 10;
	int *arrayPtr;
	arrayPtr = new int[capacity];
	int numOfElement = 0;
	string temp;

	if(data.is_open())
	{
		while(getline(data, temp))
		{
			int toBeInsert = stoi(temp);
			if(numOfElement == capacity)
			{
				resize(arrayPtr, capacity);
			}
			arrayPtr[numOfElement] = toBeInsert;
			numOfElement++;
		}
		data.close();
	}

	for(int i = 0; i < numOfElement; i++)
	{
		cout << " " << "Num: " << arrayPtr[i] << endl;
	}
	return 0;
}
