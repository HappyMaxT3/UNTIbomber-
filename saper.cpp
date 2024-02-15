#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <thread>
#define max_size 15

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

using namespace std;



int choose_level_func(){
    int button;
    int count_asshole = 100;

    cout << BLUE << "choose difficulty level:" << RESET << endl;
    cout << YELLOW << "   type '1' to easy mode (6*6 field and mines)" << RESET << endl;
    cout << YELLOW << "   type '2' to middle mode (8*8 field and more mines)" << RESET << endl;
    cout << YELLOW << "   type '3' to hard mode (14*14 field and extra mines)" << RESET << endl;

    cin >> button;

    if(button > 3){
        while(count_asshole > 0){
            cout << endl;
            cout << "YOU BROKE MY PROGRAMM, ASSHOLE!" << endl;
            cout << endl;
            count_asshole--;
        }
    }

    return button;
}


int generate_random(int *field_size){

    int min = 0;
    int max = *field_size;
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    srand(seed);
    int random_number = min + (rand() % (max - min + 1));

    return random_number;
}


int find_choices(char field_inside[max_size][max_size], int *field_size){
    int X_count = 0;
    for(int i = 0; i < *field_size; i++){
        for(int j = 0; j < *field_size; j++){
            if(field_inside[i][j] == 'X'){
                X_count++;
            }
        }
    }
    return X_count;
}


void find_mines(char field_for_player[max_size][max_size], int *x, int *y, char field_inside[max_size][max_size], int *field_size){
    int mines_around = 0;

    for(int i = 0; i < *field_size; i++){
        for(int j = 0; j < *field_size; j++){
            if( (*x == i) && (*y == j) ){

                if(field_inside[i][j - 1] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i - 1][j - 1] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i + 1][j - 1] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i - 1][j] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i + 1][j] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i - 1][j + 1] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i][j + 1] == 'B'){
                    mines_around += 1;
                }
                if(field_inside[i + 1][j + 1] == 'B'){
                    mines_around += 1;
                }

                field_for_player[*x][*y] = mines_around + '0';
            }
        }
    }

}


int main(){

    int choose_level, field_size, num_of_mines;
    char field_inside[max_size][max_size], field_for_player[max_size][max_size];

    choose_level = choose_level_func();

    if(choose_level == 1){
        field_size = 6;
        num_of_mines = 21;
    }
    if(choose_level == 2){
        field_size = 8;
        num_of_mines = 65;
    }
    if(choose_level == 3){
        field_size = 14;
        num_of_mines = 100;
    }


    for(int i = 0; i < field_size; i++){
        for(int j = 0; j < field_size; j++){
            field_for_player[i][j] = 'X';
        }
    }
    for(int i = 0; i < field_size; i++){
        for(int j = 0; j < field_size; j++){
            field_inside[i][j] = 'X';
        }
    }

    for(int i = 0; i < num_of_mines; i++){
        int x_c = generate_random(&field_size);
        this_thread::sleep_for(chrono::milliseconds(rand() %134));
        int y_c = generate_random(&field_size);
        
        field_inside[x_c][y_c] = 'B';
        cout << "generation of your field..." << endl;
    }

    // cheater mode ->
    // cout << endl << "cheater-field:" << endl;
    // for(int i = 0; i < field_size; i++){
    //     for(int j = 0; j < field_size; j++){
    //         cout << "[" << field_inside[i][j] << "]";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cheater mode -<

    for(int i = 0; i < field_size; i++){
        for(int j = 0; j < field_size; j++){
            cout << GREEN << "[" << field_for_player[i][j] << "]" << RESET;
        }
        cout << endl;
    }


    int num_of_choices = find_choices(field_inside, &field_size);
    cout << "\nchoices to win: " << num_of_choices << endl;

    int x, y, flag;

    for(; num_of_choices > 0; --num_of_choices ){
        cout << endl;
        cout << "enter coordinats x (num of column from left), y (num of line from up) and 0 or 1 (if you want to make mine-marker type 1, if you didn`t type 0): ";
        cin >> y >> x >> flag;
        x = x - 1;
        y = y - 1;

        if(field_inside[x][y] == 'B' && flag == 0){
            cout << "it`s bomb! you expoded, burned... you aren`t untibomber... you`re just a fool..." << endl;
            for(int i = 0; i < field_size; i++){
                for(int j = 0; j < field_size; j++){
                    cout << RED << "[" << field_inside[i][j] << "]" << RESET;
                }
                cout << endl;
            }
            cout << endl;
            break;
        }

        if(flag == 1){
            field_for_player[x][y] = 'F';
        }else{
            find_mines(field_for_player, &x, &y, field_inside, &field_size);
        }
        
        cout << endl;
        for(int i = 0; i < field_size; i++){
            for(int j = 0; j < field_size; j++){
                cout << GREEN << "[" <<  field_for_player[i][j] << "]" << RESET;
            }
            cout << endl;
        }
        cout << "\nchoices to win: " << num_of_choices << endl;

    }

    if(num_of_choices == 0){
        cout << "my congratulations, you win, untibomber..." << endl;
    }

}
