#include<Windows.h>
#include"resource.h"

CONST CHAR g_szClassName[] = "MyWindowClass";

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
		WS_OVERLAPPEDWINDOW,//Стиль окна (обыное окно, диалоговое окно, кнопка, текстовое поле, и т.д.)
		CW_USEDEFAULT, CW_USEDEFAULT,//Начальные координаты окна (левого верхнего угла окна)
		CW_USEDEFAULT, CW_USEDEFAULT,//Размер окна
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
	case WM_CREATE:break;
	case WM_COMMAND:break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_CLOSE:DestroyWindow(hwnd); break;	//Посылает сообщение WM_DESTROY
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}