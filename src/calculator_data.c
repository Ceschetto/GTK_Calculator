#include "../headers/calculator_data.h"
#include "string.h"


struct Calculator_Data 
{
    double op1;
    double op2;
    double (* operation)(void);
    double res;
};

typedef struct Calculator_Data CalcData;
typedef CalcData *CalcDataPtr;


CalcDataPtr dataPtr = NULL;

char flagOp1 = 'n';
char flagOp2 = 'n';



double sum(void)
{
    return (dataPtr->res = dataPtr->op1 + dataPtr->op2);
}

double diff(void)
{
    return (dataPtr->res = dataPtr->op1 - dataPtr->op2);
}

double mul(void)
{
    return (dataPtr->res = dataPtr->op1 * dataPtr->op2);
}

double divv(void)
{
    return (dataPtr->res = dataPtr->op1 / dataPtr->op2);
}




void init_calculator(void)
{
    dataPtr = (CalcDataPtr) malloc(sizeof(CalcData));
    memset(dataPtr, 0, sizeof(CalcData));
}

void set_operation(char operat)
{
    switch (operat)
    {
    case '+':
        dataPtr->operation = sum;
        break;


    case '-':
        dataPtr->operation = diff;
        break;

    case '*':
        dataPtr->operation = mul;
        break;

    case '/':
        dataPtr->operation = divv;
        break;

    default:
        break;
    }
}

void set_operand(int op)
{

    if(flagOp1 == 'n')
    { 
        dataPtr->op1 = op;
        flagOp1 = 's';
    }
    else
    {
        if(flagOp2 == 'n')
        { 
            dataPtr->op2 = op;
            flagOp2 = 's';
        }
    }
}

void remove_operand(void)
{
    if(flagOp2 != 'n') 
    {
        dataPtr->op2 = 0;
        flagOp2 = 'n';
    }
    else
    {
        if(flagOp1 != 'n')
        { 
            dataPtr->op1 = 0;
            flagOp1 = 'n';
        }
    }
}

double get_result(void)
{
    return ((dataPtr->operation) == NULL)?  dataPtr->res : (dataPtr->res = (dataPtr->operation)());
}

