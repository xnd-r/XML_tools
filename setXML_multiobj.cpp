#include <tinyxml2.h>
#include <fstream>

int main(int argc, char const *argv[])
{
    tinyxml2::XMLDocument doc;

    int y1, y2, y3;

    double data[50][2];
    data[0][0] = 11   ;
    data[1][0] = 14.5 ;
    data[2][0] = 18   ;
    data[3][0] = 21   ;
    data[4][0] = 23.5 ;
    data[5][0] = 26   ;
    data[6][0] = 29   ;
    data[7][0] = 32.5 ;
    data[8][0] = 36   ;

    data[9][0]  = 11   ;
    data[10][0] = 14.5 ;
    data[11][0] = 18   ;
    data[12][0] = 21   ;
    data[13][0] = 23.5 ;
    data[14][0] = 26.5 ;
    data[15][0] = 29.5 ;
    data[16][0] = 32   ;
    data[17][0] = 34.5 ;
    data[18][0] = 37   ;

    data[19][0] = 20 ;
    data[20][0] = 25 ;
    data[21][0] = 30 ;

    for(int ii=1; ii<argc; ii++)
    {
        doc.LoadFile(argv[ii]);

        char name[256];
        strncpy(name, argv[ii], 256);
        char* p = strrchr(name, '.');
        *p = 0;

        char pN[256];
        p = strrchr(name, '_');
        strncpy(pN, p+1, 256);
        y3 = atoi(pN);
        *p = 0;
        p = strrchr(name, '_');
        strncpy(pN, p+1, 256);
        y2= atoi(pN);
        *p = 0;
        p = strrchr(name, '_');
        strncpy(pN, p+1, 256);
        y1 = atoi(pN);
        *p = 0;

        data[0][1] = y2 + 1.5;
        data[1][1] = y2 + 1.5;
        data[2][1] = y2 + 1.5;
        data[3][1] = y2 + 1;
        data[4][1] = y2 + 1;
        data[5][1] = y2 + 1;
        data[6][1] = y2 + 1.5;
        data[7][1] = y2 + 1.5;
        data[8][1] = y2 + 1.5;

        data[9][1]  = y1 + 1.5;
        data[10][1] = y1 + 1.5;
        data[11][1] = y1 + 1.5;
        data[12][1] = y1 + 1;
        data[13][1] = y1 + 1;
        data[14][1] = y1 + 1.5;
        data[15][1] = y1 + 1;
        data[16][1] = y1 + 1;
        data[17][1] = y1 + 1;
        data[18][1] = y1 + 1;

        data[19][1] = y3 + 1;
        data[20][1] = y3 + 1;
        data[21][1] = y3 + 1;

        tinyxml2::XMLElement* e = doc.FirstChildElement("annotation")->FirstChildElement("object");
/*

        <pose3D>
            <x>240</x>
            <y>210</y>
            <z>0.00</z>
            <r1>0.00</r1>
            <r2>0.00</r2>
            <r3>0.00</r3>
        </pose3D>
*/
        for(int i = 0; i < 22; i++)
        {
            tinyxml2::XMLElement *obj = doc.NewElement("pose3D");
            e->InsertEndChild(obj);
            tinyxml2::XMLElement *tmp;
            tmp = doc.NewElement("x");
            obj->InsertEndChild(tmp);
            tmp->SetText(data[i][0]);
            tmp = doc.NewElement("y");
            obj->InsertEndChild(tmp);
            tmp->SetText( data[i][1]);
            tmp = doc.NewElement("z");
            obj->InsertEndChild(tmp);
            tmp->SetText(0);
            tmp = doc.NewElement("r1");
            obj->InsertEndChild(tmp);
            tmp->SetText(0);
            tmp = doc.NewElement("r2");
            obj->InsertEndChild(tmp);
            tmp->SetText(0);
            tmp = doc.NewElement("r3");
            obj->InsertEndChild(tmp);
            tmp->SetText(0);

            e = e->NextSiblingElement("object");
        }
        doc.SaveFile(argv[ii]);
        
    }

    return 0;
}