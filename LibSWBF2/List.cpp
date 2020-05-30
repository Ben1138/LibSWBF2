#include "stdafx.h"
#include "List.h"
#include "Logger.h"
#include "MODL.h"

namespace LibSWBF2::Types
{
	using LibSWBF2::Logging::ELogType;
	using LibSWBF2::Chunks::Mesh::MODL;

	template<class T>
	void List<T>::Init(size_t ReservedSize)
	{
		if (ArrayPtr != nullptr)
		{
			LOG("List is already initialized!", ELogType::Warning);
			return;
		}

		if (ReservedSize <= 0)
		{
			ReservedSize = LIST_DEFAULT_INIT_SIZE;
		}

		ArrayPtr = new T[ReservedSize];
		NumElements = 0;
		MaxElements = ReservedSize;
	}

	template<class T>
	List<T>::List(size_t ReservedSize)
	{
		Init(ReservedSize);
	}

	template<class T>
	List<T>::List(const List<T>& other)
	{
		CopyFrom(other);
	}

	template<class T>
	List<T>::List(List<T>&& other)
	{
		NumElements = other.NumElements;
		MaxElements = other.MaxElements;
		ArrayPtr = other.ArrayPtr;

		other.NumElements = 0;
		other.MaxElements = 0;
		other.ArrayPtr = nullptr;
	}

	template<class T>
	List<T>::~List()
	{
		Clear();
	}

	template<class T>
	void List<T>::CopyFrom(const List<T>& other)
	{
		Clear();
		if (other.NumElements > 0)
		{
			NumElements = other.NumElements;
			MaxElements = NumElements;
			ArrayPtr = new T[NumElements];
			for (size_t i = 0; i < NumElements; ++i)
			{
				ArrayPtr[i] = other.ArrayPtr[i];
			}
		}
	}
	
	template<class T>
	size_t List<T>::Size() const
	{
		return NumElements;
	}

	template<class T>
	void List<T>::Resize(size_t NewMaxSize)
	{
		if (ArrayPtr == nullptr)
		{
			Init(NewMaxSize);
			return;
		}

		if (NewMaxSize <= NumElements)
		{
			LOG("New size is too small! Nothing to Resize!", ELogType::Warning);
			return;
		}

		T* newArray = new T[NewMaxSize];
		for (size_t i = 0; i < NumElements; ++i)
		{
			newArray[i] = ArrayPtr[i];
		}
		delete[] ArrayPtr;
		ArrayPtr = newArray;

		MaxElements = NewMaxSize;
	}

	template<class T>
	void List<T>::Add(const T& Element)
	{
		if (ArrayPtr == nullptr)
		{
			Init(LIST_DEFAULT_INIT_SIZE);
		}
		if (NumElements >= MaxElements || ArrayPtr == nullptr)
		{
			Resize(MaxElements * 2);
		}

		ArrayPtr[NumElements++] = Element;
	}

	template<class T>
	T& List<T>::Emplace()
	{
		if (ArrayPtr == nullptr)
		{
			Init(LIST_DEFAULT_INIT_SIZE);
		}
		if (NumElements >= MaxElements || ArrayPtr == nullptr)
		{
			Resize(MaxElements * 2);
		}

		return ArrayPtr[NumElements++];
	}
	
	template<class T>
	List<T>& List<T>::operator=(const List<T>& other)
	{
		CopyFrom(other);
		return *this;
	}

	template<class T>
	const T& List<T>::operator[](const size_t i) const
	{
		if (i >= NumElements)
		{
			string msg = "Index " + std::to_string(i) + " is out of bounds " + std::to_string(NumElements) + "!";
			LOG(msg, ELogType::Error);
			throw std::exception(msg.c_str());
		}
		return ArrayPtr[i];
	}

	template<class T>
	const T& List<T>::operator[](const int i) const
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	const T& List<T>::operator[](const long i) const
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	const T& List<T>::operator[](const unsigned int i) const
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	const T& List<T>::operator[](const unsigned long i) const
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	T& List<T>::operator[](const size_t i)
	{
		if (i >= NumElements)
		{
			string msg = "Index " + std::to_string(i) + " is out of bounds " + std::to_string(NumElements) + "!";
			LOG(msg, ELogType::Error);
			throw std::exception(msg.c_str());
		}
		return ArrayPtr[i];
	}

	template<class T>
	T& List<T>::operator[](const int i)
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	T& List<T>::operator[](const long i)
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	T& List<T>::operator[](const unsigned int i)
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	T& List<T>::operator[](const unsigned long i)
	{
		return this->operator[]((size_t)i);
	}

	template<class T>
	void List<T>::Clear()
	{
		if (ArrayPtr != nullptr)
		{
			delete[] ArrayPtr;
			ArrayPtr = nullptr;
		}

		NumElements = 0;
		MaxElements = 0;
	}

	template<class T>
	T* List<T>::GetArrayPtr() const
	{
		return ArrayPtr;
	}
}



// ============================================================
// ============== Explicit List instantiations ================
// ============================================================

#include "Vector4.h"
#include "Animation.h"
#include "BoneFrames.h"
#include "Polygon.h"
#include "SEGM.h"
#include "MATD.h"
#include "MODL.h"
#include "FMT_.h"
#include "LVL_.h"
#include "GenericChunk.h"
#include "D3D9Types.h"

namespace LibSWBF2
{
	using namespace Types;
	using namespace Chunks;
	using namespace Chunks::Mesh;

	template LIBSWBF2_EXP class List<uint8_t>;
	template LIBSWBF2_EXP class List<uint16_t>;
	template LIBSWBF2_EXP class List<uint32_t>;
	template LIBSWBF2_EXP class List<Vector2>;
	template LIBSWBF2_EXP class List<Vector3>;
	template LIBSWBF2_EXP class List<Animation>;
	template LIBSWBF2_EXP class List<BoneFrames>;
	template LIBSWBF2_EXP class List<Polygon>;
	template LIBSWBF2_EXP class List<VertexWeights>;
	template LIBSWBF2_EXP class List<TranslationFrame>;
	template LIBSWBF2_EXP class List<RotationFrame>;
	template LIBSWBF2_EXP class List<SEGM>;
	template LIBSWBF2_EXP class List<MATD>;
	template LIBSWBF2_EXP class List<MODL>;
	template LIBSWBF2_EXP class List<GenericChunk*>;
	template LIBSWBF2_EXP class List<D3DFORMAT>;
	template LIBSWBF2_EXP class List<LVL::FMT_*>;
	template LIBSWBF2_EXP class List<LVL::LVL_*>;
}