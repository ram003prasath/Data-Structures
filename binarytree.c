#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	char name[20];
	int age;
	struct node *lc;
	struct node *rc; 
};

struct node *root=NULL;

struct node *createnode(char name[],int age)
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	strcpy(newnode->name,name);
	newnode->age=age;
	newnode->lc=NULL;
	newnode->rc=NULL;
	return newnode;
}

struct node *binaryinsert(struct node *root,char name[],int age)
{
	if(root==NULL)
	{
		return createnode(name,age);
	}
	else
	{
		if(root->lc==NULL)
		{
			root->lc=binaryinsert(root->lc,name,age);
		}
		else
		{
			if(root->lc!=NULL && root->rc==NULL)
			{
				root->rc=binaryinsert(root->rc,name,age);
			}
			else
			{
				if(root->lc->lc==NULL || root->lc->rc==NULL)
				{
					root->lc=binaryinsert(root->lc,name,age);
				}
				else
				{
					root->rc=binaryinsert(root->rc,name,age);
				}
			}
		}
	}
	return root;
}

void insert(char name[],int age)
{
	if(root==NULL)
	{
		root=createnode(name,age);
	}
	else
	{
		if(age>17)
		{
			root->lc=binaryinsert(root->lc,name,age);
		}
		else
		{
			root->rc=binaryinsert(root->rc,name,age);
		}
	}
}

void preorder(struct node *root)
{
	if(root==NULL)
		return;
	printf("\nName:%s\tAge:%d",root->name,root->age);
	preorder(root->lc);
	preorder(root->rc);
}

void main()
{
	char name[20];
	int ch,age;
	while(ch!=3)
	{
		printf("\n\t\tMENU\n1. Insert\n2. display\n3. Exit\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nEnter your name: ");
				scanf("%s",name);
				printf("\nEnter your age: ");
				scanf("%d",&age);
				insert(name,age);
				break;
			case 2:
				preorder(root);
				break;
			case 3:
				exit(0);
				break;
			default:
				printf("\nInvalid input");
		}
	}	
}
