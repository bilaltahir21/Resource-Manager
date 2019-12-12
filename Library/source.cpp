#include "database.h"
#include "screen.h"
#include <cstdlib>

int main()
{
	/*---------------------------Setting the dimensions of the console Window---------------------------*/
	//system("color F0");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	const HWND console = GetConsoleWindow();
	RECT screen;
	GetWindowRect(console, &screen);
	MoveWindow(console, screen.left, screen.top, 1600, 1000, true);
	/*----------Now the console will start from the upper-left corner and it will be stretched----------*/

	/*
	 *	Only a single object of our database is enough
	 *	and its interface will provide all the funtionalities
	 */
	database data;
	data.interface();

	system("PAUSE");
}
