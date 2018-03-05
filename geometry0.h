#ifndef GEOMETRY0_H
#define GEOMETRY0_H

#include <opencv2/highgui.hpp>
#include <opencv2/core/opengl.hpp>

#include <vector>
#include <map>

#include <QDebug>


class Geometry0;
class VectorClaster;
class GeometryCalc;
class CirclObj;


// is class implement later as a generalization
class Geometry0
{
    VectorClaster* vecClst;
    GeometryCalc*  geoCalc;
    CirclObj*      circObj;

    cv::Mat geo_mat;

    std::map<int, std::vector<cv::Point>> geo_claster;

public:
    explicit Geometry0(cv::Mat& mat) : geo_mat(mat)
    {

    }
    explicit Geometry0();

    cv::Mat getGeo_mat() const;
};


// is class individual proces to select claster line
class VectorClaster : public QObject
{
protected:
    cv::Mat matrix;

    std::map<int, std::vector<cv::Point>> claster_map;

public:
    VectorClaster(cv::Mat& mat) : matrix(mat.clone())
    {

    }



    std::map<int, std::vector<cv::Point>> countClasterSel(cv::Mat inputMat = cv::Mat())
    {
        int dbg = 0;
        std::map<int, std::vector<cv::Point>>& map = claster_map;
        if(!map.empty())
            map.clear();
qDebug("cv::Mat2i = Mat begin");
        cv::Mat mat;
        if(inputMat.empty())
            mat = matrix.clone();
        else
            mat = inputMat.clone();
qDebug("cv::Mat2i = Mat end");
        int numerator = 0;

        for(int i = 0; i < mat.rows - 1; i++) {

            if(*mat.ptr(i, 0) == 255) {

                if(numerator == 255)
                    ++numerator;

                *mat.ptr(i, 0) = ++numerator;
            }

            if(*mat.ptr(i + 1, 0) == 255 && *mat.ptr(i, 0) > 0)
                *mat.ptr(i + 1, 0) = *mat.ptr(i, 0);

        } // pass to first line

        for(int i = 0; i < mat.rows - 1; i++) {
            for(int j = 0; j < mat.cols - 1; j++) {

                if(*mat.ptr(i, j) != 0 || *mat.ptr(i + 1, j) != 0) {

                    if(*mat.ptr(i, j) == 255 || *mat.ptr(i + 1, j) == 255) {

                        if(*mat.ptr(i, j) == 255) {
                            *mat.ptr(i, j) = ++numerator;
                            map[numerator].push_back(cv::Point(i, j));
                        } else if(*mat.ptr(i + 1, j) == 255) {
                            *mat.ptr(i + 1, j) = ++numerator;
                            map[numerator].push_back(cv::Point(i + 1, j));
                        }

                        if(*mat.ptr(i + 1, j) != 0) {
                            *mat.ptr(i + 1, j) = numerator;
                            map[numerator].push_back(cv::Point(i + 1, j));
                        }

                        if(*mat.ptr(i, j + 1) != 0) {
                            *mat.ptr(i, j + 1) = numerator;
                            map[numerator].push_back(cv::Point(i, j + 1));
                        }

                        if(*mat.ptr(i + 1, j + 1) != 0) {
                            *mat.ptr(i + 1, j + 1) = numerator;
                            map[numerator].push_back(cv::Point(i + 1, j + 1));
                        }

                        continue;
                    }


                    if(*mat.ptr(i, j) != 0 || *mat.ptr(i + 1, j) != 0) {

                        int val = 0;

                        if(*mat.ptr(i, j) != 0 && *mat.ptr(i + 1, j) != 0
                                && *mat.ptr(i, j) != *mat.ptr(i, j)) {

                            int select_num = *mat.ptr(i + 1, j);
qDebug("countClasterSel %d", ++dbg);
                            map[*mat.ptr(i, j)] =  conkaintVec(map[*mat.ptr(i, j)], map[select_num]);
                        }

                        if(*mat.ptr(i, j) != 0)
                            val = *mat.ptr(i, j);
                        else if(*mat.ptr(i +1, j) != 0)
                            val = *mat.ptr(i + 1, j);

                        if(*mat.ptr(i, j) != 0) {
                            *mat.ptr(i, j) = val;
                            map[val].push_back(cv::Point(i, j));
                        }

                        if(*mat.ptr(i + 1, j) != 0) {
                            *mat.ptr(i + 1, j) = val;
                            map[val].push_back(cv::Point(i + 1, j));
                        }

                        if(*mat.ptr(i, j + 1) != 0) {
                            *mat.ptr(i, j + 1) = val;
                            map[val].push_back(cv::Point(i, j + 1));
                        }

                        if(*mat.ptr(i + 1, j + 1) != 0) {
                            *mat.ptr(i + 1, j + 1) = val;
                            map[val].push_back(cv::Point(i + 1, j + 1));
                        }

                        continue;
                    }
                }
            }
        }


        return map;
    }


    // funct countClasterSel new variant
    std::map<int, std::vector<cv::Point>> vectorClasterSel(const cv::Mat& mat/*, int min_gap = 0*/)
    {
        std::map<int, std::vector<cv::Point>> result;

        std::vector<cv::Point> vec;

        /*unsigned char* data = mat.data;*/

        int count = 0;
        for(int i = 0; i < mat.rows; i++) {
            for(int j = 0; j < mat.cols; j++) {
                if(*mat.ptr(i, j))
                    ++count;
            }
        }

        vec.reserve(count);

        //rekurseLineSel(vec, mat);

        return result;
    }

    void rekurseLineSel(std::vector<std::pair<int, cv::Point>>& cont,
                        cv::Mat& mat, int numerator = 0)
    {
        unsigned char mask[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
        for(int i = 0; i < mat.rows; i++) {
            for(int j = 0; j < mat.cols; j++) {
                if(*mat.ptr(i, j))
                    ;//!relise
            }
        }
    }


    std::vector<cv::Point> conkaintVec(std::vector<cv::Point>& hed,
                                             std::vector<cv::Point>& tail)
    {
        std::vector<cv::Point> result;
        result.reserve(hed.size() + tail.size());

        for(cv::Point poi : hed)
            result.push_back(poi);

        std::vector<cv::Point>::iterator rit = tail.end();
        while(--rit > tail.begin() - 1) {
            result.push_back(*rit);
        }

        return result;
    }


    cv::Mat writeClasterColor(cv::Mat& mat_fon, size_t min_vec_lng = 100)
    {

        qDebug("writeClasterColor channeles: %d", mat_fon.channels());
        cv::Mat mat = mat_fon.clone(); // rezult

        qDebug("writeClasterColor channeles: %d", mat.channels());

        int max = 0;

        for(std::pair<const int, std::vector<cv::Point>>& par : claster_map) {
            if(max < par.first)
                max = par.first;
        }

//        const int factor = INT_MAX / 3 / max;
//        const int surplus = INT_MAX / 3;

//        mat CV_RGB(0, 0, 0);

//        for(uchar* ch = mat.data; ch != mat.dataend - 3; ch++) {
//            *ch = 255; *(ch + 1) = 255; *(ch + 2) = 255;
//        }



        for(std::pair<const int, std::vector<cv::Point>> par : claster_map) {

            for(cv::Point poi : par.second) {
                *mat.ptr(poi.x, poi.y) = 0;
            }

            if(par.second.size() < min_vec_lng)
                continue;

            for(cv::Point poi : par.second) {
                *mat.ptr(poi.x, poi.y) = 255;//(int)par.first * factor + surplus;
            }
        }

        return mat;
    }

};


// is class geometry calc :)
class GeometryCalc : private VectorClaster
{
    std::vector<std::vector<cv::Point>> integral_mass;

    cv::Mat2i parent_mat_line;

public:

    GeometryCalc(cv::Mat& line_mat) : VectorClaster(line_mat)
    {
       std::size_t siz = claster_map.size();
       qDebug() << siz;
    }

    std::vector<std::vector<cv::Point>>& integralMass(std::vector<cv::Point>& vec,
                                                      size_t integral_limit = 4,int count = 0)
    {
        if(vec.size() < integral_limit)
            return integral_mass;

        for(size_t i = 0; i < vec.size(); i += integral_limit){

            vec.reserve(vec.size() / integral_limit);
            integral_mass.push_back(vec);
            integral_mass[count].push_back( centralMass( std::vector<cv::Point>::iterator(&vec[i]),
                                         std::vector<cv::Point>::iterator(&vec[i + integral_limit]) ) );

        }

        integralMass(integral_mass[count], integral_limit, ++count);
    }

    cv::Point centralMass(std::vector<cv::Point>::iterator begin, std::vector<cv::Point>::iterator end)
    {
        cv::Point mass_point;
        size_t distance = end - begin;

        for( ; begin < end; begin++) {
            mass_point.x += begin->x;
            mass_point.y += begin->y;
        }

        mass_point.x /= distance;
        mass_point.y /= distance;

        return mass_point;
    }

};


//is class accepts only valid circl
class CirclObj
{
    std::vector<cv::Point> circl_v;

    cv::Mat& context;

    double area;

public:
    CirclObj(std::vector<cv::Point> vec, cv::Mat& heder_mat) : circl_v(vec), context(heder_mat)
    {

    }

    bool isCircValid(std::vector<cv::Point> vec)
    {
        std::vector<cv::Point>::iterator it = vec.begin();
        while(++it < vec.end()) {

            if(it == vec.end() - 1) {
                if(it->x == vec.begin()->x) {
                    if(it->y != vec.begin()->y + 1 || it->y != vec.begin()->y - 1)
                        return false;
                    else
                        continue;
                } else if(it->y == vec.begin()->y) {
                    if(it->x != vec.begin()->x + 1 || it->x != vec.begin()->x - 1)
                        return false;
                    else
                        continue;
                }
            }

            if(it->x == (it + 1)->x) {
                if(it->y != (it + 1)->y + 1 || it->y != (it + 1)->y - 1)
                    return false;
                else
                    continue;
            } else if(it->y == (it + 1)->y) {
                if(it->x != (it + 1)->x + 1 || it->x != (it + 1)->x - 1)
                    return false;
                else
                    continue;
            }

            return false;
        }

        return true;
    }

};

#endif // GEOMETRY0_H
