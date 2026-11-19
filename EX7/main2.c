#include <stdio.h>

#define BOOK_COUNT 6

typedef struct Books {
    int id;
    int price;
    char title[100];
} book_t;

void total_price(const book_t *books, int count) {
    int sum = 0;

    for (int i = 0; i < count; i++)
        sum += books[i].price;

    printf("Total price: %d\n", sum);
}

void list_books(const book_t *books, int count) {
    printf("%-5s %-7s %s\n", "Id", "Price", "Title");

    for (int i = 0; i < count; i++)
        printf("%-5d %-7d %s\n",
               books[i].id,
               books[i].price,
               books[i].title);
}

int main(void) {
    book_t books[BOOK_COUNT] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550, "Killers of the Flower Moon"},
        {5, 870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    FILE *fp = fopen("Book.bin", "wb");

    if (fp == NULL) {
        printf("Cannot open Book.bin\n");
        return 1;
    }

    if (fwrite(books, sizeof(book_t), BOOK_COUNT, fp)
        != BOOK_COUNT) {
        printf("Cannot write Book.bin\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    list_books(books, BOOK_COUNT);
    total_price(books, BOOK_COUNT);

    return 0;
}
