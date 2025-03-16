#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <time.h>
#include <windows.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100
#define QUESTIONS_TO_ASK 10
#define TOTAL_QUESTIONS 200
#define MAX_NAME_LEN 50 

int timeout_happened = 0;
HANDLE hTimer = NULL;
HANDLE hTimerQueue = NULL;

const char *COLOR_END = "\033[0m";
const char *RED = "\033[1;31m";
const char *GREEN = "\033[1;32m";
const char *YELLOW = "\033[1;33m";
const char *BLUE = "\033[1;34m";
const char *PINK = "\033[1;35m";
const char *AQUA = "\033[1;36m";

// Styling for borders
const char *LINE = "===============================================";
const char *STAR_LINE = "***********************************************";

typedef struct
{
    char text[MAX_QUES_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

void CALLBACK timeout_handler(PVOID lpParam, BOOLEAN TimerOrWaitFired);
void start_timer(int seconds);
void stop_timer();
int read_questions(char *file_name, Question **questions);
void print_formatted_question(Question question);
void play_game(Question *questions, int no_of_questions, const char *player_name);
int use_lifeline(Question *question, int *lifeline);
void shuffle_questions(Question *questions, int no_of_questions);
void display_intro();
void display_results(int money_won, const char *player_name);
void display_end_line();
void save_results(const char *player_name, int money_won);

int main()
{
    srand(time(NULL));

    display_intro();

    // Get player's name
    char player_name[MAX_NAME_LEN];
    printf("\nEnter your name: ");
    fgets(player_name, MAX_NAME_LEN, stdin);
    fflush(stdout);

    Question *questions;
    int no_of_questions = read_questions("questions.txt", &questions);
    shuffle_questions(questions, no_of_questions);

    play_game(questions, QUESTIONS_TO_ASK, player_name);
    free(questions);

    if (hTimerQueue != NULL)
    {
        DeleteTimerQueue(hTimerQueue);
    }

    exit(0);
}

void CALLBACK timeout_handler(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
    timeout_happened = 1;
    printf("%s\n\nTime out!!!!!  Press Any Key...%s\n", RED, COLOR_END);
    fflush(stdout);
}

void start_timer(int seconds)
{
    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        printf("CreateTimerQueue failed (%d)\n", GetLastError());
        exit(1);
    }

    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)timeout_handler, NULL, seconds * 1000, 0, 0))
    {
        printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
        exit(1);
    }
}

void stop_timer()
{
    if (hTimer != NULL)
    {
        DeleteTimerQueueTimer(hTimerQueue, hTimer, NULL);
        hTimer = NULL;
    }
}

void shuffle_questions(Question *questions, int no_of_questions)
{
    for (int i = 0; i < no_of_questions; i++)
    {
        int j = rand() % no_of_questions;
        Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void display_intro()
{
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Clear the screen
    system("cls");

    // Set text color to Yellow for "QUIZ C"
    SetConsoleTextAttribute(hConsole, 14); // 14 = Yellow
    printf("%s\n", LINE);
    printf("  QQQQQ    U   U   III   ZZZZZ      CCCC  \n");
    printf(" Q     Q   U   U    I       Z       C      \n");
    printf(" Q     Q   U   U    I      Z        C      \n");
    printf(" Q     Q   U   U    I     Z         C      \n");
    printf("  QQQQQQ   UUUUU   III   ZZZZZ      CCCC  \n");
    printf("        Q    \n");
    printf("%s\n", LINE);

    // Set text color to Aqua for "MADE BY TEAM ELITE"
    SetConsoleTextAttribute(hConsole, 11); // 11 = Aqua (Cyan)
    printf("\n%s\n", STAR_LINE);
    printf("             MADE BY TEAM ELITE\n");
    printf("%s\n", STAR_LINE);

    // Reset color to default (White)
    SetConsoleTextAttribute(hConsole, 7);

    printf("\nPress ENTER to Start...");
    getchar(); // Wait for user input
}

void play_game(Question *questions, int no_of_questions, const char *player_name)
{
    int money_won = 0;
    int lifeline[] = {1, 1};                                                                    
    int prize_money[] = {1000, 3000, 10000, 100000, 300000, 600000, 12000000, 30000000, 50000000 ,70000000}; 

    for (int i = 0; i < no_of_questions; i++)
    {
        int answered = 0;
        questions[i].prize_money = prize_money[i]; 

        printf("\n%s%s ", YELLOW, STAR_LINE);
        printf("\n%sQuestion for Rs %d%s\n", BLUE, questions[i].prize_money, COLOR_END);
        printf("\n%s%s ", YELLOW, STAR_LINE);
        while (!answered)
        {
            print_formatted_question(questions[i]);
            start_timer(30);

            char ch;
            scanf(" %c", &ch);
            stop_timer();

            if (timeout_happened) 
            {
                printf("%s\nTime's up! Game Over.%s\n", RED, COLOR_END);
                display_results(money_won, player_name);
                display_end_line();
                save_results(player_name, money_won);
                return;
            }

            ch = toupper(ch);

            if (ch == 'L') // If the player chooses a lifeline
            {
                int lifeline_used = use_lifeline(&questions[i], lifeline);
                if (lifeline_used == 1)
                {
                    continue; // Continue to the next iteration of the current question
                }
                else if (lifeline_used == 2)
                {
                    break; // Skip the question if the player chooses to skip
                }
            }
            else if (ch == questions[i].correct_option) // If the player's answer is correct
            {
                printf("%s\nCorrect!%s\n", GREEN, COLOR_END);
                money_won += questions[i].prize_money;
                printf("\n%sYou have won: Rs %d%s\n", BLUE, money_won, COLOR_END);
                answered = 1; // Mark the question as answered
            }
            else // If the player's answer is wrong
            {
                // End the game immediately when a wrong answer is selected
                printf("%s\nWrong! Correct answer is %c.%s\n", RED, questions[i].correct_option, COLOR_END);
                printf("\n%sGame Over! You won Rs %d.%s\n", RED, money_won, COLOR_END);
                display_results(money_won, player_name);
                display_end_line();
                save_results(player_name, money_won);
                return; // Exit the game immediately after a wrong answer
            }
        }
    }
}

void display_results(int money_won, const char *player_name)
{
    printf("\n\n%s%sGame Over! Your total winnings are: Rs %d%s%s\n", GREEN, STAR_LINE, money_won, STAR_LINE, COLOR_END);
}

void display_end_line()
{
    printf("\n\n%s%s %sThank You for Playing! %s%s\n", YELLOW, STAR_LINE, AQUA, PINK, STAR_LINE);
}

void save_results(const char *player_name, int money_won)
{
    FILE *file = fopen("results.txt", "a");
    if (file == NULL)
    {
        printf("\nUnable to open results file for writing.\n");
        return;
    }

    fprintf(file, "Player: %s | Money Won: Rs %d\n\n", player_name, money_won);
    fclose(file);
}

int use_lifeline(Question *question, int *lifeline)
{
    printf("\n\n%sAvailable Lifelines:%s", PINK, COLOR_END);
    if (lifeline[0])
        printf("\n%s1. Fifty-Fifty (50/50)%s", PINK, COLOR_END);
    if (lifeline[1])
        printf("\n%s2. Skip the Question%s", PINK, COLOR_END);
    printf("\n%sChoose a lifeline or 0 to return: %s", PINK, COLOR_END);

    char ch;
    scanf(" %c", &ch);

    switch (ch)
    {
    case '1':
        if (lifeline[0])
        {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2)
            {
                int num = rand() % 4;
                if ((num + 'A') != question->correct_option &&
                    question->options[num][0] != '\0')
                {
                    strcpy(question->options[num], ""); // Hide option
                    removed++;
                }
            }
            return 1;
        }
        break;
    case '2':
        if (lifeline[1])
        {
            lifeline[1] = 0;
            return 2;
        }
        break;
    default:
        printf("\n%sReturning to the Question.%s", PINK, COLOR_END);
        break;
    }
    return 0;
}

void print_formatted_question(Question question)
{
    printf("\n\n%s%s%s", YELLOW, question.text, COLOR_END);
    for (int i = 0; i < 4; i++)
    {
        if (question.options[i][0] != '\0')
        {
            printf("\n%s%c. %s%s", AQUA, ('A' + i), question.options[i], COLOR_END);
        }
    }
    printf("\n%sHurry!! You have only %d Seconds to answer..%s", YELLOW, question.timeout, COLOR_END);
    printf("\n%sEnter your answer (A, B, C, or D) or L for lifeline: %s", GREEN, COLOR_END);
}

int read_questions(char *file_name, Question **questions)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("\nUnable to open the questions bank.");
        exit(0);
    }

    int no_of_questions = 0;
    *questions = (Question *)malloc(TOTAL_QUESTIONS * sizeof(Question));

    while (fscanf(file, " %[^\n]s", (*questions)[no_of_questions].text) != EOF)
    {
        for (int j = 0; j < 4; j++)
        {
            fscanf(file, " %[^\n]s", (*questions)[no_of_questions].options[j]);
        }
        fscanf(file, " %c", &(*questions)[no_of_questions].correct_option);
        fscanf(file, " %d", &(*questions)[no_of_questions].timeout);

        no_of_questions++;
    }

    fclose(file);
    return no_of_questions;
}
