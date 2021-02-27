/* Pattern Library
 * By: Cole Funseth
 *
 * This library is used to generate an array of values that can be used to 
 * drive various LED animations.  The array can be dynamically sized up to
 * 255 values depending on how many LEDs are in the circuit you wish to
 * animate.
 *
 * Styles include:
 *	0: All Off
 *	1: All On
 *	2: Blink
 *	3: Random 
 *	4: Chase
 *	5: Fill
 *	6: Empty
 *	7: Fill & Empty
 *	8: Random Fill & Empty
 *	9: Chew
 *	10: Chomp
 *	11: Chomp & Empty
 *
 * Additional styles can be added in the getUpdate() function as needed.
 *
 * Licensed under GNU GPL v3.0
*/

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
	// Resets the pattern except for the size
	
	_direction = 0;
	_speed = 500;	// Default the speed to 0.5 seconds
	_cycles = 0;
	_running = true;
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
	_cycles = 0;
	clear();
}

void Pattern::setDirection(uint8_t direction)
{
	// To-do: 
	// Update the pattern direction to be forward (0) or backwards (1)
	// Patterns will need to be updated to check this status
}

void Pattern::setSpeed(uint16_t speed)
{
	// Updates the time delay (in milliseconds) between each array element updating
	
	_speed = speed;
}

void Pattern::setSize(uint8_t size)
{
	// To-do: 
	// Add feature for dynamically adjusting the array size
	// May need to add another variable to track the original array size since we don't want to modify memory allocation
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
				// Blink
				// Toggles the array values on and off together
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
					_cycles++;
					for(uint8_t i = 0; i < _size; i++)
					{
						_array[i] = 0;
					}
				}
				break;
			case 3:
				// Random
				// Fills each element of the array with a random value
				for(uint8_t i = 0; i < _size; i++)
				{
					_array[i] = rand() % 2;
				}
				_cycles++;
				break;
			case 4:
				// Chase
				// Moves up the array only keeping one value high then loops to the beginning
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
					_cycles++;
				}
				else
				{
					
				}
				break;
			case 5:
				// Fill
				// Fills up the array sequentially then resets to the beginning
				if(_position == 0)
				{					
					_array[_position] = 1;
					_position++;
				}
				else if(_position < _size)
				{
					_array[_position] = 1;
					_position++;
				}
				else
				{					
					clear();
					_cycles++;
				}
				break;
			case 6:
				// Empty				
				if(_position == 0)
				{
					for(uint8_t i = 0; i < _size; i++) _array[i] = 1;
					
					_position++;
				}
				else if(_position < _size)
				{
					_array[(_size - 1) - (_position - 1)] = 0;
					
					_position++;
				}
				else
				{
					clear();
					_cycles++;
				}
				break;
			case 7:
				// Fill and Empty
				if(_position == 0 && _direction == 0)
				{					
					_array[_position] = 1;
					_position++;
				}
				else if(_position < _size && _direction == 0)
				{
					_array[_position] = 1;
					_position++;
				}
				else if(_position == _size && _direction == 0)
				{
					_direction = 1;
					_array[_position - 1] = 0;
					_position = _position - 2;
				}
				else if(_position > 0 && _direction == 1)
				{
					_array[_position] = 0;
					_position--;
				}
				else
				{					
					clear();
					_cycles++;
				}
				break;
			
			case 8:
				// Random Fill & Empty
				if(_position == 0 && _direction == 0)
				{
					_tempSize = random(5, _size);
					_array[_position] = 1;
					_position++;
				}
				else if(_position < _tempSize && _direction == 0)
				{
					_array[_position] = 1;
					_position++;
				}
				else if(_position == _tempSize && _direction == 0)
				{
					_direction = 1;
					_array[_position - 1] = 0;
					_position = _position - 2;
				}
				else if(_position > 0 && _direction == 1)
				{
					_array[_position] = 0;
					_position--;
				}
				else
				{					
					clear();
					_cycles++;
				}
				break;
			case 9:
				// Chew
				// "Classic" firing effect
				_tempSize = _size - 1;
				
				if(_position == 0 && _direction == 0)
				{					
					_array[_position] = 1;
					_array[_position + 1] = 1;
					_array[_position + 2] = 0;
					
					_array[_tempSize - _position] = 1;
					_array[_tempSize - (_position + 1)] = 1;
					_array[_tempSize - (_position + 2)] = 0;
					
					_position++;
				}
				else if(_position < ((_size / 2) - 1) && _direction == 0)
				{
					_array[_position - 1] = 0;
					_array[_position + 1] = 1;
					
					_array[_tempSize - (_position - 1)] = 0;
					_array[_tempSize - (_position + 1)] = 1;
					
					_position++;
				}
				else if(_position >= ((_size / 2) - 1) && _direction == 0)
				{
					_direction = 1;
					_position = _position - 1;
					
					_array[_position - 1] = 1;
					_array[_position + 1] = 0;
					
					_array[_tempSize - (_position - 1)] = 1;
					_array[_tempSize - (_position + 1)] = 0;
					
					_position--;
				}
				else if(_position > 2 && _direction == 1)
				{
					_array[_position - 1] = 1;
					_array[_position + 1] = 0;
					
					_array[_tempSize - (_position - 1)] = 1;
					_array[_tempSize - (_position + 1)] = 0;
					
					_position--;
				}
				else
				{					
					_direction = 0;
					_position = 0;
					
					_array[_position + 1] = 1;
					_array[_position + 2] = 1;
					_array[_position + 3] = 0;
										
					_array[_tempSize - (_position + 1)] = 1;
					_array[_tempSize - (_position + 2)] = 1;
					_array[_tempSize - (_position + 3)] = 0;
					
					_cycles++;
				}
				break;
			case 10:
				// Chomp
				_tempSize = _size - 1;
				
				if(_position == 0)
				{					
					_array[_position] = 1;
					_array[_tempSize - _position] = 1;
					
					_position++;
				}
				else if(_position < (_size / 2))
				{
					_array[_position] = 1;
					_array[_tempSize - (_position)] = 1;
					
					_position++;
				}
				else
				{					
					clear();
					_cycles++;
				}
				break;
			case 11:
				// Chomp & Empty
				_tempSize = _size - 1;
				
				if(_position == 0 && _direction == 0)
				{					
					_array[_position] = 1;					
					_array[_tempSize - _position] = 1;
					
					_position++;
				}
				else if(_position < (_size / 2) && _direction == 0)
				{
					_array[_position] = 1;
					_array[_tempSize - _position ] = 1;
					
					_position++;
				}
				else if(_position >= (_size / 2) && _direction == 0)
				{
					_direction = 1;					
					_position = 0;
					
					_array[_position] = 0;					
					_array[_tempSize - _position] = 0;
					
					_position++;
				}
				else if(_position < (_size / 2) && _direction == 1)
				{					
					_array[_position] = 0;					
					_array[_tempSize - _position] = 0;
					
					_position++;
				}
				else
				{
					clear();
					_cycles++;
				}
				break;
			
			case 12:
			
				// Future Pattern
				
				break;
			default:
			
				_style = 3;
				
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

uint8_t Pattern::getCycles(void)
{
	return _cycles;
}
