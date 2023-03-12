#include<Windows.h>
#include"resource.h"

CONST CHAR g_szClassName[] = "MyWindowClass";

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_INTERVAL = 2;
CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4;
CONST INT g_i_DISPLAY_HEIGHT = 25;
CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 3.6;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y * 5.9 + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;

//g_i_ - Global constant of type 'int'

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "yacht.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//http://www.rw-designer.com/cursor-set/starcraft-original
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "start.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hIcon = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_HDD));
	//wc.hIconSm = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_FDD));
	wc.hInstance = hInstance;	//Задаем экземпляр *.exe-файла
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,				//exStyle - расширенный стиль окна
		g_szClassName,		//имя класса окна
		g_szClassName,		//Заголовок окна
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,//Стиль окна (обыное окно, диалоговое окно, кнопка, текстовое поле, и т.д.)
		CW_USEDEFAULT, CW_USEDEFAULT,//Начальные координаты окна (левого верхнего угла окна)
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,//Размер окна
		//Начальные координаты и размер окна всегда задаются в пикселах
		NULL,	//Родительское окно отсутствует (как всегда бывает у WS_OVERLAPPEDWINDOW)
		NULL,	//Строка меню отсутсвует
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//Задаем режим отображения окна (свернуто в окно, развернуто на весь экран, свернуто на панель задач...)
	UpdateWindow(hwnd);			//Прорисовывает содержимое окна

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE | ES_RIGHT | ES_READONLY,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd, (HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		INT i_digit = 0;
		CHAR sz_digit[2] = {};
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				i_digit = i * 3 + j;
				sz_digit[0] = '0' + i_digit + 1;
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL)*j,
					g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(3 - i - 1),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd, (HMENU)(IDC_BUTTON_1 + i_digit),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_BUTTON_SIZE * 3 + g_i_INTERVAL * 4,
			g_i_BUTTON_SIZE * 2 + g_i_INTERVAL, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 2, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_BUTTON_SIZE * 3 + g_i_INTERVAL * 4,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		////////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "/",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_SLASH,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "*",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL * 2 + g_i_BUTTON_SIZE,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_ASTER,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "-",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL * 3 + g_i_BUTTON_SIZE * 2,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_MINUS,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "+",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL * 4 + g_i_BUTTON_SIZE * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd, (HMENU)IDC_BUTTON_PLUS,
			GetModuleHandle(NULL), NULL
		);
		/////////////////////////////////////////////////
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE * 2 + g_i_INTERVAL,
			hwnd, (HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL), NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILDWINDOW | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4, g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL * 3 + g_i_BUTTON_SIZE * 2,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE * 2 + g_i_INTERVAL,
			hwnd, (HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL), NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		CHAR sz_symbol[2] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9/* || LOWORD(wParam) == IDC_BUTTON_POINT*/)
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			sz_symbol[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			strcat(sz_buffer, sz_symbol);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_POINT:
		{
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (strchr(sz_buffer, '.'))break;
			strcat(sz_buffer, ".");
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDC_BUTTON_CLEAR:SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0"); break;
		}
	}
	break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:
		switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Question", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES: DestroyWindow(hwnd);
		case IDNO:break;
		}
		break;	//Посылает сообщение WM_DESTROY
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

/*
-----------------
	CreateWindow
	CreateWindowEx
-----------------
*/