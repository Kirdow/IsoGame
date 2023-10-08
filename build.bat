@REM CLEANUP
rmdir /S /Q build
rmdir /S /Q dist
@REM CREATION
mkdir build
mkdir dist
@REM C COMPILE + LINK
cl src\wnd.c src\main.c /Iinclude\ /link libs\SDL2.lib /out:dist\isogame.exe
@REM COPY FILES
copy libs\SDL2.dll dist\SDL2.dll
