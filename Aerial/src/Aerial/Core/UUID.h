#pragma once
#include <cstdint>
#include <random>

namespace Aerial {

	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	class AERIAL_API UUID
	{
	public:
		UUID() : m_UUID(CreateInt()) {}
		explicit UUID(const uint64_t uuid) : m_UUID(uuid) {}
		UUID(const UUID&) = default;
		explicit operator uint64_t() const { return m_UUID; }
		bool operator==(const UUID& other) const { return m_UUID == other.m_UUID; }

		uint64_t static CreateInt() { return s_UniformDistribution(s_Engine); }
	private:
		uint64_t m_UUID;
	};
}

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<Aerial::UUID>
	{
		std::size_t operator()(const Aerial::UUID& uuid) const noexcept
		{
			return static_cast<uint64_t>(uuid);
		}
	};

}