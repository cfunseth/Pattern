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
			void clear(void);

			// Configuration functions
			void setStyle(uint8_t style);
			void setDirection(uint8_t direction);
			void setSpeed(uint16_t speed);
			void setSize(uint8_t size);
			
			// Update should be called every loop of the main function
			// Returns true when an update has been performed
			bool getUpdate(void);

			// Returns the value in the pattern array
			uint8_t getValue(uint8_t position);
						
		private:
			uint8_t _size;
			uint8_t *_array;
			uint8_t _style;
			uint8_t _direction;
			uint16_t _speed;
			uint8_t _position;
			bool _running;
			
			uint32_t	_timer;
	};
#endif
