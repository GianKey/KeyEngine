#include "Kpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Key {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatirx()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		//注意矩阵相乘的顺序，先乘 view 矩阵 之后再乘 proj 矩阵
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}