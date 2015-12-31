H323 plugin for Ethereal README 
=============================== 
Contents 
1. How to build the plugin 
2. How to install the plugin 
3. How to prepare Ethereal for use with the plugin 

How to build the H.323 plugin for Ethereal 0.9.3 
------------------------------------------------ 
If you are using the binary release, skip this part. 
1. Download Ethereal 0.9.3 
2. Follow the build instructions for your platform in README.<platform> 
   (currently this version of the plugin only supports WIN32) 
3. Unzip the plugin source zip file to the plugins directory of the 
   Ethereal source directory. You should keep the existing directory info used in the 
   zipfile. 
4. Open the mini_ptlib workspace in the mini_ptlib subdirectory 
5. Go to the project settings, C/C++ tab and select the Preprocessor category 
6. Change the Additional include directories field to show three paths: The path to the 
   GLib source directory Example: e:\ethereal\gtk-dev\src\glib The path to the GTK+ 
   source directory Example: e:\ethereal\gtk-dev\src\gtk+ The path to the Ethereal source 
   directory Example: e:\ethereal\0.8.15\ Seperate these three paths with a comma! 
7. Build the library (the WIN32 Debug target), using the Batch Build command for example. 
8. Close the mini_ptlib workspace 
9. Open a command line box and got to the h323 subdirectory in the Ethereal plugins 
   directory 
10. Run vcars32.bat (You should have this file in the PATH, if not, add the correct path 
    to the PATH environment variable 
11. Run nmake like this: nmake -f Makefile.nmake 
12. The plugin should now be built. At the end you might (pretty sure) get an error about 
    LIBC being an incompatible library or something like that. Ignore this warning. The 
    build process could take some time, there are a couple of large files involved. 
    
How to install the plugin 
------------------------- 
If you want to test the plugin you have just built or you want to start using the plugin 
you have just downloaded, follow these steps: 
1. If you have downloaded the DLL in a zipfile, unzip it to a temprorary locations 
2. Copy h323.dll to the plugins\0.9.3 subdirectory. You might have to create a 0.9.3 
   subdirectory yourself. 
   
How to prepare Ethereal for use with the plugin 
----------------------------------------------- 
Before H.323 can be reliably decoded, you will need to edit some preferences: 
1. Start Ethereal 
2. Go to Edit / Preferences 
3. Click on the + in front of Protocols 
4. Click on Q.931 (scroll downwards first if necessary) 
5. Make sure the square in front of "Desegment.... TCP segments" is lowered (click on the 
   square to change any other state). 
6. Click on TCP (scroll downwards first if necessary) 
7. Make sure the square in front of "Allow....TCP streams" is lowered (click on the 
   square to change any other state). 
8. Click on TPKT (scroll downwards first if necessary) 
9. Make sure the square in front of "Desegment....TCP segments" is lowered (click on the 
   square to change any other state). 
10. Click on Save, followed by Apply followed by OK