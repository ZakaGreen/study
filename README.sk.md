[English](README.md) · [Slovenčina](README.sk.md) · [Русский](README.ru.md)

# Programátorské zadania

Moje univerzitné cvičenia v **C, C++, Jave a R** zo štúdia aplikovanej informatiky na FEI STU v Bratislave.

Je to zbierka samostatných zadaní, nie jedna aplikácia. Príklady zachytávajú precvičovanie základov programovania, údajových štruktúr, objektovo orientovaného programovania a štatistiky.

Smerníky a štruktúry v C som si spočiatku nevedel dobre predstaviť. Štúdium fungovania pamäte mi pomohlo porozumieť im a zadania som nakoniec vypracoval sám. Príklad v C uvedený nižšie je súčasťou tejto praxe. Moje [laboratórne úlohy s xv6](https://github.com/ZakaGreen/xv6-labs-2026) pokračujú témami operačných systémov; zadania sú aj na [GitLabe](https://gitlab.com/ilushkalubotin/xv6-xliubotin-2026).

## Kde začať

| Príklad | Čomu sa venuje |
| --- | --- |
| **[Simulácia armád v C](C_studying/Programming_2/zadanie4)** | Štruktúry, smerníky, údaje o výbave, kontrola vstupu a logika súbojov po ťahoch. |
| **[Evidencia tovaru v Jave](Java_studying/OOP/zadanie7)** | Dedičnosť, rozhrania, kolekcie, výnimky, triedenie a načítanie/ukladanie údajov o produktoch. Obsahuje testy k zadaniu. |
| **[Programovacie techniky v C++](C%2B%2B_studying/PT)** | Séria cvičení v C++ a objektovo orientovanom programovaní. |
| **[Matematická štatistika v R](R_studying/MatStat)** | Štatistické cvičenia a práca s analýzou dát. |

## Spustenie príkladu v C

S nainštalovaným GCC spustite z koreňového adresára repozitára:

```bash
cd C_studying/Programming_2/zadanie4
gcc -std=c11 -Wall -Wextra z4.c data.c -o army-simulation
./army-simulation 0
```

Malý príklad vstupu:

```text
1
Alice sword
1
Bob axe
```

Prvé číslo určuje veľkosť prvej armády, nasledujú jej jednotky a výbava. Druhá armáda používa rovnaký formát. Argument `0` vypíše inicializované armády bez spustenia boja. Názvy a vlastnosti výbavy sú definované v [data.c](C_studying/Programming_2/zadanie4/data.c).

Tento priamy príkaz GCC a vzorový vstup boli overené na Linuxe. Pôvodná konfigurácia CMake očakáva inú štruktúru adresárov, preto pre súbory uložené v tomto repozitári použite uvedený príkaz.

## Mapa repozitára

| Adresár | Obsah |
| --- | --- |
| [C_studying](C_studying) | Programovanie v C a cvičenia z architektúry počítačov. |
| [C++_studying](C%2B%2B_studying) | C++ a programovacie techniky. |
| [Java_studying](Java_studying) | Zadania z OOP a príprava na skúšky. |
| [R_studying](R_studying) | Cvičenia z matematickej štatistiky. |
| [MPPI_studying](MPPI_studying) | Ďalšie školské zadania v C. |
| [TZI_studying](TZI_studying) | Automaty a teoretická informatika. |

## Poznámky

- Zadania sú v rôznych štádiách a majú vlastné požiadavky; pre celý repozitár neexistuje jeden spoločný príkaz na zostavenie alebo testovanie.
- Podklady, dáta a testy poskytnuté v rámci predmetov sú uložené spolu s mojimi riešeniami. Neznamená to, že som autorom každého súboru alebo že všetky testy prechádzajú.
- Pôvodné názvy súborov a slovenské či ruské komentáre sú zachované, aby zodpovedali zadaniam.

Moje cvičenia v Pythone a strojovom učení sú v [AI_studying](https://github.com/ZakaGreen/AI_studying).
