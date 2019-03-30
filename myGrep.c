#include <stdio.h>
#include "string.h"
#include "wordList.h"
#include <stdlib.h>


/**
 * Removes an occurrence from the beginning of a list.
 * head - A pointer to the current head of a list, NULL if it's empty
 * line - A pointer at which to store the removed line
 * lineNum - A pointer at which to store the removed line number
 * wordNum - A pointer at which to store the removed word number
 *
 * Returns a pointer to the new head of the list, NULL if it's (now) empty.
 */

void printLines(Node *head) {

    char pLine[MAXLINE];
    int pLineNum = 0;
    WordNode *pWordNums;

    while(head)
    {
        head = rmFromHead(head, pLine, &pLineNum, &pWordNums);
        printf("Line %d, word(s)",pLineNum);

        while (pWordNums)
        {
            WordNode *temp = pWordNums;
            printf(" %d,", pWordNums->wordNum);
            pWordNums = pWordNums->next;
            free(temp);
        }
        printf("\b");
        printf(": %s",pLine);
    }
}

int main(int argc, char*argv[])
{
    if (argc != 3)
    {
        printf("myGrep: Improper number of arguments\n"
               "Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }
    else
    {
        FILE *file = NULL;
        file = fopen(argv[2], "r");

        if (file == NULL)
        {
            printf("myGrep: Unable to open file: %s\n", argv[2]);
            return 2;
        }
        else
        {
            char line[MAXLINE];  /* lines of file will be read into line; line will be searched for occurrences */
            char fullLine[MAXLINE];  /* before line is modified, it will be copied to fullLine */
            char *delim = " .,?!;:()\"\n";
            int lineNum = 0;

            int occurrenceCount = 0;

            int longestLineNum = 0;
            char longestLineStr[MAXLINE];

            Node *head = NULL;
            Node *tail = NULL;

            printf("%s %s %s\n",argv[0], argv[1],argv[2]);

            while (fgets(line, MAXLINE, file) != NULL)
            {
                int wordNum = 0;
                int lineCount = strlen(line);
                char *ptr;

                strcpy(fullLine,line);
                ptr = strtok(line, delim);

                if (lineCount > longestLineNum)
                {
                    longestLineNum = lineCount;
                    strcpy(longestLineStr,fullLine);
                }

                while (ptr)
                {
                    if (!strcmp(ptr,argv[1]))
                    {
                        tail = addToTail(tail, fullLine, lineNum, wordNum);

                        if (!head)  /* If the first node of the linked list has been created, it is set as the head*/
                            head = tail;

                        occurrenceCount++;
                    }
                    ptr = strtok(NULL, delim);
                    wordNum++;
                }
                lineNum++;
            }

            printf("Longest line (%d characters): %s",longestLineNum,longestLineStr);
            printf("Number of lines: %d\n",lineNum);
            printf("Total occurrences of \"%s\": %d\n",argv[1],occurrenceCount);
            printLines(head);
            fclose(file);

            return 0;
        }
    }
}

