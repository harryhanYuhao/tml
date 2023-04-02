# tEngine Documentation

## API functions

```c
void teRender(int * ptr, int * cptr, int width, int heigth, int fun()){
```

Render $width \times $height$ rectangle to screen based on the two passed in pointer to arrays of integers.

The two arrays are two dimensional array in the form of one dimensional array.

Each coordinate in the rectangle are ascii symbols based value of first array. The color are determined by the integer values of the second array. Here is the conversion:
- 0: red 
- 1: green
- 2: yellow
- 3: blue
- 4: magenta
- 5: cyne
- 10: gray box
- all other: white.
