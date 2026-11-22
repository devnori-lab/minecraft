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


VBO-vertex buffer object
VAO-vertex array object
NDC-normalized device coordinates










# Build and run
```
cmake -S . -B build -G Ninja
cmake --build build
./build/mc
```