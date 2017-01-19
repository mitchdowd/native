#ifndef _NATIVE_MAP_H_
#define _NATIVE_MAP_H_ 1

// Module Dependencies
#include "array.h"
#include "collection.h"
#include "exception.h"
#include "hash.h"

namespace native
{
	/**
		A key/value pair of generic types.
	 */
	template <class TKey, class TValue>
	struct Pair
	{
		// Instance Variables
		TKey   key;			///< The stored key.
		TValue value;		///< The associated value.

		/**
			Creates a Pair from the specified key and value.
			\param key The key to access the Pair.
			\param value The associated value.
		 */
		Pair(const TKey& key, const TValue& value) : key(key), value(value) {}
	};

	// Forward Declarations
	template <class TKey, class TValue> class MapIterator;

	/**
		A mapping of key to value, also known as an associative array. Only one
		value may be stored per key (i.e. This is not a "multi-map").
	 */
	template <class TKey, class TValue>
	class Map : public Collection< MapIterator<TKey, TValue> >
	{
	public:
		/**
			Creates an empty Map with no values in it. An optional table size may
			be specified if it is anticipated that the Map is going to be large.
			It is recommended to use prime numbers as the table size.
			\param tableSize The optional table size (defaults to 17).
		 */
		Map(size_t tableSize = 17);

		/**
			Copies the given Map to this one. This is a shallow copy wherever possible,
			with data not deep copied until a modification is made.
			\param other The Map to copy.
		 */
		Map(const Map<TKey, TValue>& other);

		/**
			Moves the given Map's contents to this one.
			\param other The Map to move.
		 */
		Map(Map<TKey, TValue>&& other) noexcept;

		/**
			Creates a Map from an initializer_list of pairs.
			\param init The initializer list.
		 */
		Map(std::initializer_list< Pair<TKey, TValue> > init);

		/** Destroys the Map and all that it contains. */
		~Map();

		/**
			Assigns the contents of another Map to this one. The previous contents
			are lost. This is a shallow copy operation when possible.
			\param other The Map to copy.
			\return This Map.
		 */
		Map<TKey, TValue>& operator=(const Map<TKey, TValue>& other);

		/**
			Adds the given key/value pair to the Map.
			\param pair The key/value pair to add.
		 */
		void add(const Pair<TKey, TValue>& pair) override;
		void add(const TKey& key, const TValue& value);

		/**
			Sets the given value for the given key.  If the key does not yet exist
			it is added to the Map.
		 */
		void set(const TKey& key, const TValue& value);

		/**
			Removes the entry with the given key from the Map.
			\param key The key of the key/value pair to remove.
		 */
		void remove(const TKey& key);

		/** Removes all items from the Map. */
		void clear() override;

		/**
			Checks if the given key is already in the Map.
			\param key The key to search for.
			\return true or false.
		 */
		bool containsKey(const TKey& key) const;

		/**
			Returns the number of key/value pairs in the Map.
			\return The Map's length.
		 */
		size_t getLength() const noexcept override;

		/**
			Retrieves the value for the given key.
			\param key The key to get the value for.
			\return The value for the given key.
			\throw ArrayIndexException if the key does not exist.
		 */
		const TValue& get(const TKey& key) const;
		const TValue& operator[](const TKey& key) const { return get(key); }

		/**
			Retrieves the value for the given key.
			\param key The key to get the value for.
			\return The value for the given key.
			\throw ArrayIndexException if the key does not exist.
		 */
		TValue& get(const TKey& key);
		TValue& operator[](const TKey& key) { return get(key); }

		/**
			Returns an Iterator positioned at the first Pair in this Map.
			\return An Iterator.
		 */
		MapIterator<TKey, TValue> begin() const override;

		/**
			Returns an Iterator positioned beyond the last Pair in the Map.
			\return An Iterator.
		 */
		MapIterator<TKey, TValue> end() const override;

	private:
		// Class Friendships
		friend class MapIterator<TKey, TValue>;

		// Type Definitions
		typedef typename internal::LinkedValue< Pair<TKey, TValue> > Link;

		// Instance Variables
		Array<Link*> _table;
		size_t _length;
	};

	/**
		An Iterator that iterates over a Map.
	 */
	template <class TKey, class TValue>
	class MapIterator : public Iterator< Pair<TKey, TValue>, MapIterator<TKey, TValue> >
	{
	public:
		/**
			Increments the MapIterator forward to the next key/value pair in the Map.
			\return The Iterator.
		 */
		MapIterator<TKey, TValue>& operator++() override;

		/**
			Returns the current key/value pair in iteration.
			\return The current pair in iteration.
		 */
		const Pair<TKey, TValue>& operator*() const override;

		/**
			Tests iterators for inequality.
			\param other The MapIterator to compare with.
			\return true if different, false if the same.
		 */
		bool operator!=(const MapIterator<TKey, TValue>& other) const override;

	private:
		// Class Friendships
		friend class Map<TKey, TValue>;

		// Type Definitions
		typedef typename internal::LinkedValue< Pair<TKey, TValue> > Link;

		/** Constructor. Used by class Map. */
		MapIterator(const Map<TKey, TValue>& map, size_t index, Link* link);

	private:
		// Instance Variables
		const Array<Link*>& _table;
		size_t _index;
		Link* _link;
	};

	template <class TKey, class TValue>
	Map<TKey, TValue>::Map(size_t tableSize) : _table(tableSize), _length(0)
	{
		if (tableSize < 1)
			throw InvalidArgumentException();

		// Initialise to nulls.
		for (size_t i = 0; i < tableSize; i++)
			_table.set(i, nullptr);
	}

	template <class TKey, class TValue>
	Map<TKey, TValue>::Map(const Map<TKey, TValue>& other) : _table(other._data), _length(other._length)
	{
	}

	template <class TKey, class TValue>
	Map<TKey, TValue>::Map(Map<TKey, TValue>&& other) noexcept : _table(std::move(other._data)), _length(other._length)
	{
		other._length = 0;
	}

	template <class TKey, class TValue>
	Map<TKey, TValue>::Map(std::initializer_list< Pair<TKey, TValue> > init) : _table(17), _length(0)
	{
		// Initialise to nulls.
		for (size_t i = 0; i < _table.getLength(); i++)
			_table.set(i, nullptr);

		for (auto i : init)
			add(i);
	}

	template <class TKey, class TValue>
	Map<TKey, TValue>::~Map()
	{
		clear();
	}

	template <class TKey, class TValue>
	Map<TKey, TValue>& Map<TKey, TValue>::operator=(const Map<TKey, TValue>& other)
	{
		_table = other._table;
		_length = other._length;

		return *this;
	}

	template <class TKey, class TValue>
	void Map<TKey, TValue>::add(const TKey& key, const TValue& value)
	{
		// Perform the hash.
		size_t hashCode = hash(key) % _table.getLength();

		// Check whether the key already exists.
		for (Link* link = _table[hashCode]; link; link = link->next)
			if (link->value.key == key)
				return;

		// Add the new link.
		_table.set(hashCode, new Link(Pair<TKey, TValue>(key, value), _table[hashCode]));
		_length++;
	}

	template <class TKey, class TValue>
	void Map<TKey, TValue>::add(const Pair<TKey, TValue>& pair)
	{
		add(pair.key, pair.value);
	}

	template <class TKey, class TValue>
	void Map<TKey, TValue>::set(const TKey& key, const TValue& value)
	{
		if (containsKey(key))
			get(key) = value;
		else
			add(key, value);
	}

	template <class TKey, class TValue>
	void Map<TKey, TValue>::remove(const TKey& key)
	{
		// Perform the hash.
		size_t hashCode = hash(key) % _table.getLength();
		Link* link = _table[hashCode];

		if (link)
		{
			if (link->value.key == key)
			{
				// It's the first item with that hash code.
				_table.set(hashCode, link->next);
				_length--;
				delete link;
			}
			else
			{
				while (link->next)
				{
					if (link->next->value.key == key)
					{
						Link* target = link->next;
						link->next = target->next;
						_length--;
						delete target;
						break;
					}

					link = link->next;
				}
			}
		}
	}

	template <class TKey, class TValue>
	void Map<TKey, TValue>::clear()
	{
		// Delete all of the values.
		for (size_t i = 0; i < _table.getLength(); i++)
		{
			Link* link = _table[i];

			while (link)
			{
				Link* target = link;
				link = link->next;
				delete target;
			}
		}

		_length = 0;
	}

	template <class TKey, class TValue>
	bool Map<TKey, TValue>::containsKey(const TKey& key) const
	{
		// Perform the hash.
		size_t hashCode = hash(key) % _table.getLength();

		// Search for the key.
		for (Link* link = _table[hashCode]; link; link = link->next)
			if (link->value.key == key)
				return true;

		return false;
	}

	template <class TKey, class TValue>
	size_t Map<TKey, TValue>::getLength() const noexcept
	{
		return _length;
	}

	template <class TKey, class TValue>
	const TValue& Map<TKey, TValue>::get(const TKey& key) const
	{
		size_t hashCode = hash(key) % _table.getLength();

		// Search for the given key.
		for (Link* link = _table[hashCode]; link; link = link->next)
			if (link->value.key == key)
				return link->value.value;

		throw ArrayIndexException();
	}

	template <class TKey, class TValue>
	TValue& Map<TKey, TValue>::get(const TKey& key)
	{
		size_t hashCode = hash(key) % _table.getLength();

		// Search for the given key.
		for (Link* link = _table[hashCode]; link; link = link->next)
			if (link->value.key == key)
				return link->value.value;

		throw ArrayIndexException();
	}

	template <class TKey, class TValue>
	MapIterator<TKey, TValue> Map<TKey, TValue>::begin() const
	{
		size_t index;
		Link* link = nullptr;

		// Move to the first valid Link.
		for (index = 0; index < _table.getLength(); ++index)
			if ((link = _table[index]) != nullptr)
				break;

		return MapIterator<TKey, TValue>(*this, index, link);
	}

	template <class TKey, class TValue>
	MapIterator<TKey, TValue> Map<TKey, TValue>::end() const
	{
		return MapIterator<TKey, TValue>(*this, _table.getLength(), nullptr);
	}

	template <class TKey, class TValue>
	MapIterator<TKey, TValue>::MapIterator(const Map<TKey, TValue>& map, size_t index, Link* link)
		: _table(map._table), _index(index), _link(link)
	{
	}

	template <class TKey, class TValue>
	MapIterator<TKey, TValue>& MapIterator<TKey, TValue>::operator++()
	{
		if (!_link)
			throw InvalidStateException();

		_link = _link->next;

		while (!_link && ++_index < _table.getLength())
			_link = _table[_index];

		return *this;
	}

	template <class TKey, class TValue>
	const Pair<TKey, TValue>& MapIterator<TKey, TValue>::operator*() const
	{
		return _link->value;
	}

	template <class TKey, class TValue>
	bool MapIterator<TKey, TValue>::operator!=(const MapIterator<TKey, TValue>& other) const
	{
		return _link != other._link || _index != other._index || &_table != &other._table;
	}
}

#endif // _NATIVE_MAP_H_
