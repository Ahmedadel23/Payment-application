#include"card.h"

uint16 charToInt(uint8 c) {
	uint16 num = 0;

	//Substract '0' from entered char to get
	//corresponding digit
	num = c - '0';

	return num;
}



EN_cardError_t getCardHolderName(ST_cardData_t * cardData)
{
	uint8 size=0;
	printf("Enter Holder Name: ");
	gets(cardData->cardHolderName);
	size = strlen(cardData->cardHolderName);
	if ( ((size >= 20) && (size <= 24))||(size==0))
	{
		printf("\n size is OK \n");
		return OK;
		
	}
	else
	{
		printf("\n size is Wrong \n");
		return WRONG_NAME;
		
	}
	
}



EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8 size = 0;
	uint8 month = 0;
	uint8 check_char = 0; // to check / in the middle between month and year
	uint8 check_month = 0; // to check value of month decimals from 1 to 12
	printf("Enter Expire Date: \n");
	gets(cardData->cardExpirationDate);
	size = strlen(cardData->cardExpirationDate);
	for (int i = 0; i < 2; i++)
	{
		month=(month*10)+charToInt(cardData->cardExpirationDate[i]);
	}
	
	 
		if ((month >= 1) && (month <= 12))
		{
			printf("correct Month \n");
			check_month = 0;
		}
		else
		{
			printf("wrong Month \n");
			check_month = 1;
		}
	
		if ((cardData->cardExpirationDate[2]) == '/')
		{
			printf("found / \n");
			check_char = 0;
		}
		else
		{
			printf("not found / \n");
			check_char = 1;
		}

	if ((size == 0) || (size < 5) || (size > 5) || (check_char==1) || (check_month==1))
	{
		printf(" wrong expire date  \n");
		return WRONG_EXP_DATE;
	}
	else
	{
		printf("correct expire date  \n");
		return OK;
	}
	check_char = 1;
	check_month = 1;

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{	
	uint16 size = 0;
	uint8 i = 0;
	uint8 check_alphanumuric = 0;
	printf("Enter PAN Number: \n");
	gets(cardData->primaryAccountNumber);
	size = (strlen(cardData->primaryAccountNumber));
	while ((cardData->primaryAccountNumber[i]) != '\0')
	{
		if ((charToInt(cardData->primaryAccountNumber[i]) >= 0) && (charToInt(cardData->primaryAccountNumber[i]) <= 9)
			|| ((cardData->primaryAccountNumber[i]) >= 'a') && ((cardData->primaryAccountNumber[i]) <= 'z')
			|| ((cardData->primaryAccountNumber[i]) >= 'A') && ((cardData->primaryAccountNumber[i]) <= 'Z'))
		{
			check_alphanumuric = 0;
		}
		else
		{
			printf("wrong alpha \n");
			check_alphanumuric = 1;
			break;
		}
		i++;
	}
	printf("size=%d \n ", size);
	if  (((size >= 16) && (size <= 19))&&(check_alphanumuric==0))
	{
		printf("card PAN is OK \n");
		return OK;
	}
	else
	{
		
		printf("wrong PAN \n");
		return WRONG_PAN;
	}
	check_alphanumuric = 0;

}


