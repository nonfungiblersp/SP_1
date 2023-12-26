#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updatePrice(const char *filename, const char *movie, float newPrice);
void removeMovie(const char *filename, const char *movie);
void addMovie(const char *filename, const char *movie, float price);
void displayMovies(const char *filename);

int main() 
{
    const char *filename = "movies.txt";

    int choice;
    char movie[50];
    float price;

    do {
        printf("\nMenu:\n");
        printf("1. Display Movie List\n");
        printf("2. Add a Movie\n");
        printf("3. Remove a Movie\n");
        printf("4. Update Movie Price\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
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

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
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

