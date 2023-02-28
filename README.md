# BML

BML is the SDL wrapper that BlueKit2D will use. It is designed to handle many of the lower level task for the engine and keep them obstructed so that I can focus more on the structure of components and data when creating the engine.

### Uses
This project is mostly for personal use so I do not plan on writing much in-depth documentation on how it works other than my personal comments I leave for myself. Just like ask me if you want to know how something works but really I am trying to keep it as straight forward as possible

### Build Instructions
Install SDL2, SDL_Image, and SDL_Mixer following instructions based off your OSs for this.
Once you have done that you can copy this code into your terminal of choice

```
git clone git@github.com:BSBussell/BML.git
cd BML
make Build
```

This will create the linker objects to use when compiling with your program.

#### Tests
If you want to build and run the tests run in the base directory and then you can run the test binaries created in tests/bin/
```
make Tests
```

Currently there is only 2 tests one for opening a window that you have to force quit to close as events haven't been integrated with it yet. The other opens a window that you can quit using events and will also print to the console when the key 'Q' is pressed. 

### Not working
Please be patient as the makefile is subject to change as this project grows in size and I am unlikely to update this ReadMe once that happens because honestly how did you even find the project?
