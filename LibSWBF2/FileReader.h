#pragma once

namespace LibSWBF2
{
	class FileReader : private ifstream
	{
	public:
		FileReader();
		~FileReader();

		bool Open(const string& File);
		int32_t ReadInt32();
		float_t ReadFloat();
		void Close();
	private:
		void CheckGood();

		string FileName;
	};
}
