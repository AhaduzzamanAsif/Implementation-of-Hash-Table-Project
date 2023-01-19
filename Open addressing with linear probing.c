#include<stdio.h>
#include<stdlib.h>
#define size 10
int arr[size];
int fIndex = 0;
int j = 0;

struct Student{

       char name[100];
       char id[100];
       float cgpa;

};

struct Student s1[10];

int main(){

    builtArray();
    int number;
    while(number!=-1){
        printf("\nPress 1 for insert value in hash table.");
        printf("\nPress 2 for delete value from hash table.");
        printf("\nPress 3 for search value from hash table.");
        printf("\nPress -1 for exit the code.\n");
        scanf("%d",&number);


        switch(number){

            case 1:

                j++;
                struct Student student;

                printf("\nThe information Student number %d: ",j);
                printf("\nPlease enter name : ");
                scanf(" %[^\n]", student.name);
                printf("\nPlease enter id : ");
                scanf(" %[^\n]", student.id);
                printf("\nPlease enter CGPA : ");
                scanf("%f", &student.cgpa);

                int index = hashFunction(student.id);
                fIndex = insert(index,student.id);
                s1[fIndex]= student;
                printf("\n");
                break;

            case 2:

                printf("\nPlease enter id to delete student info : ");
                char id2[100];
                scanf(" %[^\n]", id2);
                deleteIndex(id2);
                printf("\n");
                break;

            case 3:

                printf("\nPlease enter id to find student : ");
                char id1[100];
                scanf(" %[^\n]", id1);
                printInfo(id1);
                printf("\n");
                break;
        }
    }



}


void printInfo(char *id){
       int x = hashFunction(id);
       int f =0;
     for(int l = 0;l<size;l++){
         f++;
        if(strcmp(s1[x].id,id)==0 && arr[x] != -1){
                printf("\nThe information Student number : ");
                printf("\nName : %s",s1[x].name);
                printf("\nID : %s",s1[x].id);
                printf("\nCGPA : %.2f",s1[x].cgpa);
                printf("\n");
                return;
           }
           x++;
     }

     if(f>=size){
        printf("\nStudent is not in the list.\n");
        return;
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
   int index=sum%size;
   return index;
}



void builtArray()
{
    int i;
    for(i = 0; i < size; i++)
        arr[i] = -1;
}

int insert(int value,char *id)
{

    int key = value % size;

    if(arr[key] == -1)
    {
        arr[key] = value;
        printf("\n%s inserted at arr[%d]\n", id,key);
        return key;
    }
    else
    {
        printf("\nCollision : arr[%d] has element already!",key);
        printf("\nTo insert %s\n",id);
        int c =0;
        for(int i = 0;i<size;i++){

                c++;
           int hkey = (value+c) % size;
           if(arr[hkey] == -1)
            {
                arr[hkey] = value;
                printf("%s inserted at arr[%d] and probes is %d\n", id,hkey,c+1);
                return hkey;
        }

        }
        printf("\nArray Size if full.\n");
        return -1;


    }
}

void deleteIndex(char *id){

    int num = hashFunction(id);

    if(arr[num] == -1){
        printf("\nThere is no data for delete.\n");
    }
    else{

        for(int v = 0;v<size;v++){

            if(strcmp(s1[num].id,id)==0){
            printf("\n%s has been deleted.\n",id);
            arr[num] = -1;
         }
         num++;
        }


    }

}
