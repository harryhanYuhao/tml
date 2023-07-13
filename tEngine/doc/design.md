# The Design of tEngine

tEngine is a terminal graphic engine that can be accessed with APIs like that of OpenGL.

## Fundamental Design

## Planned Updates

- Add color and costumize output symbol

## Future Improvements

- teRender Pass in symbol instead of int?
- Shall OOP paradigm be used? -- Probably not.
- As of now it is a static library. It should be made into a dynamic library. -- It is not made into a dylib with the corresponding header `tEngine.h`. 
- Use `ncurses` for better 'graphics' -- May not be a necessary
- Use a different clear screen method the retains the previous session. See spinning dougnuts
