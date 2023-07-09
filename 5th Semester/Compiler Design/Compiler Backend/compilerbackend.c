#include <stdio.h>
#include <string.h>
void main()
{
    char icode[10][30], str[20], opr[10];
    int i = 0;
    printf("\nEnter three address Code:\n");
    do
    {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "$") != 0);
    printf("\nOPCODE,\tSRC\tDEST");
    printf("\n--------------------");
    i = 0;
    do
    {
        strcpy(str, icode[i]);
        switch (str[3])
        {
        case '+':
            strcpy(opr, "Add");
            break;
        case '-':
            strcpy(opr, "Sub");
            break;
        case '*':
            strcpy(opr, "Mul");
            break;
        case '/':
            strcpy(opr, "Div");
            break;
        }

        printf("\nMov\t%c,\tr%d", str[2], i);
        printf("\n\%s\t#%c,\tr%d", opr, str[4], i);
        printf("\nMov\tr%d,\t%c", i, str[0]);
    } while (strcmp(icode[++i], "$") != 0);
}