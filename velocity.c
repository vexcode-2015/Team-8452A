// EasyC code for bang-bang
// team 8452A
//
#include "Main.h"

void bangTBH ( void )
{
      time += 1 ;
      encOld = encNew ;
      encNew = GetQuadEncoder ( 7 , 8 ) ;
      encVelocity = encNew - encOld ;
      v1 = v2 ;
      v2 = v3 ;
      v3 = encVelocity ;
      vavg = (v1+v2+v3)/3 ;
      current = vavg ;
      errorOld = errorNew ;
      errorNew = target - current ;
      if ( pidOn )
      {
            command = trueCommand ;
            command += errorNew*kbtbh ;
            if ( sign(errorNew) != sign(errorOld) )
            {
                  commandTBH = .5 * (commandTBH + command); ;
                  command = commandTBH ;
            }
            if ( command > 127 )
            {
                  command = 127 ;
            }
            if ( command < 0 )
            {
                  command = 0 ;
            }
            if ( time > 1 && madRush == 0 ) // essentially commented here
            {
                  //madRush = 1 ;
                  //command = 127 ;
            }
            trueCommand = command ;
            if ( target - vavg > bangLambda )
            {
                  command = 127 ;
                  bang = 1 ;
            }
            if ( bang == 1 && target - vavg <= bangLambda )
            {
                  command = trueCommand ;
                  bang = 0 ;
            }
      }
      if ( Abs(errorOld) < lambda && Abs(errorNew) < lambda )
      {
            flywheelAtSpeed = 1 ;
      }
      else
      {
            flywheelAtSpeed = 0 ;
      }
}
