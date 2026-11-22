# initial setup

glfw: opens window, creates context (2d/3d)
glew: loads opengl's functions
glm: maths (vectors, matrices etc)




# How the GPU draws
```
your vertex data  →  VERTEX SHADER  →  rasterizer  →  FRAGMENT SHADER  →  screen
(positions in      (runs once per     (works out       (runs once per
 a GPU buffer)      vertex: "where     which pixels     pixel: "what
                    does it go?")      are covered)     colour is it?")



```


helper func: links shaders to program
program: helps us draw on window

VBO-vertex buffer object
VAO-vertex array object
NDC-normalized device coordinates (-1,1) from center of screen







# Build and run
```
cmake -S . -B build -G Ninja
cmake --build build
./build/mc
```