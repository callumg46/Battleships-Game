// Battleships Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

class ships {
public: 
    bool alive = true;
    vector <string> shipCoords;
    int shipHealth;
    string name;
};

string inputFunc(string grid[10][10], ships ship, int Player);
string attCheck(string grid[10][10], vector <string> attacked, string attack, int player);
vector <string> dirFunc(string grid[10][10], ships ship, int size, int player);
int attackFunc(string attack, ships enemyShip, int player);
bool aliveCheck(ships enemyShip, int player);
bool coordCheck(ships ship1, ships ship2, ships ship3, int player);
bool posCheck(ships ship1, ships ship2, ships ship3, int player);
void gridDisplay();
void battleshipDisplay();
void destroyerDisplay();
void missileDisplay();

int main() {

    srand(time(NULL));
    string grid[10][10] = {{"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "I1", "J1"},
                           {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2", "J2"},
                           {"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3", "I3", "J3"},
                           {"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "I4", "J4"},
                           {"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5", "I5", "J5"},
                           {"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6", "I6", "J6"},
                           {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7", "I7", "J7"},
                           {"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8", "I8", "J8"},
                           {"A9", "B9", "C9", "D9", "E9", "F9", "G9", "H9", "I9", "J9"},
                           {"A10", "B10", "C10", "D10", "E10", "F10", "G10", "H10", "I10", "J10"}};
  
    string input;
    string attack;

    vector <string> attackedP1;
    vector <string> attackedP2;

    bool complete = false;
    bool fit = false;
    bool win = false;
    bool positionCheck = false;
    bool firstPosCheck = false;
    bool test = false;

    ships battleshipP1;
    ships destroyer1P1;
    ships destroyer2P1;
    ships battleshipP2;
    ships destroyer1P2;
    ships destroyer2P2;

    battleshipP1.shipHealth = 5;
    destroyer1P1.shipHealth = 4;
    destroyer2P1.shipHealth = 4;
    battleshipP2.shipHealth = 5;
    destroyer1P2.shipHealth = 4;
    destroyer2P2.shipHealth = 4;

    battleshipP1.name = "Battleship";
    battleshipP2.name = "Battleship";
    destroyer1P1.name = "Destroyer1";
    destroyer1P2.name = "Destroyer1";
    destroyer2P1.name = "Destroyer2";
    destroyer2P2.name = "Destroyer2";


    int battleshipSize = 5;
    int destroyerSize = 4;

    int Player1 = 1;
    int Player2 = 2;

    //start game
    
    cout << ".______       ___     .___________..___________. __       _______      _______. __    __   __  .______        _______ \n";
    cout << "|   _  \\      /  \\    |           ||           ||  |     |   ____|    /       ||  |  |  | |  | |   _  \      /       |\n";
    cout << "|  |_)  |    /  ^ \\   `---|  |----``---|  |----`|  |     |  |__      |   (----`|  |__|  | |  | |  |_)  |    |   (----\n";
    cout << "|   _  <    /  /_\\ \\      |  |         |  |     |  |     |   __|      \\  \\     |   __   | |  | |   ___/     \\    \\    \n";
    cout << "|  |_)  |  /  ____  \\     |  |         |  |     |  `----.|  |____ .----)   |   |  |  |  | |  | |  |      .----)   |   \n";
    cout << "|______/  /__/    \\__\\    |__|         |__|     |_______||_______||_______/    |__|  |__| |__| | _|      |_______/   \n";
    
    cout << " \n Please press enter to start \n";
    cin.ignore();

    system("cls");
    // start game

    // Rules

    cout << "This is a single player game where you fight the computer. \n";
    cout << "\n";
    cout << "Each player will get three ships to place on the grid shown below. \n";
    cout << "\n";
    cout << "Of these ships, one is a Battleship that is 5 spaces long. \n";
    cout << "\n";
    battleshipDisplay();
    cout << "The other 2 are Destroyers, which are 4 spaces long. \n";
    cout << "\n";
    destroyerDisplay();
    cout << "To begin, each player will choose a starting coordinate for each ship, and the direction they would like it to face. \n";
    cout << "\n";
    cout << "Make sure all coordinates are CAPITALISED when entred \n";
    cout << "\n";
    cout << "Once all ships have been placed on the grid, you can start to attack the computer by guessing where their ships are on the grid. \n";
    cout << "\n";
    cout << "If all of your opponents ships are sunk, then you win! \n";
    cout << "\n";
    cout << "Press enter to view the grid. \n";

    cin.ignore();

    system("cls");

    cout << "This is the grid you will be playing on. \n";

    gridDisplay();

    cout << "Press enter to continue. \n";

    cin.ignore();
    system("cls");

    //Rules


    // player 1 input
    // The player enters one coordinate and then picks a direction. The rest of their coordinates are then assigned.
    // Multiple checks for the input take place, first it is checked that the input a coordinate that exsists, then it is checked that there are no ships at that position already. This check is ran again once all coordinates have been assigned.

    gridDisplay();
    cout << "Please enter the 1st coordinate for the battleship \n";

    input = inputFunc(grid, battleshipP1, Player1);        // inputFunc takes and checks first coordinate input.
    battleshipP1.shipCoords.push_back(input);

    cout << "What direction do you want the ship to face? 1 for left, 2 for right, 3 for down and 4 for up. \n";

    battleshipP1.shipCoords = dirFunc(grid, battleshipP1, battleshipSize, Player1);   // dirFunc takes that first input, gets a direction from the player and assigns the rest of the coordinates.
    battleshipDisplay();
    cout << "Press enter to continue \n";
    cin.ignore();
    system("cls");

    gridDisplay();
    cout << "Please enter the coordinates for your first destroyer \n";
   
    while (firstPosCheck == false) {                          //once one ship has been placed on the grid, checks are needed for the other two ships so they are not on top of each other. 
        destroyer1P1.shipCoords.clear();
        input = inputFunc(grid, destroyer1P1, Player1);
        destroyer1P1.shipCoords.push_back(input);
        firstPosCheck = coordCheck(destroyer1P1, battleshipP1, destroyer2P1, Player1);   //coordCheck performs this check.

    }

    cout << "What direction do you want the ship to face? 1 for left, 2 for right, 3 for down and 4 for up. \n";

    while (positionCheck == false) {

        destroyer1P1.shipCoords = dirFunc(grid, destroyer1P1, destroyerSize, Player1);
        positionCheck = posCheck(destroyer1P1, battleshipP1, destroyer2P1, Player1);

    }

    destroyerDisplay();
    cout << "Please press enter to continue \n";
    cin.ignore();
    system("cls");

    gridDisplay();
    cout << "Please enter the coordinates for your second destroyer \n";

    firstPosCheck = false;
    while (firstPosCheck == false) {

        destroyer2P1.shipCoords.clear();
        input = inputFunc(grid, destroyer2P1, Player1);
        destroyer2P1.shipCoords.push_back(input);
        firstPosCheck = coordCheck(destroyer2P1, battleshipP1, destroyer1P1, Player1);

    }

    cout << "What direction do you want the ship to face? 1 for left, 2 for right, 3 for down and 4 for up. \n";

    positionCheck = false;
    while (positionCheck == false) {

        destroyer2P1.shipCoords = dirFunc(grid, destroyer2P1, destroyerSize, Player1);
        positionCheck = posCheck(destroyer2P1, battleshipP1, destroyer1P1, Player1);

    }

    destroyerDisplay();
    cout << "Please press enter to continue \n";
    cin.ignore();
    system("cls");

    //user input

    //user2 input

    gridDisplay();
   
    input = inputFunc(grid, battleshipP2, Player2);
    battleshipP2.shipCoords.push_back(input);
    battleshipP2.shipCoords = dirFunc(grid, battleshipP2, battleshipSize, Player2);

    firstPosCheck = false;
    while (firstPosCheck == false) {

        destroyer1P2.shipCoords.clear();
        input = inputFunc(grid, destroyer1P2, Player2);
        destroyer1P2.shipCoords.push_back(input);
        firstPosCheck = coordCheck(destroyer1P2, battleshipP2, destroyer2P2, Player2);

    }

    positionCheck = false;
    while (positionCheck == false) {

        destroyer1P2.shipCoords = dirFunc(grid, destroyer1P2, destroyerSize, Player2);
        positionCheck = posCheck(destroyer1P2, battleshipP2, destroyer2P2, Player2);

    }

    firstPosCheck = false;
    while (firstPosCheck == false) {

        destroyer2P2.shipCoords.clear();
        input = inputFunc(grid, destroyer2P2, Player2);
        destroyer2P2.shipCoords.push_back(input);
        firstPosCheck = coordCheck(destroyer2P2, battleshipP2, destroyer1P2, Player2);

    }

    positionCheck = false;
    while (positionCheck == false) {

        destroyer2P2.shipCoords = dirFunc(grid, destroyer2P2, destroyerSize, Player2);
        positionCheck = posCheck(destroyer2P2, battleshipP2, destroyer1P2, Player2);
    }

    system("cls");

    //loop
    while (battleshipP1.alive == true || destroyer1P1.alive == true || destroyer2P1.alive == true) {       //gameplay loop, while player 1 ships are all alive, keep playing, a check at the end of the loop determines if player 2 ships are still alive or not.

        // player 1 attack
        gridDisplay();
        cout << "Player 1, it's your turn to attack, where will you choose? \n";
        getline(cin, attack);
        attackedP1.push_back(attCheck(grid, attackedP1, attack, Player1));      //this is where the player enters their attack coordinate. This is checked to ensure they have not attacked at that place before.
        missileDisplay();
        cout << "Press enter to see if you hit! \n";
        cin.ignore();
        system("cls");

        if (battleshipP2.alive == true) {

            battleshipP2.shipHealth = attackFunc(attack, battleshipP2, Player1);        //each ship is checked to see if it was hit by the attack.
            battleshipP2.alive = aliveCheck(battleshipP2, Player1);

        }

        if (destroyer1P2.alive == true) {

            destroyer1P2.shipHealth = attackFunc(attack, destroyer1P2, Player1);
            destroyer1P2.alive = aliveCheck(destroyer1P2, Player1);

        }
       
        if (destroyer2P2.alive == true) {

            destroyer2P2.shipHealth = attackFunc(attack, destroyer2P2, Player1);
            destroyer2P2.alive = aliveCheck(destroyer2P2, Player1);

        }

        cout << "\n";
        cout << "Get ready to defend yourself, it's Player 2's turn, good luck! Press enter to continue. \n";
        cin.ignore();
        system("cls");
       
        //player 2 attack
        
        int Index1 = rand() % 9;
        int Index2 = rand() % 9;
        attack = grid[Index1][Index2];
        attackedP2.push_back(attCheck(grid, attackedP2, attack, Player2));
        missileDisplay();
        cout << "Press enter to see if the enemy hit you! \n";
        cin.ignore();
        system("cls");

        if (battleshipP1.alive == true) {

            battleshipP1.shipHealth = attackFunc(attack, battleshipP1, Player2);
            battleshipP1.alive = aliveCheck(battleshipP1, Player2);

        }

        if (destroyer1P1.alive == true) {

            destroyer1P1.shipHealth = attackFunc(attack, destroyer1P1, Player2);
            destroyer1P1.alive = aliveCheck(destroyer1P1, Player2);

        }

        if (destroyer2P1.alive == true) {

            destroyer2P1.shipHealth = attackFunc(attack, destroyer2P1, Player2);
            destroyer2P1.alive = aliveCheck(destroyer2P1, Player2);

        }

        if (battleshipP2.alive == false && destroyer1P2.alive == false && destroyer2P2.alive == false) {

            win = true;
            break;
        }

        cout << "Back to Player 1! Press enter to continue\n";
        cin.ignore();
        system("cls");

    }

    if (win == true) {

        cout << ".______    __           ___      ____    ____  _______ .______          __     ____    __    ____  __  .__   __.      _______. __  \n";
        cout << "|   _ \\  |  |         /   \\   \\  \\  /   / |   ____||   _  \\       /_ |   \\   \  / \\  /   / |  | | \\ |  |     /       ||  | \n";
        cout << "|  |_)  | |  |        /  ^  \\   \\  \\/   /  |  |__   |  |_)  |        | |    \\   \/   \\/   /  |  | |  \\|  |    |   (----`|  | \n";
        cout << "|   ___/  |  |       /  /_\  \\   \\_    _/   |   __|  |      /         | |     \\            /   |  | |  . `  |    \\  \\    |  | \n";
        cout << "|  |      |  `----. /  _____  \\     |  |     |  |____ |  |\\\\----.    | |      \\    /\\   /    |  | |  |\\  | .----)   |   |__| \n";
        cout << "| _|      |_______|/__/     \__\\    |__|     |_______|| _| `._____|    |_|       \\__/  \\_/     |__| |__| \\_| |_______/    (__) \n";
    }

    else {

        cout << ".______    __           ___      ____    ____  _______ .______          ___      ____    __    ____  __  .__   __.      _______. __   \n";
        cout << "|   _ \\  |  |         /   \\   \\  \\  /   / |   ____||   _ \\        |__\\    \\  \\  / \\  /   / |  | | \\ |  |     /       ||  |  \n";
        cout << "|  |_)  | |  |        /  ^  \\   \\  \\/   /  |  |__   |  |_)  |          ) |    \\  \\/   \\/   /  |  | |  \\|  |    |   (----`|  | \n";
        cout << "|   ___/  |  |       /  /_\  \\   \\_    _/   |   __|  |      /          / /      \\            /   |  | |  . `  |     \\ \\    |  | \n";
        cout << "|  |      |  `----. /  _____  \\     |  |     |  |____ |  |\\\\----.    / /_       \\    /\\   /    |  | |  |\\  | .----)   |   |__| \n";
        cout << "| _|      |_______|/__/     \__\\    |__|     |_______|| _| `._____|   |____|       \\__/  \\_/     |__| |__| \\_| |_______/    (__) \n";

    }


}

string inputFunc(string grid[10][10], ships ship, int Player)    //this checks the users initial coordinate input.
{
    bool inputCheck = false;
    while (inputCheck == false) {

        ship.shipCoords.clear();
        string coord;

        if (Player == 1) {

            getline(cin, coord);

        }

        else if (Player == 2) {

            int Index1 = rand() % 9;
            int Index2 = rand() % 9;
            coord = grid[Index1][Index2];

        }

        

        for (int j = 0; j < 10; j++) {

            if (inputCheck == false) {

                for (int k = 0; k < 10; k++) {

                    if (coord == grid[j][k]) {

                        inputCheck = true;
                        ship.shipCoords.push_back(coord);

                    }
                }
            }

            if (inputCheck == true) {

                break;

            }
        }

        if (inputCheck == false && Player == 1) {

            cout << "incorrect input, try again \n";

        }
    }

    return ship.shipCoords[0];
}

vector <string> dirFunc(string grid[10][10], ships ship, int size, int player)    //this takes a direction from the user, checks it is a coordinate that exsists, and assigns the rest of the coordinates to the ship.
{
    bool fit = false;
    bool complete = false;
    bool inputCheck = false;
    string direction;  

    if (ship.shipCoords.size() > 1) {

        ship.shipCoords.erase(ship.shipCoords.begin() + 1, ship.shipCoords.end());

    }

    while (fit == false) {

        if (player == 1) {

            getline(cin, direction);

        }

        else if (player == 2) {

            string directions[4] = { "1", "2" "3", "4" };
            int Index1 = rand() % 3;
            direction = directions[Index1];

        }

        

        if (direction == "1") {

            inputCheck = true;

            for (int j = 0; j < 10; j++) {

                for (int k = 0; k < 10; k++) {

                    if (ship.shipCoords[0] == grid[j][k] && fit == false) {

                        if ((j - size) < 0) {

                            if (player == 1) {

                                cout << "The ship will not fit here, try another direction \n";

                            }

                            
                            fit = false;

                        }

                        else if ((j - size) >= 0) {

                            fit = true;

                            if (player == 1) {

                                cout << "Your ship has been placed on the grid. \n";

                            }  
                        }
                    }
                }
            }
        }

        else if (direction == "2") {

            inputCheck = true;

            for (int j = 0; j < 10; j++) {

                for (int k = 0; k < 10; k++) {

                    if (ship.shipCoords[0] == grid[j][k] && fit == false) {

                        if ((j + size) > 10) {

                            if (player == 1) {

                                cout << "The ship will not fit here, try another direction \n";

                            }

                            
                            fit = false;

                        }

                        else if ((j + size) <= 10) {

                            fit = true;

                            if (player == 1) {

                                cout << "Your ship has been placed on the grid. \n";

                            }  
                        }
                    }
                }
            }
        }

        if (direction == "3") {

            inputCheck = true;

            for (int j = 0; j < 10; j++) {

                for (int k = 0; k < 10; k++) {

                    if (ship.shipCoords[0] == grid[j][k] && fit == false) {

                        if ((k - size) < 0) {

                            if (player == 1) {

                                cout << "The ship will not fit here, try another direction \n";

                            }
                            
                            fit = false;

                        }

                        else if ((k - size) >= 0) {

                            fit = true;

                            if (player == 1) {

                                cout << "Your ship has been placed on the grid. \n";

                            }
                        }
                    }
                }
            }
        }

        if (direction == "4") {

            inputCheck = true;

            for (int j = 0; j < 10; j++) {

                for (int k = 0; k < 10; k++) {

                    if (ship.shipCoords[0] == grid[j][k] && fit == false) {

                        if ((k + size) > 10) {

                            if (player == 1) {

                                cout << "The ship will not fit here, try another direction \n";

                            }

                            fit = false;

                        }

                        else if ((k + size) <= 10) {

                            fit = true;

                            if (player == 1) {

                                cout << "The ship has been placed on the grid. \n";

                            }
                        }
                    }
                }
            }
        }

        if (inputCheck == false && player == 1) {

            cout << "That is not one of the options, please enter either 1, 2, 3 or 4 \n";

        }   
    }

    if (direction == "1") {

        for (int j = 0; j < 10; j++) {

            for (int k = 0; k < 10; k++) {

                if (ship.shipCoords[0] == grid[j + 1][k] && complete == false) {

                    for (int i = 0; i < (size - 1); i++) {

                            ship.shipCoords.push_back(grid[j--][k]);
                              
                    }

                    complete = true;

                }
            }
        }

        if (player == 1) {

            cout << "Your coordinates are: \n";

            for (int i = 0; i < ship.shipCoords.size(); i++) {

                cout << ship.shipCoords[i] << "\n";

            }
        } 
    }

    else if (direction == "2") {

        for (int j = 0; j < 10; j++) {

            for (int k = 0; k < 10; k++) {

                if (ship.shipCoords[0] == grid[j - 1][k] && complete == false) {

                    for (int i = 0; i < (size - 1); i++) {

                            ship.shipCoords.push_back(grid[j++][k]);
                         
                    }

                    complete = true;

                }
            }
        }

        if (player == 1) {

            cout << "Your coordinates are: \n";

            for (int i = 0; i < ship.shipCoords.size(); i++) {

                cout << ship.shipCoords[i] << "\n";

            }
        } 
    }

    else if (direction == "3") {

        for (int j = 0; j < 10; j++) {

            for (int k = 0; k < 10; k++) {

                if (ship.shipCoords[0] == grid[j][k + 1] && complete == false) {

                    for (int i = 0; i < (size - 1); i++) {

                            ship.shipCoords.push_back(grid[j][k--]);
                            
                    }

                    complete = true;

                }
            }
        }

        if (player == 1) {

            cout << "Your coordinates are: \n";

            for (int i = 0; i < ship.shipCoords.size(); i++) {


                cout << ship.shipCoords[i] << "\n";

            }
        }
    }

    else if (direction == "4") {

        for (int j = 0; j < 10; j++) {

            for (int k = 0; k < 10; k++) {

                if (ship.shipCoords[0] == grid[j][k - 1] && complete == false) {

                    for (int i = 0; i < (size - 1); i++) {

                            ship.shipCoords.push_back(grid[j][k++]);
                            
                    }

                    complete = true;

                }
            }
        }

        if (player == 1) {

            cout << "Your coordinates are: \n";

            for (int i = 0; i < ship.shipCoords.size(); i++) {


                cout << ship.shipCoords[i] << "\n";

            }

            cout << "\n";

        }
    }

    return ship.shipCoords;

}

string attCheck(string grid[10][10], vector <string> attacked, string attack, int player)   //This checks if the user has attacked in that position before, if they have, a new attack coordinate is requested.
{
    bool inputCheck = false;

    while (inputCheck == false) {

        if (find(attacked.begin(), attacked.end(), attack) != attacked.end()) {

            if (player == 1) {

                cout << "You have already attacked here. \n";
                cout << "You have already attacked at the following coordinates: \n";
                for (int i = 0; i < attacked.size(); i++) {

                    cout << attacked[i] << "\n";

                }

                cout << "Please entrer a new coordinate to attack from \n";
                getline(cin, attack);

            }

            else if (player == 2) {

                int Index1 = rand() % 9;
                int Index2 = rand() % 9;

                attack = grid[Index1][Index2];

            }
        }

        else {

            for (int j = 0; j < 10; j++) {

                if (inputCheck == false) {

                    for (int k = 0; k < 10; k++) {

                        if (attack == grid[j][k]) {

                            inputCheck = true;

                        }
                    }
                }
            }
        }

        if (inputCheck == false && player == 1) {

            cout << "That coordinate does not exsist, please enter one that is in the grid. \n";
            getline(cin, attack);

        }
    }

    return attack;
}

bool coordCheck(ships ship1, ships ship2, ships ship3, int player)   //This checks whether a ships initial coordinate input is not on another ship.
{
    bool inputCheck = false;
    bool flag = true;

    if (ship1.shipCoords[0] == ship2.shipCoords[0]) {

        inputCheck = false;
        flag = false;

        if (player == 1) {

            cout << "This space is already taken, please choose another \n";

        }  
    }

    else if (ship3.shipCoords.size() > 0) {

        if (ship1.shipCoords[0] == ship3.shipCoords[0]) {

            inputCheck = false;
            flag = false;

            if (player == 1) {

                cout << "This space is already taken, please choose another \n";

            }  
        }
    }

    if (flag == true) {

        inputCheck = true;

    }
   
    return inputCheck;
}

int attackFunc(string attack, ships enemyShip, int player)   //This function checks if the users attack hit the opposing ship or not.
{
    if (enemyShip.shipHealth > 0) {


        if (find(enemyShip.shipCoords.begin(), enemyShip.shipCoords.end(), attack) != enemyShip.shipCoords.end()) {

            if (player == 1) {

                cout << "That was a hit! You hit their" << enemyShip.name << "well done! \n";

            }

            else if (player == 2) {

                cout << "The enemy hit your " << enemyShip.name << ". \n";

            }

            enemyShip.shipHealth -= 1;

            cout << "\n";
            cout << "     _.-^^---....,,--        \n";
            cout << " _--                  --_   \n";
            cout << "<                        >) \n";
            cout << "|                         |  \n";
            cout << " \\._                  _./  \n";
            cout << "    ```--. . , ; .--'''      \n";
            cout << "          | |   |            \n";
            cout << "       .-=||  | |=-.    \n";
            cout << "       `-=#$%&%$#=-'   \n";
            cout << "          | ;  :|     \n";
            cout << " _____.,-#%&$@%#&#~,._____ \n";
            cout << "\n";
   
        }

        else {

            cout << "\n";
            if (enemyShip.name == "Battleship" && player == 1) {

                cout << "That missed their Battleship! \n";

            }

            else if (enemyShip.name == "Destroyer1" && player == 1) {

                cout << "That missed one of their destroyers! \n";

            }

            else if (enemyShip.name == "Destroyer2" && player == 1){

                cout << "That missed one of their destroyers! \n";

            }

            if (enemyShip.name == "Battleship" && player == 2) {

                cout << "The enemy missed your Battleship! \n";

            }

            else if (enemyShip.name == "Destroyer1" && player == 2) {

                cout << "The enemy missed one of your destroyers! \n";

            }

            else if (enemyShip.name == "Destroyer2" && player == 2) {

                cout << "That enemy missed one of your destroyers! \n";

            }
        }
    }

    return enemyShip.shipHealth;
}

bool aliveCheck(ships enemyShip, int player)  //This checks if a users ship has been destroyed or not.
{
    if (enemyShip.shipHealth <= 0) {

        enemyShip.alive = false;

        if (player == 1) {

            cout << "Your " << enemyShip.name << " has been destroyed. \n";

        }

        else if (player == 2) {

            cout << "The enemy has lost their " << enemyShip.name << ". \n";

        }
    }
    return enemyShip.alive;
}

bool posCheck(ships ship1, ships ship2, ships ship3, int player)  //This checks a ships coordinates, once assigned, are not in the way of a ship that is already placed.
{
    bool posCheck = true;

    for (int i = 0; i < ship1.shipCoords.size(); i++) {

        if (find(ship2.shipCoords.begin(), ship2.shipCoords.end(), ship1.shipCoords[i]) != ship2.shipCoords.end()) {

            if (player == 1) {

                cout << "There is already a ship in position " << ship1.shipCoords[i] << ". \n";

            }
            
            posCheck = false;
        }

        else if (ship3.shipCoords.size() > 0) {

            if ((find(ship3.shipCoords.begin(), ship3.shipCoords.end(), ship1.shipCoords[i]) != ship3.shipCoords.end())) {

                if (player == 1) {

                    cout << "There is already a ship in position " << ship1.shipCoords[i] << ". \n";

                }

                posCheck = false;

            }
        }
    }

    return posCheck;
}

void gridDisplay() //Displays the grid.
{
    cout << "\n";
    cout << "  __________________________________________________ \n";
    cout << "J|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____|  \n";
    cout << "I|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____| \n";
    cout << "H|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____| \n";
    cout << "G|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____|  \n";
    cout << "F|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____| \n";
    cout << "E|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____| \n";
    cout << "D|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____|  \n";
    cout << "C|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____| \n";
    cout << "B|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____| \n";
    cout << "A|    |    |    |    |    |    |    |    |    |    | \n";
    cout << " |____|____|____|____|____|____|____|____|____|____|  \n";
    cout << "    1    2    3    4    5    6    7    8   9    10 \n";
    cout << "\n";

}

void battleshipDisplay() //Displays the battleship.
{
    cout << "\n";
    cout << "                                  )___( \n";
    cout << "                           _______/__/_ \n";
    cout << "                  ___     /===========| \n";
    cout << " ____       __   [\\\]___/____________|__[///]   __ \n";
    cout << " \\ \\_____[\\]__/___________________________\__[//]___ \n";
    cout << "  \\                                                   | \n";
    cout << "   \\                                                 / \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    cout << "\n";
}

void destroyerDisplay() //Displays the destroyer.
{
    cout << "\n";
    cout << "                __/___             \n";
    cout << "          _____/______|            \n";
    cout << "  _______/_____\\_____ _\\_____      \n";
    cout << "  \\              < < <       |     \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
    cout << "\n";
}

void missileDisplay() //Displays the attack.
{
    cout << "\n";
    cout << "Missile firing... \n";
    cout << "\n";
    cout << "                                                   ,: \n";
    cout << "                                                 ,' | \n";
    cout << "                                                /   : \n";
    cout << "                                             --'   / \n";
    cout << "                                            \\/ />/ \n";
    cout << "                                             / /_\\ \n";
    cout << "                                          __/   / \n";
    cout << "                                          )'-. / \n";
    cout << "                                          ./  :\\ \n";
    cout << "                                           /.' ' \n";
    cout << "                                         '/' \n";
    cout << "                                         + \n";
    cout << "                                        ' \n";
    cout << "                                      `. \n";
    cout << "                                  .- - \n";
    cout << "                                 (    | \n";
    cout << "                              . .-'  '. \n";
    cout << "                             ( (.   )8: \n";
    cout << "                         .'    / (_  ) \n";
    cout << "                          _. :(.   )8P  ` \n";
    cout << "                      .  (  `-' (  `.   . \n";
    cout << "                       .  :  (   .a8a) \n";
    cout << "                      /_`( a `a. )' \n";
    cout << "                  (  (/  .  ' )==' \n";
    cout << "                 (   (    )  .8 +  \n";
    cout << "                   (`'8a.( _(   ( \n";
    cout << "                ..-. `8P    ) `  )  + \n";
    cout << "              -'   (      -ab:  ) \n";
    cout << "            '    _  `    (8PYa \n";
    cout << "          _(    (    )b  -`.  ) + \n";
    cout << "         ( 8)  ( _.aP _a  \\(\\ *  \n";
    cout << "       +  )/    (8P   (88    )  ) \n";
    cout << "          (a:f        `       ` \n";
    cout << "\n";
}
