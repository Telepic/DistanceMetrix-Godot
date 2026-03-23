#!/usr/bin/env python
import os

# 1. 获取 godot-cpp 配置好的核心编译环境
env = SConscript("godot-cpp/SConstruct")

# 2. 设置我们的 C++ 源码目录
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# 2.1 将 doc_classes/*.xml 打包进调试/编辑器构建，供 Godot 帮助系统读取
if env["target"] in ["editor", "template_debug"]:
    doc_data = env.GodotCPPDocData(
        "src/gen/doc_data.gen.cpp",
        source=Glob("doc_classes/*.xml")
    )
    sources.append(doc_data)

# 3. 拼接输出路径 (彻底解决后缀解析报错)
# env["suffix"] 是 godot-cpp 生成的中间标识 (如 .windows.template_debug.x86_64)
# env["SHLIBSUFFIX"] 是系统原生动态库扩展名 (Windows 下是 .dll)
target_path = "game/bin/libdistance_matrix" + env["suffix"] + env["SHLIBSUFFIX"]

# 4. 编译动态链接库
library = env.SharedLibrary(
    target=target_path,
    source=sources
)

Default(library)