#define _lpnm   ((LPNMHDR)lParam)
#define _ItemList   ((LPNMLISTVIEW)lParam)


#define YES         1
#define NO          0
#define HASH_SIZE	0x12345678

#define WS_MIN               WS_CHILD | WS_VISIBLE
#define SMS(_s_) SNDMSG(hStatusBar, SB_SETTEXT, 0, (LPARAM)_s_);




#define ID_LISTVIEW          1001
#define ID_DELETE            1002

