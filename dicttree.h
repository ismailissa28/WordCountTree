//
// Created by Ismail.Issa on 1/21/2022.
//

#ifndef INC_480_DICTTREE_H
#define INC_480_DICTTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define num_char 256

int endNode;
int count;

typedef struct dictnode {
    struct dictnode *children[num_char]; //array of dictnode pointers that will act as a lookup table

    bool endOfWord; //flag for our end of word
    struct dictnode *left;
    struct dictnode *right;

} dictnode;

dictnode *createnode(){ //Creates nodes to insert words from our dictionary words into a tree
    dictnode *newnode = malloc(sizeof *newnode); //stores new node

    for (int i=0; i<num_char; i++){ //starts the child nodes as null so we can change later
        newnode->children[i]=NULL;
    }
    newnode->endOfWord = false;
    return newnode;
}

bool dictinsert(dictnode **root, char *signedtext){ //Finds if words doesnt exist in tree and adds the word if its new, double pointer because we need to change root later
    if(*root ==NULL){   //if tree is empty we create a new node and set our root to the new node
        *root = createnode();
    }
    unsigned char *text = (unsigned char *)signedtext; //cast signed text to unsigned text to remove potential negative indexes
    dictnode *tmp = *root;
    int length = strlen(signedtext);

    for(int i=0; i <length; i++){
        if(tmp->children[text[i]]==NULL){ //if the child of our node is null then we create a new node for the child
            tmp->children[text[i]]=createnode();
        }
        tmp = tmp->children[text[i]]; //move through to the passed string to get the word inside our tree
    }

    if(tmp->endOfWord){
        return false;
    } else{
        tmp->endOfWord= true;  //if the word is already in the tree we return true
        return true;
    }
}

bool searchtree(dictnode *root, char *signedtext){  //Searches through our tree structure to find if word exists

    unsigned char *text = (unsigned char *) signedtext;
    int length = strlen(signedtext);

    dictnode * tmp = root;

    for(int i=0;i<length;i++){  //checks if node has children
        if(tmp->children[text[i]]==NULL){ //if at any point node has no children before loop ends then word is not in dictionary
            endNode=0; //If word has no end node then we set end node to 0
            return false;
        }
        tmp = tmp->children[text[i]]; //itterates to next child node until we get end of word
    }
    endNode = tmp;
    return endNode; //returns the location of our endNode
}

void searchAll2(dictnode *node, unsigned char *prefix, int length){

    unsigned char newprefix[length+2];
    memcpy(newprefix, prefix, length);
    newprefix[length+1]= 0;

    if(node->endOfWord){  //Everytime the endOfWord flag is triggered we increment our count by 1
        count++;
    }
    for (int i=0;i < num_char; i++){  //Loops through tree starting from our endNode of our desired word
        if(node->children[i] != NULL){
            newprefix[length]=i;
            searchAll2(node->children[i], newprefix, length+1); //Starts the loop again until node has no children
        }
    }
}

void searchAll(dictnode *root ){
    count=0; //Set count to 0 so that the count doesn't just keep adding the values
    if(endNode==0){  //from our search tree function if word is not in tree, then we set node to 0 and we print our count
        printf(" %d", count);
        return;
    }
    searchAll2(endNode, NULL, 0);  //calls searchAll2 method using the endNode value returned from the searchtree function
    printf(" %d", count);

}




#endif //INC_480_DICTTREE_H
