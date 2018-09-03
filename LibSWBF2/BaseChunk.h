#pragma once

namespace LibSWBF2::Chunks
{
	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();
		static int32_t PeekHeader(ifstream& stream);

		// These MUST be overridden in subclasses!
		virtual void RefreshSize();
		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);

		int32_t GetHeader();
		int32_t GetSize();

	protected:
		// since these variables are critical
		// we should keep them protected
		int32_t Header;
		int32_t Size;
	};
}