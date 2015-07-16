#include "toolfloodfill.h"

ToolFloodFill::ToolFloodFill()
{
}

void ToolFloodFill::press(QMouseEvent *e)
{
    Punkt P(e->x(), e->y());
    zamieniany = getColor(P);
    zamaluj(P);
}

void ToolFloodFill::zamaluj(Punkt P)
{
    QStack<Punkt> S;
    int x1, x2;
    Punkt P2;

    S.push(P);
    while (!S.empty()) {
        P = S.pop();
        if (getColor(P) == zamieniany) {
            x1 = P.x-1;
            x2 = P.x+1;
            while (x1 >= 0 && getColor(x1,P.y) == zamieniany)
                --x1;
            while (x2 < obraz->w && getColor(x2,P.y) == zamieniany)
                ++x2;
            for (int i = x1+1; i < x2; ++i) {
                setColor(i,P.y);
                if (P.y-1 >= 0) {
                    P2 = Punkt(i, P.y-1);
                    if (getColor(P2) == zamieniany)
                        S.push(P2);
                }
                if (P.y+1 < obraz->h) {
                    P2 = Punkt(i, P.y+1);
                    if (getColor(P2) == zamieniany)
                        S.push(P2);
                }
            }
        }
    }
}

void ToolFloodFill::sprzatnij() {
    bufor->wklejObraz(obraz);
}

