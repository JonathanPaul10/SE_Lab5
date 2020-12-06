#ifndef _TRI_MESH_H_
#define _TRI_MESH_H_

#include "Angel.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>


// 三角面片中的顶点序列
typedef struct vIndex {
	unsigned int x, y, z;
	vIndex(int ix, int iy, int iz) : x(ix), y(iy), z(iz) {}
} vec3i;

class TriMesh
{
public:
	TriMesh();
	~TriMesh();

	std::vector<vec3> getVertexPositions();
	std::vector<vec3> getVertexColors();
	std::vector<vec3> getVertexNormals();
	std::vector<vec3i> getFaces();
	std::vector<vec3> getPoints();
	std::vector<vec3> getColors();
	std::vector<vec3> getNormals();

	void computeTriangleNormals();
	void computeVertexNormals();

	// 获取和设置物体的旋转平移变化
	vec3 getTranslation();
	vec3 getRotation();
	vec3 getScale();
	mat4 getModelMatrix();

	void setTranslation(vec3 translation);
	void setRotation(vec3 rotation);
	void setScale(vec3 scale);

	// 设置物体材质
	vec4 getAmbient();
	vec4 getDiffuse();
	vec4 getSpecular();
	float getShininess();

	void setAmbient(vec4 _ambient );
	void setDiffuse(vec4 _diffuse);
	void setSpecular(vec4 _specular);
	void setShininess(float shininess);

	// 这里添加各种形状的、模型的读取顶点的函数
	void generateCube();
	void generateTriangle(vec3 color);
	void generateSquare(vec3 color);
	void readOff(const std::string& filename);

	// 将读取的顶点根据三角面片上的顶点下标逐个加入
	// 要传递给GPU的points等容器内
	void storeFacesPoints();

	// 清除数据
	void cleanData();

protected:
	std::vector<vec3> vertex_positions;	// 顶点坐标
	std::vector<vec3> vertex_colors;	// 顶点颜色
	std::vector<vec3> vertex_normals;	// 顶点法向量

	std::vector<vec3i> faces;	// 三角面片上每个顶点对应的下标
	std::vector<vec3> face_normals;	// 每个三角面片的法向量

	std::vector<vec3> points;	// 传入着色器的绘制点
	std::vector<vec3> colors;	// 传入着色器的颜色
	std::vector<vec3> normals;	// 传入着色器的法向量

	vec3 translation;			// 物体的平移参数
	vec3 rotation;				// 物体的旋转参数
	vec3 scale;					// 物体的缩放参数

	vec4 ambient;				// 环境光
	vec4 diffuse;				// 漫反射
	vec4 specular;				// 镜面反射
	float shininess;			// 高光系数

};


class Light: public TriMesh {
public:
	// 把实验3.2的阴影投影矩阵也加到Light类中
	mat4 getShadowProjectionMatrix();
	
};

#endif