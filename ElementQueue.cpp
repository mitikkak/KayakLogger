
#include "fstream_headers.h"
#include "ElementQueue.h"

Element::Element(const char *p_msg): msg(p_msg) {}
Element::~Element()
{
//    printf("\n element %s at %p IS DYING", msg, this);
}

template <class TYPE>
LogElement<TYPE>::LogElement(const char *p_msg, TYPE const val):
  Element(p_msg), value(val)
{
}
template class LogElement<unsigned long>;
template class LogElement<float>;
template class LogElement<int>;
template class LogElement<double>;
template class LogElement<unsigned int>;

template <class TYPE>
void LogElement<TYPE>::outputValue(ofstream& sdlog) const
{
  sdlog << value;
}
ElementQueue::ElementQueue():
numOf(0)
{ for (int i = 0; i < maximum; i++) {elems[i] = 0;} }
ElementQueue::~ElementQueue()
{
}

ElementQueue::ElementQueue(const ElementQueue& another)
{
    numOf = 0;
    for(int i = 0; i < another.numOf; i++)
    {
        this->push(another.elems[i]);
    }
}

void ElementQueue::push(Element* elem)
{
  if (numOf < maximum)
  {
    elems[numOf] = elem;
//    printf("\n push %s at %p", elem->msg, elem);
    numOf++;
  }
}
bool ElementQueue::peek() const
{
  return (numOf>0);
}
Element* ElementQueue::pop()
{
  if (numOf > 0)
  {
    numOf--;
    Element* ret = elems[numOf];
    elems[numOf] = 0;
    return ret;
  }
  return 0;
}
