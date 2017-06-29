#pragma once

class Wizard
{

public:
	 Wizard(int maxHealth, int maxMana);


private:
	
	int health;

	int mana;

	void StartAttack();

	void StopAttack();

};
