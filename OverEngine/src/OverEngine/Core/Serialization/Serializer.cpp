#include "pcheader.h"
#include "Serializer.h"

namespace OverEngine
{
	UnorderedMap<String, Serializer::EnumValues> Serializer::s_Enums;

	void Serializer::SerializeToJson(const SerializationContext& ctx,
									 void* source, nlohmann::json& out)
	{
		for (const auto& element : ctx.Elements)
		{
			void* item = (char*)source + element.Offset;
			
			switch (element.Type)
			{
			case SerializableDataType::Float:
				out[element.Name] = *(float*)item;
				break;
			case SerializableDataType::Float2:
				out[element.Name].push_back(*(float*)item);
				out[element.Name].push_back(*((float*)item + 1));
				break;
			case SerializableDataType::Float3:
				for (uint32_t i = 0; i < 3; i++)
					out[element.Name].push_back(*((float*)item + i));
				break;
			case SerializableDataType::Float4:
				for (uint32_t i = 0; i < 4; i++)
					out[element.Name].push_back(*((float*)item + i));
				break;
			case SerializableDataType::Int:
				out[element.Name] = *(int*)item;
				break;
			case SerializableDataType::UInt:
				out[element.Name] = *(uint32_t*)item;
				break;
			case SerializableDataType::Int8:
				out[element.Name] = (int)*(int8_t*)item;
				break;
			case SerializableDataType::UInt8:
				out[element.Name] = (int)*(uint8_t*)item;
				break;
			case SerializableDataType::IntEnum:
				out[element.Name] = s_Enums[element.EnumName][*(int*)item];
				break;
			case SerializableDataType::UIntEnum:
				out[element.Name] = s_Enums[element.EnumName][(int)*(uint32_t*)item];
				break;
			case SerializableDataType::Int8Enum:
				out[element.Name] = s_Enums[element.EnumName][(int)*(int8_t*)item];
				break;
			case SerializableDataType::UInt8Enum:
				out[element.Name] = s_Enums[element.EnumName][(int)*(uint8_t*)item];
				break;
			case SerializableDataType::Bool:
				out[element.Name] = *(bool*)item;
				break;
			case SerializableDataType::String:
				out[element.Name] = *(String*)item;
				break;
			default:
				OE_CORE_ASSERT(false, "Unknown SerializableDataType!");
				break;
			}
		}
	}

	void Serializer::SerializeToYaml(const SerializationContext& ctx, void* source, YAML::Node& out)
	{
		for (const auto& element : ctx.Elements)
		{
			void* item = (char*)source + element.Offset;

			switch (element.Type)
			{
			case SerializableDataType::Float:
				out[element.Name] = *(float*)item;
				break;
			case SerializableDataType::Float2:
				out[element.Name] = *(Vector2*)item;
				break;
			case SerializableDataType::Float3:
				out[element.Name] = *(Vector3*)item;
				break;
			case SerializableDataType::Float4:
				out[element.Name] = *(Vector4*)item;
				break;
			case SerializableDataType::Int:
				out[element.Name] = *(int*)item;
				break;
			case SerializableDataType::UInt:
				out[element.Name] = *(uint32_t*)item;
				break;
			case SerializableDataType::Int8:
				out[element.Name] = (int)*(int8_t*)item;
				break;
			case SerializableDataType::UInt8:
				out[element.Name] = (int)*(uint8_t*)item;
				break;
			case SerializableDataType::IntEnum:
				out[element.Name] = s_Enums[element.EnumName][*(int*)item];
				break;
			case SerializableDataType::UIntEnum:
				out[element.Name] = s_Enums[element.EnumName][(int)*(uint32_t*)item];
				break;
			case SerializableDataType::Int8Enum:
				out[element.Name] = s_Enums[element.EnumName][(int)*(int8_t*)item];
				break;
			case SerializableDataType::UInt8Enum:
				out[element.Name] = s_Enums[element.EnumName][(int)*(uint8_t*)item];
				break;
			case SerializableDataType::Bool:
				out[element.Name] = *(bool*)item;
				break;
			case SerializableDataType::String:
				out[element.Name] = *(String*)item;
				break;
			default:
				OE_CORE_ASSERT(false, "Unknown SerializableDataType!");
				break;
			}
		}
	}

	void Serializer::SerializeToYaml(const SerializationContext& ctx, void* source, YAML::Emitter& out)
	{
		for (const auto& element : ctx.Elements)
		{
			void* item = (char*)source + element.Offset;
			out << YAML::Key << element.Name << YAML::Value;

			switch (element.Type)
			{
			case SerializableDataType::Float:
				out << *(float*)item;
				break;
			case SerializableDataType::Float2:
				out << *(Vector2*)item;
				break;
			case SerializableDataType::Float3:
				out << *(Vector3*)item;
				break;
			case SerializableDataType::Float4:
				out << *(Vector4*)item;
				break;
			case SerializableDataType::Int:
				out << *(int*)item;
				break;
			case SerializableDataType::UInt:
				out << *(uint32_t*)item;
				break;
			case SerializableDataType::Int8:
				out << (int)*(int8_t*)item;
				break;
			case SerializableDataType::UInt8:
				out << (int)*(uint8_t*)item;
				break;
			case SerializableDataType::IntEnum:
				out << s_Enums[element.EnumName][*(int*)item];
				break;
			case SerializableDataType::UIntEnum:
				out << s_Enums[element.EnumName][(int)*(uint32_t*)item];
				break;
			case SerializableDataType::Int8Enum:
				out << s_Enums[element.EnumName][(int)*(int8_t*)item];
				break;
			case SerializableDataType::UInt8Enum:
				out << s_Enums[element.EnumName][(int)*(uint8_t*)item];
				break;
			case SerializableDataType::Bool:
				out << *(bool*)item;
				break;
			case SerializableDataType::String:
				out << *(String*)item;
				break;
			default:
				OE_CORE_ASSERT(false, "Unknown SerializableDataType!");
				out << YAML::Null;
				break;
			}
		}
	}

	void Serializer::DefineGlobalEnum(const String& name, const EnumValues& values)
	{
		OE_CORE_ASSERT(!GlobalEnumExists(name), "Enum '{0}' already exists!", name);
		s_Enums[name] = values;
	}

	bool Serializer::GlobalEnumExists(const String& name)
	{
		return s_Enums.find(name) != s_Enums.end();
	}

	Serializer::EnumValues& Serializer::GetGlobalEnum(const String& name)
	{
		OE_CORE_ASSERT(GlobalEnumExists(name), "Enum '{0}' doesn't exists!", name);
		return s_Enums[name];
	}

	int Serializer::GetGlobalEnumValue(const String& enumName, const String& name)
	{
		OE_CORE_ASSERT(GlobalEnumExists(enumName), "Enum '{0}' doesn't exists!", enumName);

		for (auto value : s_Enums[enumName])
			if (value.second == name)
				return value.first;
		
		OE_CORE_ASSERT(false, "Cant find enum value for {0}", name);
		return INT_MAX;
	}
}
