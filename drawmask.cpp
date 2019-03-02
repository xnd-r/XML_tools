#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/core.hpp"
#include <tinyxml2.h>

void help()
{
    printf("\n\t\"drawmask help\"\n");
    printf("\n\t\"This tool draws masks for objects from .xml-file\"\n");
    printf("\n\tuse keys:\n");
    printf("\t-name sets a name of drawing object from xml (defolt value = None)\n");
    printf("\t-i sets a number of object from xml (defolt value = 0)\n");
    printf("\t-h view help\n");
    printf("\n");
    // TODO: REFACTOR
}

int main(int argc, char const *argv[])
{
    int test_flag = 0;
    int num = 0;
    int ki = -1;
    int kn = -1;
    char name[256];
    for(int i = 1; i < argc; i++)
    {
        if((!strcmp(argv[i], "-name")) && (i+1 < argc))
        {
            test_flag = 1;
            strncpy(name, argv[i+1], 256);
            kn = i;
        }
        
        if((!strcmp(argv[i], "-i")) && (i+1 < argc))
        {
            num = atoi(argv[i+1]);
            ki = i;
        }
        if(!strcmp(argv[i], "-h")) 
        {
            help();
            return 0;
        }
    }
    fprintf(stderr, "ArgParsing alive%d\n", test_flag);

    tinyxml2::XMLDocument doc;
    for(int iter_ind=1; iter_ind<argc; iter_ind++)
    {

        if(iter_ind==ki || iter_ind==ki+1 || iter_ind==kn+1 || iter_ind==kn) continue;
        printf("1st if alive %d\n", iter_ind);
        doc.LoadFile(argv[iter_ind]);
        int width  = doc.FirstChildElement("annotation")->FirstChildElement("size")->FirstChildElement("width")->IntText();
        int height = doc.FirstChildElement("annotation")->FirstChildElement("size")->FirstChildElement("height")->IntText();

        tinyxml2::XMLElement* e = doc.FirstChildElement("annotation")->FirstChildElement("object");

        if (test_flag)
        {
        	num = 0;
            //printf("strlen>0 %s %s\n", name, e->FirstChildElement("name")->GetText());
            while(e && (strcmp(e->FirstChildElement("name")->GetText(), name))){
                printf("sibling while alive \n");
                e = e->NextSiblingElement("object");
                num++;
            }
        }
        else
        {
            for(int j = 0; j < num; j++){
                if(!e){
                    printf("big index\n");
                    return 0;
                }
                e = e->NextSiblingElement("object");
            }
        }
        printf("check Alive\n");

        int xmin = e->FirstChildElement("bndbox")->FirstChildElement("xmin")->IntText();
        int ymin = e->FirstChildElement("bndbox")->FirstChildElement("ymin")->IntText();
        int xmax = e->FirstChildElement("bndbox")->FirstChildElement("xmax")->IntText();
        int ymax = e->FirstChildElement("bndbox")->FirstChildElement("ymax")->IntText();

        printf("parsexml Alive\n");

        char pbuff[256];
        int n = strlen(argv[iter_ind]);
        strncpy(pbuff, argv[iter_ind], n);
        pbuff[n-4] = 0;
        sprintf(pbuff, "%s_%d.png", pbuff, num);
                
        cv::Mat mask(height, width, 3, cv::Scalar(0,0,0));
        cv::RotatedRect R(cv::Point2f(xmin,ymin), cv::Point2f(xmax,ymin), cv::Point2f(xmax,ymax));
        cv::ellipse(mask, R, cv::Scalar(255,255,255), -1);

        cv::imwrite(pbuff, mask);
    }

    return 0;
}