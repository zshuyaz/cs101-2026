#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n, i, j, k, temp, numbers[69];
    FILE *fp;
    time_t now;

    printf("歡迎光臨長庚樂透彩購買機台\n");

    do {
        printf("請問您要買幾組樂透彩：");
        if (scanf("%d", &n) != 1) {
            printf("輸入錯誤！\n");
            return 1;
        }
        if (n < 1 || n > 5)
            printf("請輸入 1 到 5 組。\n");
    } while (n < 1 || n > 5);

    fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法建立 lotto.txt\n");
        return 1;
    }

    now = time(NULL);
    srand((unsigned int)now);

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s", ctime(&now));

    for (i = 0; i < 5; i++) {
        fprintf(fp, "[%d]: ", i + 1);

        if (i < n) {
            for (j = 0; j < 69; j++)
                numbers[j] = j + 1;

            for (j = 0; j < 7; j++) {
                k = j + rand() % (69 - j);
                temp = numbers[j];
                numbers[j] = numbers[k];
                numbers[k] = temp;
            }

            for (j = 0; j < 5; j++) {
                for (k = j + 1; k < 6; k++) {
                    if (numbers[j] > numbers[k]) {
                        temp = numbers[j];
                        numbers[j] = numbers[k];
                        numbers[k] = temp;
                    }
                }
            }

            for (j = 0; j < 7; j++)
                fprintf(fp, "%02d%s",
                        numbers[j], j == 6 ? "" : " ");
        } else {
            fprintf(fp, "-- -- -- -- -- -- --");
        }

        fprintf(fp, "\n");
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("已為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);

    return 0;
}
