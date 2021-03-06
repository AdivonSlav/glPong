# glPong [![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
A clone of the Atari classic built with C++ and OpenGL using the GLFW and GLEW libraries.  Started as a small learning project while I was working my way through the OpenGL graphics API. For the math library, I ended up making my own and implementing simple vector and matrix containers coupled with basic mathematical operations. 
For simple text rendering functionality, I ended up using the Freetype library 

![glPongGIF](https://i.imgur.com/bcsNfhw.gif)

## Controls:
- WASD - Left paddle
- Arrow keys - Right paddle
- Esc - Closes game
- Space - Pauses game

## Build instructions
Simply run the file `genproj.bat` and it will generate the necessary VS2022 project files. After that, open the solution with Visual Studio. If generating for an earlier version of Visual Studio, edit the file and replace 'vs2022' with your version.

[Pre-compiled binaries](https://github.com/AdivonSlav/glPong/releases)

## Compatibility
I only tested this with Windows but it should work on other systems as well.

