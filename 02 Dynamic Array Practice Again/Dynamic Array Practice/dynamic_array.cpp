#include <cassert>
#include "dynamic_array.h"

DArray::DArray () {
	m_data_pointer_ = new double[1];
	m_size_ = 0;
	m_volume_ = 1;
}

DArray::DArray (const size_t nSize, const double dValue) {
	assert (nSize != 0);
	m_data_pointer_ = new double[nSize];
	m_size_ = m_volume_ = nSize;
	for (size_t i = 0; i < nSize; i++) {
		m_data_pointer_[i] = dValue;
	}
}

DArray::DArray (const DArray &array_b) {
	m_size_ = array_b.m_size_;
	m_volume_ = array_b.m_volume_;
	m_data_pointer_ = new double[m_volume_];
	for (size_t i = 0; i < m_size_; i++) {
		m_data_pointer_[i] = array_b.m_data_pointer_[i];
	}
}

DArray::~DArray () {
	this->free ();
}

std::ostream& operator<<(std::ostream& out, const DArray& A) {
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
}

size_t DArray::size () const {
	return m_size_;
}

void DArray::resize (const size_t nSize) {
	if (m_volume_ < nSize) {
		if (m_volume_ * 2 > nSize)
			m_volume_ *= 2;
		else
			m_volume_ = nSize;
		double *tmp = new double[m_volume_];
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
}

double DArray::get (const size_t nIndex) const {
	assert (validate_index (nIndex));
	return m_data_pointer_[nIndex];
}

double DArray::operator[](const size_t nIndex) const {
	assert (validate_index (nIndex));
	return m_data_pointer_[nIndex];
}

void DArray::set (const size_t nIndex, const double value) {
	assert (validate_index (nIndex));
	m_data_pointer_[nIndex] = value;
}

double& DArray::operator[](const size_t nIndex) {
	assert (validate_index (nIndex));
	return m_data_pointer_[nIndex];
}

void DArray::push_back (const double value) {
	resize (m_size_ + 1);
	m_data_pointer_[m_size_ - 1] = value;
}

void DArray::del (const size_t nIndex) {
	assert (validate_index (nIndex));
	for (size_t i = nIndex; i < m_size_ - 1; i++) {
		m_data_pointer_[i] = m_data_pointer_[i + 1];
	}
	m_size_--;
}

void DArray::insert (const size_t nIndex, const double value) {
	if (nIndex <= m_volume_)
		resize (m_size_ + 1);
	else
		resize (nIndex + 1);

	for (size_t i = 1; i < m_size_ - nIndex; i++) {
		m_data_pointer_[m_size_ - i] = m_data_pointer_[m_size_ - i - 1];
	}
	m_data_pointer_[nIndex] = value;
}

DArray &DArray::operator=(const DArray &array_b) {
	free ();
	m_size_ = array_b.m_size_;
	m_volume_ = array_b.m_volume_;
	m_data_pointer_ = new double[m_size_];
	for (size_t i = 0; i < m_size_; i++) m_data_pointer_[i] = array_b[i];
	return *this;
}