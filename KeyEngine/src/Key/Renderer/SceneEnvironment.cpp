#include "Kpch.h"
#include "SceneEnvironment.h"

#include "SceneRenderer.h"

namespace Key {

	Environment Environment::Load(const std::string& filepath)
	{
		auto [radiance, irradiance] = SceneRenderer::CreateEnvironmentMap(filepath);
		return { filepath, radiance, irradiance };
	}
}