#include "pch.h"
#include "Collider.h"

namespace Collision
{
	Collider::~Collider()
	{
		
	}

	bool IsCollision(RectCollider* _Collider1, RectCollider* _Collider2) 
	{
		const Vector3& Pos1 = _Collider1->GetPosition(); 
		const Vector3& Pos2 = _Collider2->GetPosition(); 
		const Vector3& Size1 = _Collider1->GetSize();    
		const Vector3& Size2 = _Collider2->GetSize();    

		return (std::abs(Pos1.x - Pos2.x) < (Size1.x / 2 + Size2.x / 2)) &&
			(std::abs(Pos1.y - Pos2.y) < (Size1.y / 2 + Size2.y / 2));
	}

	bool IsCollision(RectCollider* _Collider1, CircleCollider* _Collider2)
	{
		return false;
	}
	bool IsCollision(CircleCollider* _Collider1, CircleCollider* _Collider2)
	{
		return false;
	}
}