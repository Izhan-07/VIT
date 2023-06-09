// CRC (Cyclic Redundancy Check)
// 21BCB0007

#include <stdio.h>
#include <string.h>

#define MAX_DATA_LENGTH 28
#define MAX_GEN_POLY_LENGTH 10

char data[MAX_DATA_LENGTH];
char check_value[MAX_DATA_LENGTH];
char gen_poly[MAX_GEN_POLY_LENGTH]; // Generating Polynomial
int data_length, i, j;

void XOR()
{
    for (j = 1; j < strlen(gen_poly); j++)
        check_value[j] = ((check_value[j] == gen_poly[j]) ? '0' : '1');
}

void crc()
{
    for (i = 0; i < strlen(gen_poly); i++)
        check_value[i] = data[i];
    
    do
    {
        if (check_value[0] == '1')
            XOR();

        for (j = 0; j < strlen(gen_poly) - 1; j++)
            check_value[j] = check_value[j + 1];

        check_value[j] = data[i++];
    } while (i <= data_length + strlen(gen_poly) - 1);
}

void receiver()
{
    printf("Enter the data(Receiver side): ");
    scanf("%s", data);
    printf("\n");
    printf("\nData received: %s", data);

    crc();

    for (i = 0; (i < strlen(gen_poly) - 1) && (check_value[i] != '1'); i++);

    if (i < strlen(gen_poly) - 1)
        printf("\nError detected\n\n");
    else
        printf("\nNo error detected\n\n");
}

int main()
{
    printf("\nEnter data(Sender Side): ");
    scanf("%s", data);
    printf("\nEnter the G(P): ");
    scanf("%s", gen_poly);

    data_length = strlen(data);

    for (i = data_length; i < data_length + strlen(gen_poly) - 1; i++)
        data[i] = '0';

    printf("\n");
    printf("\nData padded with n-1 zeros: %s", data);
    printf("\n");

    crc();

    printf("\nCRC or Check value is: %s", check_value);

    for (i = data_length; i < data_length + strlen(gen_poly) - 1; i++)
        data[i] = check_value[i - data_length];

    printf("\n");
    printf("\nFinal data to be sent: %s", data);
    printf("\n\n");

    receiver();

    return 0;
}
