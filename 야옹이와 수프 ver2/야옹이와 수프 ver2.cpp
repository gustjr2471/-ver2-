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
    printf("=========== ���� ===========\n");
    printf("������� ���� ����: %d��\n", s);
    printf("���� cp: %d\n", cp);
    printf("%s�� ���(0~3): %d\n", n, f);
    if (f == 0) printf("����� �ſ� ���޴ϴ�\n");
    if (f == 1) printf("�ɽ����մϴ�\n");
    if (f == 2) printf("�Ļ��� �����ϴ�\n");
    if (f == 3) printf("������ �θ��ϴ�\n");
    printf("������� ����(0~4): %d\n", b);
    if (b == 0) printf("�翡 ���� ������ �Ⱦ��մϴ�\n");
    if (b == 1) printf("���� ���Ǳ� ����Դϴ�\n");
    if (b == 2) printf("�׷����� �� ���� �����Դϴ�\n");
    if (b == 3) printf("�Ǹ��� ����� �����ް� �ֽ��ϴ�\n");
    if (b == 4) printf("���� �������Դϴ�\n");
    printf("============================\n");
}

void a(char* n) {
    if (p == BP) {
        s++;
        printf("%s�� ������ ��������ϴ�! �� ����: %d\n", n, s);
    }
    else if (p == HP) {
        printf("%s�� ������ ���ϴ�.\n", n);
    }
    else if (r[p - 1] == 'S') {
        f = f < 3 ? f + 1 : 3;
        printf("%s�� ��ũ���� ������ ����� ���������ϴ�!\n", n);
    }
    else if (r[p - 1] == 'T') {
        f = f < 2 ? f + 2 : 3;
        printf("%s�� ĹŸ�� ������ �ſ� �������մϴ�!\n", n);
    }
}

void mv(char* n) {
    if (f == 0) {
        printf("����� �ſ� ���޴ϴ�. %s�� ������ ���մϴ�.\n", n);
        if (p > HP) p--;
    }
    else if (f == 1) {
        int found = 0;
        for (int i = 0; i < RW - 2; i++) {
            if (r[i] == 'S' || r[i] == 'T') {
                found = 1;
                if (p - 1 < i) p++;
                else if (p - 1 > i) p--;
                printf("%s�� �ɽ��ؼ� ���̱ⱸ ������ �̵��մϴ�.\n", n);
                break;
            }
        }
        if (!found) {
            printf("��Ÿ��� ���� ����� �������ϴ�.\n");
            f = f > 0 ? f - 1 : 0;
        }
    }
    else if (f == 2) {
        printf("%s�� ���ڸ����� �Ļ��� ���� �ֽ��ϴ�.\n", n);
    }
    else if (f == 3) {
        printf("%s�� ������ �θ��� ���� ������ ���մϴ�.\n", n);
        if (p < BP) p++;
        else if (p > BP) p--;
    }
}

int input() {
    int sel = -1;
    printf("������ �Ͻðڽ��ϱ�? (0. ����, 1. �ܾ��ֱ�, 2. �峭����, 3. ������������)\n>> ");
    scanf_s("%d", &sel);
    while (getchar() != '\n');
    return sel;
}

void pl(char* n) {
    int sel = input();
    int roll;

    if (sel == 0) {
        printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
        roll = d();
        printf("�ֻ���: %d\n", roll);
        if (roll <= 4 && b > 0) {
            b--;
            printf("ģ�е��� �����մϴ�. ����: %d\n", b);
        }
        else {
            printf("ģ�е��� �����˴ϴ�.\n");
        }
    }
    else if (sel == 1) {
        printf("%s�� ���� �ܾ��ݴϴ�.\n", n);
        roll = d();
        printf("�ֻ���: %d\n", roll);
        if (roll >= 5 && b < 4) {
            b++;
            printf("ģ�е��� �����մϴ�. ����: %d\n", b);
        }
        else {
            printf("ģ�е��� �״���Դϴ�.\n");
        }
    }
    else if (sel == 2 && mT) {
        roll = d();
        printf("�峭����� ��ϴ�. �ֻ���: %d\n", roll);
        if (roll >= 4 && b < 4) b++;
    }
    else if (sel == 3 && lT) {
        roll = d();
        printf("�����������ͷ� ��ϴ�. �ֻ���: %d\n", roll);
        if (roll >= 2 && b < 4) b++;
    }
    else {
        printf("�߸��� �����̰ų� �峭���� �����ϴ�.\n");
    }
}

void g(char* n) {
    int gain = MAX(0, f - 1) + b;
    cp += gain;
    printf("�̹� �� CP ȹ�淮: %d �� �� CP: %d\n", gain, cp);
}

void sh(char* n) {
    printf("\n[���� - ���� CP: %d]\n", cp);
    printf("1. �峭���� (1cp) %s\n", mT ? "- ǰ��" : "");
    printf("2. ������������ (2cp) %s\n", lT ? "- ǰ��" : "");
    printf("3. ��ũ���� ��ġ (4cp)\n");
    printf("4. ĹŸ�� ��ġ (6cp)\n");
    printf("0. ���� ����\n>> ");
    int sel;
    scanf_s("%d", &sel);
    while (getchar() != '\n');

    int loc = rand() % (RW - 2);
    if (sel == 1 && !mT && cp >= 1) {
        cp -= 1; mT = 1;
        printf("�峭���㸦 �����߽��ϴ�.\n");
    }
    else if (sel == 2 && !lT && cp >= 2) {
        cp -= 2; lT = 1;
        printf("�����������͸� �����߽��ϴ�.\n");
    }
    else if (sel == 3 && cp >= 4) {
        cp -= 4; r[loc] = 'S';
        printf("��ũ���ĸ� ��ġ�߽��ϴ�.\n");
    }
    else if (sel == 4 && cp >= 6) {
        cp -= 6; r[loc] = 'T';
        printf("ĹŸ���� ��ġ�߽��ϴ�.\n");
    }
    else {
        printf("�������� �ʾҰų� ������ ���� �ʽ��ϴ�.\n");
    }
}

void quiz(char* n) {
    int a = rand() % 9 + 1;
    int bq = rand() % 9 + 1;
    int ans = a * bq;
    int userAns = -1;
    time_t start = time(NULL);

    printf("\n[�̺�Ʈ �߻�] %s�� ������ ��ҽ��ϴ�!\n", n);
    printf("������ ����� ������� ȭ�� Ǯ��� �մϴ�! (3�� ����)\n");
    printf("����: %d x %d = ?\n>> ", a, bq);

    while (difftime(time(NULL), start) < 3) {
        if (_kbhit()) {
            scanf_s("%d", &userAns);
            break;
        }
    }

    if (userAns == ans) {
        printf("�����Դϴ�! ����̰� �뼭������ϴ�.\n");
    }
    else {
        printf("����! ����̰� ���� ���Ƚ��ϴ�.\n");
        f = 0; b = 0; cp = 0; s = 0;
    }
    Sleep(2000);
}

int main() {
    srand((unsigned)time(0));
    char n[20];
    clr(); c();
    printf("����� �̸��� �����ּ���: ");
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
