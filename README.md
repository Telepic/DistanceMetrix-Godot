# distance_matrix

一个基于 Godot 4 GDExtension（C++）实现的距离矩阵组件，用于高效存储和查询实体 ID 两两之间的距离值。

## 功能特性

- 提供可复用的实体 ID 分配/回收机制
- 使用上三角压缩存储距离矩阵，节省内存
- 提供高频读写友好的接口：
  - `allocate_id()`
  - `free_id(id)`
  - `set_distance(u1, u2, distance)`
  - `get_distance(u1, u2)`

## 项目结构

- `src/`：GDExtension C++ 源码
- `game/bin/distance_matrix.gdextension`：Godot 扩展声明文件
- `SConstruct`：SCons 构建脚本
- `DistanceMatrix.xml`：Godot class reference 风格接口文档
- `API.md`：项目内接口说明（中文）

## 环境要求

- Godot 4.1+（由 `distance_matrix.gdextension` 中 `compatibility_minimum` 指定）
- Python（用于运行 SCons）
- SCons
- 可用的 C++ 编译工具链（Windows 下可使用 MSVC）
- `godot-cpp` 子模块/目录已准备完成

## 构建方式

在项目根目录执行：

```bash
scons target=template_debug
scons target=template_release
```

构建完成后会在 `game/bin/` 生成对应平台动态库（如 Windows 下的 `.dll`）。

## 在 Godot 中使用

1. 确保 `game/bin/distance_matrix.gdextension` 路径和库文件名正确。
2. 在 Godot 项目中启用该 GDExtension。
3. 在脚本中直接创建并使用 `DistanceMatrix`。

示例（GDScript）：

```gdscript
var dm := DistanceMatrix.new()

var a := dm.allocate_id()
var b := dm.allocate_id()

dm.set_distance(a, b, 3.14)
print(dm.get_distance(a, b)) # 3.14

dm.free_id(a)
print(dm.get_distance(a, b)) # 0.0
```

## 接口语义说明

- 非法 ID（负数或越界）会被安全忽略
- `u1 == u2` 时：
  - `set_distance()` 不执行写入
  - `get_distance()` 返回 `0.0`
- `free_id(id)` 会清空该 ID 与其他 ID 的距离值，并将其放入复用池

## 文档

- 详细接口文档见 `API.md`
- Godot class reference 风格文档见 `DistanceMatrix.xml`

## License

当前仓库未声明许可证。建议补充 `LICENSE` 文件以明确使用与分发条款。
