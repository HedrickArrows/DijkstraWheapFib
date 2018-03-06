# DijkstraWheapFib
Projekt wyszukiwania dwóch najkrótszych ścieżek w grafie z użyciem algorytmu Djikstry i kopca Fibonacciego

Oryginalna treść zadania

Spacer Czerwonego Kapturka
Czerwony Kapturek chodziła do babci najkrótszą drogą. Jednak dziś chce przejść inną trasą, musi być to także bardzo krótka droga, bo niesie ciepły obiad dla babci. Poprosiła Cię o znalezienie drugiej najkrótszej trasy pomiędzy jej domkiem, a domkiem babci.
Uwaga: Druga najkrótsza droga nie może zawierać w całości pierwszej drogi.
Wejście
W pierwszej linii znajdują się dwie liczby n m - pierwsza, to liczba skrzyżowań w lesie, druga, to liczba dróg pomiędzy skrzyżowaniami.
Następnie w m kolejnych liniach wypisane są trzy liczby v u w - drogi pomiędzy skrzyżowaniami v i u wraz z odległością w pomiędzy nimi.
Skrzyżowania indeksowane są od 0. Czerwony Kapturek zaczyna podróż na skrzyżowaniu o indeksie 0 i musi dojść do skrzyżowania o indeksie n-1, gdzie mieszka babcia.
Wyjście
W linii należy wypisać dwie liczby - najkrótszą odległość i drugą najkrótszą odległość pomiędzy domami Czerwonego Kapturka i babci. Jeśli nie ma najkrótszej drogi lub drugiej najkrótszej drogi pomiędzy domem Czerwonego Kapturka a domem babci należy wpisać #.
Przykład

Wejście
7 8
0 1 1
1 2 1
4 0 1
2 4 2
2 3 2
5 2 1
3 6 1
6 5 1

Wyjście
4 5


Wejście
4 4
0 1 1
0 2 1
3 1 1
3 2 1

Wyjście
2 2


Wejście

3 2
0 1 1
1 2 1


Wyjście
#

Wejście
5 5
0 1 1
1 2 1
3 1 1
2 3 1
1 4 1

Wyjście
#

