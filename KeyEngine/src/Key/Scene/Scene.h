#pragma once

#include "Entity.h"
#include "Key/Renderer/Camera.h"

namespace Key {

	struct Environment
	{
		Ref<TextureCube> RadianceMap;
		Ref<TextureCube> IrradianceMap;

		static Environment Load(const std::string& filepath);
	};

	class Scene
	{
	public:
		Scene(const std::string& debugName = "Scene");
		~Scene();
		
		void Init();

		void OnUpdate(TimeStep ts);

		void SetCamera(const Camera& camera);
		Camera& GetCamera() { return m_Camera; }

		void SetEnvironment(const Environment& environment);
		void SetSkybox(const Ref<TextureCube>& skybox);

		float& GetSkyboxLod() { return m_SkyboxLod; }

		void AddEntity(Entity* entity);
		Entity* CreateEntity();
	private:
		std::string m_DebugName;
		std::vector<Entity*> m_Entities;
		Camera m_Camera;

		Environment m_Environment;
		Ref<TextureCube> m_SkyboxTexture;
		Ref<MaterialInstance> m_SkyboxMaterial;

		float m_SkyboxLod = 1.0f;

		friend class SceneRenderer;
		friend class SceneHierarchyPanel;
	};

}