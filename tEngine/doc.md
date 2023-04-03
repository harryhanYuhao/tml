# tEngine Documentation

## API functions

```c
void teRender(int * ptr, int * cptr, int width, int heigth, int fun()){
```

Render $width \times $height$ rectangle to screen based on the two passed in pointer to arrays of integers.

The two arrays are two dimensional array in the form of one dimensional array.

Each coordinate in the rectangle are ascii symbols based value of first array. The color are determined by the integer values of the second array. Here is the conversion:
- 0: white
- 1: red 
- 2: green 
- 3: yellow 
- 4: blue 
- 5: magenta 
- 6: cyne
- 10: gray box
- all other: white.

The function `fun()` is executed once every frame.
