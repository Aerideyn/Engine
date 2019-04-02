#pragma once
unsigned int LinkShaders(unsigned int VertexShaderID, unsigned int FragmentShaderID);
unsigned int CreateFragmentShader(const char * fragment_file_path);
unsigned int CreateVertexShader(const char * vertex_file_path);