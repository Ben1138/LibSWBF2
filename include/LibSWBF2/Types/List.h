#pragma once

namespace LibSWBF2::Types
{
	template<class T> 
	class LIBSWBF2_API List
	{
	private:
		const static int LIST_DEFAULT_INIT_SIZE = 8;

		T* ArrayPtr = nullptr;
		size_t NumElements = 0;
		size_t MaxElements = 0;

		void Init(size_t ReservedSize);
		void CopyFrom(const List<T>& other);

	public:
		List() = default;
		List(size_t ReservedSize);
		List(const List<T>& other);
		List(List<T>&& other);
		virtual ~List();

		size_t Size() const;
		void Resize(size_t NewSize);

		// returns index of added element
		size_t Add(const T& Element);

		// returns index of added element
		size_t Add(T&& Element);

		// returns index of last added element
		size_t Append(const List<T>& Items);

		// needs type-wise implementations!
		virtual bool Contains(const T& Element);

		T& Emplace();

		List<T>& operator=(const List<T>& other);
		List<T>& operator=(List<T>&& other);

//TEMPFIX: Clang is very stubborn with this one, 
#ifdef __clang__
		const T& operator[](const unsigned long i) const;
#else
		const T& operator[](const int8_t i) const;
		const T& operator[](const uint8_t i) const;
		const T& operator[](const int16_t i) const;
		const T& operator[](const uint16_t i) const;
		const T& operator[](const int32_t i) const;
		const T& operator[](const uint32_t i) const;
		const T& operator[](const int64_t i) const;
		const T& operator[](const uint64_t i) const;
#endif

#ifdef __clang__
		T& operator[](const unsigned long i);
#else
		T& operator[](const int8_t i);
		T& operator[](const uint8_t i);
		T& operator[](const int16_t i);
		T& operator[](const uint16_t i);
		T& operator[](const int32_t i);
		T& operator[](const uint32_t i);
		T& operator[](const int64_t i);
		T& operator[](const uint64_t i);
#endif


		// TODO: Remove(item) methods

		void Clear();
		T* GetArrayPtr() const;
	};

	template <> //GCC complaint 
	bool List<uint32_t>::Contains(const uint32_t& Element);
}