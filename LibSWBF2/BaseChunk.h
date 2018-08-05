#pragma once

namespace LibSWBF2
{
	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();

		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);

	private:
		char Header[4];
		int Size;
	};
}