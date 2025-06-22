##### vs2022 从qt模板创建工程，选择初始模块，开发过程增加了模块，需要重新添加新增的模块，否则头文件中导入找不到

![image-20250621190211011](assets/image-20250621190211011.png![image-20250621190240828](assets/image-20250621190240828.png)

##### 查看已经配置的模块

![image-20250621190316378](assets/image-20250621190316378.png)

##### 打开模块选择页

![image-20250621190330092](assets/image-20250621190330092.png)

##### 增加新增的模块

Qt VS Tools的配置改变的是pro文件的配置，不改变CMakeList配置

![image-20250621190344443](assets/image-20250621190344443.png)

##### 配置qml调试

![image-20250621190504158](assets/image-20250621190504158.png)

##### 库路径设置

![image-20250621190608894](assets/image-20250621190608894.png)

##### qt其他编译设置

![image-20250621190706123](assets/image-20250621190706123.png)

##### 使用cmake如果调用的是Visual Studio 2022 (MSVC v143) 工具链生成的就是vs的解决方案

```bash
cmake QXlsx/ -DCMAKE_INSTALL_PREFIX="D:/DemoWorkSpace/qt_demo/app_demo/QXlsx/install" -DCMAKE_BUILD_TYPE=Release
```

##### 后面cmake --build .编译的就是sln，截图显示编译的QXlsx.vcxproj，不加参数默认是debug

![image-20250621221703904](assets/image-20250621221703904.png)

##### 指定编译配置

```bash
cmake --build . --config Release -- /maxcpucount
```

##### 指定编译器

```bash
cmake QXlsx/ \
  -G "MinGW Makefiles" \
  -DCMAKE_INSTALL_PREFIX="D:/DemoWorkSpace/qt_demo/app_demo/QXlsx/install" \
  -DCMAKE_BUILD_TYPE=Release
```

##### 未指定编译器时优先级

在 Windows 上，如果你没有通过 `-G` 显式指定生成器，**CMake 默认会优先选择 MSVC（Visual Studio）编译器**，而不是 MinGW。



##### CMake 的行为逻辑是这样的：

- 在 Windows 上，CMake 默认使用的构建工具链取决于：
  - 当前平台（Windows）
  - 是否检测到 Visual Studio 安装
  - 是否有多个可用的编译器路径在 `PATH` 中

##### ⚠️ **但 CMake 不是根据 `PATH` 来决定默认编译器的！**

它优先查找已安装的 Visual Studio 工具链（MSVC），因为这是 Windows 上最“原生”的开发环境。

##### 示例：不同情况下的默认行为

| 场景                                                         | 默认生成器              | 使用的编译器    |
| ------------------------------------------------------------ | ----------------------- | --------------- |
| 只有 MinGW-w64 在 PATH 中                                    | `MinGW Makefiles`       | g++             |
| 同时安装了 MinGW-w64 和 MSVC (VS)                            | `Visual Studio XX 20XX` | MSVC (`cl.exe`) |
| 没有 Visual Studio，但有 MinGW                               | `MinGW Makefiles`       | g++             |
| 指定了 `-G "MinGW Makefiles"`                                | 强制使用 MinGW          | g++             |
| 指定了 `-G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++` | 使用 Ninja + GCC        | g++             |

##### 方法一：显式指定生成器

```bash
cmake -G "MinGW Makefiles" ..
```

##### 方法二：使用完整路径指定编译器（可选）

```bash
cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER="D:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="D:/mingw64/bin/g++.exe"
```

##### 方法三：使用 Ninja + MinGW

如果你想用更现代的构建系统（如 Ninja），也可以这样做：

```bash
cmake .. -G "Ninja" -DCMAKE_C_COMPILER="gcc" -DCMAKE_CXX_COMPILER="g++"
```

##### 如果你打开的文件夹下有CMakeList文件，Vs会自动识别生成sln

![image-20250621230134651](assets/image-20250621230134651.png)

##### 打开生成sln就进入解决方案，再切换到输出窗口里才显示CMake，才能看到CMake输出

![image-20250621230247887](assets/image-20250621230247887.png)

##### E2919命令行错误: 通过 --current_directory 选项指定的目录不是目录

我通过删除.vs目录、sln解决方案、工程目录解决了，后面只剩下CMakeList文件了，只能通过CMakeList启动项目了

![image-20250622013920983](assets/image-20250622013920983.png)

##### 按照顺序添加文件头和源文件，报错的原因是没有包含cpp文件导致的

![image-20250622014020585](assets/image-20250622014020585.png)

##### VS .Net项目sln解决方案工程属性中设置项目属性

![image-20250622132344305](assets/image-20250622132344305.png)

##### 要使用CMakeList启动程序就不要sln文件了，否则出现问题，VS C++解决方案中的工程属性中设置库路径和包含路径

包含目录都是include目录

![image-20250622133352243](assets/image-20250622133352243.png)

库目录是lib目录

![image-20250622133417686](assets/image-20250622133417686.png)

window运行库和库目录设置用来区分系统运行库和第三方运行库

![image-20250622133641344](assets/image-20250622133641344.png)

##### 创建项目时使用了预编译头文件，每个头文件都要包含stdafx.h头文件，否则报错



##### CMakeList项目，加载不到项目工程文件demo.vcxproj，编译配置就看不到启动项配置，启动配置定义在demo.vcxproj，会显示CMakeList![](assets/image-20250622134118291.png)



![image-20250622134118291](assets/image-20250622134118291.png)

##### CMakeList中配置项说明

find_package属性相当于sln项目中工程属性的库目录设置，是查到dll或lib文件的目录（选择文件窗口图片名字没有明确命名按照时间顺序排列插入）

![image-20250622134713806](assets/image-20250622134713806.png)

add_subdirectory相当于sln中的子工程demo.vcxproj文件，每个子项目都有自己的CMakeList，每个子项目有自己的ReadMe和assets资源，且会编译解决方案时，会编译子项目的代码

![image-20250622135452814](assets/image-20250622135452814.png)
