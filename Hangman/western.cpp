//  CS Final Project
//  Jessica Giardina and Maddie Eckhart
//  Hangman
//
//  Copyright © 2017 University of Cincinnati. All rights reserved.

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

class hangman{
private:
    
    vector <string> main_list;
    //IMPORT 4 LETTER WORDS
    void import_list() {
        
        string word;
        ifstream in;
        
        in.open("4letterwords.txt");
        if(!in){
            cout << "could not import" << endl;
        }else{
            while(!in.eof()){
                in >> word;
                if(!in.eof()){
                    main_list.push_back(word);
                }
            }
        }
    }
    
    // PICK STARTING WORD
    string random_word(vector <string> list){
        string word;
        
        // picks a truly random location
        srand (time(NULL));
        int loc = rand() % 50;
        
        for(int xx = 0; xx <list.size(); xx++){
            if(xx == loc){
                return list[xx];
            }
        }
        return word;
    }
    
    // CHECK TO SEE IF THE LETTER IS IN THE WORD
    bool check(char guess,string word){
        
        for (int in = 0; in < 4; in++){
            if (word[in] == guess){
                return true;
            }
        }
        return false;
    }
    
    // UPDATE WORD
    string update_word(char guess,string word, string old_string){
        string update = old_string;
        int pos=0;
        
        for (int in = 0; in < 4; in++){
            if (word[in] == guess){
                pos = in;
            }
        }
        
        // checks the position and prints out blanks and the guessed letter
        switch (pos) {
            case 0:
                update[0] = guess;
                break;
            case 1:
                update[1] = guess;
                break;
            case 2:
                update[2] = guess;
                break;
            case 3:
                update[3] = guess;
                break;
            default:
                break;
        }
        return update;
    }
    
public:
    
    // MAIN MENU
    int menu(){
        int num;
        vector <string> main_list;
        string initial_word;
        
        cout << "WELCOME TO HANGMAN!" << endl;
        cout << "ENTER 1 IF YOU WANT TO CONTINUE." << endl;
        cout << "TO QUIT ENTER 0" << endl;
        cin >> num;
        
        switch (num) {
            case 1:
                import_list();
                return 1;
                break;
            case 0:
                cout << "You picked 0" << endl;
                return 0;
            default:
                cout << "please enter 1 or 0." << endl;
                menu();
                break;
        }
        return 0;
    }
    
    
    // PLAY GAME
    int play(){
        vector <char> used_letters;
        char guess = ' ';
        bool present;
        int count = 0;
        string new_word, updated = "____";
        
        // pick the random word
        new_word = random_word(main_list);
        
        do{
            //cout << "secret word: " << new_word << endl;
            cout << "word: " << updated << endl;
            cout << "used letters: ";
            
            // print out the letters already guessed
            for(int i=0; i < used_letters.size(); i++){
                cout << used_letters[i];
                cout << setw(3);
            }
            cout << endl;
            bool used = true;
            
            // loops until they guess a different letter
            while(used == true){
                used = false;
                cout << "Guess a letter!: " << endl;
                cin >> guess;
            
                while (!isalpha(guess)){
                    cout << "Please enter a LETTER: " << endl;
                    cin >> guess;
                }
                // check to see if letter was already guessed
                for(int zz = 0; zz < used_letters.size(); zz++){
                    if (guess == used_letters[zz]){
                        used = true;
                    }
                }
                
                // update letters used
                if(used == false){
                    used_letters.push_back(guess);
                }
                if(used == true){
                    cout << "You already guessed " << guess << ". Please guess a different letter."<< endl;
                }
            }
            
            // check to see if letter is in the word
            present = check(guess, new_word);
            
            if(present == true){
        
                // update the secret word
                updated = update_word(guess, new_word, updated);
            }
            if(present == false){
                cout << "There are no " << guess <<"'s. Please guess again." << endl;
            }
            
            // check to see if they won
            if (updated == new_word){
                cout << "You won! The secret word was " << new_word << endl;
                return 0;
            }
            
            count++;
        }while (count < 10);
        cout << "You lost! The secret word was " << new_word << "!" << endl;
        return 0;
    }
};

int main() {
    int go;
    
    hangman start;
    go = start.menu();
    if(go == 1){
        start.play();
    }
}
