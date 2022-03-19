#include <stdio.h>
#include <stdlib.h>
int x,y,check=0;
char again;
struct library
{
    char name[50];
    int id;
    int quantity;
};
insertbook(struct library book[100]);
deletebook(struct library book[100]);
searchbookId(struct library book[100],int searchId,int z);
searchbookName(struct library book[100]);
displaySortedBooks(struct library book[100]);
displayUnSortedBooks(struct library book[100]);
int main()
{
    struct library book[100];
    int z=0,searchId;
    FILE *fp=fopen("library.txt","r");
    int choice;
    do
    {
        x=0;
        fseek(fp,92,SEEK_SET);
        while(!feof(fp))
        {
            fscanf(fp,"%[^\t]s",&book[x].name);
            fscanf(fp,"%d%d",&book[x].id,&book[x].quantity);
            x++;
        }
        printf("1-Insert a book\n");
        printf("2-Delete a book\n");
        printf("3-Search a book by id\n");
        printf("4-Search book by name\n");
        printf("5-Display all books sorted by name\n");
        printf("6-Display all books unsorted\n");
        printf("Please enter your choice\n");
        scanf("%d",&choice);
        if(choice <1 || choice>6)
        {
            do
            {
                printf("Wrong choice you should choose number from 1 to 6\n");
                printf("please enter your choice again\n");
                scanf("%d",&choice);
            }
            while(choice<1||choice>6);
            if(choice>=1&&choice<=6)
            {
                switch (choice)
                {
                case 1:
                    insertbook(book);
                    break;
                case 2:
                    deletebook(book);
                    break;
                case 3:
                    printf("Please enter the id of the book you want to search for\n");
                    scanf("%d",&searchId);
                    searchbookId(book,searchId,z);
                    break;
                case 4:
                    searchbookName(book);
                    break;
                case 5:
                    displaySortedBooks(book);
                    break;
                case 6:
                    displayUnSortedBooks(book);
                    break;
                }
            }
        }
        else
        {
            switch (choice)
            {
            case 1:
                insertbook(book);
                break;
            case 2:
                deletebook(book);
                break;
            case 3:
                printf("Please enter the id of the book you want to search for\n");
                scanf("%d",&searchId);
                searchbookId(book,searchId,z);
                break;
            case 4:
                searchbookName(book);
                break;
            case 5:
                displaySortedBooks(book);
                break;
            case 6:
                displayUnSortedBooks(book);
                break;
            }
        }
        printf("Do you Want to choose from the list again ? (y/n)\n");
        scanf(" %c",&again);
    }
    while(again=='y'||again=='Y');
    fclose(fp);
    return 0;
}

insertbook(struct library book[100])
{
    FILE *fp=fopen("library.txt","r+");
    fseek(fp,0,SEEK_END);
    printf("Please enter the name of the book\n");
    fflush(stdin);
    gets(book[x].name);
    printf("Please enter the id of the book\n");
    scanf("%d",&book[x].id);
    printf("Please enter the quantity of the book\n");
    scanf("%d",&book[x].quantity);
    fprintf(fp,"\n%30s\t%30d\t%30d",book[x].name,book[x].id,book[x].quantity);
    x++;
    fclose(fp);
}

deletebook(struct library book[100])
{
    check=0;
    int searchId,z;
    struct library name;
    printf("Please enter the id of the book you want to delete\n");
    scanf("%d",&searchId);
    int loop;
    for(loop=0; loop<x; loop++)
    {
        if(searchId==book[loop].id)
        {
            FILE *fp=fopen("library.txt","w");
            for(z=0; z<x; z++)
            {
                if(book[z].id==searchId)
                {
                    for(int u=z; u<x; u++)
                    {
                        name=book[u];
                        book[u]=book[u+1];
                        book[u+1]=name;
                    }
                }
            }
            fprintf(fp,"%30s\t%30s\t%30s","Name","Id","Quantity");
            for(z=0; z<x-1; z++)
            {
                fprintf(fp,"%30s\t%30d\t%30d",book[z].name,book[z].id,book[z].quantity);
            }
            fclose(fp);
            check++;
        }
    }
    if(check==0)
    {
        printf("Not found\n");
    }
}


searchbookId(struct library book[100],int searchId,int z)
{
    check=0;
    int noSpace=0;
    if(z<x)
    {
        if(book[z].id==searchId)
        {
            for(noSpace; noSpace<100; noSpace++)
            {
                if(book[z].name[noSpace]==' '||book[z].name[noSpace]=='\n'||book[z].name[noSpace]=='\t')
                {
                }
                else
                {
                    break;
                }
            }
            printf("Name:");
            while(book[z].name[noSpace]!=NULL)
            {
                printf("%c",book[z].name[noSpace]);
                noSpace++;
            }
            printf("\t\tQuantity:%d\n",book[z].quantity);
            check++;
        }
        if(check==1)
        {
        }
        else
        {
            z++;
            searchbookId( book,searchId, z);
        }
    }
    else
    {
        if(check==0)
        {
            printf("Not found\n");
        }
    }
}

searchbookName(struct library book[100])
{
    struct library Nothing[100];
    int loop,loop2,loop3;
    struct library book2[100];
    for(int i=0; i<x; i++)
    {
        for(int y=0; y<x; y++)
        {
            book2[y]=Nothing[0];
        }
    }
    loop2=0;
    loop3=0;
    for(loop=0; loop<x; loop++)
    {
        loop2=0,loop3=0;
        while(book[loop].name[loop2]!=NULL)
        {
            if(book[loop].name[loop2]==' '||book[loop].name[loop2]=='\n')
            {
            }
            else
            {
                book2[loop].name[loop3]=book[loop].name[loop2];
                loop3++;
            }
            loop2++;
        }
    }
    for(loop=0; loop<x; loop++)
    {
        book2[loop].id=book[loop].id;
        book2[loop].quantity=book[loop].quantity;
    }
    struct library temp[100];
    for(loop=0; loop<x; loop++)
    {
        for(loop2=loop+1; loop2<x; loop2++)
        {
            if((strcmp(book2[loop].name,book2[loop2].name))==-1)
            {
            }
            else
            {
                do
                {
                    temp[0]=book2[loop];
                    book2[loop]=book2[loop2];
                    book2[loop2]=temp[0];
                }
                while((strcmp(book2[loop].name,book2[loop2].name))!=-1);
            }
        }
    }
    char array[50],array2[50];
    for(int i=0; i<50; i++)
    {
        array2[i]=0;
    }
    printf("Please enter the name of the book to find it\n");
    fflush(stdin);
    gets(array);
    loop2=0,loop=0;
    while(array[loop]!=NULL)
    {
        if(array[loop]==' '||array[loop]=='\n'||array[loop]=='\t')
        {
        }
        else
        {
            array2[loop2]=array[loop];
            loop2++;
        }
        loop++;
    }
    int low=0, high=x-1, mid,check=0;
    while(low<=high)
    {
        mid=(low+high)/2;
        if((strcmp(array2,book2[mid].name))==0)
        {
            printf("Id:%d\tQuantity:%d",book2[mid].id,book2[mid].quantity);
            check++;
            break;
        }
        else if((strcmp(array2,book2[mid].name))<0)
        {
            high=mid-1;
        }
        else if((strcmp(array2,book2[mid].name))>0)
        {
            low=mid+1;
        }
    }
    if(check==0)
    {
        printf("Not found");
    }
    printf("\n");
}


displaySortedBooks(struct library book[100])
{
    int loop,loop2,loop3;
    struct library book2[100],Nothing[1];
    for(loop=0; loop<x; loop++)
    {
        for(loop2=0; loop2<x; loop2++)
        {
            book2[loop2]=Nothing[0];
        }
    }
    loop2=0;
    loop3=0;
    for(loop=0; loop<x; loop++)
    {
        loop2=0,loop3=0;
        while(book[loop].name[loop2]!=NULL)
        {
            if(book[loop].name[loop2]==' '||book[loop].name[loop2]=='\n')
            {
            }
            else
            {
                book2[loop].name[loop3]=book[loop].name[loop2];
                loop3++;
            }
            loop2++;
        }
    }
    char *p1,*p2;
    int arrange[100],arrange2=0,change;
    for(loop=0; loop<x; loop++)
    {
        p1=book2[loop].name[0];
        arrange[arrange2]=p1;
        arrange2++;
    }
    for(loop=0; loop<arrange2; loop++)
    {
        for(loop2=0; loop2<arrange2; loop2++)
        {
            if(arrange[loop]<arrange[loop2])
            {
                change=arrange[loop];
                arrange[loop]=arrange[loop2];
                arrange[loop2]=change;
            }
        }
    }
    for(loop=0; loop<arrange2; loop++)
    {
        for(loop2=0; loop2<arrange2; loop2++)
        {
            if(arrange[loop]==book2[loop2].name[0])
            {
                printf("%10s\t%10d\t%10d\n",book[loop2].name,book[loop2].id,book[loop2].quantity);
            }
        }
    }
    printf("\n");
}

displayUnSortedBooks(struct library book[100])
{
    int loop;
    for(loop=0; loop<x; loop++)
    {
        printf("%10s\t%10d\t%10d\n",book[loop].name,book[loop].id,book[loop].quantity);
    }
    printf("\n");
}


