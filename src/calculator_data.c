#include "../headers/calculator_data.h"
 

#define FLAG_OP1 0b1
#define FLAG_OP2 0b10
#define FLAG_OPERATION 0b100

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

unsigned char flags = '\0';



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

void set_operation(void *operatStr)
{
    char operat = *((char *)operatStr);
    switch (operat)
    {
    case '+':
        (dataPtr->operation) = sum;
        break;


    case '-':
        (dataPtr->operation) = diff;
        break;

    case '*':
        (dataPtr->operation) = mul;
        break;

    case '/':
        (dataPtr->operation) = divv;
        break;

    default:
        return;
        break;
    }
    flags |= FLAG_OPERATION;

}


void set_operand(void *opPtr)
{
    int op = *((int *)opPtr);

    if((flags & FLAG_OP1) == 0)
    { 
        dataPtr->op1 = op;
        flags |= FLAG_OP1;
    }
    else
    {
        if((flags & FLAG_OP2) == 0)
        { 
            dataPtr->op2 = op;
            flags |= FLAG_OP2;
        }
    }
    

}


double get_result(void)
{

    ((flags & FLAG_OPERATION) == 0)?  dataPtr->res = 0 : (dataPtr->res = (dataPtr->operation)());
    flags = '\0';  
    return dataPtr->res;  
}

