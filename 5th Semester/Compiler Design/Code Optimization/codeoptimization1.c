#include <stdio.h>
#include <string.h>

struct Operation
{
    char left;
    char right[20];
} operations[10], optimized_operations[10];

int main()
{
    int a, i, k, j, n, z = 0, m, q;
    char *p, *l;
    char temp, t;
    char *tem;
    
    printf("Enter the number of values: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++)
    {
        printf("Left: ");
        scanf(" %c", &operations[i].left);
        printf("Right: ");
        scanf(" %s", &operations[i].right);
    }
    
    printf("\nIntermediate Code:\n");
    for (i = 0; i < n; i++)
    {
        if (i==n-1)
        {
            printf("%c =: %s\n", operations[i].left, operations[i].right);
        }
        else
        {
            printf("%c = %s\n", operations[i].left, operations[i].right);
        }
        
    }
    
    for (i = 0; i < n - 1; i++)
    {
        temp = operations[i].left;
        
        for (j = 0; j < n; j++)
        {
            p = strchr(operations[j].right, temp);
            
            if (p)
            {
                optimized_operations[z].left = operations[i].left;
                strcpy(optimized_operations[z].right, operations[i].right);
                z++;
            }
        }
    }
    
    optimized_operations[z].left = operations[n - 1].left;
    strcpy(optimized_operations[z].right, operations[n - 1].right);
    z++;
    
    printf("\nAfter Dead Code Elimination:\n");
    for (k = 0; k < z; k++)
    {
        if (k==z-1)
        {
            printf("%c =: %s\n", optimized_operations[k].left, optimized_operations[k].right);
        }
        else
        {
            printf("%c = %s\n", optimized_operations[k].left, optimized_operations[k].right);
        }
    }
    
    for (m = 0; m < z; m++)
    {
        tem = optimized_operations[m].right;
        
        for (j = m + 1; j < z; j++)
        {
            p = strstr(tem, optimized_operations[j].right);
            
            if (p)
            {
                t = optimized_operations[j].left;
                optimized_operations[j].left = optimized_operations[m].left;
                
                for (i = 0; i < z; i++)
                {
                    l = strchr(optimized_operations[i].right, t);
                    
                    if (l)
                    {
                        a = l - optimized_operations[i].right;
                        /*printf("pos: %d\n", a);*/
                        optimized_operations[i].right[a] = optimized_operations[m].left;
                    }
                }
            }
        }
    }
    
    printf("Eliminate Common Expression:\n");
    for (i = 0; i < z; i++)
    {
        if (i==z-1)
        {
            printf("%c =: %s\n", optimized_operations[i].left, optimized_operations[i].right);
        }
        else
        {
            printf("%c = %s\n", optimized_operations[i].left, optimized_operations[i].right);
        }
    }
    
    for (i = 0; i < z; i++)
    {
        for (j = i + 1; j < z; j++)
        {
            q = strcmp(optimized_operations[i].right, optimized_operations[j].right);
            
            if ((optimized_operations[i].left == optimized_operations[j].left) && !q)
            {
                optimized_operations[i].left = '\0';
            }
        }
    }
    
    printf("Optimized Code:\n");
    for (i = 0; i < z; i++)
    {
        if (i==z-1 && optimized_operations[i].left != '\0')
        {
            printf("%c =: %s\n", optimized_operations[i].left, optimized_operations[i].right);
        }
        else if(optimized_operations[i].left != '\0')
        {
            printf("%c = %s\n", optimized_operations[i].left, optimized_operations[i].right);
        }
    }
    
    return 0;
}
