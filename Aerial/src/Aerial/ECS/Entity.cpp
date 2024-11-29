#include "./Entity.h"

namespace Aerial
{
	Entity::Entity(entt::registry* registry) : m_EnttID(registry->create()), m_Registry(registry)
	{
		m_ID = registry->emplace<UUID>(m_EnttID);
	}
	Entity::Entity(entt::registry* registry, UUID id) : m_EnttID(registry->create()), m_Registry(registry)
	{
		m_ID = registry->emplace<UUID>(m_EnttID, id);
	}
	Entity::Entity(entt::registry* registry, entt::entity entityID) : m_EnttID(entityID), m_Registry(registry)
	{
		m_ID = registry->emplace<UUID>(m_EnttID);
	}
	Entity::Entity(entt::registry* registry, entt::entity entityID, UUID id) : m_EnttID(entityID), m_Registry(registry)
	{
		m_ID = registry->emplace<UUID>(m_EnttID, id);
	}
}