#pragma once 
#include <GL/glew.h>
#include <string>

class Texture{
    public:
        explicit Texture(const std::string& path);
        ~Texture();
        Texture(const Texture&) = delete;
        Texture& operator = (const Texture) = delete;
        void bind(int unit) const;
    private:
        unsigned int m_id = 0;
    
};