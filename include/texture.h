#pragma once
#include <core.h>

class Texture{
public:
    Texture(const char *file_name, int index);
    ~Texture();
    void bind();
private:
    const char *file_name;
    int index;
    unsigned int texture;
    int width,height,channels;
};

Texture::Texture(const char *file_name,int index) : file_name(file_name),index(index){
    // stbImage读取图片
    // 反转y轴
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file_name,&width,&height,&channels,STBI_rgb_alpha);

    // 生成纹理
    glGenTextures(1,&texture);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE0 + index);
    // 绑定纹理
    glBindTexture(GL_TEXTURE_2D,texture);
    // 传输纹理数据,开辟显存
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    // 设置纹理的过滤方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    // 设置纹理的环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//v
    // 释放数据
    stbi_image_free(data);
}

Texture::~Texture() {
    if(texture != 0){
        glDeleteTextures(1,&texture);
    }
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D,texture);
}
