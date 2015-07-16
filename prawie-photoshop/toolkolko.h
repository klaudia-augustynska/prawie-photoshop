#ifndef TOOLKOLKO_H
#define TOOLKOLKO_H

#include "tool.h"

class ToolKolko : public Tool
{
public:
    ToolKolko();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
    void rysujOkrag(int x2, int y2);
};

#endif // TOOLKOLKO_H
