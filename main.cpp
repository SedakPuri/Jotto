//  Sedak Puri
//  main.cpp
//  Game Project 4
//  Compiler: Xcode
//  Created by Sedak Puri on 7/18/18.
//  Copyright © 2018 Sedak Puri. All rights reserved.

#include "Header.h"
const unsigned int arrSize = 32;
char *dictionary[arrSize] = {"peace", "happy", "spare", "blink", "primp", "rammy", "rainy", "rails", "voxel", "whats", "wipes", "yippy", "spine", "space", "sprat", "scary", "slogs", "sloan", "quite", "quilt", "rasta", "roman", "salsa", "panic", "puppy", "moist", "offer", "mamma", "idiot", "lapin", "house", "fujis"};
bool gameState = true;

int main() {
    //Chosing a random word
    char* chosenWord = randomWord();
   
    //Asking whether to display the word
    char display;
    cout<<"Hello User!\nWould you like to display the Chosen word? (y or n)"<<endl;
    cin>>display;
    if(display == 'y')
        cout<<"Chosen Word: "<<chosenWord<<endl;
    
    //Displaying the vocabulary list
    cout<<"Vocabulary list: {";
    for(int i = 0; i < arrSize; i++){
        cout<<*(dictionary + i)<< ((i == arrSize - 1) ? "}\n":", ");                                          //Conditional operator for formatting (I'm sorry it looks atrocious)
    }
    
    //Dynamic Allocation of memory
    char *response = new char[6];
    if (!response){
        exit (-1);
    }
    
    //Gameloop
    do{
        //Input
        cout<<"\nEnter a 5 letter word!"<<endl;
        cin>>response;
        
        
        //Checking input length
        if (getLength(response) != 5){
            cout<<"Invalid Input User! Try again, enter a 5 letter word!"<<endl;
            continue;
        }
        cout<<"Guess is: "<<response<<endl;
        

        
        //Computing common letters (the character array cl represents the non-repeating letters that match between the guessed and correct word)
        char* cl = commonLetters(response, chosenWord);
        int score = getLength(cl);
        cout<<"Response is: "<<score<<" unique letters matched (Unique letters: "<<(score == 0 ? "No letters matched!" : cl)<<")"<<endl;          //Conditional operator for formatting
        
        
        //Deallocating memory
        delete cl;
    } while(gameState);
    cout<<"\nCongratulations! You've just won! The word was: "<<chosenWord<<endl;
    
    //Deallocating memory
    delete[] response;
    return 0;
}

//Function to return a pointer to a random word
char* randomWord(){
    srand(static_cast<int>(time(nullptr)));
    return *(dictionary + (rand() % arrSize));
}

//Function to get the length of a word
int getLength(char* arr){
    int counter = 0;
    for(char *p = arr; *p; p++){
        counter++;
    }
    return counter;                                                         //Accounting for the additional termination character at the end of a character string
}

//Function to compute how many letters are shared between the guessed word and the chosen (winning word)
char* commonLetters(char* response, char* chosenWord){
    char* sentinel = new char[6];                                           //Allocating space for a sentinel char array! Allocated to worst case!
    if(!sentinel){
        exit(-1);
    }
    
    //Iterating through words and comparing
    int index = 0;
    for(char* i = response; *i; i++){                                       //Iterating through letters in guess
        for(char* j = chosenWord; *j; j++){                                 //Iterating through letters in chosen (winning) word
            if (*i == *j){                                                  //If there is a letter that matches above two conditions...
                //Checking if letter has already been added to sentinel
                bool alreadyExists = false;
                for(char* k = sentinel; *k; k++){
                    if (*j == *k){
                        alreadyExists = true;                               //Case 1: Sentinel already contains letter!
                    }
                }
                if(!alreadyExists){                                         //Case 2: Sentinel doesn't contain letter and we must add it to it
                    *(sentinel + index++) = *j;                                 //Note: You can also use *j here as they are effectively equivalent in this case
                }
            }
        }
    }

    //Testing to see if guess matched chosenword
    for(int i = 0; i < 5; i++){
        if (*(response + i) != *(chosenWord + i))
            return sentinel;
    }

    //Case: Game won and words matched!
    gameState = false;                                                  
    return sentinel;
}
