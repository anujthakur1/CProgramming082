#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 10
#define TOTAL_QUESTIONS 20
#define LEADERBOARD_SIZE 20
#define FILENAME "leaderboard.txt"

// Structure for a question
typedef struct {
    char question[256];
    char options[4][100];
    char correctOption; 
} Question;

// Structure for leaderboard entry
typedef struct {
    char name[50];
    int score;
} LeaderboardEntry;

// Function prototypes
void loadQuestions(Question questions[], int *count, int category);
void shuffleQuestions(Question questions[], int count);
int startQuiz(char playerName[], int category);
void updateLeaderboard(char playerName[], int score);
void showLeaderboard();
void swap(LeaderboardEntry *a, LeaderboardEntry *b);

int main() {
    int choice, category;
    char playerName[50];

    srand(time(NULL));

    while (1) {
        printf("\n=== QUIZ GAME ===\n");
        printf("1. Play Quiz\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter your name: ");
                fgets(playerName, 50, stdin);
                playerName[strcspn(playerName, "\n")] = 0; // Remove newline

                printf("\nSelect Category:\n");
                printf("1. General Knowledge\n2. Science\n3. Technology\n");
                printf("Enter your choice: ");
                scanf("%d", &category);

                int score = startQuiz(playerName, category);
                printf("\nYour final score: %d\n", score);
                updateLeaderboard(playerName, score);
                break;

            case 2:
                showLeaderboard();
                break;

            case 3:
                printf("Thank you for playing!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Function to load questions based on category
void loadQuestions(Question questions[], int *count, int category) {
    FILE *file;
    char filename[20];

    switch (category) {
        case 1: strcpy(filename, "general.txt"); break;
        case 2: strcpy(filename, "science.txt"); break;
        case 3: strcpy(filename, "tech.txt"); break;
        default: printf("Invalid category!\n"); exit(1);
    }

    file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    *count = 0;
    while (fscanf(file, " %[^\n]", questions[*count].question) != EOF) {
        for (int i = 0; i < 4; i++) {
            fscanf(file, " %[^\n]", questions[*count].options[i]);
        }
        fscanf(file, " %c", &questions[*count].correctOption);
        (*count)++;
    }

    fclose(file);
}

// Function to shuffle questions randomly
void shuffleQuestions(Question questions[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int j = i + rand() % (count - i);
        Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

// Function to start the quiz
int startQuiz(char playerName[], int category) {
    Question questions[TOTAL_QUESTIONS];
    int questionCount = 0;
    loadQuestions(questions, &questionCount, category);
    shuffleQuestions(questions, questionCount);

    int score = 0;
    char answer;

    printf("\nStarting Quiz...\n");
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        printf("\nQ%d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("   %c) %s\n", 'a' + j, questions[i].options[j]);
        }
        printf("Enter your answer (a/b/c/d): ");
        scanf(" %c", &answer);

        if (answer == questions[i].correctOption) {
            score++;
        }
    }

    return score;
}

// Function to update the leaderboard
void updateLeaderboard(char playerName[], int score) {
    LeaderboardEntry leaderboard[LEADERBOARD_SIZE + 1];
    int count = 0;

    FILE *file = fopen(FILENAME, "r");
    if (file) {
        while (fscanf(file, " %49[^,],%d", leaderboard[count].name, &leaderboard[count].score) != EOF) {
            count++;
        }
        fclose(file);
    }

    // Add new entry
    strcpy(leaderboard[count].name, playerName);
    leaderboard[count].score = score;
    count++;

    // Sort leaderboard in descending order
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (leaderboard[j].score < leaderboard[j + 1].score) {
                swap(&leaderboard[j], &leaderboard[j + 1]);
            }
        }
    }

    // Keep only top 20 scores
    if (count > LEADERBOARD_SIZE) {
        count = LEADERBOARD_SIZE;
    }

    // Save leaderboard to file
    file = fopen(FILENAME, "w");
    if (file) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s,%d\n", leaderboard[i].name, leaderboard[i].score);
        }
        fclose(file);
    }
}

// Function to display the leaderboard
void showLeaderboard() {
    LeaderboardEntry leaderboard[LEADERBOARD_SIZE];
    int count = 0;

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No leaderboard data found.\n");
        return;
    }

    printf("\n=== Leaderboard ===\n");
    while (fscanf(file, " %49[^,],%d", leaderboard[count].name, &leaderboard[count].score) != EOF) {
        count++;
    }
    fclose(file);

    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d\n", i + 1, leaderboard[i].name, leaderboard[i].score);
    }
}

// Function to swap leaderboard entries
void swap(LeaderboardEntry *a, LeaderboardEntry *b) {
    LeaderboardEntry temp = *a;
    *a = *b;
    *b = temp;
}