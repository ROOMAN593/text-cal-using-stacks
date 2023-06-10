#ifndef OPERATIONDATA_H
#define OPERATIONDATA_H

struct OperationData {
    char operatorChar;
    int operand;
    int previousValue;

    //Constructors
    OperationData() {}
    OperationData(char theOperator, int theOperand, int prevVal) : operatorChar(theOperator), operand(theOperand), previousValue(prevVal) {}
};

#endif // !OPERATIONDATA_H