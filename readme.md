cautious-adventure
====

```
$ git clone --recurse-submodules https://github.com/dsge/cautious-adventure.git
```
or
```
$ git clone https://github.com/dsge/cautious-adventure.git
$ cd cautious-adventure && git submodule update --init --recursive
```

--------------

```
$ sudo apt-get install python3 build-essential mingw-w64
$ python3 -m pip install scons==4.6.0
```

--------------

```
$ scons platform=linux
$ scons platform=windows
```

--------------


`./blender-and-godot-editor/Godot_linux.x86_64` or `./blender-and-godot-editor/Godot_win64.exe`