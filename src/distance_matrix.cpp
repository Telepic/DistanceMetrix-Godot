#include "distance_matrix.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void DistanceMatrix::_bind_methods() {
    ClassDB::bind_method(D_METHOD("allocate_id"), &DistanceMatrix::allocate_id);
    ClassDB::bind_method(D_METHOD("free_id", "id"), &DistanceMatrix::free_id);
    ClassDB::bind_method(D_METHOD("set_distance", "u1", "u2", "distance"), &DistanceMatrix::set_distance);
    ClassDB::bind_method(D_METHOD("get_distance", "u1", "u2"), &DistanceMatrix::get_distance);
}

DistanceMatrix::DistanceMatrix() {}
DistanceMatrix::~DistanceMatrix() {}

int DistanceMatrix::allocate_id() {
    // 1. 优先从废弃池中复用 ID (O(1) 操作)
    if (!free_ids.is_empty()) {
        int last_index = free_ids.size() - 1;
        int reused_id = free_ids[last_index];
        free_ids.resize(last_index); // 弹出末尾元素
        return reused_id;
    }

    // 2. 如果没有废弃 ID，则分配新 ID 并动态扩容
    int new_id = max_allocated_id++;
    
    int new_array_size = (max_allocated_id * (max_allocated_id - 1)) / 2;
    int old_array_size = distances.size();
    
    // 自动保留原有数据并扩展内存
    distances.resize(new_array_size); 
    
    // 获取可写指针，将新分配的内存极速清零，防止残留垃圾数据
    double *write_ptr = distances.ptrw();
    for (int i = old_array_size; i < new_array_size; i++) {
        write_ptr[i] = 0.0;
    }

    return new_id;
}

void DistanceMatrix::free_id(int id) {
    if (id < 0 || id >= max_allocated_id) return;

    // 清理该实体与其他所有存活实体的距离数据
    clear_distances_for_id(id);

    // 将 ID 放入回收池备用
    free_ids.push_back(id);
}

void DistanceMatrix::clear_distances_for_id(int id) {
    for (int other = 0; other < max_allocated_id; other++) {
        if (id == other) continue;
        set_distance(id, other, 0.0);
    }
}

void DistanceMatrix::set_distance(int u1, int u2, double distance) {
    if (u1 == u2 || u1 < 0 || u2 < 0 || u1 >= max_allocated_id || u2 >= max_allocated_id) return;
    
    // 使用 ptrw() 直接写入，绕过 Godot 容器的安全检查机制，性能最大化
    distances.ptrw()[get_index(u1, u2)] = distance;
}

double DistanceMatrix::get_distance(int u1, int u2) const {
    if (u1 == u2 || u1 < 0 || u2 < 0 || u1 >= max_allocated_id || u2 >= max_allocated_id) return 0.0;
    
    // 使用 ptr() 直接读取
    return distances.ptr()[get_index(u1, u2)];
}