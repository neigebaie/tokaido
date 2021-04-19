#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string.h>
#include <stdio.h>
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
		int score;
} Account;

int account_create(const char* nick, const char* pswd, char* outputMessage);
int account_delete(int id);
int account_login(Account* loggedAccount, const char* nick, const char* pswd, char* outputMessage);

#endif
