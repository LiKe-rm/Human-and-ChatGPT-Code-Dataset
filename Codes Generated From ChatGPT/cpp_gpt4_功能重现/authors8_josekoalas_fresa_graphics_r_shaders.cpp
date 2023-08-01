#include <iostream>
#include <fstream>
#include <vector>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

std::vector<uint32_t> readSPIRVFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open SPIR-V file");
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if (fileSize % sizeof(uint32_t) != 0)
    {
        throw std::runtime_error("Invalid SPIR-V file size");
    }

    std::vector<uint32_t> spirvData(fileSize / sizeof(uint32_t));
    file.read(reinterpret_cast<char *>(spirvData.data()), fileSize);

    return spirvData;
}

spirv_cross::CompilerGLSL createCompiler(const std::vector<uint32_t> &spirvData)
{
    return spirv_cross::CompilerGLSL(spirvData);
}

std::vector<VkDescriptorSetLayoutBinding> getDescriptorSetLayoutBindings(
    spirv_cross::CompilerGLSL &compiler)
{
    std::vector<VkDescriptorSetLayoutBinding> bindings;

    spirv_cross::ShaderResources resources = compiler.get_shader_resources();

    for (const auto &resource : resources.uniform_buffers)
    {
        VkDescriptorSetLayoutBinding binding = {};
        binding.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        binding.descriptorCount = 1;
        binding.stageFlags = compiler.get_execution_model() == spv::ExecutionModelVertex
                                 ? VK_SHADER_STAGE_VERTEX_BIT
                                 : VK_SHADER_STAGE_FRAGMENT_BIT;
        bindings.push_back(binding);
    }

    for (const auto &resource : resources.storage_buffers)
    {
        VkDescriptorSetLayoutBinding binding = {};
        binding.binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
        binding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        binding.descriptorCount = 1;
        binding.stageFlags = compiler.get_execution_model() == spv::ExecutionModelVertex
                                 ? VK_SHADER_STAGE_VERTEX_BIT
                                 : VK_SHADER_STAGE_FRAGMENT_BIT;
        bindings.push_back(binding);
    }

    return bindings;
}

size_t getBufferSize(spirv_cross::CompilerGLSL &compiler, const spirv_cross::Resource &resource)
{
    spirv_cross::SPIRType type = compiler.get_type(resource.base_type_id);
    return compiler.get_declared_struct_size(type);
}

int main()
{
    try
    {
        std::vector<uint32_t> spirvData = readSPIRVFile("path/to/your/spirv/file.spv");
        spirv_cross::CompilerGLSL compiler = createCompiler(spirvData);
        std::vector<VkDescriptorSetLayoutBinding> bindings = getDescriptorSetLayoutBindings(compiler);

        spirv_cross::ShaderResources resources = compiler.get_shader_resources();

        for (const auto &resource : resources.uniform_buffers)
        {
            size_t bufferSize = getBufferSize(compiler, resource);
            std::cout << "Uniform buffer '" << resource.name << "' has size " << bufferSize << " bytes\n";
        }

        for (const auto &resource : resources.storage_buffers)
        {
            size_t bufferSize = getBufferSize(compiler,resource);
            std::cout << "Storage buffer '" << resource.name << "' has size " << bufferSize << " bytes\n";
        }

            std::cout << "Descriptor Set Layout Bindings:\n";
        for (const auto &binding : bindings)
        {
            const char *stage = binding.stageFlags == VK_SHADER_STAGE_VERTEX_BIT ? "vertex" : "fragment";
            const char *type = binding.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
                                   ? "uniform buffer"
                                   : "storage buffer";
    
            std::cout << "  Binding " << binding.binding << ": " << type << " in " << stage << " shader\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
