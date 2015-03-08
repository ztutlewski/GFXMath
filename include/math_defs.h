#ifndef MATH_DEFS_DOT_H
#define MATH_DEFS_DOT_H
#include <array>
#include "gfxmath_config.h"
/*! \file */

/*!
 * \namespace	gfxmath
 *
 * \brief G of F of X math namespace.
 */
namespace gfxmath
{
	/*!
	 * \defgroup ScalarMathConsts Scalar Math Definitions
	 * @{
	 */

	/*!
	 * \typedef	unsigned int MaskVal
	 *
	 * \brief	Defines an alias representing the mask value.
	 */
	typedef unsigned int MaskVal;

	const float DEG_TO_RAD = 0.01745329251994329576923690768489f;   /*!<  Degrees to radians conversion factor (%%\\frac{\\pi}{180}%%) */
	const float F_PI_4 = 0.78539816339744830961566084581988f;		/*!<  %%\\frac{\\pi}{4}%% */
	const float F_PI_3 = 1.0471975511965977461542144610932f;		/*!<  %%\\frac{\\pi}{3}%% */
	const float F_PI_2 = 1.5707963267948966192313216916398f;		/*!<  %%\\frac{\\pi}{2}%% */
	const float F_2PI_3 = 2.0943951023931954923084289221863f;		/*!<  %%\\frac{2\\pi}{3}%% */
	const float F_3PI_4 = 2.3561944901923449288469825374596f;		/*!<  %%\\frac{3\\pi}{4}%% */
	const float F_PI = 3.1415926535897932384626433832795f;			/*!<  %%\\pi%% */
	const float F_PI2 = 9.8696044010893586188344909998762f;			/*!<  %%\\pi^2%% */
	const float F_4PI_3 = 4.1887902047863909846168578443727f;		/*!<  %%\\frac{4\\pi}{3}%% */
	const float F_3PI_2 = 4.7123889803846898576939650749193f;		/*!<  %%\\frac{3\\pi}{2}%% */
	const float F_2PI = 6.283185307179586476925286766559f;			/*!<  %%2\\pi%% */
	const float F_1_2PI = 0.15915494309189533576888376337251f;		/*!<  %%\\frac{1}{2\\pi}%% */
	const float F_2_PI = 0.63661977236758134307553505349006f;		/*!<  %%\\frac{2}{\\pi}%% */
	const float F_4_PI = 1.2732395447351626861510701069801f;		/*!<  %%\\frac{4}{\\pi}%% */
	const float F_4_PI2 = 0.40528473456935108577551785283891f;		/*!<  %%\\frac{4}{\\pi^2}%% */
	const float F_NEG4_PI2 = -0.40528473456935108577551785283891f;  /*!<  %%\\frac{-4}{\\pi^2}%% */
	const float F_SQRT2 = 1.4142135623730950488016887242097f;		/*!<  %%\\sqrt{2}%% */
	const float F_1_SQRT2 = 0.70710678118654752440084436210485f;	/*!<  %%\\frac{1}{\\sqrt{2}}%% */
	const float F_1_SQRT3 = 0.57735026918962576450914878050196f;	/*!<  %%\\frac{1}{\\sqrt{3}}%% */
	const float F_SQRT3_2 = 0.86602540378443864676372317075294f;	/*!<  %%\\frac{\\sqrt{3}}{2}%% */
	const float F_SQRT3 = 1.7320508075688772935274463415059f;		/*!<  %%\\sqrt{3}%% */

	/*!
	 * \brief %%\\epsilon%% (epsilon) is the smallest single-precision floating point value such that %%1.0%%f%% + \\epsilon \\not= 1.0%%f 
	 */
	float Epsilon();

	/*!
	 * \brief Single-precision floating point representation of %%\\infty%%
	 */
	float Infinity();

	/*!
	 * \brief Maximum possible value for a single-precision floating point number such that the number is not %%\\infty%%.
	 */
	float FloatMax();

	const MaskVal F_SIGN_BIT = 0x80000000;	/*!< Mask for the sign bit for standard floating point numbers. */

	

	/*!
	 * \enum	FloatPrecision
	 *
	 * \brief	Values that represent float precisions.
	 * 
	 * \remarks Used as template arguments for various
	 *			functions to determine approximation
	 *			accuracies in floating point comparisons,
	 *			and taylor approximations. Specifically used
	 *			with FLOAT_PRECISION_VALUES and TRIG_PRECISION_VALUES.
	 */
	enum FloatPrecision
	{
		HIGH = 0,			/*!< The high precision option */
		MEDIUM_HIGH = 1,	/*!< The medium-high precision option */
		MEDIUM = 2,			/*!< The medium precision option */
		MEDIUM_LOW = 3,		/*!< The medium-low precision option */
		LOW = 4				/*!< The low precision option */
	};

	const size_t NUM_TRIG_COEFS = 16;   /*!< Maximum number of trig coefficients supported by IEEE 754 single-precision floating point numbers - assuming a taylor approximation. */
	const size_t NUM_PRECISION_VALS = 5;	/*!< Number of precision values */

	/*! 
	 * \brief	Returns the (i+1)th coefficient for the taylor approximation of sine 
	 */
	inline float SinCoef(int i)
	{
		static const std::array<float, NUM_TRIG_COEFS> SIN_COEFS
		{ {
			-1.66666667e-1f,  // -1/(1+2*1)!  = -1/3!
			 8.33333333e-3f,  //  1/(1+2*2)!  =  1/5!
			-1.98412698e-4f,  // -1/(1+2*3)!  = -1/7!
			 2.75573192e-6f,  //  1/(1+2*4)!  =  1/9!
			-2.50521084e-8f,  // -1/(1+2*5)!  = -1/11!
			 1.60590438e-10f, //  1/(1+2*6)!  =  1/13!
			-7.64716373e-13f, // -1/(1+2*7)!  = -1/15!
			 2.81145725e-15f, //  1/(1+2*8)!  =  1/17!
			-8.22063525e-18f, // -1/(1+2*9)!  = -1/19!
			 1.95729411e-20f, //  1/(1+2*10)! =  1/21!
			-3.86817017e-23f, // -1/(1+2*11)! = -1/23!
		 	 6.44695028e-26f, //  1/(1+2*12)! =  1/25!
			-9.18368986e-29f, // -1/(1+2*13)! = -1/27!
			 1.13099629e-31f, //  1/(1+2*14)! =  1/29!
			-1.21612504e-34f, // -1/(1+2*15)! = -1/31!
			 1.15163356e-37f, //  1/(1+2*16)! =  1/33!
		} };

		return SIN_COEFS[i];
	}

	/*!
	 * \brief	The (i+1)th coefficient for the taylor approximation of cosine
	 */
	inline float CosCoef(int i)
	{
		static const std::array<float, NUM_TRIG_COEFS> COS_COEFS
		{ {
			-5.00000000e-1f,  // -1/(2*1)!  = -1/2!
			 4.16666667e-2f,  //  1/(2*2)!  =  1/4!
			-1.38888889e-3f,  // -1/(2*3)!  = -1/6!
			 2.48015873e-5f,  //  1/(2*4)!  =  1/8!
			-2.75573192e-7f,  // -1/(2*5)!  = -1/10!
			 2.08767570e-9f,  //  1/(2*6)!  =  1/12!
			-1.14707456e-11f, // -1/(2*7)!  = -1/14!
			 4.77947733e-14f, //  1/(2*8)!  =  1/16!
			-1.56192070e-16f, // -1/(2*9)!  = -1/18!
			 4.11031762e-19f, //  1/(2*10)! =  1/20!
			-8.89679139e-22f, // -1/(2*11)! = -1/22!
			 1.61173757e-24f, //  1/(2*12)! =  1/24!
			-2.47959626e-27f, // -1/(2*13)! = -1/26!
			 3.27988924e-30f, //  1/(2*14)! =  1/28!
			-3.769987631e-33f,// -1/(2*15)! = -1/30!
			 3.800390755e-36f //  1/(2*16)! =  1/32!
		} };

		return COS_COEFS[i];
	}

	/*! 
	 * \brief	Returns the ith single-precision floating point precision limit used for checking approximate
	 *			equality of two single-precision floating point values.
	 *
	 * \remarks	Holds the following values:
	 *				+ %%5.0*10^{-07}%% for gfxmath::FloatPrecision::HIGH
	 *				+ %%1.0*10^{-05}%% for gfxmath::FloatPrecision::MEDIUM_HIGH
	 *				+ %%1.0*10^{-03}%% for gfxmath::FloatPrecision::MEDIUM
	 *				+ %%1.0*10^{-02}%% for gfxmath::FloatPrecision::MEDIUM_LOW
	 *				+ %%1.0*10^{-01}%% for gfxmath::FloatPrecision::LOW
	 */
	template<FloatPrecision precisionVal>
	inline float FloatPrecisionValue()
	{
		static const std::array<float, NUM_PRECISION_VALS> FLOAT_PRECISION_VALUES
		{ {
			5.0e-07F,//HIGH
			1.0e-05F,//MEDIUM_HIGH
			1.0e-03F,//MEDIUM
			1.0e-02F,//MEDIUM_LOW
			1.0e-01F,//LOW
		} };

		return FLOAT_PRECISION_VALUES[precisionVal];
	}

	/*!
	 * \brief	Returns the ith trig function precision value used to determine how many iterations of a taylor
	 *			approximation are needed to reach a given accuracy standard.
	 */
	template<FloatPrecision precisionVal>
	inline int TrigPrecisionValue()
	{
		return 9 - precisionVal;
	}

	/*! @} */
}

#endif