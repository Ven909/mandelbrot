#include "ComplexPlane.h"

using namespace std;
using namespace sf;


ComplexPlane::ComplexPlane(float aspectRatio)
{
   m_aspectRatio = aspectRatio;
   m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio); //Might need as Vector2f?
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


}
size_t ComplexPlane::countIterations(Vector2f coord)
{


}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
  
}

