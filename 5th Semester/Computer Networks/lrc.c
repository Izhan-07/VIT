// LRC
// 21BCB0007
#include <stdio.h>
#include <string.h>

void convertToBinary(char data[], char binaryData[][5], int n) {
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
void calculateLRC(char binaryData[][5], char lrc[], int n) {
    
    for (int i=0; i < n; i++) {
        for (int j=0; j<4; j++)
        {
            int temp = binaryData[i][j] - '0'; // To convert into integer
            int temp1 = lrc[j] - '0'; // To convert into integer
            char temp2 = (char)(temp^temp1 + '0');
            lrc[j] = temp2;
        }
    }
}

// ReceiverSide (lrc2 = calculated_lrc + lrc)
void Receiver_check(char binaryData2[][5], char lrc[], char lrc2[],int n2) {
    
    for (int i=0; i < n2; i++) {
        for (int j=0; j<4; j++)
        {
            int temp = binaryData2[i][j] - '0'; // To convert into integer
            int temp1 = lrc2[j] - '0'; // To convert into integer
            char temp2 = (char)(temp^temp1 + '0'); // XOR Operation
            lrc2[j] = temp2;
        }
    }


    // lrc2 + lrc should be zero
    for (int k = 0; k < 4; k++)
    {
        int temp = lrc[k] - '0'; // To convert into integer
        int temp1 = lrc2[k] - '0'; // To convert into integer
        char temp2 = (char)(temp^temp1 + '0'); // XOR Operation
        lrc2[k] = temp2;
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
    char binaryData[10][5];
    
    convertToBinary(data, binaryData, n);


    printf("Binary Data:");
    for (int i = 0; i < n; i++)
    {
        printf(" %s ", binaryData[i]);
    }

    char lrc[5] = "0000"; // let lrc be 0000
    calculateLRC(binaryData, lrc, n);
    
    printf("\nCalculated LRC: %s\n", lrc);

    printf("\n--------------------------------\n");

    printf("Receiver Side\n");

    char data2[10]; 
    printf("Enter the registration number(Data to check in receiver side):");
    scanf("%s", data2);

    int n2 = strlen(data2);
    char binaryData2[10][5];
    convertToBinary(data2, binaryData2, n2);

    char lrc2[5] = "0000";
    Receiver_check(binaryData2, lrc, lrc2, n2);
    printf("Data + LRC: %s\n", lrc2);

    int flag = 1;

    for (int k = 0; k < 4; k++)
    {
        if (lrc2[k] == '0')
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
