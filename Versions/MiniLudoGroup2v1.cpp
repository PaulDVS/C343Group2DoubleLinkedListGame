#include<iostream>
#include<string>

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
}

Node topLeft;
bool endGame;
Player player1;
Player player2;
Player player3;
Player player4;
Player currentPlayer;

int main()
{
	//Outerloop Main menu loop
		//Inner game loop that calls init function
			//if current player =1 set to 2, if 4 set to 1;
			//Loop through players turn
				//Can call view map, roll dice or exit to main menu
		//Inner loop ends when ch=exit or endGame flag = True.
	//Ends when ch=end
}

void initGame(){
	//Create board
	//Create linked list and node
	//Create players and set their init values
}

void viewMap(Player currentPlayer){
	//Ignore
}

void rollDice(Player currentPlayer){
	//Use rand to roll a dixe
	//Check pos + dice
	//Loop for each dice roll -> move player forward
	//PlayLanding function
}

void movePlayer(Player currentPlayer){
	//if pos = 22/38
		//Move inside
	//Else if pos <<22
		//move prev
	//Else
		//Move next
}

void playerLanding(Player currentPlayer){
	//Check if user lands in safe space
	//Get other player positions
	//Compare current user to other players
	//Compare names to make sure it doesn't compare itself
	//If same currentNode, set other players currentNode to other player's homeNode
}


