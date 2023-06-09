// VRC
// 21BCB0007
#include <stdio.h>
#include <string.h>

void convertToBinary(char data[], char binaryData[][6], int n) {
    for (int i = 0; i < n; i++) 
    {
        switch (data[i]) {
            case '0':
                strcpy(binaryData[i], "0000");
                break;
            case '1':
                strcpy(binaryData[i], "0001");
                break;
            case '2':
                strcpy(binaryData[i], "0010");
                break;
            case '3':
                strcpy(binaryData[i], "0011");
                break;
            case '4':
                strcpy(binaryData[i], "0100");
                break;
            case '5':
                strcpy(binaryData[i], "0101");
                break;
            case '6':
                strcpy(binaryData[i], "0110");
                break;
            case '7':
                strcpy(binaryData[i], "0111");
                break;
            case '8':
                strcpy(binaryData[i], "1000");
                break;
            case '9':
                strcpy(binaryData[i], "1001");
                break;
            case 'A':
            case 'a':
                strcpy(binaryData[i], "1010");
                break;
            case 'B':
            case 'b':
                strcpy(binaryData[i], "1011");
                break;
            case 'C':
            case 'c':
                strcpy(binaryData[i], "1100");
                break;
            case 'D':
            case 'd':
                strcpy(binaryData[i], "1101");
                break;
            case 'E':
            case 'e':
                strcpy(binaryData[i], "1110");
                break;
            case 'F':
            case 'f':
                strcpy(binaryData[i], "1111");
                break;
            default:
                printf("Invalid character: %c\n", data[i]);
                break;
        }
    }
}

// SenderSide 
void calculateVRC(char binaryData[][6], char vrc[], int n) {
    for (int i=0; i < n; i++) {
        int n1 = strlen(binaryData[i]); // let binarydata[i] = 1011, then n1 len() is 4
        int temp1 = 0;
        for (int j=0; j<n1; j++)
        {
            int temp = binaryData[i][j] - '0'; // To convert into integer
            temp1 = (temp^temp1);
        }
        char temp2 = (char) (temp1 + '0'); 
        vrc[i] = temp2;
    }
}


// ReceiverSide
// Data + VRC 
void dataplusvrc(char binaryData2[][6], char vrc[],int n2)
{
    int n1 = strlen(binaryData2[0]);
    for (int k = 0; k < n2; k++)
    {
        binaryData2[k][n1] = vrc[k];
    }
    
}



int main() {
    //char data[] = "21BCB0007";

    char data[10];
    printf("\n--------------------------------\n");
    printf("Sender Side\n");
    printf("Enter the registration Number:");
    scanf("%s", data);

    int n = strlen(data);
    char binaryData[10][6];
    
    convertToBinary(data, binaryData, n);


    printf("Binary Data:");
    for (int i = 0; i < n; i++)
    {
        printf(" %s ", binaryData[i]);
    }

    char vrc[10] = {0}; 
    calculateVRC(binaryData, vrc, n);
    
    printf("\n Data - parity bit\n");

    for (int i = 0; i < n; i++)
    {
        printf("%s %c\n", binaryData[i], vrc[i]);
    }

    printf("\n--------------------------------\n");

    printf("Receiver Side\n");

    char data2[10]; 
    printf("Enter the registration number(Data to check in receiver side):");
    scanf("%s", data2);

    int n2 = strlen(data2);
    char binaryData2[10][6] = {0};
    convertToBinary(data2, binaryData2, n2);

    dataplusvrc(binaryData2, vrc, n2);
    printf("Data+VRC:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", binaryData2[i]);
    }

    calculateVRC(binaryData2, vrc, n);
    printf("VRC: %s\n", vrc);

    int n1 = strlen(vrc);

    int flag = 1;

    for (int k = 0; k < n1; k++)
    {
        if (vrc[k] == '0')
        {
            flag = 1;
        }
        else
        {
            flag = 0;
            printf("Error Occured");
            break;
        }
    }
    
    if (flag == 1)
    {
        printf("Received, No error");
    }
    printf("\n--------------------------------\n");
    return 0;
}

// by Izhan Ahmed H