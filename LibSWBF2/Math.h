#pragma once
#include <type_traits>

namespace LibSWBF2 {
	/// <summary>
	/// Contains some Clamp functions
	/// </summary>
	class Math
	{
	public:
		/// <summary>
		/// Clamps a given value between min and max
		/// </summary>
		/// <param name="value">The value to clamp</param>
		/// <param name="min">The minimum value allowed</param>
		/// <param name="max">The maximum value allowed</param>
		/// <returns>The clamped value</returns>
		template<typename T>
		static T Clamp(const T &value, const T &min, const T &max) {
			if (value < min)
				return min;
			else if (value > max)
				return max;
			else
				return value;
		}

		/// <summary>
		/// Clamps a given value between 0 and 1
		/// </summary>
		/// <param name="value">The value to clamp</param>
		/// <returns>The clamped value</returns>
		template<typename T>
		static T Clamp01(const T &value) {
			return Clamp((float_t)value, 0.0f, 1.0f);
		}
	private:
		Math() {};
		~Math() {};
	};
}