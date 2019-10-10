#include<iostream>
#include<string>
using namespace std;

/*
// Split 'arr' into 'even_arr' & 'odd_arr'
//  - 'arr': pointer to original array
//  - 'even_arr': pointer to even array
//  - 'odd_arr': pointer to odd array
*/
void split(int* &arr, int* &even_arr, int* &odd_arr, int size, int &even_size, int &odd_size)
{
  int evenIndex = 0;
  int oddIndex = 0;
  // Going through array
  for (int i = 0; i < size; i++) {
    // If the number divided by 2 has no remainder, it should be even
    if (arr[i] % 2 == 0) {
      even_arr[evenIndex] = arr[i];
      evenIndex++;
    }
    else {
      odd_arr[oddIndex] = arr[i];
      oddIndex++;
    }
  }
}

void printArray(int* arr, int size) {
    for(int i = 0; i<size; i++)
    {
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;
}

int main(int argc, char* argv[])
{
    if(argc<2)
    {
      cout<<"usage: a.out <#>";
      return -1;
    }

	// Create input array:
    int size = stoi(argv[1]);
    int *arr = new int[size];

    cout<< "original array: ";
    for(int i = 0; i<size; i++)
    {
        arr[i] = rand()%100;
        cout<< arr[i];
        if(i < size-1)
          cout << ", ";
    }
    cout<<endl;

  // Figuring out the odd and even array sizes
    int numOdd;
    int numEven;
    for (int i = 0; i < size; i++) {
      if (arr[i] % 2 == 0) {
        numEven++;
      }
      else {
        numOdd++;
      }
    }
    int even_arr[numEven];
    int odd_arr[numOdd];
  	split(arr, even_arr, odd_arr, size, numEven, numOdd);

    cout << "Odd Numbers: ";
    for (int i = 0; i < numOdd; i++) {
      cout << odd_arr[i] << " ";
    }
    cout << endl;
    cout << "Even Numbers: ";
    for (int i = 0; i < numEven; i++) {
      cout << even_arr[i] << " ";
    }

    delete [] even_arr;
    delete [] odd_arr;

    return 0;
}
