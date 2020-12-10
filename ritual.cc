#include "ritual.h"

Ritual::Ritual(std::string name, Board* board) : Card{name,board} {
	if (name == "Dark Ritual") {
		cost = 0;
		description = "At the start of your turn, gain 1 magic";
	} else if (name == "Aura Of Power") {
		cost = 1;
		description = "Whenever a minion enter a play under your control, it gains +1/+1";
	} else {
		cost = 3;
		description = "Whenever a minion enter a play, destroy it";
	}
}

void play(int owner, int targetPlayer, int minion, bool actOnRitual) 
{
	if (cost > board->getPlayer(owner)->getMagic()) return;
    board->getPlayer(owner)->setMagic(board->getPlayer(owner)->getMagic()-cost);
    auto r = std::make_shared<Ritual>(name,board);
    board->getPlayer(owner)->setRitual(r);
}

void useAbility(int owner, int playedMinion, bool isOwnerActive, When when)
{
    if (charges < activationCost) { return; }
    if (name == "Dark Ritual"){
        //At the start of your turn, gain 1 magic
        (!isOwnerActive || when!=When::Start) ? return;
        charges -= activationCost;
        board->getPlayer(owner)->incrementMagic();
    }
    else if (name == "Aura Of Power") {
        //whenever a minion enter a play under your control, it gains +1/+1
        (!isOwnerActive || when!=When::Play) ? return;
        charges -= activationCost;
        board->getPlayer(owner)->getMinion(minion)->setAttack(board->getPlayer(owner)->getMinion(minion)->getAttack()+1);
        board->getPlayer(owner)->getMinion(minion)->setDefence(board->getPlayer(owner)->getMinion(minion)->Defence()+1);
    }
    else if (name == "Standstill") {
        //whenever a minion enter a play, destroy it
        (when!=When::Play) ? return;
        int p = isOwnerActive ? owner : owner%2+1;
        charges -= activationCost;
        board->getPlayer(p)->removeMinion(board->getPlayer(p)->getNumMinions()-1);
    }
}

int Ritual::getCharges() const { return charges; }