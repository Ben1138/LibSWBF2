#pragma once
#include "BaseChunk.h"
#include "HeaderNames.h"

namespace LibSWBF2::Chunks
{
	struct LIBSWBF2_API GenericBaseChunk : public BaseChunk
	{
		GenericBaseChunk() = default;
		~GenericBaseChunk();

		String GetHeaderName() const;
		GenericBaseChunk* GetParent() const;
		const List<GenericBaseChunk*>& GetChildren() const;

		virtual String ToString();

	public:
		template<class ChildType>
		void ReadChildExplicit(GenericBaseChunk* parent, FileReader& stream, ChildType*& memberPtr)
		{
			ChildType* chunk = new ChildType();
			memberPtr = chunk;
			parent->m_Children.Add(chunk);
			chunk->m_Parent = parent;

			// Important: start reading AFTER parent and child have been set!
			chunk->ReadFromStream(stream);
		}

		void ReadGenerics(FileReader& stream);

	private:
		GenericBaseChunk* m_Parent = nullptr;
		List<GenericBaseChunk*> m_Children;
	};

	template<uint32_t Header>
	struct LIBSWBF2_API GenericChunk : public GenericBaseChunk
	{
	protected:
		void Check(FileReader& stream);

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};

	// do not perform any checks on this one
	struct LIBSWBF2_API GenericChunkNC : public GenericChunk<0> {};


#define READ_CHILD(stream, member) ReadChildExplicit(this, stream, member);
#define READ_CHILD_GENERIC(stream) { GenericChunkNC* genericChild; READ_CHILD(stream, genericChild); }
}