#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XSIZE 5
#define USER_COUNT 10

struct user_info {
    int id_num;
    char id[10];
    char password[10];
};

int load_user_info(struct user_info user[]) {
    FILE* fp = fopen("user_data.txt", "r");
    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < USER_COUNT; i++) {
        fscanf(fp, "%d %s %s", &user[i].id_num, user[i].id, user[i].password);
    }
    fclose(fp);

    for (int i = 0; i < USER_COUNT - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < USER_COUNT; j++) {
            if (strcmp(user[j].id, user[min_idx].id) < 0) {
                min_idx = j;
            }
        }
        struct user_info temp = user[i];
        user[i] = user[min_idx];
        user[min_idx] = temp;
    }
    return USER_COUNT;
}

int load_reservation_info(int s[][XSIZE]) {
    FILE* fp = fopen("reservation_data.txt", "r");
    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < XSIZE; j++) {
            fscanf(fp, "%d", &s[i][j]);
        }
    }
    fclose(fp);
    return 0;
}

int save_reservation_info(int s[][XSIZE]) {
    FILE* fp = fopen("reservation_data.txt", "w");
    if (fp == NULL) {
        return -1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < XSIZE; j++) {
            if (fprintf(fp, "%d ", s[i][j]) < 0) {
                fclose(fp);
                return -1;
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}


int check_login(struct user_info user[], char id[], char passwd[]) {
    int low = 0, high = 9, i;
    while (low <= high) {
        i = (low + high) / 2;
        if (strcmp(user[i].id, id) == 0)
        {
            if (strcmp(user[i].password, passwd) == 0)
            {
                return user[i].id_num;
            }
            else
            {
                return -2;
            }
        }
        else if (strcmp(user[i].id, id) > 0)
        {
            high = i - 1;
        }
        else
        {
            low = i + 1;
        }
    }
    return -1;
}

int print_seats(int seat_array[][XSIZE]) {
    printf("   | 0 1 2 3 4\n");
    printf("---------------\n");
    for (int i = 0; i < 3; i++) {
        printf("%c | ", 'A' + i);
        for (int j = 0; j < XSIZE; j++) {
            if (seat_array[i][j] == 0) {
                printf("O ");
            }
            else {
                printf("%d ", seat_array[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    return 1;
}

int reserve(int s_array[][XSIZE], char r, int c, int num) {
    int row = r - 'A';
    if ((row >= 0 && row < 3) && (c >= 0 && c < XSIZE) && (s_array[row][c] == 0))
    {
        s_array[row][c] = num;
        return 1;
    }
    else
    {
        return -1;
    }
}

int cancel(int s_array[][XSIZE], char r, int c, int num) {
    int row = r - 'A';
    if (row >= 0 && row < 3 && c >= 0 && c < XSIZE && s_array[row][c] == num) {
        s_array[row][c] = 0;
        return 1;
    }
    else {
        return -1;
    }
}

int main(void) {
    struct user_info user[10];
    int s[][XSIZE] = { {0}, {0}, {0} };
    int select, user_id;
    char id_input[10], passwd_input[10], row;
    int col;
    int login_result = -1;
    char c;

    if (load_user_info(user) < 0) {
        printf("error\n");
        return -1;
    }
    if (load_reservation_info(s) < 0) {
        printf("error\n");
        return -1;
    }

    while (1) {
        while (login_result <= 0) {
            printf("id: ");
            scanf("%s", id_input);
            while ((c = getchar()) != '\n' && c != EOF) {};
            printf("password: ");
            scanf("%s", passwd_input);
            while ((c = getchar()) != '\n' && c != EOF) {};

            login_result = check_login(user, id_input, passwd_input);
            if (login_result > 0)
            {
                printf("%s님 반갑습니다.\n", id_input);
                user_id = login_result;

            }
            else if (login_result == -1) {
                printf("로그인에 실패하였습니다. 다시 로그인을 하세요\n");
            }
            else if (login_result == -2) {
                printf("로그인에 실패하였습니다. 다시 로그인을 하세요\n");
            }
        }
        printf("1---좌석확인하기\n");
        printf("2---예약하기\n");
        printf("3---예약취소하기\n");
        printf("4---다른 사용자로 로그인하기\n");
        printf("5---종료하기\n");
        printf("메뉴를 선택하시오: ");
        scanf("%d", &select);
        while ((c = getchar()) != '\n' && c != EOF) {};

        if (select == 1) {
            print_seats(s);
        }
        else if (select == 2) {
            printf("예약을 원하는 자리는(예- A2)? ");
            scanf(" %c%d", &row, &col);
            while ((c = getchar()) != '\n' && c != EOF) {};
            if (reserve(s, row, col, user_id) == 1) {
                printf("예약이 완료되었습니다.\n");
                print_seats(s);
            }
            else {
                printf("이미 예약된 자리이거나 잘못된 입력입니다.\n");
            }
        }
        else if (select == 3) {
            printf("예약취소를 원하는 자리는(예- A2)? ");
            scanf(" %c%d", &row, &col);
            while ((c = getchar()) != '\n' && c != EOF) {};
            if (cancel(s, row, col, user_id) == 1) {
                printf("예약취소가 완료되었습니다.\n");
                print_seats(s);
            }
            else {
                printf("예약되지 않은 자리이거나 잘못된 입력입니다.\n");
            }
        }
        else if (select == 4) {
            login_result = -1;
            printf("로그인을 하세요.\n");
            continue;
        }
        else if (select == 5) {
            if (save_reservation_info(s) < 0) {
                printf("저장하는 동안 오류가 발생했습니다.\n");
            }
            else {
                printf("예약 정보가 성공적으로 저장되었습니다.\n");
            }
            printf("이용해 주셔서 감사합니다.\n");
            return 0;
        }
        else {
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");
        }
    }
}