#include "imgprc.h"

ImgPrc::ImgPrc(const QString read_dir, QString write_dir)
    : outdir(read_dir), indir(QString(read_dir + write_dir)),
      interval(1000)
{

    QRegExp reg("*.jpg");
    reg.setPatternSyntax(QRegExp::Wildcard);
    for(QString str : outdir.entryList()) {

        if(reg.exactMatch(str))
            f_lst.push_back(outdir.absolutePath() + "/" + str);
    }
    if(f_lst.isEmpty()) {
        qErrnoWarning("is dir not containt img");
    } else {

        it_lst = f_lst.begin();
    }

    std::string fistFrameFilename = it_lst->toStdString();
    origImg = new Img(fistFrameFilename);

    if(origImg->frame.empty()) {
        //error in opening the image
        std::cerr << "Unable to open first image frame: " << fistFrameFilename << std::endl;
        exit(EXIT_FAILURE);
    }

    frameShow();

    imgBlur = new ImgBlur(origImg->frame);
    blurShow();

    imgLine = new ImgLine(origImg->frame);
    cannyShow();

    //processImages(it_lst->toStdString());
}

std::vector<cv::Point> ImgPrc::maskStep(cv::Point p, cv::Mat &mat)
{

    std::vector<cv::Point> vec;

    int i = p.x - 1, j = p.y - 1;

    for( ; i < p.x + 2; i++)
        for( ; j < p.y + 2; j++) {
            if(*mat.ptr(i, j) == 255) {
                *mat.ptr(i, j) = 127;
                p = cv::Point(i, j);
                vec.push_back(p);
            }
        }
    return vec;

}

void ImgPrc::processImages(std::string fistFrameFilename, bool show2)
{
    origImg = new Img(fistFrameFilename);

    if(origImg->frame.empty()) {
        //error in opening the image
        std::cerr << "Unable to open first image frame: " << fistFrameFilename << std::endl;
        exit(EXIT_FAILURE);
    }

    frameShow();

    imgBlur = new ImgBlur(origImg->frame);
    blurShow();

    imgLine = new ImgLine(origImg->frame);
    cannyShow();

}

void ImgPrc::shouTwoImg(bool show2)
{
    origImg->fulChildShow();
}

bool ImgPrc::frameShow(bool show)
{
    if(frame.empty() || !show)
        return false;

    origImg->frameShow();

    return true;

}

bool ImgPrc::blurShow(bool show)
{
    if(imgBlur->frame.empty() || !show)
        return false;

    imgBlur->frameShow();

    return true;
}

bool ImgPrc::cannyShow(bool show)
{
    if(imgLine->frame.empty() || !show)
        return false;

    imgLine->frameShow();

    return true;
}

bool ImgPrc::clasterShow(cv::Mat mat, bool show)
{
    if(mat.empty() || !show)
        return false;

    cv::namedWindow(ips::win_claster);
    cv::imshow(ips::win_claster, mat);

    return true;
}

void ImgPrc::loopBlur(cv::Mat &val_blur, unsigned int qani_it)
{
    while(qani_it) {

        imgBlur->frameShow(true);
        --qani_it;
    }
}

void ImgPrc::lngLineSrch(cv::Mat &frm_line, cv::Point point, int min_lng_line)
{
    cv::Mat mat(frm_line);

    std::vector<cv::Point> val_vec;
    std::vector<std::vector<cv::Point>> claster_line;
    int line_qani = 0, lng_line = 0;

    for(int i = point.x; i <= mat.rows - 1; i++) {
        for(int j = point.y; j <= mat.cols - 1; j++) {
            if(*mat.ptr(i, j) == 255) {
                val_vec = maskStep(cv::Point(i, j), mat);

                if(val_vec.empty()) {
                    if(lng_line < min_lng_line)
                        claster_line[line_qani].clear();

                    lng_line = 0;
                    continue;
                } else {
                    lng_line += 1;
                }

                for(cv::Point p : val_vec)
                    claster_line[line_qani].push_back(p);
            }
        }
    }
}

bool ImgPrc::circlDetect(std::vector<cv::Point> &vec)
{
    //int count{};
    //double angl_x{}, angl_y{};
    std::vector<cv::Point> calk_vec(vec.size());
    std::vector<cv::Point>::iterator it = vec.begin();

    //int min_x{}, min_y{};

    //std::pair<bool, cv::Point> par = centrMass(vec);

    for( ; it < vec.end(); it++) {
        calk_vec.push_back(cv::Point(it->x - vec.begin()->x, it->y - vec.begin()->y));
    }

    //        int deam = calk_vec.size() / 3.1485;
    //        int deam10[10];
    //        for(int i = 0, count = 0; count < calk_vec.size(); count += calk_vec.size() / 10, i++) {
    //            deam10[i] = calk_vec[count] - calk_vec[calk_vec.size() / 2 + count];
    //            if(deam10[i] < deam - deam / 5 || deam + deam / 5 < deam10[i])//deam < 20%
    //                return false;
    //        }
    return true;

}

int ImgPrc::getInterval() const
{
    return interval;
}

void ImgPrc::setInterval(int value)
{
    interval = value;
}



