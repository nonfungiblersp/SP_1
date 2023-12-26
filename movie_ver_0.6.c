#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct moviedetails
{
	char name[25];
	char phone[15];
	int seat;
	int id;
};



int changeprize(int);
void reservation(int *,int,int );
int choice1(void);
void cancel(int *);        
void ticket1(int choice,char name[10],int id2,int price);
void ticket2(int choice,char name[10],int id2,int price);
void ticket3(int choice,char name[10],int id2,int price);
int cmovie(void);
int movie(void);
void details(void);


struct moviedetails person[300];
int count=0;
int id2=1000;

int checkLogin(char username[], char password[]);
int main() 
{
	int **seat,choice,price=500,slection,i;
	seat=(int **)calloc(101,sizeof(int *));
	for (i=0;i<3;i++)
		*(seat+i)=(int *)calloc(101,sizeof(int ));
	int x,y,z;
	

    char username[50];
    char password[50];

    // Get username and password from the user
    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    // Check login credentials
    if (checkLogin(username, password))
	{
        // Clear the console or terminal
        system("cls || clear");

        // Continue with the rest of your program
        printf("Login successful!\n");
	while(x!=3)
	{
		choice=useradmin_menu();
		switch(choice)
		{
			case 1:
				while(y!=5)
				{
					choice=admin();
					switch(choice)
					{
						case 1:
							price=changeprize(price);
						break;
						case 2:
							details();
						break;	
						case 3:	
							slection=movie();
							reservation(seat[slection-1],price,slection);	
							count++;
						break;
						case 4:
							slection=cmovie();	
							cancel(seat[slection-1]);	
						break;
						case 5:
							y=5;
						break;
						default: 
							printf("Choice not available\n");
						break;	
					}
				}
				break;
			case 2:
				while(z!=3)
				{
					choice=user();
					switch(choice)
					{	
						case 1:	
							slection=movie();
							reservation(seat[slection-1],price,slection);	
							count++;
							break;
						case 2:
							slection=cmovie();	
							cancel(seat[slection-1]);	
						break;
						case 3:
							z=3;
						break;
						default: 
							printf("Choice not available\n");
						break;	
					}
				}
				break;	
			case 3:
				x=3;
				break;
			default: 
				printf("Choice not available\n");
				break;	
		}
	}

    }
	else
	{
        printf("Login failed. Exiting program.\n");
    }

    return 0;
}


// Function to check login credentials
int checkLogin(char username[], char password[]) 
{
    // Replace this with your actual login logic
    // For simplicity, I'm using hardcoded values
    if (strcmp(username, "admin") == 0 && strcmp(password, "sai@123") == 0)
	{
        return 1;  // Login successful
    }
	else
	{
        return 0;  // Login failed
    }
}



int admin(void)
{
	int choice;
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             1- To edit price of ticket                         ||\n");
	printf("\t\t\t\t||             2- To view reserved tickets                        ||\n");
	printf("\t\t\t\t||             3- To puchase ticket:                              ||\n");
	printf("\t\t\t\t||             4- To cancel the seat:                             ||\n");
	printf("\t\t\t\t||             5- Exit system:                                    ||\n");
	printf("\t\t\t\t||================================================================||\n");
	printf("\t\t\t\t  Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}


int user(void)
{
	int choice;
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             1- To puchase ticket:                              ||\n");
	printf("\t\t\t\t||             2- To cancel the seat:                             ||\n");
	printf("\t\t\t\t||             3- Exit system:                                    ||\n");
	printf("\t\t\t\t||================================================================||\n");
	printf("\t\t\t\t  Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}


int useradmin_menu(void)
{
	int choice;
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             1- Admin:                                          ||\n");
	printf("\t\t\t\t||             2- Customer:                                       ||\n");
	printf("\t\t\t\t||             3- Exit system:                                    ||\n");
	printf("\t\t\t\t||================================================================||\n");
	printf("\t\t\t\t  Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}


void cancel(int *array)
{
      int Cseat,i,stop;
	  printf("Please enter ID number of ticket: ");
	  scanf("%d",&Cseat);
	  for (i=0;i<300;i++)
	  {
	  		if(Cseat==person[i].id)
	  		{
					 stop=5;
					 system("cls");
					 printf("%s your seat is %d cancelled",person[i].name,person[i].seat);
					 array[person[i].seat]=0;
					 i=300;
	  		}
	  }
	  if (stop!=5)	
	  		printf("Ticket ID number is incorrect please enter right one to cancel ticket: \n");
}
void ticket1(int choice,char name[10],int id2,int price)
{
		system("cls");
		printf("\n\n");
        printf("\t\t\t-----------------\"TICKET\"----------------\n");
        printf("\t|*|======================================================================|*|\n");
        printf("\t|*| Booking ID : %d        			      Show Name : Jawan  |*|\n",id2);
        printf("\t|*| Customer  : %s   \n",name);
        printf("\t|*|                             	              Date: 29-12-2023   |*|\n");
        printf("\t|*|                                                  Time : 08:00pm      |*|\n");
        printf("\t|*|                                                  Hall : 02           |*|\n");
        printf("\t|*|                                             seats No. : %d        \n",choice);
        printf("\t|*|                                               price . : %d      \n",price);
        printf("\t|*|======================================================================|*|\n\n");
        person[count].id=id2;
		return;
}
void details(void)
{
	int i;
	char pass[10],pak[10]="pass";
	printf("Enter the password to see details: ");
	scanf("%s",&pass);
	if (strcmp(pass,pak)==0)
	{
		for (i=0;i<count;i++)
		{
			printf("seat no: %d is booked by %s booking id is %d\n",person[i].seat,person[i].name,person[i].id);
		}
	}
	else                                                 
		printf("Entered password is wrong \n");
		system("PAUSE");
		system("CLS");
	
}             
int movie(void)
{
	int i;
	system("cls");
	printf("\t\t\twhich movie you want to see?\n");
	printf("\t\t\t----------------------------\n\n");
	printf("\t\t\tpress 1 for Jawan\n\n");
	printf("\t\t\tpress 2 for Animal \n\n");
	printf("\t\t\tpress 3 for Gadar-2\n");
	scanf("%d",&i);
	system("cls");
	return i;
}
void ticket2(int choice,char name[10],int id2,int price)
{
		system("cls");
		printf("\n\n");
        printf("\t\t\t-----------------\''TICKET\''----------------\n");
        printf("\t|*|=====================================================================|*|\n");
        printf("\t|*| Booking ID : %d \t Show Name : Animal                             |*|\n",id2);
        printf("\t|*| Customer  : %s    \n",name);
        printf("\t|*|\t                                             Date : 19-12-2023  |*|\n");
        printf("\t|*|                                                     Time  : 09:00pm |*|\n");
        printf("\t|*|                                                            Hall : 03|*|\n");
        printf("\t|*|                                                      seats No. : %d  |*|\n",choice);
        printf("\t|*|                                                       price :  %d  |*|\n",price);
        printf("\t|*|=====================================================================|*|\n\n\n");
        person[count].id=id2;
        return;
}

int cmovie(void)
{
	int i;
	printf("\t\t\twhich movie ticket you want to cancel\n");
	printf("\t\t\t-------------------------------------\n");
	printf("\t\t\tpress 1 for Jawan \n\n");
	printf("\t\t\tpress 2 for Animal \n\n");
	printf("\t\t\tpress 3 for Gadar-2\n");
	scanf("%d",&i);
	return i;		
}

void ticket3(int choice,char name[10],int id2,int price)
{
		system("cls");
		printf("\n\n");
        printf("\t\t\t-----------------\"TICKET\"----------------\n");
        printf("\t|*|====================================================================|*|\n");
        printf("\t|*| Booking ID : %d \t\t\tShow Name : Gadar-2	       |*|\n",id2);
        printf("\t|*| Customer  : %s \n",name);
        printf("\t|*|                                          Date      :19-12-2023     |*|\n");
        printf("\t|*|                                          Time      : 10:00pm       |*|\n");
        printf("\t|*|                                          Hall      : 04            |*|\n");
        printf("\t|*|                                          seats No. : %d             \n",choice);
        printf("\t|*|                                          price . : %d        \n",price);
        printf("\t|*|====================================================================\n\n");
        person[count].id=id2;
        return;
}

int changeprize(int currentPrice) {
    int newPrice;
    printf("Enter the new ticket price: ");
    scanf("%d", &newPrice);
    return newPrice;
}

void reservation(int *array, int price, int selection) {
    int i;
    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &i);

    if (array[i] == 0) {
        array[i] = 1;
        printf("Seat %d booked successfully!\n", i);
        id2++;
        switch (selection) {
            case 1:
                ticket1(i, person[count].name, id2, price);
                break;
            case 2:
                ticket2(i, person[count].name, id2, price);
                break;
            case 3:
                ticket3(i, person[count].name, id2, price);
                break;
            default:
                printf("Invalid movie selection.\n");
                break;
        }
    } else {
        printf("Seat %d is already booked. Please choose another seat.\n", i);
    }
}

