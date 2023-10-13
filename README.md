# IsoGame \[C\]
This project is about re-creating a rendering dmo I made in Java where I rendered an isometric level with software rendering.

With this project, I'm working in C under windows. *[You may have seen my other project where I made this in x64 Assembly](https://github.com/Kirdow/IsoGameAsm)*.

# Build & Run
The build pipeline uses a normal Makefile and a bash script.

## Requirements
You may need some setup before building however depending on your platform.

### Windows
Requires [MSYS2 MINGW64](https://www.msys2.org/). Simply install it from their website, then make sure it got the latest gcc and make version installed.

### macOS
Requires SDL2 installed externally. Installing SDL2 can be done using homebrew:
```sh
brew install sdl2
```

You will also need to have Xcode installed as well as CommandLineTools for macosx.

### Linux
Requires SDL2 installed externally. Installing SDL2 does depend on which distro you use.

Use one of these
```sh
# Using apt
sudo apt-get install libsdl2-dev

# Using pacman
sudo pacman -S sdl2
```
If your distro doesn't use either of those, adapt to whichever your distro uses. Some distros/package managers may need both `sdl2` and `sdl2-devel`.

## Building and Running
If you got all the required libraries and files, building is fairly simple.<br>
You may need to run `chmod +x ./exec.sh` if you lack permissions on Linux and macOS.

*__Note:__ If you simply run `./exec.sh` without arguments, it currently does both.*
### Building
```sh
./exec.sh build
```

### Running
```sh
./exec.sh run
```


# License
IsoGame \[C\] is licensed under [MIT License](https://github.com/Kirdow/IsoGame/blob/master/LICENSE).

Third party libraries are licensed under [their respective licenses](https://github.com/Kirdow/IsoGame/blob/master/ATTRIBUTIONS.txt).