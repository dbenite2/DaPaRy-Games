// Property of DaPaRy Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamageable.generated.h"

/**
 * The IIDamageable interface provides a standardized approach to applying damage to actors
 * within the game environment. It defines a contract for damageable objects, ensuring that any
 * actor implementing this interface will possess the ability to respond to damage in a consistent manner.
 */

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDamageable : public UInterface {
	GENERATED_BODY()
};

/**
 * Implementing this interface allows an actor to be considered 'damageable,' enabling interaction
 * with game systems that inflict damage, such as weapons or environmental hazards.
 */
class PROJECTSAILOR_API IIDamageable {
	GENERATED_BODY()

public:
	virtual void TakeDamage();
};

/**
 * Implementation details:
 * - The 'TakeDamage' function must be implemented by any class that adopts this interface to define
 *   how the object responds when damage is inflicted upon it.
 * - This interface facilitates a flexible damage system where objects can have diverse reactions to being
 *   damaged, depending on their specific implementation of the 'TakeDamage' method.
 */
