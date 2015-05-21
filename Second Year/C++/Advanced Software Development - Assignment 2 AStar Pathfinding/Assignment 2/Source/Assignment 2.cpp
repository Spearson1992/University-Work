// Assignment 2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Assignment 2.h"
#include "Astar\Map.h"
#include <windowsx.h>
#include <CommDlg.h>
//#include "resource.h"

//#include <vld.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

AStar::AStar *asGrid;
HBITMAP gridImages[6];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, HWND &);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK EditGrid(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
#pragma region WinMain
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
    HWND parentHWnd;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ASSIGNMENT2, szWindowClass, MAX_LOADSTRING);

    if(!MyRegisterClass(hInstance))
    {
        DWORD error = GetLastError();
        return false;
    }
	// Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow, parentHWnd))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT2));
    

    
	// Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}
#pragma endregion


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ASSIGNMENT2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND &hWnd)
{

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

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
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
#pragma region WindProc
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
        case ID_FILE_EDITGRID:
            CreateDialog(hInst, MAKEINTRESOURCE(IDD_GRIDOPTIONS),hWnd, EditGrid);
                
            break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
    case WM_LBUTTONDOWN:
        {
            if(wParam & MK_SHIFT) 
            {
                POINT cursorPos;
                if(GetCursorPos(&cursorPos))
                {
                    if(ScreenToClient(hWnd, &cursorPos))
                    {
                        AStar::Node *t = asGrid->GetNode((cursorPos.y /32) * asGrid->GetColumns() + (cursorPos.x / 32));
                            if(asGrid->GetStart())
                            {
                                asGrid->GetStart()->SetType((AStar::Node::NodeType) 1);
                            }
                            else if(asGrid->GetGoal() == t)
                            {
                                asGrid->SetGoal(NULL);
                            }
                            t->SetType(AStar::Node::NodeType::Start); // set start node
                            
                            
                        asGrid->SetStart(t);
                        asGrid->CalculatePath();
                        InvalidateRect(hWnd,NULL,TRUE);
                    
                    }
                }
            }
            else
            {
                POINT cursorPos;
                if(GetCursorPos(&cursorPos))
                {
                    if(ScreenToClient(hWnd, &cursorPos))
                    {
                        AStar::Node *t = asGrid->GetNode((cursorPos.y /32) * asGrid->GetColumns() + (cursorPos.x / 32));
                        t->SetType(AStar::Node::NodeType::Walkable);//set walkable
                            if(asGrid->GetStart() == t)
                            {
                                asGrid->SetStart(NULL);
                            }
                            else if(asGrid->GetGoal() == t)
                            {
                                asGrid->SetGoal(NULL);
                            }
                        InvalidateRect(hWnd,NULL,TRUE);
                    
                    }
                }
            }
        }
        break;
    case WM_RBUTTONDOWN:
        if(wParam & MK_SHIFT)
        {
        POINT cursorPos;
            if(GetCursorPos(&cursorPos))
            {
                if(ScreenToClient(hWnd, &cursorPos))
                {
                    AStar::Node *t = asGrid->GetNode((cursorPos.y /32) * asGrid->GetColumns() + (cursorPos.x / 32));
                    
                        if(asGrid->GetGoal())
                        {
                            asGrid->GetGoal()->SetType((AStar::Node::NodeType) 1);
                        }                        
                        if(asGrid->GetStart() == t)
                        {
                            asGrid->SetStart(NULL);
                        }
                        t->SetType(AStar::Node::NodeType::Goal);//set goal
                        asGrid->SetGoal(t);
                    InvalidateRect(hWnd,NULL,TRUE);
                    asGrid->CalculatePath();
                }
            }
        }
        else
        {
            POINT cursorPos;
            if(GetCursorPos(&cursorPos))
            {
                if(ScreenToClient(hWnd, &cursorPos))
                {
                    AStar::Node *t = asGrid->GetNode((cursorPos.y /32) * asGrid->GetColumns() + (cursorPos.x / 32));
                    t->SetType(AStar::Node::NodeType::Wall);//set wall
                        if(asGrid->GetStart() == t)
                            {
                                asGrid->SetStart(NULL);
                            }
                        else if(asGrid->GetGoal() == t)
                        {
                            asGrid->SetGoal(NULL);
                        }
                    InvalidateRect(hWnd,NULL,TRUE);
                    
                }
            }
        }
        break;
    case WM_CREATE:
        asGrid = new AStar::AStar(10,10);/*
        for(int i = 0; i < asGrid->GetSize(); i++)
        {
            asGrid->GetNode(i)->SetCost(i);
        }*/
        /////////////////////////////////////////////////////////////////
        //                  Resize Window on startup                  //
        ///////////////////////////////////////////////////////////////
        RECT rc;
        GetClientRect(hWnd, &rc);
        rc.bottom = asGrid->GetColumns() *32;
        rc.right = asGrid->GetRows() *32;
        AdjustWindowRectEx(&rc,GetWindowStyle(hWnd),TRUE, GetWindowExStyle(hWnd));
        rc.bottom -= rc.top;
        rc.right -= rc.left;
        SetWindowPos(hWnd,0,0,0,rc.right,rc.bottom,SWP_NOMOVE);
        /////////////////////////////////////////////////////////////////
        
        ////////////////////////////////////////////////////////////////
        //               Initialise image brush array                //
        //////////////////////////////////////////////////////////////
        gridImages[0] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_WALL));
        gridImages[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WALKABLE));
        gridImages[2] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_START));
        gridImages[3] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GOAL));
        gridImages[4] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_PATH));
        gridImages[5] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_CHECKED));
        //////////////////////////////////////////////////////////////
        break;
	case WM_PAINT:
        {
            
            BITMAP bm;
		    hdc = BeginPaint(hWnd, &ps);
            HDC hdcMem = CreateCompatibleDC(hdc);
            HGDIOBJ old = SelectObject(hdcMem,gridImages[1]);
            

            for(int i = 0; i < asGrid->GetRows(); i++)
            {
                for(int j = 0; j < asGrid->GetColumns(); j++)
                {
                    SelectObject(hdcMem,gridImages[(int)asGrid->GetNode(i * asGrid->GetColumns() + j)->GetType()]);
                    GetObject(gridImages[(int)asGrid->GetNode(i * asGrid->GetColumns() + j)->GetType()],sizeof(bm),&bm);
                    BitBlt(hdc, j*bm.bmWidth, i*bm.bmHeight, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
                    SelectObject(hdcMem,old);
                }
            }
            SelectObject(hdcMem, old);
            DeleteDC(hdcMem);
		    // TODO: Add any drawing code here...
		    EndPaint(hWnd, &ps);
        }
		break;
	case WM_DESTROY:
        DeleteObject(gridImages[0]);
        DeleteObject(gridImages[1]);
        DeleteObject(gridImages[2]);
        DeleteObject(gridImages[3]);
        DeleteObject(gridImages[4]);
        DeleteObject(gridImages[5]);
        if(asGrid)
            delete asGrid;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
#pragma endregion

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

INT_PTR CALLBACK EditGrid(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
            RECT rcParent;
            RECT rcDialog;
            GetClientRect(GetParent(hDlg), &rcParent);
            GetClientRect(hDlg, &rcDialog);
            if(rcParent.bottom < rcDialog.bottom ||
                rcParent.right < rcDialog.right)
            {
                rcParent.bottom = rcDialog.bottom;
                rcParent.right = rcDialog.right;
                AdjustWindowRectEx(&rcParent,GetWindowStyle(GetParent(hDlg)),TRUE, GetWindowExStyle(GetParent(hDlg)));
                rcParent.bottom -= rcParent.top;
                rcParent.right -= rcParent.left;
                SetWindowPos(GetParent(hDlg),0,0,0,rcParent.right,rcParent.bottom,SWP_NOMOVE);
                InvalidateRect(GetParent(hDlg),NULL,TRUE);
            }
            else if(rcParent.bottom < rcDialog.bottom)
            {
                rcParent.bottom = rcDialog.bottom;
                AdjustWindowRectEx(&rcParent,GetWindowStyle(GetParent(hDlg)),TRUE, GetWindowExStyle(GetParent(hDlg)));
                rcParent.bottom -= rcParent.top;
                rcParent.right -= rcParent.left;
                SetWindowPos(GetParent(hDlg),0,0,0,rcParent.right,rcParent.bottom,SWP_NOMOVE);
                InvalidateRect(GetParent(hDlg),NULL,TRUE);
            }
            else if(rcParent.right < rcDialog.right)
            {
                rcParent.right = rcDialog.right;
                AdjustWindowRectEx(&rcParent,GetWindowStyle(GetParent(hDlg)),TRUE, GetWindowExStyle(GetParent(hDlg)));
                rcParent.bottom -= rcParent.top;
                rcParent.right -= rcParent.left;
                SetWindowPos(GetParent(hDlg),0,0,0,rcParent.right,rcParent.bottom,SWP_NOMOVE);
                InvalidateRect(GetParent(hDlg),NULL,TRUE);
            }
            
            return (INT_PTR) TRUE;

    case WM_COMMAND:
        if(LOWORD(wParam) == IDC_MAKE)
        {
            
            delete asGrid;
            asGrid = 0;
            int rows = GetDlgItemInt(hDlg,IDC_ROWS,NULL,0);
            int columns = GetDlgItemInt(hDlg,IDC_COLUMNS,NULL,0);
            if(rows == 0)
                rows = 1;
            if (columns == 0)
                columns =1;
            asGrid = new AStar::AStar(columns,rows);
            for(int i = 0; i < asGrid->GetSize(); i++)
            {
                asGrid->GetNode(i)->SetType((AStar::Node::NodeType) 1);
            }
            //repaint window and resize
            RECT rcParent;
            GetClientRect(GetParent(hDlg), &rcParent);
            rcParent.right = columns*32;
            rcParent.bottom = rows*32;
            AdjustWindowRectEx(&rcParent,GetWindowStyle(GetParent(hDlg)),TRUE, GetWindowExStyle(GetParent(hDlg)));
            rcParent.bottom -= rcParent.top;
            rcParent.right -= rcParent.left;
            SetWindowPos(GetParent(hDlg),0,0,0,rcParent.right,rcParent.bottom,SWP_NOMOVE);
            InvalidateRect(GetParent(hDlg),NULL,TRUE);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR) TRUE;
        }
        else if(LOWORD(wParam) == IDC_SAVE)
        {
            wchar_t file[MAX_PATH];
            if(GetDlgItemText(hDlg, IDC_FILE,file,MAX_PATH))
                asGrid->Save(file);
            return (INT_PTR) TRUE;
        }
        else if(LOWORD(wParam) == IDC_LOAD)
        {
            wchar_t file[MAX_PATH];
            if(GetDlgItemText(hDlg, IDC_FILE,file,MAX_PATH))
            {
                AStar::AStar *temp = asGrid->Load(file);
                if(temp)
                {
                    delete asGrid;
                    asGrid = NULL;
                    asGrid = temp;
                    RECT rcParent;
                    GetClientRect(GetParent(hDlg), &rcParent);
                    rcParent.right = asGrid->GetColumns() *32;
                    rcParent.bottom =  asGrid->GetRows()*32;
                    AdjustWindowRectEx(&rcParent,GetWindowStyle(GetParent(hDlg)),TRUE, GetWindowExStyle(GetParent(hDlg)));
                    rcParent.bottom -= rcParent.top;
                    rcParent.right -= rcParent.left;
                    SetWindowPos(GetParent(hDlg),0,0,0,rcParent.right,rcParent.bottom,SWP_NOMOVE);
                    InvalidateRect(GetParent(hDlg),NULL,TRUE);
                }
            }
            EndDialog(hDlg,(INT_PTR) TRUE);
            return (INT_PTR) TRUE;
        }
        else if(LOWORD(wParam) == IDC_BROWSE)
        {
            wchar_t file[MAX_PATH];
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hDlg;
            ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
	        ofn.lpstrInitialDir = NULL;
	        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            ofn.lpstrFile = file;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrDefExt = L"txt";

            if(GetOpenFileName(&ofn) == TRUE)
            {
                SetDlgItemText(hDlg, IDC_FILE, ofn.lpstrFile);
            }
            return (INT_PTR) TRUE;
        }
            break;
    }
    return (INT_PTR) FALSE;
}