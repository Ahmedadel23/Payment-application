#include<stdio.h>
#include"app.h"

extern account_database[255];
extern counter;
extern seq_num;
extern struct ST_cardData_t card_data;
 ST_transaction ST_trans;
void appStart(void)
{
	//card data 
	
	while (getCardHolderName(&card_data));
	printf("---------------------------1-----------------------\n\n");
	while (getCardExpiryDate(&card_data));
	printf("----------------------------2----------------------\n\n");
	while (getCardPAN(&card_data));
	printf("-----------------------------3---------------------\n\n");
	
	//terminal data
	ST_terminalData_t Term_data;
	(getTransactionDate(&Term_data));
	printf("-----------------------------4---------------------\n\n");
	while (isCardExpired(card_data, Term_data));
	 printf("-----------------------------5---------------------\n\n");
	while (getTransactionAmount(&Term_data));
	printf("----------------------------6----------------------\n\n");
	if (setMaxAmount(&Term_data))
		return;
	printf("-----------------------------7---------------------\n\n");
	if (isBelowMaxAmount(&Term_data))
		return;
	printf("------------------------------8--------------------\n\n");
	
	
	//server data
	
	if (isValidAccount(card_data))
		return;
	printf("-----------------------------9---------------------\n\n");
	(isBlockedAccount(&account_database[counter]));
	printf("------------------------------10--------------------\n\n");
	if (isAmountAvailable(&Term_data))
		return;
	printf("--------------------------------11------------------\n\n");
	if (saveTransaction(&card_data))
		return;
	printf("----------------------------------12----------------\n\n");
	//while (getTransaction(seq_num, &ST_trans));
	//printf("--------------------------------------------------\n\n");
	if (recieveTransactionData(&card_data))
		return;
	printf("------------------------------------13--------------\n\n");
}

int main()
{

	appStart();

	return 0;
}