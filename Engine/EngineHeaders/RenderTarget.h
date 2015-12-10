#pragma once
#include "Texture2D.h"
#include <vector>
namespace Render
{
	/// A texture which can be rendered into, in place of the screen.
	/*! \b Usage: <br>
		Create the render target using desired height, width and format type. <br>
		Set the render target as the rendering destination by BindRenderTarget() <br>
		Render the scene. <br>
		Unbind the render target to reset the rendering destination with DisableRenderTarget() <br>
		Like the Texture2D the RenderTarget holds a reference counted handle to the data and not the data itself. <br>
		This means the RenderTarget can be copied cheaply, however all copies refer to the same texture object on the gpu. <br>

		<b> Downloading from GPU: </b> <br>
		To halt the rendering pipeline and request the texture be downloaded immediately, call the inherited Texture2D GetData() method. <br>
		To que the download to be completed when it will minimise performance impact (gpu idleing etc), call GetTextureDownloader() <br>
		The texture downloader will hold a reference counted handle to the texture.  <br>
		Since the render target is cleared and reset each time it is bound, the data held in texture downloader will not be corrupted by further use of the render target. <br>
	
	*/
	class RenderTarget : public Texture2D
	{
	public:
		RenderTarget(int Height, int Width, FormatType type);
		~RenderTarget(){};
	public:
		/// Clears the texture, and activates it as the target for rendering.
		void BindRenderTarget();
		void DisableRenderTarget();
		virtual void Release();
	private:

		class FBOHandle
		{
		public:
			FBOHandle();
			FBOHandle(unsigned int Handle);
			~FBOHandle();
			unsigned int GetHandle();
		private:
			unsigned int glHandle;
		};
		bool newTargetRequired;
		int height;
		int width;
		Texture2D::FormatType type;
		std::shared_ptr<FBOHandle> FrameBuffer;
	public:
		// the Render target will construct a new FBO and texture every time it is bound. 
		// By taking ownership of a rendertargets FBO it is safe to assume that the data it contains won't change or be deleted prematurely.
		/// Downloads RenderTarget data when appropriate.
		/*!
		
		
		*/
		class TextureDownloader
		{
			friend class RenderTarget;
		public:
			TextureDownloader(){};
			~TextureDownloader();
		public:
			bool IsDownloadComplete();
			template <typename T>
			std::vector<T> GetData(FormatType type);
			void Release();
		private:
			class PBOHandle
			{
			public:
				PBOHandle();
				PBOHandle(unsigned int Handle);
				~PBOHandle();
				unsigned int GetHandle();
			private:
				unsigned int glHandle;
			};
			TextureDownloader(std::shared_ptr<FBOHandle> handle, FormatType type, int Height, int Width);
			int height;
			int width;
			void* fence;
			std::shared_ptr<PBOHandle> pboHandle;
			std::shared_ptr<FBOHandle> fboHandle;
		};
		TextureDownloader GetTextureDownloader();
	};
}
