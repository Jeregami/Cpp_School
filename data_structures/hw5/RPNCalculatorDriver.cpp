/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.cpp"
#include <iostream>
#include <iomanip>
using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

int main()
{
  RPNCalculator stack;

  string userInput;
  float calculation;

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, userInput);
    if (userInput != "=") {
      if (isNumber(userInput)) {
        stack.push(stof(userInput));
      }
      else {
        stack.compute(userInput);
      }
    }
    else {
      if (stack.isEmpty()) {
        cout << "No operands: Nothing to evaluate" << endl;
        break;
      }
      calculation = stack.peek()->number;
      stack.pop();
      if (!stack.isEmpty()) {
        cout << "Invalid expression" << endl;
      }
      else {
        cout << setprecision(4) << calculation << endl;
      }
      break;
    }
  }
  return 0;
}
