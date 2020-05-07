#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks
{
	struct LIBSWBF2_EXP GenericChunk : public BaseChunk
	{
		GenericChunk() = default;
		~GenericChunk() = default;

		string GetHeaderName() const;
		const List<GenericChunk>& GetChildren() const;

	protected:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		//GenericChunk* m_parent = nullptr;
		List<GenericChunk> m_children;
		void* m_data = nullptr;
	};
}