# 🐍 贪吃蛇游戏 (Snake Game)

一个基于 Windows 控制台的经典贪吃蛇游戏，使用 C 语言编写，支持 WASD 实时控制。

## 📋 功能特性

- ✅ 经典贪吃蛇游戏玩法
- ✅ WASD 键实时控制方向
- ✅ ASCII 字符界面
- ✅ 实时得分显示
- ✅ 碰撞检测（墙壁和自身）
- ✅ 随机生成食物

## 🎮 游戏说明

### 控制方式

- **W** - 向上移动
- **A** - 向左移动
- **S** - 向下移动
- **D** - 向右移动
- **Q** - 退出游戏

### 游戏规则

1. 蛇用 `@` (头部) 和 `o` (身体) 表示
2. 食物用 `*` 表示
3. 吃到食物后，蛇会变长，得分增加 10 分
4. 撞到墙壁或自己的身体会导致游戏结束

### 游戏界面示例

```
╔══════════════════════════════════════╗  Score: 50
║                                      ║
║                                      ║
║              @oo                     ║
║                                      ║
║                    *                 ║
║                                      ║
║                                      ║
╚══════════════════════════════════════╝

Controls: W=Up, S=Down, A=Left, D=Right, Q=Quit
```

## 🔧 编译和运行

### 环境要求

- **操作系统**: Windows (使用了 `conio.h` 和 `windows.h`)
- **编译器**: GCC (推荐使用 MinGW)

### 安装 MinGW (如果尚未安装)

1. 下载 MinGW: https://sourceforge.net/projects/mingw/
2. 安装并将 MinGW 的 `bin` 目录添加到系统 PATH
3. 验证安装: 在命令行运行 `gcc --version`

### 编译方式

#### 方式 1: 使用 build.bat 脚本（推荐）

```batch
build.bat
```

#### 方式 2: 使用 Makefile

```batch
make
```

#### 方式 3: 直接使用 gcc 命令

```batch
gcc -Wall -O2 -o snake.exe src\snake.c
```

### 运行游戏

编译成功后，运行：

```batch
snake.exe
```

或使用 Makefile：

```batch
make run
```

## 📁 项目结构

```
snake-game/
├── src/
│   └── snake.c         # 游戏源代码
├── .github/
│   └── workflows/
│       └── build.yml   # GitHub Actions 构建配置
├── Makefile            # Make 构建脚本
├── build.bat           # Windows 批处理构建脚本
└── README.md           # 项目说明文档
```

## 🚀 持续集成

本项目使用 GitHub Actions 进行自动构建：

- **触发条件**: Push 或 Pull Request 到 main 分支
- **构建环境**: Windows Latest (使用 MinGW)
- **构建产物**: 自动生成的 `snake.exe` 可在 Actions 页面下载

查看构建状态和下载最新版本，请访问仓库的 Actions 标签页。

## 📝 技术实现

### 核心技术

- **非阻塞输入**: 使用 `conio.h` 的 `_kbhit()` 和 `_getch()` 实现实时键盘输入
- **屏幕控制**: 使用 Windows API (`windows.h`) 控制光标位置和清屏
- **帧率控制**: 使用 `Sleep()` 函数控制游戏循环速度 (100ms/帧)
- **碰撞检测**: 检测蛇头与边界、食物和自身的碰撞

### 数据结构

- **Position**: 存储 x, y 坐标
- **Snake**: 包含蛇身数组、长度和移动方向
- **Food**: 食物的位置
- **GameState**: 游戏状态（分数、是否结束）

## 🛠️ 可能的改进

- [ ] 添加难度等级（速度调整）
- [ ] 添加暂停功能
- [ ] 得分记录持久化（最高分）
- [ ] 添加障碍物
- [ ] 支持更多显示主题

## 📄 许可证

本项目仅供学习和娱乐使用。

## 👤 作者

贪吃蛇游戏 - Windows 控制台版本

---

**祝游戏愉快！ 🎮**
