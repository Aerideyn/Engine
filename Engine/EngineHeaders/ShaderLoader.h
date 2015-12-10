#pragma once
#include <map>
#include <string>

namespace detail
{
	class ShaderLoader
	{
	private:
		static std::map<const char*, unsigned int> FragmentShaderIDMap;
		static std::map<const char*, unsigned int> VertexShaderIDMap;
		static std::map<std::pair<unsigned int, unsigned int>, unsigned int> ShaderIDMap;
		static std::string rootFilePath;

		static unsigned int LoadFragmentShader(const char* Filepath, bool KeyIsCode);
		static unsigned int LoadVertexShader(const char* FilePath, bool KeyIsCode);

	public:
		static unsigned int LoadShaderUsingCode(const char* VertexShaderCode, const char* FragmentShaderCode);
		static unsigned int LoadShader(const char* VertexShader, const char* FragmentShader);
		static unsigned int LoadShader(unsigned int VertexShader, unsigned int FragmentShader);
		static void SetRootPath(std::string Path) { rootFilePath = Path; };
	};
}
