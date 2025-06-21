##### 生成工程文件



```
# 生成CMakeList
cmake ../QXlsx/   -DCMAKE_INSTALL_PREFIX="D:/DemoWorkSpace/qt_demo/app_demo/install"  -DCMAKE_BUILD_TYPE=Release
# 执行编译，编译为库文件
cmake --build .
# 执行安装
cmake --install .
```

