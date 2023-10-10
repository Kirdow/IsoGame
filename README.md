# IsoGame \[C\]
This project is about re-creating a rendering dmo I made in Java where I rendered an isometric level with software rendering.

With this project, I'm working in C under windows. *[You may have seen my other project where I made this in x64 Assembly](https://github.com/Kirdow/IsoGameAsm)*.

# Build & Run
The build pipeline uses a normal Makefile.

Currently made on Windows using [MSYS2 MINGW64](https://www.msys2.org/). Linux and macOS may be supported but you'd have to find your own copies of SDL2 for now.

In order to build, open a terminal in the repository directory and run these commands:
### Build
```sh
make
```

### Run
```sh
make run
```
*You can also run the executable directly in `./dist/isogame` if you don't want to rebuild. Only works if you built at least once though.*

# License
IsoGame \[C\] is licensed under [MIT License](https://github.com/Kirdow/IsoGame/blob/master/LICENSE).

Third party libraries are licensed under [their respective licenses](https://github.com/Kirdow/IsoGame/blob/master/ATTRIBUTIONS.txt).