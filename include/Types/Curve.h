#pragma once
#include "req.h"
#include "Types/List.h"


namespace LibSWBF2::Types
{
	using Types::List;


	#pragma pack(push,1)
	template<typename T>
	struct LIBSWBF2_API Key 
	{
		T time;
		float_t value;
	};
	#pragma pack(pop)


	template<typename T>
	struct LIBSWBF2_API Curve
	{
		const List<T>& GetIndices() const
		{
			return m_Indices;
		}

		const List<float_t>& GetValues() const
		{
			return m_Values;
		}

		const List<Key<T>> GetKeys() const
		{
			const size_t& iSize = m_Indices.Size();
			const size_t& vSize = m_Values.Size();

			uint32_t size = iSize < vSize ? iSize : vSize;

			List<Key<T>> keys;
			keys.Resize(size);

			for (uint16_t i = 0; i < size; i++)
			{
				keys.Add({ m_Indices[i], m_Values[i] });
			}

			return keys;
		}

		Curve(List<T>&& inds, List<float_t>&& vals)
		{
			m_Indices = inds;
			m_Values = vals;
		}

		Curve() = default;


	private:
		List<T> m_Indices;
		List<float_t> m_Values; 
	};
}