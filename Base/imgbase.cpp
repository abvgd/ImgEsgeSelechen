#include "imgbase.h"


Img::Img(std::string &patch, const std::string &win_name) :
    winame(win_name)
{
    frame = cv::imread(patch);
}

Img::Img(const cv::Mat &img, const std::string &win_name) :
    winame(win_name)
{
    frame = img.clone();
}


void Img::frameShow(bool show) const
{
    if(ips::switch_show = show = true /*!!! test !!!*/) {

        cv::namedWindow(winame);
        cv::imshow(winame, frame);
    } else {

        QCoreApplication::processEvents();
        cv::destroyWindow(winame);
    }
}

ImgBlur::ImgBlur(const cv::Mat &original, const std::string &win_name)
    : Img(std::move(cv::Mat()), win_name), inMat(original)
{
    blur(original);
}

ImgBlur::~ImgBlur()
{

}

void ImgBlur::blur(const cv::Mat &original)
{
    using namespace ips;
    cv::GaussianBlur(original, inMat, gb.ksize, gb.sigmaX, gb.sigmaY, gb.borderType);
}

bool ImgBlur::readBlurParam(QString str, bool restroy)
{
    using namespace ips;

    bool aloc = true;
    bool *fl = &aloc;

    QRegExp reg(QString("(?:ksize\\D+(\\d+))" ) +
                QString("(?:sigmaX\\D+(\\d+))") +
                QString("(?:sigmaY\\D+(\\d+))") +
                QString("(?:borderType\\D+(\\d{0,2}))")
                );

    reg.indexIn(str);

    gb.ksize = cv::Size(reg.cap(1).toInt(fl), reg.cap(1).toInt(fl));
    gb.sigmaX = reg.cap(2).toDouble(fl);
    gb.sigmaY = reg.cap(3).toDouble(fl);
    gb.borderType = reg.cap(4).toInt(fl);

    if(restroy) blur(inMat);

    return *fl;

}

void ImgBlur::fulChildShow()
{
    frameShow(true);
}

ImgLine::ImgLine(const cv::Mat &in_mat, const std::string &win_name)
    : Img(cv::Mat(), win_name), inMat(in_mat)
{
    canny(in_mat);

}

void ImgLine::canny(const cv::Mat &in_mat)
{
    using namespace ips;

    frame = in_mat.clone();
    cv::Mat matt = in_mat.clone();
    cv::Canny(frame, matt, cn.threshold1, cn.threshold2/*, cn.apertureSize, cn.L2gradient*/);
}

bool ImgLine::readCannyParam(QString &str, bool restroy)
{
    using namespace ips;

    bool aloc = true;
    bool *fl = &aloc;

    QRegExp reg(QString("(:?threshold1\\D+(\\d+))"  ) +
                QString("(:?threshold2\\D+(\\d+))"  ) +
                QString("(:?apertureSize\\D+(\\d+))") +
                QString(":?L2gardient\\W+(\\w))")
                );

    reg.indexIn(str);

    cn.threshold1 = reg.cap(1).toDouble(fl);
    cn.threshold2 = reg.cap(2).toDouble(fl);
    cn.apertureSize = reg.cap(3).toInt(fl);

    if(reg.cap(4) == "true" || reg.cap(4) == '1') {

        cn.L2gradient = true;
    } else if(reg.cap(4) == "fase" || reg.cap(4) == '0') {

        cn.L2gradient = false;
    } else {

        *fl = false;
    }

    if(restroy) canny(inMat);

    return *fl;
}

void ImgLine::fulChildShow()
{
    frameShow(true);
}


ImgBase::ImgBase()
{

}
