# Master-craft

The goal of this project is to realize a 3D voxel world represented only by 3D cubes in the spirit of **Minecraft**.

## Prerequisites

To run *Mastercraft*, you need:

* `CMake >= 3.7`
* `SDL2 >= 2.0.2`
* `OpenGL >= 3.3`
* `GLEW >= 2.1.0`


## Compilation

The compilation is done through `CMake` :

````bash
mkdir build
cd build
cmake ..
make
````

Compilation has been tested with `g++ >= 6.2.0` and `clang >= 7.0.1`.

The program is launch with the compiled executable `mastercraft`.

```
./mastercraft
```


## Manual


* Movement :

    * `W` / `↑` : Move forward.
    * `S` / `↓` : Move backward.
    * `A` / `←` : Strafe left.
    * `D` / `→` : Straft right.  
    * `CTRL` : Move downward.
    * `SPACE` : Move upward.  
    * Use the mouse to look around.

* Miscellaneous :

 	* `ESC` To exit the application.
    * `E` To switch between day / night.
    * `F1` : Disable/enable face culling (enable by default).
    * `F2` : Disable/enable occlusion culling (enable by default), will reload the scene.
    * `F3` : Cycle between framerate settings (default to `VSYNC`). Available FPS settings are
             `60`, `75`, `120`, `144`, `180`, `240`, `VSYNC` and `Uncapped`.
    * `F4` : Decrease distance view  .
    * `F5` : Increase distance view.
    * `F10` : Displays debug information.

Some notes :

* Controls should adapt to your keyboard layout.
* Disabling occlusion culling or increasing distance view a lot will heavily impact performance.
* Framerate may be overridden by your GPU / OpenGL configuration. 


## Work done

* Infinite world built from 2D and 3D noises.
* Multiple biome also generated from 2D noises.
* Multiple kind of tree.
* Multiple NPC.
* Transparent textures (water, leaves).
* Animated texture (water).
* Occlusion culling.
* Dynamic skybox.
* Dynamic lighting (sun's position, underwater).


## To do

* Loading SuperChunk on another thread (to avoid freeze on main loop)
* Frustum culling


## Authors

* Quentin Coumes and Elise Hardy

