import os
import sys
import subprocess
from pathlib import Path
import Utils
from io import BytesIO
from urllib.request import urlopen
from zipfile import ZipFile

VULKAN_SDK = os.environ.get('VULKAN_SDK')
VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.3.261.1/windows/vulkan_sdk.exe'
KEY_VULKAN_VERSION = '1.3.261.1'
VULKAN_SDK_EXE_PATH = 'KeyEngine/vendor/VulkanSDK/VulkanSDK.exe'



def InstallVulkanSDK():
    print('Downloading {} to {}'.format(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH))
    Utils.DownloadFile(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
    print("Done!")
    print("Running Vulkan SDK installer...")
    os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
    print("Re-run this script after installation")


def InstallVulkanPrompt():
    print("Would you like to install the Vulkan SDK?")
    install = Utils.YesOrNo()
    if (install):
        InstallVulkanSDK()
        quit()


def CheckVulkanSDK():
    if (VULKAN_SDK is None):
        print("You don't have the Vulkan SDK installed!")
        InstallVulkanPrompt()
        return False
    elif (KEY_VULKAN_VERSION not in VULKAN_SDK):
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"You don't have the correct Vulkan SDK version! (KeyEngine requires {KEY_VULKAN_VERSION})")
        InstallVulkanPrompt()
        return False

    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True


VulkanSDKDebugLibsURL = 'https://files.lunarg.com/SDK-1.2.170.0/VulkanSDK-1.2.170.0-DebugLibs.zip'
OutputDirectory = VULKAN_SDK
TempZipFile = f"{OutputDirectory}/VulkanSDK.zip"


def CheckVulkanSDKDebugLibs():
    shadercdLib = Path(f"{OutputDirectory}/Lib/shaderc_sharedd.lib")
    if (not shadercdLib.exists()):
        print(f"No Vulkan SDK debug libs found. (Checked {shadercdLib})")
        print("Downloading", VulkanSDKDebugLibsURL)
        with urlopen(VulkanSDKDebugLibsURL) as zipresp:
            with ZipFile(BytesIO(zipresp.read())) as zfile:
                zfile.extractall(OutputDirectory)

    return True