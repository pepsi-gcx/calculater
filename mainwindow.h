#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getChar();//将QString转换为QByteArray
    void getSuffix();//获取后缀表达式
    void Calc_Suffix();//计算后缀表达式
    void m_init();//初始化

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();


private:
    Ui::MainWindow *ui;
    QString in;//输入的表达式
    QByteArray ba;//输入表达式转换为字节数组
    QStack<char> s1;//中缀表达式转换为后缀表达式时用到的栈
    QVector<QString> out;//后缀表达式
    QStack<float> s2;//后缀表达式计算结果时用到的栈
    float result;//计算结果
};

#endif // MAINWINDOW_H
