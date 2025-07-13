#include "Kpch.h"
#include "AssetSerializer.h"

#include "Key/Utilities/StringUtils.h"
#include "Key/Utilities/FileSystem.h"

#include "Key/Renderer/Mesh.h"
#include "Key/Renderer/Renderer.h"

#include "yaml-cpp/yaml.h"

namespace Key {

	bool TextureSerializer::TryLoadData(const AssetMetadata& metadata, Ref<Asset>& asset) const
	{
		asset = Texture2D::Create(metadata.FilePath);
		asset->Handle = metadata.Handle;

		bool result = asset.As<Texture2D>()->Loaded();

		if (!result)
			asset->SetFlag(AssetFlag::Invalid, true);

		return result;
	}

	bool MeshAssetSerializer::TryLoadData(const AssetMetadata& metadata, Ref<Asset>& asset) const
	{
		Ref<Asset> temp = asset;
		asset = Ref<MeshAsset>::Create(metadata.FilePath);
		asset->Handle = metadata.Handle;
		return (asset.As<MeshAsset>())->GetStaticVertices().size() > 0; // Maybe?
	}

	bool EnvironmentSerializer::TryLoadData(const AssetMetadata& metadata, Ref<Asset>& asset) const
	{
		auto [radiance, irradiance] = Renderer::CreateEnvironmentMap(metadata.FilePath);

		if (!radiance || !irradiance)
			return false;

		asset = Ref<Environment>::Create(radiance, irradiance);
		asset->Handle = metadata.Handle;

		return true;
	}
}
