#include <windows.h>
#include <iostream>
#include <vector>
#include "Timer.h"

/*
 *	Mouse clicking console application.
 *	Instructions:
 *	1: Set how long you would like the app to run for.
 *	2: Move the mouse to the location you would like it to click at and press control to save that point.
 *	   You can add as many points as you want and this app will alternate through them.
 *	   Push 'c' to stop saving the points and begin the demo.
 *     *** If you don't want to save any points and want control of the mouse yourself - then don't save
 *	       any points and just push 'c' to continue past that screen. ***
 *	3: After the 5 second countdown the application will start clicking at the locations you gave it. Or
 *	   if you set no locations will click at the current location your mouse is at.
 *     *** Push esc during this stage if you wish to stop or exit the program ***
 *
 *  #: ******* REMOVE OR EDIT THE COMMENTS AT LINE 120 TO 126 *******
 */

// Function Declarations
void  LeftClick();														// Left clicks the mouse if called.
POINT GetMousePosition();												// Returns the mouses current position.
void  SetMousePosition(POINT& mp);										// Sets the mouses position.

int main()
{
	// Get the current console window.
	HWND myWindow;
	AllocConsole();
	myWindow = FindWindowA( "ConsoleWindowClass", NULL );
	
	// Variables
	float seconds           = 0.0f;										// Timer for how long the app runs.
	int   clicks            = 0;										// Number of clicks in the amount of time the app runs.
	float waitTime          = 0.0f;										// User input of howlong the app runs.
	bool  running           = true;										// Value to keep our app running.
	bool  getMousePositions = true;										// Value if true lets us make a list of mouse positions.
	int   vectorPosition    = 0;										// Value to keep track of our position in the mousePoints vector.
	int   vectorSize        = 0;										// Size of the mousePoints vector.
	bool  hasPoints         = false;									// Default false if we have no mouse points created.

	std::vector<POINT> mousePoints;										// Vector container for our mouse points.

	std::cout << "=== READ ME ===" << std::endl;
	std::cout << "*** Warning - Make sure you don't have the mouse over something important! ***" << std::endl;
	std::cout << "*** This window will close after a 5 second countdown and start clicking!! ***" << std::endl;
	std::cout << "*** After the wait time you enterd the window will open itself again.      ***" << std::endl;

	std::cout << "\n\nHow long do you want the mouse to click for in seconds \n\n >> ";
	std::cin >> waitTime;
	std::cout << std::endl;

	do
	{
		std::cout << "Press ctrl to add the current mouse position to the list or 'C' to continue" << std::endl;
		POINT mouse = GetMousePosition();
		std::cout << "Mouse X : " << mouse.x << "                " << std::endl;
		std::cout << "Mouse Y : " << mouse.y << "                " << std::endl;
		std::cout << "\nPoints saved in list : " << mousePoints.size() << std::endl;

		// If ctrl is pushed add the mouses location the the mousePoints vector.
		if(GetAsyncKeyState(VK_CONTROL))
		{
			hasPoints = true;
			mousePoints.push_back(mouse);
			std::cout << "Added Point (" << mouse.x << ", " << mouse.y << ")" << std::endl;
			Sleep(250);
		}
		// If 'c' is pushed start the clicking after the 5 second count down.
		if(GetAsyncKeyState('C'))
		{
			getMousePositions = false;
		}

		COORD pos = {0, 10};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	}while( getMousePositions );

	// Create a timer class.
	Timer t;
	t.InitGameTime();
	t.GetDeltaTime();
	// Set DT to 5 for now to start the 5 second count down.
	float DT  = 5.0f;

	do
	{
		DT -= t.GetDeltaTime();		
		COORD pos = {0,15};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		std::cout << "Clicks will start in : " << DT << std::endl;

	}while(DT > 0.0f);

	// Reset DT.
	DT = 0.0f;
	// Hide the console window.
	ShowWindow(myWindow,0);
	// Set the number of elements in our vector to its size minus one.
	vectorSize = (mousePoints.size() - 1);

	do
	{
		DT += t.GetDeltaTime();

		// If we have any points in the mousePoints vector. Alternate through them
		// and set the mouses location to the current point we are looking at in mousePoints.
		if(hasPoints)
		{
			SetMousePosition(mousePoints[vectorPosition]);
			vectorPosition++;
			if(vectorPosition > vectorSize)
			{
				vectorPosition = 0;
			}
		}
		// Remove the comment from the line below to enable the clicking.
		LeftClick();

		// Somes of the games i've tested this on need a small pause to register all the clicks.
		// Enable this if you have that problem. And/or click the object you want to constantly click first before
		// the 5 second timer runs out.
		Sleep(1);

		clicks++;
		if( DT > 1.0f )
		{
			seconds += DT;
			DT = 0.0f;
		}
		// If escape is presses quit the program.
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			running = false;
		}

	}while(seconds < waitTime && running);

	std::cout << "Finished - Mouse Was Clicked : " << clicks << " times in " << seconds << " seconds" << std::endl;
	ShowWindow(myWindow,1);
}

//
// Desc    : Clicks the left mouse button down and releases it.
// Returns : Nothing.
//
void LeftClick()
{  
	INPUT    Input={0};													// Create our input.

	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.

	ZeroMemory(&Input,sizeof(INPUT));									// Fills a block of memory with zeros.
	Input.type        = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput( 1, &Input, sizeof(INPUT) );								// Send the input.
}

//
// Desc    : Gets the cursors current position on the screen.
// Returns : The mouses current on screen position.
// Info    : Used a static POINT, as sometimes it would return trash values
//
POINT GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}

//
// Desc    : Sets the cursors position to the point you enter (POINT& mp).
// Returns : Nothing.
//
void SetMousePosition(POINT& mp)
{
	long fScreenWidth	    = GetSystemMetrics( SM_CXSCREEN ) - 1; 
	long fScreenHeight	    = GetSystemMetrics( SM_CYSCREEN ) - 1; 

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx		        = mp.x * ( 65535.0f / fScreenWidth  );
	float fy		        = mp.y * ( 65535.0f / fScreenHeight );		  
				
	INPUT Input             = { 0 };			
	Input.type		        = INPUT_MOUSE;

	Input.mi.dwFlags	    = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
				
	Input.mi.dx		        = (long)fx;
	Input.mi.dy		        = (long)fy;

	SendInput(1,&Input,sizeof(INPUT));
}