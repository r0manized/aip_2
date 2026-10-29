#include <cstddef>
struct int_view {
  int_view();
  int_view(int* b, size_t sz);
  int_view(int* b, int* e);
  int_view sub_view(size_t start) const;
  int_view end_view(size_t end) const;
  int_view sub_view(size_t start, size_t end) const;

  size_t get_size() const;
  int get(size_t id) const;
  int at(size_t id) const;

 private:
  int* begin;
  size_t size;
};
int at(int_view v, size_t id) {
  if (!(id < size)) {
    throw std::logic_error("");
  }
  return v.get(id);
}
int int_view::get(size_t id) const {
  return begin[id];
}
int int_view::at(size_t id) const {
  if (!(id < size)) {
    throw std::logic_error("");
  }
  return get(id);
}
int_view int_view::sub_view(size_t start) const {
  // ?...
  int_view v(begin + start, size - start);
  return v;
}
size_t int_view::get_size() const {
  return size;
}
int_view::int_view(int* b, size_t sz):
 begin(b), size(sz)
{}
int_view::int_view(int* b, int* e):
 begin(b), size(e - b)
{}
int_view::int_view():
 begin(nullptr), size(0)
{}

void count(int_view a)
{}
int b[10] = {};
int main() {
  int a[10] = {};
  int* c = new int[10];

  int_view a1{a, 10};
  for (size_t i = 0; i < a1.get_size(); ++i) {
    std::cout << a1.get(i) << "\n";
  }
  size_t id = 0;
  std::cin >> id;
  at(a1, id);
  int_view a2 = a1.sub_view(5);

  delete [] c;
}
