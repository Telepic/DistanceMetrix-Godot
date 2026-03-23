# distance_matrix

A Godot 4 GDExtension (C++) component for efficiently storing and querying pairwise distances between entity IDs.

## Features

- Reusable entity ID allocation and recycling
- Upper-triangular compressed storage to reduce memory usage
- High-frequency read/write friendly API:
  - `allocate_id()`
  - `free_id(id)`
  - `set_distance(u1, u2, distance)`
  - `get_distance(u1, u2)`

## Project Structure

- `src/`: GDExtension C++ source code
- `game/bin/distance_matrix.gdextension`: Godot extension declaration file
- `SConstruct`: SCons build script
- `doc_classes/DistanceMatrix.xml`: Godot class-reference style API document
- `API.md`: Project API documentation

## Requirements

- Godot 4.1+ (defined by `compatibility_minimum` in `distance_matrix.gdextension`)
- Python (for running SCons)
- SCons
- A working C++ toolchain (MSVC on Windows is recommended)
- `godot-cpp` submodule/directory prepared

## Build

Run in the project root:

```bash
scons target=template_debug
scons target=template_release
```

After building, platform-specific dynamic libraries are generated in `game/bin/` (for example, `.dll` on Windows).

## GDExtension Documentation System

This project is integrated with Godot's GDExtension documentation system:

- Custom XML docs are stored in `doc_classes/`
- `SConstruct` embeds XML docs for `editor` and `template_debug` targets

To generate or refresh XML doc stubs from registered classes, run this in the test Godot project directory:

```bash
godot --doctool ../ --gdextension-docs
```

## Use in Godot

1. Ensure `game/bin/distance_matrix.gdextension` has correct library paths and filenames.
2. Enable this GDExtension in your Godot project.
3. Create and use `DistanceMatrix` in scripts.

Example (GDScript):

```gdscript
var dm := DistanceMatrix.new()

var a := dm.allocate_id()
var b := dm.allocate_id()

dm.set_distance(a, b, 3.14)
print(dm.get_distance(a, b)) # 3.14

dm.free_id(a)
print(dm.get_distance(a, b)) # 0.0
```

## API Semantics

- Invalid IDs (negative or out of range) are safely ignored
- When `u1 == u2`:
  - `set_distance()` does not write
  - `get_distance()` returns `0.0`
- `free_id(id)` clears all distances associated with that ID and adds it to the reuse pool

## Documentation

- Detailed API docs: `API.md`
- Godot class-reference style docs: `doc_classes/DistanceMatrix.xml`

## License

This project is licensed under the MIT License. See `LICENSE` for details.
