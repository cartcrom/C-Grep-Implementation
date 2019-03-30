#define MAXLINE 101        /* The maximum length of a line, plus one. */


/**
 * Represents a node in a linked list of word-number occurrences.
 */

typedef struct WordNode {
    int wordNum;           /* The position of the word within that line */
    struct WordNode *next;     /* The next node in the list, NULL if none */
} WordNode;


/**
 * Represents a node in a linked list of word occurrences.
 * Contains a linked list of WordNodes representing different occurrences on the same line.
 */

typedef struct Node {
    char line[MAXLINE];    /* The line in which the word occurs */
    int lineNum;           /* The number of that line within the file */
    WordNode *wordHead;
    WordNode *wordTail;
    struct Node *next;     /* The next node in the list, NULL if none */
} Node;

Node *addToTail(Node *, char *, int, int);
Node *rmFromHead(Node *, char *, int *, WordNode **);
void printList(Node *);
