#ifndef TOOLLINIA_H
#define TOOLLINIA_H

#include "tool.h"

class ToolLinia : public Tool
{
public:
    ToolLinia();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
    void rysujLinie(int x2, int y2);
    void rysujLinie(Punkt A, Punkt B);
};

#endif // TOOLLINIA_H
