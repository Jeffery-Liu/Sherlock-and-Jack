#ifndef INCLUDED_COUNTER_H
#define INCLUDED_COUNTER_H

//====================================================================================================
// Filename:	counter.h
// Description:	Class for a time.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <SGE.h>
using namespace SGE;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Counter
{
public:
   Counter();
   void Start(float duration);
   bool Update(float dt);
   float GetTime() {return (60.0-mTime);}
private:
   float mTime;
   float mDuration;
};


#endif // #ifndef INCLUDED_COUNTER_H