#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>

int main()
{
    // Get the desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // create the window with full screen size
    sf::RenderWindow window(desktop, "My Window");

    // Create the TGUI GUI and attach it to the window
    tgui::Gui gui(window);

    // Create an EditBox widget
    auto editBox = tgui::EditBox::create();
    editBox->setSize(400, 50);
    editBox->setPosition(200, 275);
    editBox->setDefaultText("Enter equation...");
    gui.add(editBox);

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event); // Pass the event to the GUI
        }

        window.clear();
        gui.draw(); // Draw the GUI
        window.display();
    }

    return 0;
}