#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define RW 10
#define HP 1
#define BP (RW - 2)
#define MAX(a,b) ((a) > (b) ? (a) : (b))

int b = 2, f = 3, cp = 0, s = 0, p = HP, t = 1;
char r[RW - 1];
char m[RW - 1];
int mT = 0, lT = 0;

void clr() { system("cls"); }
void cm() { for (int i = 0; i < RW - 2; i++) m[i] = ' '; }
void pm(int prev) { cm(); m[prev - 1] = '.'; }

void c() {
    printf(" /\\_/\\  \n( o.o ) \n > ^ <  \n");
}

int d() { return rand() % 6 + 1; }

void ir() {
    for (int i = 0; i < RW - 2; i++) r[i] = ' ';
    r[HP - 1] = 'H';
    r[BP - 1] = 'B';
}

void sr() {
    printf("##########\n#");
    for (int i = 0; i < RW - 2; i++) printf("%c", r[i]);
    printf("#\n#");
    for (int i = 0; i < RW - 2; i++) {
        if (i == p - 1) printf("C");
        else if (m[i] == '.') printf(".");
        else printf(" ");
    }
    printf("#\n##########\n");
}

void st(char* n) {
    printf("=========== 상태 ===========\n");
    printf("현재까지 만든 수프: %d개\n", s);
    printf("보유 cp: %d\n", cp);
    printf("%s의 기분(0~3): %d\n", n, f);
    if (f == 0) printf("기분이 매우 나쁩니다\n");
    if (f == 1) printf("심심해합니다\n");
    if (f == 2) printf("식빵을 굽습니다\n");
    if (f == 3) printf("골골송을 부릅니다\n");
    printf("집사와의 관계(0~4): %d\n", b);
    if (b == 0) printf("곁에 오는 것조차 싫어합니다\n");
    if (b == 1) printf("간식 자판기 취급입니다\n");
    if (b == 2) printf("그럭저럭 쓸 만한 집사입니다\n");
    if (b == 3) printf("훌륭한 집사로 인정받고 있습니다\n");
    if (b == 4) printf("집사 껌딱지입니다\n");
    printf("============================\n");
}

void a(char* n) {
    if (p == BP) {
        s++;
        printf("%s가 수프를 만들었습니다! 총 수프: %d\n", n, s);
    }
    else if (p == HP) {
        printf("%s는 집에서 쉽니다.\n", n);
    }
    else if (r[p - 1] == 'S') {
        f = f < 3 ? f + 1 : 3;
        printf("%s가 스크래쳐 위에서 기분이 좋아졌습니다!\n", n);
    }
    else if (r[p - 1] == 'T') {
        f = f < 2 ? f + 2 : 3;
        printf("%s가 캣타워 위에서 매우 만족해합니다!\n", n);
    }
}

void mv(char* n) {
    if (f == 0) {
        printf("기분이 매우 나쁩니다. %s는 집으로 향합니다.\n", n);
        if (p > HP) p--;
    }
    else if (f == 1) {
        int found = 0;
        for (int i = 0; i < RW - 2; i++) {
            if (r[i] == 'S' || r[i] == 'T') {
                found = 1;
                if (p - 1 < i) p++;
                else if (p - 1 > i) p--;
                printf("%s는 심심해서 놀이기구 쪽으로 이동합니다.\n", n);
                break;
            }
        }
        if (!found) {
            printf("놀거리가 없어 기분이 나빠집니다.\n");
            f = f > 0 ? f - 1 : 0;
        }
    }
    else if (f == 2) {
        printf("%s는 제자리에서 식빵을 굽고 있습니다.\n", n);
    }
    else if (f == 3) {
        printf("%s는 골골송을 부르며 냄비 쪽으로 향합니다.\n", n);
        if (p < BP) p++;
        else if (p > BP) p--;
    }
}

int input() {
    int sel = -1;
    printf("무엇을 하시겠습니까? (0. 안함, 1. 긁어주기, 2. 장난감쥐, 3. 레이저포인터)\n>> ");
    scanf_s("%d", &sel);
    while (getchar() != '\n');
    return sel;
}

void pl(char* n) {
    int sel = input();
    int roll;

    if (sel == 0) {
        printf("아무것도 하지 않습니다.\n");
        roll = d();
        printf("주사위: %d\n", roll);
        if (roll <= 4 && b > 0) {
            b--;
            printf("친밀도가 감소합니다. 현재: %d\n", b);
        }
        else {
            printf("친밀도는 유지됩니다.\n");
        }
    }
    else if (sel == 1) {
        printf("%s의 턱을 긁어줍니다.\n", n);
        roll = d();
        printf("주사위: %d\n", roll);
        if (roll >= 5 && b < 4) {
            b++;
            printf("친밀도가 증가합니다. 현재: %d\n", b);
        }
        else {
            printf("친밀도는 그대로입니다.\n");
        }
    }
    else if (sel == 2 && mT) {
        roll = d();
        printf("장난감쥐로 놉니다. 주사위: %d\n", roll);
        if (roll >= 4 && b < 4) b++;
    }
    else if (sel == 3 && lT) {
        roll = d();
        printf("레이저포인터로 놉니다. 주사위: %d\n", roll);
        if (roll >= 2 && b < 4) b++;
    }
    else {
        printf("잘못된 선택이거나 장난감이 없습니다.\n");
    }
}

void g(char* n) {
    int gain = MAX(0, f - 1) + b;
    cp += gain;
    printf("이번 턴 CP 획득량: %d → 총 CP: %d\n", gain, cp);
}

void sh(char* n) {
    printf("\n[상점 - 현재 CP: %d]\n", cp);
    printf("1. 장난감쥐 (1cp) %s\n", mT ? "- 품절" : "");
    printf("2. 레이저포인터 (2cp) %s\n", lT ? "- 품절" : "");
    printf("3. 스크래쳐 설치 (4cp)\n");
    printf("4. 캣타워 설치 (6cp)\n");
    printf("0. 구매 안함\n>> ");
    int sel;
    scanf_s("%d", &sel);
    while (getchar() != '\n');

    int loc = rand() % (RW - 2);
    if (sel == 1 && !mT && cp >= 1) {
        cp -= 1; mT = 1;
        printf("장난감쥐를 구매했습니다.\n");
    }
    else if (sel == 2 && !lT && cp >= 2) {
        cp -= 2; lT = 1;
        printf("레이저포인터를 구매했습니다.\n");
    }
    else if (sel == 3 && cp >= 4) {
        cp -= 4; r[loc] = 'S';
        printf("스크래쳐를 설치했습니다.\n");
    }
    else if (sel == 4 && cp >= 6) {
        cp -= 6; r[loc] = 'T';
        printf("캣타워를 설치했습니다.\n");
    }
    else {
        printf("구매하지 않았거나 조건이 맞지 않습니다.\n");
    }
}

void quiz(char* n) {
    int a = rand() % 9 + 1;
    int bq = rand() % 9 + 1;
    int ans = a * bq;
    int userAns = -1;
    time_t start = time(NULL);

    printf("\n[이벤트 발생] %s의 꼬리를 밟았습니다!\n", n);
    printf("구구단 퀴즈로 고양이의 화를 풀어야 합니다! (3초 제한)\n");
    printf("문제: %d x %d = ?\n>> ", a, bq);

    while (difftime(time(NULL), start) < 3) {
        if (_kbhit()) {
            scanf_s("%d", &userAns);
            break;
        }
    }

    if (userAns == ans) {
        printf("정답입니다! 고양이가 용서해줬습니다.\n");
    }
    else {
        printf("실패! 고양이가 등을 돌렸습니다.\n");
        f = 0; b = 0; cp = 0; s = 0;
    }
    Sleep(2000);
}

int main() {
    srand((unsigned)time(0));
    char n[20];
    clr(); c();
    printf("고양이 이름을 지어주세요: ");
    scanf_s("%s", n, (unsigned)_countof(n));
    while (getchar() != '\n');
    ir(); cm();

    while (1) {
        clr();
        st(n); sr();
        if (t == 3) quiz(n);
        pl(n); mv(n); pm(p); a(n);
        g(n); Sleep(600); clr(); sh(n);
        Sleep(700); t++;
    }
    return 0;
}
