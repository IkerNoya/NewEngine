#include "collision_manager.h"

namespace Engine {
	CollisionManager::CollisionManager() {

	}

	CollisionManager::~CollisionManager() {

	}

	collisionPos CollisionManager::PartialCollision(Entity2D* entity, Entity2D* otherEntity) {
		glm::vec2 entityScale(entity->transform.scale.x, entity->transform.scale.y);
		glm::vec2 obstacleScale(otherEntity->transform.scale.x, otherEntity->transform.scale.y);
		glm::vec2 entityPos(entity->transform.position.x, entity->transform.position.y);
		glm::vec2 obstaclePos(otherEntity->transform.position.x, otherEntity->transform.position.y);
		cout << "entityPosX: " << entityPos.x << "||" << "obstaclePosX: " << obstaclePos.x << endl;
		float minX = 0.0f;
		float maxX = glm::min(entityPos.x + fabs(entityScale.x / 2), obstaclePos.x + fabs(obstacleScale.x)) - glm::max(entityPos.x - fabs(entityScale.x / 2), obstaclePos.x - fabs(obstacleScale.x));
		float overlapX = glm::max(minX, maxX);

		float minY = 0.0f;
		float maxY = glm::min(entityPos.y + fabs(entityScale.y), obstaclePos.y + fabs(obstacleScale.y)) - glm::max(entityPos.y - fabs(entityScale.y / 2), obstaclePos.y - fabs(obstacleScale.y));
		float overlapY = glm::max(minY, maxY);

		if (overlapX != 0.0f && overlapY != 0.0f) {
			if (overlapX > overlapY) {
				if (obstaclePos.y < 0 && entityPos.y < obstaclePos.y || entityPos.y > 0 && entityPos.y < obstaclePos.y) {
					std::cout << "BOTTOM" << std::endl;
					return bottomCollision;
				}
				else if (entityPos.y < 0 && entityPos.y > obstaclePos.y || entityPos.y > 0 && entityPos.y > obstaclePos.y) {
					std::cout << "TOP" << std::endl;
					return topCollision;
				}
			}
			else {
				if (entityPos.x < 0 && entityPos.x < obstaclePos.x || entityPos.x > 0 && entityPos.x < obstaclePos.x) {
					std::cout << "LEFT" << std::endl;
					return leftCollision;
				}
				else if (entityPos.x < 0 && entityPos.x > obstaclePos.x || entityPos.x > 0 && entityPos.x > obstaclePos.x) {
					std::cout << "RIGHT" << std::endl;
					return rightCollision;
				}
			}
		}
		return none;
	}

	bool CollisionManager::CheckTrigger(Entity2D* entity1, Entity2D* entity2) {
		collisionPos cPosition = PartialCollision(entity1, entity2);
		if (cPosition != none) {
			return true;
		}
		return false;
	}

	bool CollisionManager::CheckCollision(Entity2D* entity1, Entity2D* entity2, float speedEntity1) {
		collisionPos cPosition = PartialCollision(entity1, entity2);
		switch (cPosition) {
		case none:
			return false;
			break;
		case topCollision:
			entity1->transform.position = glm::vec3(entity1->transform.position.x, entity1->transform.position.y + speedEntity1, entity1->transform.position.z);
			//entity1->setPosition(entity1->transform.position.x, entity1->transform.position.y + speedEntity1, entity1->transform.position.z);
			break;
		case rightCollision:
			entity1->transform.position = glm::vec3(entity1->transform.position.x + speedEntity1, entity1->transform.position.y, entity1->transform.position.z);
			//entity1->setPosition(entity1->transform.position.x + speedEntity1, entity1->transform.position.y, entity1->transform.position.z);
			break;
		case bottomCollision:
			entity1->transform.position = glm::vec3(entity1->transform.position.x, entity1->transform.position.y - speedEntity1, entity1->transform.position.z);
			//entity1->setPosition(entity1->transform.position.x, entity1->transform.position.y - speedEntity1, entity1->transform.position.z);
			break;
		case leftCollision:
			entity1->transform.position = glm::vec3(entity1->transform.position.x - speedEntity1, entity1->transform.position.y, entity1->transform.position.z);
			//entity1->setPosition(entity1->transform.position.x - speedEntity1, entity1->transform.position.y, entity1->transform.position.z);
			break;
		default:
			break;
		}
		return false;
	}

	bool CollisionManager::ColisionWithSprite(Entity2D* entity, Sprite* sprite) {
		return true;
	}
}