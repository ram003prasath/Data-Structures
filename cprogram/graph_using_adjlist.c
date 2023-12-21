#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char data[10];
    struct node *adjvert;
    struct node *next;
    int wei;
};

struct node *head = NULL;

struct node *createvertex(char vert[10], int weight)
{
    struct node *newvert = (struct node *)malloc(sizeof(struct node));
    strcpy(newvert->data, vert);
    newvert->adjvert = NULL;
    newvert->next = NULL; 
    newvert->wei = weight;
    return newvert;
}

void addvert(char data[10])
{
    struct node *temp;
    temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->data, data) == 0)
        {
            printf("\nYour vertex is already present in the graph.");
            return;
        }
        temp = temp->next;
    }
    temp = head;
    if (head == NULL)
    {
        head = createvertex(data, 0);
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = createvertex(data, 0);
    }
}

void addedge(char src[10], char des[10], int weight)
{
    int f = 0;
    struct node *temp;
    struct node *ptr;
    struct node *temp1;
    temp1 = head;
    if (head == NULL)
    {
        printf("\nRequired number of vertices is less to perform this operation");
        return;
    }
    else
    {
        while (temp1 != NULL)
        {
            if (strcmp(temp1->data, src) == 0)
            {
                ptr = temp1;

                temp = head;
                while (temp != NULL)
                {
                    if (strcmp(temp->data, des) == 0)
                    {
                        f = 1;
                        break;
                    }
                    temp = temp->next;
                }
                if (f == 1)
                {
                    if (ptr->adjvert == NULL)
                    {
                        ptr->adjvert = createvertex(des, weight);
                    }
                    else
                    {
                        struct node *tempAdj = ptr->adjvert;
                        while (tempAdj->next != NULL)
                        {
                            tempAdj = tempAdj->next;
                        }
                        tempAdj->next = createvertex(des, weight);
                    }
                }
            }
            temp1 = temp1->next;
        }
    }
    if (f == 0)
    {
        printf("\nSource is not found");
    }
}

void display()
{
    struct node *temp, *ptr;
    temp = head;
    if (head == NULL)
    {
        printf("\nNO graph is created yet.");
        return;
    }
    else
    {
        printf("\nDisplaying graph\n\n");
        while (temp != NULL)
        {
            printf("\n%s", temp->data);
            ptr = temp->adjvert;
            while (ptr != NULL)
            {
                printf("-(%d)->%s", ptr->wei, ptr->data);
                ptr = ptr->next;
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int ch, weight;
    char ver[10], src[10], des[10];
    struct node *temp;
    while (1)
    {
        printf("\n\n\tMAIN MENU\n1. Add vertex\n2. Add edge\n3. Display\n4. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\nEnter vertex string: ");
            scanf(" %s", ver);
            addvert(ver);
            break;
        case 2:
            temp = head;
            if (head == NULL)
            {
                printf("\nNo vertices available.");
                break;
            }
            printf("\nAvailable vertices in graph are: ");
            while (temp != NULL)
            {
                printf("%s\t", temp->data);
                temp = temp->next;
            }
            printf("\nEnter source: ");
            scanf(" %s", src);
            printf("\nEnter destination: ");
            scanf(" %s", des);
            printf("\nEnter weight: ");
            scanf("%d", &weight);
            addedge(src, des, weight);
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nEnter valid input");
            break;
        }
    }
    return 0;
}
