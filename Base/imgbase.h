#ifndef IMGBASE_H
#define IMGBASE_H

#include "imgdata.h"

#include <QString>
#include <QCoreApplication>
#include <QDebug>

#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>


namespace ips {

static const std::string win_frame   = "frame";
static const std::string win_gausian = "gausian blur";
static const std::string win_canny   = "canny";
static const std::string win_claster = "claster show";

static bool switch_show = false;

static struct /*gb_struct*/{

    cv::Size ksize{3, 3};
    double sigmaX = 3; double sigmaY = 0;
    int borderType = 4;
    cv::BorderTypes getBorder()
    {
        if((borderType < 0 || 5 < borderType || borderType != 16) && borderType != 16)
            return cv::BORDER_DEFAULT;

        return static_cast<cv::BorderTypes>(borderType);
    }
}gb;

static struct {

    double threshold1 = 3;double threshold2 = 3;
    int apertureSize = 3; bool L2gradient = false;
}cn;

} // END NAMESPACE ips


class Img
{
protected:


    std::string winame;

public:
    explicit Img(std::string& patch, const std::string& win_name = ips::win_frame);

    explicit Img(const cv::Mat& img, const std::string& win_name = ips::win_frame);

    Img() {}

    void frameShow(bool show = ips::switch_show) const;

    virtual void fulChildShow() { frameShow();}

    cv::Mat frame;

};

class ImgBlur : public Img
{
    //using namespace ips;

    const cv::Mat& inMat;

public:
    explicit ImgBlur(const cv::Mat& original, const std::string& win_name = ips::win_gausian);
    ~ImgBlur();

    void blur(const cv::Mat& original);

    bool readBlurParam(QString str, bool restroy = false);

    virtual void fulChildShow();

};

class ImgLine : public Img
{
    const cv::Mat& inMat;

public:
    explicit ImgLine(const cv::Mat& in_mat, const std::string& win_name = ips::win_canny);

    void canny(const cv::Mat& in_mat);

    bool readCannyParam(QString& str, bool restroy = false);

    virtual void fulChildShow();

};


class ImgBase
{

public:
    ImgBase();
};


#endif // IMGBASE_H
