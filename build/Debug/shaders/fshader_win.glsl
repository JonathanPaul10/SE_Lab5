#version 330 core


// 给光源数据一个结构体
struct Light{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	vec3 position;
};

// 给物体材质数据一个结构体
struct Material{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float shininess;
};

in vec3 position;
in vec3 normal;

// 相机坐标
uniform vec3 eye_position;
// 光源
uniform Light light;
// 物体材质
uniform Material material;

uniform int isShadow;

out vec4 fColor;


void main()
{
	if (isShadow == 1) {
		// 如果传进来的 是阴影
		fColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else if(isShadow == 0){
			
		// @TODO: 计算四个归一化的向量 N,V,L,R(或半角向量H)
		vec3 N= normalize(normal);
    	vec3 V= normalize(eye_position - position); // 存疑
    	vec3 L= normalize(light.position - position);
    	vec3 R= reflect( -L, N);

		    // 环境光分量I_a
    vec4 I_a = light.ambient * material.ambient;

    // @TODO: Task2 计算漫反射系数alpha和漫反射分量I_d
    float alpha = max(dot(L, N),0);
    vec4 I_d = alpha * light.diffuse * material.diffuse;

    // @TODO: Task2 计算高光系数beta和镜面反射分量I_s
    float beta = max(pow(dot(R, V),material.shininess),0);
    vec4 I_s = beta * light.specular * material.specular;

    // @TODO: Task2 计算高光系数beta和镜面反射分量I_s
    // 注意如果光源在背面则去除高光
    if( dot(R, V) < 0.0 ) {
	    I_s = vec4(0.0, 0.0, 0.0, 1.0);
    }

    // 合并三个分量的颜色，修正透明度
    fColor = I_a + I_d + I_s;
    fColor.a = 1.0;
	}
	else
	{
		fColor = vec4(position, 1.0);
	}
}
