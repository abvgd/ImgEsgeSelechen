#ifndef IMGPRC_H
#define IMGPRC_H

#include "geometry0.h"
#include "base/imgbase.h"

#include <QObject>
#include <QFile>
#include <QDir>
#include <QList>
#include <QChar>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <string>



class ImgPrc : public QObject
{
    cv::Mat frame;
    Geometry0* geo0;
    QDir outdir, indir;

    QFile* fil;

    bool start = false;
    bool visualise_prc = false;

    int interval;

    std::vector<cv::Point> maskStep(cv::Point p, cv::Mat& mat);


public:

    Img*     origImg;
    ImgBlur* imgBlur;
    ImgLine* imgLine;

    ImgPrc(const QString read_dir, QString write_dir = QString("/input"));


    void processImages(std::string fistFrameFilename, bool show2 = false);

//    void setChecBoxToShow(bool checbox)
//    {
//        if(frame_blur.empty() || frame_line.empty())
//            return;

//        frame_blur_show = checbox;
//        frame_line_show = checbox;

//        if(checbox) {
//            QCoreApplication::processEvents();
//            cv::imshow(win_gausian, frame_blur);
//            cv::imshow(win_canny, frame_line);
//        } else {
//            QCoreApplication::processEvents();
//            cv::destroyWindow(win_gausian);
//            cv::destroyWindow(win_claster);
//        }
//    }

    void shouTwoImg(bool show2 = false);
    bool frameShow(bool show = true);
    bool blurShow(bool show = true);
    bool cannyShow(bool show = true);
    bool clasterShow(cv::Mat mat, bool show = true);
    void loopBlur(cv::Mat& val_blur, unsigned int qani_it = 1);

    void lngLineSrch(cv::Mat& frm_line, cv::Point point = cv::Point(1, 1), int min_lng_line = 100);

    bool circlDetect(std::vector<cv::Point>& vec);

    int  getInterval() const;
    void setInterval(int value);

    // Data
    QStringList f_lst;
    QList<QString>::iterator it_lst;

    // Data claster
    cv::Mat original_and_claster; bool orig_and_clast_show;


};



#endif // IMGPRC_H
