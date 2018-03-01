
#ifndef _ELEMENT_QUEUE_H
#define _ELEMENT_QUEUE_H

struct Element
{
  explicit Element(const char *p_msg);
  ~Element();
  const char *msg;
#ifndef ESP8266
  virtual void outputValue(ofstream& sdlog) const = 0;
#else
  virtual void outputValue(String& str) const = 0;
#endif
};

template <class TYPE>
struct LogElement : public Element
{
  explicit LogElement(const char *p_msg, TYPE const val);
#ifndef ESP8266
  void outputValue(ofstream& sdlog) const;
#else
  void outputValue(String& str) const;
#endif
  TYPE const value;
};

struct ElementQueue
{
  ElementQueue();
  ~ElementQueue();
  ElementQueue(const ElementQueue& another);
  void push(Element* elem);
  bool peek() const;
  Element* pop();

private:
  static const int maximum = 11;
  int numOf;
  Element* elems[maximum];

};

#endif
