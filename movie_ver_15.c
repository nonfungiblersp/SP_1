#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include <ctype.h>
#include<conio.h>

#define MAX_MOVIES 300
#define MAX_TITLE_LENGTH 100

struct MovieDetails
{
    int id;
    char title[MAX_TITLE_LENGTH];
};


char movies[MAX_MOVIES][50];

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
void readFromFile(const char *filename);


//login function
int adminLogin();

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
void saveToFile(const struct moviedetails *person, int count);

//new update 14_12_2023
void printMovies();
void editMovies();
void readMoviesFromFile();
void storeMoviesToFile();


struct moviedetails person[300];
int count=0;
int id2=1000;

//new functions for the admin

struct book
{
	char code[20];
	char name[20];
	char date[20];
	int cost;


}b;

int seat = 60 ;

void insert_details();//for inserting movie details
void viewAll(); // for view all data
void find(); // for finding data
void book_ticket(); //for booking tickets
void old_record(); //for view old recorrds of users,booked tickets


//for store the booked tickets in the files 
void readFromFile(const char *filename);
void saveToFile(const struct moviedetails *details, int count);
int main()
{


	int **seat,choice,price=500,slection,i;
	seat=(int **)calloc(101,sizeof(int *));

	//it shows the file of the movie
	readMoviesFromFile();

	for (i=0;i<3;i++)
	{
		*(seat+i)=(int *)calloc(101,sizeof(int ));
	}

	int x,y,z;
    int authenticated = 0;


    	printf("\n\n\n\n\n\n\n\n\n\n");
    // ASCII art for a simple header
	printf("\t\t\t||=========================================================================||\n");//set1
	printf("\t\t\t||                                                  			   ||\n");//set2
	printf("\t\t\t||                                                         	           ||\n");//set3
    printf("\t\t\t||                Welcome to Movie Ticket Booking            	           ||\n"); //set4
    printf("\t\t\t||                                                           	           ||\n");//set5
    printf("\t\t\t||                                                                         ||\n");//set6
    printf("\t\t\t|| * Enjoy the convenience of booking your favorite movie tickets online.  ||\n");//set7
    printf("\t\t\t|| * Select your preferred movies, showtimes, and seats in a few clicks!   ||\n");//set8
    printf("\t\t\t||                                                           		   ||\n");//set9
    printf("\t\t\t||                                                           		   ||\n");//set10
    printf("\t\t\t||    ...Press Enter to proceed to the login page...			   ||\n");//set11
    printf("\t\t\t||                                                           	           ||\n");
    printf("\t\t\t||=========================================================================||\n\n\n");
	
	printf("\t\t\t\t\t\t ENTER");
    // Wait for user to press Enter
    while (getchar() != '\n');

    system("cls");// Clear the screen for a clean transition

    // Placeholder for the login page (you can replace this with the actual login logic)
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t        Login Page\n");


    // Admin login loop
    do
	{

        authenticated = adminLogin();

        if (!authenticated)
		{
			system("cls");
			printf("\t\t\t\t   ||===============================================================================||\n");
			printf("\t\t\t\t   ||                                                                               ||\n");
			printf("\t\t\t\t   ||                                                                               ||\n");
            printf("\t\t\t\t   ||                Invalid admin credentials. Please try again.                   ||\n");
            printf("\t\t\t\t   ||                                                                               ||\n");
            printf("\t\t\t\t   ||                                                                               ||\n");
            printf("\t\t\t\t   ||===============================================================================||\n");
        }
    } while (!authenticated);

    printf("                                               Admin login successful!\n");



	system("cls");
	while(x!=3)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
		choice=useradmin_menu();
		switch(choice)
		{
			case 1: //admin panel
				system("cls");
				while(y!=6)
				{
					choice=adminpanel();
					switch(choice)
					{
 		                case 1 :
    		                insert_details();
   		                    break;
		                case 2:
    		                viewAll();
   		                    break;

		                case 3:
    		                find();
   		                    break;

		                case 4:
		                    book_ticket();
		                    break;

		                case 5:
		                    old_record();
		                    break;
						case 6:
							y=6;
						break;
						default:
							printf("Choice not available\n");
						break;
					}
				}
				break;
			case 2: //user panel
				system("cls");
				while(z!=3)
				{
					choice=userpanel();
					switch(choice)
					{
						case 1:
							viewAll(); // to shows which are available
							book_ticket(); //for booking tickets
							//printMovies();
							//slection=movie();
							//reservation(seat[slection-1],price,slection);
							//count++;
							
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
//thank you for using our system

	printf("\n\n\n\n\n\n\n\n\n\n");
    // ASCII art for a simple "Thank You" message
    printf("\t\t\t\t\t\t   ***************************************\n");
    printf("\t\t\t\t\t\t   *              Thank You!             *\n");
    printf("\t\t\t\t\t\t   *    for using Movie Ticket Booking   *\n");
    printf("\t\t\t\t\t\t   *     as your first choice           *\n");
    printf("\t\t\t\t\t\t   *                                     *\n");
    printf("\t\t\t\t\t\t   ***************************************\n\n");
}





void saveToFile(const struct moviedetails *details, int count)
{
    FILE *file = fopen("customer.txt", "a");

    if (file == NULL)
    {
        printf("Error opening/creating file for writing.\n");
        return;
    }

    // Now file is open in append mode, proceed to write data
    fprintf(file, "Booking ID: %d\n", details->id);
    fprintf(file, "Customer Name: %s\n", details->name);
    fprintf(file, "Phone Number: %s\n", details->phone);
    fprintf(file, "Seat Number: %d\n", details->seat);
    fprintf(file, "------------------------\n");

    fclose(file);
}

void readFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("Customer Details:\n");

    char line[100]; // Adjust the buffer size accordingly

    // Read and print each line from the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}






//new login function
int adminLogin()
{
    char username[20];
    char password[20];

    printf("\n\n\n\n \t\t\t\t    Enter admin username:");
    scanf("\t\t\t\t   %19s", username);

    printf("\t\t\t\t    Enter admin password: ");
    scanf("\t\t\t\t   %19s", password);

    FILE *credentialsFile = fopen("credentials.txt", "r");
    if (credentialsFile == NULL)
	{
        printf("Error opening credentials file.\n");
        exit(EXIT_FAILURE);
    }

    char fileUsername[20];
    char filePassword[20];
    int isValid = 0;

    while (fscanf(credentialsFile, "%19s %19s", fileUsername, filePassword) == 2)
	{
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
		{
            isValid = 1;
            break;
        }
    }

    fclose(credentialsFile);

    return isValid;
}




//change price in the movie list
int changeprize(int prize)
{
    char pass[10], pak[10] = "pass";
    printf("Enter the password to change the price of the ticket: ");
    scanf("%s", pass);

    if (strcmp(pass, pak) == 0)
    {
        printf("Please enter the new price: ");
        scanf("%d", &prize);

        // Open the file for writing
        FILE *file = fopen("movieprice.txt", "w");

        // Check if the file was opened successfully
        if (file == NULL)
        {
            printf("Error opening file for writing!\n");
            return prize;
        }

        // Write the new price to the file
        fprintf(file, "%d", prize);

        // Close the file
        fclose(file);

        printf("Price updated successfully!\n");
        system("PAUSE");
        system("CLS");
    }
    else
    {
        printf("The entered password is wrong!\n");
    }

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
		saveToFile(&person[count], count);

}




int adminpanel(void)
{
	int choice;

    /*
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             1. To edit price of ticket                         ||\n");
	printf("\t\t\t\t||             2. To view reserved tickets                        ||\n");
	printf("\t\t\t\t||             3. Exit system                                    ||\n");
	printf("\t\t\t\t||================================================================||\n");

    */
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             [1] Insert Movie                                   ||\n");
	printf("\t\t\t\t||             [2] View All Movie                                 ||\n");
	printf("\t\t\t\t||             [3] Find Movie                                     ||\n");
    printf("\t\t\t\t||             [4] Book Ticket                                    ||\n");
    printf("\t\t\t\t||             [5] View All Transections                          ||\n");
    printf("\t\t\t\t||             [6] Exit system                                    ||\n");
	printf("\t\t\t\t||================================================================||\n");

	printf("\t\t\t\t  Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}


int userpanel(void)
{
	int choice;
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             1. To puchase ticket                              ||\n");
	printf("\t\t\t\t||             2. To cancel the seat                             ||\n");
	printf("\t\t\t\t||             3. Exit system                                    ||\n");
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
	printf("\t\t\t\t||             1. Admin                                          ||\n");
	printf("\t\t\t\t||             2. Customer                                       ||\n");
	printf("\t\t\t\t||             3. Exit system                                    ||\n");
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
	{
		printf("Entered password is wrong \n");
		system("PAUSE");
		system("CLS");
	}
}


 //movie details
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


// Function to store movies in a file
void storeMoviesToFile()
{
	int i;
    FILE *file = fopen("movies.txt", "w");

    if (file == NULL)
	{
        printf("Error opening file for writing.\n");
        return;
    }

    for (i = 0; i < MAX_MOVIES; ++i)
	{
        fprintf(file, "%s\n", movies[i]);
    }

    fclose(file);
}

// Function to read movies from a file
void readMoviesFromFile()
{
    int i;
    FILE *file = fopen("movies.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    for (i = 0; i < MAX_MOVIES; ++i)
    {
        if (fscanf(file, "%99[^\n]", movies[i]) != 1)
        {
            // Handle reading error
            break;
        }
        fgetc(file);  // Consume newline character
    }

    fclose(file);
}





// Function to edit movies
void editMovies()
{
    printf("Enter the index of the movie you want to edit (1 to %d): ", MAX_MOVIES);
    int index;
    scanf("%d", &index);
    getchar();  // Consume newline character

    if (index < 1 || index > MAX_MOVIES)
	{
        printf("Invalid index.\n");
        return;
    }

    printf("Enter the new name for the movie: ");
    fgets(movies[index - 1], sizeof(movies[index - 1]), stdin);

    // Remove newline character from the end
    size_t len = strlen(movies[index - 1]);
    if (len > 0 && movies[index - 1][len - 1] == '\n')
	{
        movies[index - 1][len - 1] = '\0';
    }
}











// Function to print movies
void printMovies()
{
	int i;
    printf("Movies:\n");
    for (i = 0; i < MAX_MOVIES; ++i)
	{
        printf("%d. %s\n", i + 1, movies[i]);
    }
}






//new functions

void insert_details()
{

	FILE *fp;
	struct book b;
	printf("\t\t\t\t\t\tEnetr movie code :- ");
	scanf("%s",b.code);
	printf("\t\t\t\t\t\tEnetr  name :- ");
	scanf("%s",b.name);
	printf("\t\t\t\t\t\tEnetr Release Date:- ");
	scanf("%s",b.date);
	printf("\t\t\t\t\t\tEnetr Ticket Price:- ");
	scanf("%d",&b.cost);

	fp=fopen("data.txt","a");

	if(fp == NULL)
	{
		printf("FIle not Found");
	}
	else
	{
		fprintf(fp,"%s %s %s %d \n",b.code,b.name,b.date,b.cost);
		printf("\t\t\t\t\t\tRecord insert Sucessfull");
	}
		printf("\n");
	fclose(fp);
}
void find() //find details
{
	struct book b;
	FILE *fp;

	char ch[20];
	printf("\t\t\t\t\t\tEnter movie code :");
	scanf("%s",ch);
	//system("clear");
	fp = fopen("data.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{
		while(getc(fp) != EOF)
		{
			fscanf(fp,"%s %s %s %d",b.code,b.name,b.date,&b.cost);
			if(strcmp(b.code,ch) == 0)
			{
				//printf("%s / %s / %s / %d\n",b.code,b.name,b.date,b.cost);
				printf("\n \t\t\t\t\t\tRecord Found\n");
				printf("\n\t\t\t\t\t\t\t\tCode ::%s",b.code);
				printf("\n\t\t\t\t\t\t\t\tmovie name ::%s",b.name);
				printf("\n\t\t\t\t\t\t\t\tmovie date ::%s",b.date);
				printf("\n\t\t\t\t\t\t\t\tprice of ticket ::%d",b.cost);
				break;
			}
		}

	}

	fclose(fp);
}

void viewAll()
{
	char ch;
	FILE *fp;

	fp = fopen("data.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{
		system("cls");
		printf("\n\n\n\n\n\n");
		while( ( ch = fgetc(fp) ) != EOF )
		{
      		printf("%c",ch);
		}

	}
	fclose(fp);
}


//for ticket booking
void book_ticket()
{
 struct book b;
	FILE *fp;

	FILE *ufp;

	int total_seat,mobile,total_amount;
	char name[20];


	char ch; //used in display all movies
	char movie_code[20]; //for searching

	// disply all moives by default for movie code
	fp = fopen("data.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{
		system("clear");
		while( ( ch = fgetc(fp) ) != EOF )
      		printf("%c",ch);
	}
	fclose(fp);

	//display ends
	printf("\t\t\t\t\t\t\n For Book ticket Choise Movie(Enter Movie Code First Latter Of Movie)\n");
	printf("\t\t\t\t\t\t\n Enter movie code :");
	scanf("%s",movie_code);
	//system("clear");
	fp = fopen("data.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{
		while(getc(fp) != EOF)
		{
			fscanf(fp,"%s %s %s %d",b.code,b.name,b.date,&b.cost);
			if(strcmp(b.code,movie_code) == 0)
			{
				//printf("%s / %s / %s / %d\n",b.code,b.name,b.date,b.cost);
				printf("Record Found\n");
				printf(" Code ::%s",b.code);
				printf(" Movie name ::%s",b.name);
				printf(" date name ::%s",b.date);
				printf(" Price of ticket::%d ",b.cost);
				printf("\n");
			}
		}

	}
	printf("\n* \t\t\t\t\t\tFill Deatails  *");
	printf("\n \t\t\t\t\t\tyour name :");
	scanf("%s",name);
	printf("\t\t\t\t\t\t\n mobile number :");
	scanf("%d",&mobile);
	printf("\t\t\t\t\t\t\n Total number of tickets :");
	scanf("%d",&total_seat);


	total_amount = b.cost * total_seat;

	printf("\n \t\t\t\t\t\t** ENJOY MOVIE ***\n");
	printf("\n\t\t\t\t\tname : %s",name);
	printf("\n\t\t\t\t\tmobile Number : %d",mobile);
	printf("\n\t\t\t\t\tmovie name : %s",b.name);
	printf("\n\t\t\t\t\tTotal seats : %d",total_seat);
	printf("\n\t\t\t\t\tcost per ticket : %d",b.cost);
	printf("\n\t\t\t\t\tTotal Amount : %d",total_amount);


	ufp=fopen("oldTransection.txt","a");
	if(ufp == NULL)
	{
		printf("FIle not Found");
	}
	else
	{
		fprintf(ufp,"%s %d %d %d %s %d \n",name,mobile,total_seat,total_amount,b.name,b.cost);
		printf("\n Record insert Sucessfull to the old record file");
	}
		printf("\n");
	fclose(ufp);
	fclose(fp);

}



//for view all user transections
void old_record()
{
	char ch;
	FILE *fp;

	//system("clear");

	fp = fopen("oldTransection.txt","r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);

	}
	else
	{
		system("cls");
		while( ( ch = fgetc(fp) ) != EOF )
        {
            printf("%c",ch);
        }
	}
	fclose(fp);
}

