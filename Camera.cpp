#include "Camera.h"

Camera::Camera() { updateCamera(); };
Camera::~Camera() {}

mat4 Camera::getViewMatrix()
{
	return this->lookAt(eye, at, up);
}

mat4 Camera::getProjectionMatrix(bool isOrtho)
{
	if (isOrtho) {
		return this->ortho(-scale, scale, -scale, scale, this->near, this->far);
	}
	else {
		return this->perspective(fov, aspect, this->near, this->far);
	}
}

mat4 Camera::lookAt(const vec4& eye, const vec4& at, const vec4& up)
{
	vec4 n = normalize(eye - at);					// normalize():归一化函数
	vec4 u = normalize(vec4(cross(up, n), 0.0));	// cross()计算向量积
	vec4 v = normalize(vec4(cross(n, u), 0.0));
	vec4 t = vec4(0.0, 0.0, 0.0, 1.0);
	mat4 c = mat4(u, v, n, t);
	return c * Translate(-eye);						// 计算最后需要沿-eye方向平移
}

mat4 Camera::ortho(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	mat4 c;
	c[0][0] = 2.0 / (right - left);
	c[1][1] = 2.0 / (top - bottom);
	c[2][2] = -2.0 / (zFar - zNear);
	c[3][3] = 1.0;
	c[0][3] = -(right + left) / (right - left);
	c[1][3] = -(top + bottom) / (top - bottom);
	c[2][3] = -(zFar + zNear) / (zFar - zNear);
	return c;
}

mat4 Camera::perspective(const GLfloat fovy, const GLfloat aspect,
	const GLfloat zNear, const GLfloat zFar)
{
	GLfloat top = tan(fovy * M_PI / 180 / 2) * zNear;
	GLfloat right = top * aspect;

	mat4 c;
	c[0][0] = zNear / right;
	c[1][1] = zNear / top;
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -(2.0 * zFar * zNear) / (zFar - zNear);
	c[3][2] = -1.0;
	c[3][3] = 0.0;
	return c;
}

mat4 Camera::frustum(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	// 任意视锥体矩阵
	mat4 c;
	c[0][0] = 2.0 * zNear / (right - left);
	c[0][2] = (right + left) / (right - left);
	c[1][1] = 2.0 * zNear / (top - bottom);
	c[1][2] = (top + bottom) / (top - bottom);
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0 * zFar * zNear / (zFar - zNear);
	c[3][2] = -1.0;
	c[3][3] = 0.0;
	return c;
}


void Camera::updateCamera()
{
	float eyex = radius * cos(upAngle * M_PI / 180.0) * sin(rotateAngle * M_PI / 180.0);
	float eyey = radius * sin(upAngle * M_PI / 180.0);
	float eyez = radius * cos(upAngle * M_PI / 180.0) * cos(rotateAngle * M_PI / 180.0);

	eye = vec4(eyex, eyey, eyez, 1.0);
	at = vec4(0.0, 0.0, 0.0, 1.0);
	up = vec4(0.0, 1.0, 0.0, 0.0);

}


void Camera::keyboard(unsigned char key, int x, int y)
{
	// 键盘事件处理
	switch (key)
	{
		// 通过按键改变相机和投影的参数
	case 'u':
		rotateAngle += 5.0;
		break;
	case 'U':
		rotateAngle -= 5.0;
		break;

	case 'i':
		upAngle += 5.0;
		if (upAngle > 180)
			upAngle = 180;
		break;
	case 'I':
		upAngle -= 5.0;
		if (upAngle < -180)
			upAngle = -180;
		break;

	case 'o':
		radius += 0.1;
		break;
	case 'O':
		radius -= 0.1;
		break;

	case 'f':
		fov += 5.0;
		break;
	case 'F':
		fov -= 5.0;
		break;

	case 'g':
		aspect += 0.1;
			break;
	case 'G':
		aspect -= 0.1;
		break;
	case 'j':
		scale += 0.1;
		break;
	case 'J':
		scale -= 0.1;
		break;
	// 空格键初始化所有参数
	case ' ':
		radius = 4.0;
		rotateAngle = 0.0;
		upAngle = 0.0;
		fov = 45.0;
		aspect = 1.0;
		scale = 1.5;
		break;
	}
}
