# PACMAN - An iGraphics Project
Demo:
-----------------------
https://www.youtube.com/watch?v=xWry5NQfDuw

Command line compiling:
-----------------------
```
g++ -fpermissive -IOpenGL\include -w -c iMain.cpp -o main.o
```

Command line linking:
---------------------
```
g++ -LOpenGL\lib main.o -o main.exe -lGlaux -lGLU32 -lglui32 -lglut32 -lOPENGL32 -lgdi32
```

Command line running:
---------------------
Make sure `glut32.dll` is present in the same folder \
Run `main.exe`

