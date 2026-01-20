#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 800

// 方向常量
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

// 游戏对象类型
typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    char direction;
} Snake;

typedef struct {
    Position pos;
} Food;

typedef struct {
    int score;
    int gameOver;
} GameState;

// 全局变量
Snake snake;
Food food;
GameState gameState;

// 函数声明
void initGame();
void drawGame();
void updateGame();
void handleInput();
void generateFood();
int checkCollision();
void moveCursor(int x, int y);
void clearScreen();

// 移动光标到指定位置
void moveCursor(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 清屏
void clearScreen() {
    system("cls");
}

// 初始化游戏
void initGame() {
    srand((unsigned int)time(NULL));
    
    // 初始化蛇
    snake.length = 3;
    snake.direction = RIGHT;
    
    // 蛇从中间偏左开始
    for (int i = 0; i < snake.length; i++) {
        snake.body[i].x = WIDTH / 2 - i;
        snake.body[i].y = HEIGHT / 2;
    }
    
    // 初始化游戏状态
    gameState.score = 0;
    gameState.gameOver = 0;
    
    // 生成第一个食物
    generateFood();
}

// 生成食物
void generateFood() {
    int validPosition = 0;
    
    while (!validPosition) {
        food.pos.x = rand() % (WIDTH - 2) + 1;
        food.pos.y = rand() % (HEIGHT - 2) + 1;
        
        // 检查食物是否生成在蛇身上
        validPosition = 1;
        for (int i = 0; i < snake.length; i++) {
            if (snake.body[i].x == food.pos.x && snake.body[i].y == food.pos.y) {
                validPosition = 0;
                break;
            }
        }
    }
}

// 绘制游戏界面
void drawGame() {
    clearScreen();
    
    // 绘制顶部边框和得分
    printf("╔");
    for (int i = 0; i < WIDTH - 2; i++) printf("═");
    printf("╗  Score: %d\n", gameState.score);
    
    // 绘制游戏区域
    for (int y = 1; y < HEIGHT - 1; y++) {
        printf("║");
        for (int x = 1; x < WIDTH - 1; x++) {
            int isSnake = 0;
            int isHead = 0;
            
            // 检查是否是蛇身
            for (int i = 0; i < snake.length; i++) {
                if (snake.body[i].x == x && snake.body[i].y == y) {
                    isSnake = 1;
                    if (i == 0) isHead = 1;
                    break;
                }
            }
            
            if (isHead) {
                printf("@");  // 蛇头
            } else if (isSnake) {
                printf("o");  // 蛇身
            } else if (food.pos.x == x && food.pos.y == y) {
                printf("*");  // 食物
            } else {
                printf(" ");
            }
        }
        printf("║\n");
    }
    
    // 绘制底部边框
    printf("╚");
    for (int i = 0; i < WIDTH - 2; i++) printf("═");
    printf("╝\n");
    
    // 显示控制说明
    printf("\nControls: W=Up, S=Down, A=Left, D=Right, Q=Quit\n");
}

// 处理输入
void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        
        // 转换为小写
        if (key >= 'A' && key <= 'Z') {
            key = key + 32;
        }
        
        // 退出游戏
        if (key == 'q') {
            gameState.gameOver = 1;
            return;
        }
        
        // 更新方向（不能反向移动）
        if (key == UP && snake.direction != DOWN) {
            snake.direction = UP;
        } else if (key == DOWN && snake.direction != UP) {
            snake.direction = DOWN;
        } else if (key == LEFT && snake.direction != RIGHT) {
            snake.direction = LEFT;
        } else if (key == RIGHT && snake.direction != LEFT) {
            snake.direction = RIGHT;
        }
    }
}

// 检查碰撞
int checkCollision() {
    Position head = snake.body[0];
    
    // 检查是否撞墙
    if (head.x <= 0 || head.x >= WIDTH - 1 || head.y <= 0 || head.y >= HEIGHT - 1) {
        return 1;
    }
    
    // 检查是否撞到自己
    for (int i = 1; i < snake.length; i++) {
        if (head.x == snake.body[i].x && head.y == snake.body[i].y) {
            return 1;
        }
    }
    
    return 0;
}

// 更新游戏状态
void updateGame() {
    // 计算新的头部位置
    Position newHead = snake.body[0];
    
    switch (snake.direction) {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
    }
    
    // 移动蛇身（从尾部开始向前移动）
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    
    // 更新头部位置
    snake.body[0] = newHead;
    
    // 检查是否吃到食物
    if (newHead.x == food.pos.x && newHead.y == food.pos.y) {
        // 增加长度
        if (snake.length < MAX_SNAKE_LENGTH) {
            snake.length++;
        }
        // 增加分数
        gameState.score += 10;
        // 生成新食物
        generateFood();
    }
    
    // 检查碰撞
    if (checkCollision()) {
        gameState.gameOver = 1;
    }
}

// 主函数
int main() {
    // 设置控制台标题
    SetConsoleTitle(TEXT("Snake Game - WASD to move, Q to quit"));
    
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    // 初始化游戏
    initGame();
    
    // 游戏主循环
    while (!gameState.gameOver) {
        drawGame();
        handleInput();
        updateGame();
        Sleep(100);  // 控制帧率，100ms = 10fps
    }
    
    // 游戏结束
    clearScreen();
    printf("\n\n");
    printf("  ╔════════════════════════════════╗\n");
    printf("  ║        GAME OVER!              ║\n");
    printf("  ║                                ║\n");
    printf("  ║     Final Score: %-5d        ║\n", gameState.score);
    printf("  ║                                ║\n");
    printf("  ║  Press any key to exit...      ║\n");
    printf("  ╚════════════════════════════════╝\n");
    printf("\n");
    
    _getch();
    
    return 0;
}
