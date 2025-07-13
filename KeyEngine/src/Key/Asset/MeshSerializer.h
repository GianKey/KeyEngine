#pragma once

#include "Key/Asset/AssetSerializer.h"
#include "Key/Renderer/Mesh.h"

namespace Key {

	class MeshSerializer : public AssetSerializer
	{
	public:
		MeshSerializer();

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);

		virtual void Serialize(const AssetMetadata& metadata, const Ref<Asset>& asset) const override {}
		virtual bool TryLoadData(const AssetMetadata& metadata, Ref<Asset>& asset) const override;
	};

}