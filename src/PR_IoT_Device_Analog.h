#ifndef PR_IoT_Device_Analog_h
#define PR_IoT_Device_Analog_h

    #include <arduino.h>
    #include <PR_IoT.h>
	
	#ifndef	PR_ADC_ZERO
		#define	PR_ADC_ZERO		0		//
	#endif
	#ifndef	PR_ADC_MAX
		#define	PR_ADC_MAX		1024		//
	#endif
	
class PR_IoT_Analog : public PR_IoT_DeviceClass {
        public:
            PR_IoT_Analog(String name) : PR_IoT_DeviceClass(name)	{ } 

            void 	announce();
            void 	update();
            virtual void 	inMsgCallback(); 
            virtual void 	setupHW(uint8_t pin);			
			virtual void	loopHW()			{ }	

			void		setupHWCalibration(uint16_t lowest, uint16_t highest, bool isInverse);
			uint8_t		getValuePercentage();		
        protected:
			uint16_t 	_lowest 	= PR_ADC_ZERO;
			uint16_t 	_highest 	= PR_ADC_MAX;
			bool 		_isInverse 	= false;
			uint8_t 	_pin;
    };
	
#endif