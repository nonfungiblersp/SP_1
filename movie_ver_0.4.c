#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define CREDENTIALS_FILE "credentials.txt"

// Structure to store user information
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

// Function prototypes
void registerUser();
int loginUser();
void changePassword();
void displayMenu();


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
int select_movie(void);
void details(void);

struct moviedetails person[300];
int count=0;
int id2=1000;

void updatePrice(const char *filename, const char *movie, float newPrice);
void removeMovie(const char *filename, const char *movie);
void addMovie(const char *filename, const char *movie, float price);
void displayMovies(const char *filename);

int main()
{
	int **seat,choice,slection,i;
	seat=(int **)calloc(101,sizeof(int *));
	for (i=0;i<3;i++)
		*(seat+i)=(int *)calloc(101,sizeof(int ));
	int x,y,z;
	
	
    const char *filename = "movies.txt";
    char movie[50];
    float price;

	//login
	do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    printf("Login successful!\n");
                } else {
                    printf("Login failed. Incorrect username or password.\n");
                }
                break;
            case 3:
                changePassword();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

	
	
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
							slection=select_movie();
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
				
				printf("\nMenu:\n");
        		printf("1. Display Movie List\n");
        		printf("2. To view reserved tickets\n");
        		printf("3. Remove a Movie\n");
        		printf("4. Update Movie Price\n");
        		printf("0. Exit\n");
        		printf("Enter your choice: ");
        		scanf("%d", &choice);
				
				switch (choice)
				{
            		case 1:
                		displayMovies(filename);
                		break;
            		case 2:
                		printf("Enter the movie name: ");
                		scanf("%s", movie);
                		printf("Enter the movie price: ");
                		scanf("%f", &price);
                		addMovie(filename, movie, price);
                		break;

            		case 3:
                		printf("Enter the movie name to remove: ");
                		scanf("%s", movie);
                		removeMovie(filename, movie);
                		break;

            		case 4:
                		printf("Enter the movie name to update price: ");
                		scanf("%s", movie);
                		printf("Enter the new movie price: ");
                		scanf("%f", &price);
                		updatePrice(filename, movie, price);
                		break;
            		case 0:
                		printf("Exiting program.\n");
                		break;
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

void registerUser() {
    struct User newUser;
    printf("Enter a new username: ");
    scanf("%s", newUser.username);

    // Check if the username already exists
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file != NULL) {
        while (fscanf(file, "%s", newUser.username) != EOF) {
            if (strcmp(newUser.username, newUser.username) == 0) {
                fclose(file);
                printf("Username already exists. Please choose a different one.\n");
                return;
            }
        }
        fclose(file);
    }

    printf("Enter a password: ");
    scanf("%s", newUser.password);

    // Save the new user to the credentials file
    file = fopen(CREDENTIALS_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", newUser.username, newUser.password);
        fclose(file);
        printf("User registered successfully!\n");
    } else {
        printf("Error saving user credentials.\n");
    }
}

int loginUser() {
    struct User loginUser;
    printf("Enter your username: ");
    scanf("%s", loginUser.username);

    printf("Enter your password: ");
    scanf("%s", loginUser.password);

    // Check if the username and password match stored credentials
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", loginUser.username, loginUser.password) != EOF) {
            if (strcmp(loginUser.username, loginUser.username) == 0 &&
                strcmp(loginUser.password, loginUser.password) == 0) {
                fclose(file);
                return 1; // Login successful
            }
        }
        fclose(file);
    }

    return 0; // Login failed
}

void changePassword() {
    char username[MAX_USERNAME_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    // Check if the username exists
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (file != NULL) {
        int found = 0;
        while (fscanf(file, "%s %s", username, newPassword) != EOF) {
            if (strcmp(username, username) == 0) {
                found = 1;
                break;
            }
        }
        fclose(file);

        if (!found) {
            printf("Username not found. Password change failed.\n");
            return;
        }
    } else {
        printf("Error accessing user credentials. Password change failed.\n");
        return;
    }

    // Prompt for a new password
    printf("Enter your new password: ");
    scanf("%s", newPassword);

    // Update the password in the credentials file
    file = fopen(CREDENTIALS_FILE, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file != NULL && tempFile != NULL) {
        char currentUsername[MAX_USERNAME_LENGTH];
        char currentPassword[MAX_PASSWORD_LENGTH];

        while (fscanf(file, "%s %s", currentUsername, currentPassword) != EOF) {
            if (strcmp(currentUsername, username) == 0) {
                fprintf(tempFile, "%s %s\n", username, newPassword);
            } else {
                fprintf(tempFile, "%s %s\n", currentUsername, currentPassword);
            }
        }

        fclose(file);
        fclose(tempFile);

        // Replace the original file with the updated one
        remove(CREDENTIALS_FILE);
        rename("temp.txt", CREDENTIALS_FILE);

        printf("Password changed successfully!\n");
    } else {
        printf("Error updating password. Please try again.\n");
    }
}

void displayMenu() {
    printf("\n=== User Authentication System ===\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Change Password\n");
    printf("4. Exit\n");
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
void reservation(int *array,int price,int slection)
{          
		int i,j;
		printf("\n                                SCREEN\n\n\n");
		for (i=1;i<=100;i++)
		{
			if (array[i]==0)
				printf("%d\t",i);
			else 
				printf("*\t",i);	
			if(i%10==0)
				printf("\n\n");
		}
		printf("Please enter your name: ");
		scanf(" %19[^\n]%*[^\n]",&person[count].name);
		printf("Please enter your phone number: ");
		scanf("%u",&person[count].phone);
		printf("Which seat number you want? ");
		scanf("%d",&j);
		if (j>100||j<1)
		{
			printf("seat1 number is unavailable in this theater\n");
			printf("Please re-enter seat number: ");
			scanf("%d",&j);
		}
		if (array[j]==1)
		{
			printf("Sorry, this ticket is already booked! Please choose another seat.\n");
			scanf("%d",&j);
		}
		else			
		{
			array[j]=1;
		}
		
		person[count].seat=j;
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
int select_movie(void)
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


// Function to display the list of movies and prices
void displayMovies(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
	{
        perror("Error opening file");
        return;
    }

    printf("Movie List:\n");
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) 
	{
        printf("%s", line);
    }

    fclose(file);
}

// Function to add a new movie to the list
void addMovie(const char *filename, const char *movie, float price) 
{
    FILE *file = fopen(filename, "a");
    if (file == NULL) 
	{
        perror("Error opening file");
        return;
    }

    fprintf(file, "%s %.2f\n", movie, price);

    fclose(file);
}

// Function to remove a movie from the list
void removeMovie(const char *filename, const char *movie) 
{
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) 
	{
        perror("Error opening file");
        return;
    }

    FILE *outputFile = fopen("temp.txt", "w");
    if (outputFile == NULL) 
	{
        perror("Error opening file");
        fclose(inputFile);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), inputFile) != NULL) 
	{
        if (strstr(line, movie) == NULL) 
		{
            fputs(line, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    remove(filename);
    rename("temp.txt", filename);
}

// Function to update the price of a movie
void updatePrice(const char *filename, const char *movie, float newPrice) 
{
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) 
	{
        perror("Error opening file");
        return;
    }

    FILE *outputFile = fopen("temp.txt", "w");
    if (outputFile == NULL) 
	{
        perror("Error opening file");
        fclose(inputFile);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), inputFile) != NULL) 
	{
        if (	strstr(line, movie) != NULL) 
		{
            fprintf(outputFile, "%s %.2f\n", movie, newPrice);
        }
		else 
		{
            fputs(line, outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    remove(filename);
    rename("temp.txt", filename);
}

