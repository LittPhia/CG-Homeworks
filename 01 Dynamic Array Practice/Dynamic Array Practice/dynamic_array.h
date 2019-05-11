#pragma once
#include <iostream>

class DArray {
private:
	double *m_data_pointer_;		// pointer that stores the array data
	size_t m_size_;			// number of elements in the array

private:
	inline bool validate_index(const size_t nIndex) const {
		if (nIndex > m_size_) return false;
		return true;
	};
	inline void free() {
		if(m_data_pointer_) delete[] m_data_pointer_;
		m_data_pointer_ = nullptr;
		m_size_ = 0;
	}

public:
	DArray();
	DArray(const size_t nSize, const double dValue = 0);		// initialize the array with size set as nSize ,and default value dValue
	DArray(const DArray& array_b);	// copy construct function
	~DArray();						// destruct function

	friend std::ostream &operator<<(std::ostream &out, const DArray &A);	// print the data in the array
	size_t size() const;				// get the size of the array
	void resize(const size_t nSize);		//resize the array. fill the space beyond the previous as defaulted value 0

	double get(const size_t nIndex) const;
	double operator[](const size_t nIndex) const;
	void set(const size_t nIndex, const double value);
	double& operator[](const size_t nIndex);

	void push_back(const double value);
	void del(const size_t nIndex);
	void insert(const size_t nIndex, const double value);

	DArray& operator=(const DArray& array_b);
};
