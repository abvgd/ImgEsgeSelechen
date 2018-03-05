#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imgprc.h"

#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>

#include <QDebug>


class GeometryCalcUI;
class ParamBlock;
class ManipulateBlock;
class MainWindow;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QLineEdit* le_img_and_dir;

    QTextEdit* te_in_dat;

    QPushButton* pb_img_show;
protected:
    QPushButton* pb_canny;
    QPushButton* pb_claster;
    QPushButton* pb_clear_garage;
    QPushButton* pb_circl_srch;

    QCheckBox* chb_prc_show;

    QHBoxLayout* hlay0;
    QHBoxLayout* hlay1;
    QHBoxLayout* hlay2;
    QVBoxLayout* vlay0;
    QVBoxLayout* vlay1;
    QVBoxLayout* vlay2;



public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    // redefining the function to close opencv windows
    void closeEvent(QCloseEvent* /*event*/)
    {
        QCoreApplication::processEvents();
        cv::destroyAllWindows();

    }

private:
    Ui::MainWindow *ui;
};



class ParamBlock : public MainWindow
{
    Q_OBJECT

private:
    QHBoxLayout* _hLay;
    QLabel* functInf;
    QLineEdit* functParam;

    QPushButton* next;
    QPushButton* defaultStr;

    QWidget *paramBlcWdgt;

    struct strDefAndVal {

        const QString gausian_default = QString("Size ksize = 3 3, double sigmaX = 3, ") +
                                             "double sigmaY = 0, int borderType = 4";
        QString gausian_value   = gausian_default;


        const QString canny_default = QString("double threshold1 = 3, double threshold2 = 3, ") +
                                          "int apertureSize = 3, bool L2gradient = false";
        QString canny_value = canny_default;

        std::vector<std::pair<const QString, QString>> cont_str {
            std::pair<const QString, QString>(gausian_default, gausian_value),
            std::pair<const QString, QString>(canny_default, canny_value)
        };

        std::vector<std::pair<const QString, QString>>::iterator it = cont_str.begin();

        QString getStrLoop(bool get_default = false);

        void setStr(QString str);

    };

    struct fInfStru {
        std::vector<QString> functName {"F gausianBlur", "F canny"};
        std::vector<QString>::iterator it = functName.begin();

        QString getStrLoop()
        {
            ++it;
            if(it == functName.end())
                it = functName.begin();

            return *it;
        }
    } *f_inf_stru;

public:
    ParamBlock(QWidget *parent = 0);
    ~ParamBlock() {}

    ImgPrc* imgPrc = nullptr;

    strDefAndVal* readPrc;

    QHBoxLayout* hederLay;
    QVBoxLayout* midlLay;
};


class GeometryCalcUI : public  ParamBlock
{
    Q_OBJECT

    QWidget* gem_wid;
    QLabel*      lb0;
    QPushButton* pb0;
    QHBoxLayout* hl0;


protected:
    VectorClaster* vecClst;
private:

    cv::Mat test_mat; // is rename
    cv::Mat mat_fon;


public:

    explicit GeometryCalcUI(QWidget *parent = 0) : ParamBlock(parent)
    {

        gem_wid = new QWidget;
        lb0     = new QLabel("claster show");
        pb0     = new QPushButton("show");
        hl0     = new QHBoxLayout;

        hl0->addWidget(lb0);
        hl0->addWidget(pb0);
        gem_wid->setLayout(hl0);

        vecClst = new VectorClaster(test_mat);

        connect(pb_claster, &QPushButton::clicked, [&] () {
            if(imgPrc == nullptr) {
                pb_img_show->animateClick(500);
                QCoreApplication::processEvents();
                pb_claster->animateClick(1000);
            } else {
                if(!gem_wid->isHidden()) {
                    qDebug("delete _hederLay");

                    cv::destroyWindow("countClasterSel result show");

                    gem_wid->hide();
                } else {

                    qDebug("vlay0->addLayout(_hederLay)");

                    test_mat = imgPrc->imgLine->frame.clone();
                    mat_fon  = imgPrc->origImg->frame.clone();

                    gem_wid->show();
                    vlay0->addWidget(gem_wid);
                }

            }

        });


        connect(pb0, &QPushButton::clicked, [&] () {

            vecClst->countClasterSel();
            cv::namedWindow("countClasterSel result show");
            cv::imshow("countClasterSel result show", vecClst->writeClasterColor(mat_fon));

        } );

    }

    ~GeometryCalcUI()
    {
        delete vecClst;
    }

    void clearLayout(QLayout* layout, bool deleteWidgets = true)
    {
        while (QLayoutItem* item = layout->takeAt(0))
        {
            if (deleteWidgets)
            {
                if (QWidget* widget = item->widget())
                    widget->deleteLater();
            }
            if (QLayout* childLayout = item->layout())
                clearLayout(childLayout, deleteWidgets);
            delete item;
        }
    }

};


class ManipulateBlock : private MainWindow
{
    MainWindow& winH;

    QPushButton* claster;
    QPushButton* clasterShow;
public:
    ManipulateBlock(MainWindow& win) : winH(win)
    {

        claster     = new QPushButton("claster");
        clasterShow = new QPushButton("clst show");

        connect(claster, &QPushButton::clicked, [&] () {

        });
    }
};


#endif // MAINWINDOW_H
