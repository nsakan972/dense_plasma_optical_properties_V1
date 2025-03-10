# Dense Plasma calculations

A C++ application for parsing claculating a dense plasma optical parameters. At this momemt a work on reading pseudopotential files (UPF) and processing their XML files is still a work in progress. UPF is acronim for Unified Pseudopotential Format.

## Features

- XML parsing using pugixml library right now is parsing a UPF file, the internal storage of the structure and the file parameters and data is still being worked on
- Debug output levels for development
- CMake-based build system, thanks to FetchContent it is quite automated process

## Dependencies

- CMake (>= 3.16)
- pugixml
- OpenMP (optional, to be implemented)
- GLFW, GLAD, GLM (for visualization, to be implemented)

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

```bash
./denseplas_simple <input_file>
```

Where `<input_file>` is the path to your UPF format XML file.

## Project Structure

```
src/
├── main/           # Main application code
├── IF_parser/      # XML parsing implementation
└── globals/        # Global structures and variables
```

## Development Status

This project is currently under active development. Key features being worked on:
- XML parsing and data structure implementation
- UPF format support
- Data visualization (planned)

## License

This program is licensed under GNU General Public License v3.0 or later.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

See the [LICENSE](LICENSE) file for details.
