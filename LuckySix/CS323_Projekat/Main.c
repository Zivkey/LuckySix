#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>

// Struktura koja cuva combinaciju i zadnji x na koji je zadnji broj izasao
struct Winning {
    int* combination;
    int amount;
};

// Funkcija koja u odnosu na to koji je broj menja boju teksta i stampa broj u boji
// Kao argument uzima broj
void printColor(int number) {
    if ((number - 1) % 8 == 0) {
        printf("\033[0;32m");
    }
    else if ( (number - 2) % 8 == 0){
        printf("\033[0;34m");
    }
    else if ((number - 3) % 8 == 0) {
        printf("\033[0;31m");
    }
    else if ((number - 4) % 8 == 0) {
        printf("\033[0;35m");
    }
    else if ((number - 5) % 8 == 0) {
        printf("\033[0;33m");
    }
    else if ((number - 6) % 8 == 0) {
        printf("\033[0;37m");
    }
    else if ((number - 7) % 8 == 0) {
        printf("\033[0;36m");
    }
    else {
        printf("\033[0;37m");
    }
}

// Funkcija koja cita sve kvote iz fajla u kome su one upisane
int* createXs() {
    int *xs = (int*)malloc(30 * sizeof(int));
    FILE* fp = fopen("array.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    for (int i = 0; i < 30; i++) {
        fscanf(fp, "%d", &xs[i]);
    }
    fclose(fp);
    return xs;
}

// Funkcija koja printuje sve brojeve koji su upisani u listi i kao argument 
// uzima listu i velicinu liste
void printNumbers(int combination[], int size) {
    printf("\nYour combination is: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", combination[i]);
    }
}

// Funkcija koja proverava da li je uneti broj od korisnika izmedju 1 i 48 i da li je unikatan
// Uzima kao argument broj i combinaciju od korisnika
int checkNumber(int number, int combination[]) {
    if (number < 1 || number > 48) {
        return 1;
    }
    for (int i = 0; i < 6; i++) {
        if (combination[i] == number) {
            return 1;
        }
    }
    return 0;
}

// Funkcija koja sluzi da unesemo nasu kombinaciju od 6 brojeva
// Ona ima argument combinaciju sto je lista u kojoj se upisuju brojevi i poziva metodu checkNumer() da proveri da li je uneti broj dobar
void insertNumbers(int combination[]) {
    for (int i = 0; i < 6; i++) {
        combination[i] = 0;
    }
    int num;
    for (int i = 0; i < 6; i++) {
        printf("Enter your %d. number: ", (i + 1));
        scanf("%d", &num);
        if (checkNumber(num, combination)) {
            printf("Number is not valid you need to enter new one!\n");
            i--;
        }
        else {
            combination[i] = num;
        }
    }
}

// Funkcija koja kreira niz od 48 brojeva
int* createAllNumbers() {
    int* allNumbers;
    allNumbers = (int*)malloc(48 * sizeof(int));
    for (int i = 1; i < 49; i++) {
        allNumbers[i - 1] = i;
    }
    return allNumbers;
}

// Funkcija koja uzima niz od svih brojeva i promesa ga kompletno
void shuffleArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        int swap_index = rand() % size;
        int temp = arr[i];
        arr[i] = arr[swap_index];
        arr[swap_index] = temp;
    }
}


// Funkcija koja sluzi za pocetak igre
// Ona uzima kvote iz fajla, i krece da printuje od 48 35 brojeva redom kako izlaze iz niza
// Ukoliko korisnik u svojoj listi sadrzi broj koji je izasao ispiuje se da je njegov broj izasao i koji je po redu
// Ukoliko izadju svih 6 brojeva pise se da je korisnik pobednik i kolika mu je kvota a ukoliko ne onda pise da je korisnik izgubio
void startTheGame(int allNumbers[], int combination[]) {
    int* quota = createXs();
    int z = 0, lastQuota = 0;
    printf("\n");
    for (int i = 0; i < 35; i++) {
        printColor(allNumbers[i]);
        if (i > 4) {
            printf("%d - x%d", allNumbers[i], quota[i - 5]);
        }
        else {
            printf("%d", allNumbers[i]);
        }
        for (int j = 0; j < 6; j++) {
            if (combination[j] == allNumbers[i]) {
                z++;
                printf(" <---- YOUR NUMBER %d out of 6", z);
                if (z == 6) {
                    lastQuota = quota[i - 5];
                }
            }
        }
        printf("\n");
        Sleep(1000);
    }
    free(quota);
    printf("\033[0;37m");
    struct Winning w1;
    w1.amount = lastQuota;
    w1.combination = combination;
    if (z == 6) {
        printNumbers(w1.combination, 6);
        printf("- YOU WON! You won at %dx congratulations!", w1.amount);
    }
    else {
        printNumbers(w1.combination, 6);
        printf("- you lost better luck next time!");
    }
}


int main() {
    srand(time(NULL));
    int* combination = (int*)malloc(6 * sizeof(int));
    char playCheck[20] = "Play";
    printf("         WELCOME TO LUCKY 6 \n ");
    //scanf("%s", playCheck);
    int* allNumbers = createAllNumbers();
    while (strcmp(playCheck, "Play") == 0 || strcmp(playCheck, "Repeat") == 0) {
        if (strcmp(playCheck, "Repeat") != 0) {
            printf("You need to insert your combination of 6 numbers.\n");
            insertNumbers(combination);
        }
        shuffleArray(allNumbers, 48);
        printNumbers(combination, 6);
        printf("The game is starting!");
        startTheGame(allNumbers, combination);
        printf("\033[0;37m");
        printf("\nType Play if you want to play again or Repeat if you want to repeat the combination: ");
        scanf("%s", playCheck);
    }
    printf("Thank you for playing the game!");
    free(allNumbers);
    free(combination);
    return 0;
}