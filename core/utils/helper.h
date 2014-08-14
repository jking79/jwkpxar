/* This file contains helper classes which are used by API and DUT
   implementations to search API objects for certain properties */

#ifndef PXAR_HELPER_H
#define PXAR_HELPER_H

/** Cannot use stdint.h when running rootcint on WIN32 */
#if ((defined WIN32) && (defined __CINT__))
typedef int int32_t;
typedef short int int16_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
#else
#include <stdint.h>
#endif

#ifdef WIN32
#ifdef __CINT__
#include <Windows4Root.h>
#else
#include <Windows.h>
#endif // __CINT__
#else
#include <unistd.h>
#endif // WIN32

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

namespace pxar {
  /** Delay helper function
   *  Uses usleep() to wait the given time in milliseconds
   */
  void inline mDelay(uint32_t ms) {
    // Wait for the given time in milliseconds:
#ifdef WIN32
    Sleep(ms);
#else
    usleep(ms*1000);
#endif
  }

  /** Helper class to search vectors of pixelConfig, rocConfig and tbmConfig for 'enable' bit
   */
  class configEnableSet
  {
    const bool _isEnable;

  public:
  configEnableSet(const bool pEnable) : _isEnable(pEnable) {}

    template<class ConfigType>
      bool operator()(const ConfigType &config) const
      {
	return config.enable == _isEnable;
      }
  };

  /** Helper class to search vectors of pixelConfig for 'mask' bit
   */
  class configMaskSet
  {
    const bool _isMasked;

  public:
  configMaskSet(const bool pMask) : _isMasked(pMask) {}

    template<class ConfigType>
      bool operator()(const ConfigType &config) const
      {
	return config.mask == _isMasked;
      }
  };

  /** Helper class to search vectors of pixel or pixelConfig for 'column' and 'row' (and 'roc_id') values
   */
  class findPixelXY
  {
    const uint8_t _column;
    const uint8_t _row;
    const uint8_t _roc;
    const bool _check_roc;

  public:
  findPixelXY(const uint8_t pColumn, const uint8_t pRow)
    : _column(pColumn), _row(pRow), _roc(0), _check_roc(false) {}
  findPixelXY(const uint8_t pColumn, const uint8_t pRow, const uint8_t pRoc) 
    : _column(pColumn), _row(pRow), _roc(pRoc), _check_roc(true) {}

    template<class ConfigType>
      bool operator()(const ConfigType &config) const
      {
	if(_check_roc) return (config.row == _row) && (config.column == _column) && (config.roc_id == _roc);
	return (config.row == _row) && (config.column == _column);
      }
  };


  /** Helper class to search vectors of pixel or pixelConfig for
      'column' and 'row' values BEYOND the values given in the constructor
  */
  class findPixelBeyondXY
  {
    const uint8_t _column;
    const uint8_t _row;

  public:
  findPixelBeyondXY(const uint8_t pColumn, const uint8_t pRow) : _column(pColumn), _row(pRow) {}

    template<class ConfigType>
      bool operator()(const ConfigType &config) const
      {
	return (config.row > _row) || (config.column > _column);
      }
  };

  /** Helper class to search vectors of rocConfigs in order to find the correct i2c_address
   */
  class findRoc
  {
    const uint8_t _i2c_address;

  public:
  findRoc(const uint8_t pI2cAddress) : _i2c_address(pI2cAddress) {}

    template<class ConfigType>
      bool operator()(const ConfigType &config) const
      {
	return (config.i2c_address == _i2c_address);
      }
  };

  /** Helper function to return a printed list of an integer vector, used to shield
   *  debug code from being executed if debug level is not sufficient
   */
  template <typename T>
    std::string listVector(std::vector<T> vec, bool hex = false) {
    std::stringstream os;
    if(hex) { os << std::hex; }
    for(typename std::vector<T>::iterator it = vec.begin(); it != vec.end(); ++it) {
      if(hex) os << std::setw(4) << std::setfill('0');
      os << static_cast<int>(*it) << " ";
    }
    if(hex) { os << std::dec; }
    return os.str();
  }

}
#endif
