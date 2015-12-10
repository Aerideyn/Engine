#pragma once
#include <map>
#include <vector>
#include <string>

namespace Render { class Texture2D; };
namespace detail
{
	struct PixelBuffer
	{
		PixelBuffer(){};
		PixelBuffer(std::vector<unsigned char> Data, int Width, int Height) : data(Data), width(Width), height(Height){}
		std::vector<unsigned char> data;
		int width;
		int height;
	};

	class TextureLoader
	{
	public:
		static PixelBuffer& LoadPixelBufferFromFile(std::string FilePath);
		static Render::Texture2D& LoadTextureFromFile(std::string FilePath);

		static void SetRootFilePath(std::string FilePath) { rootFilePath = FilePath; };

	private:
		static std::map<std::string, PixelBuffer> NameToPixelBufferMap;
		static std::map<std::string, Render::Texture2D> NameToTextureCacheMap;
		static std::string rootFilePath;
	};
}