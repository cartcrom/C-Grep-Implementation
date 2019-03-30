#include <stdio.h>
#include <stdlib.h>
#include "wordList.h"
#include "string.h"

/**
 * Adds a new occurrence to the end of a list.
 * If an occurrence has already been found on this line, the new occurrences wordNum is added the the list of wordNums
 * tail - A pointer to the current tail of a list, NULL if it's empty.
 * line - The line in which the word occurs
 * lineNum - The number of that line within the file
 * wordNum - The position of that word within that line
 *
 *
 * Returns a pointer to the new tail of the list.
 */

Node *addToTail(Node *tail, char *line, int lineNum, int wordNum)
{

    if (!tail || tail->lineNum != lineNum)  /* If there isn't already an occurrence on this line, a new Node is created*/
    {
        Node *newTail = (Node *)malloc(sizeof(Node));
        strcpy(newTail->line, line);
        newTail->lineNum = lineNum;
        newTail->next = NULL;
        newTail->wordHead = (WordNode *)malloc(sizeof(WordNode));
        newTail->wordTail = newTail->wordHead;
        newTail->wordTail->wordNum = wordNum;
        newTail->wordTail->next = NULL;

        if (tail)
            tail->next = newTail;

        return newTail;
    }
    else   /* If this line already contains an occurrence, add wordNum to the current tail's word list */
    {
        WordNode *newWord = (WordNode *)malloc(sizeof(WordNode));
        newWord->wordNum = wordNum;
        newWord->next = NULL;

        tail->wordTail->next = newWord;
        tail->wordTail = newWord;

        return tail;
    }
}

/**
 * Removes an occurrence from the beginning of a list.
 * head - A pointer to the current head of a list, NULL if it's empty
 * line - A pointer at which to store the removed line
 * lineNum - A pointer at which to store the removed line number
 * wordNum - A pointer at which to store the removed word number
 *
 * Returns a pointer to the new head of the list, NULL if it's (now) empty.
 */

Node *rmFromHead(Node *head, char *line, int *lineNum, WordNode **wordNums) {
    Node *next = head->next;

    strcpy(line,head->line);
    *lineNum = head->lineNum;
    *wordNums = head->wordHead;
    head->wordHead = head->wordHead->next;

    free(head);

    if (next == NULL)
        return NULL;

    return next;
}
