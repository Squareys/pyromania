/*
 * Player.cpp
 *
 *  Created on: 30.07.2013
 *      Author: Squareys
 */

#include "Player.h"

#include <cstdlib>
#include <string.h>


//------------------------------------------
// Constructors of Player
//------------------------------------------

Player::Player() : MovingEntity(), name((char*)"Player"), bombs(0), bombPower(0), kills(0), maxBombs(0), alive(true){

}

Player::~Player() {
}

//------------------------------------------
// Public Member Funktions of Player
//------------------------------------------

void Player::update(int ticks){
	MovingEntity::update(ticks);
}

void Player::setName(char* nombre){
	name = nombre;
}

void Player::dropBomb(){
	bombs--; //TODO: Bomb Dropping
}

void Player::setBombPower(int pow){
	bombPower = pow;
}


char* Player::getName(){
	return name;
}

int Player::getBombs(){
	return bombs;
}

int Player::getBombPower(){
	return bombPower;
}

int Player::getMaxBombs(){
	return maxBombs;
}

int Player::getKills(){
	return kills;
}

char* Player::serialize(int* size) {
	int old_s = 0;

	char* result = Entity::serialize(&old_s);
	int s = old_s;

	return result;
	//------------

	realloc(result, s);

	char* pointer = result;
	pointer += old_s;

	return result;
}

char* Player::deserialize(char* s) {
	MovingEntity::deserialize(s);
	return s;
}
