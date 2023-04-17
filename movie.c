#include <stdio.h>
#include <string.h>

int main(){
    //read all data from the file and process it. then stdout: "Processed file XYZ and parsed data for M movies"
    // Processed file movies_sample_1.csv and parsed data for 24 movies

    //display a menus of interactive choices to the user
        //For the interaction choice if the user enters an incorrect integer (i.e., something other than 1 to 4), 
        //print an error message and again present the 4 choices to the user. 

    //1. Show movies released in a specified year

    //2. Show highest rated movie for each year
        //Display the data in the form: YYYY RatingValue MovieTitle
        //waht array structure would be useful for a sorting algorithm?
            //3 arrays to store each type of info independenly?
            //a struct that contain 3type of info?

    //3. Show movies and their year of release for a specific language
        //You should only do an exact match on the language entered by the user
            // E.g., "English" shouldn’t match "english"
        //can assume that the length of the language string entered by the user will be less than 20 character.

    //4. Exit

    return 0;
}