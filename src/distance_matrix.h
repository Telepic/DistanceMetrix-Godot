#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/packed_float64_array.hpp>
#include <godot_cpp/variant/packed_int32_array.hpp>

namespace godot {

class DistanceMatrix : public RefCounted {
    // GDExtension 的标准宏，替代了纯 C 中那几百行样板代码
    GDCLASS(DistanceMatrix, RefCounted)

private:
    int max_allocated_id = 0;
    PackedFloat64Array distances;
    PackedInt32Array free_ids;

    // 内联的索引计算，保证极致查询速度
    _FORCE_INLINE_ int get_index(int i, int j) const {
        if (i < j) {
            int temp = i;
            i = j;
            j = temp;
        }
        return (i * (i - 1)) / 2 + j;
    }

    // 内部方法：清理关联数据
    void clear_distances_for_id(int id);

protected:
    // 绑定方法到 Godot 引擎
    static void _bind_methods();

public:
    DistanceMatrix();
    ~DistanceMatrix();

    int allocate_id();
    void free_id(int id);
    void set_distance(int u1, int u2, double distance);
    double get_distance(int u1, int u2) const;
};

} // namespace godot