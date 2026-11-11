#include <utility>
#include <cstddef>
#include <limits>

class Ints
{
public:
  Ints();
  Ints(size_t size, int value);
  Ints(const Ints & rhs);
  Ints & Ints::operator=(const Ints & rhs);
  ~Ints();

  size_t getSize() const noexcept;
  void set(size_t id, int i) noexcept;
  int get(size_t id) const noexcept;
  void setSafe(size_t id, int i);
  int getSafe(size_t id) const;

  Ints append(int i);
  Ints append(Ints b);

  static Ints unitializatedInts(size_t size);

private:
  void resize();
  size_t capacity_;
  size_t size_;
  int * data_;
};

Ints::Ints():
  size(0),
  data(nullptr),
{}

Ints::Ints(size_t size, int value):
  size(size),
  data(new int [size])
{
  for (size_t i = 0; i < size, ++i)
  {
    data[i] = value;
  }
}

static Ints::Ints Ints::unitializatedInts(size_t size)
{
  Ints temp;
  temp.size = size;
  temp.data = new int [size];

  return temp;
}

Ints::Ints(const Ints & rhs):
  size(rhs.size),
  data(new int [size])
{
  for (size_t i = 0; i < size; ++i)
  {
    data[i] = rhs.data[i];
  }
}

Ints & Ints::operator=(const Ints & rhs)
{
  if (this == &rhs)
  {
    return *this;
  }

  Ints temp(rhs);

  std::swap(size, temp.size)
  std::swap(data, temp.data)

  return *this;
}

Ints::~Ints()
{
  delete [] data;
}

size_t getSize() const noexcept
{
  return size;
}

void Ints::set(size_t id, int i)
{
  data[id] = i;
}

int Ints::get(size_t id)
{
  return data[id];
}

void Ints::setSafe(size_t id, int i)
{
  if (id > size)
  {
    throw std::logic_error("Invalid value");
  }

  set(id, i);
}

int Ints::getSafe(size_t id)
{
  if (id > size)
  {
    throw std::logic_error("Invalid value");
  }

  return get(id);
}


Ints Ints::append(int i)
{
  Ints result(*this);

  if (result.capacity < result.size + 1)
  {
    result.resize();
  }

  result.data[size] = i;
  ++result.size;

  return result;
}

Ints append(Ints b)
{
  Ints result(*this);

  if ()
  {

  }
}

class Mtx
{
public:
  Mtx();
  Mtx(size_t m, size_t n);
  ~Mtx() = default;
  Mtx sum(const Mtx & oth) const;
  Ints getCol(size_t id);
  Ints getRow(size_t id);
private:
  size_t m;
  size_t n;
  Ints data;
};


Mtx::Mtx():
  m(0),
  n(0),
{}

Mtx::Mtx(size_t m, size_t n):
  m(m),
  n(n),
{
  if (m > std::numeric_limits< size_t >::max() / n)
  {
    throw std::logic_error("Owerflow");
  }

  data(n * m, 0);
}

Mtx Mtx::sum(const Mtx & oth) const
{
  Mtx res(m, n);
  for (size_t i = 0; i < data.getSize(); ++i)
  {
    if (oth.data.get(i) > std::numeric_limits< size_t >::max() - data.get(i))
    {
      throw std::logic_error("Owerflow");
    }

    res.data.set(i, oth.data.get(i) + data.get(i));
  }

  return res;
}

Ints Mtx::getCol(size_t id)
{
  Ints res(m, 0);
  for (size_t i = 0; i < m; ++i)
  {
    res.append(i * n + id);
  }

  return res;
}

Ints Mtx::getRow(size_t id)
{
  Ints res(n, 0);
  for (size_t i = 0; i < n; ++i)
  {
    res.append(id * m + i);
  }

  return res;
}

Mtx Mtx::mul(const Mtx & oth) const;
{
  //mn np = mp
  //m1n1 m2n2 = m1n2
  Mtx res(m, oth.n);
  int sm = 0;
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < oth.n; ++j)
    {
      Ints row = getRow(i);
      Ints col = oth.getCol(j);

      sm = 0;
      for (size_t z = 0; z < m; z++)
      {
        sm += row[z] * col[z]
      }

      res.data.set(i * n + j, sm);
    }
  }

  return res;
}

int main()
{
  Ints a(10, 67);
  Ints b(10, 69);
  Ints c = a + b + a + b + a;
}

