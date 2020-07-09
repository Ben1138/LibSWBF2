#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	struct LIBSWBF2_API RawData : public GenericChunk<Header>
	{
		~RawData();

	private:
		uint8_t* p_Data = nullptr;

	public:
		// returns false if there is no data
		bool GetData(uint8_t*& data, size_t& size);

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}