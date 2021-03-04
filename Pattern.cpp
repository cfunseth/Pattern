/* Pattern Library
 * By: Cole Funseth
 *
 * This library is used to generate an array of values that can be used to 
 * drive various light animations.  The array can be sized up to 255 values
 * depending on how many lights you wish to animate.
 *
 * Styles include:
 *	0:  Off
 *	1:  Solid
 *	2:  Blink
 *	3:  Random
 *	4:  Chase
 *	5:  Fill
 *	6:  Empty
 *	7:  Fill & Empty
 *	8:  Random Fill & Empty
 *	9:  Chew
 *	10: Chomp
 *	11: Chomp & Empty
 *
 * Additional styles can be added in the update() function as needed.
 *
 * Licensed under GNU GPL v3.0
*/

#include "Pattern.h"

Pattern::Pattern(uint8_t size)
{
	// Initiate the array that will contain the pattern values and then reset everything
	_size = size;
	_array = (uint8_t*)malloc(_size * sizeof(uint8_t));
	reset();
}

Pattern::~Pattern(void) 
{
	// Free up the memory we allocated for the array values
	free(_array);
}

void Pattern::clear(void)
{
  // Clears the array
  _position = 0;
  _direction = 0;
  
  for(uint8_t i = 0; i < _size; i++)
  {
    _array[i] = 0;
  } 

  _running = true;
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
	// Resets the pattern
	_cycles = 0;
  _limit = _size;
	_running = true;
	clear();
}

void Pattern::setStyle(uint8_t style)
{
	// Sets the style
	_style = style;
	reset();
}

void Pattern::setSpeed(uint16_t speed)
{
	// Sets the time delay (in milliseconds) between each array element
	_speed = speed;
}

void Pattern::setLimit(uint8_t limit)
{
	// Sets an upper limit on how many array elements are included in the pattern
  _limit = limit;
  _running = true;
  //clear();
}

bool Pattern::update(void)
{
	// This function should be called in every loop of the main program to keep the array updated
	if( (millis() - _timer) >= _speed && _running)
	{
		// Update timer to new value
		_timer = millis();
		
		switch(_style) {
			case 0:
				// Off
				clear();
        _running = false;  // No need to keep updating since it's a static style
				break;
			case 1:
				// Solid
        clear();
				for(uint8_t i = 0; i < _limit; i++)
				{
					_array[i] = 1;
				}
        _running = false;  // No need to keep updating since it's a static style
				break;
			case 2:
				// Blink
				// Toggles the array values on and off together
				// _position is used to track whether the values are high or low
				if(_position == 0)
				{
					_position = 1;
					for(uint8_t i = 0; i < _limit; i++)
					{
						_array[i] = 1;
					}
				}
				else
				{
					_position = 0;
					_cycles++;
					for(uint8_t i = 0; i < _limit; i++)
					{
						_array[i] = 0;
					}
				}
				break;
			case 3:
				// Random
				// Fills each element of the array with a random value
        clear();
				for(uint8_t i = 0; i < _limit; i++)
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
					_array[_limit] = 0;	// Make sure to clear the last value in the array after it loops around
					_position++;
				}
				else if(_position < _limit)
				{
					_array[_position] = 1;
					_array[_position - 1] = 0;
					_position++;
				}
				else if(_position == _limit)
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
				if(_position == 0)
				{
					_array[_position] = 1;
					_position++;
				}
				else if(_position < _limit)
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
					for(uint8_t i = 0; i < _limit; i++) _array[i] = 1;
					_position++;
				}
				else if(_position < _limit)
				{
					_array[_limit - _position] = 0;
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
				else if(_position < _limit && _direction == 0)
				{
					_array[_position] = 1;
					_position++;
				}
				else if(_position == _limit && _direction == 0)
				{
					_direction = 1;
					_position--;					
					_array[_position] = 0;
					_position--;
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
					_random = random(2, _limit);
					_array[_position] = 1;
					_position++;
				}
				else if(_position < _random && _direction == 0)
				{
					_array[_position] = 1;
					_position++;
				}
				else if(_position == _random && _direction == 0)
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
				// Bounce
        if(_position == 0)
        {
          _array[_position] = 1;
          //_array[_position + 1] = 1;

          _array[(_limit - 1) - _position] = 1;
          //_array[(_limit - 1) - (_position + 1)] = 1;
          
          _position++;
        }
        else if(_position < _limit)
        {
          
          _array[_position - 1] = 0;
          _array[(_limit - 1) - (_position - 1)] = 0;

          _array[_position] = 1;
          _array[(_limit - 1) - _position] = 1;      
          
          _position++;
        }
        
        else
        {
          _direction = 0;
          _position = 1;
          _cycles++;
        }
				break;
			case 10:
				// Chomp
				if(_position == 0)
				{					
					_array[_position] = 1;
					_array[(_limit - 1) - _position] = 1;
					
					_position++;
				}
				else if(_position < (_limit / 2))
				{
					_array[_position] = 1;
					_array[(_limit - 1) - _position] = 1;
					
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
				if(_position == 0 && _direction == 0)
				{					
					_array[_position] = 1;					
					_array[(_limit - 1) - _position] = 1;
					
					_position++;
				}
				else if(_position < (_limit / 2) && _direction == 0)
				{
					_array[_position] = 1;
					_array[(_limit - 1) - _position ] = 1;
					
					_position++;
				}
				else if(_position >= (_limit / 2) && _direction == 0)
				{
					_direction = 1;					
					_position = 0;
					
					_array[_position] = 0;					
					_array[(_limit - 1) - _position] = 0;
					
					_position++;
				}
				else if(_position < ((_limit - 1) / 2) && _direction == 1)
				{					
					_array[_position] = 0;					
					_array[(_limit - 1) - _position] = 0;
					
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
  // Returns how many times the style has completed a cycle.
  // Useful if you want a style to only run a set number of times.
	return _cycles;
}
