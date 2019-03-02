#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/core.hpp"
#include <tinyxml2.h>
#include <fstream>

char boxname[256] = "rice_in_water";

void help()
{
    printf("\n\t\"updatexml help\"\n");
    printf("\n\tuse keys:\n");
    printf("\t-i set first object namber (defolt value = 0)\n");
    printf("\t-h view help\n");
    printf("\n");
}

int main(int argc, char const *argv[])
{
	int num = 0;
	int k   = 0;

    for(int i = 1; i < argc; i++)
    {
        if((!strcmp(argv[i], "-i")) && (i+1 < argc))
        {
        	num = atoi(argv[i+1]);
        	k = i;
        }
        if(!strcmp(argv[i], "-h")) 
        {
            help();
            return 0;
        }
    }

	tinyxml2::XMLDocument doc;
	for(int ii=1; ii<argc; ii++)
	{
		if(ii==k || ii==k+1) continue;

		doc.LoadFile(argv[ii]);
		
		tinyxml2::XMLElement* e = doc.FirstChildElement("annotation");

		char name[256];
		int n = strlen(argv[ii]);
		strncpy(name, argv[ii], n);
        name[n-4] = 0;

        for(int i = num; i < 20; i++)
        {
	        char pbuff[256];
	        sprintf(pbuff, "%s_%d.png", name, i);

	        cv::Mat image = cv::imread(pbuff);
	        if(!image.data)
	        {
	        	printf("%s last mask: %d\n", argv[ii], i-1);
	        	break;
	        }

	        int xmin = image.cols;
	        int ymin = image.rows;
	        int xmax = 0;
	        int ymax = 0;

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

			        }
			    }
			}

			tinyxml2::XMLElement *obj = doc.NewElement("object");
			e->InsertEndChild(obj);
			tinyxml2::XMLElement *tmp;
			tmp = doc.NewElement("name");
			obj->InsertEndChild(tmp);
			tmp->SetText(boxname);
			tmp = doc.NewElement("pose");
			obj->InsertEndChild(tmp);
			tmp->SetText("Unspecified");
			tmp = doc.NewElement("truncated");
			obj->InsertEndChild(tmp);

			tmp->SetText(0);
			tmp = doc.NewElement("difficult");
			obj->InsertEndChild(tmp);
			tmp->SetText(0);

			tinyxml2::XMLElement *box = doc.NewElement("bndbox");
			obj->InsertEndChild(box);
			tmp = doc.NewElement("xmin");
			box->InsertEndChild(tmp);
			tmp->SetText(xmin);
			tmp = doc.NewElement("ymin");
			box->InsertEndChild(tmp);
			tmp->SetText(ymin);
			tmp = doc.NewElement("xmax");
			box->InsertEndChild(tmp);
			tmp->SetText(xmax);
			tmp = doc.NewElement("ymax");
			box->InsertEndChild(tmp);
			tmp->SetText(ymax);

			doc.SaveFile(argv[ii]);
	    }
	}

	return 0;
}