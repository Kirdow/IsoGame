from os import walk, system
from os.path import sep
import io



w = walk("src")

all_files = [f"{dirpath}{sep}{filename}" for (dirpath, dirnames, filenames) in w for filename in filenames]
w = walk("src")
obj_files = [f"build{sep}{filename[:-2]}.obj" for (dirpath, dirnames, filenames) in w for filename in filenames if filename.endswith(".c")]
[print(file) for file in obj_files]
src_files = [filename for filename in all_files if filename.endswith(".c")]

files_str_src = " ".join(src_files)
files_str_obj = " ".join(obj_files)
include_str = f"/Iinclude{sep} /Isrc{sep}"
link_files = f"libs{sep}SDL2.lib"
exe_path = f"dist{sep}isogame.exe"

compile_cmd = f"cl /c {files_str_src} {include_str} /Fo\"build{sep}\""
link_cmd = f"cl {files_str_obj} /link {link_files} /out:{exe_path}"

with open("gen.bat", "w") as f:
    f.write("@REM CLEANUP\n")
    f.write("rmdir /S /Q build\n")
    f.write("rmdir /S /Q dist\n")
    f.write("@REM CREATION\n")
    f.write("mkdir build\n")
    f.write("mkdir dist\n")
    f.write("@REM C COMPILE\n")
    f.write("echo Compiling...\n")
    for src_file in src_files:
        f.write(f"cl /c {src_file} {include_str} /Fo\"build/\"\n")
    f.write("@REM OBJ LINK\n")
    f.write("echo Linking...\n")
    f.write(link_cmd + "\n")
    f.write("@REM COPY FILES\n")
    f.write(f"copy libs{sep}SDL2.dll dist{sep}SDL2.dll\n")

print("Generated build script")
