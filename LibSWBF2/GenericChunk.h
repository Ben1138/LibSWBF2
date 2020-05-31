#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks
{
	struct LIBSWBF2_EXP GenericChunk : public BaseChunk
	{
		GenericChunk() = default;
		~GenericChunk();

		String GetHeaderName() const;
		GenericChunk* GetParent() const;
		const List<GenericChunk*>& GetChildren() const;

		virtual String ToString();

	protected:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		template<class T>
		void ReadChildExplicit(FileReader& stream, T*& memberPtr, ChunkHeader expectedHeader)
		{
			T* chunk = new T();
			memberPtr = chunk;
			m_Children.Add(chunk);
			chunk->m_Parent = this;

			// Important: start reading AFTER parent and child have been set!
			chunk->ReadFromStream(stream);
			ASSERT_HEADER(chunk->GetHeader(), expectedHeader);
		}

	private:
		GenericChunk* m_Parent = nullptr;
		List<GenericChunk*> m_Children;
		void* m_data = nullptr;
	};
}