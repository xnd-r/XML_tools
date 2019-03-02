#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/core.hpp"
#include <tinyxml2.h>

using namespace tinyxml2;

int main(int argc, char const *argv[])
{
    int threshold = 6;
    char _path[256] = "marker_on_fpan";
    char obj_1[256] = "fpan";
    char obj_2[256] = "fpanh";
    char obj_3[256] = "steak";

    char name[256];     // base name     // 012
    char img_name[256]; // name of image // 012.png
    char name_xml[256]; // name of xml   // 012.xml
    
    for(int obj_i=1; obj_i<argc; ++obj_i)
    {
        strncpy(img_name, argv[obj_i], 256); 
        int n = strlen(img_name);
        strncpy(name, img_name, n);
        name[n-4] = 0;
        sprintf(name_xml, "%s.xml", name);

        XMLDocument xmlDoc;
        XMLElement * pRoot = xmlDoc.NewElement("annotation");
        xmlDoc.InsertFirstChild(pRoot);

        // <folder>whitemarker.rs.train</folder>
        XMLElement * tmp_1, * tmp_2, * tmp_3;
        tmp_1 = xmlDoc.NewElement("folder");
        pRoot->InsertFirstChild(tmp_1);
        tmp_1->SetText(_path);

        // <filename>001.png</filename>
        tmp_1 = xmlDoc.NewElement("filename");
        pRoot->InsertEndChild(tmp_1);
        tmp_1->SetText(img_name);

        // <path>/home/egor/whitemarker.rs.train/001.png</path>
        tmp_1 = xmlDoc.NewElement("path");
        pRoot->InsertEndChild(tmp_1);
        tmp_1->SetText(_path);

        //  <source><database>Unknown</database>    </source>
        tmp_1 = xmlDoc.NewElement("source");
        pRoot->InsertEndChild(tmp_1);   
        tmp_2 = xmlDoc.NewElement("database");
        tmp_1->InsertFirstChild(tmp_2);
        tmp_2->SetText("Unknown");

        // <size>
        cv::Mat image = cv::imread(argv[1]);
        int width = image.cols, height = image.rows;
        tmp_1 = xmlDoc.NewElement("size");
        pRoot->InsertEndChild(tmp_1);
        tmp_2 = xmlDoc.NewElement("width");
        tmp_1->InsertFirstChild(tmp_2);
        tmp_2->SetText(width);
        tmp_2 = xmlDoc.NewElement("height");
        tmp_1->InsertEndChild(tmp_2);
        tmp_2->SetText(height); 
        tmp_2 = xmlDoc.NewElement("depth");
        tmp_1->InsertEndChild(tmp_2);
        tmp_2->SetText(3);

        // <segmented>0</segmented>
        tmp_1 = xmlDoc.NewElement("segmented");
        pRoot->InsertEndChild(tmp_1);
        tmp_1->SetText(0);  


        /* <object> */
        char mask_name[256];
        for(int i = 0; i < 20; i++)
        {
            sprintf(mask_name, "%s_%d.png", name, i);

            cv::Mat image = cv::imread(mask_name);
            if(!image.data)
            {
                printf("%s last mask: %d\n", argv[obj_i], i-1);
                break;
            }

            int xmin = image.cols;
            int ymin = image.rows;
            int xmax = 0;
            int ymax = 0;
            int white_bit_count = 0;

            for(int r = 0; r < image.rows; r++)
            {
                for(int c = 0; c < image.cols; c++)
                {
                    cv::Vec3b bgrPixel = image.at<cv::Vec3b>(cv::Point(c, r));
                    if(bgrPixel[0] > 50)
                    {
                        if(r < ymin) ymin = r;
                        if(r > ymax) ymax = r;
                        if(c < xmin) xmin = c;
                        if(c > xmax) xmax = c;
                        white_bit_count++;
                    }
                }
            }

            tmp_1 = xmlDoc.NewElement("object");
            pRoot->InsertEndChild(tmp_1);
            tmp_2 = xmlDoc.NewElement("name");
            tmp_1->InsertEndChild(tmp_2);
            tmp_2->SetText(white_bit_count<threshold?obj_1: (white_bit_count==threshold ? obj_2:obj_3));

            tmp_2 = xmlDoc.NewElement("pose");
            tmp_1->InsertEndChild(tmp_2);
            tmp_2->SetText("Unspecified");
            tmp_2 = xmlDoc.NewElement("truncated");
            tmp_1->InsertEndChild(tmp_2);
            tmp_2->SetText(0);
            tmp_2 = xmlDoc.NewElement("difficult");
            tmp_1->InsertEndChild(tmp_2);
            tmp_2->SetText(0);

            tmp_2 = xmlDoc.NewElement("bndbox");
            tmp_1->InsertEndChild(tmp_2);
            tmp_3 = xmlDoc.NewElement("xmin");
            tmp_2->InsertEndChild(tmp_3);
            tmp_3->SetText(xmin);
            tmp_3 = xmlDoc.NewElement("ymin");
            tmp_2->InsertEndChild(tmp_3);
            tmp_3->SetText(ymin);
            tmp_3 = xmlDoc.NewElement("xmax");
            tmp_2->InsertEndChild(tmp_3);
            tmp_3->SetText(xmax);
            tmp_3 = xmlDoc.NewElement("ymax");
            tmp_2->InsertEndChild(tmp_3);
            tmp_3->SetText(ymax);
        }

        XMLError eResult = xmlDoc.SaveFile(name_xml);
    }
    return 0;
}
