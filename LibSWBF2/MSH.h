#pragma once
#include "stdafx.h"
#include "BaseChunk.h"
#include "SHVO.h"

namespace LibSWBF2
{
	struct MSH : public BaseChunk
	{
		MSH();
		~MSH();
	private:
		SHVO shvo;
	};
}