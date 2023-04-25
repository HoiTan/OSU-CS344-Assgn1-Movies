#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct movie
{
    char movieTitle[51];
    char language[1000];
    int movieYear;
    float movieRate;
    struct movie* pre;
    struct movie* next;
} movie;

void printList(struct movie* n){
    while (n != NULL) {
        printf("n->movieTitle: %s\n", n->movieTitle);
        printf("n->movieYear: %d\n", n->movieYear);
        printf("n->language: %s\n", n->language);
        printf("n->movieRate: %1.1f\n", n->movieRate);

        n = n->next;
    }
}//print all the movie from linked list

void printByYear(struct movie* n, int year){
    int validYear = 0;
    while (n != NULL) {
        if(n->movieYear == year){
            validYear = 1;
            printf("%s\n",n->movieTitle);
        }
        n = n->next;
    }
    if (validYear == 0){
        printf("No movie from the file is released in that year.\n");
    }
}//print the selected movie of the given year
    // Display the names of all the movies released in that year, one on each line
    // If the data doesn't have any movies released in that year, print a message about this.

struct movie* processFile(char *filePath){
    FILE* myDataFile = fopen(filePath, "r"); // Open up the data file
    char fileName[100];//stores user's input file name
    char* readBuffer = NULL; // Will store a line from the file, allocated on heap
    size_t len = 0; // ignored by getline, but required
    int movieCount = 0;
    struct movie* head = (movie*)malloc(sizeof(movie));
   
    //read all data from the file and process it. then stdout: "Processed file XYZ and parsed data for M movies"
    
    if (myDataFile == NULL) { printf("fopen() failed\n"); return -1; } // Error check fopen()
    struct movie* current = head;
    struct movie* pre = NULL;

    while (getline(&readBuffer, &len, myDataFile) != -1) { // Read the file line by line
        if (movieCount > 0) {
            //printf("%s\n", readBuffer); // Display the line
            char* saveptr1;
            char* saveptr2;
            char* tok = strtok_r(readBuffer, ",", &saveptr1); //get movie title
            strcpy(current->movieTitle, tok);//get name

            tok = strtok_r(NULL, ",", &saveptr1);
            current->movieYear = atoi(tok);//get year

            tok = strtok_r(NULL, ",", &saveptr1);
            strcpy(current->language, tok);//get language

            tok = strtok_r(NULL, ",", &saveptr1);
            current->movieRate = atof(tok);

            current->next = (movie*)malloc(sizeof(movie));
            pre = current;
            current = current->next; 
            current->pre = pre;
            memset(readBuffer, '\0', sizeof(readBuffer)); // Clear the reading buffer
        }
        movieCount++;
    };
    movieCount--;
    printf("Processed file %s and parsed data for %d movies\n", filePath, movieCount);
    return head;
}//Return a linked list of movies by parsing data from

int main(int argc, char* argv[]){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./students student_info1.txt\n");
        return EXIT_FAILURE;
    }
    struct movie* head = processFile(argv[1]);
    printList(head);
    //display a menus of interactive choices to the user
    
    char choice_str[10]; //store user's choice input
    int choice = 0;//number the user selected
    while (choice == 0) {
        printf("\n1. Show movies released in a specified year\n"
            "2. Show highest rated movie for each year\n"
            "3. Show movies and their year of release for a specific language\n"
            "4. Exit\n"
            "Select an option from 1-4: ");
        scanf("%s", choice_str);
        choice = atoi(choice_str);
        if (choice < 1 || choice > 4) {
            printf("Error, please input an integer from 1-4. Try again! \n");
            choice = 0;
        }

        
        if (choice == 1){
            char year_str[10];//stores user's input year
            int yearSelected; //stores int version of year_str
            printf("Show movies released in a specified year\n"
                    "please enter the year you want to find:");
            scanf("%s", year_str);
            yearSelected = atoi(year_str);
            printByYear(head, yearSelected);
            choice = 0;
        }//1. Show movies released in a specified year

        else if (choice == 2){
            float Rate[122] = {0}; //store the highest rate of each year
            char* title[122] = {0};//store the title of the highest rate of each year
            struct movie* h = head;
            while (h != NULL) { 
                if (h->movieRate >= Rate[h->movieYear - 1900]) {
                    Rate[h->movieYear - 1900] = h->movieRate;
                    title[h->movieYear - 1900] = h->movieTitle;
                }
                h = h->next;
            };
            int i;
            for (i = 0; i < 122; i++) {
                    if (Rate[i] > 0) {
                        printf("%d %.1f %s\n", (1900 + i), Rate[i], title[i]);
                    }
                }
            choice = 0;
        }//2. Show highest rated movie for each year

        else if (choice == 3){
            char Language[20];// stores user input language
            int langExist = 0;// = 1 if there is a movie have the given language 
            printf("Enter the language for which you want to see movies:");
            scanf("%s", &Language);
            
            struct movie* h = head;
            while (h != NULL) {
                if (h->language != NULL && strlen(h->language) > 0) { // check if h->language is a valid string
                    char *token, *rest;
                    const char delim[] = "[];"; // delimiter characters
                    token = strtok_r(h->language, delim, &rest);
                    
                    while (token != NULL) {
                        if (Language != NULL && token != NULL) { // make sure Language and token are not NULL
                            if (strcmp(Language, token) == 0){
                                printf("%d %s\n", h->movieYear, h->movieTitle);
                                langExist = 1;
                                break; // terminate the inner loop if a match is found
                            }
                        }
                        token = strtok_r(NULL, delim, &rest);
                    }
                }
                h = h->next;
            }
            if(langExist == 0)
                printf("No data about movies released in %s\n", Language);

            choice = 0;
        }//3. Show movies and their year of release for a specific language

        else if (choice == 4){
            printf("Good bye!\n");
            break;
        }//4. Exit
    }


    return 0;
}
