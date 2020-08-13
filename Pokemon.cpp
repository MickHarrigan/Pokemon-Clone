/*
Title: Pokemon.cpp
Author: Michael Harrigan
Date: 4/2/2020
Description: all getters and setters for a node in the class Pokemon, as well as functions that can be used in other files
*/

#include "Pokemon.h"

// default constructor to initialize the variables in the class
Pokemon::Pokemon(){
    m_name = "Arceus";
    m_index = GOD;
    m_type = "None";
    m_strong = "None";
    SetHealth(MAX_HEALTH);

} // end of default constructor Pokemon

// overloaded constructor to create a specific Pokemon node from input data
Pokemon::Pokemon(int Index, string Name, string Type, string StrongAgainst){
    m_name = Name;
    m_index = Index;
    m_type = Type;
    m_strong = StrongAgainst;
    SetHealth(MAX_HEALTH);

} // end of overloaded constructor Pokemon

// returns the address of the next node in the linked list
Pokemon* Pokemon::GetNext(){
    return m_next;

} // end of GetNext

// returns the m_name variable of a specific node
string Pokemon::GetName(){
    return m_name;

} // end of GetName

// returns the m_index variable of a specific node
int Pokemon::GetIndex(){
    return m_index;

} // end of GetIndex

// returns the m_type variable of a specific node
string Pokemon::GetType(){
    return m_type;

} // end of GetType

// returns the m_health variable of a specific node
int Pokemon::GetHealth(){
    return m_health;
    
} // end of GetHealth

// returns the m_strong variable of a specific node
string Pokemon::GetStrong(){
    return m_strong;

} // end of GetStrong

// sets the health of a node to that of the integer input
void Pokemon::SetHealth(int Health){
    m_health = Health;

} // end of SetHealth

// sets the m_next variable of a specific node to that of the input Pokemon node
void Pokemon::SetNext(Pokemon* Pkmn){
    m_next = Pkmn;
    
} // end of SetNext

// overloads the << operator to display the contents of the variables of a node
ostream &operator<< (ostream &output, Pokemon &P){
    // outputs the index, name, type and health of the pokemon when called
    output << setfill(' ') << "Index: " << left << setw(4) << P.GetIndex();
    output << "Name: " << left << setw(13) << P.GetName(); 
    output << "Type: " << left << setw(10) << P.GetType();
    output << "Health: " << P.GetHealth() << endl;
    return output;

} // end of operator overloading