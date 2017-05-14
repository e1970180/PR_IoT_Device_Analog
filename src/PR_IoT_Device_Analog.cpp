#include "PR_IoT_Device_Analog.h"

    #include <arduino.h>    

	void 	PR_IoT_Analog::announce() {
		postMsg("analog", "HELLO"); 
	}
	
	void 	PR_IoT_Analog::setupHW(uint8_t pin) {
		_pin = pin;
	}   
	
	void	PR_IoT_Analog::setupHWCalibration(uint16_t lowest, uint16_t highest, bool isInverse) {
		_lowest = lowest;
		_highest = highest;
		_isInverse = isInverse;
	}
	
	uint8_t	PR_IoT_Analog::getValuePercentage() {
		uint16_t adc = analogRead(_pin);
		delay(5);							//delay is a must to solve analogRead interference with WiFi like connection lost (https://github.com/esp8266/Arduino/issues/1634)
		if (_isInverse) adc = PR_ADC_MAX - adc;
		
		adc = constrain(adc, _lowest, _highest);
		return map(adc,  _lowest, _highest, 0, 100);
	}
	
	void	PR_IoT_Analog::update() {
		
		postMsg ("analog[%]", String(getValuePercentage())  );
	}
	
	void	PR_IoT_Analog::inMsgCallback() {

		PR_DBGTLN("Swithc: Msg got")
		PR_DBGVLN(inMsg.payload)
		
		if (inMsg.payload == "GET")	{
			update();
		}
	}
	
