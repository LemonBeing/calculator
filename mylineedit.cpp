#include "mylineedit.h"

#include <QKeyEvent>
#include <QDebug>

MyLineEdit::MyLineEdit()
{

}

void MyLineEdit::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
}
