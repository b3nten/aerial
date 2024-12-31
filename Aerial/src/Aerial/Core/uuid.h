#pragma once
#include <cstdint>
#include <random>

namespace aerial {

	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	class AERIAL_API uuid
	{
	public:
		uuid() : m_value(CreateInt()) {}
		explicit uuid(const uint64_t uuid) : m_value(uuid) {}
		uuid(const uuid&) = default;
		explicit operator uint64_t() const { return m_value; }
		bool operator==(const uuid& other) const { return m_value == other.m_value; }

		uint64_t static CreateInt() { return s_UniformDistribution(s_Engine); }
	private:
		uint64_t m_value;
	};
}

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<aerial::uuid>
	{
		std::size_t operator()(const aerial::uuid& uuid) const noexcept
		{
			return static_cast<uint64_t>(uuid);
		}
	};

}