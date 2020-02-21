# Master-craft
The goal of this project is to realize a 3Dworld represented only by 3D cubes in the spirit of  «Minecraft».

##
### Prerequisites

For this project you need:

````bash
CMake version 3.7 at least
SDL2
OpenGL
GLEW
````
##
### Compilation

````bash
mkdir build
cd build
cmake ..
make
````
The program is launch with the compiled executable `mastercraft`.

```
./mastercraft
```

##
### Manual

The key `escape` exits the application.

The camera is controlled by:  
    * `z` (advance), `s` (back), `q` (left), `d` (right) or the arrow keys  
    * the mouse to turn around  
    
The `e` key changes from day to night mode.    

**Keys Fn:**

`F1` : disable/enable Face culling  
`F2` : disable/enable occlusion culling  
`F3` : modifie FPS  
`F4` : reduces the land  
`F5` : extends the land  
`F10` : displays the program information  

  
   
##
### Authors

* Quentin Coumes and Elise Hardy

