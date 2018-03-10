#pragma once
#pragma once

#include "priority_queue_list.h"
#include "array_list.h"
#include <exception>

namespace structures
{
	/// <summary> Prioritny front implementovany haldou. Implementujucim typom haldy je struktura ArrayList. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class Heap : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Heap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Halda, z ktorej sa prevezmu vlastnosti. </param>
		Heap(const Heap<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat haldy. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany zoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak vstupny parameter nie je halda. </exception>  
		/// <remarks> Vyuziva typovy operator priradenia. </remarks>
		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;

		/// <summary> Operator priradenia pre haldu. </summary>
		/// <param name = "other"> Halda, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato halda nachadza po priradeni. </returns>
		virtual Heap<T>& operator=(const Heap<T>& other);

		/// <summary> Vlozi prvok s danou prioritou do haldy. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(const int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z haldy. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je halda prazdna. </exception>  
		T pop() override;

	protected:
		/// <summary> Vrati index v ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je ArrayList prazdny. </exception>  
		int indexOfPeek() const override;

	private:
		/// <summary> Vrati index v ArrayList-e, na ktorom by sa mal nachadzat otec daneho prvku. </summary>
		/// <param name = "index"> Index prvku, ktoreho otca chceme vratit. </param>
		/// <returns> Index, na ktorom ba sa mal nachadzat otec prvku. </returns>
		int getParentIndex(const int index);

		/// <summary> Vrati index v ArrayList-e, na ktorom by mal mat dany prvok syna s najvacsou prioritou. </summary>
		/// <param name = "index"> Index prvku, ktoreho syna chceme vratit. </param>
		/// <returns> Index, na ktorom by sa mal nachadzat syn prvku. </returns>
		int getGreaterSonIndex(const int index);
	};

	template<typename T>
	Heap<T>::Heap() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	Heap<T>::Heap(const Heap<T>& other) :
		Heap<T>()
	{
		*this = other;
	}

	template<typename T>
	Structure* Heap<T>::clone() const
	{
		return new Heap<T>(*this);
	}

	template<typename T>
	inline PriorityQueueList<T>& Heap<T>::operator=(const PriorityQueueList<T>& other)
	{
		return *this = dynamic_cast<const Heap<T>&>(other);
	}

	template<typename T>
	inline Heap<T>& Heap<T>::operator=(const Heap<T>& other)
	{
		if (this != &other)
		{
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	void Heap<T>::push(const int priority, const T& data)
	{
		PriorityQueueItem<T>* newItem = new PriorityQueueItem<T>(priority, data);
		list_->add(newItem);
		int curIndex = list_->size() - 1;
		int parentIndex = getParentIndex(curIndex);
		while (parentIndex >= 0 && (*list_)[parentIndex]->getPriority() > (*list_)[curIndex]->getPriority()) {
			DSRoutines::swap<PriorityQueueItem<T>*>((*list_)[parentIndex], (*list_)[curIndex]);
			curIndex = parentIndex;
			parentIndex = getParentIndex(curIndex);
		}
	}

	template<typename T>
	T Heap<T>::pop()
	{
		T pom = (*list_)[0]->accessData();
		delete (*list_)[0];
		(*list_)[0] = (*list_)[list_->size() - 1];
		list_->removeAt(list_->size() - 1);
		int curIndex = 0;
		unsigned int sonIndex = getGreaterSonIndex(curIndex);
		while (sonIndex < list_->size() && (*list_)[sonIndex]->getPriority() < (*list_)[curIndex]->getPriority()) {

			DSRoutines::swap<PriorityQueueItem<T>*>((*list_)[sonIndex], (*list_)[curIndex]);
			curIndex = sonIndex;
			sonIndex = getGreaterSonIndex(curIndex);

		}
		return pom;
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(const int index)
	{
		return (index - 1) / 2;
	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(const int index)
	{
		unsigned int lsonIndex = 2 * index + 1;
		unsigned int psonIndex = 2 * index + 2;

		PriorityQueueItem<T>* lSon = lsonIndex < list_->size() ? (*list_)[lsonIndex] : nullptr;
		PriorityQueueItem<T>* pSon = psonIndex < list_->size() ? (*list_)[psonIndex] : nullptr;
		if (lSon != nullptr && pSon != nullptr) {
			return lSon->getPriority() < pSon->getPriority() ? lsonIndex : psonIndex;

		}
		else {

			return lsonIndex;
		}
	}

	template<typename T>
	inline int Heap<T>::indexOfPeek() const
	{
		return 0;
	}
}