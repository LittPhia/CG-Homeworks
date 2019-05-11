#include <cassert>
#include "dynamic_array.h"

DArray::DArray () {
	m_data_pointer_ = nullptr;
	m_size_ = 0;
}

DArray::DArray (const size_t nSize, const double dValue) {
	m_data_pointer_ = new double[nSize];
	m_size_ = nSize;
	for (size_t i = 0; i < nSize; i++) {
		m_data_pointer_[i] = dValue;
	}
}

DArray::DArray (const DArray &array_b) {
	m_size_ = array_b.m_size_;
	m_data_pointer_ = new double[m_size_];
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
	double *tmp = new double[nSize];
	size_t n = nSize;
	if (n > m_size_) n = m_size_;
	for (size_t i = 0; i < n; i++) {
		tmp[i] = m_data_pointer_[i];
	}
	for (size_t i = n; i < nSize; i++) {
		tmp[i] = 0.0;
	}
	if (m_data_pointer_) delete[] m_data_pointer_;
	m_data_pointer_ = tmp;
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
	if (m_size_ == 1) {
		delete[] m_data_pointer_;
		m_data_pointer_ = nullptr;
		m_size_ = 0;
		return;
	}

	double *tmp = new double[m_size_ - 1];
	for (size_t i = 0; i < nIndex; i++) {
		tmp[i] = m_data_pointer_[i];
	}
	for (size_t i = nIndex; i < m_size_ - 1; i++) {
		tmp[i] = m_data_pointer_[i + 1];
	}
	delete[] m_data_pointer_;		//if m_pData == nullptr, program would abort at assert sentence in line 82.
	m_data_pointer_ = tmp;
	m_size_--;
}

void DArray::insert (const size_t nIndex, const double value) {
	if (nIndex >= m_size_) {
		resize (nIndex + 1);
		m_data_pointer_[nIndex] = value;
		return;
	}
	double *tmp = new double[m_size_ + 1];
	for (size_t i = 0; i < nIndex; i++) {
		tmp[i] = m_data_pointer_[i];
	}
	tmp[nIndex] = value;
	for (size_t i = nIndex + 1; i < m_size_ + 1; i++) {
		tmp[i] = m_data_pointer_[i - 1];
	}
	if (m_data_pointer_) delete[] m_data_pointer_;
	m_data_pointer_ = tmp;
	m_size_++;
}

DArray &DArray::operator=(const DArray &array_b) {
		free ();
	m_size_ = array_b.m_size_;
	m_data_pointer_ = new double[m_size_];
	for (size_t i = 0; i < m_size_; i++) m_data_pointer_[i] = array_b[i];
	return *this;
}