#include "pch.h"
#include "List.h"
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
	void List<T>::Resize(size_t NewSize)
	{
		if (ArrayPtr == nullptr)
		{
			Init(NewSize);
			return;
		}

		NumElements = glm::min(NewSize, NumElements);
		T* newArray = new T[NewSize];
		for (size_t i = 0; i < NumElements; ++i)
		{
			newArray[i] = ArrayPtr[i];
		}
		delete[] ArrayPtr;
		ArrayPtr = newArray;

		MaxElements = NewSize;
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
	size_t List<T>::Add(T&& Element)
	{
		if (ArrayPtr == nullptr)
		{
			Init(LIST_DEFAULT_INIT_SIZE);
		}
		if (NumElements >= MaxElements || ArrayPtr == nullptr)
		{
			Resize(MaxElements * 2);
		}

		ArrayPtr[NumElements++] = std::move(Element);
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
	List<T>& List<T>::operator=(List<T>&& other)
	{
		NumElements = other.NumElements;
		MaxElements = other.MaxElements;

		if (ArrayPtr != nullptr)
			delete[] ArrayPtr;

		ArrayPtr = other.ArrayPtr;

		other.NumElements = 0;
		other.MaxElements = 0;
		other.ArrayPtr = nullptr;

		return *this;
	}


//TEMPFIX: see header
#ifdef __clang__
	template<class T>
	const T& List<T>::operator[](const unsigned long i) const
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}
#else
	
	template<class T>
	const T& List<T>::operator[](const int8_t i) const
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}


	template<class T>
	const T& List<T>::operator[](const uint8_t i) const
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	const T& List<T>::operator[](const int16_t i) const
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	const T& List<T>::operator[](const uint16_t i) const
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	const T& List<T>::operator[](const int32_t i) const
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	const T& List<T>::operator[](const uint32_t i) const
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	const T& List<T>::operator[](const int64_t i) const
	{
		if (i < 0 || (size_t)i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}


	template<class T>
	const T& List<T>::operator[](const uint64_t i) const
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}
#endif


#ifdef __clang__
	template<class T>
	T& List<T>::operator[](const unsigned long i)
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}
#else


	template<class T>
	T& List<T>::operator[](const int8_t i)
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	
	template<class T>
	T& List<T>::operator[](const uint8_t i)
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}
	

	template<class T>
	T& List<T>::operator[](const int16_t i)
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	T& List<T>::operator[](const uint16_t i)
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	T& List<T>::operator[](const int32_t i)
	{
		if (i < 0 || i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	T& List<T>::operator[](const uint32_t i)
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	
	template<class T>
	T& List<T>::operator[](const int64_t i)
	{
		if (i < 0 || (size_t)i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}

	template<class T>
	T& List<T>::operator[](const uint64_t i)
	{
		if (i >= NumElements)
		{
			THROW("Index {} is out of bounds {}!", i, NumElements);
		}
		return ArrayPtr[i];
	}
#endif
	

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
#include "Color4.h"
#include "Color4u8.h"
#include "Animation.h"
#include "BoneFrames.h"
#include "Polygon.h"
#include "LibString.h"
#include "SoundClip.h"
#include "LocalizeEntry.h"
#include "Chunks/MSH/SEGM.h"
#include "Chunks/MSH/MATD.h"
#include "Chunks/MSH/MODL.h"
#include "WorldAnimationKey.h"

#include "Chunks/LVL/common/SCOP.h"
#include "Chunks/LVL/common/DATA.h"
#include "Chunks/LVL/common/PROP.h"
#include "Chunks/LVL/coll/TREE.NODE.h"
#include "Chunks/LVL/coll/TREE.LEAF.h"
#include "Chunks/LVL/prim/prim.h"
#include "Wrappers/Config.h"

#include "Chunks/LVL/zaf_/TNOJ.h"

#include "Chunks/LVL/tex_/FMT_.h"
#include "Chunks/LVL/tex_/tex_.LVL_.h"
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/modl/modl.segm.h"
#include "Chunks/LVL/modl/modl.VBUF.h"
#include "Chunks/LVL/modl/TNAM.h"
#include "Chunks/LVL/wrld/inst.h"
#include "Chunks/LVL/wrld/regn.h"
#include "Chunks/LVL/wrld/anim.h"
#include "Chunks/LVL/wrld/anmg.h"
#include "Chunks/LVL/wrld/anmh.h"
#include "Chunks/LVL/tern/PTCH.h"
#include "Chunks/LVL/scr_/scr_.h"

#include "Chunks/LVL/sound/Stream.h"
#include "Chunks/LVL/sound/StreamData.h"
#include "Chunks/LVL/sound/SampleBank.h"



#include "Chunks/RawData.h"

#include "Chunks/GenericChunk.h"

#include "Chunks/LVL/wrld/WorldAnimKeyChunk.h"

#include "Wrappers/Wrappers.h"

#include "DirectX/D3D9FORMAT.h"

namespace LibSWBF2
{
	using namespace Chunks;
	using namespace Types;

	template class LIBSWBF2_API Types::List<const char*>;
	template class LIBSWBF2_API Types::List<uint8_t>;
	template class LIBSWBF2_API Types::List<uint16_t>;
	template class LIBSWBF2_API Types::List<uint32_t>;
	template class LIBSWBF2_API Types::List<float_t>;
	template class LIBSWBF2_API Types::List<Vector2>;
	template class LIBSWBF2_API Types::List<Vector3>;
	template class LIBSWBF2_API Types::List<Vector3u8>;
	template class LIBSWBF2_API Types::List<Matrix3x3>;
	template class LIBSWBF2_API Types::List<Color4>;
	template class LIBSWBF2_API Types::List<Color4u8>;
	template class LIBSWBF2_API Types::List<String>;
	template class LIBSWBF2_API Types::List<Animation>;
	template class LIBSWBF2_API Types::List<WorldAnimationKey>;

	template class LIBSWBF2_API Types::List<BoneFrames>;
	template class LIBSWBF2_API Types::List<Polygon>;
	template class LIBSWBF2_API Types::List<VertexWeights>;
	template class LIBSWBF2_API Types::List<TranslationFrame>;
	template class LIBSWBF2_API Types::List<RotationFrame>;
	template class LIBSWBF2_API Types::List<TerrainBufferEntry>;
	template class LIBSWBF2_API Types::List<SoundClip>;
	template class LIBSWBF2_API Types::List<LocalizeEntry>;
	template class LIBSWBF2_API Types::List<MSH::SEGM>;
	template class LIBSWBF2_API Types::List<MSH::MATD>;
	template class LIBSWBF2_API Types::List<MSH::MODL>;
	template class LIBSWBF2_API Types::List<GenericBaseChunk*>;
	template class LIBSWBF2_API Types::List<D3DFORMAT>;

	template class LIBSWBF2_API Types::List<LibSWBF2::Chunks::LVL::texture::FMT_*>;
	template class LIBSWBF2_API Types::List<LibSWBF2::Chunks::LVL::LVL_texture::LVL_*>;
	template class LIBSWBF2_API Types::List<LVL::modl::modl*>;
	template class LIBSWBF2_API Types::List<LVL::modl::segm*>;
	template class LIBSWBF2_API Types::List<LVL::modl::VBUF*>;
	template class LIBSWBF2_API Types::List<LVL::modl::TNAM*>;
	template class LIBSWBF2_API Types::List<LVL::wrld::inst*>;
    template class LIBSWBF2_API Types::List<LVL::wrld::regn*>;
   	template class LIBSWBF2_API Types::List<LVL::wrld::anmg*>;
   	template class LIBSWBF2_API Types::List<LVL::wrld::anmh*>;
    template class LIBSWBF2_API Types::List<LVL::wrld::anim*>;
    template class LIBSWBF2_API Types::List<LVL::wrld::POSK*>;
    template class LIBSWBF2_API Types::List<LVL::wrld::ROTK*>;
	template class LIBSWBF2_API Types::List<LVL::terrain::PTCH*>;
	template class LIBSWBF2_API Types::List<LVL::terrain::VBUF*>;

    template class LIBSWBF2_API Types::List<LibSWBF2::Chunks::LVL::config::DATA_CONFIG*>;

    template class LIBSWBF2_API Types::List<LVL::common::DATA*>;
    template class LIBSWBF2_API Types::List<LVL::common::SCOP*>;
    template class LIBSWBF2_API Types::List<LVL::common::PROP*>;

    template class LIBSWBF2_API Types::List<LVL::coll::TREE_NODE*>;
    template class LIBSWBF2_API Types::List<LVL::coll::TREE_LEAF*>;

    template class LIBSWBF2_API Types::List<LVL::prim::MASK *>;
    template class LIBSWBF2_API Types::List<LVL::wrld::XFRM *>;
    template class LIBSWBF2_API Types::List<LVL::prim::DATA_PRIM *>;
    
    template class LIBSWBF2_API Types::List<STR<"NAME"_m> *>;
    template class LIBSWBF2_API Types::List<STR<"PRNT"_m> *>;

    template class LIBSWBF2_API Types::List<STRMULT<"ANIM"_m> *>;

    template class LIBSWBF2_API Types::List<LVL::animation::TNOJ *>;


    template class LIBSWBF2_API Types::List<LVL::sound::Stream *>;
    template class LIBSWBF2_API Types::List<LVL::sound::StreamData *>;
    template class LIBSWBF2_API Types::List<LVL::sound::SampleBank *>;


	template class LIBSWBF2_API Types::List<Wrappers::Model>;
	template class LIBSWBF2_API Types::List<Wrappers::Segment>;
	template class LIBSWBF2_API Types::List<Wrappers::Segment *>;
	template class LIBSWBF2_API Types::List<Wrappers::Instance *>;
	template class LIBSWBF2_API Types::List<Wrappers::World *>;
	template class LIBSWBF2_API Types::List<Wrappers::CollisionPrimitive*>;
	template class LIBSWBF2_API Types::List<Wrappers::AnimationBank*>;
	template class LIBSWBF2_API Types::List<Wrappers::AnimationSkeleton*>;
	template class LIBSWBF2_API Types::List<Wrappers::Config*>;


	template class LIBSWBF2_API Types::List<const Wrappers::Instance*>;
	template class LIBSWBF2_API Types::List<const Wrappers::World*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Segment*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Texture*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Model*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Terrain*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Localization*>;
	template class LIBSWBF2_API Types::List<const Wrappers::CollisionPrimitive*>;
	template class LIBSWBF2_API Types::List<const Wrappers::AnimationBank*>;
	template class LIBSWBF2_API Types::List<const Wrappers::AnimationSkeleton*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Script*>;
	template class LIBSWBF2_API Types::List<const Wrappers::Config*>;


	template class LIBSWBF2_API Types::List<Wrappers::VertexWeight>;
	template class LIBSWBF2_API Types::List<Wrappers::Bone>;
	template class LIBSWBF2_API Types::List<Wrappers::Joint>;
	template class LIBSWBF2_API Types::List<Wrappers::Material>;
	template class LIBSWBF2_API Types::List<Wrappers::Texture>;
	template class LIBSWBF2_API Types::List<Wrappers::World>;
	template class LIBSWBF2_API Types::List<Wrappers::Terrain>;
	template class LIBSWBF2_API Types::List<Wrappers::Instance>;
	template class LIBSWBF2_API Types::List<Wrappers::Region>;
	template class LIBSWBF2_API Types::List<Wrappers::WorldAnimation>;
	template class LIBSWBF2_API Types::List<Wrappers::WorldAnimationGroup>;
	template class LIBSWBF2_API Types::List<Wrappers::WorldAnimationHierarchy>;
	template class LIBSWBF2_API Types::List<Wrappers::Script>;
	template class LIBSWBF2_API Types::List<Wrappers::Sound>;
	template class LIBSWBF2_API Types::List<Wrappers::Localization>;
	template class LIBSWBF2_API Types::List<Wrappers::EntityClass>;
	template class LIBSWBF2_API Types::List<Wrappers::CollisionPrimitive>;
	template class LIBSWBF2_API Types::List<Wrappers::AnimationBank>;
	template class LIBSWBF2_API Types::List<Wrappers::AnimationSkeleton>;
	template class LIBSWBF2_API Types::List<Wrappers::Config>;

	template class LIBSWBF2_API Types::List<Wrappers::Field>;
	template class LIBSWBF2_API Types::List<const Wrappers::Field *>;

}

