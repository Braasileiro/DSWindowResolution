# DSWindowResolution
A program to change the window size of the Dark Souls: Prepare to Die Edition.

# Installing
Installation instructions can be found in the guide of Steam created by me: [WindowResolution Tool](http://steamcommunity.com/sharedfiles/filedetails/?id=647930410)

# Building
```
windres DSWindowResolution.rc -O coff -o DSWindowResolution.res
gcc -Wall -static-libgcc DSWindowResolution.c -o DSWindowResolution.exe DSWindowResolution.res
```
