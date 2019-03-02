INCLUDE=-I./ -I/usr/local/include/ -L/usr/local/lib
LIB=-ltinyxml2 -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_calib3d -lopencv_video -lopencv_aruco

drawmask: drawmask.cpp 
	g++ -O3 drawmask.cpp -o drawmask $(INCLUDE) $(LIB) 

updatexml: updatexml.cpp 
	g++ -O3 updatexml.cpp -o updatexml $(INCLUDE) $(LIB)

setXML: setXML.cpp 
	g++ -O3 setXML.cpp -o setXML $(INCLUDE) $(LIB)

setXML_multiobj: setXML_multiobj.cpp 
	g++ -O3 setXML_multiobj.cpp -o setXML_multiobj $(INCLUDE) $(LIB)

create_xml: create_xml.cpp
	g++ -O3 create_xml.cpp -o create_xml $(INCLUDE) $(LIB)

