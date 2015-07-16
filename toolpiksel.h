#ifndef TOOLPIKSEL_H
#define TOOLPIKSEL_H

#include "tool.h"
#include "toollinia.h"

class ToolPiksel : public Tool
{
public:
    ToolPiksel();
    void press(QMouseEvent *);
    void move(QMouseEvent *);
    void release(QMouseEvent *);
    void sprzatnij();
    ToolLinia *linia;
};

#endif // TOOLPIKSEL_H
