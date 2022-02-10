/**
 * @author HuyPham
 * @brief The record of football players program
 * @version 1.0
 * @date Feb 8, 2022
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printMenu() {
    printf("+----------------------------------------+\n");
    printf("| THE RECORD OF FOOTBALL PLAYERS PROGRAM |\n");
    printf("| 1. Add player                          |\n");
    printf("| 2. Edit player                         |\n");
    printf("| 3. Delete player                       |\n");
    printf("| 4. Highest rating                      |\n");
    printf("| 5. Lowest rating                       |\n");
    printf("| 6. List of all players                 |\n");
    printf("| 7. List of players have highest rating |\n");
    printf("| 8. List of players have lowest rating  |\n");
    printf("| 9. Delete all                          |\n");
    printf("| 0. Exit                                |\n");
    printf("+----------------------------------------+\n");
}

struct Player {
    int id;
    char name[10];
    char team[10];
    int rating;
    struct Player* link;
};

struct Player* head;

void printHeader() {
    printf("+-----+----------+------+--------+\n");
    printf("| ID  |   Name   | Team | Rating |\n");
    printf("+-----+----------+------+--------+\n");
}

void printFooter() {
    printf("+--------------------------------+\n");
}

void printPlayer(struct Player* pointer) {
    printf("|  %d\t%s\t   %s\t    %d   |\n", pointer->id, pointer->name, pointer->team, pointer->rating);
}

void printList() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List of players\n");
    printHeader();
    struct Player* pointer = head;
    while (pointer != NULL) {
        printPlayer(pointer);
        pointer = pointer->link;
    }
    printFooter();
}

void addPlayer() {
    system("cls");
    printMenu();
    struct Player* createPlayer = (struct Player*)malloc(sizeof(struct Player));
    printf("Enter ID: ");
    scanf("%d", &createPlayer->id);
    printf("Enter name: ");
    scanf("%s", createPlayer->name);
    printf("Enter team: ");
    scanf("%s", createPlayer->team);
    printf("Enter rating: ");
    scanf("%d", &createPlayer->rating);
    if (head == NULL) {
        createPlayer->link = NULL;
        head = createPlayer;
        printf("---Added!---\n");
        return;
    }
    struct Player* previous = NULL;
    struct Player* current = head;
    while (current != NULL) {
        if (createPlayer->rating >= current->rating) {
            createPlayer->link = current;
            if (current == head) {
                head = createPlayer;
            } else {
                previous->link = createPlayer;
            }
            printf("---Added!---\n");
            return;
        }
        previous = current;
        current = current->link;
    }
    previous->link = createPlayer;
    createPlayer->link = NULL;
    printf("---Added!---\n");
}

void editPlayer() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printList();
    printf("Edit player who has that ID is ");
    int choose;
    scanf("%d", &choose);
    bool flag = false;
    struct Player* previous = NULL;
    struct Player* current = head;
    while (current != NULL) {
        if (current->id == choose) {
            if (current == head) {
                head = current->link;
            } else {
                previous->link = current->link;
            }
            free(current);
            flag = true;
            break;
        }
        previous = current;
        current = current->link;
    }
    if (!flag) {
        printf("List does not have that ID is %d\n", choose);
        return;
    }
    struct Player* createPlayer = (struct Player*)malloc(sizeof(struct Player));
    createPlayer->id = choose;
    printf("Enter name: ");
    scanf("%s", createPlayer->name);
    printf("Enter team: ");
    scanf("%s", createPlayer->team);
    printf("Enter rating: ");
    scanf("%d", &createPlayer->rating);
    if (head == NULL) {
        createPlayer->link = NULL;
        head = createPlayer;
        printf("---Edited!---\n");
        return;
    }
    previous = NULL;
    current = head;
    while (current != NULL) {
        if (createPlayer->rating >= current->rating) {
            createPlayer->link = current;
            if (current == head) {
                head = createPlayer;
            } else {
                previous->link = createPlayer;
            }
            printf("---Edited!---\n");
            return;
        }
        previous = current;
        current = current->link;
    }
    previous->link = createPlayer;
    createPlayer->link = NULL;
    printf("---Edited!---\n");
}

void deletePlayer() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printList();
    printf("Delete player who has that ID is ");
    int choose;
    scanf("%d", &choose);
    struct Player* previous = NULL;
    struct Player* current = head;
    while (current != NULL) {
        if (current->id == choose) {
            if (current == head) {
                head = current->link;
            } else {
                previous->link = current->link;
            }
            free(current);
            printf("---Deleted!---\n");
            return;
        }
        previous = current;
        current = current->link;
    }
    printf("List does not have that ID is %d\n", choose);
}

void printHighestRating() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("The highest rating is: %d\n", head->rating);
}

int getLowestRating() {
    struct Player* previous = NULL;
    struct Player* current = head;
    while (current != NULL) {
        previous = current;
        current = current->link;
    }
    return previous->rating;
}

void printLowestRating() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    int lowestRating = getLowestRating();
    printf("The lowest rating is: %d\n", lowestRating);
}

void printHighestRatingList() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List of players who have highest rating\n");
    printHeader();
    struct Player* printPtr = head;
    while (printPtr != NULL) {
        if (printPtr->rating == head->rating) {
            printPlayer(printPtr);
            printPtr = printPtr->link;
        } else {
            break;
        }
    }
    printFooter();
}

void printLowestRatingUsingRecursion(struct Player* pointer, int lowestRating) {
    if (pointer == NULL) return;
    printLowestRatingUsingRecursion(pointer->link, lowestRating);
    if (pointer->rating == lowestRating) {
        printPlayer(pointer);
    } else {
        return;
    }
}

void printLowestRatingList() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List of players who have lowest rating\n");
    printHeader();
    int lowestRating = getLowestRating();
    printLowestRatingUsingRecursion(head, lowestRating);
    printFooter();
}

void deleteList() {
    system("cls");
    printMenu();
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Player* current;
    while (head != NULL) {
        current = head;
        head = head->link;
        free(current);
    }
    printf("---Deleted all!---\n");
}

void process() {
    system("cls");
    printMenu();
    bool flag = true;
    do {
        printf("Your selection: ");
        int choose;
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            addPlayer();
            break;
        case 2:
            editPlayer();
            break;
        case 3:
            deletePlayer();
            break;
        case 4:
            printHighestRating();
            break;
        case 5:
            printLowestRating();
            break;
        case 6:
            printList();
            break;
        case 7:
            printHighestRatingList();
            break;
        case 8:
            printLowestRatingList();
            break;
        case 9:
            deleteList();
            break;
        case 0:
            system("cls");
            printf("See you again!\n");
            flag = false;
            break;
        default:
            system("cls");
            printMenu();
            printf("Please choose again! (0->9)\n");
        }
    } while (flag);
}

int main() {
    process();
    return 0;
}