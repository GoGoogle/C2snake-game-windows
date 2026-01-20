# Makefile for Snake Game (Windows)
# 需要安装 MinGW 或其他 GCC 工具链

CC = gcc
CFLAGS = -Wall -O2
TARGET = snake.exe
SRC = src/snake.c

# 默认目标：编译游戏
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo Build complete! Run './$(TARGET)' to play.

# 清理构建产物
clean:
	del /Q $(TARGET) 2>nul || echo Nothing to clean.

# 运行游戏
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
