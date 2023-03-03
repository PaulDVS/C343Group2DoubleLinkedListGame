#include<iostream>
#include<string>

using namespace std;

struct Node {
    bool safeSpace;
    struct Node *next;
    struct Node *prev;
    struct Node *inside;
    struct Node *outside;
};

struct Player {
    string playerName;
    int playerPos;
    Node *currentNode;
    Node *homeNode;
};

void initGame();

void viewMap(Player *currentPlayer);

void rollDice(Player *currentPlayer);

void movePlayer(Player *currentPlayer);

void playerLanding(Player *currentPlayer);


Node *topLeft;
bool endGame;
Player *player1;
Player *player2;
Player *player3;
Player *player4;
Player *currentPlayer;

int main() {
    int ch;

    do {
        cout << "Welcome to Mini Ludo" << endl;
        cout << "Enter 1: To start new game" << endl;
        cout << "Enter 9: To end game" << endl;
        cout << "Enter choice = " << endl;
        cin >> ch;
        switch (ch) {
            case 1:
                initGame();
                currentPlayer = player1;


                do {
                    do {
                        cout << currentPlayer->playerName << "'s turn'" << endl;
                        cout << "Enter any integer to roll" << endl;
                        cout << "Enter 2: to view map" << endl;
                        cout << "Enter 9: To end game" << endl;
                        cout << "Enter choice = " << endl;
                        cin >> ch;

                        if (ch == 2) {
                            viewMap(currentPlayer);
                        } else if (ch != 9) {
                            rollDice(currentPlayer);
                        }

                    } while (ch == 2);

                    if (currentPlayer == player1) {
                        currentPlayer = player2;
                    } else if (currentPlayer == player2) {
                        currentPlayer = player3;
                    } else if (currentPlayer == player3) {
                        currentPlayer = player4;
                    } else {
                        currentPlayer = player1;
                    }


                } while (ch != 9 && !endGame);
                endGame = false;
                ch = 0;
                break;
            case 9:
                cout << "Thank you for playing" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (ch != 9);
}

void initGame() {
    Node *tempNode;
    Node *prevNode = NULL;
    topLeft = NULL;

    player1 = new Player();
    player1->playerName = "Player 1";
    player1->playerPos = 0;

    player2 = new Player();
    player2->playerName = "Player 2";
    player2->playerPos = 0;

    player3 = new Player();
    player3->playerName = "Player 3";
    player3->playerPos = 0;

    player4 = new Player();
    player4->playerName = "Player 4";
    player4->playerPos = 0;


    for (int i = 0; i < 24; i++) {
        tempNode = new Node();
        tempNode->safeSpace = false;
        tempNode->inside = NULL;
        tempNode->outside = NULL;
        tempNode->prev = prevNode;

        if (prevNode == NULL) {
            topLeft = tempNode;
        } else {
            prevNode->next = tempNode;
        }

        prevNode = tempNode;


        if (i == 0) {
            tempNode->safeSpace = true;
        } else if (i == 3) {
            tempNode->safeSpace = true;
            player2->homeNode = tempNode;
            player2->currentNode = tempNode;
        } else if (i == 6) {
            tempNode->safeSpace = true;
        } else if (i == 9) {
            tempNode->safeSpace = true;
            player1->homeNode = tempNode;
            player1->currentNode = tempNode;
        } else if (i == 12) {
            tempNode->safeSpace = true;
        } else if (i == 15) {
            tempNode->safeSpace = true;
            player4->homeNode = tempNode;
            player4->currentNode = tempNode;
        } else if (i == 18) {
            tempNode->safeSpace = true;
        } else if (i == 21) {
            tempNode->safeSpace = true;
            player3->homeNode = tempNode;
            player3->currentNode = tempNode;
        } else if (i == 23) {
            tempNode->next = topLeft;
            topLeft->prev = tempNode;
        }
    }

    tempNode = NULL;
    prevNode = NULL;

    for (int i = 0; i < 16; i++) {
        tempNode = new Node();
        tempNode->safeSpace = false;
        tempNode->inside = NULL;
        tempNode->outside = NULL;
        tempNode->prev = prevNode;

        if (prevNode == NULL) {
            topLeft->prev->inside = tempNode;
        } else {
            prevNode->next = tempNode;
        }

        prevNode = tempNode;

        if (i == 0) {
            tempNode->safeSpace = true;
        } else if (i == 4) {
            tempNode->safeSpace = true;
            player2->homeNode->next->next->inside = tempNode;
        } else if (i == 8) {
            tempNode->safeSpace = true;
            player1->homeNode->next->next->inside = tempNode;
        } else if (i == 12) {
            tempNode->safeSpace = true;
            player4->homeNode->next->next->inside = tempNode;
        } else if (i == 15) {
            tempNode->next = topLeft->prev->inside;
            topLeft->prev->inside->prev = tempNode;
        }
    }

    tempNode = NULL;
    prevNode = NULL;

    for (int i = 0; i < 8; i++) {
        tempNode = new Node();
        tempNode->safeSpace = false;
        tempNode->inside = NULL;
        tempNode->outside = NULL;
        tempNode->prev = prevNode;

        if (prevNode == NULL) {
            topLeft->prev->inside->prev->inside = tempNode;
        } else {
            prevNode->next = tempNode;
        }


        if (i == 2) {
            tempNode->safeSpace = true;
            player2->homeNode->next->next->inside->prev->inside = tempNode;
        } else if (i == 4) {
            tempNode->safeSpace = true;
            player1->homeNode->next->next->inside->prev->inside = tempNode;
        } else if (i == 6) {
            tempNode->safeSpace = true;
            player4->homeNode->next->next->inside->prev->inside = tempNode;
        } else if (i == 7) {
            tempNode->next = topLeft->prev->inside->prev->inside;
            topLeft->prev->inside->prev->prev->inside = tempNode;
        }
    }
}

void viewMap(Player *currentPlayer) {
    //Ignore
}

void rollDice(Player *currentPlayer) {
    //Use rand to roll a dixe
    srand(time(NULL));
    int diceRoll = rand() % 4 + 1;
    cout << "You rolled a " << diceRoll << endl;

    //Check pos + dice
    if ((currentPlayer->playerPos + diceRoll) > 47) {
        cout << "Player rolled over the final block, try again next turn." << endl;
        return;
    } else {
        //Loop for each dice roll -> move player forward
        for (int i = 0; i < diceRoll; i++) {
            movePlayer(currentPlayer);
            //PlayLanding function
            playerLanding(currentPlayer);
        }
    }
}

void movePlayer(Player *currentPlayer) {
    //if pos = 22/38
    //Move inside
    //Else if pos <<22
    //move prev
    //Else
    //Move next
}

void playerLanding(Player *currentPlayer) {
// Check if user lands in safe space
    if (currentPlayer->currentNode->safeSpace) {
        cout << currentPlayer->playerName << " has landed on a safe space!" << endl;
        return;
    }
    //Get other player positions
    Player *players[] = {player1, player2, player3, player4};

    for (int i = 0; i < 4; ++i) {
        //Compare names to make sure it doesn't compare itself
        if (players[i] == currentPlayer) {
            continue;
        }
        else if (players[i]->currentNode == currentPlayer->currentNode) //Compare current user to other players
        {
            cout << currentPlayer->playerName << " finds " << players[i]->playerName << " sitting carelessly on the same spot. " << endl;
            players[i]->currentNode = players[i]->homeNode;
            cout << currentPlayer->playerName << " strikes and kills " << players[i]->playerName << ", sending them back to their home node!" << endl;
        }
    }
}