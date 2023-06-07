// 21BCB0007
//Program to calculate Checksum

#include <stdio.h>

long hexToBinary(char hex) {
    long binary = 0;

    switch (hex) {
        case '0':
            binary = 0;
            break;
        case '1':
            binary = 1;
            break;
        case '2':
            binary = 10;
            break;
        case '3':
            binary = 11;
            break;
        case '4':
            binary = 100;
            break;
        case '5':
            binary = 101;
            break;
        case '6':
            binary = 110;
            break;
        case '7':
            binary = 111;
            break;
        case '8':
            binary = 1000;
            break;
        case '9':
            binary = 1001;
            break;
        case 'A':
        case 'a':
            binary = 1010;
            break;
        case 'B':
        case 'b':
            binary = 1011;
            break;
        case 'C':
        case 'c':
            binary = 1100;
            break;
        case 'D':
        case 'd':
            binary = 1101;
            break;
        case 'E':
        case 'e':
            binary = 1110;
            break;
        case 'F':
        case 'f':
            binary = 1111;
            break;
    }

    return binary;
}

long binaryaddition(long binary1, long binary2) {
    int carry = 0;
    long sum = 0;
    int digit1, digit2, currentBit;
    int power = 1;

    while (binary1 != 0 || binary2 != 0) {
        digit1 = binary1 % 10;
        digit2 = binary2 % 10;

        currentBit = (digit1 + digit2 + carry) % 2;
        carry = (digit1 + digit2 + carry) / 2;

        sum = sum + (currentBit * power);
        power *= 10;

        binary1 /= 10;
        binary2 /= 10;
    }

    if (carry != 0) {
        sum = sum + (carry * power);
    }

    return sum;
}

long onesComplement(long num) {
    if (num == 0) {
        return 1;
    }
    
    long complement = 0;
    long power = 1;
    
    while (num > 0) {
        int digit = num % 10;
        digit = (digit == 0) ? 1 : 0;
        complement = complement + digit * power;
        power *= 10;
        num /= 10;
    }
    
    return complement;
}

long sender(long first, long second, long third, long fourth)
{
    long sum1 = binaryaddition(first, second);
    long sum2 = binaryaddition(third, fourth);
    long sum = binaryaddition(sum1, sum2);
    printf("Sum of two binary numbers: %ld\n", sum);


    if (sum >= 10000)
    {
        long firstTwoDigits = sum / 10000;
        long lastFourDigits = sum % 10000;
        long newSum = binaryaddition(firstTwoDigits, lastFourDigits);
        newSum = onesComplement(newSum);
        return newSum;
    }
    else
    {
        return sum;
    }

}

long receiver(long first, long second, long third, long fourth, long sender_sum)
{
    long sum1 = binaryaddition(first, second);
    long sum2 = binaryaddition(third, fourth);
    long sum = binaryaddition(sum1, sum2);
    sum = binaryaddition(sum, sender_sum);
    
    if (sum >= 10000)
    {
        long firstTwoDigits = sum / 10000;
        long lastFourDigits = sum % 10000;
        long newSum = binaryaddition(firstTwoDigits, lastFourDigits);
        newSum = onesComplement(newSum);
        return newSum;
    }
    else
    {
        return sum;
    }
}

int main()
{
    char reg[3];
    printf("Enter the registration number:");
    scanf("%s", reg);
    long first = hexToBinary(reg[0]);
    long second = hexToBinary(reg[1]);
    long third = hexToBinary(reg[2]);
    long fourth = hexToBinary(reg[3]);

    long sender_sum = sender(first, second, third, fourth);

    long receiver_sum = receiver(first, second, third, fourth, sender_sum);
    printf("sender sum: %ld", sender_sum);
    printf("\nreciever sum: %ld", receiver_sum);

    if(receiver_sum == 0)
    {
        printf("\nData received correctly");
    }
    

    return 0;
}


// By Izhan Ahmed H