#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

struct p_t
{
  int x;
  int y;
};

int safeAdd(int a, int b)
{
  if ((b > 0 && a > std::numeric_limits< int >::max() - b)
      || (b < 0 && a < std::numeric_limits< int >::min() - b))
  {
    throw std::logic_error("Overflow");
  }

  return a + b;
}

class Ints
{
public:
  Ints();
  Ints(size_t size, int value);
  Ints(const Ints & rhs);
  Ints(Ints && rhs) noexcept;
  Ints & operator=(const Ints & rhs);
  Ints & operator=(Ints && rhs) noexcept;
  Ints operator+(const Ints & rhs) const;
  ~Ints();

  size_t getSize() const noexcept;
  void set(size_t id, int i) noexcept;
  int get(size_t id) const noexcept;
  void setSafe(size_t id, int i);
  int getSafe(size_t id) const;

  Ints append(int i) const;
  Ints append(const Ints & b) const;

  static Ints unitializatedInts(size_t size);

private:
  void resize();
  size_t capacity_;
  size_t size_;
  int * data_;
};

Ints::Ints():
  capacity_(0),
  size_(0),
  data_(nullptr)
{}

Ints::Ints(size_t size, int value):
  capacity_(size),
  size_(size),
  data_(new int [size])
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = value;
  }
}

Ints Ints::unitializatedInts(size_t size)
{
  Ints temp;
  temp.capacity_ = size;
  temp.data_ = new int [size];

  return temp;
}

Ints::Ints(const Ints & rhs):
  capacity_(rhs.size_),
  size_(rhs.size_),
  data_(new int [rhs.size_])
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

Ints::Ints(Ints && rhs) noexcept:
  capacity_(rhs.capacity_),
  size_(rhs.size_),
  data_(rhs.data_)
{
  rhs.capacity_ = 0;
  rhs.size_ = 0;
  rhs.data_ = nullptr;
}

Ints & Ints::operator=(const Ints & rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  Ints temp(rhs);

  std::swap(capacity_, temp.capacity_);
  std::swap(size_, temp.size_);
  std::swap(data_, temp.data_);

  return *this;
}

Ints & Ints::operator=(Ints && rhs) noexcept
{
  if (this != &rhs)
  {
    delete [] data_;

    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_ = rhs.data_;

    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.data_ = nullptr;
  }

  return *this;
}

Ints Ints::operator+(const Ints & rhs) const
{
  if (getSize() != rhs.getSize())
  {
    throw std::invalid_argument("Arrays have different size");
  }

  Ints result(getSize(), 0);
  for (size_t i = 0; i < getSize(); ++i)
  {
    result.set(i, safeAdd(get(i), rhs.get(i)));
  }

  return result;
}

Ints::~Ints()
{
  delete [] data_;
}

size_t Ints::getSize() const noexcept
{
  return size_;
}

void Ints::set(size_t id, int i) noexcept
{
  data_[id] = i;
}

int Ints::get(size_t id) const noexcept
{
  return data_[id];
}

void Ints::setSafe(size_t id, int i)
{
  if (id >= size_)
  {
    throw std::logic_error("Invalid value");
  }

  set(id, i);
}

int Ints::getSafe(size_t id) const
{
  if (id >= size_)
  {
    throw std::logic_error("Invalid value");
  }

  return get(id);
}

void Ints::resize()
{
  size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
  int * newData = new int [newCapacity];

  for (size_t i = 0; i < size_; ++i)
  {
    newData[i] = data_[i];
  }

  delete [] data_;
  data_ = newData;
  capacity_ = newCapacity;
}

Ints Ints::append(int i) const
{
  Ints result(*this);

  if (result.capacity_ < result.size_ + 1)
  {
    result.resize();
  }

  result.data_[result.size_] = i;
  ++result.size_;

  return result;
}

Ints Ints::append(const Ints & b) const
{
  Ints result = unitializatedInts(size_ + b.size_);

  for (size_t i = 0; i < size_; ++i)
  {
    result.data_[i] = data_[i];
  }
  for (size_t i = 0; i < b.size_; ++i)
  {
    result.data_[size_ + i] = b.data_[i];
  }
  result.size_ = size_ + b.size_;

  return result;
}

void printInts(const Ints & a)
{
  for (size_t i = 0; i < a.getSize(); ++i)
  {
    std::cout << a.get(i) << ' ';
  }
  std::cout << '\n';
}

class Points
{
public:
  size_t getSize() const noexcept;
  void set(size_t id, p_t p);
  p_t get(size_t id) const;
  Points append(p_t p) const;

private:
  Ints data_;
};

size_t Points::getSize() const noexcept
{
  return data_.getSize() / 2;
}

void Points::set(size_t id, p_t p)
{
  if (id >= getSize())
  {
    throw std::logic_error("Invalid value");
  }

  data_.set(2 * id, p.x);
  data_.set(2 * id + 1, p.y);
}

p_t Points::get(size_t id) const
{
  if (id >= getSize())
  {
    throw std::logic_error("Invalid value");
  }

  return {data_.get(2 * id), data_.get(2 * id + 1)};
}

Points Points::append(p_t p) const
{
  Points result;
  result.data_ = data_.append(p.x).append(p.y);

  return result;
}

int main()
{
  Ints a(3, 67);
  Ints b(3, 69);
  Ints c = a + b + a;
  printInts(c);

  Ints d = c.append(1).append(a);
  printInts(d);

  Points pts;
  pts = pts.append({1, 2}).append({3, 4});
  pts.set(0, {5, 6});
  for (size_t i = 0; i < pts.getSize(); ++i)
  {
    p_t p = pts.get(i);
    std::cout << '(' << p.x << ", " << p.y << ") ";
  }
  std::cout << '\n';
}

