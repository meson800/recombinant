# recombinant


# Installing wxWidgets on Windows
After downloading the installer (or source code) from wxWidgets, you need to build it, in x64 mode
and alternatively in release/debug, as needed.

Furthermore, the FindwxWidgets CMake script has a hard-coded list of paths. This means that you need
to copy, for example, the folder wxWidgets-3.1.3 to wxWidgets.

After that, open a *x64 Visual Studio command prompt*, and go to the build/msw directory. From there, 
run
```
nmake /f makefile.vc BUILD=release TARGET_CPU=X64
nmake /f makefile.vc TARGET_CPU=X64
```
This will build both the release and debug versions of the libraries and place them in the correct locations.
You can omit the second call if you just want to build the release versions of Recombinant.