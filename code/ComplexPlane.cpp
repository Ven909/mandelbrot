//made by Venkata G. Ande and Aws Khaleel

#include "ComplexPlane.h"

using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(float aspectRatio)
{
   m_aspectRatio = aspectRatio;
   m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio); 
   m_view.setCenter(0.0, 0.0);
   m_zoomCount = 0;
}
View ComplexPlane::getView()
{
   return m_view;
}
void ComplexPlane::zoomIn()
{
   m_zoomCount++;
   float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
   float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
   m_view.setSize(x_size, y_size);

}
void ComplexPlane::zoomOut()
{
   m_zoomCount--;
   float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
   float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
   m_view.setSize(x_size, y_size);

}
void ComplexPlane::setCenter(Vector2f coord)
{
   m_view.setCenter(coord);
}
void ComplexPlane::setMouseLocation(Vector2f coord)
{
   m_mouseLocation = coord;
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

   //do it until max iterations z surpasses the radius 2
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
   if(count == MAX_ITER)
  {
    r = 0;
    g = 0;
    b = 0;
  }
  else if(count < 10)
  {
    r = 127;
    g = 0;
    b = 255;
  }
  else if(count < 20)
  {
    r = 0;
    g = 255;
    b = 0;
  }
  else if(count < 30)
  {   
    r = 0;
    g = 0;
    b = 255;
  }
  else if(count < 40)
  {
    r = 255;
    g = 255;
    b = 0;
  }
  else if(count < 50)
  {
    r = 255;
    g = 0;
    b = 0;
  }

  
}

