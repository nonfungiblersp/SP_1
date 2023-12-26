#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include <ctype.h>


struct moviedetails
{
	char name[25];
	char phone[15];
	int seat;
	int id;
};


//new functins for the validation
void getValidName(char *name);
void getValidPhone(char *phone);
int getValidSeat(int *array);


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

int main()
{
	int **seat,choice,price=500,slection,i;
	seat=(int **)calloc(101,sizeof(int *));
	for (i=0;i<3;i++)
		*(seat+i)=(int *)calloc(101,sizeof(int ));
	int x,y,z;
	
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
int changeprize(int prize)
{
	char pass[10],pak[10]="pass";
	printf("Enter the password to change price of ticket: ");
	scanf("%s",&pass);
	if (strcmp(pass,pak)==0)
	{
		printf("Please enter new price: ");
		scanf("%d",&prize);
		system("PAUSE");
		system("CLS");
	}
	else 
		printf("The entered password is wrong! ");
	return prize;
}


// Function to validate and get a valid name input
void getValidName(char *name) 
{
    int i, isValidInput;

    do {
        printf("Please enter your name (up to 19 characters): ");
        isValidInput = 1;

        if (scanf(" %19[^\n]", name) != 1 || getchar() != '\n' || strlen(name) == 0)
		{
            isValidInput = 0;
            printf("Invalid name. Please enter a valid name containing only alphabetic characters.\n");
            // Clear input buffer
            while (getchar() != '\n');
        }
		else
		{
            for (i = 0; name[i] != '\0'; i++)
			{
                if (!isalpha(name[i]))
				{
                    isValidInput = 0;
                    printf("Invalid name. Please enter a valid name containing only alphabetic characters.\n");
                    break;
                }
            }
        }
    } while (!isValidInput);
}
// Function to validate and get a valid phone input
void getValidPhone(char *phone) 
{
	int i;
    do {
        printf("Please enter your phone number (10 digits): ");
        scanf("%10s", phone);
        while (getchar() != '\n'); // Clear input buffer

        int valid = 1;
        for (i = 0; i < 10; ++i)
		{
            if (!isdigit(phone[i]))
			{
                valid = 0;
                break;
            }
        }

        if (strlen(phone) != 10 || !valid)
		{
            printf("Invalid phone number format. Please enter a 10-digit number.\n");
        }
    } while (strlen(phone) != 10);
}

// Function to validate and get a valid seat input
int getValidSeat(int *array) 
{
    int seat;
    char input[100];
    int isValidInput;

    do {
        printf("Which seat number do you want? ");
        isValidInput = 1;

        if (fgets(input, sizeof(input), stdin) == NULL)
		{
            fprintf(stderr, "Error reading input.\n");
            exit(EXIT_FAILURE);
        }

        if (sscanf(input, "%d", &seat) != 1 || seat > 100 || seat < 1 || array[seat] == 1)
		{
            isValidInput = 0;
            printf("Invalid seat number or seat already booked. Please choose another seat.\n");
        }
    } while (!isValidInput);

    return seat;
}
void reservation(int *array, int price, int slection)
{
    int i, j;
    printf("\n                                SCREEN\n\n\n");
    for (i = 1; i <= 100; i++)
	{
        if (array[i] == 0)
            printf("%d\t", i);
        else
            printf("*\t", i);
        if (i % 10 == 0)
            printf("\n\n");
    }

    // Validate and get user inputs
    getValidName(person[count].name);
    getValidPhone(person[count].phone);
    j = getValidSeat(array);

    array[j] = 1; // Mark seat as booked

    person[count].seat = j;

	if (slection==1)
	{
		ticket1(j,person[count].name,id2,price);
	}
	else if (slection==2) 	
	{
		ticket2(j,person[count].name,id2,price);
	}
	else 
	{
		ticket3(j,person[count].name,id2,price);
	}			
	id2++;	
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
