#include "Texture.h"
#include <stb/stb_image.h>
#include <iostream>
using namespace std;

Texture::Texture(const string& path){
    stbi_set_flip_vertically_on_load(true);
    int w,h,channels;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 4);
    if(!data){
        cout<<"failed to load texture: " << path <<stbi_failure_reason() <<endl;
        return;
    }
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);   // deleting 0 is safely ignored
}


void Texture::bind(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);  // choose the slot
    glBindTexture(GL_TEXTURE_2D, m_id);   // put this texture in it
}