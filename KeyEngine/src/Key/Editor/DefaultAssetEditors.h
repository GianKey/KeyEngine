#pragma once

#include "AssetEditorPanel.h"
#include "Key/Renderer/Mesh.h"

namespace Key {


	class TextureViewer : public AssetEditor
	{
	public:
		TextureViewer();

		virtual void SetAsset(const Ref<Asset>& asset) override { m_Asset = (Ref<Texture>)asset; }

	private:
		virtual void OnClose() override;
		virtual void Render() override;

	private:
		Ref<Texture> m_Asset;
	};


}
