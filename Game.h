
											//*************START HERE***********//


/*****  
This header file is the heart of the game, GameBetting.cpp, GameCards.cpp GameSetUp.cpp are all cpp files of this header file.
It contains all the functions that the game uses. You may find some of the definitions of these functions in GameBetting.cpp, GameCards.cpp, 
GameSetup.cpp as well as Game.cpp. Remember they all share from this class. It's just separated so that there arent 10,000 lines of code in 
one file. FYI, all of the functions and variables that start with SDL_ are SDL specific keywords and are not mine. Everything else is custom. 
I hope that helps.
*****/


#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <string>

class GameObject;

class Game {
public:
	Game();
	~Game();

	//This function is used in the main function to open a window. It also initializes true type fonts and other SDL unique properties
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	//This function specifically handles mouse up and down events. It can also do keyboard events but I didn't use it in this program
	void handleEvents();

	/*This function keeps running so long as the program is. It's constantly checking which state the game is in and changes the
	game accordingly. Such as which images to render among other things. Update calls other functions which in turn may call others
	it could get confusing but if you follow the trail it should make sense. This function is called in the main function while loop*/
	void update();

	//render diverts to the Render() function in the Texture manager. This is basically a builder to render textures and load them.
	void render();

	//Just a function to desctruct everything
	void clean();

	//This is used to close the window, or rather end the while loop in the main function so that we can exit the game
	bool running() { return isRunning; }
	static SDL_Event event;

	void getMouseState();	//This checks the location of the mouse, it is used to determine if it hovers over a button using coordinates
	void playButton();		//This is only to check whether the mouse is over the play button in the first scene. It sets the variable for the second scene.
	
	/*This function goes through a png file that is present in the project folder and assigns them to game objects and gives them values
	based on the card number. This is easy because the png is pretty well symmetrical and using the size of the file, I can go through each
	individual element within that png based on its location. Also, the cards are in order of card numbers and suits, as so I made an
	algorithm that can assign them automatically without having to go through each one individually*/
	void Cards();
	
	/*This creates the text that appears at the top of the screen to let player know what to do. It uses one of the GameObject constructors
	(there's 2), the one specifically made for text. GameObject also uses the text manager to build it for us*/
	void Text();

	/*This function has game objects that ask their owner (GameObject) to render them. These objects are declared below in the private sector 
	under Text Objects. This function is called in the render() function of this (Game) class. render() is called in the main game loop in the
	main function*/
	void TextRender();

	/*This sets the poitions on the screen for all the text. It calls the update function from the game object class. The game object
	class is responsible for creating and setting positions for all the game objects. It has it's own update function to help take care
	of all that. It also, of course, uses the texture manager to build the objects*/
	void TextPositions();


	void VectorPositions();			//This sets the positions for the dealers cards and the player's cards algorithmically if they have any.
	void VectorRender();			//This deals with rendering the dealer's and player's cards. It uses the Rnder function in GameObject.
	void Chips();					//This goes through each png of chips and creates game objects as well as set their value
	void ChipsRender();				//This renders the chips using the GameObject Render()
	void ChipsPosition();			//This sets the chip positions and uses it's parent's (GameObject) update function to set them every frame.
	void MouseUpBet();				//When the player clicks on one of the chips, we add it to their bet and remove it from their credits.
	
	/*This is when the player clicks on the deck to deal the cards. We add cards to the player's hand and add to their points, being how 
	many points they have out of 21. By adding cards to the player's hand, they automatically render in the VectorRender() function and 
	locations are set in the VectorPositions function. Because they are called in the update() function of this class, and the update()
	function is called the main while loop in the main function, we don't have to do anything except give the player the cards and the 
	game takes care of the rest*/
	void MouseUpDeal();

	/*There are only two buttons on the left side of the main game scene, hit and stand. in this function we check if the mouse is within
	the coordinates of where the buttons are and alter our booleans accordingly. Again, we only need to set triggers because the update
	functions handle all of the rendering and location setting for all the text and game objects. For example, when you hit, all I need to do
	is puch a card object to the players hand and the update functions will take care of the rest*/
	void MouseUpButtons();

	void ResetTriggers();			//When we start a new round, it's important that all of our booleans/triggers are set appropriately
	void UpdateBetText();			//This updates the text that says "Current Bet: " and makes it equal to the bet amount.
	void UpdateCreditText();		//This updates the text that says "Credits: " and makes it equal to how much money the player has left
	
	/*This is for when it's the dealer's turn, as the dealer is controlled by the game, it uses time delay(declared at the bottom of this
	page) to deal the cards automatically one by one rather than instantly. It happens when the player stands. It keeps going until the dealer
	has 17 points or more, or if he just has more points than the player. This function is called in the update function and is called when
	a boolean is set. Eventually this function will get routed to the EndGame() function which deals with the calculation at the end of the
	round as well as determining who wins round*/
	void UpdateDealerCards();

	/*This calculates who wins or loses the round and updates triggers (booleans) appropriately to display the correct messages and reset 
	all the triggers. It then goes to the ResetRound() function. The boolean that is passed as an argument is to tell the function whether
	or not the player got a natrual*/
	void EndGame(bool natural);
	void Shuffle();				//This shuffles the deck, which is a vector. This is called in the ResetRound() function() (below)
	void ResetRound();			//This calls the Shuffle() function and resets a few values for the next round
	
	/*This takes an integer (how many points the dealer or player has) and tells you whether or not they should make their ace worth 11 as 
	aces are worth 1 in this game by default. This is used when the player stands to calculate their points if they have an ace, and for the 
	dealer, it is triggerd in the update funtion of this class with a boolean between every card they are dealt to make sure they are using
	it to their advantage*/
	void Ace(int* points);	

private:
	std::vector<GameObject> deck;
	std::vector<GameObject> pCards;
	std::vector<GameObject> dCards;			//These are the game object vector that contain the dealer and player cards as well as text objects
	std::vector<GameObject> betText;
	std::vector<GameObject> creditText;
	
	int betTextAmount;
	int creditTextAmount = 50000;
	int dealCounter;
	int deckCounter;				//Variable for the logic of the game
	int playerPoints;
	int dealerPoints;

	//One of these represents the deck at the top right of the screen and the other is for the dealer's second card on the first deal
	GameObject* faceDownCard;
	GameObject* faceDownCard2;

	bool isRunning;				//This keeps the main while loop going. If it's false, the game shuts down.
	bool firstScene = true;

	//These are SDL specific objects that help to create windows and render objects you will see the renderer a lot in this program
	SDL_Window* window;
	SDL_Renderer* renderer;

	//Chips
	GameObject* five;
	GameObject* ten;
	GameObject* twentyFive;
	GameObject* fifty;
	GameObject* hundred;		//Each one is an image with a value
	GameObject* fiveHundred;
	GameObject* thousand;
	GameObject* fiveThousand;
	GameObject* tenThousand;

	//Text Objects
	GameObject* credit;
	GameObject* betAmount;
	GameObject* betMessage;
	GameObject* dealtMessage;
	GameObject* notEnoughMoney;
	GameObject* betBeforeDeal;		//Different messages that show at the top of the screen at the right times.
	GameObject* bustedMessage;
	GameObject* dealerBusted;
	GameObject* standOffMessage;
	GameObject* youWinMessage;
	GameObject* houseWinsMessage;
	GameObject* playerStandsMessage;

	//Game Triggers
	bool bett = false;
	bool bettM = false;
	bool deal = false;
	bool ddownn = false;
	bool ddowned = false;
	bool notEnough = false;
	bool stood = false;
	bool busted = false;
	bool makeBet = false;
	bool dealerBust = false;
	bool standOff = false;
	bool youWin = false;
	bool houseWins = false;
	bool playerStands = false;
	bool updateDealer = false;
	bool faceUp = false;
	bool dealerAce = false;
	bool playerAce = false;

	//X Coordinates For Card Placement. As the player and dealer both have their cards on the same X coordinates I only have to have differnt Ys
	int xPos[6] = {300, 360, 420, 480, 540, 600};
	int playerYpos = 400;
	int dealerYpos = 120;

	//Time Management
	Uint32 startTime;
	Uint32 delayTime = 1500;
};

									//********SEE TEXTURE.H NEXT THEN GAMEOBJECT.H********//
