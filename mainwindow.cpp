#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);



    int width = 5;
    int height = 5;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j>width;j++)
        {
            int t = qrand()%2;
            int n = qrand()%3;
            test1(t,n,i,j,width,height);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//添加液滴
{
    m_d = Drop(ui->spinBox->value(),ui->spinBox_2->value());
    ui->label->update();
    ui->spinBox_3->setMaximum(m_d.height);
    ui->spinBox_3->setMinimum(1);
    ui->spinBox_3->setValue(1);
    ui->spinBox_4->setMaximum(m_d.width);
    ui->spinBox_4->setMinimum(1);
    ui->spinBox_4->setValue(1);
    ui->spinBox_6->setMaximum(m_d.height);
    ui->spinBox_6->setMinimum(1);
    ui->spinBox_6->setValue(1);
    ui->spinBox_7->setMaximum(m_d.width);
    ui->spinBox_7->setMinimum(1);
    ui->spinBox_7->setValue(1);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label && event->type() == QEvent::Paint)
    {
        MyPainter();
        return true;
    }
    return QMainWindow::eventFilter(watched,event);
}

void MainWindow::MyPainter()
{
    QPainter painter(ui->label);
    QPen pen;

    for(int i=0;i<m_d.height;i++)
    {
        for	(int j=0;j<m_d.width;j++)
        {
            painter.setBrush(QBrush(Qt::transparent));

            if(m_d.T.at(i).at(j) ==0)
            {
                painter.setBrush(QBrush(Qt::white));
            }
            else if(m_d.T.at(i).at(j) == 1)
            {
                painter.setBrush(QBrush(Qt::green));
            }
            else if(m_d.T.at(i).at(j) > 1)
            {
                painter.setBrush(QBrush(Qt::white));
            }

            if(m_d.N.at(i).at(j) == 0)
            {
                painter.setBrush(QBrush(Qt::red));
            }
            if(m_d.N.at(i).at(j) > 0)
            {
                painter.setBrush(QBrush(Qt::white));
            }
            painter.drawRect(10+j*10,10+i*10,10,10);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int i = ui->spinBox_3->value();
    int j = ui->spinBox_4->value();
    m_d.T[i-1][j-1] = ui->spinBox_5->value();
    ui->label->update();
    j++;
    if(j> m_d.width)
    {
        ui->spinBox_4->setValue(1);
        if(i == m_d.height)
        {
            QMessageBox::information(this,"information","finish");
            i = 1;
            j = 1;
            while (true)
            {
                if(m_d.T[i-1][j-1] == 1)
                {
                    ui->spinBox_6->setValue(i);
                    ui->spinBox_7->setValue(j);
                    break;
                }
                else
                {
                    j++;
                    if(j > m_d.width)
                    {
                        j=1;
                        i++;
                    }
                    if(i>m_d.height)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            ui->spinBox_3->setValue(i+1);
        }
    }
    else
    {
        ui->spinBox_4->setValue(j);
    }
}

bool MainWindow::test1(int t, int n, int r, int c,int w,int h)
{
    if(t != 1)
    {
        return false;
    }
    if(n !=0)
    {
        return false;
    }
    int newW = 1;
    int newH = 1;
    if(w == 1 && h == 1)
    {
        newW = 1;
        newH =1;
    }
    else if(w == 1 || h == 1 )
    {
        if(w == 1)
        {
            newW = 1;
            if(r>h-r)
            {
                newH = h-r+1;
            }
            else
            {
                newH = r;
            }
        }
        else
        {
            newH = 1;
            if(c>w-c)
            {
                newW = w-c+1;
            }
            else
            {
                newW = c;
            }
        }
    }
    else
    {
        if(r == 0 || r == h || c == 0 || c == w)//在边上
        {
            if(r == 0)
            {
                //切割位置 r=1,目标液滴 大小 （1，w）坐标（0，0）
                newH = 1;
                newW = w;
            }
            else if(r == h)
            {
                //切割位置 r = h-1; (1,w) 坐标（h，0）
                newH = 1;
                newW = w;
            }
            else if(c == 0)
            {
                //切割位置 c=1；大小（h,1）坐标（0,0）
                newH = h;
                newW = 1;
            }
            else if(c == w)
            {
                //切割位置c=w-1;大小（h,1）坐标（0,w）
                newH = h;
                newW = 1;
            }
        }
        else
        {
            //在中间
            if(w>h) //宽大于高
            {
                if(c > w-c)
                {
                    newH = h;
                    newW = w-c + 1;
                }
                else
                {
                    newH = h;
                    newW = c;
                }
            }
            else
            {
                if(r>h-r)
                {
                    newH = h - r + 1;
                    newW = w;
                }
                else
                {
                    newH = r;
                    newW = w;
                }
            }
        }

    }

    ui->spinBox->setValue(newH);
    ui->spinBox_2->setValue(newW);
    on_pushButton_clicked();
    return true;
}

void MainWindow::on_pushButton_3_clicked()
{
    int i = ui->spinBox_6->value();
    int j = ui->spinBox_7->value();
    m_d.N[i-1][j-1] = ui->spinBox_8->value();
    ui->label->update();
    while(true)
    {
        j++;
        if(j>m_d.width)
        {
            i++;
            j=1;
            if(i>m_d.height)
            {
                QMessageBox::information(this,"information","finish");
                break;
            }
        }
        if(m_d.T[i-1][j-1] == 1)
        {
            break;
        }
    }
    ui->spinBox_6->setValue(i);
    ui->spinBox_7->setValue(j);

}

void MainWindow::on_pushButton_4_clicked()
{
    int t =1;
    int n=0;
    int r = ui->spinBox_9->value();
    int c = ui->spinBox_10->value();
    int w = m_d.width;
    int h = m_d.height;
    test1(t,n,r,c,w,h);
}
