/*
Title: Game.cpp
Author: Michael Harrigan
Date: 4/2/2020
Description: program that uses the linked list and nodes inside to create a functioning game
*/

#include "Game.h"

// constuctor that allocates memory for each of the specified member variables and takes in the filename
Game::Game(string FileName){
    m_list = new PokemonList;
    m_userPocket = new PokemonList;
    m_enemyPocket = new PokemonList;
    m_filename = FileName;

} // end of constructor Game

// destructor of the Game class, deletes the contents of the member variables using their respective destructors
Game::~Game(){
    // deletes the contents of each list using PokemonList destructor
    // then points to null
    delete m_list;
    m_list = nullptr;

    delete m_userPocket;
    m_userPocket = nullptr;

    delete m_enemyPocket;
    m_enemyPocket = nullptr;

    // this line could be negligible, but it is here just in case
    m_filename = "";
    
} // end of destructor ~Game

// takes the input file that is loaded with the game and reads the information into the m_list linked list
void Game::LoadFile(){
    ifstream Pokedex(m_filename);
    
    if (Pokedex.is_open()){
        while (Pokedex.good()){

            //creates temp variables for each pokemon to input into the new pokemon
            int tempIndex;
            string tempName;
            string tempType;
            string tempStrong;
            
            Pokedex >> tempIndex;
            Pokedex.ignore(1,',');
            getline(Pokedex, tempName, ',');
            getline(Pokedex, tempType, ',');
            getline(Pokedex, tempStrong);

            Pokemon *temp = new Pokemon(tempIndex, tempName, tempType, tempStrong);

            m_list->InsertEnd(temp);

        } // end of while loop
    
    } // end of if statement

    Pokedex.close();

} // end of LoadFile

// allows the user to choose their team from the roster inside of the master linked list
void Game::ChooseTeam(){ 
    int teamSize = NUM_TEAM; // max team size and counter used to show how many are needed to fill the team
    int indexInput; // what the user inputs to take a Pokemon into their team

    while (teamSize > 0){
        // prints out the total pokemon that are available
        cout << "Here is a list of Pokemon that are allowed to be chosen: " << endl;
        m_list->Display();

        do{
            // asks the Pokemon to have joining the team, checks the existance in the master list
            cout << "Pick a Pokemon by entering the index " << "(" << teamSize << " left): ";
            cin >> indexInput;
        } while (m_list->Exist(indexInput) != true);
        teamSize--;

        // moves the pokemon selected into the users team, and removes it from the list m_list
        m_list->Transfer(indexInput, m_userPocket);

        m_list->Remove(indexInput);

    } // end of while loop

} // end of ChooseTeam

// displays the menu for the user to use and interact with, as well as returning the input that they would like to do
int Game::Menu(){
    int playerChoice; // what choice the user makes in their turn
    do{
        cout << "Menu:" << endl;
        cout << "1. Attack" << endl << "2. Swap" << endl << "3. Forfeit" << endl;
        cin >> playerChoice;
    }while ((playerChoice > FORFEIT) or (playerChoice < ATTACK));

    return playerChoice;

} // end of Menu

// shows the teams, makes the leaders fight, and checks for the win conditions within the game
int Game::Battle(){
    bool reDisp = false; // used to decide if the menu will redisplay
    int playerChoice; // used to take the input of the user on what action to take
    int round = 1; // the round that the game is currently on, adds when a new action is taken

    // displays the players chosen team
    cout << "Here is your current team: " << endl;
    m_userPocket->Display();

    // displays the enemy team
    cout << "Here is the enemy team: " << endl;
    m_enemyPocket->Display();

    Pokemon *enemyHead = m_enemyPocket->GetHead();
    Pokemon *yourHead = m_userPocket->GetHead();

    // displays the round, leading Pokemon, and the menu
    cout << "Round " << round << ":" << endl;
    cout << "CPU's Pokemon: " << enemyHead->GetName() << " (" << enemyHead->GetType() << ", " << enemyHead->GetHealth() << " Health)" << endl << endl;
    cout << "Your Pokemon: " << yourHead->GetName() << " (" << yourHead->GetType() << ", " << yourHead->GetHealth() << " Health)" << endl << endl;
    cout << setfill('-') << setw(80);
    cout << " " << endl;
    cout << setfill(' ');

    playerChoice = Menu();
    bool gameEnd = false;
    while (!gameEnd){
        // updates the headers
        Pokemon *enemyHead = m_enemyPocket->GetHead();
        Pokemon *yourHead = m_userPocket->GetHead();

        // redisplays the leading pokemon each turn other than the first
        if (reDisp == true){
            cout << setfill('-') << setw(80);
            cout << " " << endl << setfill(' ');
            cout << "Round " << round << ":" << endl;
            cout << "CPU's Pokemon: " << enemyHead->GetName() << " (" << enemyHead->GetType() << ", " << enemyHead->GetHealth() << " Health)" << endl << endl;
            cout << "Your Pokemon: " << yourHead->GetName() << " (" << yourHead->GetType() << ", " << yourHead->GetHealth() << " Health)" << endl << endl;
            cout << setfill('-') << setw(80);
            cout << " " << endl;
            cout << setfill(' ');

            playerChoice = Menu();

        } // end of if statement

        switch (playerChoice){
            case ATTACK:
                // call attack function
                reDisp = true;
                round++;
                break;
    
            case SWAP:
                m_userPocket->SwapPokemon();
                reDisp = true;
                round++;
                break;

            case FORFEIT:
                return 2;
                break;

            default:
                cout << "Please enter a valid number, 1 through 3." << endl;
                playerChoice = Menu();
                reDisp = true;
                break;

        } // end of switch statement

        // runs the battle between the 2 pokemon
        int battleResult = m_userPocket->Attack(m_enemyPocket);

        // checks for the deaths of each head pokemon
        if (battleResult == ENEMY_DEATH){
            m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());

        } // end of if statement

        if (battleResult == YOUR_DEATH){
            m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());
            if (m_userPocket->GetSize() > 0){
                m_userPocket->SwapPokemon();
            
            } // end of if statement

        } // end of if statement

        if ((m_userPocket->GetSize() == 0) or (m_enemyPocket->GetSize() == 0)){
            gameEnd = true;

        } // end of if statement

    } // end of while loop

    if (m_enemyPocket->GetSize() == 0){
        return USER_WIN;

    } // end of if statement

    else if (m_userPocket->GetSize() == 0){
        return ENEMY_WIN;

    } // end of else if statement

    else{
        return BATTLE_BROKE;

    } // end of else statement

} // end of Battle

// loads in the file via LoadFile, fills the 2 teams and allows the battling to begin
int Game::Start(){
    int enemyIndex; // the index used to add to the enemyPocket
    int result; // what the ending of battle will yield into

    LoadFile();

    int maxSize = m_list->GetSize(); // the biggest that the main list will be after the loading of the file

    ChooseTeam();

    // fills in the enemy team using the original size of the master list
    for (int i = 0; i < NUM_TEAM; i++){
        // gets an int in range of the max size of the main list, adds it to m_enemypocket
        enemyIndex = rand() % maxSize;
        // checks for the existance in the master list, if it does not, tries again unti it does
        while (m_list->Exist(enemyIndex) == false){
            enemyIndex = rand() % maxSize;

        } // end of while loop

        m_list->Transfer(enemyIndex, m_enemyPocket);
        m_list->Remove(enemyIndex);

    } // end of for loop

    result = Battle();

    return result;

} // end of Start