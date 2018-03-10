#pragma once

#include "queue.h"
#include "array.h"

#include <stdexcept>

// implementacia pomocou pola (array)

namespace structures
{
	/// <summary> Implicitny front. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo fronte. </typepram>
	template<typename T>
	class ImplicitQueue : public Queue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ImplicitQueue();

		/// <summary> Parametricky konstruktor. </summary>
		/// <param name = "capacity"> Maximalna velkost frontu. </param>
		ImplicitQueue(const size_t capacity);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Implicitny front, z ktoreho sa prevezmu vlastnosti. </param>
		ImplicitQueue(const ImplicitQueue<T>& other);

		/// <summary> Destruktor. </summary>
		~ImplicitQueue();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat frontu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov vo fronte. </summary>
		/// <returns> Pocet prvkov vo fronte. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		Queue<T>& operator=(const Queue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento front nachadza po priradeni. </returns>
		ImplicitQueue<T>& operator=(const ImplicitQueue<T>& other);

		/// <summary> Vymaze front. </summary>
		void clear() override;

		/// <summary> Prida prvok do frontu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front plny. </exception>  
		void push(const T& data) override;

		/// <summary> Odstrani prvok z frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati prvok na zaciatku frontu. </summary>
		/// <returns> Prvok na zaciatku frontu. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je front prazdny. </exception>  
		const T peek() const override;

	protected:
		/// <summary> Pole, pomocou ktoreho je implementovany front. </summary>	
		Array<T>* array_;

		/// <summary> Index prveho prvku vo fronte. </summary>	
		int startIndex_;

		/// <summary> Pocet prvkov vo fronte. </summary>	
		size_t size_;
	};

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue() :
		ImplicitQueue(10)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(const size_t capacity) :
		Queue(),
		array_(new Array<T>(capacity)),
		startIndex_(0),
		size_(0)
	{
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(const ImplicitQueue<T>& other) :
		Queue(other),
		array_(new Array<T>(*other.array_)),
		startIndex_(other.startIndex_),
		size_(other.size_)
	{
	}

	template<typename T>
	ImplicitQueue<T>::~ImplicitQueue()
	{
		delete array_;
		array_ = nullptr;
		startIndex_ = 0;
		size_ = 0;
	}

	template<typename T>
	inline Queue<T>& ImplicitQueue<T>::operator=(const Queue<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ImplicitQueue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ImplicitQueue<T>& ImplicitQueue<T>::operator=(const ImplicitQueue<T>& other)
	{
		if (this != &other) {
			if (array_->size() < other.size_) {
				throw std::logic_error("Implicit queue = : Arrays aren't compatible");
			}
			Array<T>::copy(*other.array_, other.startIndex_, *array_, 0, static_cast<int>(other.size_) - other.startIndex_ + 1);
			Array<T>::copy(*other.array_, 0, *array_, static_cast<int>(other.size_) - other.startIndex_ + 1, (static_cast<int>(other.size_) + other.startIndex_) % other.array_->size());

			/*

			toto len ak podmienka je, ze maju polia rovnake velkosti

			*array_ = *other.array_;
			startIndex_ = other.startIndex_;
			size_ = other.size_;
			*/
		}
		return *this;
	}

	template<typename T>
	inline Structure * ImplicitQueue<T>::clone() const
	{
		return new ImplicitQueue<T>(*this);
	}

	template<typename T>
	size_t ImplicitQueue<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline void ImplicitQueue<T>::clear()
	{
		startIndex_ = 0;
		size_ = 0;
	}

	template<typename T>
	inline void ImplicitQueue<T>::push(const T& data) //dorobit
	{
		size_t cap = array_->size();
		if (size_ + 1 >= cap) {
			throw std::out_of_range("Implicit queue is full");
		}

		(*array_)[(startIndex_ + static_cast<int>(size_)) % cap] = data;

		/* vvvvv to iste ako riadok hore vvvvv
		if (startIndex_ + size_ >= cap) {
		(*array_)[size + startIndex_ - cap] = data;
		}
		else {
		(*array_)[size_ + startIndex_] = data;
		}
		*/
		size_++;
	}


	template<typename T>
	inline T ImplicitQueue<T>::pop() //dorobit
	{
		if (size_ == 0) {
			throw std::out_of_range("Implicit queue is empty");
		}
		T pom = (*array_)[(startIndex_)];
		startIndex_++;
		if (startIndex_ >= array_->size()) {
			startIndex_ = 0;
		}
		size_--;
		return pom;
	}

	template<typename T>
	inline T& ImplicitQueue<T>::peek() //dorobit
	{
		if (size_ == 0) {
			throw::std::length_error("Queue is empty");
		}

		return (*array_)[startIndex_];
	}

	template<typename T>
	inline const T ImplicitQueue<T>::peek() const //dorobit
	{
		if (size_ == 0) {
			throw::std::length_error("Queue is empty");
		}

		return (*array_)[startIndex_];
	}
}