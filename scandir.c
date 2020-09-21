#include "main.h"
void AddItem(int index, int iImage, unsigned char *ext,unsigned char *number);
void ChangeFound(unsigned int index,unsigned char *value);
unsigned int getExtHash(unsigned char *FileName);


int proc_ImlListView(unsigned char *Path)
{
    SHFILEINFO sfi;
    HIMAGELIST himl;
 	ZeroMemory(&sfi,sizeof(SHFILEINFO));
    himl=(HIMAGELIST)SHGetFileInfo(Path,0,&sfi,sizeof(SHFILEINFO),SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	if(himl == 0)
    {
       return -1;
    }
    SNDMSG(hListView,LVM_SETIMAGELIST,LVSIL_SMALL,(LPARAM)himl);
	return sfi.iIcon;
}

void AddToTable(unsigned char *FullPathFileName, unsigned char *ShortPathFileName)
{
   unsigned int Chash;
   unsigned int i;
   int iImage;
   Chash = getExtHash(ShortPathFileName);
   if(Chash > 0)
   {
       for(i=0;i<nlist;i++)
       {
           if(list[i].extHash == Chash)
           {
                list[i].count++;
                sprintf(Tbuf,"%u\0",list[i].count);
                ChangeFound(i,Tbuf);
                return;
           }
       }                
       list = (TABLE*)realloc(list,(nlist+1)*sizeof(TABLE));
       list[nlist].extHash = Chash;
       list[nlist].count = 1;
       list[nlist].deleted = 0;
       list[nlist].verify = 0;
       list[nlist].need = NO;
     //  list[nlist].iImage = proc_ImlListView(FullPathFileName);
       iImage = proc_ImlListView(FullPathFileName);
       memset(list[nlist].ext,0,16);
       snprintf(list[nlist].ext,15,"%s",strrchr(FullPathFileName,'.'));
       AddItem(nlist,iImage, list[nlist].ext,"1"); 
       nlist++;
   }
   else
   {
      OtherFiles++;  
   }
}


int FindExt(unsigned char *Path)
{
	HANDLE h;
	WIN32_FIND_DATA info;
    unsigned char SearchPath[MAX_PATH]; 
    unsigned char CurrentFile[MAX_PATH]; 
    int ret;
    memset(SearchPath,0,MAX_PATH);
    memset(CurrentFile,0,MAX_PATH);
    
    sprintf(SearchPath,"%s\\*\0",Path);
	h = FindFirstFile(SearchPath, &info);
	if(h == INVALID_HANDLE_VALUE)  return -1;
		
    while(FindNextFile(h, &info) != 0)
    {
        if(strcmp(info.cFileName, ".") == 0){  continue; }
        if(strcmp(info.cFileName, "..") == 0){ continue; }
        
        sprintf(CurrentFile, "%s\\%s\0", Path,info.cFileName);
        SMS(&CurrentFile[droppedLen]);
        if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
              ret = FindExt(CurrentFile);
		      if(ret == -1)
              {
                 return -1;    
              } 
        }
        else//it is a file
        {    
           AddToTable(CurrentFile,info.cFileName);
        }  
    } 
    FindClose(h); //end of scan   
    return 0;
}




void scanForExt()
{
     int ret;
     unsigned char SHpath[MAX_PATH];
     OtherFiles = 0;
     nlist = 0;
     IsScanning = YES;
     SetWindowText(hWnd,"Start");
     memset(SHpath,0,MAX_PATH);
     if(GetShortPathName(dropped,SHpath,MAX_PATH) == ERROR_INVALID_PARAMETER)
     {
        strcpy(SHpath,dropped);                                         
     }
     ret = FindExt(dropped); 
     //append all at the end of list
     if(OtherFiles > 0)
     {
        sprintf(Tbuf,"%u\0",OtherFiles);       
        AddItem(nlist,-1, "OTherFiles",Tbuf);           
     }              
     if(ret == 0)
     {
        SetWindowText(hWnd,"End");
        SMS(SHpath);
     }
     else
     {
        SetWindowText(hWnd,"Error");
     }
     IsScanning = NO;
}

