#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "counter.h"

using namespace std;

Counter::Counter()
{
   mTime = 0.0f;
   mDuration = 0.0f;
}

void Counter::Start(float duration)
{
   mTime = 0.0f;
   mDuration = duration;
}

bool Counter::Update(float dt)
{
   mTime += dt;
   if (mTime >= mDuration)
   {
      mTime = 0.0f;
      return true;
   }
   return false;
}



