
#include "ElementQueue.h"

Element::Element(const char *p_msg): msg(p_msg) {}

template <class TYPE>
LogElement<TYPE>::LogElement(const char *p_msg, TYPE const val):
  Element(p_msg), value(val)
{
}
template <class TYPE>
void LogElement<TYPE>::outputValue(ofstream& sdlog) const
{
  sdlog << value;
}
ElementQueue::ElementQueue():
numOf(0)
{ for (int i = 0; i < maximum; i++) {elems[i] = 0;} }

void ElementQueue::push(Element* elem)
{
  if (numOf < maximum)
  {
    elems[numOf] = elem;
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
    return elems[numOf];
  }
  return 0;
}
