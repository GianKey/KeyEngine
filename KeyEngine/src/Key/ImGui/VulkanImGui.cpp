#include "Kpch.h"
#include "ImGui.h"

#include "Key/Renderer/RendererAPI.h"

#include "Key/Platform/Vulkan/VulkanTexture.h"
#include "Key/Platform/Vulkan/VulkanImage.h"

#include "Key/Platform/OpenGL/OpenGLTexture.h"
#include "Key/Platform/OpenGL/OpenGLImage.h"

#include "imgui/examples/imgui_impl_vulkan_with_textures.h"

namespace Key::UI {

	void Image(const Ref<Image2D>& image, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col)
	{
		if (RendererAPI::Current() == RendererAPIType::OpenGL)
		{
			Ref<OpenGLImage2D> glImage = image.As<OpenGLImage2D>();
			ImGui::Image((ImTextureID)glImage->GetRendererID(), size, uv0, uv1, tint_col, border_col);
		}
		else
		{
			Ref<VulkanImage2D> vulkanImage = image.As<VulkanImage2D>();
			const auto& imageInfo = vulkanImage->GetImageInfo();
			if (!imageInfo.ImageView)
				return;
			auto textureID = ImGui_ImplVulkan_AddTexture(imageInfo.Sampler, imageInfo.ImageView, vulkanImage->GetDescriptor().imageLayout);
			ImGui::Image((ImTextureID)textureID, size, uv0, uv1, tint_col, border_col);
		}
	}

	void Image(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col)
	{
		if (RendererAPI::Current() == RendererAPIType::OpenGL)
		{
			Ref<OpenGLImage2D> image = texture->GetImage().As<OpenGLImage2D>();
			ImGui::Image((ImTextureID)image->GetRendererID(), size, uv0, uv1, tint_col, border_col);
		}
		else
		{
			Ref<VulkanTexture2D> vulkanTexture = texture.As<VulkanTexture2D>();
			const VkDescriptorImageInfo& imageInfo = vulkanTexture->GetVulkanDescriptorInfo();
			auto textureID = ImGui_ImplVulkan_AddTexture(imageInfo.sampler, imageInfo.imageView, imageInfo.imageLayout);
			ImGui::Image((ImTextureID)textureID, size, uv0, uv1, tint_col, border_col);
		}
	}

	bool ImageButton(const Ref<Image2D>& image, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
	{
		if (RendererAPI::Current() == RendererAPIType::OpenGL)
		{
			Ref<OpenGLImage2D> glImage = image.As<OpenGLImage2D>();
			return ImGui::ImageButton((ImTextureID)glImage->GetRendererID(), size, uv0, uv1, frame_padding, bg_col, tint_col);
		}
		else
		{
			Ref<VulkanImage2D> vulkanImage = image.As<VulkanImage2D>();
			const auto& imageInfo = vulkanImage->GetImageInfo();
			if (!imageInfo.ImageView)
				return false;
			auto textureID = ImGui_ImplVulkan_AddTexture(imageInfo.Sampler, imageInfo.ImageView, vulkanImage->GetDescriptor().imageLayout);
			return ImGui::ImageButton((ImTextureID)textureID, size, uv0, uv1, frame_padding, bg_col, tint_col);
		}
	}

	bool ImageButton(const Ref<Texture2D>& texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
	{
		if (RendererAPI::Current() == RendererAPIType::OpenGL)
		{
			Ref<OpenGLImage2D> image = texture->GetImage().As<OpenGLImage2D>();
			return ImGui::ImageButton((ImTextureID)image->GetRendererID(), size, uv0, uv1, frame_padding, bg_col, tint_col);
		}
		else
		{
			Ref<VulkanTexture2D> vulkanTexture = texture.As<VulkanTexture2D>();
			const VkDescriptorImageInfo& imageInfo = vulkanTexture->GetVulkanDescriptorInfo();
			auto textureID = ImGui_ImplVulkan_AddTexture(imageInfo.sampler, imageInfo.imageView, imageInfo.imageLayout);
			return ImGui::ImageButton((ImTextureID)textureID, size, uv0, uv1, frame_padding, bg_col, tint_col);
		}
	}

}