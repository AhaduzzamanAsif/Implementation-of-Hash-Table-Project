#include<stdio.h>
#include<stdlib.h>
#include <string.h>
struct node{
    int data;
    char id[20];
    char name[50];
    float cgpa;
    int flag;
    struct node *next;
};
struct node *hashList[10];
int main()
{
    createHashTable(hashList);
    int choice;
    while(1)
    {
      printf("\n1. Insert");
       printf("\n2. search");
       printf("\n3. delete");
       printf("\n4. Exit");

       printf("\nEnter your choice: ");
       scanf("%d", &choice);
       fflush(stdin);

       switch (choice){
        case 1: insert(hashList);
                break;
        case 2: search(hashList);
                break;
        case 3: deleteit(hashList);
                break;
        case 4: exit(0);
                break;

       }
    }
}
void createHashTable(struct node *hashList[])
{
    for(int i=0;i<10;i++)
    {
        struct node *temp=(struct node*)malloc(sizeof(struct node));
        temp->data=-1;
        strcpy(temp->id,"null");
        temp->flag=0;
        temp->next=NULL;
        hashList[i]=temp;
    }
}
int hashFunction(char *id)
{
    char temp[20];
    strcpy(temp,id);
    int sum=0;
   char * token = strtok(temp,"-");

   while( token != NULL ){
        sum+=atoi(token);
        token = strtok(NULL,"-");
   }
   int index=sum%10;
   return index;
}
void insert(struct node *hashList[])
{
    char id[20];
    char name[50];
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    printf("Enter ID: ");
    scanf("%[^\n]",id);
    fflush(stdin);
    printf("Name: ");
    scanf("%[^\n]",name);
    fflush(stdin);
    float cgpa;
    printf("CGPA: ");
    scanf("%f",&cgpa);
    strcpy(temp->id,id);
    strcpy(temp->name,name);
    temp->cgpa=cgpa;
    temp->next=NULL;

    int index=hashFunction(temp->id);
    if(hashList[index]->flag==0)
    {
        printf("Information of ID: %s inserted at index %d",temp->id,index);
        hashList[index]=temp;
        hashList[index]->flag=1;
    }
    else
    {
        printf("Collision Occur!\nInformation of ID: %s inserted at index %d",temp->id,index);
        temp->next=hashList[index];
        hashList[index]=temp;
        hashList[index]->flag=2;
    }
}
void search(struct node *hashList[])
{
    char id[20];
    printf("Enter ID to Search:\n");
    scanf("%[^\n]",id);
    fflush(stdin);

    int index=hashFunction(id);
    struct node *curr;
    curr=hashList[index];
    while(strcmp(curr->id,id)!=0&&curr->next!=NULL)
    {
        curr=curr->next;
    }
    if(curr->flag>0&&strcmp(curr->id,id)==0)
    {
        printf("**Student Information**\n");
        printf("Name: %s\n",curr->name);
        printf("ID: %s\n",curr->id);
        printf("CGPA: %f",curr->cgpa);
    }
    else
        printf("Item not found");
}
void deleteit(struct node *hashList[])
{
    char id[20];
    printf("Enter ID to Delete:\n");
    scanf("%[^\n]",id);
    fflush(stdin);

    int index=hashFunction(id);
    struct node *curr=hashList[index];
    if(curr->flag==0){
        printf("Not found");
    }
    else if(strcmp(curr->id,id)==0&&curr->flag==1)
    {
        printf("%s delete successful",hashList[index]->id);
        hashList[index]->data=-1;
        strcpy(hashList[index]->id,"null");
        hashList[index]->flag=0;
        hashList[index]->next=NULL;
    }
    else if(strcmp(curr->id,id)==0)
    {
        printf("%s delete successful",curr->id);
        hashList[index]=hashList[index]->next;
        if(hashList[index]->next==NULL)
        {
            hashList[index]->flag=1;
        }
    }
    else
    {
        int c=0;
        struct node *search=hashList[index];


        while(strcmp(search->id,id)!=0&&search->next!=NULL)
        {
            search=search->next;
        }
        if(search->flag>0&&strcmp(search->id,id)==0)
        {
            c++;
        }
        else
            printf("Item not found");

        if(c==1)
        {
            while(strcmp(curr->next->id,id)!=0&&curr->next!=NULL)
            {
                curr=curr->next;
            }
            if(curr->next->flag>0&&strcmp(curr->next->id,id)==0)
            {
                printf("%s delete successful",curr->next->id);
                curr->next=curr->next->next;
                if(hashList[index]->next==NULL)
                {
                    hashList[index]->flag=1;
                }
            }
        }
    }

}
