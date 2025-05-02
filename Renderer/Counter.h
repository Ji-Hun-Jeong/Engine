#pragma once

namespace Graphics
{
	class Counter
	{
	public:
		Counter() = default;
		virtual ~Counter() = default;

	public:
		void AddRef() { RefCount += 1; }
		void Release()
		{
			RefCount -= 1;
			if (RefCount == 0)
				delete this;
		}

	protected:
		UINT RefCount = 0;

	};
}


