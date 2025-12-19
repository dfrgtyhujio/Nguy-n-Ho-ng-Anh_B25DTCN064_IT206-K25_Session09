#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_QUESTIONS 10
#define PLAY_QUESTIONS 5

// ===== STRUCT =====
struct Question {
    char content[200];
    char A[100];
    char B[100];
    char C[100];
    char D[100];
    char correct;
};

struct Player {
    char name[50];
    int score;
};

// ===== HAM NHAP TEN =====
void inputPlayerName(struct Player *player) {
    printf("Nhap ten nguoi choi: ");
    fgets(player->name, sizeof(player->name), stdin);
    player->name[strcspn(player->name, "\n")] = '\0';
    player->score = 0;
}

// ===== HAM TRON CAU HOI =====
void shuffleQuestions(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// ===== HAM HOI 1 CAU =====
int askQuestion(struct Question q, int number) {
    char answer;

    printf("\nCau %d: %s\n", number, q.content);
    printf("A. %s\n", q.A);
    printf("B. %s\n", q.B);
    printf("C. %s\n", q.C);
    printf("D. %s\n", q.D);
    printf("Nhap dap an (A-D): ");
    scanf(" %c", &answer);

    if (answer == q.correct || answer == q.correct + 32) {
        printf("=> Dung!\n");
        return 1;
    } else {
        printf("=> Sai! Dap an dung la %c\n", q.correct);
        return 0;
    }
}

// ===== HAM CHOI GAME =====
void playQuiz(struct Player *player, struct Question questions[]) {
    int index[TOTAL_QUESTIONS];

    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        index[i] = i;
    }

    shuffleQuestions(index, TOTAL_QUESTIONS);

    printf("\n===== BAT DAU TRO CHOI =====\n");

    for (int i = 0; i < PLAY_QUESTIONS; i++) {
        player->score += askQuestion(questions[index[i]], i + 1);
    }
}

// ===== HAM LUU DIEM =====
void saveScoreToFile(struct Player player) {
    FILE *fp = fopen("score.txt", "a");
    if (fp == NULL) {
        printf("Khong mo duoc file score.txt\n");
        return;
    }
    fprintf(fp, "%s %d\n", player.name, player.score);
    fclose(fp);
}

// ===== HAM HIEN THI BANG XEP HANG =====
void showRanking() {
    FILE *fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("Chua co du lieu bang xep hang!\n");
        return;
    }

    char name[50];
    int score;

    printf("\n===== BANG XEP HANG =====\n");
    printf("%-20s %s\n", "Ten", "Diem");
    printf("------------------------------\n");

    while (fscanf(fp, "%s %d", name, &score) != EOF) {
        printf("%-20s %d\n", name, score);
    }

    fclose(fp);
}

// ===== MAIN =====
int main() {
    srand(time(NULL));

    struct Question questions[TOTAL_QUESTIONS] = {
        {"Ngon ngu C do ai sang lap?",
         "Dennis Ritchie", "James Gosling", "Bjarne Stroustrup", "Guido van Rossum", 'A'},

        {"Tu khoa dung de khai bao hang so trong C la?",
         "static", "const", "typedef", "define", 'B'},

        {"Kieu du lieu dung de luu so nguyen la?",
         "float", "double", "int", "char", 'C'},

        {"Toan tu dung de gan gia tri la?",
         "==", "=", "!=", "<=", 'B'},

        {"Ham nao dung de in du lieu ra man hinh?",
         "scanf()", "printf()", "gets()", "puts()", 'B'},

        {"Vong lap nao luon thuc hien it nhat 1 lan?",
         "for", "while", "do-while", "switch", 'C'},

        {"Ky tu ket thuc chuoi trong C la?",
         "\\n", "\\0", "EOF", "NULL", 'B'},

        {"Thu vien nao can de dung ham rand()?",
         "math.h", "stdlib.h", "string.h", "time.h", 'B'},

        {"Toan tu && trong C la phep gi?",
         "Hoac", "Va", "Nhan", "Chia", 'B'},

        {"Ham main() trong C tra ve kieu du lieu nao?",
         "void", "float", "char", "int", 'D'}
    };

    struct Player player;

    inputPlayerName(&player);
    playQuiz(&player, questions);

    printf("\n===== KET QUA =====\n");
    printf("Nguoi choi: %s\n", player.name);
    printf("Diem so: %d/%d\n", player.score, PLAY_QUESTIONS);

    saveScoreToFile(player);
    showRanking();

    return 0;
}
