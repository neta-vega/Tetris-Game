#include "player.h"
#include "human.h"
#include "Computer.h"
#include "board.h"
#include "game.h"
#include "menu.h"
#include "point.h"
#include "shape.h"
#include "utils.h"
#pragma warning (disable:4996)
using namespace std;
#include <iostream>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "point.h"
#include "shape.h"

void Point::setValue(int& _x, int& _y)
{
	x = _x;
	y = _y;
}
int Point::getX()const
{
	return x;
}
int Point::getY()const
{
	return y;
}