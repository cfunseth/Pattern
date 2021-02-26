#include "Pattern.h"

Pattern::Pattern(uint8_t size)
{
	// Initiate the array that will contain the pattern values and then reset everything
	_size = size;
	_array = (uint8_t*)malloc(_size * sizeof(uint8_t));
  clear();
	reset();
}

Pattern::~Pattern(void) 
{
	// Free up the memory we allocated for the array values
	free(_array);
}

void Pattern::start(void)
{
	_running = true;
}

void Pattern::stop(void)
{
	_running = false;
}

void Pattern::reset(void)
{
	// Completely resets the pattern except for the size
	
	_style = 3;	// Default the style to "Chase"
	_direction = 0;
	_speed = 500;	// Default the speed to 0.5 seconds
	_running = false;
}

void Pattern::clear(void)
{
	// Clears all of the array values and resets the position and direction
	
	_position = 0;
	_direction = 0;
	
	for(uint8_t i = 0; i < _size; i++)
	{
		_array[i] = 0;
	}	
}

void Pattern::setStyle(uint8_t style)
{
	// Updates the pattern style and clears the array
	
	_style = style;
	
	clear();
}

void Pattern::setDirection(uint8_t direction)
{
	// Updates the direction to be forward (0) or backwards (1)
	
	_direction = direction;
	
	clear();
}

void Pattern::setSpeed(uint16_t speed)
{
	// Updates the time delay (in milliseconds) between each array element updating
	
	_speed = speed;
}

void Pattern::setSize(uint8_t size)
{
	// To-do: Add feature for dynamically adjusting the array size
}

bool Pattern::getUpdate(void)
{

	if( (millis() - _timer) >= _speed && _running)
	{
		// Update timer to new value
		_timer = millis();
		
		switch(_style) {
			case 0:
				// All Off
				for(uint8_t i = 0; i < _size; i++)
				{
					_array[i] = 0;
				}
				break;
			case 1:
				// All On
				for(uint8_t i = 0; i < _size; i++)
				{
					_array[i] = 1;
				}
				break;
			case 2:
				// Blink All
				// The _position value is used to track whether the values are high or low
				if(_position == 0)
				{
					_position = 1;
					for(uint8_t i = 0; i < _size; i++)
					{
						_array[i] = 1;
					}
				}
				else
				{
					_position = 0;
					for(uint8_t i = 0; i < _size; i++)
					{
						_array[i] = 0;
					}
				}
				break;
			case 3:
				// Chase
				// The pattern will move up the array only keeping one value high and then loop around to the beginning
				if(_position == 0)
				{
					_array[_position] = 1;
					_array[_size - 1] = 0;	// Make sure to clear the last value in the array after it loops around
					_position++;
				}
				else if(_position < _size)
				{
					_array[_position] = 1;
					_array[_position - 1] = 0;
					_position++;
				}
				else if(_position == _size)
				{					
					_array[_position] = 1;
					_array[_position - 1] = 0;
					_position = 0;
				}
				else
				{
					
				}
				break;
			case 4:
				// Fill
				break;
			case 5:
				//Cylon
				break;
			default:
			
				break;
		}
		
		return true;
	}
	
	else	return false;
}

uint8_t Pattern::getValue(uint8_t position)
{
	// Returns the value stored inside the array at the specified position
	
	return _array[position];
}
