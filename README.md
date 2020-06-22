# Projekt-4-Symulator-dzwigu

## Wstęp
Rozwiązanie zadania 4.3 z projektu czwartego na przedmiot Techniki Programowania wykonane przez Mateusza Czapskiego i Piotra Łyczko, oparte o przykładowy program draw2 udostępniony przez prowadzących zajęcia.

## Działanie programu
Uruchomiony program wyświetla w oknie systemu Windows wszystkie przyciski wymagane do jego obsługi. Wciśnięcie przycisku **Start/reset** rysuje model 2D dźwigu w początkowej pozycji, oraz dostępne dla użytownika figury:
* trzy koła
* jeden kwadrat

Przyciski:
* **Start/reset** - pozwala na ponowne rysowanie całej planszy,
* **Up, Down, Left, Right** - uruchamiają, zrealizowane za pomocą timera, przesuwanie się haka (*końcówki liny*) dźwigu,
* **Stop** - zatrzymuje poruszanie się haka dźwigu,
* **Catch** - pozwala na chwycenie przez hak wybranej figury geometrycznej,
* **Release** - odczepia hak od aktualnie przenoszonej figury.

## Realizacja
Interfejs graficzny systemu Windows z elementami (dźwig, figury geometryczne, elementy ruchome dźwigu) rysowanymi z użyciem GDI+.
Przemieszczanie liny oraz haka dźwigu zrealizowane za pomoca timera, z aktualizacją jedynie obecnie zmieniającej się części obrazu w celu zminimalizowania efektu migotania wywołanego ponownym rysowaniem widocznej planszy.
Dane o dostępnych dla użytkownika figurach, zdefiniowanych w strukturze *figure*, zapisywane są w tablicy tych struktur. Nazwa *name* = s oznacza kwadrat, a *name* = c oznacza okrąg.
Na końcu kodu źródłowego znajdują się funkcje odpowiedzialne za zachowanie warunków danych w zadaniu. Funkcje kończące się członem *Check* odpowiedzialne są za utrzymywanie wszystkich elementów ruchomych w zadanym w programie obszarze roboczym. Funkcja *treeCircle* sprawdza natomiast warunek pozwalający na zbudowanie wieży z maksymalnie trzech elementów o kształcie koła. 
