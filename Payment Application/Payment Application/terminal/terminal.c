#include"terminal.h"
#include "../server/server.h"
float32 val;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8 size = 0;
	uint8 size_month;
	
	uint8  str1[3] = {0}, str2[5] = {0};
	uint8 str_m[3] = {'0'};
	time_t now = time(NULL);
	struct tm* current_time;
	current_time = localtime(&now);

	uint8 val_month = current_time->tm_mon+1;
	sprintf(termData->transactionDate, "%d", current_time->tm_mday);
	sprintf(str1, "%d", val_month);
	sprintf(str2, "%d", (current_time->tm_year)+1900);
	//printf("%s \n", termData->transactionDate);
	//printf("%s \n", str1);
	//printf("%s \n", str2);
	size_month = strlen(str1);
	//printf("str1 %s\n", str1);
	//printf("strm %s\n", str_m);
	//printf("val=%d\n", val_month);
	if ((val_month >= 0) && (val_month <= 9))
	{
		strcat(str_m, str1);
	}
	else
	{
		str_m[0] = str1[0];
		str_m[1] = str1[1];
	}
	
	
	strcat(termData->transactionDate, "/");
	strcat(termData->transactionDate,str_m);
	strcat(termData->transactionDate, "/");
	strcat(termData->transactionDate, str2);
	printf("%s \n", termData->transactionDate);
	size = strlen(termData->transactionDate);
	printf("size=%d \n", size);
	if ((size == 0) || (size < 9))
	{
		printf("wrong date \n");
		return WRONG_DATE;
	}
	else
	{
		printf("correct date\n");
		return OKay;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint8 card_month=0;
	uint8 card_year=0;
	uint8 term_month=0;
	uint8 term_year=0;
	card_month = charToInt(cardData.cardExpirationDate[0]) * 10 + charToInt(cardData.cardExpirationDate[1]);
	//printf("card month=%d \n",card_month);
	card_year = charToInt(cardData.cardExpirationDate[3]) * 10 + charToInt(cardData.cardExpirationDate[4]);
	//printf("card year=%d \n",card_year);
	term_month = charToInt(termData.transactionDate[3]) * 10 + charToInt(termData.transactionDate[4]);
	//printf("term month=%d \n", term_month);
	term_year = charToInt(termData.transactionDate[8]) * 10 + charToInt(termData.transactionDate[9]);
	//printf("term year=%d \n", term_year);
	if (card_year < term_year)
	{
		printf("year is invalid\n");
		return EXPIRED_CARD;
	}
	else if((term_month>card_month)&&(term_year>card_year))
	{
		printf("month is invalid\n");
		return EXPIRED_CARD;
	}
	else
	{
		printf("card expired date is vaild\n");
		return OKay;
	}
	
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	
	printf("enter transaction amount:\n");
	scanf_s("%f",&val);
	termData->transAmount=val;
	if (termData->transAmount <= 0)
	{
		printf("invalid trans amount\n");
		return INVALID_AMOUNT;
	}
	else
	{
		printf("valid trans amount\n");
		return OKay;
	}

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		printf("exceed max amount\n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		printf("not exceed trans amount\n");
		return OKay;
	}

}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	float32 value=5000.0;
	termData->maxTransAmount = value;
	if ((termData->maxTransAmount) <= 0)
	{
		printf("invalid max amount\n");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		
		printf("valid max amount\n");
		return OKay;
	}

}