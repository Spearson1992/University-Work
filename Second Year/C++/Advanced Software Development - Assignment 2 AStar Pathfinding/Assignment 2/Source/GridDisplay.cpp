
//
//GridDisplay::GridDisplay(int columns, int rows, HINSTANCE hIn)
//    :grid(columns, rows), hInst(hIn){}
//
//GridDisplay::~GridDisplay()
//{}
//
//ATOM GridDisplay::RegisterGrid(HINSTANCE hInstance, LPCWSTR className)
//{
//    WNDCLASS wc;
//
//
//	wc.style			= CS_HREDRAW | CS_VREDRAW;
//    wc.lpszClassName	= className;
//    wc.lpfnWndProc	    = GridProc;
//	wc.hInstance		= hInstance;
//    wc.hbrBackground	= CreateSolidBrush(RGB(230,230,230));
//    wc.hCursor          = LoadCursor(0,IDC_ARROW);
//    wc.hIcon = NULL;
//    wc.lpszMenuName = NULL;
//    wc.cbClsExtra = 0;
//    wc.cbWndExtra = 0;
//    BOOL ret = RegisterClass(&wc);
//	return ret;
//}
//BOOL GridDisplay::InitGrid(HINSTANCE hInstance, int nCmdShow, HWND hParent, LPCWSTR className)
//{
//     HWND hWnd;
//
//   //hInst = hInstance; // Store instance handle in our global variable
//     RECT parentSize;
//     GetClientRect(hParent, &parentSize);
//     hWnd = CreateWindow(className, L"test", WS_CHILD | WS_VISIBLE | WS_BORDER,
//         parentSize.right/6, parentSize.top, parentSize.right - parentSize.right / 6, parentSize.bottom, hParent, NULL, hInstance, NULL);
//
//   if (!hWnd)
//   {
//      DWORD error =  GetLastError();
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//   
//   return TRUE;
//}
////LRESULT CALLBACK GridProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
////{
////    switch (message)
////    {
////    case WM_CREATE:
////        gridImages[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_WALKABLE));
////        gridImages[1] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_WALL));
////        gridImages[2] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_START));
////        gridImages[3] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GOAL));
////        gridImages[4] = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_PATH));
////        break;
////    case WM_LBUTTONUP:
////        Beep(50,40);
////        return 0;
////    default:
////        return DefWindowProc(hWnd,message,wParam,lParam);
////        break;
////    }
////    
////}