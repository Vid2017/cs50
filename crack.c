#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <cs50.h>

#define _XOPEN_SOURCE
#include <unistd.h>
#include <math.h>

char *crypt(const char *key, const char *salt);
const int CHARS = 52;

/*
printf statements through the code were meant to help me visualize what was happening
*/

void getWord(int n, char* word){
    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    int combinations;
}

/**
 * check out https://stackoverflow.com/questions/10159649/generate-all-letter-combinations
 **/
void inc_str(char* alphabet, char *str, int* word_index){
    int index, carry;
    int max_index = CHARS - 1;
    for(index = strlen(str)-1;index>=0;--index){
        if(word_index[index] == max_index){
            carry = 1;
            word_index[index] = 0;
            str[index] = alphabet[word_index[index]];
        } else {
            carry = 0;
            word_index[index] += 1;
            str[index] = alphabet[word_index[index]];
        }
        if(carry == 0)break;
    }
}



int check_hash(char* hash_given){
    const char* hashed_word = NULL;

    char salt[3];
    salt[0] = hash_given[0];
    salt[1] = hash_given[1];
    salt[2] = 0;

    int i;
    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* word;
    int* word_index;

    int n;
    int ret_val = 1;

    for (n=1; n<=6; n++){
        word=(char*)malloc(sizeof(char)*(n+1));
        word_index = (int *)malloc(sizeof(int)*(n+1));
        memset(word, alphabet[0], n);
        memset(word_index, 0, n);
        word[n]='\0';

        long t=0;
        long max = (long)powl(CHARS,n);
        printf("combination %li %d %d\n", max, n, CHARS);
        do{
            //printf("%s ",word);
            hashed_word = crypt(word, salt);
            if ( strcmp(hashed_word, hash_given) == 0 )
            {
                printf("hash %s can be produced by %s\n", hashed_word, word);
                ret_val = 1;
                return 1;
            }
            inc_str(alphabet, word, word_index);
            t++;
        }while(t < max);
        free(word);
        free(word_index);
    }
    if (ret_val == 1){
        printf("not matched");
    }
    return ret_val;
}

int main (int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char* hash_given = argv[1];
    char* salt = "50\0";
    char* test_word="TF";
    char* test_encrypt = crypt(test_word, salt);
    printf("test encrypt %s ==> %s\n", test_word,test_encrypt);
    printf("Checking hash %s\n", hash_given);
    return check_hash(hash_given);
/*
    const char* hashed_word = NULL;

    const char* hash_given = argv[1];

    char salt[3];
    salt[0] = hash_given[0];
    salt[1] = hash_given[1];

    char word[6];

    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //check a-Z
    for (int x = 0; x < 52; x++)
    {
        word[0] = alphabet[x];

        //printf("%s\n", word);

        hashed_word = crypt(word, salt);

        if ( strcmp(hashed_word, hash_given) == 0 )
        {
            goto PRINT;
        }
    }

    //check aa-ZZ
    for (int x = 0; x < 52; x++)
    {
        word[0] = alphabet[x];

        //printf("%s\n", word);

        hashed_word = crypt(word, salt);

        if ( strcmp(hashed_word, hash_given) == 0 )
        {
            goto PRINT;
        }

        for (int y = 0; y < 52; y++)
        {
            word[1] = alphabet[y];

            //printf("%s\n", word);

            hashed_word = crypt(word, salt);

            if ( strcmp(hashed_word, hash_given) == 0 )
            {
                goto PRINT;
            }
        }
    }

    //check aaa-ZZZ
    for (int x = 0; x < 52; x++)
    {
        word[0] = alphabet[x];

        //printf("%s\n", word);

        hashed_word = crypt(word, salt);

        if ( strcmp(hashed_word, hash_given) == 0 )
        {
            goto PRINT;
        }

        for (int y = 0; y < 52; y++)
        {
            word[1] = alphabet[y];

            //printf("%s\n", word);

            hashed_word = crypt(word, salt);

            if ( strcmp(hashed_word, hash_given) == 0 )
            {
                goto PRINT;
            }

            for (int z = 0; z < 52; z++)
            {
                word[2] = alphabet[z];

                //printf("%s\n", word);

                hashed_word =  crypt(word, salt);

                if ( strcmp(hashed_word, hash_given) == 0 )
                {
                    goto PRINT;
                }
            }
        }
    }

    //check aaaa-ZZZZ
    for (int x = 0; x < 52; x++)
    {
        word[0] = alphabet[x];

        //printf("%s\n", word);

        hashed_word = crypt(word, salt);

        if ( strcmp(hashed_word, hash_given) == 0 )
        {
            goto PRINT;
        }

        for (int y = 0; y < 52; y++)
        {
            word[1] = alphabet[y];

            //printf("%s\n", word);

            hashed_word = crypt(word, salt);

            if ( strcmp(hashed_word, hash_given) == 0 )
            {
                goto PRINT;
            }

            for (int z = 0; z < 52; z++)
            {
                word[2] = alphabet[z];

                //printf("%s\n", word);

                hashed_word =  crypt(word, salt);

                if ( strcmp(hashed_word, hash_given) == 0 )
                {
                    goto PRINT;
                }

                for (int t = 0; t < 52; t++)
                {
                    word[3] = alphabet[t];

                    //printf("%s\n", word);

                    hashed_word =  crypt(word, salt);

                    if ( strcmp(hashed_word, hash_given) == 0 )
                    {
                        goto PRINT;
                    }

                    for (int u = 0; u < 52; u++)
                    {
                        word[4] = alphabet[t];

                        //printf("%s\n", word);

                        hashed_word =  crypt(word, salt);

                        if ( strcmp(hashed_word, hash_given) == 0 )
                        {
                            goto PRINT;
                        }
                    }
                }
            }
        }
    }

    PRINT: printf("%s\n", word);

    return 0;*/
}
