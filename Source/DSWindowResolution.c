/*
    DSWindowResolution: A program to change the window size of the Dark Souls: Prepare to Die Edition.

    Copyright (C) 2016  Lucas Cota (BrasileiroGamer)
    lucasbrunocota@live.com
    <http://www.github.com/BrasileiroGamer/>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _WIN32_WINNT 0x0500
#include <time.h>
#include <stdio.h>
#include <windows.h>

int main()
{
	int FirstRun; //Run Control
	int WindowWidth; //Width Size
	int WindowHeight; //Height Size
	HWND WindowHandle; //Window Handle

	int TimeLimit; //FindWindow() Limit
	clock_t TimeStart; //FindWindow() Start

	//Checking INI
	FILE *DSWindowResolution = fopen("./DSWindowResolution.ini", "r");
	FirstRun = GetPrivateProfileInt("Global", "FirstRun", -1, "./DSWindowResolution.ini");
	TimeLimit = GetPrivateProfileInt("Global", "TimeLimit", -1, "./DSWindowResolution.ini");
	WindowWidth = GetPrivateProfileInt("Window", "WindowWidth", -1, "./DSWindowResolution.ini");
	WindowHeight = GetPrivateProfileInt("Window", "WindowHeight", -1, "./DSWindowResolution.ini");

	if(DSWindowResolution == NULL || FirstRun == 1 || FirstRun == -1 || TimeLimit == -1 || WindowWidth == -1 || WindowHeight == -1)
	{
		DSWindowResolution = fopen("./DSWindowResolution.ini", "w");

		//Getting Configurations
		system("cls");
		printf("\n DSWindowResolution Tool v2016.1\n\n");
		printf(" Well, it looks like it's the first time you're running DSWindowResolution.\n");
		printf(" 'WindowWidth' is the value of the width of the window (eg: 1920).\n");
		printf(" 'WindowHeight' is the value of the height of the window (eg: 1080).\n");
		printf(" Please enter values for configuration:\n\n");

		printf(" WindowWidth: ");
		scanf("%i", &WindowWidth); fflush(stdin);
		printf(" WindowWidth: ");
		scanf("%i", &WindowHeight); fflush(stdin);

		ShowWindow(GetConsoleWindow(), SW_HIDE); //Hiding Console

		//Writing Configurations
		fprintf(DSWindowResolution, "[Global]\n");
		fprintf(DSWindowResolution, "# Verifies that the program has already been set.\n");
		fprintf(DSWindowResolution, "FirstRun=0\n\n");

		fprintf(DSWindowResolution, "# Is the limit of time (in seconds) that the program will look for the game window.\n");
		fprintf(DSWindowResolution, "# Decrease this only when necessary, if you put a very small amount, it may be the program does not find the game window.\n");
		fprintf(DSWindowResolution, "TimeLimit=30\n\n");

		fprintf(DSWindowResolution, "[Window]\n");
		fprintf(DSWindowResolution, "# Is the value of the width of the window (eg: 1920).\n");
		fprintf(DSWindowResolution, "WindowWidth=%i\n\n", WindowWidth);

		fprintf(DSWindowResolution, "# Is the value of the height of the window (eg: 1080).\n");
		fprintf(DSWindowResolution, "WindowHeight=%i\n", WindowHeight);
		fclose(DSWindowResolution);

		MessageBox(NULL, "You can view this prompt again by setting 'FirstRun=1' in 'DSWindowResolution.ini' or deleting it. You can also edit the information manually in 'DSWindowResolution.ini'.\n\nPress OK to continue.", "DSWindowResolution Tool", MB_ICONINFORMATION);
	}
	else
	{
		fclose(DSWindowResolution);
		ShowWindow(GetConsoleWindow(), SW_HIDE); //Hiding Console
	}

	//Reading INI
	TimeLimit = GetPrivateProfileInt("Global", "TimeLimit", -1, "./DSWindowResolution.ini");
	WindowWidth = GetPrivateProfileInt("Window", "WindowWidth", -1, "./DSWindowResolution.ini");
	WindowHeight = GetPrivateProfileInt("Window", "WindowHeight", -1, "./DSWindowResolution.ini");

	system("START steam://rungameid/211420"); //Starting Game
	WindowHandle = FindWindow(NULL, "DARK SOULS"); //Getting Handling

	TimeStart = clock(); //Countdown Start
	TimeLimit = TimeLimit + ((TimeLimit * 100) / 1000); //Countdown Limit (Compensating 100 ms)

	//Fiding Window
	while(WindowHandle == NULL && ((clock() - TimeStart) / (double) CLOCKS_PER_SEC) <= TimeLimit)
	{
		Sleep(100);
		WindowHandle = FindWindow(NULL, "DARK SOULS");
	}

	if(WindowHandle == NULL)
	{
		MessageBox(NULL, "Could not find the Dark Souls: Prepare to Die Edition window!\n\nThe program will close, press OK to continue.", "DSWindowResolution Tool", MB_ICONERROR);
		return 1;
	}
	else
	{
		//Applying Resolution
		Sleep(5000);
		SetWindowPos(WindowHandle, NULL, ((GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2), ((GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2), WindowWidth, WindowHeight, SWP_SHOWWINDOW);
	}
	return 0;
}
