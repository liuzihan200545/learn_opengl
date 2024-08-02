#pragma once
#include<core.h>

class VertexArray{
public:

    // vertices:数据
    // vertices_size:数据数组大小，应传入sizeof(vertices)
    // indices:面与顶点对应关系
    // indices_size:indices数组大小，应传入sizeof(indices)
    // attr_length[]:传入数组，数组中元素依次表示每个顶点的特性的float数量
    // attris_size：attr_length的长度
    VertexArray(float *vertices, unsigned int vertices_size, unsigned int *indices, unsigned int indices_size,
                unsigned int *attr_length, unsigned int attris_size);

    void SetProperty(int index, int vertex_num, int stride, int offsite);

    void bindVAO();

    void bindVBO();

    ~VertexArray();

private:
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
};


VertexArray::VertexArray(float *vertices, unsigned int vertices_size, unsigned int *indices,unsigned int indices_size,unsigned int attr_length[],unsigned int attris_size) {

    glGenBuffers(1,&vbo);
    //将生成的VBO绑定到VBO插槽上
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    //开辟对应的显存，填入数据
    glBufferData(GL_ARRAY_BUFFER,vertices_size,vertices,GL_STATIC_DRAW);

    //生成一个VAO
    glGenVertexArrays(1,&vao);
    //将生成的VAO绑定到VAO插槽上
    glBindVertexArray(vao);
    //将上下文切换至posVBO
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    //解锁VAO中0号位置
    //生成一个EBO
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices_size,indices,GL_STATIC_DRAW);
    //将ebo绑定到vao
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    unsigned int sum_attris = 0;
    for(int i = 0;i<attris_size;i++){
        sum_attris += attr_length[i];
    }
    int offsite = 0;
    for(int i = 0;i<attris_size;i++){
        SetProperty(i,(int)attr_length[i],(int)sum_attris,offsite);
        offsite += (int)attr_length[i];
    }
    glBindVertexArray(0);
}

void VertexArray::SetProperty(int index,int vertex_num,int stride,int offsite) {
    glEnableVertexAttribArray(index);
    //VAO加入描述信息
    glVertexAttribPointer(index, vertex_num, GL_FLOAT, GL_FALSE, stride * sizeof(float),(void *) (offsite * sizeof(float)));
}

void VertexArray::bindVAO() {
    glBindVertexArray(vao);
}

VertexArray::~VertexArray() {
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);
    glDeleteVertexArrays(1,&vao);
}

void VertexArray::bindVBO() {
    this->bindVAO();
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
}
