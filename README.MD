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



Matrix	::::
-Model	Where is this object, how is it rotated and scaled?	Each chunk's position in the world
-View	Where is the camera, and which way does it face?	The player's eyes (Lesson 5)
-Projection	How does 3D get flattened to 2D?	Field of view, aspect ratio, how far you can see


# Build and run
```
cmake -S . -B build -G Ninja && cmake --build build && ./build/mc
```