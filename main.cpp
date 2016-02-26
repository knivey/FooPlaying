#include <iostream>
#include <windows.h>
#include <malloc.h>
#include <cstring>

using namespace std;

int ewcb(HWND hWin, LPARAM lParam)
{
	LPSTR title = (LPSTR)malloc(sizeof(CHAR)*512);
	memset(title, 0, 512);
	char *cutoff = NULL;
	if (GetWindowText(hWin, title, 512) != 0) {
		if((cutoff = strstr(title, " [foobar2000 v")) != NULL) {
			*cutoff = 0;
			cout << title << endl;
		}
	}
	return TRUE;
}

int main()
{
	EnumWindows(ewcb, 0);
	return 0;
}

