/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.cpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[])
{
	ProducerConsumer queue;
	string choice;
	string itemChoice;
	int numItems;
	string item;
	int loop = 0;

	while (loop < 1) {
		menu();
		getline(cin, choice);
		switch (stoi(choice)) {
			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				getline(cin, itemChoice);
				numItems = stoi(itemChoice);
				for (int i = 0; i < numItems; i++) {
					cout << "Item" << (i+1) << ":" << endl;
					getline(cin, item);
					queue.enqueue(item);
				}
				break;
			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				getline(cin, itemChoice);
				numItems = stoi(itemChoice);
				for (int i = 0; i < numItems; i++) {
					if (queue.isEmpty()) {
						cout << "No more items to consume from queue" << endl;
						break;
					}
					else {
						cout << "Consumed: " << queue.peek() << endl;
						queue.dequeue();
					}
				}
				break;
			case 3:
				cout << "Number of items in the queue:" << queue.queueSize() << endl;
				loop = 2;
				break;
		}
	}
}
