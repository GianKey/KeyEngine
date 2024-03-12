#include "Kpch.h"
#include "Camera.h"

namespace Key {

	Camera::Camera(const glm::mat4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
	{
	}

}