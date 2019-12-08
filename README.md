# 说明
裁剪Chromium的base库的代码，并提供了相关的使用示例。目前只支持Windows平台的编译，后续会做其他平台的处理。
# Chromium源码说明
目前的源码是基于Chromium的分支79.0.3945.56开发，后续会跟随Chromium源码进行升级。
# 前置条件
### Windows
* 安装Visual Studio 2017 (>=15.7.2) or 2019 (>=16.0.0)
    * 必须安装MFC/ATL。
    * 安装windows sdk，且版本大于或等于10.0.18362
# 编译说明
封装了编译脚本build_debug.bat，并在src/examples目录下创建了很多示例代码，如果能把示例代码正常运行，就说明编译是什么问题的。
1. 运行build_debug.bat进行编译。
2. 运行src\Default\strings_example.exe

编译失败的情况，可参考[Chromium常见编译问题](https://bingoli.github.io/2019/11/18/chromium-build-trouble-shooting/)。