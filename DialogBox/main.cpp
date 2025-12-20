#include<Windows.h>
#include"resource.h"
//прототип
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*
* ____________________________________
* Окно, сообщение и параметры сообщения; 
* hwnd - окно;
* uMsg - сообщения;
* wParam, lParam - параметры сообщения;
* ____________________________________
* HWND - Handler to Window (Дескриптор, описатель окна);
* WPARAM, LPARAM  - это сымые обычные значения типа DWORD(INT);
* Эти параметры часто делят на HIWORD и LOWORD;
* ____________________________________
*/
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: //Инициализация окна диалога. Эта секция отрабатывает 1 раз -  при запуске окна.
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON,0,(LPARAM)hIcon);
	}
		break;
	case WM_COMMAND:// в этой секции отрабатываются нажатия кнопок, клавиш и другие события
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND heditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//Функция GetDlgItem() - позволяет получить HWND элемента окна по RESOURSE_ID нужного элемента.
			//RESOURSE_ID - это самое обычнок значение типа "INT"
			//WM_-WindowsMassege (такое сообщение можно отправить любому окну)
			
			SendMessage(heditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);

		}break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK|MB_ICONINFORMATION);break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE://Отрабатывает й раз при закрыти окна
		EndDialog(hwnd, 0);		
	}
	return FALSE;
}

