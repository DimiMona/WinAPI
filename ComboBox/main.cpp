#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include<stdio.h>
#include "resource.h"


CONST CHAR* g_sz_VALUES[] = { "This","is","my","first","Combo","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)// проверить сколько строк
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			INT i = SendMessage(hCombo, CB_GETCURSEL,0,0);
			if (i == CB_ERR)
			{
				MessageBox(hwnd, "Вы ничего не выбрали", NULL, MB_OK | MB_ICONERROR);
					break;
			}
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; // создаем 2 переменные
			CHAR sz_message[SIZE] = {};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемент №%i со значением %s", i, sz_buffer);
			MessageBox(hwnd, sz_message, "info", MB_OK | MB_ICONINFORMATION);

		}
		break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);

	}
	return FALSE;
}