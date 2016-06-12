
struct Element
{
  explicit Element(const char *p_msg);
  const char *msg;
  virtual void outputValue(ofstream& sdlog) const = 0;
};

template <class TYPE>
struct LogElement : public Element
{
  explicit LogElement(const char *p_msg, TYPE const val);
  void outputValue(ofstream& sdlog) const;
  TYPE const value;
};

struct ElementQueue
{
  ElementQueue();
  void push(Element* elem);
  bool peek() const;
  Element* pop();
  private:
  static const int maximum = 11;
  int numOf;
  Element* elems[maximum];
};
