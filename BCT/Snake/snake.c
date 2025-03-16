#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define HEIGHT 20       
#define WIDTH 80         

int snakeTailX[100], snakeTailY[100];
int snakeTailLen;
int gameover, key, score;
int x, y, fruitx, fruity;
char playerName[50];

int highestScore = 0;
char highestPlayer[50];

COORD coord = {0, 0};  

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void show_cursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void update_highscore(const char* playerName, int score) {
    if (score > highestScore) {
        highestScore = score;
        strcpy(highestPlayer, playerName);
    }
}

void save_score(const char* playerName, int score) {
    FILE *file = fopen("game_records.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", playerName, score);
        fclose(file);
    }
}

void load_records() {
    FILE *file = fopen("game_records.txt", "r");
    if (file != NULL) {
        char line[100];
        int scoreRecord;
        char name[50];

        highestScore = 0;
        strcpy(highestPlayer, "");

        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%s %d", name, &scoreRecord);
            if (scoreRecord > highestScore) {
                highestScore = scoreRecord;
                strcpy(highestPlayer, name);
            }
        }

        fclose(file);
    }
}

void setup() {
    gameover = 0;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitx = rand() % (WIDTH - 2) + 1;
    fruity = rand() % (HEIGHT - 2) + 1;
    score = 0;
}

void draw() {
    gotoxy(0, 0);

    for (int i = 0; i < WIDTH + 2; i++)   
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH)  
                printf("#");
            else if (i == y && j == x)  
                printf("O");
            else if (i == fruity && j == fruitx)   
                printf("*");
            else {
                int prTail = 0;
                for (int k = 0; k < snakeTailLen; k++) {  
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        printf("o");
                        prTail = 1;
                    }
                }
                if (!prTail)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)  
        printf("#");
    printf("\n");

    printf("score = %d", score);
    printf("\nPress W, A, S, D for movement.\nPress X to quit the game.");
}

void input() {
    if (kbhit()) {
        switch (tolower(getch())) {
        case 'a':
            if (key != 2)
                key = 1;
            break;
        case 'd':
            if (key != 1)
                key = 2;
            break;
        case 'w':
            if (key != 4)
                key = 3;
            break;
        case 's':
            if (key != 3)
                key = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (key) {
    case 1:
        x--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y--;
        break;
    case 4:
        y++;
        break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameover = 1;

    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            gameover = 1;
    }

    if (x == fruitx && y == fruity) {
        fruitx = rand() % (WIDTH - 2) + 1;
        fruity = rand() % (HEIGHT - 2) + 1;
        score += 10;
        snakeTailLen++;
    }
}

void view_records() {
    FILE *file = fopen("game_records.txt", "r");
    if (file != NULL) {
        char line[100];

        printf("\n--- Highest Score: %d by %s ---\n", highestScore, highestPlayer);
        printf("\n--- Game Records ---\n");

        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }

        fclose(file);
    }
}

void main_menu() {
    int choice;
    while (1) {
        printf("Welcome to the Snake Game!\n");
        printf("1. View Game Records\n");
        printf("2. Play New Game\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            view_records();
            break;
        } else if (choice == 2) {
            printf("Enter your name (or press Enter to use name 'Player'): ");
            getchar();
            fgets(playerName, sizeof(playerName), stdin);

            playerName[strcspn(playerName, "\n")] = '\0';

            if (strlen(playerName) == 0) {
                strcpy(playerName, "Player");
            }

            system("cls");

            setup();
            while (!gameover) {
                draw();
                input();
                logic();
                Sleep(33);
            }
            save_score(playerName, score);
            update_highscore(playerName, score);
            printf("\nGame Over! Your score is %d\n", score);
            break;
        } else {
            printf("Invalid choice, please try again!\n\n");
        }
    }
}

int main() {
    hide_cursor();
    load_records();
    main_menu();
    show_cursor();
    return 0;
}
