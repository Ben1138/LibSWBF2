#pragma once

namespace LibSWBF2
{
	class FileWriter : private ofstream
	{
	public:
		FileWriter();
		~FileWriter();

		bool Open(const string& File);
		void WriteInt32(const int32_t& value);
		void WriteFloat(const float_t& value);
		void Close();
	private:
		void CheckGood();

		string FileName;
	};
}
