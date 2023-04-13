#include "calculator.h"

#include <QLineEdit>
#include <QFont>
#include <QPushButton>
#include <QKeyEvent>
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QWidget{parent}
{
    inputLineEdit = new MyLineEdit;
    inputLineEdit->setText(tr("0"));
    inputLineEdit->setReadOnly(true);
    inputLineEdit->setAlignment(Qt::AlignRight);
    inputLineEdit->setMinimumHeight(100);
    inputLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    inputLineEdit->setFont(QFont("宋体", 25));
    inputLineEdit->setMaxLength(20);

    displayLineEdit = new MyLineEdit;
    displayLineEdit->setReadOnly(true);
    displayLineEdit->setAlignment(Qt::AlignRight);
    displayLineEdit->setMinimumHeight(100);
    displayLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    displayLineEdit->setFont(QFont("宋体", 20));

    displayLayout = new QVBoxLayout;
    displayLayout->setSpacing(1);
    displayLayout->addWidget(displayLineEdit);
    displayLayout->addWidget(inputLineEdit);

    charPushButton = new QPushButton(tr("±"));
    zeroPushButton = new QPushButton(tr("0"));
    pointPushButton = new QPushButton(tr("."));
    resultPushButton = new QPushButton(tr("="));

    onePushButton = new QPushButton(tr("1"));
    twoPushButton = new QPushButton(tr("2"));
    threePushButton = new QPushButton(tr("3"));
    addPushButton = new QPushButton(tr("+"));

    fourPushButton = new QPushButton(tr("4"));
    fivePushButton = new QPushButton(tr("5"));
    sixPushButton = new QPushButton(tr("6"));
    minusPushButton = new QPushButton(tr("-"));

    sevenPushButton = new QPushButton(tr("7"));
    eightPushButton = new QPushButton(tr("8"));
    ninePushButton = new QPushButton(tr("9"));
    multiplyPushButton = new QPushButton(tr("*"));

    dividePushButton = new QPushButton(tr("/"));
    modPushButton = new QPushButton(tr("%"));
    backspacePushButton = new QPushButton(tr("backspace"));
    clearPushButton = new QPushButton(tr("AC"));

    buttonLayout = new QGridLayout;
    buttonLayout->setSpacing(2);

    //addButton(charPushButton, 4, 0);
    addButton(zeroPushButton, 4, 0, 1, 2);
    addButton(pointPushButton, 4, 2);
    addButton(resultPushButton, 4, 3);

    addButton(onePushButton, 3, 0);
    addButton(twoPushButton, 3, 1);
    addButton(threePushButton, 3, 2);
    addButton(addPushButton, 3, 3);

    addButton(fourPushButton, 2, 0);
    addButton(fivePushButton, 2, 1);
    addButton(sixPushButton, 2, 2);
    addButton(minusPushButton, 2, 3);

    addButton(sevenPushButton, 1, 0);
    addButton(eightPushButton, 1, 1);
    addButton(ninePushButton, 1, 2);
    addButton(multiplyPushButton, 1, 3);

    addButton(clearPushButton, 0, 0);
    addButton(backspacePushButton, 0, 1);
    addButton(modPushButton, 0, 2);
    addButton(dividePushButton, 0, 3);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(displayLayout);
    mainLayout->setStretchFactor(displayLayout, 1);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setStretchFactor(buttonLayout, 2);

    isHasPoint = false;
    isHasOperator = false;
    infixExpression = "0";
    op_precedence.insert('+', 0);
    op_precedence['-'] = 0;
    op_precedence['*'] = 1;
    op_precedence['/'] = 1;
    setLayout(mainLayout);

    usefulChar = {Qt::Key_0, Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4,
                  Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8, Qt::Key_9,
                  Qt::Key_Plus, Qt::Key_Minus, Qt::Key_Asterisk, Qt::Key_Slash,
                  Qt::Key_Period, Qt::Key_Backspace, Qt::Key_Return, Qt::Key_Enter};

    connect(zeroPushButton, &QPushButton::clicked, this, [=](){ inputChar('0'); });
    connect(onePushButton,&QPushButton::clicked, this, [=](){ inputChar('1'); });
    connect(twoPushButton, &QPushButton::clicked, this, [=](){ inputChar('2'); });
    connect(threePushButton, &QPushButton::clicked, this, [=](){ inputChar('3'); });
    connect(fourPushButton, &QPushButton::clicked, this, [=](){ inputChar('4'); });
    connect(fivePushButton, &QPushButton::clicked, this, [=](){ inputChar('5'); });
    connect(sixPushButton, &QPushButton::clicked, this, [=](){ inputChar('6'); });
    connect(sevenPushButton, &QPushButton::clicked, this, [=](){ inputChar('7'); });
    connect(eightPushButton, &QPushButton::clicked, this, [=](){ inputChar('8'); });
    connect(ninePushButton, &QPushButton::clicked, this, [=](){ inputChar('9'); });

    connect(resultPushButton, &QPushButton::clicked, this, [=](){ calculte(); });

    connect(pointPushButton, &QPushButton::clicked, this, [=](){ inputChar('.'); });
    connect(addPushButton, &QPushButton::clicked, this, [=](){ inputChar('+'); });
    connect(minusPushButton, &QPushButton::clicked, this, [=](){ inputChar('-'); });
    connect(multiplyPushButton, &QPushButton::clicked, this, [=](){ inputChar('*'); });
    connect(dividePushButton, &QPushButton::clicked, this, [=](){ inputChar('/'); });
    connect(modPushButton, &QPushButton::clicked, this, [=](){ inputChar('%'); });

    connect(clearPushButton, &QPushButton::clicked, this, [=](){ clearInputLineEdit(); });
    connect(backspacePushButton, &QPushButton::clicked, this, [=](){ backspaceInputLineEdit(); });
}

void Calculator::keyPressEvent(QKeyEvent *event)
{
    if(!usefulChar.contains(event->key()))
        return;

    if(event->key() == Qt::Key_Backspace)
    {
        backspaceInputLineEdit();
    }
    else if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        calculte();
    }
    else if(event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9)
    {
        inputChar(event->key());
    }
    else
    {
        inputChar(event->key());
    }
}

double Calculator::calculte()
{
    if(isHasOperator)
    {
        infixExpression.chop(1);
    }
    displayLineEdit->setText(infixExpression + tr("="));
    transform_infix_to_postfix();

    for(int i = 0; i < postfix.size(); ++i)
    {
        if(postfix.at(i).second == 0)
        {
            numStack.push(postfix.at(i).first.toDouble());
        }
        else
        {
            double num2 = numStack.pop();
            double num1 = numStack.pop();
            QString op = postfix.at(i).first;
            if(op == "+")
            {
                result = num1 + num2;
            }
            else if(op == "-")
            {
                result = num1 - num2;
            }
            else if(op == "*")
            {
                result = num1 * num2;
            }
            else if(op == "/")
            {
                result = num1 / num2;
            }
            else if(op == "%")
            {
                while(num1 > num2)
                {
                    num1 -= num2;
                }
                result = num1;
            }
            numStack.push(result);
        }
    }

    infixExpression = QString::number(result);
    postfixExpression.clear();
    postfix.clear();
    inputLineEdit->setText(QString::number(result));
    return result;
}

void Calculator::inputChar(const QChar ch)
{
    if(infixExpression.isEmpty() || infixExpression == "0")
    {
        setFirstChar(ch);
        return;
    }

    //如果上一个字符是操作符，则如下：
    if(isHasOperator)
    {
        //最新输入为数字，加入中缀表达式；否则，更新操作符
        if(isDidit(ch))
        {
            infixExpression += ch;
            isHasOperator = false;
        }
        else if(isHasPoint && ch == '.')
        {
            return;
        }
        else if(!isHasPoint && ch == '.')
        {
            infixExpression.chop(1);
            infixExpression += ch;
            isHasPoint = true;
        }
        else
        {
            infixExpression.chop(1);
            infixExpression += ch;
            isHasPoint = false;
        }
    }
    //如果上一个字符是数字，则如下：
    else
    {
        if(isDidit(ch))
        {
            infixExpression += ch;
        }
        else if(ch == '.' && !isHasPoint)
        {
            infixExpression += ch;
            isHasPoint =true;
        }
        else if(isHasPoint && ch == '.')
        {
            return;
        }
        else
        {
            infixExpression += ch;
            isHasOperator = true;
        }
    }
    inputLineEdit->setText(infixExpression);
}

void Calculator::setFirstChar(const QChar ch)
{
    if(isDidit(ch))
    {
        if(infixExpression == "0")
        {
            infixExpression.clear();
        }
        infixExpression += ch;
    }
    else
    {
        if(ch == '.')
        {
            isHasPoint = true;
        }
        isHasOperator = true;
        infixExpression += ch;
    }
    inputLineEdit->setText(infixExpression);
}

void Calculator::clearInputLineEdit()
{
    infixExpression = "0";
    inputLineEdit->setText(infixExpression);
}

void Calculator::backspaceInputLineEdit()
{
    if(infixExpression.length() <= 1)
    {
        infixExpression = "0";
        inputLineEdit->setText(infixExpression);
        return;
    }

    if(isHasOperator)
    {
        isHasOperator = false;
        infixExpression.chop(1);
        inputLineEdit->setText(infixExpression);
        return;
    }

    if(infixExpression.back() == '.')
    {
        isHasPoint = false;
        infixExpression.chop(1);
        inputLineEdit->setText(infixExpression);
        return;
    }

    infixExpression.chop(1);
    if(!isDidit(infixExpression.back()) && infixExpression.back() != '.')
    {
        isHasOperator = true;
    }
    else if(infixExpression.back() == '.')
    {
        infixExpression.chop(1);
        isHasPoint = false;
    }
    inputLineEdit->setText(infixExpression);
}

bool Calculator::isDidit(const QChar ch)
{
    if(ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

void Calculator::transform_infix_to_postfix()
{
    int startPos = 0;
    for(int i = 0; i < infixExpression.size(); ++i)
    {
        if(isDidit(infixExpression.at(i)) || infixExpression.at(i) == '.')
        {
            continue;
        }
        else
        {
            QString num = infixExpression.mid(startPos, i - startPos);
            startPos = i + 1;
            postfixExpression += num;
            postfix.push_back(qMakePair(num, 0));

            if(operatorStack.isEmpty())
                operatorStack.push(infixExpression.at(i));
            else if(op_precedence[infixExpression.at(i)] > op_precedence[operatorStack.top()])
            {
                operatorStack.push(infixExpression.at(i));
            }
            else
            {
                while(!operatorStack.isEmpty())
                {
                    QChar op = operatorStack.pop();
                    postfixExpression += op;
                    postfix.push_back(qMakePair(op, 1));
                }
                operatorStack.push(infixExpression.at(i));
            }
        }
    }

    QString num = infixExpression.mid(startPos, infixExpression.size() + 1 - startPos);
    postfixExpression += num;
    postfix.push_back(qMakePair(num, 0));

    while(!operatorStack.isEmpty())
    {
        QChar op = operatorStack.pop();
        postfixExpression += op;
        postfix.push_back(qMakePair(op, 1));
    }
}

void Calculator::addButton(QPushButton *button, int row, int column)
{
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonLayout->setRowMinimumHeight(row, 75);
    buttonLayout->addWidget(button, row, column);
}

void Calculator::addButton(QPushButton *button, int row, int column, int rowSpan, int columnSpan)
{
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    buttonLayout->setRowMinimumHeight(row, 75);
    buttonLayout->addWidget(button, row, column, rowSpan, columnSpan);
}
