﻿#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStack>
#include <QMap>

#include "mylineedit.h"

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);


protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    double calculte();


private:
    void addButton(QPushButton* button, int row, int column);
    void addButton(QPushButton *button, int row, int column, int rowSpan, int columnSpan);
    void inputChar(const QChar ch);
    void setFirstChar(const QChar ch);
    void clearInputLineEdit();
    void backspaceInputLineEdit();

    bool isDidit(const QChar ch);
    void transform_infix_to_postfix();

    MyLineEdit* inputLineEdit;
    MyLineEdit* displayLineEdit;
    QVBoxLayout* displayLayout;

    QPushButton* charPushButton;
    QPushButton* zeroPushButton;
    QPushButton* pointPushButton;
    QPushButton* resultPushButton;
    QPushButton* onePushButton;
    QPushButton* twoPushButton;
    QPushButton* threePushButton;
    QPushButton* addPushButton;
    QPushButton* fourPushButton;
    QPushButton* fivePushButton;
    QPushButton* sixPushButton;
    QPushButton* minusPushButton;
    QPushButton* sevenPushButton;
    QPushButton* eightPushButton;
    QPushButton* ninePushButton;
    QPushButton* multiplyPushButton;
    QPushButton* dividePushButton;
    QPushButton* modPushButton;
    QPushButton* backspacePushButton;
    QPushButton* clearPushButton;
    QGridLayout* buttonLayout;

    QVBoxLayout* mainLayout;

    bool isHasPoint;
    bool isHasOperator;
    QChar preChar;
    QString infixExpression;//中缀表达式
    QList<QPair<QString, int>> postfix;
    QString postfixExpression;//后缀表达式
    QStack<double> numStack;
    QStack<QChar> operatorStack;
    double result;

    QMap<QChar, int> op_precedence;

};

#endif // CALCULATOR_H