#version 330 core

in vec3 vPosition;
in vec3 vColor;
in vec3 vNormal;

// 模型变换矩阵、相机观察矩阵、投影矩阵
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position;
out vec3 normal;

void main() 
{
	vec4 v1 = model * vec4(vPosition, 1.0);  
	// 由于model矩阵有可能为阴影矩阵，为了得到正确位置，我们需要做一次透视除法
	vec4 v2 = vec4(v1.xyz / v1.w, 1.0);
	// 考虑相机和投影
	vec4 v3 = projection* view * v2;
	// 再做一次透视除法 (为了明确概念，我们显式做一次透视除法)
	vec4 v4 = vec4(v3.xyz / v3.w, 1.0);
	gl_Position = v4;

    // position = vPosition;
    // normal = vNormal;
    position = vec3(v2.xyz);
    normal = vec3( model * vec4(vNormal, 0.0) );
}

