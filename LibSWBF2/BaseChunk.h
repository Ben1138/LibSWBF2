#pragma once
#include "stdafx.h"

namespace LibSWBF2
{
	struct BaseChunk
	{
	private:
		char Header[4];
		int Size;

	public:
		BaseChunk();
		~BaseChunk();

		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);

		friend ofstream& operator<<(ofstream& stream, const BaseChunk& chunk);
		friend ifstream& operator>>(ifstream& stream, BaseChunk& chunk);
	};
}