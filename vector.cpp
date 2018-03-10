#include "vector.h"
#include "ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),    //memmory_ = calloc(size,1)  //alokuje a vr·ti odkaz na pam‰ù, pojme size prvkov o velkosti 1 (vysledna pam‰t ma 1*size bytov)
		size_(size)                  //size_ = size; 
		{
	}

	Vector::Vector(const Vector& other) :       //kopia pam‰te spravovanej vektorom other
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size()); //kopiruje size bitov z pam‰te zaËinajucej na memory_ do pam‰te zaËinajucej na other.menory_
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other) {
			size_ = other.size_;
			memory_ = realloc(memory_, size_);
			memcpy(memory_, other.memory_, size_);
			}
		return  *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		return size_ == other.size_ && memcmp(memory_, other.memory_, size_);
	}

	byte& Vector::operator[](const int index) //vracia objekt adresou, pracujeme s kopiou
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index"); //aby index nebol v‰ËöÌ ako size
		return *(reinterpret_cast<byte*>(memory_) + index);		//moze tam byt aj char unsigned char...(chceme sa posuvat po jednom)
	}

	byte Vector::operator[](const int index) const //pristupujem priamo
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index"); //aby index nebol v‰ËöÌ ako size
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest) //zoberie prvok na poziicii index, count = kolko prvkov zoberie :D
	{
		DSRoutines::rangeCheck(index, size_, true);
		DSRoutines::rangeCheck(index + count + 1, size_, true);
		DSRoutines::rangeCheck(count, size_, true);

		memcpy(&dest, reinterpret_cast<byte*>(memory_) + index, count);
		return dest;
	}


	//src - z kade kopirujeme, 2 - na ktorom bite zaËinam, 3 kam kopirujem 4 nna ktorom vektore zaËinam  5 - kolko bitov idem kopirovaù
	//ak je lenght 0  nech to niË nerobi
	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		DSRoutines::rangeCheck(srcStartIndex, src.size_, true);
		DSRoutines::rangeCheck(srcStartIndex + length - 1, src.size_, true);
		DSRoutines::rangeCheck(length, dest.size_ + 1, true);
		DSRoutines::rangeCheck(destStartIndex, dest.size_, true);
		DSRoutines::rangeCheck(destStartIndex + length - 1, dest.size_, true);

		if (&src != &dest)
		{
			memcpy(reinterpret_cast<byte*>(dest.memory_) + destStartIndex,
				reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
		}
		else
		{
			memmove(reinterpret_cast<byte*>(dest.memory_) + destStartIndex,
				reinterpret_cast<byte*>(src.memory_) + srcStartIndex, length);
		}
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index"); 
		return reinterpret_cast<byte*>(memory_) + index;
	}

}