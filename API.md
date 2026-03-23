# DistanceMatrix GDExtension 接口说明

本项目对外暴露一个 `RefCounted` 类：`DistanceMatrix`。

## 类概览

- **类名**: `DistanceMatrix`
- **继承**: `RefCounted`
- **用途**: 管理实体 ID 两两之间的距离值
- **存储结构**: 上三角压缩数组（节省内存）

## 方法说明

### `int allocate_id()`

分配并返回一个可用 ID。

- 若有已释放 ID，则优先复用
- 否则创建新 ID 并扩容内部存储

### `void free_id(int id)`

释放一个已分配 ID。

- 会将该 ID 与其他实体的距离清零
- 将该 ID 放入复用池
- 若 `id` 非法（越界或负数），不做任何操作

### `void set_distance(int u1, int u2, float distance)`

设置两个实体之间的距离值。

- `u1 == u2` 时忽略
- 任一 ID 非法时忽略
- 仅对有效、不同 ID 写入数据

### `float get_distance(int u1, int u2) const`

读取两个实体之间的距离值。

- `u1 == u2` 时返回 `0.0`
- 任一 ID 非法时返回 `0.0`
- 正常情况下返回最近一次设置的值

## 使用示例（GDScript）

```gdscript
var dm := DistanceMatrix.new()

var a := dm.allocate_id()
var b := dm.allocate_id()

dm.set_distance(a, b, 12.5)
print(dm.get_distance(a, b)) # 12.5

dm.free_id(a)
print(dm.get_distance(a, b)) # 0.0（a 释放后被清理）
```

## 文档维护建议

- 若新增/修改绑定方法，请同步更新 `DistanceMatrix.xml` 与本文件
- 方法描述建议包含：用途、参数约束、返回值、异常/非法输入行为
- 保持与 Godot Class Reference 风格一致（简明、可检索、可验证）
