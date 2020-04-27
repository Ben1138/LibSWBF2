#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks
{
	using std::vector;

	struct LIBSWBF2_EXP GenericChunk : public BaseChunk
	{
		GenericChunk() = default;
		~GenericChunk() = default;

		string GetHeaderName() const;
		const vector<GenericChunk>& GetChildren() const;

	protected:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

	private:
		//GenericChunk* m_parent = nullptr;
		vector<GenericChunk> m_children;
		void* m_data = nullptr;
	};
}