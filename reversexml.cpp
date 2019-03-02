#include <tinyxml2.h>

int main(int argc, char const *argv[])
{
	tinyxml2::XMLDocument doc;
	for(int i=1; i<argc; i++)
	{
		doc.LoadFile(argv[i]);
		tinyxml2::XMLElement* e = doc.FirstChildElement("annotation");
		int width = e->FirstChildElement("size")->FirstChildElement("width")->IntText();

		e = e->FirstChildElement("object");

		tinyxml2::XMLElement* min = e->FirstChildElement("bndbox")->FirstChildElement("xmin");
        tinyxml2::XMLElement* max = e->FirstChildElement("bndbox")->FirstChildElement("xmax");

		int xmin = min->IntText();
		int xmax = max->IntText();

		int tmpmin = xmin;
		xmin = width - xmax;
		xmax = width - tmpmin;

		char pbuff[256];
		sprintf(pbuff, "%d", xmin);
		if(min) min->SetText(pbuff);

		sprintf(pbuff, "%d", xmax);
        if(max) max->SetText(pbuff);


        e=e->NextSiblingElement("object");

        min = e->FirstChildElement("bndbox")->FirstChildElement("xmin");
        max = e->FirstChildElement("bndbox")->FirstChildElement("xmax");

		xmin = min->IntText();
		xmax = max->IntText();

		tmpmin = xmin;
		xmin = width - xmax;
		xmax = width - tmpmin;

		sprintf(pbuff, "%d", xmin);
		if(min) min->SetText(pbuff);

		sprintf(pbuff, "%d", xmax);
        if(max) max->SetText(pbuff);

		doc.SaveFile(argv[i]);
		
	}

	return 0;
}