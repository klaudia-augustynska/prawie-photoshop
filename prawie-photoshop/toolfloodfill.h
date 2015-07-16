#ifndef TOOLFLOODFILL_H
#define TOOLFLOODFILL_H

#include "tool.h"
#include <QStack>

class ToolFloodFill : public Tool
{
public:
    ToolFloodFill();
    void press(QMouseEvent *);
    void sprzatnij();
private:
    void zamaluj(Punkt);
    QColor zamieniany;
};

#endif // TOOLFLOODFILL_H
