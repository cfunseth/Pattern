
#ifndef Pattern_h
  #define Pattern_h
  
  #if (ARDUINO >= 100)
    #include "Arduino.h"
  #else
    #include "WProgram.h"
  #endif
	
	class Pattern
	{
		public:
			// Constructor & deconstructor
			Pattern(uint8_t size);
			~Pattern(void);
			
			// Control functions
			void start(void);
			void stop(void);
      void reset(void);

			// Configuration functions
			void setStyle(uint8_t style);
			void setSpeed(uint16_t speed);
			void setLimit(uint8_t limit);

      // Update should be called every loop of the main function
			bool update(void); 

      // Status functions
			uint8_t getValue(uint8_t position);
			uint8_t getCycles(void);
						
     private:
			uint8_t *_array;
      uint8_t _cycles;
      uint8_t _direction;
      uint8_t _limit;
      uint8_t _position;
      bool _running;
      uint8_t _random;
			uint8_t _size;
      uint16_t _speed;
			uint8_t _style;
      uint32_t  _timer;
      
			void clear(void);
	};
#endif
