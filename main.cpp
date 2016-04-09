#include <iostream>
#include <windows.h>
#include <malloc.h>
#include <cstring>
#include <string>

using namespace std;

string output;

int ewcb(HWND hWin, LPARAM lParam)
{
	LPSTR title = (LPSTR)malloc(sizeof(CHAR)*512);
	memset(title, 0, 512);
	char *cutoff = NULL;
	if (GetWindowText(hWin, title, 512) != 0) {
		if((cutoff = strstr(title, " [foobar2000 v")) != NULL) {
			*cutoff = 0;
			cout << title << endl;
			output = title;
		}
	}
	return TRUE;
}

int main(int argc, char* argv[])
{
	EnumWindows(ewcb, 0);
	if(argc > 1 && !strcmp("/clip", argv[1])) {
		if(!OpenClipboard(NULL)) {
			cout << "Cannot open the Clipboard" << endl;
			return -1;
		}
		if(!EmptyClipboard()) {
			cout << "Cannot empty the Clipboard" << endl;
			return -1;
		}
		HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 512);
		strcpy_s((char*)hGlob, 512, output.c_str());

		if(SetClipboardData(CF_TEXT, hGlob) == NULL)	{
			cout << "Unable to set Clipboard data, error: " << GetLastError() << endl;
			CloseClipboard();
			GlobalFree(hGlob);
			return -1;
		}
		//ClipBoard is now responsible for hGlob
		CloseClipboard();
		cout << "Copied to clipboard" << endl;
	}
	return 0;
}

