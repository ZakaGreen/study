/*
Meno a priezvisko: Ilia Liubotin

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu
naprogramovat (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v
zadanych funkciach). Nemente implementacie zadanych datovych typov, ani
implementacie hotovych pomocnych funkcii (ak nie je v zadani ulohy uvedene
inak). (7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo
datove typy. (8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou
doplnenych pomocnych funkcii alebo datovych typov). Testovaci kod ale nebude
hodnoteny. (9)  Funkcia 'main' musi byt v zdrojovom kode posledna.

insertion sort
for (size_t i = 1; i < length; ++i){
        int current = data[i];
        size_t j = i;
        while(j > 0 && (data[j - 1] >  current)){
            data[j] = data[j - 1];
            --j;
        }
        data[j] = current;
    }

merge sort
void mergeSort(int *data, const size_t length) {
  int *temp = new int[length];
  int start = 0;
  int end = length - 1;

  if (start == end) {
    return;
  }

  int mid = (start + end) / 2;
  mergeSort(data, length);
  mergeSort(data, length);

  int left = start;
  int right = mid + 1;
  int temp_index = left;

  while (left <= mid && right <= end) {
    if (data[left] < data[right]) {
      temp[temp_index++] = data[right++];
    } else {
      temp[temp_index++] = data[left++];
    }
  }

  while (left <= mid) {
    temp[temp_index++] = data[left++];
  }

  while (right <= end) {
    temp[temp_index++] = data[right++];
  }

  int copy_index = start;
  for (int i = start; i <= end; ++i, ++copy_index) {
    data[i] = temp[i];
  }

  delete[] temp;
  return;
}

*/

#include <cstring>
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
  int data;    // hodnota uzla
  Node *next;  // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
  Node *first;  // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (5) -> (5)
        () -> ()
         2, 5, 8, 3
*/
void insertionSort(int *data, const size_t length) {
  for (size_t i = 1; i < length; ++i) {
    int current = data[i];
    size_t j = i;
    while (j > 0 && (data[j - 1] < current)) {
      data[j] = data[j - 1];
      --j;
    }
    data[j] = current;
  }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po
   najmensi (lexikograficky). Preusporiadajte smerniky v poli. Pouzite
   algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet
   prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej",
   nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj",
   "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej",
   nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo
   standardnej kniznice.
*/
void insertionSort(const char *data[]) {
  size_t len = 0;
  while (data[len] != nullptr) ++len;

  for (size_t i = 1; i < len; ++i) {
    const char* current = data[i];
    size_t j = i;
    while (j > 0 && (strcmp(data[j - 1], current) < 0)) {
      data[j] = data[j - 1];
      --j;
    }
    data[j] = current;
  }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List *list) {
  if ((list->first == nullptr) || (list->first->next == nullptr)) {
    return;
  }
  size_t len = 1;
  Node *currentNode = list->first;
  while (currentNode->next != nullptr) {
    currentNode = currentNode->next;
    ++len;
  }
  currentNode = list->first;
  List *sortedList = new List;
  sortedList->first = nullptr;
  for (size_t i = 0; i < len; ++i) {
    Node *nextNode = currentNode->next;
    if (sortedList->first == nullptr) {
      sortedList->first = currentNode;
      currentNode->next = nullptr;
    } else if (currentNode->data >= sortedList->first->data) {
      currentNode->next = sortedList->first;
      sortedList->first = currentNode;
    } else {
      Node *sortedCurrent = sortedList->first;
      Node *sortedPrevious = nullptr;
      while ((sortedCurrent != nullptr) &&
             (currentNode->data < sortedCurrent->data)) {
        sortedPrevious = sortedCurrent;
        sortedCurrent = sortedCurrent->next;
      }
      sortedPrevious->next = currentNode;
      currentNode->next = sortedCurrent;
    }
    currentNode = nextNode;
  }
  list->first = sortedList->first;
  delete sortedList;
  return;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma
   linearnu vypoctovu zlozitost. Kombinuje dve susedne, usporiadane casti v poli
   'input', do jednej usporiadanej casti v poli 'output'. Usporiadanie je od
   najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1]
   bude po vykonani funkcie usporiadana [in]  input  - vstupne pole, ktoreho
   casti input[low]...input[middle-1] a input[middle]...input[high-1] musia byt
   pri volani funkcie usporiadane od najvacsieho prvku po najmensi [in]  low -
   index 1. prvku lavej usporiadanej casti pola 'input' [in]  middle - index 1.
   prvku pravej usporiadanej casti pola 'input' [in]  high   - index za
   poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low]
   ... input[high-1]. Prvky s indexami mensimi ako 'low' sa nemenia (ani v
   jednom poli). Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia
   (ani v jednom poli).

    PRIKLAD:
        low: 4                                          low            middle
   high middle: 8                                        |               | |
        hight: 12                                        V               V V
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,
   2,  1, 10, 10, 10, 10) output pred vykonanim funkcie: (20, 20, 20, 20, 20,
   20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20) output po vykonani funkcie: (20,
   20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low,
                     const size_t middle, const size_t high) {
  size_t left = low;
  size_t right = middle;
  size_t temp_index = low;
  while ((left < middle) && (right < high)) {
    if (input[left] >= input[right]) {
      output[temp_index++] = input[left++];
    } else {
      output[temp_index++] = input[right++];
    }
  }
  while (left < middle) {
    output[temp_index++] = input[left++];
  }
  while (right < high) {
    output[temp_index++] = input[right++];
  }
  return;
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola
   pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (5) -> (5)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho
   pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete
   hlavnu cast algoritmu merge sort.
*/

void mergeSort(int *data, const size_t length) {
  if (length == 0) {
    return;
  }
  int *temp = new int[length];

  int start = 0;
  int end = length - 1;
  if (start == end) {
    delete[] temp;
    return;
  }
  int mid = (start + end) / 2;
  mergeSort(data, mid + 1);
  mergeSort(data + mid + 1, length - mid - 1);
  mergeNeighbours(temp, data, start, mid + 1, end + 1);
  for (int i = start; i <= end; ++i) {
    data[i] = temp[i];
  }
  delete[] temp;

  return;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

int main() {
  int data[] = {2, 5, 8, 3, 6, 1, 4, 7};
  // mergeSort(data, 8);
  // for (int i = 0; i < 8; ++i) {
  //   cout << ' ' << data[i];
  // }
  // cout << endl;
  

  return 0;
}
