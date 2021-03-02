build.bat will work only with Dev-C++ 4.9.9.*


run DirCleanUp.exe (32Bit Windows) 

1.Drag-Drop Folder to start scanner.
2.Check file EXT that you want to keep.
3.Click [ START ]
4.If an Error Occurs the App will stop and the StatusBar will show the filename
  where the Error is.(rename the file and start again).[ no support for multibyte filenames ]
5.The app with stop if the FullPath of file > MAX_PATH(0xFF),just move the folder to C:\\
  and start again.

INFO:
When you download a BIG Zip file which contains maybe > 500MB of code+helpfiles+images+ecc..
And you want to keep only [ .cpp ] or [.java] or [.??? ] files,
Then with "DirCleanUp.exe" you will delete all [ junk files ] including empty folders.
Or
You can use it to remove all empty folders(directory & subdirectory)
1.Inside the folder create a file with a random EXT (sample.abcd).
2.Drag-Drop Folder to start scanner.
3.Check all file EXT and leave unchecked .abcd (ext of sample.abcd).
4.Click [ START ].
5.DONE.

IMPORTANT:
Default Settings[ can't be changed unless you modify the code ]

DirCleanUp.exe will delete all:
                    Empty Folders
                    Files with size=0
                    Files with no extension
