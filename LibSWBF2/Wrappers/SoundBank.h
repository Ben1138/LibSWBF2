#pragma once
#include "req.h"
#include "Types/LibString.h"
#include "Sound.h"

namespace LibSWBF2::Chunks::BNK
{
	struct BNK; 
}


namespace LibSWBF2
{
	class Container;
}

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;

	/*
	 * This and the other wrapper classes just serve as abstraction Layers
	 * to wrap around the chunk data. You can of course just use the chunk data
	 * directly if you want. This is just to make access to desired data more
	 * straight forward.
	 */
	class LIBSWBF2_API SoundBank
	{
	private:
		friend Container;

		SoundBank(LibSWBF2::Chunks::BNK::BNK* soundBank);
		~SoundBank();

	private:
		LibSWBF2::Chunks::BNK::BNK* p_soundBank;
		List<Sound> m_Sounds;
		class SoundMapsWrapper* m_NameToIndexMaps;

	public:

		static SoundBank* FromFile(String path);
		static SoundBank* FromChunk(LibSWBF2::Chunks::BNK::BNK* soundChunk);
		static void Destroy(SoundBank* soundBank);

		const List<Sound>& GetSounds() const;
		const Sound* GetSound(String soundName) const;
		const Sound* GetSound(FNVHash soundHash) const;
	};
}