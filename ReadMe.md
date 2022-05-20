## meshler

Dabbeling with OOP.

![](media/ubuntu_meshler.png)

## Building

Download the source code:

```
git clone https://github.com/timow-gh/FilApp.git
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