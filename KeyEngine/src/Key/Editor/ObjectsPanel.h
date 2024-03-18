#pragma once

#include "Key/Renderer/Texture.h"
#include "Key/Asset/AssetManager.h"
namespace Key {

	class ObjectsPanel
	{
	public:
		ObjectsPanel();

		void OnImGuiRender();

	private:
		void DrawObject(const char* label, AssetHandle handle);
	private:
		Ref<Texture2D> m_CubeImage;
	};

}
