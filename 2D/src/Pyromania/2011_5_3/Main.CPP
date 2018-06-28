#define ALLEGRO_NO_MAGIC_MAIN

#include <process.h> // is for threadding.
#include <allegro.h>
#include <winalleg.h>

#include "Util.h"
#include "Game.h"



/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "Bomberman Version 0.1";


void GameThread (LPVOID param){
	Game* game = new Game();
	game->play();
	_endthread();
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
    	WNDCLASSEX wincl;        /* Data structure for the windowclass */

	RECT WindowRect; 
  	// Speicher für aktuelle Auflösung
  
  	WindowRect.left=(long)0; 
  	// Die linke Seite des Rechtecks wirtd auf 0 gesetzt

  	WindowRect.right=(long)810; 

  	WindowRect.top=(long)0; 

  	WindowRect.bottom=(long)650; 

    	/* The Window structure */
    	wincl.hInstance = hThisInstance;
    	wincl.lpszClassName = szClassName;
    	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    	wincl.cbSize = sizeof (WNDCLASSEX);

    	/* Use default icon and mouse-pointer */
    	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    	wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    	wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    	wincl.lpszMenuName = NULL;                 /* No menu */
    	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    	wincl.cbWndExtra = 0;                      /* structure or the window instance */
    	/* Use Windows's default color as the background of the window */
    	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	wincl.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; 
  	// Bei Veränderungen in der Höhe und/oder Breite, 
  	// soll ne gezeichnet werden

  	wincl.lpfnWndProc = (WNDPROC) WindowProcedure; 
  	// WndProc behandelt die auftretenden Nachrichten

  	wincl.hIcon = LoadIcon(NULL, IDI_WINLOGO); 
  	wincl.hbrBackground = NULL;

    	/* Register the window class, and if it fails quit the program */
    	if (!RegisterClassEx(&wincl)) // Versuch die Klasse zu registrieren
  	{
    		MessageBox(NULL,"Konnte die Fensterklasse nicht registrieren.",
                "ERROR",MB_OK|MB_ICONEXCLAMATION);
    		return FALSE; // FALSE zurückgeben und beenden
  	}

    	/* The class is registered, let's create the program*/
    	hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Bomberman Verion 0.1",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           600,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    	/* Make the window visible on the screen */
    	ShowWindow (hwnd, nFunsterStil);

    	/* Start initializing allegro */
    	win_set_window(hwnd);

    	init(800, 600, 60, false);

	_beginthread(GameThread, 0, NULL);
        


    	/* The program return-value is 0 - The value that PostQuitMessage() gave */
    	/* Run the message loop. It will run until GetMessage() returns 0 */
    	while (GetMessage (&messages, NULL, 0, 0))
    	{
       	 	/* Translate virtual-key messages into character messages */
        	TranslateMessage(&messages);
    	    	/* Send message to WindowProcedure */
    	    	DispatchMessage(&messages);
    	}
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
	case WM_DESTROY:
		done();
                PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
                break;
        default:                      /* for messages that we don't deal with */
                return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
