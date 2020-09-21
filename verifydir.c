#include "main.h"
void AddItem(int index, int iImage, unsigned char *ext,unsigned char *number);
void ChangeVerify(unsigned int index,unsigned char *value);
unsigned int CheckInList(unsigned char *FileName);
unsigned int NbOtherFiles;


int VerifyExt(unsigned char *Path)
{
	HANDLE h;
	WIN32_FIND_DATA info;
    unsigned char SearchPath[MAX_PATH]; 
    unsigned char CurrentFile[MAX_PATH]; 
    int ret;
    unsigned int index;
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
              ret = VerifyExt(CurrentFile);
		      if(ret == -1)
              {
                 return -1;    
              } 
        }
        else//it is a file
        {    
              index = CheckInList( info.cFileName);
			  if(index < nlist) //the hash is in the list ,not OTHER FILES
              {  
                  list[index].verify++;       
                  sprintf(Tbuf,"%u\0",list[index].verify);
		          ChangeVerify(index,Tbuf);
              }
              else
              {
                  NbOtherFiles++;
              }
        }  
    } 
    FindClose(h); //end of scan   
    return 0;
}




void scanToVerify()
{
     int ret;
     NbOtherFiles = 0;
     ret = VerifyExt(dropped); 
     
     if(NbOtherFiles > 0) //found othefiles,but it should'nt
     {
         if(OtherFiles == 0) //dont have a field
         {
            AddItem(nlist,-1, "OTherFiles",""); 
         }
         sprintf(Tbuf,"%u\0",NbOtherFiles);            
         ChangeVerify(nlist,Tbuf);        
     }              
     if(ret == 0)
     {
        SetWindowText(hWnd,"End");
        SMS("Done");
     }
     else
     {
        SetWindowText(hWnd,"Error");
     }
}

