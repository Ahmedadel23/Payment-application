
#ifndef card_H_
#define card_H_
#include<stdio.h>
#include<string.h>
#include"../Std_types.h"


typedef enum EN_cardError_t
{
	OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


typedef struct ST_cardData_t
{
	uint8 cardHolderName[25];
	uint8 cardExpirationDate[6];
	uint8 primaryAccountNumber[20];
	
}ST_cardData_t;

struct ST_cardData_t card_data;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);



#endif // !card_H_
