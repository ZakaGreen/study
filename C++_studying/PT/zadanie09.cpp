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
datove typy. (8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo
rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE V pripade
implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej
rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE (9)  Vase riesenie
otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo
datovych typov). Testovaci kod ale nebude hodnoteny. (10) Funkcia 'main' musi
byt v zdrojovom kode posledna.
*/

#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
  int value;      // hodnota uzla
  Node* smaller;  // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako
                  // 'value'
  Node* greater;  // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako
                  // 'value

  explicit Node(int value = 0, Node* smaller = nullptr, Node* greater = nullptr)
      : value(value), smaller(smaller), greater(greater) {}
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
  Node* root;  // koren stromu

  explicit BinarySearchTree(Node* root = nullptr) : root(root) {}
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho
   vyhladavacieho stromu. Napriklad, pri hladani minima treba prejst len cez
   potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree* tree) {
  if (tree == nullptr || tree->root == nullptr)
    throw ValueNotExistsException();
  else {
    Node* currentNode = tree->root;
    while (currentNode->smaller != nullptr) {
      currentNode = currentNode->smaller;
    }
    return currentNode->value;
  }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome
   nenachdza
*/

size_t depth(const BinarySearchTree* tree, int value) {
  if (tree == nullptr || tree->root == nullptr)
    throw ValueNotExistsException();
  else {
    size_t hlbka = 0;
    Node* currentNode = tree->root;
    while (currentNode != nullptr) {
      if (value == currentNode->value) return hlbka;
      if (currentNode->value > value) {
        currentNode = currentNode->smaller;
        ++hlbka;
      } else {
        currentNode = currentNode->greater;
        ++hlbka;
      }
    }
    throw ValueNotExistsException();
  }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s
   hodnotou 'value'. Prva hodnota vystupneho zoznamu je hodnota korena, druha
   hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd. Poslednou
   hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie
   zastavilo. Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou
   vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani
   porovnavat. Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu
   prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree* tree, int value) noexcept {
  list<int> lst;
  if (!tree || !tree->root) {
    return lst;
  }
  Node* currentNode = tree->root;
  while (currentNode != nullptr) {
    if (value == currentNode->value) {
      lst.push_back(currentNode->value);
      return lst;
    }
    if (currentNode->value > value) {
      lst.push_back(currentNode->value);
      currentNode = currentNode->smaller;
    } else {
      lst.push_back(currentNode->value);
      currentNode = currentNode->greater;
    }
  }
  return lst;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/

size_t count(const BinarySearchTree* tree) noexcept {
  if (!tree || !tree->root) {
    return 0;
  } else {
    std::queue<Node*> q;
    size_t hlbka = 0;
    q.push(tree->root);
    while (!q.empty()) {
      Node* currentNode = q.front();
      ++hlbka;
      q.pop();
      if (currentNode->smaller) q.push(currentNode->smaller);
      if (currentNode->greater) q.push(currentNode->greater);
    }
    return hlbka;
  }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/

list<int> all(const BinarySearchTree* tree) noexcept {
  list<int> lst;
  if (!tree || !tree->root) {
    return lst;
  }
  stack<Node*> st;
  Node* currentNode = tree->root;
  while (currentNode != nullptr || !st.empty()) {
    while (currentNode != nullptr) {
      st.push(currentNode);
      currentNode = currentNode->smaller;
    }
    currentNode = st.top();
    st.pop();
    lst.push_back(currentNode->value);
    currentNode = currentNode->greater;
  }
  return lst;
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako
   'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich
   podmienku [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/

size_t countGreaterNode(const Node* node, int value);

size_t countGreater(const BinarySearchTree* tree, int value) noexcept {
  if (!tree || !tree->root) return 0;
  return countGreaterNode(tree->root, value);
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/
// void clear(BinarySearchTree* tree) noexcept {
//   if (!tree || !tree->root) return;
//   while (tree->root->greater != nullptr || tree->root->smaller != nullptr){
//     Node* currentNode = tree->root;
//     while(currentNode->greater->greater != nullptr ||
//     currentNode->smaller->smaller != nullptr || currentNode->greater->smaller
//     != nullptr || currentNode->smaller->greater != nullptr){
//       if (currentNode->smaller) currentNode = currentNode->smaller;
//       if (currentNode->greater) currentNode = currentNode->greater;
//     }
//     if (currentNode->smaller){
//       delete currentNode->smaller;
//       currentNode->smaller = nullptr;
//     }
//     if (currentNode->greater){
//       delete currentNode->greater;
//       currentNode->greater = nullptr;
//       }

//   }
//   delete tree->root;
//   tree->root = nullptr;
// }
void clearSubtree(Node* node);

void clear(BinarySearchTree* tree) noexcept {
  if (!tree) return;
  clearSubtree(tree->root);
  tree->root = nullptr;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/

size_t contains(const vector<int>& data, int value) noexcept {
  int len = data.size();
  if (len == 0) return 0;
  int min = 0;
  int max = len - 1;
  size_t cnt = 0;
  while (min <= max) {
    ++cnt;
    int mid = (min + max) / 2;
    if (value < data[mid]) {
      max = mid - 1;
    } else if (value > data[mid]) {
      min = mid + 1;
    } else {
      return cnt;
    }
  }
  return cnt;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore
   slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac",
   "okno", "luk") vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno"
   -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string>& data) noexcept {
  map<string, size_t> mp;
  for (string i : data) {
    ++mp[i];
  }
  return mp;
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov
   jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa
   slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v
   'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac",
   "okno", "luk") vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" ->
   {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string>& data) noexcept {
  map<string, set<size_t>> mp;
  size_t ind = 0;
  for (const string& i : data) {
    mp[i].insert(ind);
    ++ind;
  }
  return mp;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------
void clearSubtree(Node* node) {
  if (!node) return;
  clearSubtree(node->smaller);
  clearSubtree(node->greater);
  delete node;
}

size_t countGreaterNode(const Node* node, int value) {
  if (!node) return 0;

  if (node->value <= value) {
    return countGreaterNode(node->greater, value);
  } else {
    size_t left = countGreaterNode(node->smaller, value);
    size_t right = countGreaterNode(node->greater, value);
    return 1 + left + right;
  }
}

int main() {
  // tu mozete doplnit testovaci kod

  return 0;
}
