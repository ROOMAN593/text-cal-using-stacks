
/**
  class Stack {
    Stack();
    bool isEmpty();
    bool push(OperationData newValue);
    OperationData pop();
    OperationData top();
  }
}
**/

#include "Stack.h"
#include "OperationData.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//RUNNER: Will run one test at a time, based on the test name given.
bool runSpecificTest(string testName);

//Check contents and print out any differences, removes items from the stack
bool validateAndPrintContents(Stack& stack, int numItems, OperationData *items, bool validateList);

//Method used to return a dynamically allocated stack with some items in it
Stack& getStack(OperationData arr[], int numItems);

bool testEmptyConstructor();

bool testAddOneOperationData();

bool testRemoveOneOperationData();

bool testAddAndRemoveManyOperationData();

bool testIsEmpty();

bool testCopyConstructor();

bool testCopyConstructorShallowCopy();

bool testAddAfterCopyConstructor();

bool testAssignmentOperator();

bool testAssignmentOperatorShallowCopy();

bool testAssignmentOperatorSelfCopy();

bool testAddAfterAssignmentOperator();

int main(int argc, char** argv)
{
    // Collection of test names
    vector<string> allTests = {
            "addOneItem", "removeOneItem",
            "addAndRemoveManyItems", "isEmpty",
            "copyConstructor", "copyConstructorShallowCopy",
            "assignmentOperator", "assignmentOperatorShallowCopy", "assignmentOperatorSelfCopy"
        };

    cout << "EMPTY CONSTRUCTOR TEST RUNNING..." << endl;
    bool constructor = testEmptyConstructor();

    //If the empty constructor test passes, run the rest of the tests.
    if(constructor){
        if (argc > 1){
            string testName = argv[1];
            //Run the test
            if (testName != "constructor"){
                runSpecificTest(testName);
            }
        } else {
            bool passedPreviousTest = true;
            int testIndex = 0;

            //Since a test name wasn't passed in, we will run all the tests in sequential passing order
            while (passedPreviousTest && testIndex < allTests.size()) {
                passedPreviousTest = runSpecificTest(allTests[testIndex++]);
            }

            if (passedPreviousTest){
                cout << "Congrats! You have passed all of the provided tests (" << allTests.size()+1 << "). Be sure to use Valgrind to check for memory leaks, and do your own thorough testing." << endl;
            } else {
                cout << "You have failed the last test that ran " << "(" << testIndex << "/" << allTests.size()+1 << "). Therefore, additional tests will not be run.\n"
                     << "Please fix your implementation so that the failing test passes, and run again once you feel you've fixed that functionality." << endl;
            }
        }
    } else {
        cout << "Constructor test failed, additional tests will not be run." << endl;
    }

    return 0;
}

bool runSpecificTest(string testName){
    if ( testName == "addOneItem" ) {
        //Call test
        cout << "ADD ONE ITEM (Needs top) TEST RUNNING..." << endl;
        return testAddOneOperationData();
    } else if ( testName == "removeOneItem" ) {
        //Call test
        cout << "REMOVE ONE ITEM TEST RUNNING..." << endl;
        return testRemoveOneOperationData();
    } else if ( testName == "addAndRemoveManyItems" ) {
        //Call test
        cout << "ADD & REMOVE MULTIPLE ITEMS TEST RUNNING..." << endl;
        return testAddAndRemoveManyOperationData();
    } else if ( testName == "isEmpty" ) {
        //Call test
        cout << "ISEMPTY TEST RUNNING..." << endl;
        return testIsEmpty();
    } else if ( testName == "copyConstructor" ) {
        //Call test
        cout << "COPY CONSTRUCTOR TEST RUNNING..." << endl;
        return testCopyConstructor();
    } else if ( testName == "copyConstructorShallowCopy" ) {
        //Call test
        cout << "COPY CONSTRUCTOR SHALLOW COPY TEST RUNNING..." << endl;
        return testCopyConstructorShallowCopy();
    } else if ( testName == "assignmentOperator" ) {
        //Call test
        cout << "ASSIGNMENT OPERATOR TEST RUNNING..." << endl;
        return testAssignmentOperator();
    } else if ( testName == "assignmentOperatorShallowCopy" ) {
        //Call test
        cout << "ASSIGNMENT OPERATOR SHALLOW COPY TEST RUNNING..." << endl;
        return testAssignmentOperatorShallowCopy();
    } else if ( testName == "assignmentOperatorSelfCopy" ) {
        //Call test
        cout << "ASSIGNMENT OPERATOR SELF COPY TEST RUNNING..." << endl;
        return testAssignmentOperatorSelfCopy();
    } else {
        cerr << "===TEST NAME NOT FOUND, HELP===" << endl;
        exit(1);
    }
}

bool validateAndPrintContents(Stack& stack, int numItems, OperationData *items = nullptr, bool validateList = true)
{
    //Instantiate vars to store test result
    bool passedTests = true;
    string testResult = "";

    try{
        //Check each item in the list
        if (numItems > 0 && validateList)
        {
            //Guard again nullptr in the items array
            if (items == nullptr)
            {
                //Test failure - exit immeadiately
                std::cerr << "TEST FAILURE: NULLPTR" << std::endl;
                exit(1);
            }

            for (int i = 0; i < numItems; i++)
            {
                OperationData top = stack.top();
                OperationData& curItem = items[numItems - i - 1];
                //Check each item
                if (
                        top.operatorChar != curItem.operatorChar ||
                        top.operand != curItem.operand ||
                        top.previousValue != curItem.previousValue
                    )
                {
                    //Print a failed result
                    testResult += "\n\tstack[" + std::to_string(i) + "] = OperationData(" + std::to_string(top.operatorChar) + ", " + std::to_string(top.operand) + ", " +  std::to_string(top.previousValue) + ")" +
                    "; SHOULD BE OperationData(" + std::to_string(curItem.operatorChar) + ", " + std::to_string(curItem.operand) + ", " +  std::to_string(curItem.previousValue) + ")\n";

                    //Some validation failed
                    passedTests = false;
                }

                stack.pop();
            }
        }
        
    } catch (std::exception& e)
    {
        std::cout << "EXCEPTION: " << e.what() << std::endl;
        passedTests = false;
    }

    if (passedTests)
    {
        std::cout << " PASSED" << std::endl;
    } else {
        std::cout << " FAILED" << testResult << std::flush;
    }

    return passedTests;
}

//Pass in nullptr, receive array of values copied to doublelist
Stack& getStack(OperationData arr[], int numItems){

    Stack* stack = new Stack();

    for(int i = 0; i < numItems; i++){
        (*stack).push(arr[i]);
    }

    return *stack;
}


bool testEmptyConstructor()
{
    Stack stack;

	return validateAndPrintContents(stack, 0, nullptr, false);
}


bool testAddOneOperationData()
{
    Stack stack;
    OperationData items[1] = { OperationData('a', 2, 3) };

    //Add int
    stack.push(items[0]);

    OperationData topOfStack = stack.top();

    if
    (
        topOfStack.operatorChar == items[0].operatorChar &&
        topOfStack.operand == items[0].operand &&
        topOfStack.previousValue == items[0].previousValue
    ){
        cout << " PASSED" << endl;
        return true;
    } else {
        cout << " FAILED\n\tstack[top] = OperationData(" << topOfStack.operatorChar <<  ", " << topOfStack.operand << ", " << topOfStack.previousValue << ")" <<
                        "; SHOULD BE OperationData(" << items[0].operatorChar << ", " << items[0].operand << ", " << items[0].previousValue << ")\n";
        return false;
    }
}

bool testRemoveOneOperationData()
{
    Stack stack;
    OperationData items[1] = { OperationData('a', 2, 3) };

    //Add int
    stack.push(items[0]);

    OperationData popItem = stack.pop();

    if
    (
        popItem.operatorChar == items[0].operatorChar &&
        popItem.operand == items[0].operand &&
        popItem.previousValue == items[0].previousValue
    ){
        cout << " PASSED" << endl;
        return true;
    } else {
        cout << " FAILED\n\tstack removed OperationData(" << popItem.operatorChar <<  ", " << popItem.operand << ", " << popItem.previousValue << ")" <<
                        "; SHOULD BE OperationData(" << items[0].operatorChar << ", " << items[0].operand << ", " << items[0].previousValue << ")\n";
        return false;
    }
}

bool testAddAndRemoveManyOperationData()
{
    OperationData items[5] = { 
        OperationData('a', 2, 3),
        OperationData('b', 5, 6),
        OperationData('c', 8, 9),
        OperationData('d', 11, 12),
        OperationData('e', 14, 15)
    };
    int numItems = 5;

    //Add ints
    Stack& stack = getStack(items, numItems);

    //Verify test results
	bool result = validateAndPrintContents(stack, numItems, items);
    delete &stack;
    return result;
}

bool testIsEmpty()
{
    Stack stack;
    bool passedTest = false;
    OperationData items[1] = { OperationData('a', 2, 3) };

    bool isEmptyNoItems = stack.isEmpty();

    if (!isEmptyNoItems){
        cout << " FAILED\n\tempty stack claims to not be empty" << endl;
    } else {
        //Add int
        stack.push(items[0]);

        bool isEmptyHasItems = stack.isEmpty();

        if (isEmptyHasItems){
            cout << " FAILED\n\tnot empty stack claims to be empty" << endl;
        } else {
            cout << " PASSED" << endl;
            passedTest = true;
        }
    }

    return passedTest;
}

bool testCopyConstructor()
{
    OperationData items[5] = { 
        OperationData('a', 2, 3),
        OperationData('b', 5, 6),
        OperationData('c', 8, 9),
        OperationData('d', 11, 12),
        OperationData('e', 14, 15)
    };
    int numItems = 5;

    //Add ints
    Stack& stack = getStack(items, numItems);
    Stack stack2(stack);

    //Verify test results
	bool result = validateAndPrintContents(stack2, numItems, items);
    delete &stack;
    return result;
}

bool testCopyConstructorShallowCopy()
{
    OperationData items[6] = { 
        OperationData('a', 2, 3),
        OperationData('b', 5, 6),
        OperationData('c', 8, 9),
        OperationData('d', 11, 12),
        OperationData('e', 14, 15),
        OperationData('f', 17, 18)
    };
    int numItems = 6;

    //Add ints
    Stack& stack = getStack(items, numItems-1);
    Stack stack2(stack);

    //Remove some items from the original stack and the stack
    stack.pop();
    stack.pop();
    stack.pop();
    delete &stack;

    stack2.push(OperationData('f', 17, 18));

    //Verify test results
	bool result = validateAndPrintContents(stack2, numItems, items);
    if (result) {
        cout << " (test assumes memory is being appropriately freed)" << endl;
    }
    return result;
}

bool testAssignmentOperator()
{
    OperationData items[6] = { 
        OperationData('a', 2, 3),
        OperationData('b', 5, 6),
        OperationData('c', 8, 9),
        OperationData('d', 11, 12),
        OperationData('e', 14, 15),
        OperationData('f', 17, 18)
    };
    int numItems = 6;

    //Add ints
    Stack& stack = getStack(items, numItems);
    Stack stack2;

    //Call assignment operatorChar
    stack2 = stack;

    //Verify test results
	bool result = validateAndPrintContents(stack2, numItems, items);
    delete &stack;
    return result;
}

bool testAssignmentOperatorShallowCopy()
{
    OperationData items[6] = { 
        OperationData('a', 2, 3),
        OperationData('b', 5, 6),
        OperationData('c', 8, 9),
        OperationData('d', 11, 12),
        OperationData('e', 14, 15),
        OperationData('f', 17, 18)
    };
    OperationData dummyArr[4] = { 
        OperationData('g', 1, 1),
        OperationData('h', 2, 2),
        OperationData('i', 3, 3),
        OperationData('j', 4, 4)
    };
    int numItems = 6;

    //Add ints
    Stack& stack = getStack(items, numItems-1);
    Stack& stack2 = getStack(dummyArr, 4);

    //Call assignment operatorChar
    stack2 = stack;

    //Remove some items from the original stack and the stack
    stack.pop();
    stack.pop();
    stack.pop();
    delete &stack;

    stack2.push(OperationData('f', 17, 18));

    //Verify test results
	bool result = validateAndPrintContents(stack2, numItems, items);
    if (result) {
        cout << " (test assumes memory is being appropriately freed)" << endl;
    }
    delete &stack2;
    return result;
}

bool testAssignmentOperatorSelfCopy()
{
    OperationData items[6] = { 
        OperationData('a', 2, 3),
        OperationData('b', 5, 6),
        OperationData('c', 8, 9),
        OperationData('d', 11, 12),
        OperationData('e', 14, 15),
        OperationData('f', 17, 18)
    };
    int numItems = 6;

    //Add ints
    Stack& stack = getStack(items, numItems);

    //Call assignment operatorChar
    stack = stack;

    //Verify test results
	bool result = validateAndPrintContents(stack, numItems, items);
    delete &stack;
    return result;
}