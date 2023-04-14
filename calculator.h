#ifndef CALCULATOR_H
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

    void resetAllValue();       //每次计算后，重置isHasPoint和isHasOperator
    void resetIsHasPoint();     //每次计算后，根据result重置isHasPoint
    void printIsHasPoint();     //测试函数，正序输出isHasPoint

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

    QStack<bool> isHasPoint;    //每输入一个字符，都更新小数点的作用范围，主要用于backspace功能
    bool isHasOperator;     //上一个字符是否是操作符，不包括小数点
    QString infixExpression;    //中缀表达式
    QList<QPair<QString, int>> postfix;     //后缀表达式，同时用int值记录该值是数字还是操作符
    QString postfixExpression;  //后缀表达式
    QStack<double> numStack;    //数字存储栈
    QStack<QChar> operatorStack;    //操作符存储栈
    double result;

    QMap<QChar, int> op_precedence;     //存储操作符及其优先级，通过int值存储操作的优先级
    QList<int> usefulChar;  //存储可从键盘获得的键值
};

#endif // CALCULATOR_H
