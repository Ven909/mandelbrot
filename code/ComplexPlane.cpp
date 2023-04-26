//made by Venkata G. Ande and Aws Khaleel

#include "ComplexPlane.h"

using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(float aspectRatio)
{
   m_aspectRatio = aspectRatio;  //set the aspectRatio into m_aspectRatio
   m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);  //using global variable to define the size
   m_view.setCenter(0.0, 0.0);   //set center at 0, 0
   m_zoomCount = 0;              //set zoom count to 0
}
View ComplexPlane::getView()
{
   return m_view;      //getter method to get the view
}
void ComplexPlane::zoomIn()
{
   m_zoomCount++;
   float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));      //using zoom in formula for the x dimension
   float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));   //using zoom in formula for the y dimension
   m_view.setSize(x_size, y_size);   //set the now zoomed in dimensions

}
void ComplexPlane::zoomOut()
{
   m_zoomCount--;
   float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));     //using zoom out formula for the x dimension
   float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));    //using zoom out formula for the y dimension
   m_view.setSize(x_size, y_size);    //set the now zoomed out dimensions

}
void ComplexPlane::setCenter(Vector2f coord)
{
   m_view.setCenter(coord);			//set the center at the given coordinate
}
void ComplexPlane::setMouseLocation(Vector2f coord)
{
   m_mouseLocation = coord;			//store the given coordinate in m_mouseLocation
}
void ComplexPlane::loadText(Text& text)
{
   stringstream out;

	out << "Mandelbrot Set\n";  //print tittle of game
   out << "Center:(" << m_view.getCenter().x << "," << m_view.getCenter().y << ")" << endl;  //print the center
   out << "Cursor:(" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;        //print the mouse location
   out << "Left-click to Zoom in" << endl;     //instructions for user on how to use program
   out << "Right-click to Zoom out" << endl;
   // Set the text string of the Text object to the stringstream contents
   text.setString(out.str());

   text.setCharacterSize(22);       //setting text size
   text.setFillColor(Color::White); //setting text color
   text.setPosition(50,50);         //setting text position
}
size_t ComplexPlane::countIterations(Vector2f coord)
{
   complex<double> c(coord.x, coord.y);  //turn pixel's coord into a compex number
   //initialize to 0
   complex<double> z(0,0);
   size_t count = 0;

   //do it until max iterations or z surpasses the radius 2
   while(abs(z) < 2 && count < MAX_ITER)
   {  
      z = z*z + c;
      count++;
   }
   return count;

}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
   //creating a color scheme
   //simple color scheme
   if(count == MAX_ITER)	//At MAX_ITER color the pixel black
  {
    r = 0;
    g = 0;
    b = 0;
  }
  else if(count < 10)		//purple
  {
    r = 127;
    g = 0;
    b = 255;
  }
  else if(count < 20)		//just green
  {
    r = 0;
    g = 255;
    b = 0;
  }
  else if(count < 30)		//just blue
  {   
    r = 0;
    g = 0;
    b = 255;
  }
  else if(count < 40)		//yellow
  {
    r = 255;
    g = 255;
    b = 0;
  }
  else if(count < 50)		//fully red
  {
    r = 255;
    g = 0;
    b = 0;
  }

  
}

