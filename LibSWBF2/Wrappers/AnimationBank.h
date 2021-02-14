#pragma once
#include "Chunks/LVL/zaa_/zaa_.h"



namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::String;
	using namespace Chunks::LVL::animation;


	class LIBSWBF2_API AnimationBank
	{

	public:

		static bool FromChunk(zaa_ *chunk, AnimationBank &setOut);

		bool GetCurve(CRCChecksum anim, CRCChecksum bone, uint16_t component,
					List<uint16_t> &frame_indices, List<float_t> &frame_values) const;
	
		bool ContainsAnimation(CRCChecksum anim) const;

		List<CRCChecksum> GetAnimationNames() const;
		List<CRCChecksum> GetBoneNames() const;
		
		bool GetAnimationMetadata(CRCChecksum anim, uint32_t &numFrames, uint32_t &numBones) const;

		String name;


	private:

		zaa_ *animChunk = nullptr;

		class AnimDecompressor
		{
		public:
			AnimDecompressor(void *_buffer, size_t _length);
			AnimDecompressor();
			void SetDecompressionParams(float_t mult = 1.0f / 2047.0f, float_t offset = 0.0) const;
			bool DecompressFromOffset(size_t offset, uint16_t num_frames, 
									List<uint16_t> &frame_indicies, 
									List<float_t> &frame_values) const;
		private:
			int8_t *buffer;
			size_t length;

			mutable size_t read_head;
			mutable float_t bias, multiplier;

			inline bool ReadInt16(int16_t &val) const;
			inline bool ReadInt8(int8_t &val) const;
			inline bool ReadUInt8(uint8_t &val) const;
		};

		#pragma warning(disable:4251)
		AnimDecompressor decompressor;
		#pragma warning(default:4251)
	};
}