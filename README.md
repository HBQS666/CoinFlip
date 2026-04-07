# 🎮 CoinFlip 翻金币小游戏
基于 Qt 6 开发的经典翻金币益智小游戏，支持 macOS / Windows 双平台。

## 📖 项目介绍
- 经典玩法：点击金币翻转自身及上下左右相邻金币，目标是将所有金币翻为正面
- 多关卡系统：内置多难度关卡，逐步挑战
- 完整音效：点击、返回、胜利音效全覆盖
- 流畅动画：金币翻转动画、胜利弹窗弹跳动画
- 跨平台支持：一套代码，macOS / Windows 均可编译运行

## 🛠️ 开发环境
- Qt 6.10.2
- CMake 构建系统
- C++ 17

## 🚀 编译运行
### macOS
1.  用 Qt Creator 打开项目根目录的 `CMakeLists.txt`
2.  选择 `Qt 6.10.2 for macOS` 构建套件
3.  切换到 Release 配置，点击构建
4.  用 `macdeployqt` 打包成独立 `.app` 即可运行

### Windows
1.  安装 Qt 6.10.2 MinGW 64-bit 版本
2.  用 Qt Creator 打开项目，选择 MinGW 套件
3.  构建 Release 版本，用 `windeployqt` 打包依赖
4.  双击 `CoinFlip.exe` 即可运行

## 📦 项目结构
