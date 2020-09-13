#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(450,450);
    ui->lineEdit->setReadOnly(true);//只读模式
    ui->lineEdit->setAlignment(Qt::AlignRight);//从右侧显示
    setWindowTitle(QString("简易计算器"));//设置标题
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getChar()  //将QString转换为QByteArray
{
    ba=in.toLatin1();
}

void MainWindow::getSuffix()  //获取后缀表达式
{
  for(int i=0;i<ba.size();i++)
  {
      if((ba[i]>='0' && ba[i]<='9')||ba[i]=='.')//1,数字直接输出
      {
         QString str;
         QByteArray m;
         for(;(ba[i]>='0' && ba[i]<='9')||ba[i]=='.';i++)
         {
             //将一个数字存储到字节数组m中
             char x=ba[i];
             m.append(x);
         }
         //将字节数组m转换为QString，并将字符串输出
         str=QString(m);
         out.append(str);
         i--;
      }
      else if(s1.isEmpty())//2,遇见非数字时, 如果堆栈为空，则直接把该字符放入堆栈
      {
          s1.push(ba[i]);
          if(ba[i]=='s' || ba[i]=='c'||ba[i]=='t'||ba[i]=='l' )
          {
              //把字符转换为字符串输出

              char x=ba[i];
              out.append(QString(x));
              i=i+2;
          }
      }
      else if(ba[i]=='+' || ba[i]=='-')
          //2.1,如果是+或- 那么遍历堆栈栈顶元素 一直输出优先级>=加减的 即输出栈顶的+-*/,
          //当遇到其他字符时（如左括号）或堆栈空时break
      {
          while(!s1.empty())
          {
              if(s1.top()=='+' || s1.top()=='-'||s1.top()=='*' || s1.top()=='/')
              {
                  //把字符转换为字符串输出
                  QString str=QString(s1.pop());
                  out.append(str);
              }
              else break;
          }
          s1.push(ba[i]);
      }
      else if(ba[i]=='*' || ba[i]=='/')  //2.2,如果是*或/ 那么遍历堆栈栈顶元素 一直输出优先级>=乘除的 即输出栈顶的*/,
          //当遇到其他字符时（如左括号，减号，除号）或堆栈空时break
      {
          while(!s1.empty())
          {
              if(s1.top()=='*' || s1.top()=='/')
              {
                  //把字符转换为字符串输出
                  QString str=QString(s1.pop());
                  out.append(str);
              }else break;
          }
          s1.push(ba[i]);
      }
      else if(ba[i]=='(')
          //2.4,如果该字符是左括号时，直接放入堆栈
      {
          s1.push(ba[i]);
      }
      else if(ba[i]==')')
          //2.3,如果该字符是右括号时，一直输出栈顶元素，直到遇见左括号为止break:
      {
          while(!s1.empty())
          {
              if(s1.top()=='(')
              {
                  s1.pop();
                  break;
              }
              //把字符转换为字符串输出
              QString str=QString(s1.pop());
              out.append(str);
           }
      }
  }

  //字符串循环结束后 再输出堆栈中剩余的数据
  while(!s1.empty()){
      //把字符转换为字符串输出
      QString str=QString(s1.pop());
      out.append(str);
  }
  //输出后缀表达式
  qDebug()<<out;
}

void MainWindow::Calc_Suffix()  //计算后缀表达式
{
  for(int i=0;i<out.size();i++)
  {
      bool is_Num =true;
      out[i].toFloat(&is_Num);
      if(is_Num)//如果是数字，直接入栈
      {
          s2.push(out[i].toFloat(&is_Num));
      }
      else if(out[i]=="+"||out[i]=="-"||out[i]=="*"||out[i]=="/"||out[i]=="s"||out[i]=="c"||out[i]=="t"||out[i]=="l")
          //如果是运算符，弹栈两次，并进行运算，运算后，结果入栈
      {
          float x=s2.pop();
          float y=s2.pop();
          if(out[i]=="+")
          {
              s2.push(y+x);
          }else if(out[i]=="-"){
              s2.push(y-x);
          }else if(out[i]=="*"){
              s2.push(y*x);
          }else if(out[i]=="/"){
              s2.push(y/x);
          }
      }
      else if(out[i]=="s"||out[i]=="c"||out[i]=="t"||out[i]=="l")
      {
          float x=s2.pop();
          if(out[i]=="s")
             s2.push(sin(x));
          if(out[i]=="c")
              s2.push(cos(x));
          if(out[i]=="t")
             s2.push(tan(x));
          if(out[i]=="l")
             s2.push(log(x));
      }
  }
  result = s2.pop();
  qDebug()<<result;
}

void MainWindow::m_init()
{
    ba.clear();
    out.clear();
}


void MainWindow::on_pushButton_clicked()
{
    //等于号
    in=ui->lineEdit->text();//获取表达式
    getChar();
    getSuffix();
    Calc_Suffix();
    ui->lineEdit->clear();//清空文本编辑框
    ui->lineEdit->setText(QString("%1").arg(result));//显示结果
    m_init();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(0));
}

void MainWindow::on_pushButton_3_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(1));
}

void MainWindow::on_pushButton_4_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(2));
}

void MainWindow::on_pushButton_5_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(3));
}

void MainWindow::on_pushButton_6_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(4));
}

void MainWindow::on_pushButton_7_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(5));
}

void MainWindow::on_pushButton_8_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(6));
}

void MainWindow::on_pushButton_9_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(7));
}

void MainWindow::on_pushButton_10_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(8));
}

void MainWindow::on_pushButton_11_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(9));
}

void MainWindow::on_pushButton_12_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("+"));
}

void MainWindow::on_pushButton_13_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("-"));
}

void MainWindow::on_pushButton_14_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("*"));
}

void MainWindow::on_pushButton_15_clicked()
{
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("/"));
}

void MainWindow::on_pushButton_16_clicked()
{
    //清空所有内容，并初始化
    ui->lineEdit->clear();
    m_init();
}

void MainWindow::on_pushButton_17_clicked()
{
    //退格删除一个字符
    ui->lineEdit->backspace();
}

void MainWindow::on_pushButton_18_clicked()
{
    //前括号
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("("));
}

void MainWindow::on_pushButton_19_clicked()
{
    //后括号
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg(")"));
}

void MainWindow::on_pushButton_20_clicked()
{
    //小数点
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("."));
}

void MainWindow::on_pushButton_21_clicked()
{
    //sin
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("sin"));
}

void MainWindow::on_pushButton_22_clicked()
{
    //cos
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("cos"));
}

void MainWindow::on_pushButton_23_clicked()
{
    //tan
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("tan"));
}

void MainWindow::on_pushButton_24_clicked()
{
    //平方
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("^2"));
}

void MainWindow::on_pushButton_25_clicked()
{
    //最大公约数
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("最大公约数"));
}

void MainWindow::on_pushButton_26_clicked()
{
    //最小公倍数
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("最小公倍数"));
}

void MainWindow::on_pushButton_27_clicked()
{
    //log
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("ln"));
}

void MainWindow::on_pushButton_28_clicked()
{
    //三次方
    QString str=ui->lineEdit->text();
    ui->lineEdit->setText(QString("%1%2").arg(str).arg("^3"));
}
