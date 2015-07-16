# Prawie Photoshop
Połączenie zadań na grafikę 2D wykonywanych w ramach przedmiotu _"Laboratorium Grafiki i Multimediów"_ jako jeden projekt. Wykorzystany został C++/Qt.

Zalety projektu:

- polimorfizm - jest klasa abstrakcyjna Tool oraz implementacje w postaci poszczególnych narzędzi
- tworzenie warstw - dzięki temu naprawdę przypomina Photoshopa :)
- własne widżety - widoczne w okienku wyboru kolorów; wykorzystują zdarzenia.

Możliwości:

- rysowanie punktów, prostych, koła, elipsy, obrót elipsy
- rysowanie krzywych Béziera, krzywych B-Sklejanych z możliwością zmiany punktów odniesienia przy pomocy myszki
- wypełnianie obszaru (floodfill) oraz kształtu (scanline)
- zmiana aktywnego koloru oraz koloru tła w odniesieniu do modeli RGB oraz HSV
- zmiana trybu mieszania warstw, ustawianie przezroczystości dla warstwy
