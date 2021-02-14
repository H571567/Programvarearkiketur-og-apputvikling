// Oblig2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Oblig2.h"
#include <vector>
#include <tuple>
#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
typedef std::tuple <int, int, int> car;
static std::vector<car> cars;
static int pw, pn;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    selectProb(HWND, UINT, WPARAM, LPARAM);
void                drawLight(HDC, int, int, int,int, int);
void                drawCar(HDC, int, int, int);
void                updateCar(int, int,int, int);
void                deleteCars();
void                handleStop(int);
int                 getCarState(int, int, int, int);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OBLIG2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBLIG2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBLIG2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBLIG2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int light = 1;
    static int timer = 1;
    
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
    {
        switch (wParam)
        {
        case 1:
        {
            if (light < 4)
            {
                light++;
            }
            else
            {
                light = 1;
            }
            timer = 1;
            //InvalidateRect(hWnd, 0, true);
        }
        break;
        case 2:
        {
            timer = 2;
            
            
            InvalidateRect(hWnd, 0, true);
        }
        break;
        case 3:
        {
            if (rand() % 100 < pw)
            {
                int i = cars.size()-1;
                bool found = false;
                while (!found && i >= 0)
                {
                    if (std::get<1>(cars[i]) <= 70)
                    {

                        found = true;
                    }
                    i--;
                }
                if (!found)
                {
                    cars.push_back(std::make_tuple(1, 50, 310));
                }                           
            }
            if (rand() % 100 < pn)
            {
                int i = cars.size() - 1;
                bool found = false;
                while (!found && i >= 0)
                {
                    if (std::get<2>(cars[i]) <= 40)
                    {
                        found = true;
                    }
                    i--;
                }
                if (!found)
                {
                    cars.push_back(std::make_tuple(2, 510, 10));
                }
            }
            InvalidateRect(hWnd, 0, true);
        }
        break;
        }
       
    }
    break;
    case WM_CREATE:
    {
        //open dialogbox and get pw and pn
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, selectProb);
        SetTimer(hWnd, 1, 2000, 0);
        SetTimer(hWnd, 2, 200, 0);
        SetTimer(hWnd, 3, 1000, 0);

    }
    break;
    case WM_KEYDOWN:
    {
        //increase cars from west
        if (wParam == VK_RIGHT)
        {
           
            if (pw <= 90)
            {
                pw += 10;
            }
            else
            {
                pw = 100;
            }
        }
        //decrease cars from west
        else if (wParam == VK_LEFT)
        {
            if (pw >= 10)
            {
                pw -= 10;
            }
            else
            {
                pw = 0;
            }
        }
        //increase cars from north
        else if (wParam == VK_UP)
        {
            if (pn <= 90)
            {
                pn += 10;
            }
            else
            {
                pn = 100;
            }
        }
        //decrease cars from north
        else if (wParam == VK_DOWN)
        {
            if (pn >= 10)
            {
                pn -= 10;
            }
            else
            {
                pn = 0;
            }
        }
    }
    break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        WCHAR sz[100];

        HBRUSH hbGray = CreateSolidBrush(RGB(105, 105, 105));
        HBRUSH hbDark = CreateSolidBrush(RGB(90, 90, 90));
        HGDIOBJ hOrg = SelectObject(hdc, hbGray);

        RECT client;
        GetClientRect(hWnd, &client);

        wsprintf(sz, _T("PW: %d PN: %d"), pw, pn);
        TextOut(hdc, 10, 10, sz, wcslen(sz));

        //North
        Rectangle(hdc, 500, 10, 550, 300);
        //South
        Rectangle(hdc, 500, 350, 550, 680);
        //West
        Rectangle(hdc, 50, 300, 500, 350);
        //East
        Rectangle(hdc, 550, 300, 1000, 350);
        //Middle
        SelectObject(hdc, hbDark);
        Rectangle(hdc, 500, 300, 550, 350);

        SelectObject(hdc, hOrg);
        DeleteObject(hbGray);
        DeleteObject(hbDark);

        //Light for west
        drawLight(hdc, light, 400, 150, 50, 130);
        //Light for north
        drawLight(hdc, ((light + 1) % 4) + 1, 600, 400, 50, 130);

        deleteCars();

        if (timer == 2)
        {
            //check for collision and update positions
            handleStop(light);
            for (int i = 0; i < cars.size(); i++)
            {
                drawCar(hdc, std::get<0>(cars[i]), std::get<1>(cars[i]), std::get<2>(cars[i]));
            } 
        } 
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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

INT_PTR CALLBACK selectProb(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        HWND strCtrl = GetDlgItem(hDlg, IDC_STATIC);
        SetWindowText(strCtrl, L"Probability for cars from west 'pw' \n\n\n Probability for cars from north 'pn'");
        
        return (INT_PTR)TRUE;
    }
    break;
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            HWND handle = GetDlgItem(hDlg, IDC_EDIT1);
            BOOL isNum = false;
            int a = GetDlgItemInt(hDlg, IDC_EDIT1, &isNum, true);
            int b = GetDlgItemInt(hDlg, IDC_EDIT2, &isNum, true);
            if (isNum)
            {
                pw = a;
                pn = b;
            }


            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
    }
    
}

/**
* Draws a traffic light
params: HDC hdc: decive context
        int state: state of light
        int x/y: x-position / y-position
        int width/height: size of traffic light
*/
void drawLight(HDC hdc, int state, int x, int y, int width, int height)
{

    //Black rectangle
    HBRUSH hbBlack = CreateSolidBrush(RGB(0, 0, 0));
    HGDIOBJ hOrg = SelectObject(hdc, hbBlack);
    Rectangle(hdc, x, y, x+width, y+height);
    SelectObject(hdc, hOrg);
    DeleteObject(hbBlack);

    switch (state)
    {
    case 1:
    {
        //red ellipse
        HBRUSH hbRed = CreateSolidBrush(RGB(255, 0, 0));
        hOrg = SelectObject(hdc, hbRed);
        Ellipse(hdc, x+10, y+10, x+width-10, y+(height/3)-5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbRed);

        //gray ellipse
        HBRUSH hbGray = CreateSolidBrush(RGB(105, 105, 105));
        hOrg = SelectObject(hdc, hbGray);
        Ellipse(hdc, x + 10, y + (height / 3)+5, x + width - 10, y + 2*(height / 3)-5);
        Ellipse(hdc, x + 10, y + 2*(height / 3)+5, x + width - 10, y+height-5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbGray);
    }
    break;
    case 2:
    {
        //red ellipse
        HBRUSH hbRed = CreateSolidBrush(RGB(255, 0, 0));
        hOrg = SelectObject(hdc, hbRed);
        Ellipse(hdc, x + 10, y + 10, x + width - 10, y + (height / 3) - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbRed);

        //yellow ellipse
        HBRUSH hbYellow = CreateSolidBrush(RGB(255, 255, 0));
        hOrg = SelectObject(hdc, hbYellow);
        Ellipse(hdc, x + 10, y + (height / 3) + 5, x + width - 10, y + 2 * (height / 3) - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbYellow);

        //gray ellipse
        HBRUSH hbGray = CreateSolidBrush(RGB(105, 105, 105));
        hOrg = SelectObject(hdc, hbGray);
        Ellipse(hdc, x + 10, y + 2 * (height / 3) + 5, x + width - 10, y + height - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbGray);
    }
    break;
    case 3:
    {
        //gray ellipse
        HBRUSH hbGray = CreateSolidBrush(RGB(105, 105, 105));
        hOrg = SelectObject(hdc, hbGray);
        Ellipse(hdc, x + 10, y + 10, x + width - 10, y + (height / 3) - 5);
        Ellipse(hdc, x + 10, y + (height / 3) + 5, x + width - 10, y + 2 * (height / 3) - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbGray);

        //green ellipse
        HBRUSH hbGreen = CreateSolidBrush(RGB(0, 255, 0));
        hOrg = SelectObject(hdc, hbGreen);
        Ellipse(hdc, x + 10, y + 2 * (height / 3) + 5, x + width - 10, y + height - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbGreen);
    }
    break;
    case 4:
    {
        //gray ellipse
        HBRUSH hbGray = CreateSolidBrush(RGB(105, 105, 105));
        hOrg = SelectObject(hdc, hbGray);
        Ellipse(hdc, x + 10, y + 10, x + width - 10, y + (height / 3) - 5);
        Ellipse(hdc, x + 10, y + 2 * (height / 3) + 5, x + width - 10, y + height - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbGray);

        //yellow ellipse
        HBRUSH hbYellow = CreateSolidBrush(RGB(255, 255, 0));
        hOrg = SelectObject(hdc, hbYellow);
        Ellipse(hdc, x + 10, y + (height / 3) + 5, x + width - 10, y + 2 * (height / 3) - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbYellow);
    }
    break;
    default:
        //red ellipse
        HBRUSH hbRed = CreateSolidBrush(RGB(255, 0, 0));
        hOrg = SelectObject(hdc, hbRed);
        Ellipse(hdc, x + 10, y + 10, x + width - 10, y + (height / 3) - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbRed);

        //gray ellipse
        HBRUSH hbGray = CreateSolidBrush(RGB(105, 105, 105));
        hOrg = SelectObject(hdc, hbGray);
        Ellipse(hdc, x + 10, y + (height / 3) + 5, x + width - 10, y + 2 * (height / 3) - 5);
        Ellipse(hdc, x + 10, y + 2 * (height / 3) + 5, x + width - 10, y + height - 5);
        SelectObject(hdc, hOrg);
        DeleteObject(hbGray);
        break;
    }

}

/*
* Draws a car in position <x,y> in the direction dir (1:from west, 2:from north)
*/
void drawCar(HDC hdc, int dir, int x, int y)
{
    switch (dir)
    {
    //From West
    case 1:
    {
        HBRUSH hbBlue = CreateSolidBrush(RGB(0, 0, 255));
        HGDIOBJ hOrg = SelectObject(hdc, hbBlue);

        Rectangle(hdc, x, y, x+30, y+15);



        SelectObject(hdc, hOrg);
        DeleteObject(hbBlue);
    }
    break;
    //From North
    case 2:
    {
        HBRUSH hbBlue = CreateSolidBrush(RGB(0, 0, 255));
        HGDIOBJ hOrg = SelectObject(hdc, hbBlue);

        Rectangle(hdc, x, y, x+15, y+30);



        SelectObject(hdc, hOrg);
        DeleteObject(hbBlue);
    }
    break;
    default:
    {
        HBRUSH hbBlue = CreateSolidBrush(RGB(0, 0, 255));
        HGDIOBJ hOrg = SelectObject(hdc, hbBlue);

        Rectangle(hdc, x, y, x+20, y+10);



        SelectObject(hdc, hOrg);
        DeleteObject(hbBlue);
    }
    }
}

/*
* Moves the postion of the car if the car is not between pos x and pos y when light is not green
*/
void updateCar(int light, int index, int x, int y)
{

    switch (std::get<0>(cars[index]))
    {
        case 1:
        {
            int pos = std::get<1>(cars[index]);
            if (pos >= x && pos < x + 20 && light != 3)
            {
                //dont update
            }
            else
            {
                std::get<1>(cars[index]) += 20;
            }

        }
        break;
        case 2:
        {
            int pos = std::get<2>(cars[index]);
            if (pos >= y && pos < y + 20 && ((light + 1) % 4) + 1 != 3)
            {
               
            }
            else
            {
                std::get<2>(cars[index]) += 20;
            }
            
        }
        break;
    }
}

/*
* returns if the car is stopped, redundant method..
*/
int getCarState(int light, int index, int x, int y)
{
    switch (std::get<0>(cars[index]))
    {
    case 1:
    {
        int pos = std::get<1>(cars[index]);
        if (pos >= x && pos < x + 20 && light != 3)
        {
            return 1;
 
        }
        else
        {
            return 0;
        }
    }
    break;
    case 2:
    {
        int pos = std::get<2>(cars[index]);
        if (pos >= y && pos < y + 20 && ((light + 1) % 4) + 1 != 3)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    break;
    }
}

//Delete car if pos is outside the road
void deleteCars()
{
    if (cars.size() >= 1)
    {
        if (std::get<0>(cars[0]) == 1 && std::get<1>(cars[0]) >= 800)
        {
            cars.erase(cars.begin() + 0);
        }
        else if (std::get<0>(cars[0]) == 2 && std::get<2>(cars[0]) >= 600)
        {
            cars.erase(cars.begin() + 0);
        }
    }
}
//Crash logic
void handleStop(int light)
{
    bool wFin = false;    //found car from west that is stopped
    bool nFin = false;    // found car from north that is stopped
    int i = 0;
    while(!nFin && !wFin && i<cars.size())
    {
        int state = getCarState(light, i, 470, 270);
        updateCar(light, i, 470, 270);
        if (state == 1)
        {
            wFin = true;  
            int n = 1;
            bool m = false;
            for (int j = i+1; j < cars.size(); j++)
            {
                if (std::get<0>(cars[j]) == 1)
                {
                    updateCar(light, j, 470 - (40 * n), 270);
                    n++;
                }
                else
                {
                    if(getCarState(light, j, 470, 270) == 2 && !m)
                    {
                        m = true;
                        int v = 1;
                        for (int k = j + 1; k < cars.size(); k++)
                        {
                            if (std::get<0>(cars[k]) == 2)
                            {
                                updateCar(light, k, 470, 270 - (40 * v));
                                v++;
                            }
                        }
                    }
                    else if(!m)
                    {
                        updateCar(light, j, 470, 270);
                    }
                    
                }
            }

        }
        else if (state == 2)
        {
            nFin = true;
            int n = 1;
            bool m = false;
            for (int j = i+1; j < cars.size(); j++)
            {
                if (std::get<0>(cars[j]) == 2)
                {
                    updateCar(light, j, 470, 270 - (40 * n));
                    n++;
                }
                else
                {
                    if (getCarState(light, j, 470, 270) == 1 && !m )
                    {
                        m = true;
                        int v = 1;
                        for (int k = j + 1; k < cars.size(); k++)
                        {
                            if (std::get<0>(cars[k]) == 1)
                            {
                                updateCar(light, k, 470 - (40 * v), 270);
                                v++;
                            }
                        }
                    }
                    else if(!m)
                    {
                        updateCar(light, j, 470, 270);
                    }
                }
            }
        }
        else
        {
        }
        i++;
    }

}