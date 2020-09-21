#include "main.h"
void ChangeDeleted(unsigned int index,unsigned char *value);
unsigned int CheckInList(unsigned char *FileName);
void scanToVerify();
unsigned int NbOtherFiles;


int CancelaFile(unsigned char *Path)
{
	HANDLE h;
	WIN32_FIND_DATA info;
    unsigned char SearchPath[MAX_PATH]; 
    unsigned char CurrentFile[MAX_PATH]; 
    int ret = -1;
	unsigned int index;
    unsigned char DirIsEmpty = YES;
    unsigned char SourceDetected = NO;
    unsigned char UnDeleteFolder = NO;
    
    SetFileAttributes(Path,FILE_ATTRIBUTE_NORMAL);
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
        DirIsEmpty = NO; //if arrives here mean dir contain someting
        if(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
              SMS(&CurrentFile[droppedLen]);
			  ret = CancelaFile(CurrentFile);
		      if(ret == -1) return -1;
		      if(ret == 0) UnDeleteFolder = YES;
        }
        else//it is a file
        {
              index = CheckInList( info.cFileName);
			  if(index < nlist) //the hash is in the list ,not OTHER FILES
              {  
			     if((list[index].need == YES) && (info.nFileSizeLow>0) )
			     {
				     SourceDetected = YES;  
                     continue; 
			     }
              }
              //found some file that has to be deleted
              SetFileAttributes(CurrentFile,FILE_ATTRIBUTE_NORMAL);
			  SMS(&CurrentFile[droppedLen]);
              if(DeleteFile(CurrentFile) == 0)
               return -1;
			  if(index == nlist) //other files
			  {
			     NbOtherFiles++;
				 sprintf(Tbuf,"%u\0",NbOtherFiles);
				 ChangeDeleted(nlist,Tbuf);
			  }
			  else
			  {
			     list[index].deleted++;
			     sprintf(Tbuf,"%u\0",list[index].deleted);
				 ChangeDeleted(index,Tbuf);
			  }  
        }  
    } 
    FindClose(h); //end of scan
    if(DirIsEmpty == YES)
    {
	   SMS(&Path[droppedLen]);
       if(RemoveDirectory(Path) == 0)
       {
           return -1;
       }
       return 1; // mean this dir is removes
    }      //no dir detected and all files deleted
    else if( (UnDeleteFolder == NO) && (SourceDetected == NO) )
    {
	   SMS(&Path[droppedLen]);
       if(RemoveDirectory(Path) == 0)
       {
           return -1;
       }
       return 1; // mean this dir is removes
    }
    return 0;
}


void StartDelete()
{	   
     int ret;
     NbOtherFiles = 0;
     IsScanning = YES;
	 EnableWindow(B_go,0);
     SetWindowText(hWnd,"Delete"); 
     
	 ret = CancelaFile(dropped);
     if(ret == 0)
     {
        SetWindowText(hWnd,"Verify"); 
        scanToVerify();
     }
     else
     {
         SetWindowText(hWnd,"Error"); 
     }
    // IsScanning = NO;
}
