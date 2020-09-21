#include "main.h"
char szClassName[ ] = "WindowsAppDir";
void CenterOnScreen();
void scanForExt();
void StartDelete();

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
             InitCommonControls();
             hWnd = hwnd;
             B_go = CreateWindow("BUTTON","Start",WS_MIN|WS_DISABLED,2,275,404,20,hwnd,(HMENU)ID_DELETE,ins,NULL);
            
             CreateListView(hwnd);

             hStatusBar = CreateWindow(STATUSCLASSNAME,0,WS_MIN,0,0,0,0,hwnd,0,ins,0);
             CenterOnScreen();
             DragAcceptFiles(hwnd,1);
        }
        break;   
        case WM_NOTIFY:
        {//WM_NOTIFY
          if(IsScanning == YES){  break; }
            switch(LOWORD(wParam))
            { //  switch
   	            case ID_LISTVIEW: 
        	    { ///listview
                    switch(_lpnm->code)
                    {//switch
						case LVN_ITEMCHANGED:
						{		
                            unsigned int ret;  
                            if(_ItemList->iItem == nlist)
                            {
                                ListView_SetCheckState(hListView,nlist,0);
                                sprintf(Tbuf,"%s","OtherFiles MUST be Deleted\0");
                            }
                            else
                            {
                               ret = ListView_GetCheckState(hListView,_ItemList->iItem);
							   if(ret == 1) //checked
							   {
                                  sprintf(Tbuf,"Don't Delete [%s] FILES\0",list[_ItemList->iItem].ext);
								  if(list[_ItemList->iItem].need == NO){  ExtSelected++; }
                                  list[_ItemList->iItem].need = YES;
                               }
	       					   else if(ret == 0)
	   						   {
                                  sprintf(Tbuf,"Delete [%s] FILES\0",list[_ItemList->iItem].ext);
						  		  if(list[_ItemList->iItem].need == YES){ ExtSelected--; }
                                  list[_ItemList->iItem].need = NO;
                               }
	   						   else
							   {
							     sprintf(Tbuf,"BUG WITH [%s] EXT\0",list[_ItemList->iItem].ext);
							   }
                            }
	   						SMS(Tbuf);
	   						if(ExtSelected > 0)
			                {
                                EnableWindow(B_go,1);
                            } 
                            else
                            {
                                 EnableWindow(B_go,0);
                            }          
 						}
 						break;
 					}//switch
				}//listview
            } //switch
        }//WM_NOTIFY
        break; 
        case WM_DROPFILES:
		{
			HDROP hDrop;  			
			memset(dropped,0,MAX_PATH);
			hDrop=(HDROP)wParam;
			DragQueryFile(hDrop,0,dropped,MAX_PATH);
			DragFinish(hDrop);
			if((GetFileAttributes(dropped) & FILE_ATTRIBUTE_DIRECTORY)!=FILE_ATTRIBUTE_DIRECTORY)
               break;
                                          
            if(strlen(dropped) < 2)
			{  
                MessageBox(NULL,"This is a Protected Folder","ERROR", MB_ICONINFORMATION|MB_SYSTEMMODAL|MB_OK);
			    break;
			}
            EnableWindow(B_go,0);
            ExtSelected = 0;
            IsScanning = NO;
            droppedLen = (unsigned int)strlen(dropped);
            SNDMSG(hListView,LVM_DELETEALLITEMS,0,0);
            CreateThread(0,0,(LPTHREAD_START_ROUTINE)scanForExt,0,0,0); 
         }
		 break;
       case WM_COMMAND:
       {
            switch(LOWORD(wParam))
            {                  
                 case 1111:
                 {
                    //SetWindowText(logger,"");        
                 }
                 break;
                 case ID_DELETE:
                 {
                    EnableWindow(B_go,0);  
                    CreateThread(0,0,(LPTHREAD_START_ROUTINE)StartDelete,0,0,0);        
                 }
                 break;                 
            }
            return 0;
       }
       break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
            
    MSG messages;    
    WNDCLASSEX wincl;  
    HWND hwnd;       
    ins=hThisInstance;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;  
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (ins,MAKEINTRESOURCE(200));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;  
    wincl.cbClsExtra = 0;  
    wincl.cbWndExtra = 0;      
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx(WS_EX_TOPMOST,szClassName,"DIR CleanUp",WS_SYSMENU|WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,
    414,347,HWND_DESKTOP,NULL,hThisInstance,NULL );
    
    ShowWindow (hwnd, nFunsterStil);

    while (GetMessage (&messages, NULL, 0, 0))
    {
         TranslateMessage(&messages);
         DispatchMessage(&messages);
    }

     return messages.wParam;
}

void CenterOnScreen()
{
     RECT rcClient, rcDesktop;
	 int nX, nY;
     SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
     GetWindowRect(hWnd, &rcClient);
	 nX=((rcDesktop.right - rcDesktop.left) / 2) -((rcClient.right - rcClient.left) / 2);
	 nY=((rcDesktop.bottom - rcDesktop.top) / 2) -((rcClient.bottom - rcClient.top) / 2);
SetWindowPos(hWnd, NULL, nX, nY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

unsigned int getExtHash(unsigned char *FileName)
{
    unsigned char *c;    
    unsigned int hash = 2280;

    c = (unsigned char*)strrchr(FileName,'.');
    if(c == NULL)
       return 0;
    c++;
    if(c[0] == 0)
       return 0;
    
    for( ; *c; c++)
    {
         hash += (hash << 5);  //= hash * 32
         hash += *c;
         hash = hash % HASH_SIZE;
    } 
    return hash+1;
}

unsigned int CheckInList(unsigned char *FileName)
{
    unsigned int nHash,i;
    unsigned int ret = nlist;
    nHash = getExtHash(FileName);  
    for(i=0;i<nlist;i++)
    {
        if(list[i].extHash == nHash)
        {
            ret = i;
            break;
        }
    }  
  return ret;
}
