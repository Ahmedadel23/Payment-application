#include"server.h"
#include"../terminal/terminal.h"
uint8 counter ;
uint8 seq_num = 0;
uint8 block_check = 0;
extern float32 val;

 extern ST_accountsDB_t account_database[255] = {
	{2500.0, RUNNING, "1002341237897800" },
	{2000.0, BLOCKED, "1002341237897811" },
	{1500.0, RUNNING, "1002341237897822" },
	{5000.0, RUNNING, "1002341237897833" },
	{9000.0, BLOCKED, "1002341237897844" },
	{7000.0, RUNNING, "1002341237897855" },
	{1000.0, RUNNING, "1002341237897866" },
	{3000.0, BLOCKED, "1002341237897877" },
	{5000.0, RUNNING, "1002341237897888" },
	{6000.0, RUNNING, "1002341237897899" }
};


 ST_transaction transaction_database[255] = { 0 };



EN_transStat_t recieveTransactionData(ST_transaction* transData)
{
	EN_transStat_t r_transaction_data;

	if (isValidAccount(transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		printf("fraud card\n");
		transaction_database[seq_num].transState = FRAUD_CARD;
		return FRAUD_CARD;
		
		
	}
	
		
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
		{
		printf("DECLINED_INSUFFECIENT_FUND \n");
		transaction_database[seq_num].transState = DECLINED_INSUFFECIENT_FUND;
			return DECLINED_INSUFFECIENT_FUND;
			
		}

		else if (isBlockedAccount(&account_database[counter])==BLOCKED_ACCOUNT)
		{
		printf("DECLINED_STOLEN_CARD \n");
		transaction_database[seq_num].transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;

		}

		else if (saveTransaction(&transaction_database[seq_num])==SAVING_FAILED)
		{
		printf(" SAVING_FAILED \n");
		transaction_database[seq_num].transState = SAVING_FAILED;
		return SAVING_FAILED;
			
		}
		
		else
		{
		printf("APPROVED \n");
		printf("val= %f\n", val);
		account_database[counter].balance = account_database[0].balance - val;
		printf("new balance in account = %f\n", account_database[0].balance);
		
			return APPROVED;
		}

}

EN_serverError_t isValidAccount(ST_cardData_t cardData)
{
	
	counter = 0;
	uint8 check_flag = 0;
	for (uint8 i = 0; i <= 254; i++)
	{
		
		 
		if (strcmp((cardData.primaryAccountNumber),(account_database[i].primaryAccountNumber)) == 0)
		{
			check_flag = 1;
			counter = i;
			printf("counter=%d\n", counter);
			break;
		}
		else
		{
			check_flag = 0;

		}
		
	}

	if(check_flag==1)
	{
		printf("reference account:%s \n", account_database[counter].primaryAccountNumber);

		printf("valid account\n");
		//printf("counter=%d\n",counter);
		
		return SERVER_OK;
	}
	else
	{
		printf("account not found\n");
		//printf("counter=%d\n", counter);
		
		return ACCOUNT_NOT_FOUND;
	}
	
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{	
	accountRefrence->state = account_database[counter].state;
	
	//printf("state=%d \n", accountRefrence->state);
	//printf("counter=%d\n", counter);
	if (accountRefrence->state== RUNNING)
	{
		printf("running \n");
		
		return SERVER_OK;
	}
	else if(accountRefrence->state==BLOCKED)
	{
		printf("blocked \n");
		
		return BLOCKED_ACCOUNT;
	}
	else
	{

	}
	
	
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	//printf("counter=%d\n", counter);
	if (termData->transAmount <= account_database[counter].balance)
	{
		printf("server ok\n");
		return SERVER_OK;
	}
	else
	{
		printf("low balance\n");
		return LOW_BALANCE;
	}

}

EN_serverError_t saveTransaction(ST_transaction* transData)
{
	EN_serverError_t save_checker;

	transData->transactionSequenceNumber = seq_num;
	transaction_database[seq_num] = *transData;

	if ((transData->transactionSequenceNumber) >= 255)
	{
		save_checker= SAVING_FAILED;

		printf("save transaction is failed \n");
	}
	else
	{
		transaction_database[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		transaction_database[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		transaction_database[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
		seq_num++;
		save_checker= SERVER_OK;
		printf("save transaction is ok \n");
	}
	return save_checker;
		
}

EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction* transData)
{	
	int i;
	for ( i = 0; i < 255; i++)
	{
		if (transaction_database[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			printf("server is ok\n");
			return SERVER_OK;
		}
	}
	//printf("transaction :%s \n", transaction_database[i].transactionSequenceNumber);
	//printf("seq_num=%d", seq_num);
	//printf("transaction :%s \n", transaction_database[seq_num]);
	printf("transaction not found\n");
	
	return TRANSACTION_NOT_FOUND;

}
