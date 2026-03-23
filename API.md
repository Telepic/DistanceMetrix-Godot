# DistanceMatrix GDExtension API

This project exposes one `RefCounted` class: `DistanceMatrix`.

## Class Overview

- **Class name**: `DistanceMatrix`
- **Inherits**: `RefCounted`
- **Purpose**: Store pairwise distances between entity IDs
- **Storage model**: Upper-triangular compressed array (memory efficient)

## Method Reference

### `int allocate_id()`

Allocates and returns an available ID.

- Reuses an ID from the free pool when possible
- Otherwise creates a new ID and resizes internal storage

### `void free_id(int id)`

Releases a previously allocated ID.

- Clears all distances related to this ID
- Pushes the ID into the reuse pool
- Does nothing if `id` is invalid (negative or out of range)

### `void set_distance(int u1, int u2, float distance)`

Sets the distance value between two entities.

- Ignored when `u1 == u2`
- Ignored when either ID is invalid
- Writes only for valid and distinct IDs

### `float get_distance(int u1, int u2) const`

Gets the distance value between two entities.

- Returns `0.0` when `u1 == u2`
- Returns `0.0` when either ID is invalid
- Otherwise returns the last value written for that pair

## Usage Example (GDScript)

```gdscript
var dm := DistanceMatrix.new()

var a := dm.allocate_id()
var b := dm.allocate_id()

dm.set_distance(a, b, 12.5)
print(dm.get_distance(a, b)) # 12.5

dm.free_id(a)
print(dm.get_distance(a, b)) # 0.0 (cleared after releasing a)
```

## Documentation Maintenance Notes

- When adding or changing bound methods, update `doc_classes/DistanceMatrix.xml` and this file together.
- Each method description should include intent, parameter constraints, return behavior, and invalid-input behavior.
- Keep style aligned with Godot Class Reference conventions: concise, searchable, and verifiable.
