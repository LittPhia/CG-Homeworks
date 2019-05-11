#pragma once
#include <cassert>
#include <iostream>

template <typename Type>
class DArray {
private:
	Type *m_data_pointer_;		// pointer that stores the array data
	size_t m_size_;				// number of elements in the array
	size_t m_volume_;			// volume of the array

private:
	inline bool validate_index (const size_t nIndex) const {
		if (nIndex > m_size_) return false;
		return true;
	}
	inline void free () {
		if (m_data_pointer_) delete[] m_data_pointer_;
		m_data_pointer_ = nullptr;
		m_size_ = 0;
	}

public:
	DArray () {
		m_data_pointer_ = new Type[1];
		m_size_ = 0;
		m_volume_ = 1;
	}
	DArray (const size_t nSize, const Type dValue) {
		assert (nSize != 0);
		m_data_pointer_ = new Type[nSize];
		m_size_ = m_volume_ = nSize;
		for (size_t i = 0; i < nSize; i++) {
			m_data_pointer_[i] = dValue;
		}
	} // initialize the array with size set as nSize, and default value dValue
	DArray (const DArray& array_b) {
		m_size_ = array_b.m_size_;
		m_volume_ = array_b.m_volume_;
		m_data_pointer_ = new Type[m_volume_];
		for (size_t i = 0; i < m_size_; i++) {
			m_data_pointer_[i] = array_b.m_data_pointer_[i];
		}
	} // copy construct function
	~DArray () {
		free();
	} // destruct function

	friend std::ostream &operator<<(std::ostream &out, const DArray &A) {
		if (A.m_size_ == 0) {
			out << "null" << std::endl;
			return out;
		}
		out << '[';
		for (size_t i = 0; i < A.m_size_ - 1; i++) {
			out << A[i] << ", ";
		}
		out << A[A.m_size_ - 1] << ']' << std::endl;
		return out;
	} // print the data in the array
	size_t size () const {
		return m_size_;
	} // get the size of the array
	void resize (const size_t nSize) {
		if (m_volume_ < nSize) {
			m_volume_ = nSize;
			Type *tmp = new Type[m_volume_];
			for (size_t i = 0; i < m_size_; i++) {
				tmp[i] = m_data_pointer_[i];
			}
			for (size_t i = m_size_; i < m_volume_; i++) {
				tmp[i] = 0.0;
			}
			delete[] m_data_pointer_;
			m_data_pointer_ = tmp;
		}
		for (size_t i = nSize; i < m_size_; i++) {
			m_data_pointer_[i] = 0.0;
		}
		m_size_ = nSize;
	} //resize the array. fill the space beyond the previous as defaulted value 0

	Type get (const size_t nIndex) const {
		assert (validate_index (nIndex));
		return m_data_pointer_[nIndex];
	}
	Type operator[](const size_t nIndex) const {
		assert (validate_index (nIndex));
		return m_data_pointer_[nIndex];
	}
	void set (const size_t nIndex, const Type value) {
		assert (validate_index (nIndex));
		m_data_pointer_[nIndex] = value;
	}
	Type& operator[](const size_t nIndex) {
		assert (validate_index (nIndex));
		return m_data_pointer_[nIndex];
	}

	void push_back (const Type value) {
		resize (m_size_ + 1);
		m_data_pointer_[m_size_ - 1] = value;
	}
	void del (const size_t nIndex) {
		assert (validate_index (nIndex));
		for (size_t i = nIndex; i < m_size_ - 1; i++) {
			m_data_pointer_[i] = m_data_pointer_[i + 1];
		}
		m_size_--;
	}
	void insert (const size_t nIndex, const Type value) {
		if (nIndex <= m_volume_)
			resize (m_size_ + 1);
		else
			resize (nIndex + 1);

		for (size_t i = 1; i < m_size_ - nIndex; i++) {
			m_data_pointer_[m_size_ - i] = m_data_pointer_[m_size_ - i - 1];
		}
		m_data_pointer_[nIndex] = value;
	}

	DArray& operator=(const DArray& array_b) {
		free();
		m_size_ = array_b.m_size_;
		m_volume_ = array_b.m_volume_;
		m_data_pointer_ = new Type[m_size_];
		for (size_t i = 0; i < m_size_; i++) m_data_pointer_[i] = array_b[i];
		return *this;
	}
};
