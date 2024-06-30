#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QEvent>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct Drop{
    int width,height;
    QVector<QVector<int>> T,N;

    Drop(int h, int w)
    {
        width = w;
        height = h;
        T.clear();
        N.clear();
        for(int i=0;i<h;i++)
        {
            QVector<int> temp;
            for(int j=0;j<w;j++)
            {
                temp.append(-1);
            }
            T.append(temp);
            N.append(temp);
        }
    }
}Drop;

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *watched,QEvent* event) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    void MyPainter();
    bool test1(int t, int n, int r, int c,int w,int h);

private:
    Ui::MainWindow *ui;

    Drop m_d = Drop(0,0);
};
#endif // MAINWINDOW_H
