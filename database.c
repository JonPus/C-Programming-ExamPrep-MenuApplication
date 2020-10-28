#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

//Print Menu function

struct ELEMENT *head = NULL;
struct ELEMENT *tail = NULL;
char menuInput = '\0';
char *searchName;

struct ELEMENT *tempPointer = NULL;

char printMenu()
{
    char input;

    printf("Skriv inn ønsket element i databasen. [1 - 5]:\n");
    printf("1. Legg til et element i databasen.\n");
    printf("2. Finn et element i databasen.\n");
    printf("3. Finn antall elementer i databasen.\n");
    printf("4. Slett et element fra databasen.\n");
    printf("5. Avslutte\n");

    input = getchar();

    getchar();

    return input;
}

//Get Input function

char *getInput(char *outputString)
{
    char *userInput = NULL;
    size_t szBuffer = 0;
    int inputCount = 0;

    printf("%s", outputString);
    inputCount = getline(&userInput, &szBuffer, stdin);

    userInput[inputCount - 1] = '\0';
    return userInput;
}

void insertElement()
{
    struct ELEMENT *newElement = NULL;

    newElement = (struct ELEMENT *)malloc(sizeof(struct ELEMENT));

    newElement->elementName = getInput("Input Name: ");
    newElement->next = NULL;

    if (head == NULL)
    {
        newElement->elementNumber = 1;
        newElement->prev = NULL;
        head = newElement;
        tail = head;
    }
    else
    {
        newElement->elementNumber = tail->elementNumber + 1;
        newElement->prev = tail;
        tail->next = newElement;
        tail = tail->next;
    }
}

//Print one Element

void printOneElement(struct ELEMENT *currentPointer)
{
    printf("*** Record: %d ***\n", currentPointer->elementNumber);
    printf("*** Name: %s ***\n\r", currentPointer->elementName);
}

void printAllRecords()
{
    struct ELEMENT *listPointer = NULL;

    if (head == NULL)
    {
        printf("No Elements found\n\r");
    }
    else
    {
        listPointer = head;

        printf("\n\r");

        while (listPointer != NULL)
        {
            printOneElement(listPointer);
            listPointer = listPointer->next;
        }
        printf("\n");
    }
}

struct ELEMENT *searchElement(char *searchName)
{
    struct ELEMENT *listPointer = NULL;
    int temp;

    if (head == NULL)
    {
        printf("Element empty\n\r");
    }
    else
    {
        listPointer = head;

        while (listPointer != NULL)
        {
            if (strcmp(listPointer->elementName, searchName) == 0)
            {
                return listPointer;
            }
            else
            {
                listPointer = listPointer->next;
            }
        }
        printf("Element %s not foind\n\r", searchName);
    }

    return NULL;
}

void deleteOneRecord(struct ELEMENT *listPointer)
{
    if (head == tail)
    {
        head = NULL;
        tail = NULL;
    }
    else if (listPointer == head)
    {
        head = listPointer->next;
        head->prev = NULL;
    }
    else if (listPointer == tail)
    {
        tail = listPointer->prev;
        tail->next = NULL;
    }
    else
    {
        listPointer->next->prev = listPointer->prev;
        listPointer->prev->next = listPointer->next;
    }

    free(listPointer);
}

void cleanupList()
{
    struct ELEMENT *tempPointer = NULL;

    while (head != NULL)
    {
        tempPointer = head;
        head = head->next;
        free(tempPointer);
    }
}

void menuLog()
{
    do
    {
        menuInput = printMenu();

        switch (menuInput)
        {
        case '1':
            printf("Legger til Element\n\r");
            insertElement();
            break;
        case '2':
            printf("Søker etter Element\n\r");
            if (head == NULL)
            {
                printf("Tom liste.\n\r");
            }
            else
            {
                searchName = getInput("Element Navn: ");
                tempPointer = searchElement(searchName);

                if (tempPointer != NULL)
                {
                    printOneElement(tempPointer);
                    tempPointer = NULL;
                }
            }
            break;
        case '3':
            printf("Printer alle element.\n\r");
            printAllRecords();
            break;
        case '4':
            printf("Sletter et element\n\r");

            if (head == NULL)
            {
                printf("Tom liste\n\r");
            }
            else
            {
                searchName = getInput("Slett element navn: ");
                tempPointer = searchElement(searchName);

                if (tempPointer != NULL)
                {
                    deleteOneRecord(tempPointer);
                    tempPointer = NULL;
                }
            }
            break;
        case '5':
            printf("Avslutter. Ha det bra!");
            cleanupList();
            break;
        default:
            printf("ERROR: Invalid Meny Valg\n\r");
            break;
        }
    } while (menuInput != '0' && menuInput != '0');
}