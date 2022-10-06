#ifndef terminal_H_
#define terminal_H_
#include<stdio.h>
#include<string.h>
#include"../Std_types.h"
#include<time.h>
#include"../card/card.h"
#pragma warning(disable : 4996) //to disable warnings for using time library



 typedef struct ST_terminalData_t
{
	float32 transAmount;
	float32 maxTransAmount;
	uint8 transactionDate[11];
}ST_terminalData_t;
 
typedef enum EN_terminalError_t
{
	OKay, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

ST_terminalData_t terminal_data;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData); 

#endif // !terminal_H_

