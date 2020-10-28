#ifndef _DATABASE_H_
#define _DATABASE_H_

#define OK 0
#define ERROR 1

struct ELEMENT
{
    int elementNumber;
    char *elementName;
    struct ELEMENT *prev;
    struct ELEMENT *next;
};

char printMenu();
char *getInput(char *outputString);
void insertElement();
struct ELEMENT *searchElement(char *searchName);
void printOneElement(struct ELEMENT *currentPointer);
void deleteOneRecord(struct ELEMENT *listPointer);
void printAllRecords();
void cleanupList();
void menuLog();

#endif // _DATABASE_H
