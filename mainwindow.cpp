#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    le_img_and_dir = new QLineEdit("C:/img");

    te_in_dat = new QTextEdit();

    pb_img_show     = new QPushButton("Img show");
    pb_claster      = new QPushButton("claster");
    pb_clear_garage = new QPushButton("Clear Gar");
    pb_canny        = new QPushButton("Sel Canny");
    pb_circl_srch   = new QPushButton("Circl Srch");

    chb_prc_show    = new QCheckBox("Show ful Img");

    hlay0 = new QHBoxLayout;
    hlay1 = new QHBoxLayout;
    hlay2 = new QHBoxLayout;

    vlay0 = new QVBoxLayout;
    vlay1 = new QVBoxLayout;
    vlay2 = new QVBoxLayout;

    vlay0->addLayout(hlay0);

    hlay0->addWidget(le_img_and_dir);
    hlay0->addWidget(chb_prc_show);

    vlay0->addLayout(hlay1);

    hlay1->addLayout(vlay1);

    vlay1->addWidget(te_in_dat);

    hlay1->addLayout(vlay2);

    vlay2->addWidget(pb_img_show);
    vlay2->addWidget(pb_claster);
    vlay2->addWidget(pb_clear_garage);
    vlay2->addWidget(pb_canny);
    vlay2->addWidget(pb_circl_srch);

    ui->centralWidget->setLayout(vlay0);

}

MainWindow::~MainWindow()
{
    delete ui;
}



ParamBlock::ParamBlock(QWidget *parent) : MainWindow(parent)
{

    if(imgPrc == nullptr)
        imgPrc = new ImgPrc(le_img_and_dir->text());

    readPrc = new strDefAndVal;
    f_inf_stru = new fInfStru;

    hederLay   = new QHBoxLayout;
    midlLay    = new QVBoxLayout;
    _hLay      = new QHBoxLayout;
    functInf   = new QLabel("F gausianBlyr");
    next       = new QPushButton("next F");
    defaultStr = new QPushButton("default");
    functParam = new QLineEdit(readPrc->it->first);

    paramBlcWdgt = new QWidget();

    midlLay->addLayout(_hLay);

    _hLay->addWidget(functParam);

    hederLay->addLayout(midlLay);

    hederLay->addWidget(functInf);
    hederLay->addWidget(next);
    hederLay->addWidget(defaultStr);

    paramBlcWdgt->setLayout(hederLay);



    connect(next, &QPushButton::clicked, [&] () {

        readPrc->setStr(functParam->text());

        functParam->setText(readPrc->getStrLoop());

        functInf->setText(f_inf_stru->getStrLoop());
    });

    connect(defaultStr, &QPushButton::clicked, [&] () {

        readPrc->it->second = readPrc->it->first;
        functParam->setText(readPrc->it->second);
    });

//    connect(functParam, &QLineEdit::returnPressed, [&] () {

//        readPrc->setStr(functParam->text());
//        readPrc->writeToSetVal(imgPrc);
//    });

    connect(pb_img_show, &QPushButton::clicked, [&] () {

        if(imgPrc == nullptr) {

//            imgPrc = new ImgPrc(le_img_and_dir->text());
//            imgPrc->processImages(imgPrc->it_lst->toStdString());
//            vlay0->addWidget(paramBlcWdgt);
        } else {

            vlay0->addWidget(paramBlcWdgt);

            imgPrc->processImages(imgPrc->it_lst->toStdString());
        }
    } );

//    imgPrc->setChecBoxToShow(chb_prc_show->isTristate());

//    connect(chb_prc_show, &QCheckBox::clicked, imgPrc, &ImgPrc::setChecBoxToShow);

}


QString ParamBlock::strDefAndVal::getStrLoop(bool get_default)
{
    QString val;

    if(get_default) {
        if(++it == cont_str.end())
            it = cont_str.begin();

        val = it->first;
        return val;
    }


    if(++it == cont_str.end())
        it = cont_str.begin();

    val = it->second;
    return val;
}

void ParamBlock::strDefAndVal::setStr(QString str)
{
    it->second = str;
}

