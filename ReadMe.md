## meshler

[![Ubuntu](https://github.com/timow-gh/meshler/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/timow-gh/meshler/actions/workflows/ubuntu.yml)
[![Windows](https://github.com/timow-gh/meshler/actions/workflows/windows.yml/badge.svg)](https://github.com/timow-gh/meshler/actions/workflows/windows.yml)

![](media/ubuntu_meshler.png)

## Building

Download the source code:

```
git clone https://github.com/timow-gh/meshler.git
```

### Windows

Tested with Visual Studio 16, 64bit. Configure cmake:

```
cmake -B <path-to-build-dir> -S <path-to-source-dir> -G "Visual Studio 16 2019" -A x64 -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=20
```

Build the target MeshlerApp:

```
cmake --build <path-to-build-dir> --target MeshlerApp --config Release --parallel -- /p:CL_MPcount=<your-number-of-processors>
```


### Ubuntu

Requirements:

- libglu1-mesa-dev # listed filament dep
- libxi-dev # listed filament dep
- libxxf86vm-dev # for sdl2

```
sudo apt install libglu1-mesa-dev libxi-dev libxxf86vm-dev
```