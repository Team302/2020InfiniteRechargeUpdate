
//====================================================================================================================================================
// Copyright 2019 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================


// C++ Includes
#include <memory>

// FRC includes
#include <frc/Counter.h>

// Team 302 includes
#include <hw/interfaces/IDragonSensor.h>
#include <hw/interfaces/IDragonDistanceSensor.h>
#include <hw/DragonUltrasonicPWM.h>

// Third Party Includes



using namespace std;
using namespace frc;

DragonUltrasonicPWM::DragonUltrasonicPWM
(
	IDragonSensor::SENSOR_USAGE usage, 
	int digitalPinChannel
) : IDragonSensor(),
	IDragonDistanceSensor(),
	m_pulseWidthCounter( make_unique<Counter>(digitalPinChannel)),
	m_usage(usage)
{
	m_pulseWidthCounter->SetSemiPeriodMode(true);
}


///-----------------------------------------------------------------------
/// Method:      GetDistance
/// Description: Return the measured distance in inches
/// Returns:     double     Measured Distance
///-----------------------------------------------------------------------
double DragonUltrasonicPWM::GetDistance() const 
{
	double m_conversion = m_pulseWidthCounter->GetPeriod().to<double>();
	return m_conversion * 100000.0 * 0.393701;
}


///-----------------------------------------------------------------------
/// Method:      GetConfidence
/// Description: Indicates how accurate the returned value is
/// Returns:     double    0.0 == ignore (sensor has an error)
///                        1.0 == very confident 
///-----------------------------------------------------------------------
double DragonUltrasonicPWM::GetConfidence() const
{
    return 1.0;
}

///-----------------------------------------------------------------------
/// Method:      GetUsage
/// Description: Indicate what the sensor is used for
/// Returns:     SENSOR_USAGE    sensor usage 
///-----------------------------------------------------------------------
IDragonSensor::SENSOR_USAGE DragonUltrasonicPWM::GetUsage() const 
{
	return m_usage;
}
