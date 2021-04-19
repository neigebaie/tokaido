#include "account.h"

void sha256_string(const char* string, char* outputBuffer)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[ACCOUNT_PSWD_SIZE - 1] = 0;
}

void print_account(Account account)
{
	printf("NICK = %s\n", account.nick);
	printf("PSWD = %s\n", account.pswd);
	printf("ID   = %d\n", account.id);
}

void account_load_file(Account* accounts, int* accountCount)
{
	FILE* file = fopen("user_data/accounts.dat", "r");
	*accountCount = 0;

	if (file == NULL) // pas de comptes
		return;

	while (!feof(file) && fread(&accounts[*accountCount], sizeof(Account), 1, file))
	{
		// print_account(accounts[*accountCount]);
		*accountCount = *accountCount + 1;
		if (*accountCount >= ACCOUNT_MAX_COUNT)
			break;
	}
	fclose(file);

	return;
}

int account_save_file(Account* accounts, int accountCount)
{
	struct stat st = {0};

	if (stat("user_data", &st) == -1) {
	    mkdir("user_data", 0700);
			printf("Création du dossier user_data\n");
	}

	FILE* file = fopen("user_data/accounts.dat", "w");

	if (file == NULL)
		return 1;

	for (int i = 0; i < accountCount; i++) {
		fwrite(&accounts[i], sizeof(Account), 1, file);
	}
	fclose(file);
	return 0;
}

int account_create(const char* nick, const char* pswd, char* outputMessage)
{
	Account accounts[ACCOUNT_MAX_COUNT];
	Account newAccount;
	int accountCount = 0;

	account_load_file(accounts, &accountCount);

	if(accountCount) // Regarde si le nickname est déja pris
	{
		for (int i = 0; i < accountCount; i++)
		{
			// printf("%d\n", i);
			if(strcmp(accounts[i].nick, nick) == 0)
			{
				strcpy(outputMessage, "Le nom d'utilisateur a déja été pris !");
				return 1;
			}
		}
	}

	if (strlen(nick) > ACCOUNT_NICK_SIZE) // Si le nickname est trop long
	{
		sprintf(outputMessage, "Nom d'utilisateur trop long ! (%d car. max)", ACCOUNT_NICK_SIZE);
		return 1;
	}

	if (strlen(pswd) > ACCOUNT_PSWD_SIZE) // Si le mdp est trop long
	{
		sprintf(outputMessage, "Mot de passe trop long ! (%d car. max)", ACCOUNT_PSWD_SIZE);
		return 1;
	}
	else if (strlen(pswd) < ACCOUNT_MIN_PSWD_LEN) // Si le mdp est trop court
	{
		printf("PSWD LEN = %d\n", strlen(pswd));
		sprintf(outputMessage, "Mot de passe trop court ! (%d car. min)", ACCOUNT_MIN_PSWD_LEN);
		return 1;
	}

	char outputBuffer[ACCOUNT_PSWD_SIZE];
	sha256_string(pswd, outputBuffer); // On hash le mdp pour plus de sécurité

	strcpy(newAccount.nick, nick);
	strcpy(newAccount.pswd, outputBuffer);
	newAccount.id = accountCount;
	newAccount.score = 0;

	// print_account(newAccount);

	accounts[accountCount] = newAccount;
	accountCount++;

	if (account_save_file(accounts, accountCount))
	{
		strcpy(outputMessage, "Sauvegarde du compte échouée :(");
		return 1;
	}

	strcpy(outputMessage, "Compte créé !");

	return 0;
}

int account_delete(int id)
{
	Account accounts[ACCOUNT_MAX_COUNT];
	int accountCount = 0;

	account_load_file(accounts, &accountCount);

	if (accountCount)
	{
		for (int i = 0; i < accountCount; i++)
		{
			if (accounts[i].id == id)
			{
				accounts[i] = accounts[accountCount - 1];
				accountCount--;
				account_save_file(accounts, accountCount);
				return 0;
			}
		}
		return 1; // Compte non trouvé
	}
	return 1; // Pas de comptes
}

int account_login(Account* loggedAccount, const char* nick, const char* pswd, char* outputMessage)
{
	Account accounts[ACCOUNT_MAX_COUNT];
	int accountCount = 0;

	account_load_file(accounts, &accountCount);

	if (accountCount)
	{
		char outputBuffer[65];
		sha256_string(pswd, outputBuffer);
		printf("HASH = %s\n", outputBuffer);

		for (int i = 0; i < accountCount; i++)
		{
			if (strcmp(accounts[i].nick, nick) == 0)
			{
				if (strcmp(accounts[i].pswd, outputBuffer) == 0)
				{
					// print_account(accounts[i]);
					memcpy(loggedAccount, &accounts[i], sizeof(Account));
					sprintf(outputMessage, "Bienvenue %s !", nick);
					return 0;
				}
				else
				{
					strcpy(outputMessage, "Mot de passe invalide !");
					return 1;
				}
			}
		}
	}
	strcpy(outputMessage, "Ce compte n'existe pas !");
	return 1;
}
