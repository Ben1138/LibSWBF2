#pragma once

using namespace System;

namespace LibSWBF2NET 
{
	template<class T>
	public ref class ManagedObject
	{
	private:
		T* Instance = nullptr;

	protected:
		T* GetInstance()
		{
			return Instance;
		}

	public:
		ManagedObject(T* instance)
			: Instance(instance)
		{
		}
		virtual ~ManagedObject()
		{
			if (Instance != nullptr)
			{
				delete Instance;
			}
		}

		// Managed destructor (GC call)
		!ManagedObject()
		{
			if (Instance != nullptr)
			{
				delete Instance;
			}
		}
	};
}
