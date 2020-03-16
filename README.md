# Kill-mob

The goal of this project is to realize a 3D shoot voxel world represented only by 3D cubes.

## Prerequisites

To run *kill-mob*, you need:

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

The program is launch with the compiled executable `kill-mob`.

```
./kill-mob
```


## Manual

Use `ESC` to exit the application.

* Movement :

    * `w` / `↑` : Move forward.
    * `s` / `↓` : Move backward.
    * `a` / `←` : Strafe left.
    * `d` / `→` : Straft right.    
    * Use the mouse to look around.
    * `t` : Shoot with canon
    * `b` : Shoot bomb (if monsters kills > 3)
    * `c` : cheat camera
    * `ctrl` : down camera if cheat activ
    * `space` : up camera if cheat activ

* Miscellaneous :

    * `E` To switch between day / night (if cheat activ).
    * `F1` : Disable/enable face culling (enable by default).
    * `F2` : Disable/enable occlusion culling (enable by default), will reload the scene.
    * `F3` : Cycle between framerate settings (default to `VSYNC`). Available FPS settings are
             `60`, `75`, `120`, `144`, `180`, `240`, `VSYNC` and `Uncapped`.
    * `F4` : Decrease distance view  .
    * `F5` : Increase distance view.
    * `F10` : Displays debug information.
    * `k` : information kills

Some notes :

* Controls should adapt to your keyboard layout.
* Disabling occlusion culling and increasing distance view will heavily impact performance.
* Framerate may be overridden by your GPU configuration. 


## Authors

* CetteElise Hardy

