/*
Title: PokemonList.cpp
Author: Michael Harrigan
Date: 4/2/2020
Description: File that determines the functions that can be used on the objects of PokemonList type
*/

#include "PokemonList.h"

// default constructor that initializes the variables in the class
PokemonList::PokemonList(){
    // initializes the variables in the class to null and zero to show an empty linked list
    m_head = nullptr;
    m_size = 0;
    
} // end of Constructor PokemonList

// destructor that removes the data inside of a PokemonList object
PokemonList::~PokemonList(){
    // removes the items in the linked list
    Pokemon *curr = m_head;
    while (curr != nullptr){
        m_head = curr;
        curr = curr->GetNext();
        delete m_head;

    } // end of while loop

    m_head = nullptr;
    m_size = 0;

} // end of Destructor ~PokemonList

// function InsertEnd which puts a Pokemon node at the end of the linked list that calls the function
void PokemonList::InsertEnd(Pokemon* Pkmn){
    // if the size is zero, sets the head as the input and increases the size.
    if (m_size == 0){
        m_head = Pkmn;
        m_size++;

    } // end of if statement
    
    // if there is actual data in the list, finds the node that points to a null, and replaces it with the input
    else{
        Pokemon *curr = m_head;
        Pokemon *next = m_head->GetNext();
        while (next != nullptr){
            curr = curr->GetNext();
            next = curr->GetNext();

        } // end of while loop

        // increases the size
        if (next == nullptr){
            curr->SetNext(Pkmn);
            
            m_size++;
        } // end of if statement

    } // end of else statement

} // end of InsertEnd

// displays the Pokemon nodes in the list, uses an overloaded << operator to display the specific pieces of data
void PokemonList::Display(){
    cout << setfill('-') << setw(DASH_LENGTH) << " " << endl;
    
    Pokemon *curr = m_head;
    while (curr != nullptr){
        // uses the overloaded operator to display all the information for each Pokemon
        cout << setfill(' ');
        cout << *curr << endl;
        curr = curr->GetNext();

    } // end of while loop

    cout << setfill('-') << setw(DASH_LENGTH) << " " << endl;

} // end of Display

// transfers the Pokemon node from the list that calls the function to the list passed as a parameter, and the index of the desired node
void PokemonList::Transfer(int Index, PokemonList* List){
    Pokemon *curr = m_head;
    while (curr != nullptr){
        // if the current node has the same index as that input, puts it at the end of the input list
        if (curr->GetIndex() == Index){
            
            // creates a new pokemon to fill in the passed list
            Pokemon *replacement = new Pokemon(curr->GetIndex(), curr->GetName(), curr->GetType(), curr->GetStrong());
            
            List->InsertEnd(replacement);
            curr = curr->GetNext();

        } // end of if statement

        else{
            curr = curr->GetNext();
        
        } // end of else statement

    } // end of for loop

} // end of Transfer

// removes the pokemon of the desired index from the linked list that calls the function
void PokemonList::Remove(int Index){
    Pokemon *curr = m_head; // beginning point for traversal
    Pokemon *prev; // uninitialized pointer for use in removal
    bool continueCheck = true; // used for checking through the list and stopping when the indexed item is found

    // if the index is the first, sets m_head to the second item, and deletes the info and pointer from m_head, reduces the size
    if (curr->GetIndex() == Index){
        m_head = m_head->GetNext();
        delete curr;
        curr = nullptr;
        m_size--;

    } // end of if statement

    // if the index is in the middle or the end
    else{
        // short circuit to stop the checking of the newly nullified pointer once continueCheck is false
        while ((continueCheck == true) && (curr->GetIndex() != Index)){
            // sets the previous to the current, then moves the current up one
            prev = curr;
            curr = curr->GetNext();

            // if the index is not at the end or beginning, checks through the middle for it
            // removes the data and points the previous point to the next point, deleting the current point
            if ((curr->GetNext() != nullptr) and (curr->GetIndex() == Index)){
                prev->SetNext(curr->GetNext());
                delete curr;
                curr = nullptr;
                m_size--;
                continueCheck = false;

            } // end of if

            // checks if the index is at the end, then removes the data, clears the pointer and sets the point before to null
            // also reduces the size
            else if (curr->GetNext() == nullptr){
                prev->SetNext(nullptr);
                delete curr;
                curr = nullptr;
                m_size--;
                continueCheck = false;

            } // end of else if statement

        } // end of while loop

    } // end of else statement

} // end of Remove

// getter for the m_size variable of objects of type PokemonList
int PokemonList::GetSize(){
    return m_size;

} // end of GetSize

// getter of the m_head variable of objects of type PokemonList
Pokemon* PokemonList::GetHead(){
    return m_head;

} // end of GetHead

// runs the battling of 2 Pokemon nodes, checking each of its attributes against the others and changes the health values
int PokemonList::Attack(PokemonList* EnemyList){
    // sets the heads of each of the lists to new variables
    Pokemon *yourHead = GetHead();
    Pokemon *enemyHead = EnemyList->GetHead();

    
    /* TESTING FOR WIN CONDITION */
    if (yourHead->GetType() == "None"){
        // Easiest way to implement this for testing is to add a new Pokemon in the text file with the type of "None"
        enemyHead->SetHealth(0);
        yourHead->SetHealth(9);
        
    } // end of if statement

    
    // user attacks first

    // enemy head is weak to your head's type
    if (enemyHead->GetType() == yourHead->GetStrong()){
        enemyHead->SetHealth(enemyHead->GetHealth() - STRONG_DAMAGE);
    
    } // end of if statement

    // enemy head is not weak to your head's type
    if (enemyHead->GetType() != yourHead->GetStrong()){
        enemyHead->SetHealth(enemyHead->GetHealth() - DAMAGE2ENEMY);

    } // end of else if statement 

    // if the enemy head pokemon has less than 0 health
    if (enemyHead->GetHealth() <= 0){
        cout << "Enemy " <<enemyHead->GetName() << " has fainted!" << endl;
        return ENEMY_DEATH;

    } // end of if statement

    // enemy attacks second

    // your head is weak to enemy's head
    if (yourHead->GetType() == enemyHead->GetStrong()){
        yourHead->SetHealth(yourHead->GetHealth() - STRONG_DAMAGE);
    
    } // end of if statement

    // your head is not weak to enemy's head
    if (yourHead->GetType() != enemyHead->GetStrong()){
        yourHead->SetHealth(yourHead->GetHealth() - DAMAGE2USER);
    
    } // end of else if statement

    // if your head pokemon has less than 0 health
    if (yourHead->GetHealth() <= 0){
        cout << "Your " << yourHead->GetName() << " has fainted!" << endl;
        return YOUR_DEATH;

    } // end of if statement
    
} // end of Attack

// moves the location of one Pokemon node from where it is before to the head of the linked list, moves the others back
void PokemonList::SwapPokemon(){
    int swapIndex; // index for what the user wants to put to the front
    do{
        // asks the input of the user, and places it into the swapIndex variable
        cout << "Here is your team. " << endl;
        Display();
        cout << "What Pokemon would you like to swap to the front?" << endl;
        cin >> swapIndex;

    // if the index input doesnt exist in the case of m_userPocket, reruns
    }while (!Exist(swapIndex));

    Pokemon *curr = m_head; // beginning node for the iteration through the linked list
    Pokemon *prev = m_head; // used in swapping the positions

    if (curr->GetIndex() == swapIndex){
        cout << "You cannot move that Pokemon. It is already at the front." << endl;

    } // end of if statement

    else{
        while (curr != nullptr){
            // moves the selected point to the head and pushes the rest of the points back
            if (curr->GetIndex() == swapIndex){
                prev->SetNext(curr->GetNext());
                curr->SetNext(m_head);
                m_head = curr;

            } // end of if statement

            // changes the curr and prev to reiterate
            prev = curr;
            curr = curr->GetNext();

        } // end of while loop

    } // end of else statement

} // end of SwapPokemon

// checks for the existence of a Pokemon node in the calling linked list
bool PokemonList::Exist(int Index){
    Pokemon *curr = m_head;
    while (curr != nullptr){
        // if the index input is in the list, returns true
        if (curr->GetIndex() == Index){
            return true;
        } // end of if statement

        curr = curr->GetNext();
    } // end of while loop

    // if the index was not found, returns false
    return false;

} // end of Exist