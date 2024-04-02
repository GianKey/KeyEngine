#pragma once

#include "Key/Renderer/Mesh.h"

#include "Key/Scene/Scene.h"
#include "Key/Scene/Entity.h"

#include "Key/Editor/EditorCamera.h"

#include "AssetEditorPanel.h"

namespace Key {

	// NOTE(Yan): this is SEVERELY WIP
	class MeshViewerPanel : public AssetEditor
	{
	private:
		struct MeshScene
		{
			Ref<Scene> m_Scene;
			Ref<SceneRenderer> m_SceneRenderer;
			EditorCamera m_Camera;
			std::string m_Name;
			Ref<Mesh> m_Mesh;
			Entity m_MeshEntity;
			Entity m_DirectionaLight;
			bool m_ViewportPanelFocused = false;
			bool m_ViewportPanelMouseOver = false;
			bool m_ResetDockspace = true;
			bool m_IsViewportVisible = false;
		};
	public:
		MeshViewerPanel();
		~MeshViewerPanel();

		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnEvent(Event& e) override;
		void RenderViewport();
		virtual void OnImGuiRender() override;

		virtual void SetAsset(const Ref<Asset>& asset) override;

		virtual void OnClose() override {}
		virtual void Render() override {}

		void ResetCamera(EditorCamera& camera);
	private:
		void RenderMeshTab(ImGuiID dockspaceID, const std::shared_ptr<MeshScene>& sceneData);
		void DrawMeshNode(const Ref<Mesh>& mesh);
		void MeshNodeHierarchy(const Ref<Mesh>& mesh, aiNode* node, const glm::mat4& parentTransform = glm::mat4(1.0f), uint32_t level = 0);
	private:
		bool m_ResetDockspace = true;
	
		std::unordered_map<std::string, std::shared_ptr<MeshScene>> m_OpenMeshes;
		glm::vec2 m_ViewportBounds[2];

		bool m_WindowOpen = false;

		std::string m_TabToFocus;
	};

}