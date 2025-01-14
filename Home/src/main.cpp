#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <exprtk.hpp>

// Function to evaluate an equation using exprtk
float evaluateEquation(const std::string &equation, float x)
{
    typedef exprtk::symbol_table<float> symbol_table_t;
    typedef exprtk::expression<float> expression_t;
    typedef exprtk::parser<float> parser_t;

    // Setup the symbol table
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    // Setup the expression
    expression_t expression;
    expression.register_symbol_table(symbol_table);

    // Parse the equation
    parser_t parser;
    if (!parser.compile(equation, expression))
    {
        std::cerr << "Error parsing equation: " << parser.error() << "\n";
        return 0.0f; // Indicates failure
    }

    // Return the evaluated result
    return expression.value();
}

// Function to plot the graph
void plotGraph(const std::string &equation)
{
    // Validate the equation input
    if (equation.empty())
    {
        std::cerr << "Error: Equation is empty. Cannot plot graph.\n";
        return;
    }
    sf::RenderWindow graphWindow(sf::VideoMode({800, 600}), "Graph Window");

    // Define scaling factors for better visualization
    const float xScale = 50.0f;
    const float yScale = 50.0f;
    const float xOffset = 400.0f; // Center of the graph (X-axis)
    const float yOffset = 300.0f; // Center of the graph (Y-axis)

    // Create axes
    sf::VertexArray xAxis(sf::PrimitiveType::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, yOffset);
    xAxis[0].color = sf::Color::White;
    xAxis[1].position = sf::Vector2f(800, yOffset);
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::PrimitiveType::Lines, 2);
    yAxis[0].position = sf::Vector2f(xOffset, 0);
    yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(xOffset, 600);
    yAxis[1].color = sf::Color::White;

    // Generate points for the graph
    sf::VertexArray graph(sf::PrimitiveType::LineStrip);
    for (float x = -400; x <= 400; x += 1.0f)
    {
        float scaledX = x / xScale; // Scale down the x-coordinate
        float y = evaluateEquation(equation, scaledX);

        // Check for evaluation failure
        if (y == 0.0f && equation.find("x") != std::string::npos)
        {
            continue; // Skip invalid points if equation depends on x
        }

        float screenX = xOffset + x;
        float screenY = yOffset - y * yScale; // Scale and invert Y for graph alignment

        // Add the point to the graph
        graph.append(sf::Vertex({sf::Vector2f({screenX, screenY}), sf::Color::Green}));
    }

    // Main loop to render the graph
    while (graphWindow.isOpen())
    {
        while (const std::optional<sf::Event> event = graphWindow.pollEvent())
        {
            // calling the is method inside event object and it is checking the type of event called..
            // sf::Event::Closed represents a constant value inside Event class..
            if (event->is<sf::Event::Closed>())
            {
                graphWindow.close();
            }
        }

        graphWindow.clear(sf::Color::Black);
        graphWindow.draw(xAxis);
        graphWindow.draw(yAxis);
        graphWindow.draw(graph);
        graphWindow.display();
    }
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");

    // Load an image into a texture
    sf::Texture texture;
    if (!texture.loadFromFile("D:\\Equation_Visualizer\\Home\\images\\equation_visualizer_logo.png"))
    {
        std::cerr << "Failed to load image\n";
        std::cerr << "Provided path: " << "D:\\Equation_Visualizer\\Home\\images\\equation_visualizer_logo.png" << "\n";
        return -1; // Return an error if the image cannot be loaded
    }

    // Create a sprite and set its texture
    sf::Sprite sprite(texture);

    // Input Box
    sf::RectangleShape inputBox(sf::Vector2f(260.f, 40.f));
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setFillColor(sf::Color::White);
    inputBox.setPosition({230.f, 350.f});

    // Search Button
    sf::RectangleShape searchButton(sf::Vector2f(30.f, 40.f));
    searchButton.setOutlineColor(sf::Color::Black);
    searchButton.setOutlineThickness(2);
    searchButton.setFillColor(sf::Color::Black);
    searchButton.setPosition({490.f, 350.f});

    // Boxes of Different Equations....
    sf::RectangleShape linear(sf::Vector2f(100.f, 30.f));
    sf::RectangleShape quadratic(sf::Vector2f(100.f, 30.f));
    sf::RectangleShape cubic(sf::Vector2f(100.f, 30.f));
    sf::RectangleShape exponential(sf::Vector2f(100.f, 30.f));
    sf::RectangleShape logarithmic(sf::Vector2f(100.f, 30.f));
    sf::RectangleShape trignometric(sf::Vector2f(100.f, 30.f));
    sf::RectangleShape absolute(sf::Vector2f(100.f, 30.f));

    // setting their fill color
    linear.setFillColor(sf::Color::Black);
    quadratic.setFillColor(sf::Color::Black);
    cubic.setFillColor(sf::Color::Black);
    exponential.setFillColor(sf::Color::Black);
    logarithmic.setFillColor(sf::Color::Black);
    trignometric.setFillColor(sf::Color::Black);
    absolute.setFillColor(sf::Color::Black);

    // setting their positions...
    linear.setPosition({150.f, 420.f});
    quadratic.setPosition({275.f, 420.f});
    cubic.setPosition({400.f, 420.f});
    exponential.setPosition({525.f, 420.f});
    logarithmic.setPosition({215.f, 470.f});
    trignometric.setPosition({340.f, 470.f});
    absolute.setPosition({465.f, 470.f});

    // INSIDED SECTION IMAGE
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

    // Create a sprite and set its texture
    sf::Sprite spritemain(texturemain);
    sf::Sprite spritesearch(texturesearchicon);

    float scaleX = 0.18f; // Scale factor for the x-axis
    float scaleY = 0.20f; // Scale factor for the y-axis

    sprite.setScale(sf::Vector2f(scaleX, scaleY));
    sprite.setPosition({188.f, 160.f}); // absolute position

    spritemain.setScale(sf::Vector2f(scaleX, scaleY));
    spritemain.setPosition({188.f, 160.f}); // absolute position

    spritesearch.setScale(sf::Vector2f(0.03, 0.05));
    spritesearch.setPosition({497.f, 357.f});

    sf::Font font("D:\\Equation_Visualizer\\Home\\fonts\\STIXTwoText-VariableFont_wght.ttf");
    if (!font.openFromFile("D:\\Equation_Visualizer\\Home\\fonts\\STIXTwoText-VariableFont_wght.ttf"))
    {
        std::cerr << "Font not loaded correctly !!!";
    }

    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    text.setString("EQUATION VISUALIZER");

    // set the character size
    text.setCharacterSize(28); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Bold);

    text.setPosition({210.f, 360.f}); // absolute position

    sf::Text Linear(font); // a font is required to make a text object
    Linear.setString("Linear");
    Linear.setCharacterSize(14); // in pixels, not points!
    Linear.setFillColor(sf::Color::White);
    Linear.setStyle(sf::Text::Bold);
    Linear.setPosition({175.f, 428.f}); // absolute position

    sf::Text Quadratic(font); // a font is required to make a text object
    Quadratic.setString("Quadratic");
    Quadratic.setCharacterSize(14); // in pixels, not points!
    Quadratic.setFillColor(sf::Color::White);
    Quadratic.setStyle(sf::Text::Bold);
    Quadratic.setPosition({290.f, 428.f}); // absolute position

    sf::Text Cubic(font); // a font is required to make a text object
    Cubic.setString("Cubic");
    Cubic.setCharacterSize(14); // in pixels, not points!
    Cubic.setFillColor(sf::Color::White);
    Cubic.setStyle(sf::Text::Bold);
    Cubic.setPosition({430.f, 428.f}); // absolute position

    sf::Text Exponential(font); // a font is required to make a text object
    Exponential.setString("e^x");
    Exponential.setCharacterSize(14); // in pixels, not points!
    Exponential.setFillColor(sf::Color::White);
    Exponential.setStyle(sf::Text::Bold);
    Exponential.setPosition({560.f, 428.f}); // absolute position

    sf::Text Trignometric(font); // a font is required to make a text object
    Trignometric.setString("Sinx");
    Trignometric.setCharacterSize(14); // in pixels, not points!
    Trignometric.setFillColor(sf::Color::White);
    Trignometric.setStyle(sf::Text::Bold);
    Trignometric.setPosition({370.f, 478.f}); // absolute position

    sf::Text Logarithmic(font); // a font is required to make a text object
    Logarithmic.setString("Logx");
    Logarithmic.setCharacterSize(14); // in pixels, not points!
    Logarithmic.setFillColor(sf::Color::White);
    Logarithmic.setStyle(sf::Text::Bold);
    Logarithmic.setPosition({250.f, 478.f}); // absolute position

    sf::Text Absolute(font); // a font is required to make a text object
    Absolute.setString("|x|");
    Absolute.setCharacterSize(14); // in pixels, not points!
    Absolute.setFillColor(sf::Color::White);
    Absolute.setStyle(sf::Text::Bold);
    Absolute.setPosition({505.f, 478.f}); // absolute position

    // Search Text
    //  sf::Text searchButtonText(font);
    //  searchButtonText.setString("PLOT");
    //  searchButtonText.setCharacterSize(14); // in pixels, not points!
    //  searchButtonText.setFillColor(sf::Color::White);
    //  searchButtonText.setPosition({510.f, 350.f});

    // LOADING BAR ANIMATION

    // Create a background rectangle for the loading bar
    sf::RectangleShape loadingBarBackground(sf::Vector2f(200, 20));
    loadingBarBackground.setOutlineColor(sf::Color(255, 255, 255));
    loadingBarBackground.setFillColor(sf::Color(0, 0, 0));
    loadingBarBackground.setPosition({285.f, 430.f}); // x-offset , y-offset
    loadingBarBackground.setOutlineThickness(3);

    // Create the loading bar
    sf::RectangleShape loadingBar(sf::Vector2f(0, 20));
    loadingBar.setFillColor(sf::Color(255, 255, 255));
    loadingBar.setPosition({285.f, 430.f}); // x-offset , y-offset

    // Simulate loading process
    float progress = 0.0f;
    float loadingSpeed = 0.8f; // Adjust this value to change the loading speed
    bool loadingComplete = false;

  
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        // window.pollEvent() retrieves event one at a time from event queue...
        // std::optional ensures program safety as it won't crash if no event exists...

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // calling the is method inside event object and it is checking the type of event called..
            // sf::Event::Closed represents a constant value inside Event class..
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            
            if (event->is<sf::Event::TextEntered>())
            {
                if (event.text.unicode == '\b') // Handle backspace
                {
                    if (!userInput.empty())
                    {
                        userInput.pop_back();
                    }
                }
                else if (event->text.unicode < 128) // Handle ASCII characters
                {
                    userInput += static_cast<char>(event->text.unicode);
                }
            }

            if (event->is<sf::Event::KeyPressed>() && event->key.code == sf::Keyboard::Enter)
            {
                plotGraph(userInput);
            }
        }
    
        if (!loadingComplete)
        {
            // Update the loading bar
            if (progress < 1.0f)
            {
                progress += loadingSpeed * 0.01f;                           // Increment progress
                loadingBar.setSize(sf::Vector2f(200 * progress, 20));       // Update the size of the loading bar
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate loading delay
            }
            else
            {
                loadingComplete = true;
            }
        }

        if (loadingComplete)
        {
            window.clear(sf::Color::White);
            window.draw(spritemain);
            window.draw(inputBox);
            window.draw(searchButton);
            // window.draw(searchButtonText);

            window.draw(spritesearch);
            window.draw(linear);
            window.draw(quadratic);
            window.draw(cubic);
            window.draw(exponential);
            window.draw(trignometric);
            window.draw(logarithmic);
            window.draw(absolute);

            window.draw(Linear);
            window.draw(Quadratic);
            window.draw(Cubic);
            window.draw(Exponential);
            window.draw(Trignometric);
            window.draw(Logarithmic);
            window.draw(Absolute);

            // window.draw(logarithmic);
            // window.draw(trignometric);
        }
        else
        {
            // clear the window with black color
            window.clear(sf::Color::Black);
        }

        if (!loadingComplete)
        {

            // draw the sprite
            window.draw(sprite);

            // draw text
            window.draw(text);

            // draw loading bar background
            window.draw(loadingBarBackground);

            // draw loading bar
            window.draw(loadingBar);
        }

        // end the current frame
        window.display();
    }
}