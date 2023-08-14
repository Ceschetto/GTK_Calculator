#include "../headers/calculator_data.h"


#define FLAG_OP1 0b1
#define FLAG_OP2 0b10
#define FLAG_DECIMAL 0b100
#define FLAG_OPERATION 0b1000

struct Calculator_Data 
{
    double n_decimals;
    double op1;
    double op2;
    double (* operation)(void);
    double res;
};

typedef struct Calculator_Data CalcData;
typedef CalcData *CalcDataPtr;



CalcDataPtr dataPtr = NULL;

unsigned char flags = '\0';



double sum(void);
double diff(void);
double mul(void);
double divv(void);
void set_operator_flag_active(void);
bool is_decimal(void);
void reset_calculator_preserve_res(void);
void set_false_decimal_flag(void);





void init_calculator(void)
{
    dataPtr = (CalcDataPtr) malloc(sizeof(CalcData));
    memset(dataPtr, 0, sizeof(CalcData));
    dataPtr->n_decimals = 0.1;

}



void set_operation(char operat)
{

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
    set_false_decimal_flag();

}

void set_operand(double op)
{



    if(!is_operator_selected())
    {


        flags |= FLAG_OP1;
        if(!is_decimal())
        {
            dataPtr->op1 = (dataPtr->op1 * 10) + op ;
        }
        else
        { 
            dataPtr->op1 += (op * dataPtr->n_decimals);
            dataPtr->n_decimals *= 0.1; 
        }


    }
    else
    {
        if(!is_decimal())
        {
            flags |= FLAG_OP2;            
            dataPtr->op2 = (dataPtr->op2 * 10) + op;

        }
        else
        {

            dataPtr->op2 += (op * dataPtr->n_decimals);
            dataPtr->n_decimals *= 0.1; 
        }

    }



    

}




double get_result(void)
{

    ((flags & FLAG_OPERATION) == 0)?  dataPtr->res = 0 : (dataPtr->res = (dataPtr->operation)());
    reset_calculator_preserve_res();  
    return dataPtr->res;  
}

double get_operand1(void)
{
    return dataPtr->op1;
}

double get_operand2(void)
{
    return dataPtr->op2;
}





bool is_operator_selected(void)
{
    return ((flags & FLAG_OPERATION) == 0)? false : true;
}

void set_operator_flag_active(void)
{
    flags |= FLAG_OPERATION;
}

bool is_decimal()
{
    return ((flags & FLAG_DECIMAL))? true : false;
}

void set_true_decimal_flag(void)
{
    flags |= FLAG_DECIMAL;
}

void set_false_decimal_flag(void)
{
    if(is_decimal()) flags ^= FLAG_DECIMAL;
    dataPtr->n_decimals = 0.1;
}


void reset_calculator_preserve_res(void)
{
    double res = dataPtr->res;
    flags = '\0';
    memset(dataPtr, 0, sizeof(CalcData));
    dataPtr->res = res;
}








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





