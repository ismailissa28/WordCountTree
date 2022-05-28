#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dicttree.h"

int main( int argc, char **argv ) {

    if (argc <2){ //returns 1 if we dont have enough arguments

        printf("Not enough arguments\n");
        return 1;
    }

    dictnode * root = NULL;

    //FILE *fp = fopen("C:\\Users\\Ismail.Issa\\CLionProjects\\480\\dictionarysource.txt","r");
    //FILE *fp2 = fopen("C:\\Users\\Ismail.Issa\\CLionProjects\\480\\testfile1.txt","r");
    FILE *fp = fopen( argv[1],"r");
    FILE *fp2 = fopen( argv[2],"r");

    char buf[512];
    char buf2[512];
    char c;

    while( fgets(buf, 512, fp) )
    {
        char * token = strtok(buf, "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~"); //use delimiters to extract our words
        dictinsert(&root, token); //insert words into trie
    }
    while( fgets(buf2, 512, fp2) ){

        char * token2 = strtok(buf2, "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~");

        while (token2 != NULL){
            printf("%s",token2); //print word first since we cant process capital letters
            int i=0;
            while (token2[i]){ //sets all letters in our token to lowercase letters to process
                c=token2[i];
                char s = tolower(c);
                token2[i]=s;
                i++;
            }
            searchtree(root, token2); //call searchtree method first to get our endNode value
            searchAll(root); //searchAll returns our count value using the endNode of our token as the root
            printf("\n");

            token2 = strtok(NULL, "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~");
        }
    }
    fclose(fp);
    fclose(fp2); //close files
    return 0;
}
