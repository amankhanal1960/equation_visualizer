#include <SFML/Graphics.hpp>
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

    // IMAGES
    //  Load an image into a texture
    sf::Texture texture;
    if (!texture.loadFromFile("D:\\Equation_Visualizer\\Home\\images\\equation_visualizer_logo.png"))
    {
        std::cerr << "Failed to load image\n";
        std::cerr << "Provided path: " << "D:\\Equation_Visualizer\\Home\\images\\equation_visualizer_logo.png" << "\n";
        return -1; // Return an error if the image cannot be loaded
    }

    //  Load an image into a texture
    sf::Texture texturemain;
    if (!texturemain.loadFromFile("D:\\Equation_Visualizer\\Home\\images\\equation_visualizer_black.png"))
    {
        std::cerr << "Failed to load image\n";
        std::cerr << "Provided path: " << "D:\\Equation_Visualizer\\Home\\images\\equation_visualizer_black.png" << "\n";
        return -1; // Return an error if the image cannot be loaded
    }

    // Load an image into a texture
    sf::Texture texturesearchicon;
    if (!texturesearchicon.loadFromFile("D:\\Equation_Visualizer\\Home\\images\\magnifying-glass.png"))
    {
        std::cerr << "Failed to load image\n";
        std::cerr << "Provided path: " << "D:\\Equation_Visualizer\\Home\\images\\magnifying-glass.png" << "\n";
        return -1; // Return an error if the image cannot be loaded
    }

    // Input Box
    sf::RectangleShape inputBox(sf::Vector2f({window.getSize().x * 0.30f, window.getSize().y * 0.05f}));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setPosition({window.getSize().x * 0.33f, window.getSize().y * 0.48f});

    // Search Button
    sf::RectangleShape searchButton(sf::Vector2f({window.getSize().x * 0.05f, window.getSize().y * 0.05f}));
    searchButton.setOutlineColor(sf::Color::Black);
    searchButton.setOutlineThickness(2);
    searchButton.setFillColor(sf::Color::Black);
    searchButton.setPosition({window.getSize().x * 0.62f, window.getSize().y * 0.48f});

    // Boxes of Different Equations....
    sf::RectangleShape linear(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));
    sf::RectangleShape quadratic(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));
    sf::RectangleShape cubic(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));
    sf::RectangleShape exponential(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));
    sf::RectangleShape logarithmic(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));
    sf::RectangleShape trignometric(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));
    sf::RectangleShape absolute(sf::Vector2f({window.getSize().x * 0.09f, window.getSize().y * 0.04f}));

    // setting their fill color
    linear.setFillColor(sf::Color::Black);
    quadratic.setFillColor(sf::Color::Black);
    cubic.setFillColor(sf::Color::Black);
    exponential.setFillColor(sf::Color::Black);
    logarithmic.setFillColor(sf::Color::Black);
    trignometric.setFillColor(sf::Color::Black);
    absolute.setFillColor(sf::Color::Black);

    // setting their positions...
    linear.setPosition({window.getSize().x * 0.27f, window.getSize().y * 0.58f});
    quadratic.setPosition({window.getSize().x * 0.39f, window.getSize().y * 0.58f});
    cubic.setPosition({window.getSize().x * 0.51f, window.getSize().y * 0.58f});
    exponential.setPosition({window.getSize().x * 0.63f, window.getSize().y * 0.58f});
    logarithmic.setPosition({window.getSize().x * 0.33f, window.getSize().y * 0.65f});
    trignometric.setPosition({window.getSize().x * 0.45f, window.getSize().y * 0.65f});
    absolute.setPosition({window.getSize().x * 0.57f, window.getSize().y * 0.65f});

    // Loading Bar....
    //  Create a background rectangle for the loading bar
    sf::RectangleShape loadingBarBackground(sf::Vector2f(window.getSize().x * 0.25f, window.getSize().y * 0.03f));
    loadingBarBackground.setOutlineColor(sf::Color(255, 255, 255));
    loadingBarBackground.setFillColor(sf::Color(0, 0, 0));
    loadingBarBackground.setPosition({window.getSize().x * 0.37f, window.getSize().y * 0.68f}); // x-offset , y-offset
    loadingBarBackground.setOutlineThickness(3);

    // Create the loading bar
    sf::RectangleShape loadingBar(sf::Vector2f(0, 20));
    loadingBar.setFillColor(sf::Color(255, 255, 255));
    loadingBar.setPosition({window.getSize().x * 0.37f, window.getSize().y * 0.68f}); // x-offset , y-offset

    // Simulate loading process
    float progress = 0.0f;
    float loadingSpeed = 0.8f; // Adjust this value to change the loading speed
    bool loadingComplete = false;

    // Create a sprite and set its texture
    sf::Sprite sprite(texture);

    sf::Sprite spritemain(texturemain);

    sf::Sprite spritesearch(texturesearchicon);

    float scaleX = 0.38f; // Scale factor for the x-axis
    float scaleY = 0.45f; // Scale factor for the y-axis

    sprite.setScale(sf::Vector2f(scaleX, scaleY));
    sprite.setPosition({window.getSize().x * 0.28f, window.getSize().y * 0.20f}); // absolute position

    spritemain.setScale(sf::Vector2f(scaleX, scaleY));
    spritemain.setPosition({window.getSize().x * 0.28f, window.getSize().y * 0.10f}); // absolute position

    spritesearch.setScale(sf::Vector2f(scaleX * 0.15, scaleY * 0.15));
    spritesearch.setPosition({window.getSize().x * 0.635f, window.getSize().y * 0.49f});

    // TEXT SECTION

    sf::Font font("D:\\Equation_Visualizer\\Home\\fonts\\STIXTwoText-VariableFont_wght.ttf");
    if (!font.openFromFile("D:\\Equation_Visualizer\\Home\\fonts\\STIXTwoText-VariableFont_wght.ttf"))
    {
        std::cerr << "Font not loaded correctly !!!";
    }

    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    text.setString("EQUATION  VISUALIZER");

    // set the character size
    text.setCharacterSize(60); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Bold);

    text.setPosition({window.getSize().x * 0.31f, window.getSize().y * 0.58f}); // absolute position


    sf::Text Linear(font); // a font is required to make a text object
    Linear.setString("Linear");
    Linear.setCharacterSize(26); // in pixels, not points!
    Linear.setFillColor(sf::Color::White);
    Linear.setStyle(sf::Text::Bold);
    Linear.setPosition({window.getSize().x * 0.295f, window.getSize().y * 0.585f}); // absolute position

    sf::Text Quadratic(font); // a font is required to make a text object
    Quadratic.setString("Quadratic");
    Quadratic.setCharacterSize(26); // in pixels, not points!
    Quadratic.setFillColor(sf::Color::White);
    Quadratic.setStyle(sf::Text::Bold);
    Quadratic.setPosition({window.getSize().x * 0.405f, window.getSize().y * 0.585f}); // absolute position

    sf::Text Cubic(font); // a font is required to make a text object
    Cubic.setString("Cubic");
    Cubic.setCharacterSize(26); // in pixels, not points!
    Cubic.setFillColor(sf::Color::White);
    Cubic.setStyle(sf::Text::Bold);
    Cubic.setPosition({window.getSize().x * 0.538f, window.getSize().y * 0.585f}); // absolute position

    sf::Text Exponential(font); // a font is required to make a text object
    Exponential.setString("e^x");
    Exponential.setCharacterSize(26); // in pixels, not points!
    Exponential.setFillColor(sf::Color::White);
    Exponential.setStyle(sf::Text::Bold);
    Exponential.setPosition({window.getSize().x * 0.662f, window.getSize().y * 0.585f}); // absolute position

    sf::Text Trignometric(font); // a font is required to make a text object
    Trignometric.setString("Sinx");
    Trignometric.setCharacterSize(26); // in pixels, not points!
    Trignometric.setFillColor(sf::Color::White);
    Trignometric.setStyle(sf::Text::Bold);
    Trignometric.setPosition({window.getSize().x * 0.357f, window.getSize().y * 0.655f}); // absolute position

    sf::Text Logarithmic(font); // a font is required to make a text object
    Logarithmic.setString("Logx");
    Logarithmic.setCharacterSize(26); // in pixels, not points!
    Logarithmic.setFillColor(sf::Color::White);
    Logarithmic.setStyle(sf::Text::Bold);
    Logarithmic.setPosition({window.getSize().x * 0.477f, window.getSize().y * 0.655f}); // absolute position

    sf::Text Absolute(font); // a font is required to make a text object
    Absolute.setString("|x|");
    Absolute.setCharacterSize(26); // in pixels, not points!
    Absolute.setFillColor(sf::Color::White);
    Absolute.setStyle(sf::Text::Bold);
    Absolute.setPosition({window.getSize().x * 0.607f, window.getSize().y * 0.655f}); // absolute position

    sf::Text userInput(font); // a font is required to make a text object
    userInput.setCharacterSize(50); // in pixels, not points!
    userInput.setFillColor(sf::Color::Black);
    userInput.setPosition({window.getSize().x * 0.33f, window.getSize().y * 0.48f});
    
    // Start the game loop
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // calling the is method inside event object and it is checking the type of event called..
            // sf::Event::Closed represents a constant value inside Event class..
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (!loadingComplete)
        {

            if (progress < 1.0f)
            {
                progress += loadingSpeed * 0.2f;                                                                     // Increment progress
                loadingBar.setSize(sf::Vector2f(window.getSize().x * 0.25f * progress, window.getSize().y * 0.03f)); // Update the size of the loading bar
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

                window.clear(sf::Color::Black);

                // draw the sprite
                window.draw(sprite);

                // draw text
                window.draw(text);

                // draw loading bar background
                window.draw(loadingBarBackground);

                // draw loading bar
                window.draw(loadingBar); // Simulate loading delay
            }
            else
            {
                loadingComplete = true;
            }
        }

        if (loadingComplete)
        {
            std::string inputText = "";

            window.clear(sf::Color::White);
            window.draw(spritemain);
            window.draw(inputBox);
            window.draw(searchButton);
            window.draw(spritesearch);

            // Boxes...
            window.draw(linear);
            window.draw(quadratic);
            window.draw(cubic);
            window.draw(exponential);
            window.draw(trignometric);
            window.draw(logarithmic);
            window.draw(absolute);

            // Text...
            window.draw(Linear);
            window.draw(Quadratic);
            window.draw(Cubic);
            window.draw(Exponential);
            window.draw(Trignometric);
            window.draw(Logarithmic);
            window.draw(Absolute);
            window.draw(userInput);
            

            while (const std::optional<sf::Event> event = window.pollEvent())
            {
                
                // calling the is method inside event object and it is checking the type of event called..
                // sf::Event::Closed represents a constant value inside Event class..
                if (event->is<sf::Event::TextEntered>())
                {
                    if (event->getIf<sf::Event::TextEntered>()->unicode == 8)
                    { // Backspace key
                        if (!inputText.empty())
                        {
                            inputText.pop_back();
                           
                        }
                    }
                    else if (event->getIf<sf::Event::TextEntered>()->unicode < 128)
                    { // Printable ASCII
                        inputText += static_cast<char>(event->getIf<sf::Event::TextEntered>()->unicode);
                        
                    }
                    
                    userInput.setString(inputText);
                }
            }
        }

        window.display();
    }
}