#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIE_NAME_LENGTH 100

void addMovieToFile(const char *filename, const char *movieName);
void displayMovieList(const char *filename);
void deleteMovieFromFile(const char *filename, const char *movieName);
void accessMovieFromFile(const char *filename, const char *movieName);
void updateMovieInFile(const char *filename, const char *oldMovieName, const char *newMovieName);
void clearMovieList(const char *filename);

void adminMenu(const char *filename);

int main()
{
    char newMovieName[MAX_MOVIE_NAME_LENGTH];
    char movieName[MAX_MOVIE_NAME_LENGTH];
    const char *filename = "movielist.txt";

    int choice;
    while (choice)
    {
        printf("\nAdmin Menu:\n");
        printf("1. Display Movie List\n");
        printf("2. Delete Movie\n");
        printf("3. Access Movie\n");
        printf("4. Update Movie\n");
        printf("5. Clear Movie List\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMovieList(filename);
            break;
        case 2:
            printf("Enter the movie name to delete: ");
            scanf(" %[^\n]", movieName);
            deleteMovieFromFile(filename, movieName);
            displayMovieList(filename);
            break;
        case 3:
            printf("Enter the movie name to access: ");
            scanf(" %[^\n]", movieName);
            accessMovieFromFile(filename, movieName);
            break;
        case 4:
            printf("Enter the old movie name to update: ");
            scanf(" %[^\n]", movieName);
            printf("Enter the new movie name: ");
            scanf(" %[^\n]", newMovieName);
            updateMovieInFile(filename, movieName, newMovieName);
            displayMovieList(filename);
            break;
        case 5:
            clearMovieList(filename);
            printf("Movie list cleared.\n");
            break;
        case 6:
            return 0;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    return 0;
}

void addMovieToFile(const char *filename, const char *movieName) {
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", movieName);
    fclose(file);
}

void displayMovieList(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    printf("\nList of Movies:\n");

    char movieName[MAX_MOVIE_NAME_LENGTH];

    while (fgets(movieName, sizeof(movieName), file) != NULL) {
        printf("- %s", movieName);
    }

    fclose(file);
}

void deleteMovieFromFile(const char *filename, const char *movieName) {
    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    // Open a temporary file in write mode
    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("Error opening the temporary file");
        exit(EXIT_FAILURE);
    }

    char currentMovie[MAX_MOVIE_NAME_LENGTH];

    // Read each line from the original file and write to the temporary file, excluding the movie to delete
    while (fgets(currentMovie, sizeof(currentMovie), file) != NULL) {
        if (strcmp(currentMovie, movieName) != 0) {
            fprintf(tempFile, "%s", currentMovie);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    remove(filename);
    rename("temp.txt", filename);
}

void accessMovieFromFile(const char *filename, const char *movieName) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    char currentMovie[MAX_MOVIE_NAME_LENGTH];
    int found = 0;

    // Search for the specified movie in the file
    while (fgets(currentMovie, sizeof(currentMovie), file) != NULL) {
        if (strcmp(currentMovie, movieName) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("Movie '%s' found in the list.\n", movieName);
    } else {
        printf("Movie '%s' not found in the list.\n", movieName);
    }
}

void updateMovieInFile(const char *filename, const char *oldMovieName, const char *newMovieName) {
    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    // Open a temporary file in write mode
    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("Error opening the temporary file");
        exit(EXIT_FAILURE);
    }

    char currentMovie[MAX_MOVIE_NAME_LENGTH];

    // Read each line from the original file and write to the temporary file
    while (fgets(currentMovie, sizeof(currentMovie), file) != NULL) {
        if (strcmp(currentMovie, oldMovieName) == 0) {
            fprintf(tempFile, "%s\n", newMovieName);
        } else {
            fprintf(tempFile, "%s", currentMovie);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    remove(filename);
    rename("temp.txt", filename);
}

void clearMovieList(const char *filename)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
	{
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

