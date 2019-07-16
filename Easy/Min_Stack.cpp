#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class MinStack {
  private:
    vector<int> stack;
    int minElement;
    int numMin;
    char popped;

  public:
    /** initialize your data structure here. */
    MinStack() {
      stack = vector<int>();
      minElement = std::numeric_limits<int>::max();
      popped = false;
      numMin = 0;
    }

    void push(int x) {
      stack.push_back(x);
      if(x < minElement) {
        minElement = x;
        numMin = 1;
      } else if(x == minElement) numMin++;
    }

    void pop() {
      if(stack.back() == minElement && --numMin == 0) popped = true;
      stack.pop_back();
    }

    int top() {
      return stack.back();
    }

    int getMin() {
      if(popped) {
        minElement = std::numeric_limits<int>::max();
        for(int i: stack) {
          if(i < minElement) {
            minElement = i;
            numMin = 1;
          } else if(i == minElement) numMin++;
        }
        popped = false;
      }

      return minElement;
    }
};

// https://leetcode.com/problems/min-stack/discuss/49016/C%2B%2B-using-two-stacks-quite-short-and-easy-to-understand
class MinStackGoodSolution {
  private:
    stack<int> stOriginal;
    stack<int> stMin;

  public:
    MinStack() {
      // Do nothing
    }

    void push(int x) {
      storiginal.push(x);
      if(stMin.empty() || x <= getMin()) stMin.push(x);
    }

    void pop() {
      if(stOriginal.top() == stMin.top()) stMin.pop();
      stOriginal.pop();
    }

    int top() {
      return stOriginal.top();
    }

    int getMin() {
      return stMin.top();
    }
}

int main() {
  MinStack* obj = new MinStack();
  obj->push(-2);
  obj->push(0);
  obj->push(-3);
  cout << obj->getMin() << endl;
  obj->pop();
  cout << obj->top() << endl;
  cout << obj->getMin() << endl;

  delete(obj);
}
