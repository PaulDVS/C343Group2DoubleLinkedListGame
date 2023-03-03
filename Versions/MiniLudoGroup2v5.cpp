#include<iostream>
#include<string>
#include<cstdlib>
#include<time.h>

using namespace std;

struct Node
{
	bool safeSpace;
	struct Node *next;
	struct Node *prev;
	struct Node *inside;
	struct Node *outside;
};

struct Player
{
	string playerName;
	int playerPos;
	Node *currentNode;
	Node *homeNode;
};

void initGame();
void viewMap(Player *currentPlayer);
void tileCheck(Node *currentNode);
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

int main()
{
	int ch;
	
	do
	{
		cout<<"Welcome to Mini Ludo"<<endl;
		cout<<"Enter 1: To start new game"<<endl;
		cout<<"Enter 9: To end game"<<endl;
		cout<<"Enter choice = "<<endl;
		cin>>ch;
		switch(ch){
			case 1:
				initGame();
				currentPlayer=player1;
				
				do
				{	
					Node *testNode = player1->homeNode->next->next->inside->prev->inside->prev;
					
				
					do{
						cout<<currentPlayer->playerName<<"'s turn'"<<endl;
						cout<<"Enter any integer to roll"<<endl;
						cout<<"Enter 2: to view map"<<endl;
						cout<<"Enter 9: To end game"<<endl;
						cout<<"Enter choice = "<<endl;
						cin>>ch;
						
						if(ch == 2){
							viewMap(currentPlayer);
						}
						else if(ch !=9){
							rollDice(currentPlayer);
						}
						
					}while(ch==2);
					
					if(currentPlayer == player1){
						currentPlayer = player2;
					}
					else if(currentPlayer == player2){
						currentPlayer = player3;
					}
					else if(currentPlayer == player3){
						currentPlayer = player4;
					}
					else{
						currentPlayer=player1;
					}
					
					
				}while(ch!=9 && !endGame);
				endGame = false;
				ch=0;	
				break;
			case 9:
					cout<<"Thank you for playing"<<endl;
				break;
			default: cout<<"Invalid choice"<<endl;
		}
	}while(ch!=9);
}

void initGame(){
	Node *tempNode;
	Node *prevNode =NULL;
	topLeft = NULL;
	
	player1 = new Player();
	player1->playerName = "Player 1";
	player1->playerPos  = 0;
	
	player2 = new Player();
	player2->playerName = "Player 2";
	player2->playerPos  = 0;
	
	player3 = new Player();
	player3->playerName = "Player 3";
	player3->playerPos  = 0;
	
	player4 = new Player();
	player4->playerName = "Player 4";
	player4->playerPos  = 0;
	
	
	for(int i = 0; i<24; i++){
		tempNode = new Node();
		tempNode->safeSpace = false;
		tempNode->inside=NULL;
		tempNode->outside=NULL;
		tempNode->prev = prevNode;
		
		if(prevNode == NULL){
			topLeft = tempNode;
		}
		else{
			prevNode->next=tempNode;
		}	
		
		prevNode = tempNode;
		
		
		if(i==0){
			tempNode->safeSpace = true;
		}
		else if(i==3){
			tempNode->safeSpace = true;
			player2->homeNode = tempNode;
			player2->currentNode = tempNode;
		}
		else if(i==6){
			tempNode->safeSpace = true;
		}
		else if(i==9){
			tempNode->safeSpace = true;
			player1->homeNode = tempNode;
			player1->currentNode = tempNode;
		}
		else if(i==12){
			tempNode->safeSpace = true;
		}
		else if(i==15){
			tempNode->safeSpace = true;
			player4->homeNode = tempNode;
			player4->currentNode = tempNode;
		}
		else if(i==18){
			tempNode->safeSpace = true;
		}
		else if(i==21){
			tempNode->safeSpace = true;
			player3->homeNode = tempNode;
			player3->currentNode = tempNode;
		}
		else if(i==23){
			tempNode->next = topLeft;
			topLeft->prev = tempNode;
		}
	}
	
	tempNode = NULL;
	prevNode = NULL;
	
	for(int i = 0; i<16; i++){
		tempNode = new Node();
		tempNode->safeSpace = false;
		tempNode->inside=NULL;
		tempNode->outside=NULL;
		tempNode->prev = prevNode;
		
		if(prevNode == NULL){
			topLeft->prev->inside = tempNode;
		}
		else{
			prevNode->next=tempNode;
		}	
		
		prevNode = tempNode;
		
		if(i==0){
			tempNode->safeSpace = true;
		}
		else if(i==4){
			tempNode->safeSpace = true;
			player2->homeNode->next->next->inside = tempNode;
		}
		else if(i==8){
			tempNode->safeSpace = true;
			player1->homeNode->next->next->inside = tempNode;
		}
		else if(i==12){
			tempNode->safeSpace = true;
			player4->homeNode->next->next->inside = tempNode;
		}
		else if(i==15){
			tempNode->next = topLeft->prev->inside;
			topLeft->prev->inside->prev = tempNode;
		}
	}
	
	tempNode = NULL;
	prevNode = NULL;
	
	for(int i = 0; i<8; i++){
		tempNode = new Node();
		tempNode->safeSpace = false;
		tempNode->inside=NULL;
		tempNode->outside=NULL;
		tempNode->prev = prevNode;
		
		if(prevNode == NULL){
			topLeft->prev->inside->prev->inside = tempNode;
		}
		else{
			prevNode->next=tempNode;
		}	
		
		prevNode = tempNode;
		
		if(i==2){
			player2->homeNode->next->next->inside->prev->inside = tempNode;
		}
		else if(i==4){
			player1->homeNode->next->next->inside->prev->inside = tempNode;
		}
		else if(i==6){
			player4->homeNode->next->next->inside->prev->inside = tempNode;
		}
		else if(i==7){
			tempNode->next = topLeft->prev->inside->prev->inside;
			topLeft->prev->inside->prev->inside->prev = tempNode;
		}
	}
}

void viewMap(Player *currentPlayer){
	
	Node *currentNode = topLeft;
	string tileCentre;
	
	cout<<"========================================================="<<endl;
	
	//First Row
	cout<<"|";
	currentNode = topLeft;
	for(int i = 0; i<7 ;i++){
		tileCheck(currentNode);
		currentNode= currentNode->next;
	}
	cout<<endl;
	
	//Second Row
	cout<<"|";
	currentNode = topLeft->prev;
	tileCheck(currentNode);
	
	currentNode = currentNode->inside;
	for(int i = 0; i<5 ;i++){
		tileCheck(currentNode);
		currentNode= currentNode->next;
	}
	currentNode = player1->homeNode->prev->prev;
	tileCheck(currentNode);
	cout<<endl;
	
	//Third row
	cout<<"|";
	currentNode = topLeft->prev->prev;
	tileCheck(currentNode);
	
	currentNode = topLeft->prev->inside->prev;
	tileCheck(currentNode);
	
	currentNode = currentNode->inside;
	for(int i = 0; i<3 ;i++){
		tileCheck(currentNode);
		currentNode = currentNode->next;
	}
	
	currentNode = player2->homeNode->next->next->inside->next;
	tileCheck(currentNode);
	
	currentNode = player1->homeNode->prev;
	tileCheck(currentNode);
	
	cout<<endl;
	

	//Fourth row
	cout<<"|";
	currentNode = player3->homeNode;
	tileCheck(currentNode);
	
	currentNode = player3->homeNode->next->next->inside->prev->prev;
	tileCheck(currentNode);
	currentNode = player3->homeNode->next->next->inside->prev->inside->prev;
	tileCheck(currentNode);
	
	cout<<" END |";
	
	currentNode = player1->homeNode->next->next->inside->prev->inside->prev;
	tileCheck(currentNode);
	
	currentNode = player1->homeNode->next->next->inside->prev->prev;
	tileCheck(currentNode);
	
	currentNode = player1->homeNode;
	tileCheck(currentNode);
	cout<<endl;


	//Fifth row
	cout<<"|";
	currentNode = player3->homeNode->prev;
	tileCheck(currentNode);
	
	currentNode = player4->homeNode->next->next->inside->next;
	tileCheck(currentNode);
	
	currentNode = topLeft->prev->inside->prev->inside->prev->prev;
	for(int i = 0; i<3 ;i++){
		tileCheck(currentNode);
		currentNode= currentNode->prev;
	}
	
	currentNode = player1->homeNode->next->next->inside->prev;
	tileCheck(currentNode);
	
	currentNode = player1->homeNode->next;
	tileCheck(currentNode);
	
	cout<<endl;

	
	//Sixth row
	cout<<"|";
	currentNode = player3->homeNode->prev->prev;
	tileCheck(currentNode);
	
	currentNode = topLeft->prev->inside->prev->prev->prev->prev;
	for(int i = 0; i<5 ;i++){
		tileCheck(currentNode);
		currentNode= currentNode->prev;
	}
	
	currentNode = player1->homeNode->next->next;
	tileCheck(currentNode);
	cout<<endl;
	
	
	//Seventh row
	cout<<"|";
	currentNode = player4->homeNode->next->next->next;
	for(int i = 0; i<7 ;i++){
		tileCheck(currentNode);
		currentNode= currentNode->prev;
	}
	cout<<endl;
	
	cout<<"========================================================="<<endl;
}

void tileCheck(Node *currentNode){
	string tileCentre = "";
		
	if(currentNode==player1->currentNode || currentNode==player2->currentNode  || currentNode==player3->currentNode || currentNode==player4->currentNode){
		tileCentre ="P";
		if(currentNode==player1->currentNode){
			tileCentre += "1";
		}
		if(currentNode==player2->currentNode){
			tileCentre += "2";
		}
		if(currentNode==player3->currentNode){
			tileCentre += "3";
		}
		if(currentNode==player4->currentNode){
			tileCentre += "4";
		}
		
		for(int i = tileCentre.size(); i<5; i++){
			tileCentre += " ";
		}
	}
	else if(currentNode->safeSpace){
		tileCentre = "  S  ";
	}
	else{
		tileCentre = "  *  ";
	}
	cout<<tileCentre<<"|";
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
    }
	else if((currentPlayer->playerPos + diceRoll) == 47){
		cout << currentPlayer->playerName <<" has won the game." << endl;
		cout<< endl;
		endGame = true;
		return;
	}
	else {
        //Loop for each dice roll -> move player forward
        for (int i = 0; i < diceRoll; i++) {
            movePlayer(currentPlayer);
        }
        //PlayLanding function
        playerLanding(currentPlayer);
    }
}

void movePlayer(Player *currentPlayer){
	if(currentPlayer->playerPos == 22 || currentPlayer->playerPos==38){
		currentPlayer->currentNode = currentPlayer->currentNode->inside;
	}
	else if(currentPlayer->playerPos < 22 ){
		currentPlayer->currentNode = currentPlayer->currentNode->prev;
	}
	else{
		currentPlayer->currentNode = currentPlayer->currentNode->next;
	}
	currentPlayer->playerPos ++;
}

void playerLanding(Player *currentPlayer) {
// Check if user lands in safe space
    if (currentPlayer->currentNode->safeSpace) {
        cout << currentPlayer->playerName << " has landed on a safe space!" << endl;
        return;
    }
    else{
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
		        players[i]->playerPos = 0;
		        cout << currentPlayer->playerName << " strikes and kills " << players[i]->playerName << ", sending them back to their home node!" << endl;
		    }
		}
    	
	}
    
}


