#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"

class Ritual : public Card {
	std::string description;
	int activationCost
	int charges;
  public:
  	void play(int player, int minion = 0, bool actOnRitual = false) override;
	void useAbility(int player, int minion);
};

#endif