# XD

> **Note:** All entries in this file must be in English.

## Building the Project

The `_cmake` folder is the **working directory for the build system** and must not be deleted. The project should only be built using the batch files provided in this folder:

- `build_windows_debug.bat` - Build in Debug configuration
- `build_windows_release.bat` - Build in Release configuration

To build the project, navigate to the `_cmake` folder and run the desired batch file.

## Modules

The project consists of independent modules located in the `_mod` folder. Each module is responsible for specific functionality:

### _app
Contains the main application logic. Responsible for coordinating the work of other modules and managing the application lifecycle.

### _data
Contains methods for working with data and loading it from disk. Provides interfaces for data persistence and recovery.

### _gfx
Contains the code for the 3D rendering subsystem. Responsible for visualization and graphical display.

### _os
Contains logic for operating system interaction. Manages interaction with system resources and OS API.

### Module Independence
Modules are independent of each other but can work with common abstract data types, providing flexibility and the ability to reuse components.