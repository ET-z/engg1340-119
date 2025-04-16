#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Character {
	public:
		int health;
		bool isTurn;
		std::string name;
		int damage;
		Character(std::string name, int health, bool isTurn)
			: name(name), health(health), isTurn(isTurn), damage(20) {}

		void takeDamage(int damage) {
			health -= damage;
			if (health < 0) health = 0;
		}

		void begTurn() {
			isTurn = true;
		}

		void endTurn() {
			isTurn = false;
		}
};

class Player : public Character {
	public:
		    Player(std::string name, int health, bool isTurn)
			            : Character(name, health, isTurn) {}
};

class Opponent : public Character {
	public:
		    Opponent(std::string name, int health, bool isTurn)
			            : Character(name, health, isTurn) {}
};

#endif

