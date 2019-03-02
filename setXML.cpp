#include <tinyxml2.h>
#include <fstream>

int main(int argc, char const *argv[])
{
	tinyxml2::XMLDocument doc;
	std::ifstream file;
	file.open("coordinates");

	int data[500][2];
	int tmp;
	int n = 0;

	while (file >> tmp) {
        data[n][0] = tmp;
        file >> tmp;
        data[n][1] = tmp;
        n++;
    }

	for(int i=1; i<argc; i++)
	{
		doc.LoadFile(argv[i]);

		char name[256];
    	strncpy(name, argv[i], 256);
		char* p = strrchr(name, '.');
		*p = 0;
		int j = atoi(name);

		printf("%s %d %d\n", name, data[j][0], data[j][1]);

		if(data[j][0] == 0)
		{
			continue;
		}

		tinyxml2::XMLElement* e = doc.FirstChildElement("annotation")->FirstChildElement("object")->FirstChildElement("pose3D");

		tinyxml2::XMLElement* x = e->FirstChildElement("x");
        tinyxml2::XMLElement* y = e->FirstChildElement("y");

		char pbuff[256];

		sprintf(pbuff, "%d", data[j][0]);
		if(x) x->SetText(pbuff);

		sprintf(pbuff, "%d", data[j][1]);
        if(y) y->SetText(pbuff);

		doc.SaveFile(argv[i]);
		
	}

	file.close();
	return 0;
}