#ifndef _MENU_H
#define _MENU_H


class Menu {
	int choice;
public:
	bool setChoice(int choice);
	void getChoice(int& choice_num)const;
	int menuChoice(bool pause);
	void instructions();
	int whichLevel();
};

#endif //_MENU_H