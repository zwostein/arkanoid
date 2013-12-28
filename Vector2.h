#ifndef _VECTOR2__INCLUDED_
#define _VECTOR2__INCLUDED_


#include <limits>
#include <cassert>
#include <cmath>


template<class T> struct Vector2
{
	union
	{
		T xy[2];	///< Storage for 2 components - first is x, second is y.
		struct
		{
			T x;	///< Direct access to x component.
			T y;	///< Direct access to y component.
		};
	};

	/// Initializes all components to their default value.
	inline Vector2() : x(), y()
	{
	}

	/// Initializes all components to the given values.
	template<class U> inline Vector2( U x, U y ) : x(static_cast<T>(x)), y(static_cast<T>(y))
	{
	}

	/// Initializes all components using the values in given vector.
	template<class U> inline Vector2( const Vector2<U> & vec ) : x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y))
	{
	}

	/// Initializes all components to the values in given array.
	template<class U> inline Vector2( const U xy[2] ) : x(static_cast<T>(xy[0])), y(static_cast<T>(xy[1]))
	{
	}

	/// Initializes all components to a normalized vector with given absolute angle.
	inline explicit Vector2( const double & angle )
	{
		if( std::numeric_limits<T>::is_integer )
		{
			x = std::numeric_limits<T>::max() * sin(angle);
			y = std::numeric_limits<T>::max() * cos(angle);
		}
		else
		{
			x = sin(angle);
			y = cos(angle);
		}
	}

	/// Component access using the index operator.
	inline T operator[]( int i ) const
	{
		assert( i < 2 );
		return xy[i];
	}

	/// Component access using the index operator.
	inline T & operator[]( int i )
	{
		assert( i < 2 );
		return xy[i];
	}

	/// Assign the component values from another vector to this one.
	inline Vector2<T> & operator=( const Vector2<T> & rhs )
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	/// Negates each component.
	inline Vector2<T> operator-() const
	{
		return Vector2<T>(-x,-y);
	}

	/// Component addition.
	inline const Vector2<T> operator+( const Vector2<T> & rhs ) const
	{
		return Vector2<T>( x+rhs.x, y+rhs.y );
	}

	/// Calculates difference between two vectors.
	inline const Vector2<T> operator-( const Vector2<T> & rhs ) const
	{
		return Vector2<T>( x-rhs.x, y-rhs.y );
	}

	/// Scalar multiplication.
	inline const Vector2<T> operator*( const T & rhs ) const
	{
		return Vector2<T>( x*rhs, y*rhs );
	}

	explicit inline operator bool() const
	{
		return x || y;
	}

	/// Scalar division.
	inline const Vector2<T> operator/( const T &rhs ) const
	{
		return Vector2<T>( x/rhs, y/rhs );
	}

	/// Add another vector to this one.
	inline Vector2<T> & operator+=( const Vector2<T> & rhs )
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	/// Subtract another vector from this one.
	inline Vector2<T> & operator-=( const Vector2<T> & rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	/// Multiply by scalar.
	inline Vector2<T> & operator*=( const T & rhs )
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	/// Divide by scalar.
	inline Vector2<T> & operator/=( const T & rhs )
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	/// Scalar multiplication.
	friend inline const Vector2<T> operator*( const T & lhs, const Vector2<T> rhs )
	{
		return  rhs * lhs;
	}

	/// Calculates dot product.
	inline const T dot( const Vector2<T> & rhs ) const
	{
		return ( x*rhs.x + y*rhs.y );
	}

	/// Calculates perpendicular dot product.
	inline const T perpDot( const Vector2<T> & rhs ) const
	{
		return ( x*y - rhs.x*rhs.y );
	}

	/// Calculates perpendicular.
	inline const Vector2<T> perpendicular() const
	{
		return Vector2<T>(-y,x);
	}

	/// Calculates this vector's squared length. (faster than the real length)
	inline const T lengthSquared() const
	{
		return ( x*x + y*y );
	}

	/// Calculates this vector's length.
	inline const T length() const
	{
		return sqrt( lengthSquared() );
	}

	/// Calculates the normalized vector.
	inline const Vector2<T> normalized() const
	{
		T len = length();
		if( len == 0 )
			return Vector2<T>( 0, 0 );
		if( std::numeric_limits<T>::is_integer )
			return (*this) * (T)( std::numeric_limits<T>::max() / len );
		else
			return (*this) * (T)( T(1) / len );
	}

	/// Normalize this vector.
	inline void normalize()
	{
		(*this) = this->normalized();
	}

	/// Calculates the distance to another vector.
	inline const T distance( const Vector2<T> & rhs ) const
	{
		return (rhs-*this).length();
	}

	/// Calculates the squared distance. (faster than the real length)
	inline const T distanceSquared( const Vector2<T> & rhs ) const
	{
		return (rhs-*this).lengthSquared();
	}

	/// Calculates the normalized direction vector to another vector.
	inline const Vector2<T> direction( const Vector2<T> & rhs ) const
	{
		return (rhs-*this).normalized();
	}

	/// Returns this vector rotated by angle.
	inline const Vector2<T> rotated( const double & angle ) const
	{
		double sine( sin(angle) ), cosine( cos(angle) );
		return Vector2<T>( cosine*x-sine*y, sine*x+cosine*y );
	}

	/// Rotates this vector by angle.
	inline void rotate( const double & angle )
	{
		(*this) = this->rotated();
	}

	/// Returns this vector rotated by another vector.
	inline const Vector2<T> rotated( const Vector2<T> & v ) const
	{
		return Vector2<T>( x*v.x - y*v.y, x*v.y + y*v.x );
	}

	/// Rotates this vector by another vector.
	inline void rotate( const Vector2<T> & v )
	{
		(*this) = rotated( v );
	}

	/// Returns the absolute angle.
	inline double angle()
	{
		return atan2( y, x );
	}

	/// Returns this vector reflected at normal
	inline const Vector2<T> reflected( const Vector2<T> & n ) const
	{
		return (*this) - 2.0 * (this->dot(n)) * n;
	}

	/// Reflects this vector at normal
	inline void reflect( const Vector2<T> & n )
	{
		(*this) = reflected(n);
	}

	/// Swaps X and Y.
	inline void swap()
	{
		T tmp = x;
		x = y;
		y = tmp;
	}

	/// Conversion to pointer operator
	/**
	* \return Pointer to xy.
	*/
	operator T*()
	{
		return (T*) xy;
	}

	/// Conversion to pointer operator
	/**
	* \return Constant Pointer to xy
	*/
	operator const T*() const
	{
		return (const T*) xy;
	}
};

typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;


#endif
