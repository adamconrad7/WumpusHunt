#ifndef _event
#define _event

class Event{
public:
  Event() {};
  virtual ~Event() {} ;
  virtual void percept() = 0;
  virtual char symbol() = 0;
  virtual int encounter() = 0;
};

#endif
