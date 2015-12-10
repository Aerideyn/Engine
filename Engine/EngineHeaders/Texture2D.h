#pragma once
#include <vector>
#include <memory>

namespace Render
{
	class Texture2D
	{
		friend class Shader;
	public:
		enum class FormatType{ Single, Vector2, Vector4, Color, };
		enum class FilterMode{ Nearest, Linear };
		enum class WrapMode{ ClampToEdge, ClampToBorder, Repeat, Mirror };

	public:
		Texture2D();
		Texture2D(std::string FilePath, bool GenerateNewTexture);
		Texture2D(int Width, int Height, FormatType Type, void * Data, bool GenerateMipmaps);
		virtual ~Texture2D();
		virtual void SetWrapModeX(Texture2D::WrapMode mode);
		virtual void SetWrapModeY(Texture2D::WrapMode mode);
		virtual void SetFilterMode(Texture2D::FilterMode mode);
		virtual void SetMipmapFilterMode(Texture2D::FilterMode mode);
		virtual void Release();

		template <typename T>
		std::vector<T> GetData(FormatType type);
		bool IsEmpty() { return isEmpty; };

	protected:
		// The handle is an object, and will be accessed through a shared pointer.
		// Reference counted handles are required to support copying of textures without messy ownership issues.
		class TextureHandle
		{
		public:
			TextureHandle(unsigned int Handle);
			~TextureHandle();
			unsigned int GetHandle();
		private:
			unsigned int glHandle;
		};

		bool isEmpty;
		bool mipmappingEnabled;
		bool DataIsCached;
		std::string filepath;
		std::shared_ptr<TextureHandle> handle;
	};
}
