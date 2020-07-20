#include "stdafx.h"
#include "List.h"
#include "InternalHelpers.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Types
{
	template<class T>
	void List<T>::Init(size_t ReservedSize)
	{
		if (ArrayPtr != nullptr)
		{
			LOG_WARN("List is already initialized!");
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
			LOG_WARN("New size is too small! Nothing to Resize!");
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
	size_t List<T>::Add(const T& Element)
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
		return NumElements - 1;
	}

	template<class T>
	size_t List<T>::Append(const List<T>& Items)
	{
		if (ArrayPtr == nullptr)
		{
			Init(LIST_DEFAULT_INIT_SIZE);
		}
		for (size_t i = 0; i < Items.Size(); ++i)
		{
			Add(Items[i]);
		}
		return NumElements - 1;
	}

	template<class T>
	bool List<T>::Contains(const T& Element)
	{
		return false;
	}

	template<>
	bool List<uint32_t>::Contains(const uint32_t& Element)
	{
		// linear search is slow AF, but I'm too lazy
		// right now to implement a proper lookup
		for (size_t i = 0; i < NumElements; ++i)
		{
			if (ArrayPtr[i] == Element)
				return true;
		}
		return false;
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
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
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

	/*
	template<class T>
	const T& List<T>::operator[](const unsigned long i) const
	{
		return this->operator[]((size_t)i);
	}
	*/

	template<class T>
	T& List<T>::operator[](const size_t i)
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
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

	/*
	template<class T>
	T& List<T>::operator[](const unsigned long i)
	{
		return this->operator[]((size_t)i);
	}
	*/

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
#include "Vector3u8.h"
#include "Color.h"
#include "Animation.h"
#include "BoneFrames.h"
#include "Polygon.h"
#include "LibString.h"
#include "SoundClip.h"
#include "Chunks/MSH/SEGM.h"
#include "Chunks/MSH/MATD.h"
#include "Chunks/MSH/MODL.h"

#ifndef EXCLUDE_LVL

#include "Chunks/LVL/tex_/FMT_.h"
#include "Chunks/LVL/tex_/tex_.LVL_.h"
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/modl/modl.segm.h"
#include "Chunks/LVL/modl/modl.VBUF.h"
#include "Chunks/LVL/modl/TNAM.h"
#include "Chunks/LVL/wrld/inst.h"
#include "Chunks/LVL/tern/PTCH.h"
#include "Chunks/LVL/scr_/scr_.h"

#endif //EXCLUDE_LVL

#include "Chunks/GenericChunk.h"
#include "Wrappers/Level.h"
#include "Wrappers/SoundBank.h"
#include "DirectX/D3D9FORMAT.h"

namespace LibSWBF2
{
	using namespace Chunks;
	using namespace Types;

	template LIBSWBF2_API class Types::List<uint8_t>;
	template LIBSWBF2_API class Types::List<uint16_t>;
	template LIBSWBF2_API class Types::List<uint32_t>;
	template LIBSWBF2_API class Types::List<Vector2>;
	template LIBSWBF2_API class Types::List<Vector3>;
	template LIBSWBF2_API class Types::List<Vector3u8>;
	template LIBSWBF2_API class Types::List<Matrix3x3>;
	template LIBSWBF2_API class Types::List<Color>;
	template LIBSWBF2_API class Types::List<String>;
	template LIBSWBF2_API class Types::List<Animation>;
	template LIBSWBF2_API class Types::List<BoneFrames>;
	template LIBSWBF2_API class Types::List<Polygon>;
	template LIBSWBF2_API class Types::List<VertexWeights>;
	template LIBSWBF2_API class Types::List<TranslationFrame>;
	template LIBSWBF2_API class Types::List<RotationFrame>;
	template LIBSWBF2_API class Types::List<TerrainBufferEntry>;
	template LIBSWBF2_API class Types::List<SoundClip>;
	template LIBSWBF2_API class Types::List<MSH::SEGM>;
	template LIBSWBF2_API class Types::List<MSH::MATD>;
	template LIBSWBF2_API class Types::List<MSH::MODL>;
	template LIBSWBF2_API class Types::List<GenericBaseChunk*>;
	template LIBSWBF2_API class Types::List<D3DFORMAT>;

#ifndef EXCLUDE_LVL
	template LIBSWBF2_API class Types::List<LVL::texture::FMT_*>;
	template LIBSWBF2_API class Types::List<LVL::LVL_texture::LVL_*>;
	template LIBSWBF2_API class Types::List<LVL::modl::modl*>;
	template LIBSWBF2_API class Types::List<LVL::modl::segm*>;
	template LIBSWBF2_API class Types::List<LVL::modl::VBUF*>;
	template LIBSWBF2_API class Types::List<LVL::modl::TNAM*>;
	template LIBSWBF2_API class Types::List<LVL::wrld::inst*>;
	template LIBSWBF2_API class Types::List<LVL::terrain::PTCH*>;
	template LIBSWBF2_API class Types::List<LVL::terrain::VBUF*>;
#endif //EXCLUDE_LVL

	template LIBSWBF2_API class Types::List<Wrappers::Model>;
	template LIBSWBF2_API class Types::List<Wrappers::Segment>;
	template LIBSWBF2_API class Types::List<Wrappers::VertexWeight>;
	template LIBSWBF2_API class Types::List<Wrappers::Bone>;
	template LIBSWBF2_API class Types::List<Wrappers::Material>;
	template LIBSWBF2_API class Types::List<Wrappers::Texture>;
	template LIBSWBF2_API class Types::List<Wrappers::World>;
	template LIBSWBF2_API class Types::List<Wrappers::Terrain>;
	template LIBSWBF2_API class Types::List<Wrappers::Instance>;
	template LIBSWBF2_API class Types::List<Wrappers::Script>;
	template LIBSWBF2_API class Types::List<Wrappers::Sound>;
	template LIBSWBF2_API class Types::List<const Wrappers::Texture*>;
}