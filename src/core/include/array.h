#ifndef _NATIVE_ARRAY_H_
#define _NATIVE_ARRAY_H_ 1

// Standard Dependencies
#include <initializer_list>
#include <type_traits>

// Module Dependencies
#include "atomic.h"
#include "memory.h"

namespace native
{
	/**
		A dynamic, resizable Array of values. Each value is guaranteed to occupy
		consecutive memory locations from the previous value in the Array, just
		as is the case with a native C-style array.

		Efficiency is important at this level, so trivial types are optimised
		by performing simple memory copy operations rather than iterating
		copy constructors.

		For more high-level, index-based object management, consider using class
		List. List will work more efficiently with complex values than Array,
		as it does not require items to be stored in sequential memory. Array
		is best for temporary storage of trivial types.
	 */
	template <class TValue>
	class Array
	{
	public:
		/**
			Default constructor. Creates an Array of zero length.
		 */
		Array() noexcept;

		/**
			Creates an Array of the given length. That number of items will
			be created in the Array.
			\param length The length of the Array.
		 */
		Array(size_t length);

		/**
			Copies another Array to this one. This is a shallow copy - they will
			share data behind the scenes.
			\param other The Array to copy.
		 */
		Array(const Array<TValue>& other);

		/**
			Move constructor. Moves the contents of the other Array to this one.
			The previous Array will now be empty.
			\param other The Array to move.
		 */
		Array(Array<TValue>&& other) noexcept;

		/**
			Creates an Array from an initializer_list of values. The Array will
			have the same length and contents as the initializer list.
			\param init The initial values to add.
		*/
		Array(std::initializer_list<TValue> init);

		/**
			Destructor. Destroys the Array and its contents.
		 */
		~Array();

		/**
			Copies another Array to this one. This is a shallow copy - they will
			share data behind the scenes.
			\param other The Array to copy.
			\return This Array.
		 */
		Array<TValue>& operator=(const Array<TValue>& other);

		/**
			Moves another Array into this one, discarding the previous contents.
			\param other The Array to move.
			\return This Array.
		 */
		Array<TValue>& operator=(Array<TValue>&& other);

		/**
			Sets a new length for the Array. If this is shorter than the previous
			length, then items at the end of the array are truncated.
			\param length The new Array length.
		 */
		void setLength(size_t length);

		/**
			Deallocates the Array. It will have length zero after it has
			been cleared.
		 */
		void clear();

		/**
			The number of values in the Array.
			\return The array's length.
		 */
		size_t getLength() const noexcept;

		/**
			Gets a pointer to the first value in the underyling C array.
			This may point to data shared between 
		 */
		const TValue* toArray() const noexcept;

		/**
			Sets the item at the specified index to the given value.
			\param index The zero-based index to set at.
			\param value The value to set.
		 */
		void set(size_t index, const TValue& value);

		/**
			Sets a number of values at once from another array.
			\param startIndex The index of the first value to set.
			\param source The array of values to set.
			\param count The number of values to set.
		 */
		void set(size_t startIndex, const TValue* source, size_t count);

		/**
			Sets the given value to multiple locations in the Array.
			\param startIndex The first index to assign the value to.
			\param value The value to assign.
			\param count The number of indecies to assign it to.
		 */
		void set(size_t startIndex, const TValue& value, size_t count);

		/**
			Retrieves a reference to the value at the given zero-based index in
			the Array.
			\param index The index to get the value for.
			\return A non-modifiable reference to that value.
		 */
		const TValue& atIndex(size_t index) const;
		const TValue& operator[](size_t index) const;
		const TValue& operator[](int index) const;

		/**
			Gets an iterator (really just a pointer) pointing at the start of
			the Array.
			\return Iterator at beginning of the Array.
		 */
		TValue* begin() const;

		/**
			Gets an iterator (really just a pointer) pointing past the last value
			in the Array.
			\return Iterator at end of the Array.
		 */
		TValue* end() const;

		/**
			Ensures that this Array does not share its contents with another Array,
			and can therefore be safely modified.
		 */
		void detatch();

	private:
		/** Shared Array data. */
		struct Data
		{
			TValue* data;						///< The native C array of values.
			size_t length;						///< The length of the Array.
			volatile int16_t referenceCount;	///< Reference count minus 1.
		};

		// Helper Functions
		static Data* allocate(size_t length);
		static void release(Data* details) noexcept;

		// Static Variables
		static Data _empty;

		// Instance Variables
		Data* _data;	///< Reference counted Array data.
	};

	/**
		Convenience class for an Array of bytes. ByteArrays are used to
		represent items such as encoded text.
	 */
	class ByteArray : public Array<byte_t>
	{
	public:
		/** 
			Default constructor. Creates empty array of size zero. 
		 */
		ByteArray() noexcept {}

		/**
			Creates a ByteArray that contains the given bytes of data.
		 	\param data The byte data to contain.
		 	\param length The number of bytes.
		 */
		ByteArray(const byte_t* data, size_t length);
		ByteArray(const char* data, size_t length = (size_t) ~0);

		/**
			Creates a ByteArray of the given length.
			\param length The Array length.
		 */
		ByteArray(size_t length);

		/**
			Returns a pointer to the underlying array, cast as signed
			characters.
			\return The Array data.
		 */
		operator const char*() const noexcept { return (const char*) toArray(); }
	};

	ByteArray operator+(const ByteArray& lhs, const ByteArray& rhs);
	ByteArray operator+(const ByteArray& lhs, const char* rhs);
	ByteArray operator+(const char* lhs, const ByteArray& rhs);

	// ---------------------------------------------------------------------- //

	namespace internal
	{
		// Helper Functions
		void raiseArrayIndexException();
		void raiseInvalidArgumentException();
		size_t getCapacityForLength(size_t length) noexcept;

		/** Provides optimised functions based on type, using... voodoo magic. */
		template <class T, bool isTrivial = std::is_trivial<T>::value>
		struct ArrayOptimizer {};

		template <class T>
		struct ArrayOptimizer<T, true>
		{
			typedef Array<T> TArray;
			static T* allocateData(size_t length) { return (T*) Memory::allocateAndZero(++length * sizeof(T)); }
			static void freeData(T* data) noexcept { Memory::free(data); }
			static void copyData(T* destination, const T* source, size_t count) {
				if ((source > destination && source <= destination + count) || (destination > source && destination <= source + count))
					Memory::move(destination, source, count * sizeof(T));
				else
					Memory::copy(destination, source, count * sizeof(T));
			}
			static T& getValue(const T& value) { return (T&) value; }
			static T& getValue(T& value) { return (T&) value; }
		};

		template <class T>
		struct ArrayOptimizer<T, false>
		{
			typedef Array<T*> TArray;
			static T* allocateData(size_t length) { return new T[length]; }
			static void freeData(T* data) noexcept { delete[] data; }
			static void copyData(T* destination, const T* source, size_t count) {
				for (size_t i = 0; i < count; i++)
					destination[i] = source[i];
			}
			static T& getValue(const T* value) { return (T&) *value; }
			static T& getValue(T* value) { return (T&) *value; }
			static T* getValue(const T& value) { return new T(value); }
		};
	}

	// Static Variable Initializers
	template <class TValue>
	typename Array<TValue>::Data Array<TValue>::_empty;

	template <class TValue>
	Array<TValue>::Array() noexcept : _data(&_empty)
	{
		Atomic::increment(_data->referenceCount);
	}

	template <class TValue>
	Array<TValue>::Array(size_t length)
	{
		if (length == 0)
		{
			_data = &_empty;
			Atomic::increment(_data->referenceCount);
		}
		else
		{
			_data = allocate(length);
		}
	}

	template <class TValue>
	Array<TValue>::Array(const Array<TValue>& other) : _data(other._data)
	{
		Atomic::increment(_data->referenceCount);
	}

	template <class TValue>
	Array<TValue>::Array(Array<TValue>&& other) noexcept : _data(other._data)
	{
		other._data = &_empty;
		Atomic::increment(_empty.referenceCount);
	}

	template <class TValue>
	Array<TValue>::Array(std::initializer_list<TValue> init)
	{
		if (init.size() == 0)
		{
			_data = &_empty;
			Atomic::increment(_data->referenceCount);
		}
		else
		{
			_data = allocate(init.size());

			// Copy the initializer_list data into the Array.
			const TValue* value = init.begin();
			size_t  i = 0;

			while (value != init.end())
				_data->data[i++] = *value++;
		}
	}

	template <class TValue>
	Array<TValue>::~Array()
	{
		release(_data);
	}

	template <class TValue>
	Array<TValue>& Array<TValue>::operator=(const Array<TValue>& other)
	{
		if (other._data != _data)
		{
			release(_data);
			_data = other._data;
			Atomic::increment(_data->referenceCount);
		}

		return *this;
	}

	template <class TValue>
	Array<TValue>& Array<TValue>::operator=(Array<TValue>&& other)
	{
		if (other._data != _data)
		{
			// Pass the other's data over.
			release(_data);
			_data = other._data;
		}

		// Nullify the originating Array.
		other._data = &_empty;
		Atomic::increment(_empty.referenceCount);

		return *this;
	}

	template <class TValue>
	void Array<TValue>::setLength(size_t length)
	{
		if (length != getLength())
		{
			if (length == 0)
			{
				release(_data);

				// Use the empty array detail.
				_data = &_empty;
				Atomic::increment(_data->referenceCount);
			}
			else
			{
				Data* old = _data;

				// Allocate a new chunk to copy data into.
				_data = allocate(length);
				internal::ArrayOptimizer<TValue>::copyData(_data->data, old->data, length > old->length ? old->length : length);

				release(old);
			}
		}
	}

	template <class TValue>
	void Array<TValue>::clear()
	{
		if (getLength() > 0)
		{
			release(_data);

			_data = &_empty;
			Atomic::increment(_data->referenceCount);
		}
	}

	template <class TValue>
	size_t Array<TValue>::getLength() const noexcept
	{
		return _data->length;
	}

	template <class TValue>
	const TValue* Array<TValue>::toArray() const noexcept
	{
		return _data->data;
	}

	template <class TValue>
	void Array<TValue>::set(size_t index, const TValue& value)
	{
		detatch();

		if (index >= _data->length)
			internal::raiseArrayIndexException();

		_data->data[index] = value;
	}

	template <class TValue>
	void Array<TValue>::set(size_t startIndex, const TValue* source, size_t count)
	{
		size_t offset = startIndex + count;

		if (offset > getLength())
			internal::raiseArrayIndexException();

		if (_data->referenceCount > 0)
		{
			Data* old = _data;

			// The data is shared. Get unique data.
			_data = allocate(old->length);

			if (startIndex > 0)
				internal::ArrayOptimizer<TValue>::copyData(_data->data, old->data, startIndex);

			internal::ArrayOptimizer<TValue>::copyData(_data->data + startIndex, source, count);

			if (offset < getLength())
				internal::ArrayOptimizer<TValue>::copyData(_data->data + offset, old->data + offset, getLength() - offset);

			release(old);
		}
		else
		{
			internal::ArrayOptimizer<TValue>::copyData(_data->data + startIndex, source, count);
		}
	}

	template <class TValue>
	void Array<TValue>::set(size_t startIndex, const TValue& value, size_t count)
	{
		detatch();

		for (size_t i = startIndex; i < startIndex + count; i++)
			_data->data[i] = value;
	}

	template <class TValue>
	const TValue& Array<TValue>::atIndex(size_t index) const
	{
		if (index >= getLength())
			internal::raiseArrayIndexException();

		return _data->data[index];
	}

	template <class TValue>
	const TValue& Array<TValue>::operator[](size_t index) const
	{
		return atIndex(index);
	}

	template <class TValue>
	const TValue& Array<TValue>::operator[](int index) const
	{
		if (index < 0)
			internal::raiseArrayIndexException();

		return atIndex((size_t) index);
	}

	template <class TValue>
	TValue* Array<TValue>::begin() const
	{
		return _data->data;
	}

	template <class TValue>
	TValue* Array<TValue>::end() const
	{
		return _data->data + _data->length;
	}

	template <class TValue>
	void Array<TValue>::detatch()
	{
		if (_data->referenceCount > 0 && _data->length > 0)
		{
			Data* data = allocate(_data->length);
			internal::ArrayOptimizer<TValue>::copyData(data->data, _data->data, _data->length);

			release(_data);
			_data = data;
		}
	}

	template <class TValue>
	typename Array<TValue>::Data* Array<TValue>::allocate(size_t length)
	{
		if (length == 0)
			internal::raiseInvalidArgumentException();

		Data* data = new Data;
		data->referenceCount = 0;
		data->data = internal::ArrayOptimizer<TValue>::allocateData(length);
		data->length = length;

		return data;
	}

	template <class TValue>
	void Array<TValue>::release(Data* data) noexcept
	{
		if (Atomic::decrement(data->referenceCount) < 0)
		{
			internal::ArrayOptimizer<TValue>::freeData(data->data);
			delete data;
		}
	}
}

#endif // _NATIVE_ARRAY_H_

