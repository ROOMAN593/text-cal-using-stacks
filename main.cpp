#include<iostream>
#include<fstream>
#include<string>
#include "Stack.h"
#include <cstdlib>
using namespace std;




int main(int argc,char *argv[]) {
    string infilename,ofilename;

	// ofstream outfile("sum.txt");

	infilename=argv[1];
    ofilename=argv[2];
    // ofstream outfile(ofilename);
	  ofstream outfile(argv[2]);
    if(outfile.fail())
    {
        cerr << "Could not openfor Output\n";
        return 0;
    }
      ifstream infile(argv[1]);
    if (infile.fail())
    {
        cerr << "Could not open " << argv[1] << " for input\n";
        return 0;
    }

    int result = 0;
    Stack undoStack, redoStack,st;
    outfile << "Welcome to the Undo-Redo Calculator!" << endl;
    outfile << "This calculator handles the following commands: +, -, *, /, %, C, U, R, and Q" << endl;
    outfile << "Arithmetic operators are followed by a single positive integer." << endl;
    outfile << "C will clear memory, U will undo, R will redo, and Q will quit." << endl;
    outfile << result << endl;
    // outfile << ">";

    
      
      string line= "";
      while (infile >> line)
      {
        //  std:: getline(infile,line);
        //  cout<<"Hi "<<line<<endl;
        //  infile >> line;
        //   cout<<"Hey "<<line<<endl;
        char command;

        int value;
        command = line[0];
        // cout<<"Hi "<<command<<endl;
        string x;
        if(line.length()>1)
        {
        for(int i = 1; i <= line.length(); i++) 
        {
            x= x + line[i];
        }
        
        value = stoi(x);
        // cout<<"i "<<value<<endl;
        }
        else
        {
            value =0;
        }
        
        OperationData d;
        d=st.top();
        result = d.operand;
        if (command == '+') {
            // cin >> value;
            
            // cout<<"op "<<d.operand<<endl;
            // cout<<"opc "<<d.operatorChar<<endl;
            // cout<<"opp "<<d.previousValue<<endl;
            result += value;
            
            d.operand = result;
            d.operatorChar = command;
            d.previousValue = value;
            outfile << ">"<< result<<endl;
            st.push(d);
            while (!redoStack.isEmpty()) {
                redoStack.pop();
            }
        } else if (command == '-') {
            // cin >> value;
            result -= value;
            d.operand = result;
            d.operatorChar = command;
            d.previousValue = value;
            outfile << ">"<< result<<endl;
            st.push(d);
            while (!redoStack.isEmpty()) {
                redoStack.pop();
            }
        } else if (command == '*') {
            // cin >> value;
            result *= value;
            d.operand = result;
            d.operatorChar = command;
            d.previousValue = value;
            outfile << ">"<< result<<endl;
            st.push(d);
            while (!redoStack.isEmpty()) {
                redoStack.pop();
        }
            }
         else if (command == '/') {
            // cin >> value;
            result /= value;
            d.operand = result;
            d.operatorChar = command;
            d.previousValue = value;
            outfile << ">"<< result<<endl;
            st.push(d);
            while (!redoStack.isEmpty()) {
                redoStack.pop();
         }
            }
         else if (command == '%') {
            // cin >> value;
            result %= value;
            d.operand = result;
            d.operatorChar = command;
            d.previousValue = value;
            outfile << ">"<< result<<endl;
            st.push(d);
            while (!redoStack.isEmpty()) {
                redoStack.pop();
         }
            }
       
      else if (command == 'C') {
          OperationData temp;
          temp = st.top();
            result = 0;
            d.operand = temp.previousValue;
            d.previousValue = 0;
            d.operatorChar = command;
            // st.pop();
            st.push(d);
            
            redoStack.pop();

        }
        else if (command == 'U') {
          if (st.isEmpty()) {
        outfile << ">Nothing to undo." << endl;
      } else {
          redoStack.push(st.top());
          st.pop();
        OperationData temp = st.top();
        outfile<<">"<<temp.operand<<endl;
        // int previousValue = temp.previousValue;
        // st.pop();
        // int currentValue = temp.operand;
        // char previousOperation = temp.operatorChar;
        // if (previousOperation == '+') {
        //   currentValue -= previousValue ;
        // } else if (previousOperation == '-') {
        //   currentValue += previousValue;
        // } else if (previousOperation == '*') {
        //   currentValue /= previousValue ;
        // } else if (previousOperation == '/') {
        //   currentValue *= previousValue ;
        // } else if (previousOperation == '%') {
        //   int remainder = currentValue %  previousValue;
        //   currentValue -=  remainder;
        // }
        // outfile<<">"<<currentValue<<endl;
        //  d  = st.top();
        //  temp.operatorChar = d.operatorChar;
        //  temp.operand = currentValue;
        //  st.push(temp);
        }
        
      }
      else if (command == 'R') {
      if (redoStack.isEmpty()) {
        outfile << ">Nothing to redo." << endl;
        OperationData d = st.top();
        outfile << d.operand << endl;
      } else {
        st.push(redoStack.top());
        OperationData d = redoStack.top();
        outfile << ">Redoing:" << d.operatorChar <<d.previousValue << endl;
        redoStack.pop();
      
        
        // redoStack.push(undoStack.top());
        // OperationData temp = redoStack.top(); 
        // int currentValue = temp.operand;
        // int previousValue = temp.previousValue;
        // char previousOperation = temp.operatorChar;
        // if (previousOperation == '+') {
        //   currentValue += previousValue ;
        //   outfile<<">Redoing :"<< previousValue<<endl;
        // } else if (previousOperation == '-') {
        //     currentValue -= previousValue ;
        //     outfile<<">Redoing :"<< previousValue<<endl;
        // }
        // else if (previousOperation == '*') {
        //     currentValue *= previousValue ;
        //     outfile<<">Redoing :"<< previousValue<<endl;
        // }
        // else if (previousOperation == '/') {
        //     currentValue /= previousValue ;
        //     outfile<<">Redoing :"<< previousValue<<endl;
        // }
        // else if (previousOperation == '%') {
        //     currentValue %= previousValue ;
        //     outfile<<">Redoing :"<< previousValue<<endl;
        // }
        // outfile<< currentValue;
        // temp.operand = currentValue;
        // undoStack.push(temp);
        //  while (!redoStack.isEmpty()) {
        //         redoStack.pop();
        // }
      

    }
      }
    else if (command == 'Q') {
            outfile << "Goodbye." << endl;
            return 1;
      
}

}
	infile.close();
    outfile.close();
}

