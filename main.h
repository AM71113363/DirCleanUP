#define _WIN32_IE  0x0501
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#include "resource.h"

unsigned char Tbuf[64];

HINSTANCE ins;
HWND hWnd;
HWND hListView;
HWND hStatusBar;
HWND B_go;

unsigned char dropped[MAX_PATH];
unsigned int droppedLen;

typedef struct _TABLE
{ 
    unsigned char ext[16];
    unsigned int extHash; 
    unsigned int count; 
    unsigned int deleted;
    unsigned int verify;
    unsigned char need;
  //  int iImage;
}TABLE;

TABLE *list;
unsigned char IsScanning;
unsigned int nlist;        // TABLE list number of entries
unsigned int OtherFiles;   //contain number of entries with no extentions
unsigned int ExtSelected;  //at least on ext must be selected
