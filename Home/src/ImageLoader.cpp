// filepath: /D:/Equation_Visualizer/Home/src/ImageLoader.cpp
#include "ImageLoader.h"

bool loadTexture(sf::Texture& texture, const std::string& filepath)
{
    if (!texture.loadFromFile(filepath))
    {
        std::cerr << "Failed to load image\n";
        std::cerr << "Provided path: " << filepath << "\n";
        return false;
    }
    return true;
}