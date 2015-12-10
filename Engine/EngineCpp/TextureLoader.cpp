#include <iostream>
#include "Texture2D.h"
#include "TextureLoader.h"
#include "lodepng.h"

std::string detail::TextureLoader::rootFilePath = "";
std::map<std::string, detail::PixelBuffer> detail::TextureLoader::NameToPixelBufferMap;
std::map<std::string, Render::Texture2D> detail::TextureLoader::NameToTextureCacheMap;

detail::PixelBuffer& detail::TextureLoader::LoadPixelBufferFromFile(std::string FilePath)
{
	// if the pixel buffer already exists in cache;
	auto iter = NameToPixelBufferMap.find(rootFilePath + FilePath);
	if (iter != NameToPixelBufferMap.end()) return iter->second;
	
	//otherwise load it.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, rootFilePath + FilePath);

	//if there's an error, display it
	if (error) 
	{
		std::cout << "Texture name: " << FilePath << " decoder error " << error << ": " << lodepng_error_text(error) << "Returning null texture." << std::endl;
		throw;
	}

	// if no errors, cache loaded texture.
	PixelBuffer newpb = PixelBuffer(image, width, height);
	NameToPixelBufferMap[rootFilePath + FilePath] = newpb;
	return NameToPixelBufferMap[rootFilePath + FilePath] = newpb;
}

Render::Texture2D& detail::TextureLoader::LoadTextureFromFile(std::string FilePath)
{
	// if the texture already exists in cache;
	auto iter = NameToTextureCacheMap.find(rootFilePath + FilePath);
	if (iter != NameToTextureCacheMap.end()) 
		return iter->second;

	//otherwise load it.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, rootFilePath + FilePath);

	//if there's an error, display it
	if (error)
	{
		std::cout << "Texture name: " << FilePath << " decoder error " << error << ": " << lodepng_error_text(error) << "Returning null texture." << std::endl;
		throw;
	}

	// if no errors, cache loaded texture to both caches.
	PixelBuffer newpb = PixelBuffer(image, width, height);
	NameToPixelBufferMap[rootFilePath + FilePath] = newpb;
	NameToTextureCacheMap[rootFilePath + FilePath] = Render::Texture2D(FilePath, true);
	return NameToTextureCacheMap[rootFilePath + FilePath];
}