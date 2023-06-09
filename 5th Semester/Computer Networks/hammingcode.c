// 21BCB0007
// Hamming code
// Give input in reverse order to match with manual calculation (Dependes on how you solved)
// For example my regno is 21BCB0007
// Lets take BC - 1 0 1 1 0 1 1 1 as D12 D11 D10 P8 D7 D6 D5 P4 D3 P2 P1
// give input data as 1 1 1 0 1 1 0 1 

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void input(int *nd, int a[]) {
    printf("Enter Length of Data String: ");
    scanf("%d", nd);

    printf("Enter Data String (bits separated by spaces): ");
    for (int i = 0; i < *nd; i++) {
        scanf("%1d", &a[i]);
    }
}

void calculateHammingCode(int nd, int a[], int maxp, int temp[], int *nh, int *n) {
    int j = 0;
    for (int i = 0; i < nd; i++) {
        for (int k = 0; k < maxp; k++) {
            int t = pow(2, k) - 1;
            if (j == t) {
                temp[j] = 0;
                j++;
            }
        }
        temp[j] = a[i];
        j++;
    }
    *nh = j;
    *n = *nh - nd;
}

void generateParityBits(int temp[], int nh, int n) {
    int sum = 0;
    for (int k = 0; k < n; k++) {
        int t = pow(2, k) - 1;

        for (int i = t; i < nh;) {
            for (int j = 0; j <= t; j++) {
                sum += temp[i];
                i++;
                if (i >= nh)
                    break;
            }

            if (i >= nh)
                break;

            for (int j = 0; j <= t; j++) {
                i++;
                if (i >= nh)
                    break;
            }

            if (i >= nh)
                break;
        }
        temp[t] = sum % 2;
        sum = 0;
        printf("P%d: %d\n", t + 1, temp[t]);
    }
}

void senderSide(int temp[], int nh) {
    printf("\nHamming code: Sender side:   ");
    for (int i = 0; i < nh; i++) {
        printf("%d ", temp[i]);
    }
}

void receiverSide(int temp2[], int nh) {
    printf("\nHamming code: Receiver side(bits separated by spaces): ");
    for (int i = 0; i < nh; i++) {
        scanf("%d", &temp2[i]);
    }
}

void calculateErrorAndCorrect(int temp[], int temp2[], int nh, int n) {
    int b[n];
    int m = n - 1;
    int sum = 0;
    for (int k = 0; k < n; k++) {
        int t = pow(2, k) - 1;

        for (int i = t; i < nh;) {
            for (int j = 0; j <= t; j++) {
                sum += temp2[i];
                i++;
                if (i >= nh)
                    break;
            }

            if (i >= nh)
                break;

            for (int j = 0; j <= t; j++) {
                i++;
                if (i >= nh)
                    break;
            }

            if (i >= nh)
                break;
        }
        b[m] = sum % 2;
        sum = 0;
        printf("P%d: %d\n", t + 1, b[m]);
        m--;
    }

    int pos = 0;
    for (int m = 0; m < n; m++) {
        pos += b[n - m - 1] * pow(2, m);
    }
    printf("Position of Error: %d\n", pos);
    if (temp2[pos - 1] == 0)
        temp2[pos - 1] = 1;
    else
        temp2[pos - 1] = 0;
}

void correctedOutput(int temp2[], int nh) {
    printf("\nHamming code: Receiver side: Error Corrected:  ");
    for (int i = 0; i < nh; i++) {
        printf("%d ", temp2[i]);
    }
}

int main() {
    int maxp = 6;
    int a[50], temp[70], temp2[70];
    int nd, nh, n;

    input(&nd, a);
    printf("-----------------------------------\n", nd);

    calculateHammingCode(nd, a, maxp, temp, &nh, &n);
    printf("Length of Hamming code: %d bits\n", nh);
    printf("Number of Parity Bits: %d \n", n);

    generateParityBits(temp, nh, n);

    senderSide(temp, nh);

    receiverSide(temp2, nh);

    calculateErrorAndCorrect(temp, temp2, nh, n);

    correctedOutput(temp2, nh);

    printf("\n-----------------------------------\n", nd);

    return 0;
}

// By Izhan Ahmed H

// References : https://github.com/jay17ab/Computer-Networks/blob/master/Hamming%20code.c