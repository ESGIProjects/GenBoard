#pragma once

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "genboard.h"

class TictactoeBoard : virtual public GenBoard
{
public:
    TictactoeBoard();
};