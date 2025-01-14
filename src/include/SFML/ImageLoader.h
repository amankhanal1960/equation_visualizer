// filepath: /D:/Equation_Visualizer/Home/include/ImageLoader.h
#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <SFML/Graphics.hpp>
#include <iostream>

bool loadTexture(sf::Texture& texture, const std::string& filepath);

#endif // IMAGELOADER_H