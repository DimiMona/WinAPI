#undef UNICODE
#include <Windows.h>

CONST CHAR g_sz_CLASS_NAME[] = "Main Window PV=522";//Name Class window

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	/*
	___________________________________________________
	hInstance - это экземпляр *.exe - файла нашей программы, загруженный в ОЗУ
	hPrevInst - предыдущий загруженный экземпляр. В современных ОС Windosw этот параметр не используется;
	LPSTR  - LongPointer to STRing;
	ipCmdLine - это командная строка, с которой запустилась программа. При запуске без параметров
				в lpCmdLine хранится только имя исполняемого файла программы.
				Через этот параметр в программу можно передать начальные данные.
				Например : в текстовый редактор - имя открываемого файла, в браузер, URL открываемого ресурса,
				в проигрыватель - файл с фильмом или музыкой.
	nCmdShow - режим отображения окна: развернуто на весь экран, свернуто на панель
	___________________________________________________
	Главное окно программы

	Главное окно любой программы создается в 3 этапа:
	1.	Регистрация класса окна:
	1.1) Объявить имя класса окна;
	1.2) Создать и проинициализщировать экземпляр структуры WNDCLASSEX;
	*/
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass)); // обнуляет память
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0; //cb Bytes;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL; //Главное меню
	wClass.lpszClassName = g_sz_CLASS_NAME;
	wClass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Ошибка при регистрации класса", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	/*
	2.	Создание окна:
	*/
	HWND hwnd = CreateWindowEx
	(
		NULL,// exStyles
		g_sz_CLASS_NAME,//ClassName
		g_sz_CLASS_NAME, // Window title
		WS_OVERLAPPEDWINDOW,// Стиль окна. Набор стилей всегда зависит от класса окна
		//Стиль главного окна ЦWS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT, // Начальная позиция окна (при запуске)
		CW_USEDEFAULT, CW_USEDEFAULT, //Размер окна
		NULL,	// Parent Window
		NULL,	//hMenu. Для главного окна этот определяет главное меню.
		//		Для дочернего окна (Control)  это параметр содержит ResourseID дочернего окна.
		// Блягодоря hMenu, дочернее окно всегда можно найти при помощи функции GetDlgItem()
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
			return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	/*
	3.	Запуск цикла сообщений:
	*/
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;

}