#include <iostream>

using namespace std;

string determinePrime(int number) {
  string num = to_string(number);
  for (int i = number-1; i > 1; i--) {
    if (number % i == 0) {
      return num + " is not a prime number";
    }
  }
  return num + " is a prime number";
}

int main() {
  cout << determinePrime(8) << endl;
  cout << determinePrime(7) << endl;
}
