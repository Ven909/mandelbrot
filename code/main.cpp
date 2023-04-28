//made by Venkata G. Ande and Aws Khaleel

#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;


int main()
{
   Event event;
   //set size of window	with respect to the computer widthe and height
   float width = VideoMode::getDesktopMode().width;
   float height = VideoMode::getDesktopMode().height;
   
   VideoMode vm(width, width);  //set the size
   // Construct the window
    RenderWindow window(VideoMode(width, height), "Mandelbrot Set");

   ComplexPlane plane(height /width);  //so that it doesn't get distorted

   //making font and text objects
   Font font;
   font.loadFromFile("fonts/KOMIKAP_.ttf");

   Text message;
   message.setFont(font);
   message.setCharacterSize(24);
   message.setPosition(10, 10);

   //construct vertex array to draw a color for each pixel
   VertexArray vArray(Points, height * width);

   enum State{CALCULATING, DISPLAYING};

   // initialize the state to  CALCULATING
   State state = CALCULATING;

   while(window.isOpen())  //Handle Input segment 
   {
      while (window.pollEvent(event))
      {
         if ((event.type == Event::Closed)  || (Keyboard::isKeyPressed(Keyboard::Escape)))
         {
            window.close();
         }
         //if the user presses mouse.....
         if(event.type == Event::MouseButtonPressed)
         {
            Vector2f pos = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
            //if user clicks right mouse button zoom out
            if (event.mouseButton.button == Mouse::Right) 
            {
               plane.zoomOut();
               plane.setCenter(pos);  //find the position
               state = State::CALCULATING;     //generate the new complex plane view
            } 
            //else if the user clicks left mosue button zoom in
            else if (event.mouseButton.button == Mouse::Left) 
            {
               plane.zoomIn();
               plane.setCenter(pos);
               state = State::CALCULATING;
            }
         }
         //when the mosue moves....
         if (event.type == Event::MouseMoved) 
         {
            //find the Vector2f coordinates in the ComplexPlane view that corresponds to the mouse location
            Vector2f pos = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());

            //setMouseLocation on the ComplexPlane object to store this coordination
            plane.setMouseLocation(pos);
         } 
      }
      if (state == State::CALCULATING) 
      {
         for (auto i = 0; i < height; i++) 
         {
            for (auto j = 0; j < width; j++) 
            {
               // Set the position of the vertex to the pixel coordinates
               vArray[j + i * width].position = { (float)j,(float)i };

               // find the coordinate in the ComplexPlane View that corresponds to the screen pixel location at j,i
               Vector2f coord = window.mapPixelToCoords({j, i}, plane.getView());

               // get and store the number of iterations
               int iterations = plane.countIterations(coord);

               // store the RGB values for the current pixel 
               Uint8 r, g, b;
               //Pass the number of iterations and the RGB variables into iterationsToRGB()
               plane.iterationsToRGB(iterations, r, g, b);

               // set the vertex color to the corrsponding rgb color
               vArray[j + i * width].color = {r, g, b};
            }
         }
         // set the state to DISPLAYING
         state = State::DISPLAYING;
      }

      // Update the text on the screen
      plane.loadText(message);
      //draw everything
      window.clear();
      window.draw(vArray);
      window.draw(message);
      window.display();
   
   }
}

