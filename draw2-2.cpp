// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <string>

#define MAX_LOADSTRING 100
#define TMR_1 1
#define TMR_2 2
#define TMR_3 3
#define TMR_4 4
#define TMR_5 5
#define TMR_6 6

using namespace std;

// functions
void catchCheck();
int hookHeightCheck();
bool hookLeftCheck();
bool hookRightCheck();
bool figureLeftCheck(HWND hWnd1, int f);
bool figureRightCheck(HWND hWnd1, int f);
void killtime(HWND hWnd1);
int releaseCheck();
bool treeCircle();
bool realisebetween();

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
INT hook_x = 200;
INT hook_y = 81;
INT hook_w = 200;
INT hook_h = 350;
BOOL podnoszony = FALSE;
INT witchFigure;

// buttons
HWND hwndButton;

// sent data
RECT drawArea1 = { 0, 0, 0, 0 };
RECT drawArea2 = { 0, 0, 0, 1 };
RECT drawArea3 = { 0, 0, 0, 2 };
RECT drawArea4 = { 0, 0, 0, 3 };
RECT drawArea5 = { 0, 0, 0, 4 };

// struct

struct figure {
	char name;
	int x;
	int y;
	int width;
	int height;
};

figure tab[5];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen penBlk(Color(255, 0, 0, 0));
	Pen penGra(Color(255, 128, 128, 128)); //gray
	Pen penYel(Color(255, 255, 230, 20)); //yellow
	Pen penOrg(Color(255, 255, 128, 0)); //orange

	RECT grph;
	SetRect(&grph, 20, 20, 700, 500); // rectangle defining draw area

	// Rectangle(hdc, grph.left, grph.top, grph.right, grph.bottom); // drawing defining rectangle

	// horizontal crane beam

	for (int i = 0; i < 33; i++) {
		PointF pthc1(40 + 20 * i, 80);
		PointF pthc2(40 + 20 * i, 60);
		PointF pthc3(60 + 20 * i, 80);

		PointF pointsHc[3] = { pthc1, pthc2, pthc3 };

		graphics.DrawLines(&penYel, pointsHc, 3);
	}

	PointF pth1(40, 60);
	PointF pth2(680.00F, 60.00F);
	PointF pth3(700.00F, 80.00F);
	PointF pth4(40.00F, 80.00F);

	PointF pointsH[5] = { pth1, pth2, pth3, pth4, pth1 };

	graphics.DrawLines(&penOrg, pointsH, 5);

	//drawing veritcal crane beam

	for (int i = 0; i < 18; i++) {
		PointF ptvc1(100, 80 + 20 * i);
		PointF ptvc2(120, 100 + 20 * i);
		PointF ptvc3(100, 100 + 20 * i);

		PointF pointsVc[3] = { ptvc1, ptvc2, ptvc3 };

		graphics.DrawLines(&penYel, pointsVc, 3);
	}

	PointF ptv1(110, 20);
	PointF ptv2(120, 60);
	PointF ptv3(120, 440);
	PointF ptv4(100, 440);
	PointF ptv5(100, 60);

	PointF pointsV[6] = { ptv1, ptv2, ptv3, ptv4, ptv5, ptv1 };

	graphics.DrawLines(&penOrg, pointsV, 6);

	//drawing crane details

	RECT bott1, bott2, bott3, top1, top2, cab;
	SetRect(&bott1, 60, 460, 160, 480);
	SetRect(&bott2, 80, 440, 140, 460);
	SetRect(&bott3, 50, 495, 170, 500);
	SetRect(&top1, 20, 50, 30, 90);
	SetRect(&top2, 30, 50, 40, 90);

	Rectangle(hdc, bott1.left, bott1.top, bott1.right, bott1.bottom);
	Rectangle(hdc, bott2.left, bott2.top, bott2.right, bott2.bottom);
	Rectangle(hdc, bott3.left, bott3.top, bott3.right, bott3.bottom);
	Rectangle(hdc, top1.left, top1.top, top1.right, top1.bottom);
	Rectangle(hdc, top2.left, top2.top, top2.right, top2.bottom);

	PointF lLine1(40, 60);
	PointF top(110, 20);
	PointF rLine1(180, 60);
	PointF rLine2(520, 60);

	PointF lines[5] = { lLine1, top, rLine1, top, rLine2 };
	graphics.DrawLines(&penGra, lines, 5);

	graphics.DrawLine(&penBlk, 90, 440, 60, 495);
	graphics.DrawLine(&penBlk, 95, 440, 65, 495);
	graphics.DrawLine(&penBlk, 125, 440, 155, 495);
	graphics.DrawLine(&penBlk, 130, 440, 160, 495);


	SetRect(&cab, 110, 90, 130, 110);
	HBRUSH bBlack = CreateSolidBrush(RGB(128, 128, 128));

	FillRect(hdc, &cab, bBlack);
	//for (int i = 1; i < 100; i++)
		//graphics.DrawLine(&pen2, data[i - 1].X, data[i - 1].Y, data[i].X, data[i].Y);

	//graphics.DrawRectangle(&pen, 50 + value, 400, 10, 20);

	// figure 

	Point points[4] = { Point(tab[0].x,tab[0].y),  Point(tab[0].x,tab[0].y + tab[0].height),   Point(tab[0].x + tab[0].width,tab[0].y + tab[0].height), Point(tab[0].x + tab[0].width,tab[0].y) };
	Point* pPoints = points;

	graphics.DrawPolygon(&penBlk, pPoints, 4);
	for(int i = 1; i < 5; i++)
		graphics.DrawEllipse(&penBlk, tab[i].x, tab[i].y, tab[i].width, tab[i].height);

	// crane hook

	//RECT hook1;
	//SetRect(&hook1, 120, 80, 120, 90);

	graphics.DrawLine(&penBlk, hook_x, hook_y, hook_w, hook_h);
}

void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{	
	RECT hookarea1;
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else if ((drawArea == &drawArea1) && !podnoszony) {
		SetRect(&hookarea1, hook_x - 1, hook_h - 1, hook_w + 1, 450);
		InvalidateRect(hWnd, &hookarea1, TRUE); //repaint drawArea
	}
	else if ((drawArea == &drawArea2) && !podnoszony) {
		SetRect(&hookarea1, hook_x - 1, hook_h - 1, hook_w + 1, hook_h + 1);
		InvalidateRect(hWnd, &hookarea1, TRUE); //repaint drawArea
	}
	else if ((drawArea == &drawArea3) && !podnoszony){
		SetRect(&hookarea1, hook_x - 1, hook_y, hook_w + 2, hook_h + 1);
		InvalidateRect(hWnd, &hookarea1, TRUE); //repaint drawArea
	}
	else if ((drawArea == &drawArea4) && !podnoszony) {
		SetRect(&hookarea1, hook_x - 1, hook_y, hook_w + 1, hook_h + 1);
		InvalidateRect(hWnd, &hookarea1, TRUE); //repaint drawArea
	}
	else if (podnoszony || drawArea == &drawArea5){
		SetRect(&hookarea1, tab[witchFigure].x - 1, hook_y, tab[witchFigure].x + tab[witchFigure].width + 2, hook_h + tab[witchFigure].height + 2);
		InvalidateRect(hWnd, &hookarea1, TRUE); //repaint drawArea
	}


	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

void inputFigure()
{
	for (int i = 0; i < 5; i++) {
		tab[i].x = 220 + 70 * i;
		tab[i].y = 450;
		tab[i].width = 50;
		tab[i].height = 50;
		if (i == 0)
			tab[i].name = 's';
		else
			tab[i].name = 'c';
	}
}


int OnCreate(HWND window)
{
	inputFigure();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Start"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		750, 0,                                  // the left and top co-ordinates
		80, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Up"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		770, 60,                                  // the left and top co-ordinates
		40, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Down"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		770, 100,                                  // the left and top co-ordinates
		40, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON3,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Left"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		720, 100,                                  // the left and top co-ordinates
		40, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON4,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Right"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		820, 100,                                  // the left and top co-ordinates
		40, 30,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Stop"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		750, 150,                                  // the left and top co-ordinates
		80, 40,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON6,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Catch"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		750, 200,                                  // the left and top co-ordinates
		80, 40,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON7,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Release"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		750, 250,                                  // the left and top co-ordinates
		80, 40,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON8,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	// create button and store the handle                                                       

	//hwndButton = CreateWindow(TEXT("button"), TEXT("Timer ON"),
	//	WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
	//	300, 155, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	//hwndButton = CreateWindow(TEXT("button"), TEXT("Timer OFF"),
	//	WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
	//	300, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	bool realiseleftright = FALSE;
	bool realiseleftright_do = FALSE;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		case ID_BUTTON2:
			//hook_h--;
			KillTimer(hWnd, TMR_2);
			//KillTimer(hWnd, TMR_3);
			//KillTimer(hWnd, TMR_4);
			repaintWindow(hWnd, hdc, ps, NULL);
			SetTimer(hWnd, TMR_1, 50, 0);
			break;
		case ID_BUTTON3:
			//hook_h++;
			KillTimer(hWnd, TMR_1);
			//KillTimer(hWnd, TMR_3);
			//KillTimer(hWnd, TMR_4);
			repaintWindow(hWnd, hdc, ps, NULL);
			SetTimer(hWnd, TMR_2, 50, 0);
			break;
		case ID_BUTTON4:
			//hook_w--;
			//hook_x--;
			//KillTimer(hWnd, TMR_1);
			//KillTimer(hWnd, TMR_2);
			KillTimer(hWnd, TMR_4);
			repaintWindow(hWnd, hdc, ps, NULL);
			SetTimer(hWnd, TMR_3, 50, 0);
			break;
		case ID_BUTTON5:
			//hook_w++;
			//hook_x++;
			//KillTimer(hWnd, TMR_1);
			//KillTimer(hWnd, TMR_2);
			KillTimer(hWnd, TMR_3);
			repaintWindow(hWnd, hdc, ps, NULL);
			SetTimer(hWnd, TMR_4, 50, 0);
			break;
		case ID_BUTTON6:					// zastopowanie timerow wszystkich i dzialania wyciagu dzwigu
			killtime(hWnd);
			//KillTimer(hWnd, TMR_5);
			break;
		case ID_BUTTON7:
			killtime(hWnd);
			repaintWindow(hWnd, hdc, ps, NULL);
			catchCheck();							// sprawdzenie czy mozna podniesc
			if (podnoszony == TRUE)
				SetTimer(hWnd, TMR_6, 50, 0);
			//KillTimer(hWnd, TMR_6);
			break;
		case ID_BUTTON8:							// opuszczneie ladunku
			repaintWindow(hWnd, hdc, ps, NULL);
			if (!treeCircle()) {
				podnoszony = FALSE;
				SetTimer(hWnd, TMR_5, 50, 0);
			}
			else
				podnoszony = TRUE;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea1);
			hook_h--;		
			if (hook_h <= 90)
				KillTimer(hWnd, TMR_1);
			if (podnoszony == TRUE) {
				tab[witchFigure].y--;
			}
			break;
		case TMR_2:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			hook_h++;		
			if(hook_h >= 500 || hook_h >= hookHeightCheck())
				KillTimer(hWnd, TMR_2);
			if (podnoszony == TRUE) {
				tab[witchFigure].y++;
			}
			break;
		case TMR_3:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			hook_w--;
			hook_x--;
			if(hook_w <= 200 || hookLeftCheck())
				KillTimer(hWnd, TMR_3);
			if (podnoszony == TRUE && !figureLeftCheck(hWnd, witchFigure)) {
				tab[witchFigure].x--;
			}
			break;
		case TMR_4:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea4);
			hook_w++;
			hook_x++;
			if (hook_w >= 650 || hookRightCheck())
				KillTimer(hWnd, TMR_4);
			if (podnoszony == TRUE && !figureRightCheck(hWnd, witchFigure)) {
				tab[witchFigure].x++;
			}
			break;
		case TMR_5:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea5);
			killtime(hWnd);
			if(tab[witchFigure].y >= releaseCheck())
				KillTimer(hWnd, TMR_5);
			else {
				//SetTimer(hWnd, TMR_7, 50, 0);
				int w;
				int mid;
				for (int i = 0; i < 5; i++) {
					if ((hook_x + 25 > tab[i].x) && (hook_x - 25 < tab[i].x + tab[i].width) && i != witchFigure) {
						w = i;
						realiseleftright = TRUE;
					}
				}
				if (realiseleftright) {
					mid = tab[w].x + tab[w].width / 2; //srodek figury na ziemi
				//repaintWindow(hWnd, hdc, ps, &drawArea4);
					if (hook_x - 1 > mid) {
						hook_w--;
						hook_x--;
						tab[witchFigure].x--;
					}
					else if (hook_x + 1 < mid) {
						hook_x++;
						hook_w++;
						tab[witchFigure].x++;
					}
					else {
						realiseleftright_do = TRUE;
						//KillTimer(hWnd, TMR_7);
					}
				}
			}
			if ((realiseleftright_do || !realiseleftright)) {
				hook_h++;
				tab[witchFigure].y++;
			}
			realiseleftright = FALSE;
			break;
		case TMR_6:
			repaintWindow(hWnd, hdc, ps, &drawArea3);
			killtime(hWnd);
			int mid;
			mid = tab[witchFigure].x + tab[witchFigure].width / 2; //srodek figury wybranej
			if (hook_x != mid) {
				if (hook_x > mid) {
					hook_w--;
					hook_x--;
				}
				if (hook_x < mid){
					hook_x++;
					hook_w++;
				}
			}
			else
				KillTimer(hWnd, TMR_6);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void catchCheck() {
	for (int i = 0; i < 5; i++)
		if ((hook_x > tab[i].x) && (hook_x < tab[i].x + tab[i].width) && (hook_h == tab[i].y))
			if (tab[i].name == 'c') {
				podnoszony = TRUE;
				witchFigure = i;
			}
}

int hookHeightCheck() {
	int hookxMAX = 500;
	int ile = 0;
	for (int i = 0; i < 5; i++)
		if ((hook_x > tab[i].x) && (hook_x < tab[i].x + tab[i].height))
			ile++;
	hookxMAX -= 50 * ile;
	return hookxMAX;
}

bool hookLeftCheck() {
	for (int i = 0; i < 5; i++)
		if ((hook_h > tab[i].y) && (hook_x == tab[i].x + tab[i].width))
			return TRUE;
	return FALSE;
}

bool hookRightCheck() {
	for (int i = 0; i < 5; i++)
		if ((hook_h > tab[i].y) && (hook_x == tab[i].x))
			return TRUE;
	return FALSE;
}

bool figureLeftCheck(HWND hWnd1, int f) {
	for (int i = 0; i < 5; i++)
		if (i != f && (tab[f].y + tab[f].height > tab[i].y) && (tab[f].x == tab[i].x + tab[i].width)){
			podnoszony = FALSE;
			SetTimer(hWnd1, TMR_5, 50, 0);
			return TRUE;
		}
	return FALSE;
}

bool figureRightCheck(HWND hWnd1, int f) {
	for (int i = 0; i < 5; i++)
		if (i != f && (tab[f].y + tab[f].height > tab[i].y) && (tab[f].x + tab[f].width == tab[i].x)) {
			podnoszony = FALSE;
			SetTimer(hWnd1, TMR_5, 50, 0);
			return TRUE;
		}	
	return FALSE;
}


int releaseCheck() {
	int MAX = 500;
	int ile = 0;
	int x = tab[witchFigure].x + tab[witchFigure].width / 2;
	for (int i = 0; i < 5; i++)
		if ((x > tab[i].x) && (x < tab[i].x + tab[i].height))
			ile++;
	MAX -= 50 * ile;
	return MAX-1;
}

bool treeCircle() {
	int ile = 0;
	for (int i = 0; i < 5; i++)
		if ((hook_x + 25 > tab[i].x) && (hook_x - 25 < tab[i].x + tab[i].height))
			ile++;
	if (ile == 4)
		return TRUE;
	else
		return FALSE;
}

bool realisebetween() {
	for (int i = 0; i < 5; i++)
		if (i != witchFigure && (hook_x + 25 > tab[i].x && hook_x + 25 < tab[i].x + tab[i].width) && podnoszony)
			return TRUE;
	return FALSE;
}

void killtime(HWND hWnd1) {
	KillTimer(hWnd1, TMR_1);
	KillTimer(hWnd1, TMR_2);
	KillTimer(hWnd1, TMR_3);
	KillTimer(hWnd1, TMR_4);
}