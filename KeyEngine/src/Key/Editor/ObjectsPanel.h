#pragma once

#include "Key/Renderer/Texture.h"

namespace Key {

	class ObjectsPanel
	{
	public:
		ObjectsPanel();

		void OnImGuiRender();

	private:
		Ref<Texture2D> m_CubeImage;
	};

}
