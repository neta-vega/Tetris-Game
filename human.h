#ifndef _Human_H
#define _Human_H
class Player;

class Human : public Player
{
	char keys[10];
public:
	virtual const char* getType() const { return "Human"; }
	char* getKeys() { return keys; };
	void setKeys(char arr[10]);
	bool setPlayerInput(char input);
};

#endif // _Human_H