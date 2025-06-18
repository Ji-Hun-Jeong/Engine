#include "pch.h"
#include "SwiftPhantom.h"
#include <Collision/src/Collision/RigidBody.h>

namespace Game
{
	void SwiftPhantom::Cast()
	{
		auto& RigidBody = RefPlayer.GetRigidBody();
		//RigidBody.AddForce(Vector2(1.0f, 0.1f));
		RigidBody.AddVelocity(Vector2(1.0f, 0.3f));
	}
}

