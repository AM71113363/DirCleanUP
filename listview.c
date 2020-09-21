#include "main.h"
LVITEM LvItem;

void CreateListView(HWND hwnd)
{
   hListView = CreateWindowEx(0,"SysListView32",0,  //
                             WS_CHILD | WS_VISIBLE |LVS_REPORT | LVS_SINGLESEL | LVS_NOSORTHEADER ,
                             2, 2, 404, 272, hwnd,(HMENU)ID_LISTVIEW, ins, NULL);
    LVCOLUMN LvCol;   
	memset(&LvCol,0,sizeof(LVCOLUMN));
	
	LvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM|LVCF_FMT;
	LvCol.cx=0xAA;		
	LvCol.fmt = LVCFMT_RIGHT;
	
	LvCol.pszText = "Extention";
	SNDMSG(hListView,LVM_INSERTCOLUMN,0,(LPARAM)&LvCol);

    LvCol.cx=0x47;
    LvCol.pszText = "Found";
	SNDMSG(hListView,LVM_INSERTCOLUMN,1,(LPARAM)&LvCol);
   
    LvCol.pszText = "Deleted";
	SNDMSG(hListView,LVM_INSERTCOLUMN,2,(LPARAM)&LvCol);
   
    LvCol.pszText = "Verify";
	SNDMSG(hListView,LVM_INSERTCOLUMN,3,(LPARAM)&LvCol);
	    
    SNDMSG(hListView,LVM_SETEXTENDEDLISTVIEWSTYLE,0,(WPARAM)LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT); 
    SNDMSG(hListView, WM_SETREDRAW, TRUE, 0);
return;
}

void AddItem(int index, int iImage, unsigned char *ext,unsigned char *number)
{	
    memset(&LvItem,0,sizeof(LvItem)); 
	LvItem.mask=LVIF_TEXT | LVIF_IMAGE;
	LvItem.cchTextMax = MAX_PATH;		 
	LvItem.iItem = index;					  
	LvItem.iImage = iImage;	//-------- Insert Image ------------------
    SNDMSG(hListView,LVM_INSERTITEM,0,(LPARAM)&LvItem); 		  
	LvItem.iSubItem=0;	//-------- Insert Element 0 --------------
	LvItem.pszText = ext; //"ext"
	SNDMSG(hListView,LVM_SETITEM,0,(LPARAM)&LvItem);
	LvItem.iSubItem=1;	//-------- Insert Element 1 --------------
	LvItem.pszText = number; // numer
	SNDMSG(hListView,LVM_SETITEM,0,(LPARAM)&LvItem);
	LvItem.iSubItem=2;	//-------- Insert Element 2 --------------
	LvItem.pszText = ""; // numer
	SNDMSG(hListView,LVM_SETITEM,0,(LPARAM)&LvItem);

  //  SNDMSG(hListView, WM_SETREDRAW, TRUE, 0);// ----------------- refresh() ----------
 // RedrawWindow(hListView,NULL,NULL,RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
 return;    
}

void ChangeSubItem(int subitem,unsigned int index,unsigned char *value)
{
   memset(&LvItem,0,sizeof(LvItem)); 
   LvItem.mask=LVIF_TEXT;
   LvItem.iItem = (int)index;
   LvItem.iSubItem = subitem;
   LvItem.pszText = value;    
   SNDMSG(hListView,LVM_SETITEM,(WPARAM)0,(LPARAM)&LvItem);
}     

void ChangeFound(unsigned int index,unsigned char *value)
{
   ChangeSubItem(1,index,value);
}

void ChangeDeleted(unsigned int index,unsigned char *value)
{
   ChangeSubItem(2,index,value);
}
void ChangeVerify(unsigned int index,unsigned char *value)
{
   ChangeSubItem(3,index,value);
}


