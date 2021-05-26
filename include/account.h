#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/sha.h>

#define ACCOUNT_NICK_SIZE 32
#define ACCOUNT_PSWD_SIZE 65
#define ACCOUNT_MAX_COUNT 50
#define ACCOUNT_MIN_PSWD_LEN 8

typedef struct
{
		int  id;
    char nick[ACCOUNT_NICK_SIZE];
    char pswd[ACCOUNT_PSWD_SIZE];
		int wonGames; // nb de parties gagnées
		int lostGames; // nb de parties perdues

} Account;

// compte par défaut quand personne n'est connecté
Account* guest_account();

// création d'un compte
int account_create(const char* nick, const char* pswd, char* outputMessage);

// supression d'un compte
int account_delete(int id, char* outputMessage);

// connexion à un compte
int account_login(Account* loggedAccount, const char* nick, const char* pswd, char* outputMessage);

// ajoute une victoire/défaite à un compte (won==1 pour une victoire)
void add_won_lost(Account* loggedAccount, int won);

#endif
