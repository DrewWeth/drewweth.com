
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#include "SFML/Network.hpp"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>

using namespace std;

int main(int, char const**)
{
    sf::TcpSocket socket;
    sf::IpAddress ip;
    ip = ip.LocalHost;
    unsigned short port = 3000;
    int window_x = 1200;
    int window_y = 600;
    
    sf::Socket::Status status = socket.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        std::cout << "Connection Error!\n";
    }
    else
    {
        std::cout << "Connected!\n";
    }
    
    
    string brand = "Empire's Edge";
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), brand);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    
    if (!texture.loadFromFile(resourcePath() + "joyous.jpg")) {
        cout << "Cannot load background img";
    }
    texture.setRepeated(true);
    texture.setSmooth(true);
    
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text(brand, font, 50);
    text.setColor(sf::Color::Black);

    sf::Text text2("Press space to start", font, 50);
    text2.setColor(sf::Color::Red);
    sf::Vector2u size = window.getSize();
    text2.setPosition(size.x / 2, size.y / 2);

    sf::Text text3("a", font, 28);
    text3.setColor(sf::Color::Blue);
    text3.setPosition(size.x - 300, size.y - 100);

    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    //music.play();
    // Start the game loop
    sf::Clock clock;
    
    while (window.isOpen())
    {
        
        text3.setString(to_string(clock.getElapsedTime().asSeconds()));
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed &&  event.key.code == sf::Keyboard::Space)
            {
                
                window.create(sf::VideoMode(window_x, window_y), "New Window");
            }
            
            char data[] = "A";
            sf::Socket::Status s = socket.send(&data, sizeof(data));
            if ( s != sf::Socket::Done)
                std::cout << "Send problem :(\n";
            else
                std::cout << "No send problem :)\n";
        }
        
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);
        sprite.setColor(sf::Color(255, 255, 255, 200)); // half transparent

        sprite.setScale(2, 2);
        // Draw the string
        window.draw(text);
        
        window.draw(text2);
        
        window.draw(text3);
        
        
        
        // Update the window
        window.display();
    
       
    }
    
    
    
    

    return EXIT_SUCCESS;
}
