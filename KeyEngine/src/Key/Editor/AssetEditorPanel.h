#pragma once

#include "Key/ImGui/ImGui.h"
#include "Key/Core/TimeStep.h"
#include "Key/Core/Events/Event.h"
namespace Key {

	class AssetEditor
	{
	protected:
		AssetEditor(const char* title);

	public:
		virtual ~AssetEditor(){}

		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender();

		void SetOpen(bool isOpen);
		virtual void SetAsset(const Ref<Asset>& asset) = 0;

	protected:
		void SetMinSize(uint32_t width, uint32_t height);
		void SetMaxSize(uint32_t width, uint32_t height);

	private:
		virtual void OnClose() = 0;
		virtual void Render() = 0;

	private:
		const char* m_Title;
		bool m_IsOpen = false;

		ImGuiWindowFlags m_Flags = 0;
		ImVec2 m_MinSize, m_MaxSize;
	};

	class AssetEditorPanel
	{
	public:
		static void RegisterDefaultEditors();
		static void UnregisterAllEditors();
		static void OnUpdate(TimeStep ts);
		static void OnEvent(Event& e);
		static void OnImGuiRender();
		static void OpenEditor(const Ref<Asset>& asset);

		template<typename T>
		static void RegisterEditor(AssetType type)
		{
			static_assert(std::is_base_of<AssetEditor, T>::value, "AssetEditorPanel::RegisterEditor requires template type to inherit from AssetEditor");
			KEY_CORE_ASSERT(s_Editors.find(type) == s_Editors.end(), "There's already an editor for that asset!");
			s_Editors[type] = CreateScope<T>();
		}

	private:
		static std::unordered_map<AssetType, Scope<AssetEditor>> s_Editors;
	};

}
