//welcome page updated
//Thank you page at the end of the code

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
    // Add other details as needed
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

//new update 14_12_2023
void printMovies();
void editMovies();
void readMoviesFromFile();
void storeMoviesToFile();


struct moviedetails person[300];
int count=0;
int id2=1000;



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
	printf("\t\t\t\t   ||===========================================================||\n");
	printf("\t\t\t\t   ||                                                           ||\n");
	printf("\t\t\t\t   ||                                                           ||\n");
    printf("\t\t\t\t   ||                Welcome to Movie Ticket Booking            ||\n");
    printf("\t\t\t\t   ||                                                           ||\n");
    printf("\t\t\t\t   ||                                                           ||\n");
    printf("\t\t\t\t   ||===========================================================||\n\n\n\n\n");
    // Description
    printf("\t\t\t\t   * Enjoy the convenience of booking your favorite movie tickets online.\n");
    printf("\t\t\t\t   * Select your preferred movies, showtimes, and seats with just a few clicks!\n\n\n\n\n");

    // Prompt for user action
    printf("\t\t\t\t         Press Enter to proceed to the login page...");

    // Wait for user to press Enter
    while (getchar() != '\n');

    system("cls");// Clear the screen for a clean transition

    // Placeholder for the login page (you can replace this with the actual login logic)
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t        Login Page\n");
    printf("\n\n\n\n\n\n\n");

    

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
				while(y!=5)
				{
					choice=adminpanel();
					switch(choice)
					{
						case 1: //change ticket price
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
			case 2: //user panel
				system("cls");
				while(z!=3)
				{
					choice=userpanel();
					switch(choice)
					{	
						case 1:
							printMovies();
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
}




int adminpanel(void)
{
	int choice;
	printf("\n\n");
	printf("\t\t\t\t                 \"Movie Ticket Booking\"\n");
	printf(" \t\t\t\t ==================================================================\n");
	printf("\t\t\t\t||             1. To edit price of ticket                         ||\n");
	printf("\t\t\t\t||             2. To view reserved tickets                        ||\n");
	printf("\t\t\t\t||             3. To puchase ticket                              ||\n");
	printf("\t\t\t\t||             4. To cancel the seat                             ||\n");
	printf("\t\t\t\t||             5. Exit system                                    ||\n");
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



//function for the tickets
void ticket1(int choice, char name[10], int id2, int price) {
    system("cls");
    printf("\n\n");
    printf("\t\t\t-----------------\"TICKET\"----------------\n");
    printf("\t|*|======================================================================|*|\n");
    printf("\t|*| Booking ID : %d        			      Show Name : %s  |*|\n", id2, name);
    printf("\t|*| Customer  : %s   \n", name);
    printf("\t|*|                             	              Date: 29-12-2023   |*|\n");
    printf("\t|*|                                                  Time : 08:00pm      |*|\n");
    printf("\t|*|                                                  Hall : 02           |*|\n");
    printf("\t|*|                                             seats No. : %d        \n", choice);
    printf("\t|*|                                               price . : %d      \n", price);
    printf("\t|*|======================================================================|*|\n\n");
    
    // Update data
    person[count].id = id2;

    // Open the file for reading
    FILE *moviesFile = fopen("movieslist.txt", "r");

    // Check if the file opened successfully
    if (moviesFile == NULL) {
        printf("Error opening movieslist.txt file.\n");
        return;
    }

    // Read the first line (assuming one line corresponds to one movie name)
    char movieName[50];
    if (fgets(movieName, sizeof(movieName), moviesFile) != NULL) {
        // Remove the newline character from the movieName
        size_t length = strlen(movieName);
        if (length > 0 && movieName[length - 1] == '\n') {
            movieName[length - 1] = '\0';
        }

        // Set the customer name to the movie name
        strcpy(name, movieName);
    } else {
        printf("Error reading movie name from movieslist.txt.\n");
    }

    // Close the file
    fclose(moviesFile);

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
        if (fscanf(file, "%49[^\n]", movies[i]) != 1)
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
