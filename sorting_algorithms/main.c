#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

bool asc = true; ///boolean specifying order in sort
int comaprisionsNumber = 0;
int changesNumber = 0;

/// funkcja odpowiedzialna za insertion sort
void insertionSort(int* arr, int n){
    int i, key, j;
    for(i = 1; i < n; i++){
        key = arr[i];
        j = i-1;
        /// w zaleznosci od tego czy sortujemy rosnaco(asc) czy malejaco wybieramy odpowiadnia nierownosc
        while(j >= 0 && ((arr[j] > key && asc == true) || (arr[j] < key && asc == false))){
            //if (asc) {fprintf(stderr, "porownanie: %d > %d \n", arr[j], key);}
            //else{fprintf(stderr, "porownanie: %d < %d \n", arr[j], key);}
            comaprisionsNumber++;
            //fprintf(stderr, "przestawienie: arr[%d] <- arr[%d]\n", j+1, j);
            arr[j+1] = arr[j];
            changesNumber++;

            j = j-1;
        }
        //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", j+1, key);
        arr[j+1] = key;
        changesNumber++;
    }
}

/// funkcja pomocnicza odpowiedzialna za "mergowanie" podtablic w merge sorcie
/// przyjmuje sortowana tablice(arr)
/// l -> poczatek lewej podtablicy
/// m -> srodek oraz r -> koniec prawej podtablicy
void merge(int* arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1; /// wyznaczamy rozmiar lewej podstablicy
    int n2 =  r - m;    /// wyznaczamy rozmiar prawej podtablicy

    /// deklarujemy tablice pomocnicze
    int L[n1], R[n2];

    /// kopiujemy dane do tablic pomocniczych
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /// mergujemy podtablice do tablicy glownej
    i = 0; /// poczatek lewej podtablicy
    j = 0; /// poczatek prawej podtablicy
    k = l; /// indeks bedacy poczatkiem "mergowanej" tablicy
    while (i < n1 && j < n2)
    {
        comaprisionsNumber++;
        if (L[i] <= R[j] && asc == true)
        {
            //fprintf(stderr, "porownanie: %d <= %d\n", L[i], R[j]);
            //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", k, L[i]);
            arr[k] = L[i];  ///jesli sortujemy rosnaco, to przepisujemy mniejszy element i przesuwamy sie w odpowiedniej tablicy indeksem
            changesNumber++;
            i++;
        }
        else if (L[i] >= R[j] && asc == true){
            //fprintf(stderr, "porownanie: %d >= %d\n", L[i], R[j]);
            //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", k, R[j]);
            arr[k] = R[j];
            changesNumber++;
            j++;
        }
        else if (L[i] >= R[j] && asc == false){
            //fprintf(stderr, "porownanie: %d >= %d\n", L[i], R[j]);
            //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", k, L[i]);
            arr[k] = L[i];
            changesNumber++;
            i++;
        }
        else if (L[i] <= R[j] && asc == false){
            //fprintf(stderr, "porownanie: %d <= %d\n", L[i], R[j]);
            //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", k, R[j]);
            arr[k] = R[j];
            changesNumber++;
            j++;
        }
        k++;
    }

    /// jesli "skonczyly" nam sie elementy z prawej podtablicy, to przepisz po kolei to co zostalo w lewej
    while (i < n1)
    {
        //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", k, L[i]);
        changesNumber++;
        arr[k] = L[i];
        i++;
        k++;
    }

    /// jesli "skonczyly" nam sie elementy z lewej podtablicy, to przepisz po kolei to co zostalo w prawej
    while (j < n2)
    {
        //fprintf(stderr, "przestawienie: arr[%d] <- %d\n", k, R[j]);
        changesNumber++;
        arr[k] = R[j];
        j++;
        k++;
    }
}


/// l - poczatek lewej podtablicy
/// r - koniec prawej podtablicy
/// funkcja odpowiedzialna za merge sort
void mergeSort(int* arr, int l, int r)
{
    if (l < r)
    {
        /// wyznaczamy srodek tablicy
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);   /// sortujemy lewa podtablice -> [l .. m]
        mergeSort(arr, m+1, r); /// sortujemy prawa podtablice -> [m+1 .. r]

        merge(arr, l, m, r);    /// "mergujemy" posrotowane podtablice
    }
}

/// funkcja pomocnicza do zamieniania wartosci miedzy zmiennymi
void swap(int* a, int* b)
{
    int t = *a; /// do t wrzucamy wartosc a
    *a = *b; /// wartosc a ustawiamy na wartosc b
    *b = t; ///zas wartosc b na t (czyli poprzednia wartosc a)
}

/// funkcja pomocnicza sluzaca do podzialu tablicy na czesci przy quick sorcie
 int partion(int* arr, int low, int high)
{
    int pivot = arr[high];    /// jako pivot przyjmuje ostatni element tablicy
    int i = (low - 1);  /// i posluzy jako "granica" wzgl, ktorej bedziemy dzielic tablice

    /// bedziemy porownywac elementy tablicy z pivotem
    /// liczby mniejsze musza znalezc sie przed "granica" (przed pivotem)
    /// liczby wieksze musze znalezc sie za "granica" (za pivotem)
    for (int j = low; j <= high- 1; j++)
    {
        /// sprawdzamy czy dany element jest mniejszy/wiekszy od pivota (w zaleznosci od tego jak sortujemy)
        comaprisionsNumber++;
        if ((arr[j] < pivot && asc == true) || (arr[j] > pivot && asc == false))
        {
            //if(asc){fprintf(stderr, "porownanie: %d < %d\n", arr[j], pivot);}
            //else{fprintf(stderr, "porownanie: %d > %d\n", arr[j], pivot);}
            i++;    /// "przesuwamy granice"
            swap(&arr[i], &arr[j]); /// dokonujemy "swapa"
            //fprintf(stderr, "zamiana wartosci miejscami: %d <-> %d\n", arr[i], arr[j]);
            changesNumber++;
            /// np. gdy mamy ciag |9123 ("|" symbolizuje granice) 9 > 3, wiec jest dobrze,
            /// ale 1 < 3, zatem przesuwamy granice (i++): 9|123 i robimy swap 9 i 1: 1|923...
        }
    }
    //fprintf(stderr, "zamiana wartosci miejscami: %d <-> %d\n", arr[i+1], arr[high]);
    changesNumber++;
    swap(&arr[i + 1], &arr[high]); /// umieszczamy pivot w "odpowiednim" miejscu
    return (i + 1); /// i zwracamy indeks na jakim znalazl sie pivot
}

/// glowna funkcja odpowiedzialna za guicksort
/// low -> indeks poczatku
/// high -> indeks konca
void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        /// do zmiennej pi zostanie zwrocony ideks, gdzie zostal wrzucony pivot
        /// po podzieleniu tablicy, gdyz wiemy, ze on znajduje sie na odpowiednim miejscu
        /// i nalezy posortowac wszystko na lewo(mniejsze od pivota) od pivota oraz na prawo (wieksze od pivota)
        int pivotPosition = partion(arr, low, high);

        /// Teraz osobno sortujemy wszystko przed pivotem
        /// oraz wszystko za pivotem
        quickSort(arr, low, pivotPosition - 1);
        quickSort(arr, pivotPosition + 1, high);
    }
}


/// funkcja pomocnicza sluzaca do wyswietlania tablicy
void printArray(int* array, int size){
    for(int i = 0; i < size; i++){
        printf("%d", array[i]);
    }
}

int main(int argc, char* argv[])
{
    /// przyjmujemy dwa parametry wyjsciowe:
    /// --type(argv[1]) insert | merge | quick (argv[2])
    /// --comp (argv[3]) '>=' | '<=' (argv[4])

    char* type = "";
    char* fileName = "";
    int k = 0;

    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "--type") == 0){
            if(i+1 < argc){
                if (strcmp(argv[i+1], "insert") == 0 ||  strcmp(argv[i+1], "merge") || strcmp(argv[i+1], "quick")){
                    type = argv[i+1];
                }
                else{
                    printf("Unknown type\n");
                    exit(0);
                }
            }
            else{
                printf("Too few arguments\n");
                exit(0);
            }
        }
        else if(strcmp(argv[i], "--comp") == 0){
            if (i+1 < argc){
                if(strcmp(argv[i+1], "<=") == 0){ asc = true; }
                else if(strcmp(argv[i+1], ">=") == 0){ asc = false; }
                else{
                    printf("Unknown comp type\n");
                    exit(0);
                }
            }
            else{
                printf("Too few arguments\n");
                exit(0);
            }
        }
        else if(strcmp(argv[i], "--stat") == 0){
            if(i+1 < argc && i+2 < argc){
                fileName = argv[i+1];
                k = atoi(argv[i+2]);
            }
            else{
                printf("Too few arguments\n");
                exit(0);
            }
        }
    }

    if(strlen(type) == 0){
        printf("Too few arguments");
        exit(0);
    }

    if(strlen(fileName) == 0){
        int n;
        printf("Podaj rozmiar tablicy: ");
        scanf("%d", &n);
        int* toSort = malloc(sizeof(int) * n);
        printf("Podaj elementy tablicy(oddzielone spacja): \n");
        int i = 0;
        while (i < n && scanf("%d", &toSort[i++]) == 1);

        struct timeval startTime, endTime; ///struktura posiadajaca czas w sekundach oraz milisekundach

        /// w zaleznosci od wybranej opcji wybieramy odpowiedni typ sortowania
        if(strcmp(type, "insert") == 0){
        ///insertion sort
            gettimeofday(&startTime, NULL); ///pobieramy czas przed sortowaniem

            insertionSort(toSort, n);

            gettimeofday(&endTime, NULL); ///pobieramy czas po sortowaniu
            time_t executionTime = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
            printArray(toSort, n);
            printf("\n\nCzas sortowania(w mikrosekundach): %ld", executionTime);
        }
        else if(strcmp(type, "merge") == 0){
        ///merge sort
            gettimeofday(&startTime, NULL); ///pobieramy czas przed sortowaniem

            mergeSort(toSort, 0, n-1);

            gettimeofday(&endTime, NULL); ///pobieramy czas po sortowaniu
            time_t executionTime = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
            printArray(toSort, n);
            printf("\n\nCzas sortowania(w mikrosekundach): %ld", executionTime);
        }
        else if(strcmp(type, "quick") == 0){
        ///quick sort
            gettimeofday(&startTime, NULL); ///pobieramy czas przed sortowaniem

            quickSort(toSort, 0, n-1);


            gettimeofday(&endTime, NULL); ///pobieramy czas po sortowaniu
            time_t executionTime = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
            printArray(toSort, n);
            printf("\n\nCzas sortowania(w mikrosekundach): %ld", executionTime);
        }

        fprintf(stderr, "\ncomparision number: %d\n", comaprisionsNumber);
        fprintf(stderr, "changes number: %d\n", changesNumber);

        int sortedElements = 1;

        /// sprawdzamy poprawnosc sortowania
        for(int i = 0; i < n-1; i++) {
            if (asc && toSort[i] <= toSort[i+1]){
                sortedElements++;
            }
            else if(!asc && toSort[i] >= toSort[i+1]){
                sortedElements++;
            }
            else{
                printf("Sorting failed\n");
                break;
            }
        }
        printf("Liczba posortowanych elementow: %d", sortedElements);
    }
    else{
        struct timeval startTime, endTime; ///struktura posiadajaca czas w sekundach oraz milisekundach
        time_t executionTime; /// zmienna do ktorej bedziemy wpisywac czas dzialania algorytmu (w mikrosekundach)
        srand(time(NULL));
        FILE *fptr;
        fptr = fopen(fileName, "a");
        if (fptr == NULL) {
            printf("Nie udalo sie zaladowac pliku");
            exit(1);
        }
        fprintf(fptr, "rozmiar,porownania,przestawienia,czas\n"); /// wykorzystam plik w formacie csv (comma separated)
        int n = 0;
        for(int i = 100; i <= 10000; i += 100){
            for(int j = 0; j < k; j++){
                comaprisionsNumber = 0; ///przed kazda z prob zerujemy te zmienne globalne
                changesNumber = 0;
                n = i; /// pobieramy aktualna wartosc n = 100, 200, ..., 10000
                int numbers[n]; /// inizjalizujemy tablice
                /// wypelniamy tablice randomowymi liczbami
                for(int m = 0; m < n; m++){
                    numbers[m] = rand();
                }
                    /// w zaleznosci od wybranej opcji wybieramy odpowiedni typ sortowania
                    if(strcmp(type, "insert") == 0){
                    ///insertion sort
                        gettimeofday(&startTime, NULL); ///pobieramy czas przed sortowaniem
                        insertionSort(numbers, n);
                        gettimeofday(&endTime, NULL); ///pobieramy czas po sortowaniu
                        executionTime = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
                    }
                    else if(strcmp(type, "merge") == 0){
                    ///merge sort
                        gettimeofday(&startTime, NULL); ///pobieramy czas przed sortowaniem
                        mergeSort(numbers, 0, n-1);
                        gettimeofday(&endTime, NULL); ///pobieramy czas po sortowaniu
                        executionTime = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
                    }
                    else if(strcmp(type, "quick") == 0){
                    ///quick sort
                        gettimeofday(&startTime, NULL); ///pobieramy czas przed sortowaniem
                        quickSort(numbers, 0, n-1);
                        gettimeofday(&endTime, NULL); ///pobieramy czas po sortowaniu
                        executionTime = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));
                    }
                    /// dla kazdej z prob wpisujemy odpowiednie dane do pliku
                    fprintf(fptr, "%d,%d,%d,%ld\n", n, comaprisionsNumber, changesNumber, executionTime);
            }
        }
    }


    return 0;
}
